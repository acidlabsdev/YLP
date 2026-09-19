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
	    m_SandboxRoot(sandboxRoot),
	    m_Root(other)
	{
		if (sandboxRoot != other)
		{
			if (auto absPath = IO::MakeAbsPath(sandboxRoot, other); !absPath.has_value())
				m_Root = fs::path{};
		}
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

	void LuaPath::MakeDir() const
	{
		if (Exists() || !IsDir())
			return;

		IO::CreateFolder(m_Root);
	}

	std::string LuaPath::Filename() const
	{
		return m_Root.filename().string();
	}

	std::string LuaPath::Extension() const
	{
		return m_Root.extension().string();
	}

	LuaPath LuaPath::Parent() const
	{
		auto parent = m_Root.parent_path();
		if (parent == m_SandboxRoot)
			return LuaPath(m_SandboxRoot, m_SandboxRoot);

		auto absPath = IO::MakeAbsPath(m_SandboxRoot, parent);
		if (!absPath.has_value())
		{
			LOG_ERROR("The Path class is restricted to the module's root folder.");
			return {};
		}

		return LuaPath(m_SandboxRoot, *absPath);
	}

	LuaPath LuaPath::Join(std::string_view child) const
	{
		auto absPath = IO::MakeAbsPath(m_Root, child);
		if (!absPath.has_value())
			return {};

		return LuaPath(m_SandboxRoot, *absPath);
	}
}
