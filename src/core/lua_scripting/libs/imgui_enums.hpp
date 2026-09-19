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
			* field None<integer>
			* field Horizontal<integer>
			* field Vertical<integer>
			* field SpanAllColumns<integer>
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
			* field None<integer>
			* field Arrow<integer>
			* field TextInput<integer>
			* field ResizeAll<integer>
			* field ResizeNS<integer>
			* field ResizeEW<integer>
			* field ResizeNESW<integer>
			* field ResizeNWSE<integer>
			* field Hand<integer>
			* field Wait<integer>
			* field Progress<integer>
			* field NotAllowed<integer>
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
			* field None<integer>
			* field Left<integer>
			* field Right<integer>
			* field Up<integer>
			* field Down<integer>
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
			* field None<integer>
			* field PopupAlignLeft<integer>
			* field HeightSmall<integer>
			* field HeightRegular<integer>
			* field HeightHeightLarge<integer>
			* field HeightHeightLargest<integer>
			* field NoArrowButton<integer>
			* field NoPreview<integer>
			* field WidthFitPreview<integer>
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
			* field None<integer>
			* field Borders<integer>
			* field AlwaysUseWindowPadding<integer>
			* field ResizeX<integer>
			* field ResizeY<integer>
			* field AlwaysAutoResize<integer>
			* field FrameStyle<integer>
			* field NavFlattened<integer>
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
			* field None<integer>
			* field NoTitleBar<integer>
			* field NoResize<integer>
			* field NoMove<integer>
			* field NoScrollbar<integer>
			* field NoScrollWithMouse<integer>
			* field NoCollapse<integer>
			* field AlwaysAutoResize<integer>
			* field NoBackground<integer>
			* field NoSavedSettings<integer>
			* field NoMouseInputs<integer>
			* field MenuBar<integer>
			* field HorizontalScrollbar<integer>
			* field NoFocusOnAppearing<integer>
			* field NoBringToFrontOnFocus<integer>
			* field AlwaysVerticalScrollbar<integer>
			* field AlwaysHorizontalScrollbar<integer>
			* field NoNavInputs<integer>
			* field NoNavFocus<integer>
			* field UnsavedDocument<integer>
			* field NoNav<integer>
			* field NoDecoration<integer>
			* field NoInputs<integer>
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
			* field DisabledAlpha<integer>
			* field WindowPadding<integer>
			* field WindowRounding<integer>
			* field WindowBorderSize<integer>
			* field WindowMinSize<integer>
			* field WindowTitleAlign<integer>
			* field ChildRounding<integer>
			* field ChildBorderSize<integer>
			* field PopupRounding<integer>
			* field PopupBorderSize<integer>
			* field FramePadding<integer>
			* field FrameRounding<integer>
			* field FrameBorderSize<integer>
			* field ItemSpacing<integer>
			* field ItemInnerSpacing<integer>
			* field IndentSpacing<integer>
			* field CellPadding<integer>
			* field ScrollbarSize<integer>
			* field ScrollbarRounding<integer>
			* field ScrollbarPadding<integer>
			* field GrabMinSize<integer>
			* field GrabRounding<integer>
			* field ImageBorderSize<integer>
			* field TabRounding<integer>
			* field TabBorderSize<integer>
			* field TabMinWidthBase<integer>
			* field TabMinWidthShrink<integer>
			* field TabBarBorderSize<integer>
			* field TabBarOverlineSize<integer>
			* field TableAngledHeadersAngle<integer>
			* field TableAngledHeadersTextAlign<integer>
			* field TreeLinesSize<integer>
			* field TreeLinesRounding<integer>
			* field ButtonTextAlign<integer>
			* field SelectableTextAlign<integer>
			* field SeparatorTextBorderSize<integer>
			* field SeparatorTextAlign<integer>
			* field SeparatorTextPadding<integer>
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
			* field TextDisabled<integer>
			* field WindowBg<integer>
			* field ChildBg<integer>
			* field PopupBg<integer>
			* field Border<integer>
			* field BorderShadow<integer>
			* field FrameBg<integer>
			* field FrameBgHovered<integer>
			* field FrameBgActive<integer>
			* field TitleBg<integer>
			* field TitleBgActive<integer>
			* field TitleBgCollapsed<integer>
			* field MenuBarBg<integer>
			* field ScrollbarBg<integer>
			* field ScrollbarGrab<integer>
			* field ScrollbarGrabHovered<integer>
			* field ScrollbarGrabActive<integer>
			* field CheckMark<integer>
			* field SliderGrab<integer>
			* field SliderGrabActive<integer>
			* field Button<integer>
			* field ButtonHovered<integer>
			* field ButtonActive<integer>
			* field Header<integer>
			* field HeaderHovered<integer>
			* field HeaderActive<integer>
			* field Separator<integer>
			* field SeparatorHovered<integer>
			* field SeparatorActive<integer>
			* field ResizeGrip<integer>
			* field ResizeGripHovered<integer>
			* field ResizeGripActive<integer>
			* field InputTextCursor<integer>
			* field TabHovered<integer>
			* field Tab<integer>
			* field TabSelected<integer>
			* field TabSelectedOverline<integer>
			* field TabDimmed<integer>
			* field TabDimmedSelected<integer>
			* field TabDimmedSelectedOverline<integer>
			* field PlotLines<integer>
			* field PlotLinesHovered<integer>
			* field PlotHistogram<integer>
			* field PlotHistogramHovered<integer>
			* field TableHeaderBg<integer>
			* field TableBorderStrong<integer>
			* field TableBorderLight<integer>
			* field TableRowBg<integer>
			* field TableRowBgAlt<integer>
			* field TextLink<integer>
			* field TextSelectedBg<integer>
			* field TreeLines<integer>
			* field DragDropTarget<integer>
			* field UnsavedMarker<integer>
			* field NavCursor<integer>
			* field NavWindowingHighlight<integer>
			* field NavWindowingDimBg<integer>
			* field ModalWindowDimBg<integer>
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
