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


#include "mem_helpers.hpp"


namespace YLP::Memory
{
	uintptr_t AlignDown(uintptr_t addr, size_t pageSize)
	{
		return addr & ~(pageSize - 1);
	}

	size_t AlignUp(uintptr_t addr, size_t len, size_t pageSize)
	{
		uintptr_t end       = addr + len;
		uintptr_t pageStart = AlignDown(addr, pageSize);
		uintptr_t pageEnd   = (end + pageSize - 1) & ~(pageSize - 1);
		return pageEnd - pageStart;
	}

	/*
	size_t GetInstructionLength(uint8_t* addr, size_t maxBytes)
	{
		mhde64s hs{};
		size_t len = mhde64_disasm(addr, &hs);
		if (len == 0 || len > maxBytes)
		{
			LOG_WARN("Invalid instruction length at 0x{:X}", static_cast<void*>(addr));
			return -1;
		}

		return len;
	}

	size_t ComputeInstructionSize(uint8_t* addr, size_t minBytes, size_t maxBytes)
	{
		size_t total = 0;
		while (total < minBytes)
		{
			mhde64s hs{};
			size_t len = mhde64_disasm(addr + total, &hs);
			if (len == 0)
				return minBytes;

			total += len;
			if (total > 64)
				return total;
		}

		return (total <= maxBytes) ? total : maxBytes;
	}
	*/

	std::vector<uint8_t> Nop(size_t size)
	{
		return std::vector<uint8_t>(size, 0x90);
	}

	void FlushICache(HANDLE process, void* instAddr, SIZE_T len)
	{
		FlushInstructionCache(process, instAddr, len);
	}

	void* VirtualAllocNear(HANDLE hProcess, void* hint, SIZE_T size)
	{
		const uintptr_t targetAddr = reinterpret_cast<uintptr_t>(hint);
		const uintptr_t maxDelta   = 0x7FFFFFFF;
		const uintptr_t start      = (targetAddr > maxDelta) ? (targetAddr - maxDelta) : 0;
		const uintptr_t end        = targetAddr + maxDelta;
		const SIZE_T step          = 0x10000;

		for (uintptr_t addr = targetAddr; addr >= start; addr = (addr > step ? addr - step : 0))
		{
			void* p = VirtualAllocEx(hProcess, reinterpret_cast<void*>(addr), size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			if (p)
				return p;
			if (addr == 0)
				break;
		}

		for (uintptr_t addr = targetAddr + step; addr <= end; addr += step)
		{
			void* p = VirtualAllocEx(hProcess, reinterpret_cast<void*>(addr), size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			if (p)
				return p;
		}

		return nullptr;
	}

	BYTE* GenerateRandomAddress(DWORD imageSize)
	{
		static std::random_device rd;
		static std::mt19937_64 gen(rd() ^ GetTickCount64());
		std::uniform_int_distribution<ULONG_PTR> dist(0x10000000ULL, 0x7FF00000000ULL);
		ULONG_PTR baseAddr  = dist(gen); baseAddr &= ~0xFFFFULL;

		if (baseAddr > (0x7FFFFFFF0000ULL - imageSize))
			baseAddr = 0x10000000ULL;

		return reinterpret_cast<BYTE*>(baseAddr);
	}
}
