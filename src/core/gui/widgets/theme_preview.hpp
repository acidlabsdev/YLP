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

namespace ImGui
{
	inline bool ThemePreview(const YLP::Frontend::Theme& theme, bool selected = false, const ImVec2& size = {200, 200})
	{
		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec2 windowPadding = style.WindowPadding;

		ImGui::BeginGroup();
		ImGui::PushID(&theme);

		auto& themeStyles = theme.m_StyleVars;
		auto& themeColors = theme.m_Colors;

		ImVec4 windowBg = themeColors.find("WindowBg") != themeColors.end() ? themeColors.at("WindowBg") : style.Colors[ImGuiCol_WindowBg];
		ImVec4 childBg = themeColors.find("ChildBg") != themeColors.end() ? themeColors.at("ChildBg") : style.Colors[ImGuiCol_ChildBg];
		ImVec4 borderCol = themeColors.find("Border") != themeColors.end() ? themeColors.at("Border") : style.Colors[ImGuiCol_Border];
		ImVec4 textColor = themeColors.find("Text") != themeColors.end() ? themeColors.at("Text") : style.Colors[ImGuiCol_Text];
		ImVec4 buttonColor = themeColors.find("Button") != themeColors.end() ? themeColors.at("Button") : style.Colors[ImGuiCol_Button];
		
		float childRounding = themeStyles.find("ChildRounding") != themeStyles.end() ? std::get<float>(themeStyles.at("ChildRounding")) : style.ChildRounding;
		float frameRounding = themeStyles.find("FrameRounding") != themeStyles.end() ? std::get<float>(themeStyles.at("FrameRounding")) : style.FrameRounding;
		bool clicked = ImGui::InvisibleButton("##preview", size + style.ItemSpacing + ImVec2(0, ImGui::GetFrameHeight()));
		bool hovered = ImGui::IsItemHovered();
		const float pad = size.x * 0.06f;
		const float consoleMockHeight = size.x * 0.22f;
		const float lowerTextHeight = style.ItemSpacing.y * 7;
		const float lineH = size.y * 0.025f;
		ImDrawList* drawList = ImGui::GetWindowDrawList();
		ImVec2 min = pos + ImVec2(1, 1);
		ImVec2 max = min + size - ImVec2(1, 1 + consoleMockHeight + lowerTextHeight);
		drawList->AddRectFilled(
		    min,
		    max,
		    ImGui::GetColorU32(windowBg),
		    childRounding);

		const float sidebarW = size.x * 0.1f;
		ImVec2 sidebarMin(min.x + 4.0f, min.y + 8.0f);
		ImVec2 sidebarMax(sidebarMin.x + sidebarW, max.y - 8.0f);
		drawList->AddRectFilled(
		    sidebarMin - ImVec2(1, 1),
		    sidebarMax + ImVec2(1, 1),
		    ImGui::GetColorU32(borderCol),
		    childRounding);

		drawList->AddRectFilled(
		    sidebarMin,
		    sidebarMax,
		    ImGui::GetColorU32(ImVec4(childBg.x, childBg.y, childBg.z, childBg.w)),
		    childRounding);

		ImVec2 navButtonMin(sidebarMin.x + 6.0f, sidebarMin.y + 20.0f);
		ImVec2 navButtonMax(navButtonMin.x + 6.5f, navButtonMin.y + 6.5f);
		float buttonPadding = pad * 1.2f;
		for (int i = 0; i < 4; i++)
		{
			drawList->AddRectFilled(
			    navButtonMin,
			    navButtonMax,
			    ImGui::GetColorU32(textColor),
			    frameRounding);
			navButtonMin.y += buttonPadding;
			navButtonMax.y += buttonPadding;
		}

		float contentX = min.x + sidebarW + pad;
		ImVec2 lineMin(contentX, min.y + 12.0f);
		ImVec2 lineMax(max.x - 6.0f, lineMin.y + 1.6f);
		drawList->AddRectFilled(
		    lineMin,
		    lineMax,
		    ImGui::GetColorU32(textColor),
		    1.5f);

		drawList->AddRectFilled(
		    lineMin + ImVec2(0, pad),
		    lineMax + ImVec2(0, pad),
		    ImGui::GetColorU32(textColor),
		    1.5f);

		drawList->AddRectFilled(
		    lineMin + ImVec2(0, pad * 2),
		    ImVec2(lineMax.x - 60.f, lineMax.y + (pad * 2)),
		    ImGui::GetColorU32(textColor),
		    1.5f);

		ImVec2 buttonMin = lineMin + ImVec2(0, pad * 4);
		ImVec2 buttonMax(buttonMin.x + 11.0f, buttonMin.y + 6.0f);
		for (int i = 0; i < 5; i++)
		{
			drawList->AddRectFilled(
			    buttonMin,
			    buttonMax,
			    ImGui::GetColorU32(buttonColor),
			    frameRounding);
			buttonMin.x += buttonPadding;
			buttonMax.x += buttonPadding;
		}

		ImVec2 consoleMin(min.x, max.y + (pad * 0.5));
		ImVec2 consoleMax(max.x, consoleMin.y + consoleMockHeight);
		drawList->AddRectFilled(
		    consoleMin,
		    consoleMax,
		    ImGui::GetColorU32(windowBg),
		    childRounding);

		drawList->AddRectFilled(
		    consoleMin + ImVec2(4.f, 4.f),
		    consoleMax - ImVec2(4.f, 4.f),
		    IM_COL32(0, 0, 0, 225),
		    childRounding);

		int textColIdx = selected ? ImGuiCol_CheckMark : hovered ? ImGuiCol_TextDisabled :
		                                                           ImGuiCol_Text;
		ImVec2 textSize = ImGui::CalcTextSize(theme.m_Name.data());
		ImVec2 rbSize = ImGui::CalcTextSize(ICON_MD_RADIO_BUTTON_CHECKED);
		float textCenter = (pos.x + max.x - textSize.x) * 0.5f;
		float rbCenter = (pos.x + max.x - rbSize.x) * 0.5f;
		drawList->AddText(
		    ImVec2(textCenter, consoleMax.y + style.ItemSpacing.y),
		    ImGui::GetColorU32(style.Colors[textColIdx]),
		    theme.m_Name.data());

		drawList->AddText(
		    ImVec2(rbCenter, consoleMax.y + textSize.y + (style.ItemSpacing.y * 2)),
		    ImGui::GetColorU32(style.Colors[textColIdx]),
		    selected ? ICON_MD_RADIO_BUTTON_CHECKED : ICON_MD_RADIO_BUTTON_UNCHECKED);

		if (hovered)
		{
			ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
			bool pressed = hovered && ImGui::IsMouseDown(0);
			float alpha = pressed ? 65 : 25;
			drawList->AddRectFilled(
			    min,
			    consoleMax,
			    IM_COL32(255, 255, 255, alpha),
			    childRounding);
		}
		ImGui::PopID();
		ImGui::EndGroup();
		return clicked;
	}
}
