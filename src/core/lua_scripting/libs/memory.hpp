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
#include "../../memory/pointer.hpp"


namespace YLP::LuaJIT
{
	// TODO
	class LuaMemLib : public LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

	public:
		void Register(sol::state& L) override
		{
			// clang-format off

			auto ptrUsertype = L.new_usertype<Pointer>("Pointer", sol::no_constructor,
				sol::meta_function::addition, &Pointer::Add,
				sol::meta_function::subtraction, &Pointer::Sub,
				"Add", &Pointer::Add,
				"Sub", &Pointer::Sub,
				"Rip", &Pointer::Rip,
				"Dereference", &Pointer::Dereference,
				"GetAddress", &Pointer::GetAddress
			);

			// clang-format on

			ptrUsertype["__eq"] = sol::overload(
			    [](Pointer& self, Pointer& rh) {
				    return self.GetAddress() == rh.GetAddress();
			    },
			    [](Pointer& self, uintptr_t& rh) {
				    return self.GetAddress() == rh;
			    });

			ptrUsertype["IsNull"] = [](Pointer& self) {
				return self.GetAddress() == 0;
			};

			ptrUsertype["ReadString"] = [](Pointer& self, sol::optional<size_t> maxLength) {
				return self.Read<std::string>(maxLength.value_or(64));
			};

			ptrUsertype["ReadInt8"] = [](Pointer& self) {
				return self.Read<int8_t>();
			};
			ptrUsertype["ReadUint8"] = [](Pointer& self) {
				return self.Read<uint8_t>();
			};
			ptrUsertype["ReadInt16"] = [](Pointer& self) {
				return self.Read<int16_t>();
			};
			ptrUsertype["ReadUint16"] = [](Pointer& self) {
				return self.Read<uint16_t>();
			};
			ptrUsertype["ReadInt32"] = [](Pointer& self) {
				return self.Read<int32_t>();
			};
			ptrUsertype["ReadUint32"] = [](Pointer& self) {
				return self.Read<uint32_t>();
			};
			ptrUsertype["ReadInt64"] = [](Pointer& self) {
				return self.Read<int64_t>();
			};
			ptrUsertype["ReadUint64"] = [](Pointer& self) {
				return self.Read<uint64_t>();
			};
			ptrUsertype["ReadFloat"] = [](Pointer& self) {
				return self.Read<float>();
			};
			ptrUsertype["ReadDouble"] = [](Pointer& self) {
				return self.Read<double>();
			};

			ptrUsertype["WriteString"] = [](Pointer& self, std::string arg, sol::optional<size_t> maxLength) {
				self.Write<std::string>(arg, maxLength.value_or(64));
			};

			ptrUsertype["WriteInt8"] = [](Pointer& self, int8_t arg) {
				self.Write<int8_t>(arg);
			};
			ptrUsertype["WriteUint8"] = [](Pointer& self, uint8_t arg) {
				self.Write<uint8_t>(arg);
			};
			ptrUsertype["WriteInt16"] = [](Pointer& self, int16_t arg) {
				self.Write<int16_t>(arg);
			};
			ptrUsertype["WriteUint16"] = [](Pointer& self, uint16_t arg) {
				self.Write<uint16_t>(arg);
			};
			ptrUsertype["WriteInt32"] = [](Pointer& self, int32_t arg) {
				self.Write<int32_t>(arg);
			};
			ptrUsertype["WriteUint32"] = [](Pointer& self, uint32_t arg) {
				self.Write<uint32_t>(arg);
			};
			ptrUsertype["WriteInt64"] = [](Pointer& self, int64_t arg) {
				self.Write<int64_t>(arg);
			};
			ptrUsertype["WriteUint64"] = [](Pointer& self, uint64_t arg) {
				self.Write<uint64_t>(arg);
			};
			ptrUsertype["WriteFloat"] = [](Pointer& self, float arg) {
				self.Write<float>(arg);
			};
			ptrUsertype["WriteDouble"] = [](Pointer& self, double arg) {
				self.Write<double>(arg);
			};
		}
	};

	LuaMemLib _LuaMemLib;
}
