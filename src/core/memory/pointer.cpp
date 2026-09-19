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


#include "pointer.hpp"


namespace YLP::Memory
{
	Pointer::Pointer(HANDLE hProcess, uintptr_t address) :
	    m_ProcessHandle(hProcess),
	    m_Address(address)
	{
	}

	Pointer Pointer::Add(int32_t offset)
	{
		return Pointer(m_ProcessHandle, m_Address + offset);
	}

	Pointer Pointer::Sub(int32_t offset)
	{
		return Pointer(m_ProcessHandle, m_Address - offset);
	}

	Pointer Pointer::Rip()
	{
		int32_t rel = Read<int32_t>();
		return Pointer(m_ProcessHandle, m_Address + rel + 4);
	}

	Pointer Pointer::Dereference()
	{
		return Pointer(m_ProcessHandle, Read<uintptr_t>());
	}

	uintptr_t Pointer::GetAddress() const noexcept
	{
		return m_Address;
	}
	

	std::vector<uint8_t> Pointer::ReadBytes(size_t len)
	{
		std::vector<uint8_t> out(len);
		SIZE_T bytesRead{};
		if (!ReadProcessMemory(m_ProcessHandle,
		        reinterpret_cast<LPCVOID>(m_Address),
		        out.data(),
		        len,
		        &bytesRead)
		    || bytesRead != len)
		{
			LOG_ERROR("Failed to read {} bytes at 0x{:X}", len, m_Address);
			return {};
		}

		return out;
	}

	bool Pointer::WriteBytes(std::span<const uint8_t> bytes)
	{
		DWORD oldProtect{};
		if (!VirtualProtectEx(m_ProcessHandle, reinterpret_cast<LPVOID>(m_Address), bytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect))
		{
			LOG_ERROR("Failed to change memory protection at 0x{:X}: {}", m_Address, PsUtils::TranslateError(GetLastError()));
			return false;
		}

		SIZE_T bytesWritten{};
		const bool success = WriteProcessMemory(m_ProcessHandle,
		        reinterpret_cast<LPVOID>(m_Address),
		        bytes.data(),
		        bytes.size(),
		        &bytesWritten)
		    && bytesWritten == bytes.size();

		DWORD temp{};
		if (!VirtualProtectEx( m_ProcessHandle, reinterpret_cast<LPVOID>(m_Address), bytes.size(), oldProtect, &temp))
			LOG_ERROR("Failed to restore memory protection at 0x{:X}", m_Address);

		if (!success)
		{
			LOG_ERROR("Failed to write {} bytes at 0x{:X}", bytes.size(), m_Address);
			return false;
		}

		FlushInstructionCache(m_ProcessHandle, reinterpret_cast<LPCVOID>(m_Address), bytes.size());
		return true;
	}
}
