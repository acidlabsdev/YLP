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


#include "scanner.hpp"


namespace YLP
{
	ProcessScanner::ProcessScanner(const std::string& processName) :
	    m_ProcessHandle(nullptr),
	    m_Pid(0),
	    m_BaseAddress(0),
	    m_ProcessName(processName)
	{
		FindProcess(); // just to immediately update the scanner in case the process is already running
	}

	ProcessScanner::~ProcessScanner()
	{
		if (m_ProcessHandle)
			CloseHandle(m_ProcessHandle);
	}

	bool ProcessScanner::FindProcess()
	{
		auto maybepid = PsUtils::GetProcessId(m_ProcessName);
		if (!maybepid.has_value())
			return false;

		m_Pid			= maybepid.value();
		m_ProcessHandle = OpenProcess(
			SYNCHRONIZE
			| PROCESS_VM_READ
			| PROCESS_VM_WRITE
		    | PROCESS_VM_OPERATION
			| PROCESS_QUERY_INFORMATION
			, FALSE, m_Pid);

		if (!m_ProcessHandle)
			return false;

		RefreshModules();
		return true;
	}

	bool ProcessScanner::IsProcessRunning() const
	{
		if (!m_ProcessHandle)
			return false;

		DWORD exitCode = 0;
		if (!GetExitCodeProcess(m_ProcessHandle, &exitCode))
			return false;

		return exitCode == STILL_ACTIVE;
	}

	void ProcessScanner::RefreshModules()
	{
		m_Modules.clear();

		HMODULE hMods[1024];
		DWORD cbNeeded;

		if (EnumProcessModulesEx(m_ProcessHandle, hMods, sizeof(hMods), &cbNeeded, LIST_MODULES_ALL))
		{
			for (unsigned i = 0; i < (cbNeeded / sizeof(HMODULE)); ++i)
			{
				char modName[MAX_PATH];
				if (GetModuleFileNameExA(m_ProcessHandle, hMods[i], modName, sizeof(modName)))
				{
					std::string baseName = Utils::StringToLower(std::string(strrchr(modName, '\\') + 1));
					m_Modules[baseName] = (Utils::StringToLower(modName));
				}
			}
		}
	}

	bool ProcessScanner::IsModuleLoaded(const std::string& moduleName) const
	{
		std::string lower = Utils::StringToLower(moduleName);

		HMODULE hMods[1024];
		DWORD cbNeeded;

		if (EnumProcessModulesEx(m_ProcessHandle, hMods, sizeof(hMods), &cbNeeded, LIST_MODULES_ALL))
		{
			for (unsigned i = 0; i < (cbNeeded / sizeof(HMODULE)); ++i)
			{
				char modName[MAX_PATH];
				if (GetModuleFileNameExA(m_ProcessHandle, hMods[i], modName, sizeof(modName)))
				{
					std::string baseName = Utils::StringToLower(std::string(strrchr(modName, '\\') + 1));
					if (baseName == lower)
						return true;
				}
			}
		}
		return false;
	}

	uintptr_t ProcessScanner::GetBaseAddress() const
	{
		if (m_BaseAddress)
			return m_BaseAddress;

		HMODULE hMods[1024];
		DWORD cbNeeded;

		if (EnumProcessModules(m_ProcessHandle, hMods, sizeof(hMods), &cbNeeded))
		{
			m_BaseAddress = reinterpret_cast<uintptr_t>(hMods[0]);
			return m_BaseAddress;
		}
		return 0;
	}

	size_t ProcessScanner::GetModuleSize() const
	{
		MODULEINFO modInfo{};
		uintptr_t base = GetBaseAddress();

		if (!base)
			return 0;

		if (GetModuleInformation(m_ProcessHandle, reinterpret_cast<HMODULE>(base), &modInfo, sizeof(modInfo)))
			return modInfo.SizeOfImage;

		return 0;
	}

	bool ProcessScanner::IsAddressValid(uintptr_t address) const
	{
		return address > 0 && address < 0x7FFFFFFFFFFF;
	}

