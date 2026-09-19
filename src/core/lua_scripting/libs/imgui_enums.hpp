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

#include "../lua_library.hpp"
#include "../lua_module.hpp"


namespace YLP::LuaJIT
{
	class LuaImGuiEnumsLib : public LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

	public:
		void Register(sol::state& L) override
		{
			/*@ylp.enum ImGuiSeparatorFlags
			* field None
			* field Horizontal
			* field Vertical
			* field SpanAllColumns
			@*/
			L.new_enum("ImGuiSeparatorFlags",
			    "None",
			    ImGuiSeparatorFlags_None,
			    "Horizontal",
			    ImGuiSeparatorFlags_Horizontal,
			    "Vertical",
			    ImGuiSeparatorFlags_Vertical,
			    "SpanAllColumns",
			    ImGuiSeparatorFlags_SpanAllColumns);

			/*@ylp.enum ImGuiMouseCursor
			* field None
			* field Arrow
			* field TextInput
			* field ResizeAll
			* field ResizeNS
			* field ResizeEW
			* field ResizeNESW
			* field ResizeNWSE
			* field Hand
			* field Wait
			* field Progress
			* field NotAllowed
			@*/
			L.new_enum("ImGuiMouseCursor",
			    "None",
			    ImGuiMouseCursor_None,
			    "Arrow",
			    ImGuiMouseCursor_Arrow,
			    "TextInput",
			    ImGuiMouseCursor_TextInput,
			    "ResizeAll",
			    ImGuiMouseCursor_ResizeAll,
			    "ResizeNS",
			    ImGuiMouseCursor_ResizeNS,
			    "ResizeEW",
			    ImGuiMouseCursor_ResizeEW,
			    "ResizeNESW",
			    ImGuiMouseCursor_ResizeNESW,
			    "ResizeNWSE",
			    ImGuiMouseCursor_ResizeNWSE,
			    "Hand",
			    ImGuiMouseCursor_Hand,
			    "Wait",
			    ImGuiMouseCursor_Wait,
			    "Progress",
			    ImGuiMouseCursor_Progress,
			    "NotAllowed",
			    ImGuiMouseCursor_NotAllowed);

			/*@ylp.enum ImGuiDir
			* field None
			* field Left
			* field Right
			* field Up
			* field Down
			@*/
			L.new_enum("ImGuiDir",
			    "None",
			    ImGuiDir_None,
			    "Left",
			    ImGuiDir_Left,
			    "Right",
			    ImGuiDir_Right,
			    "Up",
			    ImGuiDir_Up,
			    "Down",
			    ImGuiDir_Down);

			/*@ylp.enum ImGuiComboFlags
			* field None
			* field PopupAlignLeft
			* field HeightSmall
			* field HeightRegular
			* field HeightHeightLarge
			* field HeightHeightLargest
			* field NoArrowButton
			* field NoPreview
			* field WidthFitPreview
			@*/
			L.new_enum("ImGuiComboFlags",
			    "None",
			    ImGuiComboFlags_None,
			    "PopupAlignLeft",
			    ImGuiComboFlags_PopupAlignLeft,
			    "HeightSmall",
			    ImGuiComboFlags_HeightSmall,
			    "HeightRegular",
			    ImGuiComboFlags_HeightRegular,
			    "HeightHeightLarge",
			    ImGuiComboFlags_HeightLarge,
			    "HeightHeightLargest",
			    ImGuiComboFlags_HeightLargest,
			    "NoArrowButton",
			    ImGuiComboFlags_NoArrowButton,
			    "NoPreview",
			    ImGuiComboFlags_NoPreview,
			    "WidthFitPreview",
			    ImGuiComboFlags_WidthFitPreview);

			/*@ylp.enum ImGuiChildFlags
			* field None
			* field Borders
			* field AlwaysUseWindowPadding
			* field ResizeX
			* field ResizeY
			* field AlwaysAutoResize
			* field FrameStyle
			* field NavFlattened
			@*/
			L.new_enum("ImGuiChildFlags",
			    "None",
			    ImGuiChildFlags_None,
			    "Borders",
			    ImGuiChildFlags_Borders,
			    "AlwaysUseWindowPadding",
			    ImGuiChildFlags_AlwaysUseWindowPadding,
			    "ResizeX",
			    ImGuiChildFlags_ResizeX,
			    "ResizeY",
			    ImGuiChildFlags_ResizeY,
			    "AlwaysAutoResize",
			    ImGuiChildFlags_AlwaysAutoResize,
			    "FrameStyle",
			    ImGuiChildFlags_FrameStyle,
			    "NavFlattened",
			    ImGuiChildFlags_NavFlattened);

			/*@ylp.enum ImGuiWindowFlags
			* field None
			* field NoTitleBar
			* field NoResize
			* field NoMove
			* field NoScrollbar
			* field NoScrollWithMouse
			* field NoCollapse
			* field AlwaysAutoResize
			* field NoBackground
			* field NoSavedSettings
			* field NoMouseInputs
			* field MenuBar
			* field HorizontalScrollbar
			* field NoFocusOnAppearing
			* field NoBringToFrontOnFocus
			* field AlwaysVerticalScrollbar
			* field AlwaysHorizontalScrollbar
			* field NoNavInputs
			* field NoNavFocus
			* field UnsavedDocument
			* field NoNav
			* field NoDecoration
			* field NoInputs
			@*/
			L.new_enum("ImGuiWindowFlags",
			    "None",
			    ImGuiWindowFlags_None,
			    "NoTitleBar",
			    ImGuiWindowFlags_NoTitleBar,
			    "NoResize",
			    ImGuiWindowFlags_NoResize,
			    "NoMove",
			    ImGuiWindowFlags_NoMove,
			    "NoScrollbar",
			    ImGuiWindowFlags_NoScrollbar,
			    "NoScrollWithMouse",
			    ImGuiWindowFlags_NoScrollWithMouse,
			    "NoCollapse",
			    ImGuiWindowFlags_NoCollapse,
			    "AlwaysAutoResize",
			    ImGuiWindowFlags_AlwaysAutoResize,
			    "NoBackground",
			    ImGuiWindowFlags_NoBackground,
			    "NoSavedSettings",
			    ImGuiWindowFlags_NoSavedSettings,
			    "NoMouseInputs",
			    ImGuiWindowFlags_NoMouseInputs,
			    "MenuBar",
			    ImGuiWindowFlags_MenuBar,
			    "HorizontalScrollbar",
			    ImGuiWindowFlags_HorizontalScrollbar,
			    "NoFocusOnAppearing",
			    ImGuiWindowFlags_NoFocusOnAppearing,
			    "NoBringToFrontOnFocus",
			    ImGuiWindowFlags_NoBringToFrontOnFocus,
			    "AlwaysHorizontalScrollbar",
			    ImGuiWindowFlags_AlwaysHorizontalScrollbar,
			    "NoNavInputs",
			    ImGuiWindowFlags_NoNavInputs,
			    "NoNavFocus",
			    ImGuiWindowFlags_NoNavFocus,
			    "UnsavedDocument",
			    ImGuiWindowFlags_UnsavedDocument,
			    "NoNav",
			    ImGuiWindowFlags_NoNav,
			    "NoInputs",
			    ImGuiWindowFlags_NoInputs);

			/*@ylp.enum ImGuiStyleVar
			* field DisabledAlpha
			* field WindowPadding
			* field WindowRounding
			* field WindowBorderSize
			* field WindowMinSize
			* field WindowTitleAlign
			* field ChildRounding
			* field ChildBorderSize
			* field PopupRounding
			* field PopupBorderSize
			* field FramePadding
			* field FrameRounding
			* field FrameBorderSize
			* field ItemSpacing
			* field ItemInnerSpacing
			* field IndentSpacing
			* field CellPadding
			* field ScrollbarSize
			* field ScrollbarRounding
			* field ScrollbarPadding
			* field GrabMinSize
			* field GrabRounding
			* field ImageBorderSize
			* field TabRounding
			* field TabBorderSize
			* field TabMinWidthBase
			* field TabMinWidthShrink
			* field TabBarBorderSize
			* field TabBarOverlineSize
			* field TableAngledHeadersAngle
			* field TableAngledHeadersTextAlign
			* field TreeLinesSize
			* field TreeLinesRounding
			* field ButtonTextAlign
			* field SelectableTextAlign
			* field SeparatorTextBorderSize
			* field SeparatorTextAlign
			* field SeparatorTextPadding
			@*/
			L.new_enum("ImGuiStyleVar",
			    "DisabledAlpha",
			    ImGuiStyleVar_DisabledAlpha,
			    "WindowPadding",
			    ImGuiStyleVar_WindowPadding,
			    "WindowRounding",
			    ImGuiStyleVar_WindowRounding,
			    "WindowBorderSize",
			    ImGuiStyleVar_WindowBorderSize,
			    "WindowMinSize",
			    ImGuiStyleVar_WindowMinSize,
			    "WindowTitleAlign",
			    ImGuiStyleVar_WindowTitleAlign,
			    "ChildRounding",
			    ImGuiStyleVar_ChildRounding,
			    "ChildBorderSize",
			    ImGuiStyleVar_ChildBorderSize,
			    "PopupRounding",
			    ImGuiStyleVar_PopupRounding,
			    "PopupBorderSize",
			    ImGuiStyleVar_PopupBorderSize,
			    "FramePadding",
			    ImGuiStyleVar_FramePadding,
			    "FrameRounding",
			    ImGuiStyleVar_FrameRounding,
			    "FrameBorderSize",
			    ImGuiStyleVar_FrameBorderSize,
			    "ItemSpacing",
			    ImGuiStyleVar_ItemSpacing,
			    "ItemInnerSpacing",
			    ImGuiStyleVar_ItemInnerSpacing,
			    "IndentSpacing",
			    ImGuiStyleVar_IndentSpacing,
			    "CellPadding",
			    ImGuiStyleVar_CellPadding,
			    "ScrollbarSize",
			    ImGuiStyleVar_ScrollbarSize,
			    "ScrollbarRounding",
			    ImGuiStyleVar_ScrollbarRounding,
			    "ScrollbarPadding",
			    ImGuiStyleVar_ScrollbarPadding,
			    "GrabMinSize",
			    ImGuiStyleVar_GrabMinSize,
			    "GrabRounding",
			    ImGuiStyleVar_GrabRounding,
			    "ImageBorderSize",
			    ImGuiStyleVar_ImageBorderSize,
			    "TabRounding",
			    ImGuiStyleVar_TabRounding,
			    "TabBorderSize",
			    ImGuiStyleVar_TabBorderSize,
			    "TabMinWidthBase",
			    ImGuiStyleVar_TabMinWidthBase,
			    "TabMinWidthShrink",
			    ImGuiStyleVar_TabMinWidthShrink,
			    "TabBarBorderSize",
			    ImGuiStyleVar_TabBarBorderSize,
			    "TabBarOverlineSize",
			    ImGuiStyleVar_TabBarOverlineSize,
			    "TableAngledHeadersAngle",
			    ImGuiStyleVar_TableAngledHeadersAngle,
			    "TableAngledHeadersTextAlign",
			    ImGuiStyleVar_TableAngledHeadersTextAlign,
			    "TreeLinesSize",
			    ImGuiStyleVar_TreeLinesSize,
			    "TreeLinesRounding",
			    ImGuiStyleVar_TreeLinesRounding,
			    "ButtonTextAlign",
			    ImGuiStyleVar_ButtonTextAlign,
			    "SelectableTextAlign",
			    ImGuiStyleVar_SelectableTextAlign,
			    "SeparatorTextBorderSize",
			    ImGuiStyleVar_SeparatorTextBorderSize,
			    "SeparatorTextAlign",
			    ImGuiStyleVar_SeparatorTextAlign,
			    "SeparatorTextPadding",
			    ImGuiStyleVar_SeparatorTextPadding);

			/*@ylp.enum ImGuiCol
			* field TextDisabled
			* field WindowBg
			* field ChildBg
			* field PopupBg
			* field Border
			* field BorderShadow
			* field FrameBg
			* field FrameBgHovered
			* field FrameBgActive
			* field TitleBg
			* field TitleBgActive
			* field TitleBgCollapsed
			* field MenuBarBg
			* field ScrollbarBg
			* field ScrollbarGrab
			* field ScrollbarGrabHovered
			* field ScrollbarGrabActive
			* field CheckMark
			* field SliderGrab
			* field SliderGrabActive
			* field Button
			* field ButtonHovered
			* field ButtonActive
			* field Header
			* field HeaderHovered
			* field HeaderActive
			* field Separator
			* field SeparatorHovered
			* field SeparatorActive
			* field ResizeGrip
			* field ResizeGripHovered
			* field ResizeGripActive
			* field InputTextCursor
			* field TabHovered
			* field Tab
			* field TabSelected
			* field TabSelectedOverline
			* field TabDimmed
			* field TabDimmedSelected
			* field TabDimmedSelectedOverline
			* field PlotLines
			* field PlotLinesHovered
			* field PlotHistogram
			* field PlotHistogramHovered
			* field TableHeaderBg
			* field TableBorderStrong
			* field TableBorderLight
			* field TableRowBg
			* field TableRowBgAlt
			* field TextLink
			* field TextSelectedBg
			* field TreeLines
			* field DragDropTarget
			* field UnsavedMarker
			* field NavCursor
			* field NavWindowingHighlight
			* field NavWindowingDimBg
			* field ModalWindowDimBg
			@*/
			L.new_enum("ImGuiCol",
			    "TextDisabled",
			    ImGuiCol_TextDisabled,
			    "WindowBg",
			    ImGuiCol_WindowBg,
			    "ChildBg",
			    ImGuiCol_ChildBg,
			    "PopupBg",
			    ImGuiCol_PopupBg,
			    "Border",
			    ImGuiCol_Border,
			    "BorderShadow",
			    ImGuiCol_BorderShadow,
			    "FrameBg",
			    ImGuiCol_FrameBg,
			    "FrameBgHovered",
			    ImGuiCol_FrameBgHovered,
			    "FrameBgActive",
			    ImGuiCol_FrameBgActive,
			    "TitleBg",
			    ImGuiCol_TitleBg,
			    "TitleBgActive",
			    ImGuiCol_TitleBgActive,
			    "TitleBgCollapsed",
			    ImGuiCol_TitleBgCollapsed,
			    "MenuBarBg",
			    ImGuiCol_MenuBarBg,
			    "ScrollbarBg",
			    ImGuiCol_ScrollbarBg,
			    "ScrollbarGrab",
			    ImGuiCol_ScrollbarGrab,
			    "ScrollbarGrabHovered",
			    ImGuiCol_ScrollbarGrabHovered,
			    "ScrollbarGrabActive",
			    ImGuiCol_ScrollbarGrabActive,
			    "CheckMark",
			    ImGuiCol_CheckMark,
			    "SliderGrab",
			    ImGuiCol_SliderGrab,
			    "SliderGrabActive",
			    ImGuiCol_SliderGrabActive,
			    "Button",
			    ImGuiCol_Button,
			    "ButtonHovered",
			    ImGuiCol_ButtonHovered,
			    "ButtonActive",
			    ImGuiCol_ButtonActive,
			    "Header",
			    ImGuiCol_Header,
			    "HeaderHovered",
			    ImGuiCol_HeaderHovered,
			    "HeaderActive",
			    ImGuiCol_HeaderActive,
			    "Separator",
			    ImGuiCol_Separator,
			    "SeparatorHovered",
			    ImGuiCol_SeparatorHovered,
			    "SeparatorActive",
			    ImGuiCol_SeparatorActive,
			    "ResizeGrip",
			    ImGuiCol_ResizeGrip,
			    "ResizeGripHovered",
			    ImGuiCol_ResizeGripHovered,
			    "ResizeGripActive",
			    ImGuiCol_ResizeGripActive,
			    "InputTextCursor",
			    ImGuiCol_InputTextCursor,
			    "TabHovered",
			    ImGuiCol_TabHovered,
			    "Tab",
			    ImGuiCol_Tab,
			    "TabSelected",
			    ImGuiCol_TabSelected,
			    "TabSelectedOverline",
			    ImGuiCol_TabSelectedOverline,
			    "TabDimmed",
			    ImGuiCol_TabDimmed,
			    "TabDimmedSelected",
			    ImGuiCol_TabDimmedSelected,
			    "TabDimmedSelectedOverline",
			    ImGuiCol_TabDimmedSelectedOverline,
			    "PlotLines",
			    ImGuiCol_PlotLines,
			    "PlotLinesHovered",
			    ImGuiCol_PlotLinesHovered,
			    "PlotHistogram",
			    ImGuiCol_PlotHistogram,
			    "PlotHistogramHovered",
			    ImGuiCol_PlotHistogramHovered,
			    "TableHeaderBg",
			    ImGuiCol_TableHeaderBg,
			    "TableBorderStrong",
			    ImGuiCol_TableBorderStrong,
			    "TableBorderLight",
			    ImGuiCol_TableBorderLight,
			    "TableRowBg",
			    ImGuiCol_TableRowBg,
			    "TableRowBgAlt",
			    ImGuiCol_TableRowBgAlt,
			    "TextLink",
			    ImGuiCol_TextLink,
			    "TextSelectedBg",
			    ImGuiCol_TextSelectedBg,
			    "TreeLines",
			    ImGuiCol_TreeLines,
			    "DragDropTarget",
			    ImGuiCol_DragDropTarget,
			    "UnsavedMarker",
			    ImGuiCol_UnsavedMarker,
			    "NavCursor",
			    ImGuiCol_NavCursor,
			    "NavWindowingHighlight",
			    ImGuiCol_NavWindowingHighlight,
			    "NavWindowingDimBg",
			    ImGuiCol_NavWindowingDimBg,
			    "ModalWindowDimBg",
			    ImGuiCol_ModalWindowDimBg);
		}
	};

	LuaImGuiEnumsLib _LuaImGuiEnumsLib;
}
