#pragma once
/*
 * SyscallInjector - Direct Syscall Implementation
 * 
 * Bypasses EDR/AV hooks by executing syscalls directly, avoiding
 * hooked kernel32.dll and ntdll.dll functions.
 * 
 * Features:
 * - Dynamic SSN (System Service Number) resolution at runtime
 * - Halo's Gate technique to recover SSN from hooked functions
 * - Works across Windows versions (no hardcoded SSNs)
 * 
 * Inspired by: https://github.com/0xflux/GoSneak
 * Reference: https://redops.at/en/blog/direct-syscalls-vs-indirect-syscalls
 * 
 * License: MIT
 */

#pragma warning(push)
#pragma warning(disable: 4201)  // nonstandard extension: nameless struct/union

#include <windows.h>
#include <winternl.h>
#include <cstdint>

// ============================================================================
// SSN (System Service Number) STORAGE
// ============================================================================
// These are populated at runtime by resolving from ntdll.dll
// The assembly stubs read these values when making syscalls

extern "C" {
    extern DWORD wNtAllocateVirtualMemory;
    extern DWORD wNtWriteVirtualMemory;
    extern DWORD wNtReadVirtualMemory;
    extern DWORD wNtProtectVirtualMemory;
    extern DWORD wNtFreeVirtualMemory;
    extern DWORD wNtQueryVirtualMemory;
    extern DWORD wNtCreateThreadEx;
    extern DWORD wNtWaitForSingleObject;
    extern DWORD wNtOpenProcess;
    extern DWORD wNtClose;
}

typedef struct _OBJECT_ATTRIBUTES_SYSCALL
{
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;
    PVOID SecurityQualityOfService;
} OBJECT_ATTRIBUTES_SYSCALL, *POBJECT_ATTRIBUTES_SYSCALL;

typedef struct _CLIENT_ID_SYSCALL
{
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID_SYSCALL, *PCLIENT_ID_SYSCALL;

typedef struct _PS_ATTRIBUTE
{
    ULONGLONG Attribute;
    SIZE_T Size;
    union {
        ULONG_PTR Value;
        PVOID ValuePtr;
    };
    PSIZE_T ReturnLength;
} PS_ATTRIBUTE, *PPS_ATTRIBUTE;

typedef struct _PS_ATTRIBUTE_LIST
{
    SIZE_T TotalLength;
    PS_ATTRIBUTE Attributes[2];
} PS_ATTRIBUTE_LIST, *PPS_ATTRIBUTE_LIST;

// ============================================================================
// SYSCALL FUNCTION PROTOTYPES
// ============================================================================
// These are implemented in syscalls.asm - they execute 'syscall' directly

extern "C"
{
    // Memory operations
	NTSTATUS NTAPI NtAllocateVirtualMemory(
        HANDLE ProcessHandle,
        PVOID* BaseAddress,
        ULONG_PTR ZeroBits,
        PSIZE_T RegionSize,
        ULONG AllocationType,
        ULONG Protect
    );

    NTSTATUS NTAPI NtWriteVirtualMemory(
        HANDLE ProcessHandle,
        PVOID BaseAddress,
        PVOID Buffer,
        SIZE_T BufferSize,
        PSIZE_T NumberOfBytesWritten
    );

    NTSTATUS NTAPI NtReadVirtualMemory(
        HANDLE ProcessHandle,
        PVOID BaseAddress,
        PVOID Buffer,
        SIZE_T BufferSize,
        PSIZE_T NumberOfBytesRead
    );

    NTSTATUS NTAPI NtProtectVirtualMemory(
        HANDLE ProcessHandle,
        PVOID* BaseAddress,
        PSIZE_T RegionSize,
        ULONG NewProtect,
        PULONG OldProtect
    );

    NTSTATUS NTAPI NtFreeVirtualMemory(
        HANDLE ProcessHandle,
        PVOID* BaseAddress,
        PSIZE_T RegionSize,
        ULONG FreeType
    );

    NTSTATUS NTAPI NtQueryVirtualMemory(
        HANDLE ProcessHandle,
        PVOID BaseAddress,
        ULONG MemoryInformationClass,
        PVOID MemoryInformation,
        SIZE_T MemoryInformationLength,
        PSIZE_T ReturnLength
    );

    // Thread operations
	NTSTATUS NTAPI NtCreateThreadEx(
        PHANDLE ThreadHandle,
        ACCESS_MASK DesiredAccess,
        POBJECT_ATTRIBUTES_SYSCALL ObjectAttributes,
        HANDLE ProcessHandle,
        PVOID StartRoutine,
        PVOID Argument,
        ULONG CreateFlags,
        SIZE_T ZeroBits,
        SIZE_T StackSize,
        SIZE_T MaximumStackSize,
        PPS_ATTRIBUTE_LIST AttributeList
    );

    NTSTATUS NTAPI NtWaitForSingleObject(
        HANDLE Handle,
        BOOLEAN Alertable,
        PLARGE_INTEGER Timeout
    );

    // Handle operations
	NTSTATUS NTAPI NtOpenProcess(
        PHANDLE ProcessHandle,
        ACCESS_MASK DesiredAccess,
        POBJECT_ATTRIBUTES_SYSCALL ObjectAttributes,
        PCLIENT_ID_SYSCALL ClientId
    );

    NTSTATUS NTAPI NtClose(HANDLE Handle);
}

namespace Syscall {
    
    /**
     * @brief Initialize all syscall SSNs by reading from ntdll.dll
     * 
     * This MUST be called before any syscall functions are used.
     * Resolves SSN values from ntdll.dll memory at runtime, making it
     * compatible across Windows versions.
     * 
     * Uses Halo's Gate technique to recover SSNs from hooked functions
     * by checking neighboring syscall stubs.
     * 
     * @return true if all critical SSNs were resolved successfully
     */
    bool Initialize();
    
    /**
     * @brief Check if syscalls have been initialized
     * @return true if Initialize() completed successfully
     */
    bool IsInitialized();
    
    /**
     * @brief Get SSN for a specific NT function from ntdll.dll
     * 
     * The SSN is found at offset +4 from the function address:
     *   mov r10, rcx    ; 3 bytes  (4C 8B D1)
     *   mov eax, SSN    ; 5 bytes  (B8 xx xx xx xx)
     *   syscall         ; 2 bytes
     *   ret             ; 1 byte
     * 
     * If the function is hooked (prologue != 4C 8B D1), uses Halo's Gate
     * to find SSN from neighboring clean syscall stubs.
     * 
     * @param hNtdll Handle to ntdll.dll
     * @param funcName Name of the NT function (e.g., "NtAllocateVirtualMemory")
     * @return DWORD The SSN value, or 0 on failure
     */
    DWORD GetSSN(HMODULE hNtdll, const char* funcName);
}

#pragma warning(pop)
