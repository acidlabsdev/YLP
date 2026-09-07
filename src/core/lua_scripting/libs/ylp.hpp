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

#include "../lua_library.hpp"
#include "../lua_module.hpp"
#include "../../memory/scanner.hpp"


namespace YLP::LuaJIT
{
	class LuaYLPLib : public LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

	public:
		void Register(sol::state& L) override
		{
			auto ylpTable = L["YLP"].get_or_create<sol::table>();

			ylpTable["RegisterProcessWatcher"] = [&](std::string_view processName, sol::protected_function callback, sol::optional<int> delayMs) {
				auto module = GetModuleFromLuaState(L);
				if (!module)
					return false;

				int ms = std::max(0, delayMs.value_or(0));
				module->RegisterProcessWatcher(
					processName.data(),
				    callback,
				    static_cast<std::chrono::milliseconds>(ms)
				);

				return true;
			};

			ylpTable["OnShutdown"] = [&](sol::protected_function callback) {
				auto module = GetModuleFromLuaState(L);
				if (!module)
					return false;

				module->RegisterShutdownCallback(callback);
			};
		}
	};

	LuaYLPLib _LuaYLPLib;
}
