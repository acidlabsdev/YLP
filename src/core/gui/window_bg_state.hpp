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


enum eWindowCompositionAttribute : int
{
	WCA_UNDEFINED,
	WCA_NCRENDERING_ENABLED,
	WCA_NCRENDERING_POLICY,
	WCA_TRANSITIONS_FORCEDISABLED,
	WCA_ALLOW_NCPAINT,
	WCA_CAPTION_BUTTON_BOUNDS,
	WCA_NONCLIENT_RTL_LAYOUT,
	WCA_FORCE_ICONIC_REPRESENTATION,
	WCA_EXTENDED_FRAME_BOUNDS,
	WCA_HAS_ICONIC_BITMAP,
	WCA_THEME_ATTRIBUTES,
	WCA_NCRENDERING_EXILED,
	WCA_NCADORNMENTINFO,
	WCA_EXCLUDED_FROM_LIVEPREVIEW,
	WCA_VIDEO_OVERLAY_ACTIVE,
	WCA_FORCE_ACTIVEWINDOW_APPEARANCE,
	WCA_DISALLOW_PEEK,
	WCA_CLOAK,
	WCA_CLOAKED,
	WCA_ACCENT_POLICY,
	WCA_FREEZE_REPRESENTATION,
	WCA_EVER_UNCLOAKED,
	WCA_VISUAL_OWNER,
	WCA_HOLOGRAPHIC,
	WCA_EXCLUDED_FROM_DDA,
	WCA_PASSIVEUPDATEMODE,
	WCA_LAST,
};


struct WINDOWCOMPOSITIONATTRIBUTEDATA
{
	eWindowCompositionAttribute m_attribute;
	LPVOID m_data_ptr;
	UINT m_data_size;
};


using SetWindowCompositionAttribute_t			 = BOOL(WINAPI*)(HWND, WINDOWCOMPOSITIONATTRIBUTEDATA*);
static inline auto procaddr						 = GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute");
static inline auto SetWindowCompositionAttribute = reinterpret_cast<SetWindowCompositionAttribute_t>(procaddr);

namespace YLP
{
	// TODO: (maybe?) migrate this to the new API
	// https://learn.microsoft.com/en-us/windows/win32/api/dwmapi/nf-dwmapi-dwmsetwindowattribute

	enum eWindowAccentState : int
	{
		ACCENT_DISABLED,
		ACCENT_ENABLE_GRADIENT,
		ACCENT_ENABLE_TRANSPARENTGRADIENT,
		ACCENT_ENABLE_BLURBEHIND,
		ACCENT_ENABLE_ACRYLICBLURBEHIND,
		ACCENT_ENABLE_HOSTBACKDROP,
	};

	struct ACCENT_POLICY
	{
		eWindowAccentState m_state;
		UINT m_flags;
		INT m_color_ref;
		LONG m_anim_id;
	};

	void SetBackgroundAccentState(HWND hwnd, eWindowAccentState state = ACCENT_DISABLED);
}
