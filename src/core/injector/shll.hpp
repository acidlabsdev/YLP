#pragma once

#define INVALID_DATA_POINTER ((HINSTANCE)0x404040)
#define SEH_SUPPORT_FAILED ((HINSTANCE)0x505050)
#define IS_RELOC_FLAG_32(flag) ((flag >> 0x0C) == IMAGE_REL_BASED_HIGHLOW)
#define IS_RELOC_FLAG_64(flag) ((flag >> 0x0C) == IMAGE_REL_BASED_DIR64)

#ifdef _WIN64
	#define RELOC_FLAG IS_RELOC_FLAG_64
#else
	#define RELOC_FLAG IS_RELOC_FLAG_32
#endif


struct MMappingData
{
	pLoadLibraryA fnLoadLib;
	pGetProcAddress fnGetProc;
	pAddFuncTable fnAddFuncTable;

	bool enableSEH;

	BYTE* pBase;
	HINSTANCE hModule;
	DWORD dwReason;
	LPVOID lpReserved;
};


#pragma runtime_checks("", off)
#pragma optimize("", off)

static void __stdcall _shell(MMappingData* pData)
{
	if (!pData)
		return;

	BYTE* pBase = pData->pBase;
	auto* pOpt  = &reinterpret_cast<IMAGE_NT_HEADERS*>(pBase + reinterpret_cast<IMAGE_DOS_HEADER*>(pBase)->e_lfanew)->OptionalHeader;

	auto _LoadLibraryA   = pData->fnLoadLib;
	auto _GetProcAddress = pData->fnGetProc;
	auto _DllMain        = reinterpret_cast<BOOL(WINAPI*)(void*, DWORD, void*)>(pBase + pOpt->AddressOfEntryPoint);
	BYTE* LocationDelta  = pBase - pOpt->ImageBase;

	if (LocationDelta && pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size)
	{
		auto* pRelocData      = reinterpret_cast<IMAGE_BASE_RELOCATION*>(pBase + pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
		const auto* pRelocEnd = reinterpret_cast<BYTE*>(pRelocData) + pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size;

		while (reinterpret_cast<BYTE*>(pRelocData) < pRelocEnd && pRelocData->SizeOfBlock)
		{
			const UINT Count    = (pRelocData->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
			WORD* pRelativeInfo = reinterpret_cast<WORD*>(pRelocData + 1);

			for (UINT i = 0; i < Count; ++i)
			{
				if (RELOC_FLAG(pRelativeInfo[i]))
				{
					UINT_PTR* pPatch  = reinterpret_cast<UINT_PTR*>(pBase + pRelocData->VirtualAddress + (pRelativeInfo[i] & 0xFFF));
					*pPatch          += reinterpret_cast<UINT_PTR>(LocationDelta);
				}
			}
			pRelocData = reinterpret_cast<IMAGE_BASE_RELOCATION*>(reinterpret_cast<BYTE*>(pRelocData) + pRelocData->SizeOfBlock);
		}
	}

	if (pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size)
	{
		auto* pImportDesc = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(pBase + pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
		while (pImportDesc->Name)
		{
			HMODULE hMod = _LoadLibraryA(reinterpret_cast<char*>(pBase + pImportDesc->Name));
			if (!hMod)
			{
				pData->hModule = INVALID_DATA_POINTER;
				return;
			}

			ULONG_PTR* pThunk = reinterpret_cast<ULONG_PTR*>(pBase + pImportDesc->OriginalFirstThunk);
			ULONG_PTR* pFunc  = reinterpret_cast<ULONG_PTR*>(pBase + pImportDesc->FirstThunk);

			if (!pImportDesc->OriginalFirstThunk)
				pThunk = pFunc;

			for (; *pThunk; ++pThunk, ++pFunc)
			{
				if (IMAGE_SNAP_BY_ORDINAL(*pThunk))
					*pFunc = reinterpret_cast<ULONG_PTR>(_GetProcAddress(hMod, reinterpret_cast<char*>(*pThunk & 0xFFFF)));
				else
					*pFunc = reinterpret_cast<ULONG_PTR>(_GetProcAddress(hMod, reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(pBase + *pThunk)->Name));
			}
			++pImportDesc;
		}
	}

	if (pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].Size)
	{
		auto* pTLS                     = reinterpret_cast<IMAGE_TLS_DIRECTORY*>(pBase + pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);
		PIMAGE_TLS_CALLBACK* pCallback = reinterpret_cast<PIMAGE_TLS_CALLBACK*>(pTLS->AddressOfCallBacks);

		for (; pCallback && *pCallback; ++pCallback)
			(*pCallback)(pBase, DLL_PROCESS_ATTACH, nullptr);
	}

	bool ExceptionSupportFailed = false;
#ifdef _WIN64
	if (pData->enableSEH)
	{
		const auto& exceptionEntry = pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION];
		if (exceptionEntry.Size && pData->fnAddFuncTable)
		{
			auto pRtFuncEntry = reinterpret_cast<IMAGE_RUNTIME_FUNCTION_ENTRY*>(pBase + exceptionEntry.VirtualAddress);
			if (!pData->fnAddFuncTable(pRtFuncEntry, exceptionEntry.Size / sizeof(IMAGE_RUNTIME_FUNCTION_ENTRY), reinterpret_cast<DWORD64>(pBase)))
				ExceptionSupportFailed = true;
		}
	}
#endif

	_DllMain(pBase, pData->dwReason, pData->lpReserved);
	pData->hModule = ExceptionSupportFailed ? SEH_SUPPORT_FAILED : reinterpret_cast<HINSTANCE>(pBase);
}

#pragma runtime_checks("", restore)
#pragma optimize("", on)
