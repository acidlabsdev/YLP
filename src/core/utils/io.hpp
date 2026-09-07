// YLP Project - GPL-3.0
// See LICENSE file or <https://www.gnu.org/licenses/> for details.


#pragma once

#include <combaseapi.h>
#include <shellapi.h>
#include <shobjidl.h>


namespace fs = std::filesystem;

namespace YLP::IO
{
	fs::path Path(const fs::path& _path);

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
	void OpenW(const std::wstring& path);
	void Rename(const fs::path& src, const fs::path& dest);

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
}
