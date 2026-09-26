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


#include "lua_path.hpp"


namespace YLP::LuaJIT
{
	LuaPath::LuaPath(const fs::path& sandboxRoot, const fs::path& other) :
	    m_SandboxRoot(sandboxRoot)
	{
		if (sandboxRoot == other)
		{
			m_Root = other;
			return;
		}

		auto absPath = IO::MakeAbsPath(sandboxRoot, other);
		if (!absPath.has_value())
		{
			LOG_ERROR("[LuaPath]: The Path class is restricted to the module's root folder. Path '{}' is not allowed.", other.string());
			throw LuaPathError("The Path class is restricted to the module's root folder.");
		}

		m_Root = *absPath;
	}

	const fs::path& LuaPath::Get() const noexcept
	{
		return m_Root;
	}

	bool LuaPath::Exists() const
	{
		return IO::Exists(m_Root);
	}

	bool LuaPath::IsFile() const
	{
		return IO::IsFile(m_Root);
	}

	bool LuaPath::IsDir() const
	{
		return IO::IsDir(m_Root);
	}

	bool LuaPath::MakeDir() const
	{
		if (Exists())
			return true;

		return IO::CreateFolder(m_Root);
	}

	bool LuaPath::MakeDirs() const
	{
		if (Exists())
			return true;

		return IO::CreateFolders(m_Root);
	}

	std::string LuaPath::Filename() const
	{
		return m_Root.filename().string();
	}

	std::string LuaPath::Stem() const
	{
		return m_Root.filename().stem().string();
	}

	std::string LuaPath::Extension() const
	{
		return m_Root.extension().string();
	}

	uintmax_t LuaPath::Size() const
	{
		return fs::file_size(m_Root);
	}

	LuaPath LuaPath::Parent() const
	{
		auto parent = m_Root.parent_path();
		if (parent == m_SandboxRoot)
			return LuaPath(m_SandboxRoot, m_SandboxRoot);

		return LuaPath(m_SandboxRoot, parent);
	}

	LuaPath LuaPath::Join(const std::string& sub) const
	{
		fs::path other = fs::path(sub);
		if (!m_Root.string().empty())
			other = m_Root / sub;

		return LuaPath(m_SandboxRoot, other);
	}
}
