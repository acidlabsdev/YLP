// Copyright (C) 2025 SAMURAI (xesdoog) & Contributors
// This file is part of YLP.
//
// YLP is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// YLP is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with YLP.  If not, see <https://www.gnu.org/licenses/>.
//
// Credit goes to https://github.com/YimMenu/YimMenuV2 for most of this code.


#include "lua_module.hpp"
#include "lua_mgr.hpp"


namespace YLP::LuaJIT
{
	// https://sol2.readthedocs.io/en/latest/exceptions.html
	static int ExceptionHandler(lua_State* L, sol::optional<const std::exception&> maybe_exception, sol::string_view description)
	{
		if (maybe_exception)
		{
			const std::exception& e = *maybe_exception;
			LOG_ERROR(e.what());
		}
		else
		{
			LOG_ERROR(description);
		}
		return sol::stack::push(L, description);
	}

	static inline void PanicHandler(sol::optional<std::string> maybe_msg)
	{
		LOG_ERROR("Lua is in a panic state and will now abort the application");
		if (maybe_msg)
		{
			const std::string& msg = maybe_msg.value();
			LOG_ERROR("error message: {}", msg);
		}
	}

	static int TracebackErrorHandler(lua_State* L)
	{
		std::string msg = "An unknown error has triggered the error handler";
		sol::optional<sol::string_view> maybetopmsg = sol::stack::unqualified_check_get<sol::string_view>(L, 1, &sol::no_panic);
		if (maybetopmsg)
		{
			const sol::string_view& topmsg = maybetopmsg.value();
			msg.assign(topmsg.data(), topmsg.size());
		}
		luaL_traceback(L, L, msg.c_str(), 1);
		sol::optional<sol::string_view> maybetraceback = sol::stack::unqualified_check_get<sol::string_view>(L, -1, &sol::no_panic);
		if (maybetraceback)
		{
			const sol::string_view& traceback = maybetraceback.value();
			msg.assign(traceback.data(), traceback.size());
		}
		LOG_ERROR(msg);
		return sol::stack::push(L, msg);
	}

	template<size_t N>
	static constexpr auto DisabledLuaFunc(const char (&funcName)[N])
	{
		return [funcName](sol::this_state state, sol::variadic_args args)
		{
			sol::state_view Lua(state);
			Lua.safe_script(std::format("error(\"Can not invoke '{}', a deleted function.\", 2)", funcName));
		};
	}

	LuaModule::LuaModule(fs::path root) :
		m_LuaState(sol::state{}),
		m_Root(root),
		m_Entry(root / "main.lua"),
		m_Name(root.filename().string())
	{
		m_LuaState.open_libraries(
		    sol::lib::base,
		    sol::lib::bit32,
		    sol::lib::coroutine,
		    sol::lib::ffi,
		    sol::lib::io,
		    sol::lib::jit,
		    sol::lib::math,
		    sol::lib::os,
		    sol::lib::package,
		    sol::lib::string,
		    sol::lib::table,
		    sol::lib::utf8);

		m_LuaState["this*"]  = reinterpret_cast<void*>(this);
		m_LuaState["whodis"] = m_Name;

		m_LuaState.set_exception_handler(ExceptionHandler);
		m_LuaState.set_panic(sol::c_call<decltype(&PanicHandler), &PanicHandler>);
		lua_CFunction traceback_function = sol::c_call<decltype(&TracebackErrorHandler), &TracebackErrorHandler>;
		sol::protected_function::set_default_handler(sol::object(m_LuaState.lua_state(), sol::in_place, traceback_function));

		m_PathWatcher = PathWatcher(root / "main.lua", 1s);
		auto strlib   = m_LuaState["string"];
		m_LuaStrFmt   = strlib["format"];

		LuaManager::RegisterLibraries(m_LuaState);
	}

	LuaModule::~LuaModule()
	{
		std::unique_lock lock(m_TaskMutex);
		m_Tasks.clear();
		m_ProcessWatchers.clear();

		for (auto& func : m_ShutdownCallbacks)
		{
			if (func.valid())
				func();
		}

		for (auto& patch : m_BytePatches)
			patch->Restore();

		m_BytePatches.clear();
		m_GuiCallback = {};
	}

	std::string LuaModule::FormatLuaString(const std::string& fmt, sol::variadic_args args)
	{
		if (!m_LuaStrFmt.valid())
			return fmt;

		auto result = m_LuaStrFmt(fmt, args);
		if (!result.valid())
			return fmt;

		return result.get<std::string>();
	}

