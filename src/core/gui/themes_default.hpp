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

#include "theme.hpp"


/*
	credits for these themes: 

	https://github.com/ocornut/imgui/issues/707
	https://github.com/YimMenu-Lua/Samurais-Scripts/blob/main/SSV2/includes/lib/theme_library.lua
*/
namespace YLP::Frontend::DefaultThemes
{
	inline Theme Nord()
	{
		Theme theme{};
		theme.m_Name = "Nord";
		theme.m_AuthorName = "Advik-B (ImGui#707)";
		theme.m_StyleVars = {
		    {"WindowRounding", 8.0f},
		    {"ChildRounding", 6.0f},
		    {"FrameRounding", 5.0f},
		    {"PopupRounding", 6.0f},
		    {"ScrollbarRounding", 5.0f},
		    {"GrabRounding", 4.0f},
		    {"TabRounding", 5.0f},
		    {"WindowBorderSize", 0.0f},
		    {"FrameBorderSize", 0.0f},
		    {"PopupBorderSize", 1.0f},
		    {"WindowPadding", ImVec2(14, 14)},
		    {"FramePadding", ImVec2(10, 6)},
		    {"ItemSpacing", ImVec2(10, 10)},
		    {"ItemInnerSpacing", ImVec2(6, 4)},
		};
		theme.m_Colors = {
		    {"WindowBg", ImVec4(0.12f, 0.13f, 0.15f, 1.00f)},
		    {"ChildBg", ImVec4(0.14f, 0.15f, 0.17f, 1.00f)},
		    {"PopupBg", ImVec4(0.10f, 0.10f, 0.12f, 0.95f)},
		    {"Border", ImVec4(0.30f, 0.33f, 0.42f, 0.40f)},
		    {"Text", ImVec4(0.90f, 0.93f, 0.95f, 1.00f)},
		    {"TextDisabled", ImVec4(0.60f, 0.65f, 0.70f, 1.00f)},
		    {"Header", ImVec4(0.36f, 0.42f, 0.55f, 0.60f)},
		    {"HeaderHovered", ImVec4(0.44f, 0.50f, 0.68f, 0.80f)},
		    {"HeaderActive", ImVec4(0.46f, 0.55f, 0.75f, 1.00f)},
		    {"Button", ImVec4(0.28f, 0.34f, 0.48f, 0.70f)},
		    {"ButtonHovered", ImVec4(0.36f, 0.45f, 0.65f, 0.85f)},
		    {"ButtonActive", ImVec4(0.40f, 0.50f, 0.70f, 1.00f)},
		    {"FrameBg", ImVec4(0.20f, 0.22f, 0.28f, 1.00f)},
		    {"FrameBgHovered", ImVec4(0.28f, 0.32f, 0.42f, 1.00f)},
		    {"FrameBgActive", ImVec4(0.32f, 0.38f, 0.50f, 1.00f)},
		    {"Tab", ImVec4(0.26f, 0.30f, 0.42f, 0.80f)},
		    {"TabHovered", ImVec4(0.36f, 0.42f, 0.58f, 1.00f)},
		    {"TabActive", ImVec4(0.42f, 0.50f, 0.68f, 1.00f)},
		    {"TabUnfocused", ImVec4(0.20f, 0.24f, 0.32f, 0.80f)},
		    {"TabUnfocusedActive", ImVec4(0.30f, 0.36f, 0.50f, 1.00f)},
		    {"TitleBg", ImVec4(0.20f, 0.25f, 0.30f, 1.00f)},
		    {"TitleBgActive", ImVec4(0.25f, 0.30f, 0.40f, 1.00f)},
		    {"TitleBgCollapsed", ImVec4(0.10f, 0.12f, 0.15f, 0.75f)},
		    {"ScrollbarBg", ImVec4(0.13f, 0.14f, 0.18f, 1.00f)},
		    {"ScrollbarGrab", ImVec4(0.25f, 0.30f, 0.38f, 0.60f)},
		    {"ScrollbarGrabHovered", ImVec4(0.35f, 0.40f, 0.50f, 0.80f)},
		    {"ScrollbarGrabActive", ImVec4(0.45f, 0.50f, 0.65f, 1.00f)},
		    {"CheckMark", ImVec4(0.80f, 0.85f, 1.00f, 1.00f)},
		    {"SliderGrab", ImVec4(0.50f, 0.65f, 0.90f, 1.00f)},
		    {"SliderGrabActive", ImVec4(0.60f, 0.75f, 1.00f, 1.00f)},
		    {"ResizeGrip", ImVec4(0.30f, 0.40f, 0.50f, 0.60f)},
		    {"ResizeGripHovered", ImVec4(0.40f, 0.50f, 0.60f, 0.80f)},
		    {"ResizeGripActive", ImVec4(0.50f, 0.60f, 0.80f, 1.00f)},
		    {"Separator", ImVec4(0.35f, 0.40f, 0.48f, 0.7f)},
		    {"SeparatorHovered", ImVec4(0.50f, 0.60f, 0.72f, 0.9f)},
		    {"SeparatorActive", ImVec4(0.65f, 0.70f, 0.85f, 1.0f)},
		    {"MenuBarBg", ImVec4(0.14f, 0.15f, 0.17f, 1.00f)},
		    {"DragDropTarget", ImVec4(0.50f, 0.85f, 1.00f, 0.90f)},
		};

		return theme;
	}

