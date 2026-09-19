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


#pragma once

#include "core/updater.hpp"
#include "core/injector/injector.hpp"
#include "core/memory/scanner.hpp"

#include "../lua_library.hpp"
#include "../lua_module.hpp"


namespace YLP::LuaJIT
{
	class LuaYLPLib : public LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

	public:
		void Register(sol::state& L) override
		{
			/* @ylp.table YLP
			* description
				### YLP namespace

			* function GetVersion
			* return string version The current YLP version.

			* function RegisterProcessWatcher Registers a callback to be executed once when a process is first seen.~~You can call `Task.Yield` and `Task.Sleep` in your callback function.
			* param processName<string> The name of the process
			* param callback<fun(process: Process)> The function to execute. YLP will pass a Process object to the function as an argument.
			* param delay<integer?> Optional delay in milliseconds
			* return boolean success Whether the registration was successful or not.

			* function RegisterGui Registers an ImGui callback to be drawn in the 'Lua Scripting' tab.
			* param callback<function> The UI to draw. ImGui functions can only be called here.

			* function InjectDll Injects a dynamic link library into a target process.
			* param dllPath<Path> DLL file path. Must be a [Path](lua://Path) object.
			* param processName<string> Name of the target process.
			* param manualMap<boolean?> Use manual mapping instead of standard `LoadLibrary`
			* param manualMapArgs<{ eraseHeaders: boolean?, enableSEH: boolean?, randomizeBaseAddress: boolean?}?> Optional manual mapping configuration.
			* return boolean status Success or failure.
			* return string? failReason Optional error message if injection fails.

			* function OnShutdown Registers a function to be executed when YLP is shutting down.
			* param callback<function> The function to execute

			* function UnloadThisModule Unloads the caller module.~~The module can only be loaded again from the Settings tab in YLP's UI.
			@*/
			auto ylpTable = L["YLP"].get_or_create<sol::table>();

			ylpTable["GetVersion"] = []()
			{
				return YLPUpdater.GetLocalVersion().ToString();
			};

			ylpTable["RegisterProcessWatcher"] = [&](const std::string& processName, sol::protected_function callback, sol::optional<int> delayMs)
			{
				auto mod = GetModuleFromLuaState(L);
				if (!mod)
					return false;

				int ms = std::max(0, delayMs.value_or(0));
				mod->RegisterProcessWatcher(processName, callback, std::chrono::milliseconds(ms));
				return true;
			};

			ylpTable["RegisterGui"] = [&](sol::protected_function callback)
			{
				auto mod = GetModuleFromLuaState(L);
				if (!mod)
					return;

				auto name = mod->GetName();
				if (name == "CodeExecutor")
				{
					LOG_ERROR("CodeExecutor can not register GUIs.");
					return;
				}

				if (mod->m_GuiCallback.valid())
				{
					LOG_WARN("Module '{}' already has a GUI!", name);
					return;
				}

				mod->m_GuiCallback = std::move(callback);
			};

			ylpTable["InjectDll"] = [&](const LuaPath& dllPath, const std::string& processName, bool manualMap, sol::optional<sol::table> manualMappingConfig)
			{
				auto args = manualMappingConfig.value_or(sol::table());

				Injector::InjectorConfig cfg = {
				    .m_Mode             = manualMap ? 1 : 0,
				    .m_WipePE           = args["eraseHeaders"].get_or(false),
				    .m_RandomizeAddress = args["randomizeBaseAddress"].get_or(false),
				    .m_EnableSEH        = args["enableSEH"].get_or(false)
				};

				Injector::InjectResult res = Injector::Inject(processName, dllPath.Get(), cfg);
				return std::make_tuple(res.m_Success, res.m_Message);
			};

			ylpTable["OnShutdown"] = [&](sol::protected_function callback)
			{
				if (auto module = GetModuleFromLuaState(L))
					module->RegisterShutdownCallback(callback);
			};

			ylpTable["UnloadThisModule"] = [&]()
			{
				if (auto module = GetModuleFromLuaState(L))
					module->Unload();
			};
		}
	};

	LuaYLPLib _LuaYLPLib;
}
