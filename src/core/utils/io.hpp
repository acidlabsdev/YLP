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

#include <combaseapi.h>
#include <shellapi.h>
#include <shobjidl.h>


namespace fs = std::filesystem;

namespace YLP::IO
{
	struct DllInfo
	{
		bool ok         = false;
		bool is64bit    = false;
		bool hasExports = false;

		fs::path filepath{};

		std::string error{};
		std::string checksum{};
		std::string name{};
		std::string lastKnownProcess{};
	};

	void HandleFsErr(const std::error_code& ec);

	bool Exists(const fs::path& _path);
	bool IsDir(const fs::path& _path);
	bool IsFile(const fs::path& _path);
	bool IsEmpty(const fs::path& _path);
	bool CreateFolder(const fs::path& _path);
	bool CreateFolders(const fs::path& _path);
	bool Remove(const fs::path& _path);
	bool RemoveAll(const fs::path& target);
	bool HasLuaFiles(const fs::path& root);
	bool FilterLuaFiles(const fs::path& root);

	void Open(const std::string& path);
	void Open(const std::wstring& path);
	void HighlightFile(const std::string& filePath);
	void HighlightFile(const std::wstring& filePath);
	bool Rename(const fs::path& src, const fs::path& dest);

	DllInfo AddDLL();
	DllInfo ValidateDLL(const std::filesystem::path& file);

	std::wstring ReadRegistryKey(HKEY rootPath, const wchar_t* subkeyPath, const wchar_t* subkeyValue);

	fs::path _OpenFileDialog(
	    const std::vector<COMDLG_FILTERSPEC>& filters,
	    const wchar_t* title,
	    FILEOPENDIALOGOPTIONS flags,
	    const std::filesystem::path& defaultFolder = {},
	    const wchar_t* defaultName = nullptr,
	    const wchar_t* defaultExtension = nullptr);

	fs::path OpenFileDialog(
	    const std::vector<COMDLG_FILTERSPEC>& filters = {{L"All Files", L"*.*"}},
	    const wchar_t* title = L"Open File",
	    bool multiselect = false,
	    const std::filesystem::path& defaultFolder = {});

	fs::path OpenFolderDialog(
	    const wchar_t* title = L"Select Folder",
		bool multiselect = false,
	    const fs::path& defaultFolder = {});

	fs::path SaveFileDialog(
	    const std::vector<COMDLG_FILTERSPEC>& filters = {{L"All Files", L"*.*"}},
		const wchar_t* title = L"Save As",
		const wchar_t* defaultName = L"",
		const wchar_t* defaultExtension = L"",
	    const fs::path& defaultFolder = {});

	std::optional<std::filesystem::path> MakeAbsPath(const fs::path& root, const fs::path& other);
}