	// https://github.com/ocornut/imgui/issues/707#issuecomment-3592676777
	inline Theme CatppuccinMocha()
	{
		const ImVec4 base = ImVec4(0.117f, 0.117f, 0.172f, 1.0f);     // #1e1e2e
		const ImVec4 mantle = ImVec4(0.109f, 0.109f, 0.156f, 1.0f);   // #181825
		const ImVec4 surface0 = ImVec4(0.200f, 0.207f, 0.286f, 1.0f); // #313244
		const ImVec4 surface1 = ImVec4(0.247f, 0.254f, 0.337f, 1.0f); // #3f4056
		const ImVec4 surface2 = ImVec4(0.290f, 0.301f, 0.388f, 1.0f); // #4a4d63
		const ImVec4 overlay0 = ImVec4(0.396f, 0.403f, 0.486f, 1.0f); // #65677c
		const ImVec4 overlay2 = ImVec4(0.576f, 0.584f, 0.654f, 1.0f); // #9399b2
		const ImVec4 text = ImVec4(0.803f, 0.815f, 0.878f, 1.0f);     // #cdd6f4
		const ImVec4 subtext0 = ImVec4(0.639f, 0.658f, 0.764f, 1.0f); // #a3a8c3
		const ImVec4 mauve = ImVec4(0.796f, 0.698f, 0.972f, 1.0f);    // #cba6f7
		const ImVec4 peach = ImVec4(0.980f, 0.709f, 0.572f, 1.0f);    // #fab387
		const ImVec4 yellow = ImVec4(0.980f, 0.913f, 0.596f, 1.0f);   // #f9e2af
		const ImVec4 green = ImVec4(0.650f, 0.890f, 0.631f, 1.0f);    // #a6e3a1
		const ImVec4 teal = ImVec4(0.580f, 0.886f, 0.819f, 1.0f);     // #94e2d5
		const ImVec4 sapphire = ImVec4(0.458f, 0.784f, 0.878f, 1.0f); // #74c7ec
		const ImVec4 blue = ImVec4(0.533f, 0.698f, 0.976f, 1.0f);     // #89b4fa
		const ImVec4 lavender = ImVec4(0.709f, 0.764f, 0.980f, 1.0f); // #b4befe

		Theme theme{};
		theme.m_Name = "Catppuccin Mocha";
		theme.m_AuthorName = "TheAncientOwl (ImGui#707)";
		theme.m_StyleVars = {
		    {"WindowPadding", ImVec2(12.0f, 12.0f)},
		    {"FramePadding", ImVec2(6.0f, 4.0f)},
		    {"ItemSpacing", ImVec2(8.0f, 6.0f)},
		    {"ScrollbarSize", 14.0f},
		    {"GrabMinSize", 12.0f},
		    {"WindowRounding", 8.0f},
		    {"FrameRounding", 5.0f},
		    {"PopupRounding", 5.0f},
		    {"ScrollbarRounding", 12.0f},
		    {"GrabRounding", 5.0f},
		    {"TabRounding", 5.0f},
		    {"WindowBorderSize", 1.0f},
		    {"FrameBorderSize", 0.0f},
		    {"PopupBorderSize", 1.0f},
		};
		theme.m_Colors = {
		    {"Text", ImVec4(0.80f, 0.84f, 0.96f, 1.00f)},
		    {"TextDisabled", ImVec4(0.42f, 0.45f, 0.55f, 1.00f)},
		    {"WindowBg", ImVec4(0.12f, 0.12f, 0.18f, 1.00f)},
		    {"ChildBg", ImVec4(0.09f, 0.09f, 0.15f, 1.00f)},
		    {"PopupBg", ImVec4(0.07f, 0.07f, 0.11f, 0.96f)},
		    {"Border", ImVec4(0.19f, 0.20f, 0.27f, 1.00f)},
		    {"BorderShadow", ImVec4(0.00f, 0.00f, 0.00f, 0.00f)},
		    {"FrameBg", ImVec4(0.19f, 0.20f, 0.27f, 1.00f)},
		    {"FrameBgHovered", ImVec4(0.25f, 0.26f, 0.35f, 1.00f)},
		    {"FrameBgActive", ImVec4(0.31f, 0.32f, 0.42f, 1.00f)},
		    {"TitleBg", ImVec4(0.09f, 0.09f, 0.15f, 1.00f)},
		    {"TitleBgActive", ImVec4(0.12f, 0.12f, 0.18f, 1.00f)},
		    {"TitleBgCollapsed", ImVec4(0.07f, 0.07f, 0.11f, 1.00f)},
		    {"MenuBarBg", ImVec4(0.09f, 0.09f, 0.15f, 1.00f)},
		    {"ScrollbarBg", ImVec4(0.09f, 0.09f, 0.15f, 1.00f)},
		    {"ScrollbarGrab", ImVec4(0.31f, 0.32f, 0.42f, 1.00f)},
		    {"ScrollbarGrabHovered", ImVec4(0.37f, 0.38f, 0.51f, 1.00f)},
		    {"ScrollbarGrabActive", ImVec4(0.42f, 0.45f, 0.55f, 1.00f)},
		    {"CheckMark", ImVec4(0.71f, 0.75f, 1.00f, 1.00f)},
		    {"SliderGrab", ImVec4(0.45f, 0.78f, 0.93f, 1.00f)},
		    {"SliderGrabActive", ImVec4(0.45f, 0.78f, 0.93f, 1.00f)},
		    {"Button", ImVec4(0.19f, 0.20f, 0.27f, 1.00f)},
		    {"ButtonHovered", ImVec4(0.80f, 0.65f, 0.97f, 1.00f)},
		    {"ButtonActive", ImVec4(0.70f, 0.55f, 0.87f, 1.00f)},
		    {"Header", ImVec4(0.19f, 0.20f, 0.27f, 1.00f)},
		    {"HeaderHovered", ImVec4(0.25f, 0.26f, 0.35f, 1.00f)},
		    {"HeaderActive", ImVec4(0.31f, 0.32f, 0.42f, 1.00f)},
		    {"Tab", ImVec4(0.12f, 0.12f, 0.18f, 1.00f)},
		    {"TabHovered", ImVec4(0.31f, 0.32f, 0.42f, 1.00f)},
		    {"TabActive", ImVec4(0.19f, 0.20f, 0.27f, 1.00f)},
		    {"TabUnfocused", ImVec4(0.09f, 0.09f, 0.15f, 1.00f)},
		    {"TabUnfocusedActive", ImVec4(0.12f, 0.12f, 0.18f, 1.00f)},
		    {"PlotLines", ImVec4(0.94f, 0.72f, 0.42f, 1.00f)},
		    {"TextSelectedBg", ImVec4(0.31f, 0.32f, 0.42f, 1.00f)},
		    {"NavHighlight", ImVec4(0.71f, 0.75f, 1.00f, 1.00f)},
		};

		return theme;
	}

