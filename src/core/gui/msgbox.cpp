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

#include <common.hpp>
#include "msgbox.hpp"


namespace YLP
{
	int MsgBox::Show(
	    const std::wstring& title,
	    const std::wstring& message,
	    Buttons buttons,
	    Icon icon)
	{
		INITCOMMONCONTROLSEX icce{sizeof(icce), ICC_STANDARD_CLASSES};
		InitCommonControlsEx(&icce);

		TASKDIALOGCONFIG config{};
		config.cbSize = sizeof(config);
		config.hwndParent = g_Hwnd;
		config.hInstance = g_Instance;
		config.dwFlags = TDF_ALLOW_DIALOG_CANCELLATION;
		config.pszWindowTitle = title.c_str();
		config.pszMainInstruction = message.c_str();
		config.pszMainIcon = GetIcon(icon);
		config.dwCommonButtons = GetButtons(buttons);

		int button = -1;
		const HRESULT hr = TaskDialogIndirect(&config, &button, nullptr, nullptr);
		if (!SUCCEEDED(hr))
		{
			LOG_ERROR("[MsgBox]: TaskDialogIndirect failed with HRESULT: 0x{:X}", static_cast<unsigned>(hr));
			button = -1;
		}

		return button;
	}

	UINT MsgBox::GetButtons(Buttons buttons)
	{
		switch (buttons)
		{
		case Buttons::OK: return TDCBF_OK_BUTTON;
		case Buttons::OKCancel: return TDCBF_OK_BUTTON | TDCBF_CANCEL_BUTTON;
		case Buttons::YesNo: return TDCBF_YES_BUTTON | TDCBF_NO_BUTTON;
		case Buttons::YesNoCancel: return TDCBF_YES_BUTTON | TDCBF_NO_BUTTON | TDCBF_CANCEL_BUTTON;
		default: return TDCBF_OK_BUTTON;
		}
	}

	PCWSTR MsgBox::GetIcon(Icon icon)
	{
		switch (icon)
		{
		case Icon::Info: return TD_INFORMATION_ICON;
		case Icon::Warning: return TD_WARNING_ICON;
		case Icon::Error: return TD_ERROR_ICON;
		case Icon::Question: return TD_SHIELD_ICON;
		default: return nullptr;
		}
	}
}