	bool LuaModule::Load()
	{
		if (!Config().enableScripting)
			return false;

		auto result = m_LuaState.safe_script_file(m_Entry.string(), &sol::script_pass_on_error, sol::load_mode::text);
		if (!result.valid())
		{
			sol::error e = result;
			LOG_ERROR("Failed to load module '{}' : {}", m_Name, e.what());
			m_LoadState = BROKEN;
			return false;
		}

		LOG_INFO("Loaded module '{}'", m_Name);
		m_LoadState = RUNNING;
		return true;
	}

	void LuaModule::Reload()
	{
		m_LoadState = WANTS_RELOAD;
	}

	void LuaModule::Unload()
	{
		m_LoadState = WANTS_UNLOAD;
	}

	void LuaModule::SetAsBroken(std::optional<std::string> errorMsg)
	{
		m_LoadState = BROKEN;
		m_LastError = errorMsg.value_or("");
	}

	void LuaModule::Disable()
	{
		m_LoadState = WANTS_DISABLE;
	}

	const std::string LuaModule::GetErrorMsg() const
	{
		return m_LastError;
	}

	const bool LuaModule::IsSafeToUnload() const noexcept
	{
		return !m_IsRunningTasks;
	}

	lua_State* LuaModule::GetLuaState()
	{
		return m_LuaState.lua_state();
	}

	const LuaModule::eLuaLoadState LuaModule::GetLoadState() const noexcept
	{
		return m_LoadState;
	}

	std::string_view LuaModule::GetName() const noexcept
	{
		return m_Name;
	}

	fs::path LuaModule::GetRoot() const noexcept
	{
		return m_Root;
	}

	void LuaModule::SandboxOsLib()
	{
		auto os = m_LuaState["os"];
		sol::table sandboxedOs(m_LuaState, sol::create);

		sandboxedOs["clock"]    = os["clock"];
		sandboxedOs["date"]     = os["date"];
		sandboxedOs["difftime"] = os["difftime"];
		sandboxedOs["time"]     = os["time"];

		sandboxedOs["rename"] = [this](const std::string& oldname, const std::string& newname) -> sol::object
		{
			const auto oldPath = IO::MakeAbsPath(m_Root, oldname);
            const auto newPath = IO::MakeAbsPath(m_Root, newname);

			if (!oldPath || !newPath)
			{
				LOG_WARN("os.rename is restricted to the module's root only.");
				return sol::make_object(m_LuaState, std::make_tuple(false, "Invalid file path."));
			}

			try
			{
				std::filesystem::rename(oldPath.value(), newPath.value());
				return sol::make_object(m_LuaState, true);
			}
			catch (const std::exception& e)
			{
				return sol::make_object(m_LuaState, std::make_tuple(false, e.what()));
			}
		};

		m_LuaState["os"] = sandboxedOs;
	}

	void LuaModule::SandboxIoLib()
	{
		auto ioLib  = m_LuaState["io"];
		m_LuaIoOpen = ioLib["open"];

		sol::table sandboxedIo(m_LuaState, sol::create);
		sandboxedIo["open"] = [this](const std::string& filename, const std::string& mode)
		{
			const auto absPath = IO::MakeAbsPath(m_Root, filename);
			if (!absPath.has_value())
				return std::make_tuple(sol::reference(m_LuaState, sol::lua_nil), "io is restricted to the module's root only.");

			LOG_DEBUG("sandbox io.open: BEFORE original");

			auto result = m_LuaIoOpen(absPath->u8string().c_str(), mode);

			LOG_DEBUG("sandbox io.open: AFTER original");

			if (!result.valid())
			{
				sol::error err = result;
				LOG_ERROR("original io.open failed: {}", err.what());

				return std::make_tuple(sol::reference(m_LuaState, sol::lua_nil), err.what());
			}

			LOG_DEBUG("sandbox io.open: result valid");

			return std::make_tuple(result.get<sol::reference>(), "");
		};

		sandboxedIo["exists"] = [this](const std::string& filename) -> bool {
			const auto absPath = IO::MakeAbsPath(m_Root, filename);
			if (!absPath)
			{
				LOG_ERROR("io is restricted to the module's root only.");
				return false;
			}

			return IO::Exists(*absPath);
		};

		m_LuaState["io"] = sandboxedIo;
	}

	// https://github.com/Mr-X-GTA/YimMenu/blob/master/src/lua/lua_module.cpp#L175
	void LuaModule::SetRequireFolder(const fs::path& pluginsPath)
	{
		std::string searchPath = pluginsPath.string() + "/?.lua;";
		for (const auto& entry : std::filesystem::recursive_directory_iterator(pluginsPath, std::filesystem::directory_options::skip_permission_denied))
		{
			if (!entry.is_directory())
				continue;

			if (std::filesystem::relative(entry, pluginsPath).wstring().contains(L"disabled"))
				continue;

			searchPath += entry.path().string() + "/?.lua;";
		}

		searchPath.pop_back();
		m_LuaState["package"]["path"] = searchPath;
	}

