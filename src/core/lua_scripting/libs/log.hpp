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


namespace YLP::LuaJIT
{
	class LuaLogLib : public LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

	private:
		static inline std::string tostr(sol::state& L, sol::variadic_args args)
		{
			auto moduleName = L["whodis"].get<std::string>();
			std::string output;
			for (auto arg : args)
			{
				if (!output.empty())
					output += '\t';

				sol::object obj(arg);
				sol::protected_function tostring = L["tostring"];
				sol::protected_function_result r = tostring(arg);
				output += r.valid() ? r.get<std::string>() : "";
			}
			return "[" + moduleName + "/main.lua]: " + output;
		}

	public:
		void Register(sol::state& L) override
		{
			L["print"] = [&](sol::variadic_args args) {
				LOG_INFO(tostr(L, args));
			};

			/* @ylp.table log
			* description
				Provides functions to output text to console and log file.
			@*/
			auto log = L["log"].get_or_create<sol::table>();

			/* @ylp.function log.info Logs an information message.
			* param ...<any> Any number of arguments of any type.
			@*/
			log["info"] = [&](sol::variadic_args args) {
				LOG_INFO(tostr(L, args));
			};

			/* @ylp.function log.warning Logs a warning message.
			* param ...<any> Any number of arguments of any type.
			@*/
			log["warning"] = [&](sol::variadic_args args) {
				LOG_WARN(tostr(L, args));
			};

			/* @ylp.function log.debug Logs a debug message.
			* param ...<any> Any number of arguments of any type.
			@*/
			log["debug"] = [&](sol::variadic_args args) {
				LOG_DEBUG(tostr(L, args));
			};

			/* @ylp.function log.error Logs an error message.
			* param ...<any> Any number of arguments of any type.
			@*/
			log["error"] = [&](sol::variadic_args args) {
				LOG_ERROR(tostr(L, args));
			};
		}
	};

	LuaLogLib _LuaLogLib;
}
