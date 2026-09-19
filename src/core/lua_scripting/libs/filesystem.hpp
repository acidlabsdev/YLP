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
#include "../lua_path.hpp"


namespace YLP::LuaJIT
{
	class LuaFsLib : public LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

	private:
		fs::path GetModuleRoot(sol::state& L)
		{
			auto mod = GetModuleFromLuaState(L);
			if (!mod)
				return {};

			return mod->GetRoot();
		}

		inline auto Iterator(sol::state& L, const LuaPath& path)
		{
			auto iterator = std::make_shared<std::filesystem::recursive_directory_iterator>(path.Get(), fs::directory_options::skip_permission_denied);
			auto end      = std::filesystem::recursive_directory_iterator{};
			auto modRoot  = GetModuleRoot(L);

			sol::state_view lua(L);
			return [iterator, end, modRoot, lua]() mutable -> sol::object {
				if (*iterator == end)
					return sol::lua_nil;

				LuaPath result(modRoot, (*iterator)->path());
				++(*iterator);

				return sol::make_object(lua, result);
			};
		};

	public:
		void Register(sol::state& L) override
		{
			/*@ylp.table Filesystem
			* description
				Provides file system functions. Paths are limited to the `/Plugins` folder only.

			* field Path Path
			
			* function MyRoot Returns the module's root path.
			* return Path

			* function IterDir Recursive directory iterator.
			* param path<Path>
			* return fun(): Path

			* function Rename
			* param oldPath<Path>
			* param newPath<Path>
			* return boolean successOrFailure
			* return string failReason

			* function Remove
			* param path<Path>
			* return boolean successOrFailure
			* return string failReason
			@*/
			auto luaFs = L["Filesystem"].get_or_create<sol::table>();

			luaFs["MyRoot"] = [&]()
			{
				auto modRoot = GetModuleRoot(L);
				return LuaPath(modRoot, modRoot);
			};

			luaFs["IterDir"] = [&](const LuaPath& path)
			{
				return Iterator(L, path);
			};

			luaFs["Rename"] = [&](const LuaPath& oldPath, const LuaPath& newPath)
			{
				if (!oldPath.Exists())
					return std::make_tuple(false, "File not found");

				bool success = IO::Rename(oldPath.Get(), newPath.Get());
				return std::make_tuple(success, success ? "" : "An error has occured.");
			};

			luaFs["Remove"] = [&](const LuaPath& path)
			{
				if (!path.Exists())
					return std::make_tuple(false, "File not found");

				bool success = IO::RemoveAll(path.Get());
				return std::make_tuple(success, success ? "" : "An error has occured.");
			};

			/*@ylp.class Path
			* description
				A path object limited to the `/Plugins` folder

			* constructor __call
			* param path<string>
			
			* operator div
			* param other<string>
			* return Path

			* method Exists
			* return boolean

			* method IsFile
			* return boolean

			* method IsDir
			* return boolean

			* method GetFilename
			* return string

			* method GetExtension
			* return string ext The file extension including the leading dot. Ex: `.json`. Returns empty string for folders.

			* method Join
			* param subPath<string>
			* return Path

			* method Open
			* param mode<openmode?>
			* return file*?
			* return string failReason An error message if the operation fails.

			* method IterDir Recursive directory iterator.
			* return fun(): Path

			* method Sha256Sum Calculates the file's SHA256 checksum. Throws if the path is not a file.
			* return string hash SHA256 checksum
			@*/
			auto pathCls = luaFs.new_usertype<LuaPath>("Path",
			    sol::call_constructor, sol::factories([&](const fs::path& path)
				{
					auto modRoot = GetModuleRoot(L);
					if (!IO::Exists(modRoot))
						return LuaPath();

					if (modRoot == path)
						return LuaPath(modRoot, modRoot);

					auto absPath = IO::MakeAbsPath(modRoot, path);
					if (!absPath.has_value())
					{
						L.safe_script("error(\"The Path class is restricted to the module's root folder.\", 2)");
						return LuaPath();
					}

					return LuaPath(modRoot, *absPath); 
				}));

			pathCls["GetFilename"]  = &LuaPath::Filename;
			pathCls["GetExtension"] = &LuaPath::Extension;
			pathCls["Exists"]       = &LuaPath::Exists;
			pathCls["IsFile"]       = &LuaPath::IsFile;
			pathCls["IsDir"]        = &LuaPath::IsDir;
			pathCls["MakeDir"]      = &LuaPath::MakeDir;
			pathCls["Join"]         = &LuaPath::Join;

			pathCls["Open"] = [](const LuaPath& self, std::string_view mode, sol::this_state s) {
				sol::state_view Lua(s);
				auto io                        = Lua["io"];
				sol::protected_function ioOpen = io["open"]; // we already store the original io.open in LuaModule but this bitch kept crashing when I called the function here
				return ioOpen(self.Get().u8string().c_str(), mode);
			};

			pathCls["ToString"] = [](const LuaPath& self) {
				return self.Get().string();
			};

			pathCls["IterDir"] = [&](const LuaPath& self) {
				return Iterator(L, self);
			};

			pathCls["Sha256Sum"] = [&](const LuaPath& self) {
				if (!self.IsFile())
				{
					L.safe_script("error('Attempt to calculate sha256 checksum of a non-file Path object.')");
					return std::string(); // why do-I have to return bruh
				}
				return Utils::CalcSha256(self.Get());
			};

			pathCls["__tostring"] = [](const LuaPath& self) {
				return self.Get().string();
			};

			pathCls["__eq"] = [](const LuaPath& self, const LuaPath& other) {
				return self == other;
			};

			pathCls["__div"] = [](const LuaPath& self, std::string_view sub) {
				return self.Join(sub);
			};
		}
	};

	LuaFsLib _LuaFsLib;
}
