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


namespace fs = std::filesystem;

namespace YLP::LuaJIT
{
	class LuaPathError : public std::runtime_error
	{
	public:
		using std::runtime_error::runtime_error;
	};

	class LuaPath
	{
	public:
		LuaPath() = default;
		explicit LuaPath(const fs::path& sandboxRoit, const fs::path& other);

		const fs::path& Get() const noexcept;

		bool Exists() const;
		bool IsFile() const;
		bool IsDir() const;
		bool MakeDir() const;
		bool MakeDirs() const;

		std::string Filename() const;
		std::string Extension() const;
		std::string Stem() const;
		uintmax_t Size() const;

		LuaPath Parent() const;
		LuaPath Join(const std::string& sub) const;

		bool operator==(const LuaPath& other) const noexcept
		{
			return m_Root == other.Get();
		}

		LuaPath operator/(const std::string& sub) const
		{
			return Join(sub);
		}

	private:
		fs::path m_SandboxRoot{};
		fs::path m_Root{};
	};
}