	inline Theme RoseQuartz()
	{
		Theme theme{};
		theme.m_Name = "Rose Quartz";
		theme.m_AuthorName = "TheAncientOwl (ImGui#707)";
		theme.m_StyleVars = {
		    {"WindowPadding", ImVec2(10.0f, 10.0f)},
		    {"FramePadding", ImVec2(6.0f, 4.0f)},
		    {"ItemSpacing", ImVec2(8.0f, 5.0f)},
		    {"ScrollbarSize", 14.0f},
		    {"GrabMinSize", 12.0f},
		    {"WindowRounding", 10.0f},
		    {"ChildRounding", 6.0f},
		    {"FrameRounding", 6.0f},
		    {"PopupRounding", 6.0f},
		    {"ScrollbarRounding", 12.0f},
		    {"GrabRounding", 6.0f},
		    {"TabRounding", 6.0f},
		    {"WindowBorderSize", 1.0f},
		    {"FrameBorderSize", 0.0f},
		};
		theme.m_Colors = {
		    {"Text", ImVec4(0.95f, 0.90f, 0.95f, 1.00f)},
		    {"TextDisabled", ImVec4(0.55f, 0.45f, 0.55f, 1.00f)},
		    {"WindowBg", ImVec4(0.12f, 0.10f, 0.12f, 1.00f)},
		    {"ChildBg", ImVec4(0.14f, 0.12f, 0.14f, 1.00f)},
		    {"PopupBg", ImVec4(0.10f, 0.08f, 0.10f, 0.96f)},
		    {"Border", ImVec4(0.35f, 0.25f, 0.35f, 0.50f)},
		    {"BorderShadow", ImVec4(0.00f, 0.00f, 0.00f, 0.00f)},
		    {"FrameBg", ImVec4(0.20f, 0.15f, 0.20f, 1.00f)},
		    {"FrameBgHovered", ImVec4(0.30f, 0.22f, 0.30f, 1.00f)},
		    {"FrameBgActive", ImVec4(0.40f, 0.28f, 0.40f, 1.00f)},
		    {"TitleBg", ImVec4(0.15f, 0.10f, 0.15f, 1.00f)},
		    {"TitleBgActive", ImVec4(0.25f, 0.15f, 0.25f, 1.00f)},
		    {"TitleBgCollapsed", ImVec4(0.08f, 0.06f, 0.08f, 1.00f)},
		    {"MenuBarBg", ImVec4(0.15f, 0.10f, 0.15f, 1.00f)},
		    {"ScrollbarBg", ImVec4(0.08f, 0.06f, 0.08f, 1.00f)},
		    {"ScrollbarGrab", ImVec4(0.40f, 0.25f, 0.40f, 1.00f)},
		    {"ScrollbarGrabHovered", ImVec4(0.55f, 0.35f, 0.55f, 1.00f)},
		    {"ScrollbarGrabActive", ImVec4(0.70f, 0.45f, 0.70f, 1.00f)},
		    {"CheckMark", ImVec4(0.95f, 0.60f, 0.75f, 1.00f)},
		    {"SliderGrab", ImVec4(0.85f, 0.50f, 0.65f, 1.00f)},
		    {"SliderGrabActive", ImVec4(0.95f, 0.60f, 0.75f, 1.00f)},
		    {"Button", ImVec4(0.45f, 0.25f, 0.35f, 1.00f)},
		    {"ButtonHovered", ImVec4(0.65f, 0.35f, 0.50f, 1.00f)},
		    {"ButtonActive", ImVec4(0.85f, 0.45f, 0.65f, 1.00f)},
		    {"Header", ImVec4(0.45f, 0.25f, 0.35f, 1.00f)},
		    {"HeaderHovered", ImVec4(0.55f, 0.30f, 0.45f, 1.00f)},
		    {"HeaderActive", ImVec4(0.65f, 0.35f, 0.55f, 1.00f)},
		    {"Tab", ImVec4(0.20f, 0.15f, 0.20f, 1.00f)},
		    {"TabHovered", ImVec4(0.65f, 0.35f, 0.50f, 1.00f)},
		    {"TabActive", ImVec4(0.45f, 0.25f, 0.35f, 1.00f)},
		    {"TextSelectedBg", ImVec4(0.95f, 0.60f, 0.75f, 0.35f)},
		    {"NavHighlight", ImVec4(0.95f, 0.60f, 0.75f, 1.00f)},
		};

		return theme;
	}