	bool ProcessScanner::IsMemoryReadable(uintptr_t address) const
	{
		MEMORY_BASIC_INFORMATION mbi{};
		if (VirtualQueryEx(m_ProcessHandle, reinterpret_cast<LPCVOID>(address), &mbi, sizeof(mbi)))
			return (mbi.State == MEM_COMMIT && !(mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD)));
		return false;
	}

	std::vector<uint8_t> ProcessScanner::ReadMemory(uintptr_t address, size_t size) const
	{
		if (!m_ProcessHandle)
			throw std::runtime_error("Process handle is invalid!");

		std::vector<uint8_t> buffer(size);
		SIZE_T bytesRead = 0;

		if (!ReadProcessMemory(m_ProcessHandle, reinterpret_cast<LPCVOID>(address), buffer.data(), size, &bytesRead))
			throw std::runtime_error(std::format("ReadProcessMemory failed at 0x{:X}", address));
		buffer.resize(bytesRead);
		return buffer;
	}

	std::vector<std::optional<uint8_t>> ProcessScanner::ParsePattern(const std::string& sig)
	{
		std::vector<std::optional<uint8_t>> bytes{};
		const auto nonNull = sig.size() - 1;
		bytes.reserve(nonNull / 2);

		for (size_t i = 0; i < sig.size();)
		{
			if (sig[i] == ' ')
			{
				++i;
				continue;
			}

			if (sig[i] == '?')
			{
				bytes.push_back({});
				i += (i + 1 < sig.size() && sig[i + 1] == '?') ? 2 : 1;
			}
			else
			{
				auto c1 = Utils::CharToHex(sig[i]);
				auto c2 = (i + 1 < sig.size()) ? Utils::CharToHex(sig[i + 1]) : std::nullopt;
				if (c1 && c2)
					bytes.emplace_back(static_cast<uint8_t>((*c1 << 4) + *c2));

				i += 2;
			}
		}

		return bytes;
	}

	uint64_t ProcessScanner::ScanPattern(std::vector<std::optional<uint8_t>> bytes, std::vector<uint8_t> memchunk)
	{
		size_t numBytes = bytes.size();
		size_t current  = memchunk.size();
		if (numBytes == 0 || current < numBytes)
			return {};

		size_t maxIdx   = numBytes - 1;
		size_t maxShift = numBytes;
		size_t wildcardIdx{static_cast<size_t>(-1)};
		for (int i{static_cast<int>(maxIdx - 1)}; i >= 0; --i)
		{
			if (!bytes[i])
			{
				maxShift    = maxIdx - i;
				wildcardIdx = i;
				break;
			}
		}

		if (wildcardIdx == static_cast<size_t>(-1))
			wildcardIdx = 0;

		std::size_t shiftTable[UINT8_MAX + 1]{};
		for (std::size_t i{}; i <= UINT8_MAX; ++i)
			shiftTable[i] = maxShift;

		for (std::size_t i{wildcardIdx + 1}; i != maxIdx; ++i)
			shiftTable[*bytes[i]] = maxIdx - i;

		const auto scanEnd = current - numBytes;
		auto currentIdx    = 0;
		while (currentIdx <= scanEnd)
		{
			bool match = true;
			for (size_t i = 0; i < numBytes; ++i)
			{
				auto& b = bytes[i];
				if (b && memchunk[currentIdx + i] != *b)
				{
					match = false;
					break;
				}
			}
			if (match)
				return currentIdx;

			currentIdx++;
		}
		return NULL;
	}

	Pointer ProcessScanner::FindPattern(const std::string& pattern, const std::string& name, size_t chunkSize)
	{
		auto bytes = ParsePattern(pattern);
		if (bytes.empty())
			return {};

		auto currentAddr = GetBaseAddress();
		auto moduleSize  = GetModuleSize();
		auto endAddr     = currentAddr + moduleSize;

		LOG_DEBUG("Scanning memory pattern: '{}'", name);
		const size_t overlap = bytes.size() - 1;

		while (currentAddr < endAddr)
		{
			const auto remaining = endAddr - currentAddr;
			const auto readSize  = std::min(chunkSize, remaining);

			std::vector<uint8_t> chunk;

			try
			{
				chunk = ReadMemory(currentAddr, readSize);
			}
			catch (const std::exception& e)
			{
				LOG_ERROR("Failed to read memory!: '{}'", e.what());
				currentAddr += readSize;
				continue;
			}

			auto offset = ScanPattern(bytes, chunk);

			if (offset != NULL)
			{
				const auto address = currentAddr + offset;

				LOG_DEBUG(
				    "Found pattern '{}' at 0x{:X}",
				    name,
				    address);

				return Pointer(m_ProcessHandle, address);
			}

			if (readSize <= overlap)
				break;

			currentAddr += readSize - overlap;
		}

		LOG_ERROR("Failed to find pattern {}", name);
		return {};
	}
}
