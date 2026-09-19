/*
 * SyscallInjector - Syscall Implementation
 * 
 * Dynamically resolves SSN (System Service Numbers) from ntdll.dll at runtime.
 * Uses Halo's Gate technique to recover SSN from hooked functions by checking
 * neighboring syscall stubs.
 * 
 * License: MIT
 */


#include <cstdio>
#include "syscall.h"


extern "C" {
	DWORD wNtAllocateVirtualMemory = 0;
	DWORD wNtWriteVirtualMemory    = 0;
	DWORD wNtReadVirtualMemory     = 0;
	DWORD wNtProtectVirtualMemory  = 0;
	DWORD wNtFreeVirtualMemory     = 0;
	DWORD wNtQueryVirtualMemory    = 0;
	DWORD wNtCreateThreadEx        = 0;
	DWORD wNtWaitForSingleObject   = 0;
	DWORD wNtOpenProcess           = 0;
	DWORD wNtClose                 = 0;
}

static bool g_syscallsInitialized = false;

namespace Syscall
{
	using namespace YLP;

	static bool IsFunctionHooked(BYTE* pFunc)
	{
		if (pFunc[0] == 0x4C && pFunc[1] == 0x8B && pFunc[2] == 0xD1)
			return false;
		return true;
	}

	static DWORD GetSSNFromNeighbor(BYTE* pFunc, int maxDistance = 32)
	{
		constexpr int SYSCALL_STUB_SIZE = 32;

		for (int i = 1; i <= maxDistance; i++)
		{
			BYTE* pNeighbor = pFunc - (i * SYSCALL_STUB_SIZE);
        
			if (pNeighbor[0] == 0x4C && pNeighbor[1] == 0x8B && pNeighbor[2] == 0xD1 && pNeighbor[3] == 0xB8)
			{
				DWORD neighborSSN = *reinterpret_cast<DWORD*>(pNeighbor + 4);
				return neighborSSN + i;
			}
		}

		for (int i = 1; i <= maxDistance; i++)
		{
			BYTE* pNeighbor = pFunc + (i * SYSCALL_STUB_SIZE);

			if (pNeighbor[0] == 0x4C && pNeighbor[1] == 0x8B && pNeighbor[2] == 0xD1 && pNeighbor[3] == 0xB8)
			{
				DWORD neighborSSN = *reinterpret_cast<DWORD*>(pNeighbor + 4);
				return neighborSSN - i;
			}
		}
    
		return 0;
	}

	DWORD GetSSN(HMODULE hNtdll, const char* funcName)
	{
		if (!hNtdll || !funcName)
			return 0;

		FARPROC funcAddr = GetProcAddress(hNtdll, funcName);
		if (!funcAddr)
		{
			LOG_ERROR("Failed to find {} in ntdll.dll", funcName);
			return 0;
		}
    
		BYTE* pFunc = reinterpret_cast<BYTE*>(funcAddr);

		if (IsFunctionHooked(pFunc))
		{
			LOG_DEBUG("{} is hooked (prologue: {:02X} {:02X} {:02X}), using Halo's Gate...",
				funcName,
				static_cast<int>(pFunc[0]),
			    static_cast<int>(pFunc[1]),
			    static_cast<int>(pFunc[2]));
        
			DWORD ssn = GetSSNFromNeighbor(pFunc);
			if (ssn != 0)
			{
				LOG_DEBUG("Recovered SSN for {}: 0{:X} (via Halo's Gate)", funcName, static_cast<int>(ssn));
				return ssn;
			}
        
			LOG_WARN("Could not recover SSN for {}", funcName);
			return 0;
		}

		if (pFunc[3] != 0xB8)
		{
			LOG_WARN("{} has unexpected instruction at offset 3: {:02X}", funcName, static_cast<int>(pFunc[3]));
			return 0;
		}
    
		return *reinterpret_cast<DWORD*>(pFunc + 4);
	}

	bool Initialize()
	{
		if (g_syscallsInitialized)
			return true;
    
		HMODULE hNtdll = GetModuleHandleW(L"ntdll.dll");
		if (!hNtdll)
		{
			LOG_ERROR("Failed to get handle to ntdll.dll");
			return false;
		}
    
		LOG_DEBUG("Resolving SSNs from ntdll.dll...");

		wNtAllocateVirtualMemory = GetSSN(hNtdll, "NtAllocateVirtualMemory");
		wNtWriteVirtualMemory    = GetSSN(hNtdll, "NtWriteVirtualMemory");
		wNtReadVirtualMemory     = GetSSN(hNtdll, "NtReadVirtualMemory");
		wNtProtectVirtualMemory  = GetSSN(hNtdll, "NtProtectVirtualMemory");
		wNtFreeVirtualMemory     = GetSSN(hNtdll, "NtFreeVirtualMemory");
		wNtQueryVirtualMemory    = GetSSN(hNtdll, "NtQueryVirtualMemory");
		wNtCreateThreadEx        = GetSSN(hNtdll, "NtCreateThreadEx");
		wNtWaitForSingleObject   = GetSSN(hNtdll, "NtWaitForSingleObject");
		wNtOpenProcess           = GetSSN(hNtdll, "NtOpenProcess");
		wNtClose                 = GetSSN(hNtdll, "NtClose");

		bool success = (wNtAllocateVirtualMemory != 0) &&
					   (wNtWriteVirtualMemory != 0) &&
					   (wNtCreateThreadEx != 0) &&
					   (wNtWaitForSingleObject != 0);
    
		if (success)
		{
			LOG_DEBUG("SSNs resolved successfully:");
			if (wNtProtectVirtualMemory != 0)
				LOG_DEBUG("  NtProtectVirtualMemory:  0x{:X}", wNtProtectVirtualMemory);
			else
				LOG_DEBUG("  NtProtectVirtualMemory:  BYPASSED (using RWX allocation)");
   
			g_syscallsInitialized = true;
		}
		else
		{
			LOG_ERROR("Failed to resolve critical SSNs");
			LOG_DEBUG("  Allocation: {}, Write: {}, Thread: {}, Wait: {}",
				wNtAllocateVirtualMemory ? "OK" : "FAIL",
				wNtWriteVirtualMemory ? "OK" : "FAIL",
				wNtCreateThreadEx ? "OK" : "FAIL",
				wNtWaitForSingleObject ? "OK" : "FAIL");
		}
    
		return success;
	}

	bool IsInitialized()
	{
		return g_syscallsInitialized;
	}
}
