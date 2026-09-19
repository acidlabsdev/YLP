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


namespace YLP::Memory
{
	class Pointer
	{
	public:
		Pointer()  = default;
		~Pointer() = default;

		Pointer(HANDLE hProcess, uintptr_t address);

		std::vector<uint8_t> ReadBytes(size_t len = 4);

		bool WriteBytes(std::span<const uint8_t> bytes);

		Pointer Add(int32_t offset);

		Pointer Sub(int32_t offset);

		Pointer Rip();

		Pointer Dereference();

		uintptr_t GetAddress() const noexcept;

		explicit operator bool() const
		{
			return m_Address != 0;
		}

		template<typename T>
		T Read(size_t maxLength = 64) const
		{
			if constexpr (std::is_same_v<T, std::string>)
			{
				std::string buffer(maxLength, '\0');
				SIZE_T bytesRead = 0;
				if (ReadProcessMemory(m_ProcessHandle,
				        reinterpret_cast<LPCVOID>(m_Address),
				        buffer.data(),
				        maxLength - 1,
				        &bytesRead))
				{
					buffer.resize(strnlen(buffer.c_str(), bytesRead));
					return buffer;
				}

				LOG_ERROR("Failed to read string at 0x{:X}", m_Address);
				return std::string{};
			}
			else
			{
				T value{};
				SIZE_T bytesRead = 0;

				if (!ReadProcessMemory(m_ProcessHandle,
				        reinterpret_cast<LPCVOID>(m_Address),
				        &value,
				        sizeof(T),
				        &bytesRead))
				{
					LOG_ERROR("Failed to read memory at 0x{:X}", m_Address);
				}

				return value;
			}
		}

		template<typename T>
		bool Write(T arg, size_t maxLength = 64) const
		{
			unsigned long oldProtect;
			if (!VirtualProtectEx(m_ProcessHandle, reinterpret_cast<LPVOID>(m_Address), maxLength, PAGE_EXECUTE_READWRITE, &oldProtect))
			{
				LOG_ERROR("Failed to write memory at 0x{:X}", m_Address);
				return false;
			}

			bool success        = false;
			size_t bytesWritten = 0;
			if constexpr (std::is_same_v<T, std::string>)
			{
				success = WriteProcessMemory(m_ProcessHandle, reinterpret_cast<LPVOID>(m_Address), arg.data(), maxLength - 1, &bytesWritten);
			}
			else
			{
				success = WriteProcessMemory(m_ProcessHandle, reinterpret_cast<LPVOID>(m_Address), &arg, sizeof(arg), &bytesWritten);
			}

			unsigned long temp;
			VirtualProtectEx(m_ProcessHandle, reinterpret_cast<LPVOID>(m_Address), maxLength, oldProtect, &temp);

			if (!success)
				LOG_ERROR("Failed to write memory at 0x{:X}", m_Address);

			return success;
		}

	private:
		uintptr_t m_Address    = 0;
		HANDLE m_ProcessHandle = INVALID_HANDLE_VALUE;
	};
}
