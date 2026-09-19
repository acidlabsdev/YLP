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

#include "pointer.hpp"


namespace YLP::Memory
{
	class BytePatch final
	{
	public:
		BytePatch(const Pointer& ptr, const std::span<uint8_t> values);

		bool Apply();
		bool Restore();

		BytePatch(const BytePatch&)            = delete;
		BytePatch& operator=(const BytePatch&) = delete;
		BytePatch(BytePatch&&)                 = delete;
		BytePatch& operator=(BytePatch&&)      = delete;

		bool IsApplied() const
		{
			return m_IsApplied;
		}

	private:
		Pointer m_Ptr;
		bool m_IsApplied{false};

		std::mutex m_Mutex{};
		std::size_t m_Size{};
		std::vector<uint8_t> m_Value{};
		std::vector<uint8_t> m_OriginalBytes{};
	};
}
