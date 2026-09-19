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


#include "byte_patch.hpp"


namespace YLP::Memory
{
	BytePatch::BytePatch(const Pointer& ptr, const std::span<uint8_t> values) :
	    m_Ptr(ptr),
	    m_Size(values.size()),
	    m_Value(values.begin(), values.end())
	{
	}

	bool BytePatch::Apply()
	{
		if (m_IsApplied)
			return true;

		std::lock_guard lock(m_Mutex);

		m_OriginalBytes = m_Ptr.ReadBytes(m_Value.size());
		if (m_OriginalBytes.empty() && !m_Value.empty())
			return false;

		if (!m_Ptr.WriteBytes(m_Value))
			return false;

		m_IsApplied = true;
		return true;
	}

	bool BytePatch::Restore()
	{
		if (!m_IsApplied)
			return true;

		std::lock_guard lock(m_Mutex);

		if (!m_Ptr.WriteBytes(m_OriginalBytes))
			return false;

		m_IsApplied = false;
		return true;
	}
}
