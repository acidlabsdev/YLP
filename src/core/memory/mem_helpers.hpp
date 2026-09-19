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

//#include "mhde64.hpp"


namespace YLP::Memory
{
	uintptr_t AlignDown(uintptr_t addr, size_t pageSize);

	size_t AlignUp(uintptr_t addr, size_t len, size_t pageSize);

	/*
	size_t GetInstructionLength(uint8_t* addr, size_t maxBytes = 16);
	size_t ComputeInstructionSize(uint8_t* addr, size_t minBytes = 5, size_t maxBytes = 16);
	*/

	void FlushICache(HANDLE process, void* addr, SIZE_T len);
	void* VirtualAllocNear(HANDLE hProcess, void* hint, SIZE_T size);

	std::vector<uint8_t> Nop(size_t size);

	template<size_t N>
	constexpr std::array<uint8_t, N> Nop()
	{
		std::array<uint8_t, N> arr{};
		arr.fill(0x90);
		return arr;
	}

	BYTE* GenerateRandomAddress(DWORD imageSize);
}