	inline Theme Moonlight()
	{
		Theme theme{};
		theme.m_Name = "Moonlight";
		theme.m_AuthorName = "ImThemes (Madam-Herta)";
		theme.m_StyleVars = {
		    {"DisabledAlpha", 1.0f},
		    {"WindowPadding", ImVec2(12.0f, 12.0f)},
		    {"WindowRounding", 11.5f},
		    {"WindowBorderSize", 0.0f},
		    {"WindowTitleAlign", ImVec2(0.5f, 0.5f)},
		    {"ChildRounding", 0.0f},
		    {"ChildBorderSize", 1.0f},
		    {"PopupRounding", 0.0f},
		    {"PopupBorderSize", 1.0f},
		    {"FramePadding", ImVec2(6.0f, 6.0f)},
		    {"FrameRounding", 11.9f},
		    {"FrameBorderSize", 0.0f},
		    {"ItemSpacing", ImVec2(4.3f, 5.5f)},
		    {"ItemInnerSpacing", ImVec2(7.1f, 4.0f)},
		    {"CellPadding", ImVec2(12.1f, 9.2f)},
		    {"IndentSpacing", 0.0f},
		    {"ColumnsMinSpacing", 4.9f},
		    {"ScrollbarSize", 11.6f},
		    {"ScrollbarRounding", 15.9f},
		    {"GrabMinSize", 3.7f},
		    {"GrabRounding", 20.0f},
		    {"TabRounding", 0.0f},
		    {"TabBorderSize", 0.0f},
		    {"TabMinWidthForCloseButton", 0.0f},
		    {"ButtonTextAlign", ImVec2(0.5f, 0.5f)},
		    {"SelectableTextAlign", ImVec2(0.0f, 0.0f)},
		};
		theme.m_Colors = {
		    {"Text", ImVec4(1.0f, 1.0f, 1.0f, 1.0f)},
		    {"TextDisabled", ImVec4(0.27450982f, 0.31764707f, 0.4509804f, 1.0f)},
		    {"WindowBg", ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f)},
		    {"ChildBg", ImVec4(0.09411765f, 0.101960786f, 0.11764706f, 1.0f)},
		    {"PopupBg", ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f)},
		    {"Border", ImVec4(0.15686275f, 0.16862746f, 0.19215687f, 1.0f)},
		    {"BorderShadow", ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f)},
		    {"FrameBg", ImVec4(0.11372549f, 0.1254902f, 0.15294118f, 1.0f)},
		    {"FrameBgHovered", ImVec4(0.15686275f, 0.16862746f, 0.19215687f, 1.0f)},
		    {"FrameBgActive", ImVec4(0.15686275f, 0.16862746f, 0.19215687f, 1.0f)},
		    {"TitleBg", ImVec4(0.047058824f, 0.05490196f, 0.07058824f, 1.0f)},
		    {"TitleBgActive", ImVec4(0.047058824f, 0.05490196f, 0.07058824f, 1.0f)},
		    {"TitleBgCollapsed", ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f)},
		    {"MenuBarBg", ImVec4(0.09803922f, 0.105882354f, 0.12156863f, 1.0f)},
		    {"ScrollbarBg", ImVec4(0.047058824f, 0.05490196f, 0.07058824f, 1.0f)},
		    {"ScrollbarGrab", ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f)},
		    {"ScrollbarGrabHovered", ImVec4(0.15686275f, 0.16862746f, 0.19215687f, 1.0f)},
		    {"ScrollbarGrabActive", ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f)},
		    {"CheckMark", ImVec4(0.972549f, 1.0f, 0.49803922f, 1.0f)},
		    {"SliderGrab", ImVec4(0.972549f, 1.0f, 0.49803922f, 1.0f)},
		    {"SliderGrabActive", ImVec4(1.0f, 0.79607844f, 0.49803922f, 1.0f)},
		    {"Button", ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f)},
		    {"ButtonHovered", ImVec4(0.18039216f, 0.1882353f, 0.19607843f, 1.0f)},
		    {"ButtonActive", ImVec4(0.15294118f, 0.15294118f, 0.15294118f, 1.0f)},
		    {"Header", ImVec4(0.14117648f, 0.16470589f, 0.20784314f, 1.0f)},
		    {"HeaderHovered", ImVec4(0.105882354f, 0.105882354f, 0.105882354f, 1.0f)},
		    {"HeaderActive", ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f)},
		    {"Separator", ImVec4(0.12941177f, 0.14901961f, 0.19215687f, 1.0f)},
		    {"SeparatorHovered", ImVec4(0.15686275f, 0.18431373f, 0.2509804f, 1.0f)},
		    {"SeparatorActive", ImVec4(0.15686275f, 0.18431373f, 0.2509804f, 1.0f)},
		    {"ResizeGrip", ImVec4(0.14509805f, 0.14509805f, 0.14509805f, 1.0f)},
		    {"ResizeGripHovered", ImVec4(0.972549f, 1.0f, 0.49803922f, 1.0f)},
		    {"ResizeGripActive", ImVec4(1.0f, 1.0f, 1.0f, 1.0f)},
		    {"Tab", ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f)},
		    {"TabHovered", ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f)},
		    {"TabActive", ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f)},
		    {"TabUnfocused", ImVec4(0.078431375f, 0.08627451f, 0.101960786f, 1.0f)},
		    {"TabUnfocusedActive", ImVec4(0.1254902f, 0.27450982f, 0.57254905f, 1.0f)},
		    {"PlotLines", ImVec4(0.52156866f, 0.6f, 0.7019608f, 1.0f)},
		    {"PlotLinesHovered", ImVec4(0.039215688f, 0.98039216f, 0.98039216f, 1.0f)},
		    {"PlotHistogram", ImVec4(0.88235295f, 0.79607844f, 0.56078434f, 1.0f)},
		    {"PlotHistogramHovered", ImVec4(0.95686275f, 0.95686275f, 0.95686275f, 1.0f)},
		    {"TableHeaderBg", ImVec4(0.047058824f, 0.05490196f, 0.07058824f, 1.0f)},
		    {"TableBorderStrong", ImVec4(0.047058824f, 0.05490196f, 0.07058824f, 1.0f)},
		    {"TableBorderLight", ImVec4(0.0f, 0.0f, 0.0f, 1.0f)},
		    {"TableRowBg", ImVec4(0.11764706f, 0.13333334f, 0.14901961f, 1.0f)},
		    {"TableRowBgAlt", ImVec4(0.09803922f, 0.105882354f, 0.12156863f, 1.0f)},
		    {"TextSelectedBg", ImVec4(0.9372549f, 0.9372549f, 0.9372549f, 1.0f)},
		    {"DragDropTarget", ImVec4(0.49803922f, 0.5137255f, 1.0f, 1.0f)},
		    {"NavHighlight", ImVec4(0.26666668f, 0.2901961f, 1.0f, 1.0f)},
		    {"NavWindowingHighlight", ImVec4(0.49803922f, 0.5137255f, 1.0f, 1.0f)},
		    {"NavWindowingDimBg", ImVec4(0.19607843f, 0.1764706f, 0.54509807f, 0.5019608f)},
		    {"ModalWindowDimBg", ImVec4(0.19607843f, 0.1764706f, 0.54509807f, 0.5019608f)},
		};

		return theme;
	}

	inline Theme CP2077()
	{
		Theme theme{};
		theme.m_Name = "CP2077";
		theme.m_AuthorName = "SSV2";
		theme.m_StyleVars = {
		    {"WindowRounding", 0.0f},
		    {"ChildRounding", 0.0f},
		    {"FrameRounding", 0.0f},
		    {"GrabRounding", 0.0f},
		    {"TabRounding", 0.0f},
		    {"ScrollbarRounding", 0.0f},
		    {"WindowBorderSize", 0.0f},
		    {"FrameBorderSize", 0.01f},
		    {"PopupBorderSize", 0.0f},
		    {"ItemSpacing", ImVec2(10, 10)},
		    {"FramePadding", ImVec2(5, 6)},
		};
		theme.m_Colors = {
		    {"WindowBg", ImVec4(0.00, 0.00, 0.00, 0.94)},
		    {"ChildBg", ImVec4(0.05, 0.05, 0.05, 1.00)},
		    {"PopupBg", ImVec4(0.06, 0.04, 0.06, 0.90)},
		    {"Border", ImVec4(1.00, 0.38, 0.33, 1.00)},
		    {"TitleBg", ImVec4(0.06, 0.04, 0.06, 0.90)},
		    {"TitleBgActive", ImVec4(0.06, 0.04, 0.06, 0.90)},
		    {"TitleBgCollapsed", ImVec4(0.06, 0.04, 0.06, 0.90)},
		    {"ScrollbarBg", ImVec4(0.23, 0.07, 0.09, 1.00)},
		    {"ScrollbarGrab", ImVec4(0.95, 0.30, 0.28, 0.80)},
		    {"ScrollbarGrabHovered", ImVec4(0.95, 0.30, 0.28, 0.90)},
		    {"ScrollbarGrabActive", ImVec4(0.95, 0.30, 0.28, 1.00)},
		    {"Header", ImVec4(0.08, 0.08, 0.15, 1.00)},
		    {"HeaderHovered", ImVec4(0.22, 0.64, 0.69, 0.30)},
		    {"HeaderActive", ImVec4(0.22, 0.64, 0.69, 0.50)},
		    {"Button", ImVec4(0.10, 0.15, 0.24, 0.90)},
		    {"ButtonHovered", ImVec4(0.12, 0.22, 0.32, 0.95)},
		    {"ButtonActive", ImVec4(0.11, 0.18, 0.26, 1.00)},
		    {"FrameBg", ImVec4(0.08, 0.10, 0.12, 0.90)},
		    {"FrameBgHovered", ImVec4(0.12, 0.15, 0.18, 0.95)},
		    {"FrameBgActive", ImVec4(0.14, 0.17, 0.20, 1.00)},
		    {"Tab", ImVec4(0.52, 0.12, 0.12, 0.75)},
		    {"TabHovered", ImVec4(0.54, 0.14, 0.14, 0.90)},
		    {"TabActive", ImVec4(0.57, 0.17, 0.16, 1.00)},
		    {"CheckMark", ImVec4(1.00f, 0.93f, 0.04f, 1.00f)},
		    {"SliderGrab", ImVec4(0.99, 0.96, 0.00, 0.90)},
		    {"SliderGrabActive", ImVec4(0.99, 0.96, 0.00, 1.00)},
		    {"Text", ImVec4(0.00, 0.87, 1.00, 1.00)},
		    {"TextDisabled", ImVec4(0.00, 0.80, 0.90, 0.50)},
		    {"PlotHistogram", ImVec4(0.00, 0.94, 0.94, 0.40)},
		    {"PlotHistogramHovered", ImVec4(0.00, 0.94, 0.94, 0.60)},
		};

		return theme;
	}

	inline Theme Silverlight()
	{
		Theme theme{};
		theme.m_Name = "Silverlight";
		theme.m_AuthorName = "SSV2";
		theme.m_StyleVars = {
		    {"WindowPadding", ImVec2(12.0f, 12.0f)},
		    {"FramePadding", ImVec2(6.0f, 4.0f)},
		    {"CellPadding", ImVec2(6.0f, 4.0f)},
		    {"ItemSpacing", ImVec2(8.0f, 6.0f)},
		    {"ItemInnerSpacing", ImVec2(6.0f, 4.0f)},
		    {"ScrollbarSize", 14.0f},
		    {"GrabMinSize", 12.0f},
		    {"WindowRounding", 2.0f},
		    {"ChildRounding", 2.0f},
		    {"FrameRounding", 2.0f},
		    {"PopupRounding", 2.0f},
		    {"ScrollbarRounding", 12.0f},
		    {"GrabRounding", 2.0f},
		    {"TabRounding", 2.0f},
		    {"WindowBorderSize", 1.0f},
		    {"ChildBorderSize", 1.0f},
		    {"PopupBorderSize", 1.0f},
		    {"FrameBorderSize", 1.0f},
		    {"TabBorderSize", 1.0f},
		};
		theme.m_Colors = {
		    {"WindowBg", ImVec4(0.83, 0.83, 0.83, 1.00)},
		    {"ChildBg", ImVec4(0.80, 0.80, 0.80, 1.0)},
		    {"PopupBg", ImVec4(0.82, 0.82, 0.82, 1.0)},
		    {"Border", ImVec4(0.15, 0.15, 0.15, 1.00)},
		    {"TitleBg", ImVec4(0.85, 0.85, 0.85, 0.90)},
		    {"TitleBgActive", ImVec4(0.85, 0.85, 0.85, 0.90)},
		    {"TitleBgCollapsed", ImVec4(0.85, 0.85, 0.85, 0.90)},
		    {"ScrollbarBg", ImVec4(0.87, 0.87, 0.87, 1.00)},
		    {"ScrollbarGrab", ImVec4(0.75, 0.78, 0.82, 1.00)},
		    {"ScrollbarGrabHovered", ImVec4(0.70, 0.73, 0.77, 1.00)},
		    {"ScrollbarGrabActive", ImVec4(0.65, 0.68, 0.72, 1.00)},
		    {"Header", ImVec4(0.75, 0.78, 0.82, 1.00)},
		    {"HeaderHovered", ImVec4(0.70, 0.73, 0.77, 1.00)},
		    {"HeaderActive", ImVec4(0.65, 0.68, 0.72, 1.00)},
		    {"Button", ImVec4(0.75, 0.77, 0.80, 1.00)},
		    {"ButtonHovered", ImVec4(0.70, 0.72, 0.75, 1.00)},
		    {"ButtonActive", ImVec4(0.65, 0.67, 0.70, 1.00)},
		    {"FrameBg", ImVec4(0.82, 0.83, 0.85, 1.00)},
		    {"FrameBgHovered", ImVec4(0.77, 0.78, 0.80, 1.00)},
		    {"FrameBgActive", ImVec4(0.72, 0.73, 0.75, 1.00)},
		    {"Tab", ImVec4(0.82, 0.82, 0.85, 1.00)},
		    {"TabHovered", ImVec4(0.75, 0.75, 0.78, 1.00)},
		    {"TabActive", ImVec4(0.70, 0.70, 0.73, 1.00)},
		    {"CheckMark", ImVec4(0.15, 0.35, 0.80, 1.00)},
		    {"SliderGrab", ImVec4(0.10, 0.30, 0.80, 0.90)},
		    {"SliderGrabActive", ImVec4(0.15, 0.40, 1.00, 1.00)},
		    {"Text", ImVec4(0.27, 0.27, 0.29, 1.00)},
		    {"TextDisabled", ImVec4(0.50, 0.50, 0.52, 1.00)},
		    {"PlotHistogram", ImVec4(0.09, 0.55, 0.75, 1.00)},
		    {"PlotHistogramHovered", ImVec4(0.15, 0.45, 1.00, 1.00)},
		};

		return theme;
	}

	inline Theme Synthwave()
	{
		Theme theme{};
		theme.m_Name = "Synthwave";
		theme.m_AuthorName = "SSV2";
		theme.m_StyleVars = {
		    {"WindowRounding", 8.0f},
		    {"ChildRounding", 8.0f},
		    {"FrameRounding", 6.0f},
		    {"PopupRounding", 6.0f},
		    {"ScrollbarRounding", 8.0f},
		    {"GrabRounding", 6.0f},
		    {"TabRounding", 6.0f},
		    {"WindowBorderSize", 0.0f},
		    {"FrameBorderSize", 0.0f},
		    {"PopupBorderSize", 0.0f},
		    {"WindowPadding", ImVec2(12.0f, 12.0f)},
		    {"FramePadding", ImVec2(8.0f, 6.0f)},
		    {"ItemSpacing", ImVec2(10.0f, 8.0f)},
		    {"ItemInnerSpacing", ImVec2(8.0f, 6.0f)},
		};
		theme.m_Colors = {
		    {"WindowBg", ImVec4(0.05, 0.04, 0.09, 1.00)},
		    {"ChildBg", ImVec4(0.06, 0.05, 0.11, 1.00)},
		    {"PopupBg", ImVec4(0.06, 0.05, 0.11, 0.98)},
		    {"Border", ImVec4(0.75, 0.55, 0.95, 0.55)},
		    {"TitleBg", ImVec4(0.06, 0.05, 0.11, 0.98)},
		    {"TitleBgActive", ImVec4(0.06, 0.05, 0.11, 0.98)},
		    {"TitleBgCollapsed", ImVec4(0.06, 0.05, 0.11, 0.98)},
		    {"ScrollbarBg", ImVec4(0.10, 0.10, 0.10, 1.00)},
		    {"ScrollbarGrab", ImVec4(0.50, 0.00, 0.50, 1.00)},
		    {"ScrollbarGrabHovered", ImVec4(0.50, 0.00, 0.50, 0.95)},
		    {"ScrollbarGrabActive", ImVec4(0.50, 0.00, 0.50, 0.85)},
		    {"Header", ImVec4(0.13, 0.10, 0.20, 0.80)},
		    {"HeaderHovered", ImVec4(0.18, 0.14, 0.30, 0.95)},
		    {"HeaderActive", ImVec4(0.22, 0.16, 0.40, 1.00)},
		    {"Button", ImVec4(0.18, 0.10, 0.28, 0.85)},
		    {"ButtonHovered", ImVec4(0.55, 0.00, 0.65, 0.85)},
		    {"ButtonActive", ImVec4(0.75, 0.10, 0.85, 1.00)},
		    {"FrameBg", ImVec4(0.10, 0.08, 0.18, 0.90)},
		    {"FrameBgHovered", ImVec4(0.30, 0.12, 0.45, 0.90)},
		    {"FrameBgActive", ImVec4(0.55, 0.15, 0.75, 1.00)},
		    {"Tab", ImVec4(0.18, 0.10, 0.28, 0.85)},
		    {"TabHovered", ImVec4(0.55, 0.00, 0.65, 0.85)},
		    {"TabActive", ImVec4(0.75, 0.10, 0.85, 1.00)},
		    {"CheckMark", ImVec4(0.0, 1.00, 1.00, 0.50)},
		    {"SliderGrab", ImVec4(0.60, 0.10, 0.90, 0.80)},
		    {"SliderGrabActive", ImVec4(0.75, 0.20, 1.00, 1.00)},
		    {"Text", ImVec4(0.90, 0.88, 0.95, 1.00)},
		    {"TextDisabled", ImVec4(0.55, 0.52, 0.65, 1.00)},
		    {"PlotHistogram", ImVec4(0.60, 0.15, 0.90, 0.85)},
		    {"PlotHistogramHovered", ImVec4(0.75, 0.25, 1.00, 1.00)},
		};

		return theme;
	}

	inline Theme CriminalMastermind()
	{
		Theme theme{};
		theme.m_Name = "Criminal Mastermind";
		theme.m_AuthorName = "SSV2";
		theme.m_StyleVars = {
		    {"WindowRounding", 6.0f},
		    {"ChildRounding", 6.0f},
		    {"FrameRounding", 5.0f},
		    {"PopupRounding", 6.0f},
		    {"ScrollbarRounding", 6.0f},
		    {"GrabRounding", 4.0f},
		    {"TabRounding", 5.0f},
		    {"WindowBorderSize", 0.0f},
		    {"FrameBorderSize", 0.0f},
		    {"PopupBorderSize", 0.0f},
		    {"WindowPadding", ImVec2(12.0f, 12.0f)},
		    {"FramePadding", ImVec2(8.0f, 6.0f)},
		    {"ItemSpacing", ImVec2(10.0f, 8.0f)},
		    {"ItemInnerSpacing", ImVec2(8.0f, 6.0f)},
		};
		theme.m_Colors = {
		    {"WindowBg", ImVec4(0.07, 0.07, 0.08, 0.96)},
		    {"ChildBg", ImVec4(0.08, 0.08, 0.09, 0.96)},
		    {"PopupBg", ImVec4(0.06, 0.06, 0.07, 0.94)},
		    {"Border", ImVec4(0.92, 0.90, 0.86, 1.00)},
		    {"TitleBg", ImVec4(0.06, 0.06, 0.07, 0.94)},
		    {"TitleBgActive", ImVec4(0.06, 0.06, 0.07, 0.94)},
		    {"TitleBgCollapsed", ImVec4(0.06, 0.06, 0.07, 0.94)},
		    {"ScrollbarBg", ImVec4(0.08, 0.08, 0.09, 0.96)},
		    {"ScrollbarGrab", ImVec4(0.16, 0.15, 0.13, 0.85)},
		    {"ScrollbarGrabHovered", ImVec4(0.22, 0.21, 0.18, 0.95)},
		    {"ScrollbarGrabActive", ImVec4(0.28, 0.26, 0.22, 1.00)},
		    {"Header", ImVec4(0.16, 0.15, 0.13, 0.85)},
		    {"HeaderHovered", ImVec4(0.22, 0.21, 0.18, 0.95)},
		    {"HeaderActive", ImVec4(0.28, 0.26, 0.22, 1.00)},
		    {"Button", ImVec4(0.14, 0.13, 0.11, 0.90)},
		    {"ButtonHovered", ImVec4(0.20, 0.19, 0.16, 0.95)},
		    {"ButtonActive", ImVec4(0.26, 0.24, 0.20, 1.00)},
		    {"FrameBg", ImVec4(0.11, 0.11, 0.12, 0.92)},
		    {"FrameBgHovered", ImVec4(0.17, 0.16, 0.14, 0.96)},
		    {"FrameBgActive", ImVec4(0.22, 0.21, 0.18, 1.00)},
		    {"Tab", ImVec4(0.12, 0.11, 0.10, 0.90)},
		    {"TabHovered", ImVec4(0.22, 0.21, 0.18, 1.00)},
		    {"TabActive", ImVec4(0.18, 0.17, 0.14, 1.00)},
		    {"CheckMark", ImVec4(0.78, 0.65, 0.30, 1.00)},
		    {"SliderGrab", ImVec4(0.72, 0.60, 0.28, 0.75)},
		    {"SliderGrabActive", ImVec4(0.85, 0.72, 0.35, 1.00)},
		    {"PlotHistogram", ImVec4(0.72, 0.60, 0.28, 0.85)},
		    {"PlotHistogramHovered", ImVec4(0.85, 0.72, 0.35, 1.00)},
		    {"Text", ImVec4(0.92, 0.90, 0.86, 1.00)},
		    {"TextDisabled", ImVec4(0.45, 0.44, 0.42, 1.00)},
		};

		return theme;
	}
}