	// https://github.com/Mr-X-GTA/YimMenu/blob/master/src/lua/lua_module.cpp#L321
	void LuaModule::SandboxAPI(const fs::path& pluginsPath)
	{
		m_LuaState["load"]       = DisabledLuaFunc("load");
		m_LuaState["loadstring"] = DisabledLuaFunc("loadstring");
		m_LuaState["loadfile"]   = DisabledLuaFunc("loadfile");
		m_LuaState["dofile"]     = DisabledLuaFunc("dofile");

		m_LuaState["package"]["loadlib"]      = DisabledLuaFunc("package.loadlib");
		m_LuaState["package"]["cpath"]        = "";
		m_LuaState["package"]["searchers"][3] = DisabledLuaFunc("package.searcher C");
		m_LuaState["package"]["searchers"][4] = DisabledLuaFunc("package.searcher Croot");

		SetRequireFolder(pluginsPath);
		SandboxIoLib();
		SandboxOsLib();
	}

	const bool LuaModule::IsRunningTasks() const noexcept
	{
		return m_IsRunningTasks;
	}

	void LuaModule::Execute(const std::string_view& code)
	{
		if (!Config().enableScripting)
			return;

		if (auto result = m_LuaState.safe_script(code.data(), &sol::script_pass_on_error); !result.valid())
		{
			sol::error error = result;
			LOG_ERROR(error.what());
		}
	}

	void LuaModule::RegisterTask(sol::protected_function func, std::chrono::milliseconds delayMs, std::vector<sol::object> args)
	{
		std::unique_lock lock(m_TaskMutex);
		auto thread = sol::thread::create(m_LuaState);
		auto co     = sol::coroutine(m_LuaState, func);
		m_Tasks.push_back({
			std::move(thread),
			std::move(co),
		    std::chrono::steady_clock::now() + delayMs,
		    std::move(args)
		});
	}

	void LuaModule::AddBytePatch(std::shared_ptr<BytePatch> patch)
	{
		m_BytePatches.emplace_back(std::move(patch));
	}

	void LuaModule::RegisterProcessWatcher(const std::string& processName, sol::protected_function callback, std::chrono::milliseconds delayMs)
	{
		m_ProcessWatchers.push_back({processName, std::move(callback), delayMs});
	}

	void LuaModule::RegisterShutdownCallback(sol::protected_function callback)
	{
		m_ShutdownCallbacks.push_back(std::move(callback));
	}

	void LuaModule::DispatchProcessWatchers(const std::chrono::steady_clock::time_point& tickStart)
	{
		if (tickStart - m_LastProcessPollTime < 500ms)
			return;

		std::erase_if(m_ProcessWatchers, [this](const auto& watcher) {
			if (!PsUtils::GetProcessId(watcher.m_ProcessName).has_value())
				return false;

			if (watcher.m_Callback.valid())
			{
				auto proc = sol::make_object<ProcessScanner>(m_LuaState, watcher.m_ProcessName);
				RegisterTask(watcher.m_Callback, watcher.m_CallbackDelayMs, {std::move(proc)});
			}

			return true;
		});

		m_LastProcessPollTime = tickStart;
	}

	void LuaModule::Tick()
	{
		const auto now = std::chrono::steady_clock::now();
		m_IsRunningTasks.store(true);
		DispatchProcessWatchers(now);

		{
			std::scoped_lock lock(m_TaskMutex);
			for (auto it = m_Tasks.begin(); it != m_Tasks.end();)
			{
				if (!g_Running)
					break;

				if (now < it->m_NextRun)
				{
					++it;
					continue;
				}

				auto result = it->m_Coroutine(sol::as_args(it->m_Args));
				if (!result.valid())
				{
					sol::error error = result;
					LOG_ERROR(error.what());
					it = m_Tasks.erase(it);
					continue;
				}

				if (!it->m_Coroutine.runnable())
				{
					it = m_Tasks.erase(it);
					continue;
				}

				const auto delay = result.return_count() > 0 ? result[0] : 0;
				it->m_NextRun = now + std::chrono::milliseconds(delay);
				++it;
			}
		}

		if (Config().autoReloadLuaModules)
		{
			m_PathWatcher.PollOnce([this](const fs::path& _unused, PathWatcher::ePathStatus status) {
				switch (status)
				{
				case PathWatcher::ePathStatus::Created:
				case PathWatcher::ePathStatus::Modified:
				case PathWatcher::ePathStatus::Erased:
					m_LoadState = WANTS_RELOAD;
					break;
				}
			});
		}

		if (m_UnloadFromCode)
		{
			m_UnloadFromCode = false;
			m_LoadState    = WANTS_UNLOAD;
		}

		m_IsRunningTasks.store(false);
	}
}
