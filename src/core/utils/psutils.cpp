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


#include "psutils.hpp"


namespace YLP::PsUtils
{

	void ProcessList::StartUpdatingImpl()
	{
		if (m_Running)
			return;

		m_Running = true;
		ThreadManager::RunDetached([this]() {
			while (m_Running)
			{
				UpdateProcesses();
				std::unique_lock lock(m_CVMutex);
				m_ConVar.wait_for(lock, 2s, [this] {
					return !m_Running;
				});
			}
		});
	}

	void ProcessList::StopUpdatingImpl()
	{
		if (!m_Running)
			return;

		m_Running = false;
		m_ConVar.notify_all();
	}

	const std::vector<ProcessEntry> ProcessList::GetSnapshotImpl()
	{
		std::scoped_lock lock(m_Mutex);
		return m_Processes;
	}

	void ProcessList::UpdateProcessesImpl()
	{
		if (std::chrono::steady_clock::now() - m_LastUpdated < 1s)
			return;

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (snapshot == INVALID_HANDLE_VALUE)
			return;

		PROCESSENTRY32W entry{.dwSize = sizeof(entry)};
		std::vector<ProcessEntry> tempList;

		if (Process32FirstW(snapshot, &entry))
		{
			do
			{
				char name[260];
				WideCharToMultiByte(CP_UTF8, 0, entry.szExeFile, -1, name, sizeof(name), nullptr, nullptr);
				tempList.push_back({.m_Name = name, .m_Pid = entry.th32ProcessID});
			} while (Process32NextW(snapshot, &entry));
		}

		CloseHandle(snapshot);
		std::scoped_lock lock(m_Mutex);
		m_Processes.swap(tempList);
		m_LastUpdated = std::chrono::steady_clock::now();
	}

	std::optional<DWORD> WaitForProcessExit(HANDLE hProc, DWORD timeoutMs)
	{
		if (!hProc || hProc == INVALID_HANDLE_VALUE)
		{
			LOG_ERROR("[PsUtils]: WaitForProcessExit failed with invalid handle: 0x{:X}", (uintptr_t)hProc);
			return std::nullopt;
		}

		DWORD wait = WaitForSingleObject(hProc, timeoutMs);
		if (wait == WAIT_OBJECT_0)
		{
			DWORD exitCode = STILL_ACTIVE;
			if (!GetExitCodeProcess(hProc, &exitCode))
			{
				DWORD last = GetLastError();
				LOG_ERROR("[PsUtils]: GetExitCodeProcess failed with error 0x{:X} ({})", last, TranslateError(last));
				return std::nullopt;
			}
			return exitCode;
		}
		else if (wait == WAIT_TIMEOUT)
		{
			return std::nullopt;
		}
		else
		{
			DWORD last = GetLastError();
			LOG_ERROR("[PsUtils]: WaitForSingleObject failed with error 0x{:X} ({})", last, TranslateError(last));
			return std::nullopt;
		}
	}
	
	std::optional<DWORD> GetProcessId(std::string_view name)
	{
		ProcessList::UpdateProcesses();
		for (auto& entry : ProcessList::GetSnapshot())
		{
			if (entry.m_Name == name)
				return entry.m_Pid;
		}

		return std::nullopt;
	}

	const bool IsSameArch(HANDLE hTargetProcess)
	{
		BOOL targetIsWow = FALSE;
		if (!IsWow64Process(hTargetProcess, &targetIsWow))
			return false;

		BOOL selfIsWow = FALSE;
		if (!IsWow64Process(GetCurrentProcess(), &selfIsWow))
			return false;

		return (targetIsWow == selfIsWow);
	}

	std::string TranslateError(DWORD exitCode)
	{
		LPWSTR msgBuffer = nullptr;
		DWORD result = FormatMessageW(
		    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		    nullptr,
		    exitCode,
		    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		    reinterpret_cast<LPWSTR>(&msgBuffer),
		    0,
		    nullptr);

		std::string errorMsg;
		if (result != 0 && msgBuffer != nullptr)
		{
			errorMsg = Utils::WideToUTF8(msgBuffer);
			LocalFree(msgBuffer);

			if (auto lastPos = errorMsg.find_last_not_of(" \r\n"); lastPos != std::string::npos)
				errorMsg.erase(lastPos + 1);
		}
		else
		{
			errorMsg = "UNKNOWN_ERROR";
		}

		return errorMsg;
	}

	const bool IsServiceRunning(const std::wstring& serviceName)
	{
		SC_HANDLE scm = OpenSCManagerW(nullptr, nullptr, SC_MANAGER_CONNECT);
		if (!scm)
		{
			DWORD err = GetLastError();
			LOG_DEBUG("[PsUtils]: OpenSCManager failed with error {}: {}", err, TranslateError(err));
			return false;
		}

		SC_HANDLE svc = OpenServiceW(scm, serviceName.c_str(), SERVICE_QUERY_STATUS);
		if (!svc)
		{
			CloseServiceHandle(scm);
			return false;
		}

		SERVICE_STATUS_PROCESS ssp{};
		DWORD bytesNeeded = 0;
		BOOL ok = QueryServiceStatusEx(svc, SC_STATUS_PROCESS_INFO, reinterpret_cast<LPBYTE>(&ssp), sizeof(ssp), &bytesNeeded);
		if (!ok)
		{
			CloseServiceHandle(svc);
			CloseServiceHandle(scm);
			return false;
		}

		bool running = (ssp.dwCurrentState == SERVICE_RUNNING);
		CloseServiceHandle(svc);
		CloseServiceHandle(scm);
		return running;
	}

	BOOL CALLBACK EnumProcessWindows(HWND hwnd, LPARAM lParam)
	{
		EnumWindowData& ewd = *reinterpret_cast<EnumWindowData*>(lParam);
		DWORD dwPid = 0;

		GetWindowThreadProcessId(hwnd, &dwPid);

		if (dwPid == ewd.m_Pid)
		{
			ewd.m_HWND = hwnd;
			return FALSE;
		}
		return TRUE;
	}

	HWND GetHwndFromPid(DWORD pid)
	{
		EnumWindowData ewd{0};
		ewd.m_Pid = pid;
		EnumWindows(EnumProcessWindows, reinterpret_cast<LPARAM>(&ewd));
		return ewd.m_HWND;
	}
}
