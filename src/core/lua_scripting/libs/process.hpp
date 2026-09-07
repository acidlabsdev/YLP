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
	class LuaProcLib : public LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

	public:
		void Register(sol::state& L) override
		{
			auto processUsertype = L.new_usertype<ProcessScanner>("Process",
			    sol::call_constructor, sol::constructors<ProcessScanner(std::string)>(),
			    "IsRunning", &ProcessScanner::IsProcessRunning,
			    "IsModuleLoaded", &ProcessScanner::IsModuleLoaded,
			    "GetModuleSize", &ProcessScanner::GetModuleSize,
			    "GetModuleBase", &ProcessScanner::GetBaseAddress,
			    "Update", &ProcessScanner::FindProcess);

			processUsertype["FindPattern"] = [&](
				ProcessScanner& self,
				const std::string& pattern,
				sol::optional<std::string> name,
				sol::optional<size_t> chunkSize)
			{
				return self.FindPattern(pattern, name.value_or(pattern), chunkSize.value_or(4096));
			};
		}
	};

	LuaProcLib _LuaProcLib;
}
