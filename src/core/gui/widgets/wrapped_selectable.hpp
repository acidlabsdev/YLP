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
	inline bool WrappedSelectable(const char* label)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiStyle& style = ImGui::GetStyle();
		ImVec4 hoverColor = style.Colors[ImGuiCol_HeaderHovered];
		ImVec4 activeColor = style.Colors[ImGuiCol_HeaderActive];
		float wrapX = ImGui::GetCursorPos().x + ImGui::GetContentRegionAvail().x;
		ImGui::PushTextWrapPos(wrapX);

		ImVec2 textPos = ImGui::GetCursorScreenPos();
		ImVec2 labelSize = ImGui::CalcTextSize(label, nullptr, false, wrapX - textPos.x);
		labelSize.x += style.FramePadding.x * 2;
		labelSize.y += style.FramePadding.y * 2;
		ImRect rect(textPos, textPos + labelSize);
		bool hovered = ImGui::IsMouseHoveringRect(rect.Min, rect.Max);
		bool clicked = hovered && ImGui::IsMouseClicked(0);
		bool held = hovered && ImGui::IsMouseDown(0);
		if (hovered)
			ImGui::GetWindowDrawList()->AddRectFilled(rect.Min, rect.Max, ImGui::ColorConvertFloat4ToU32(held ? activeColor : hoverColor), 4.f);

		ImGui::RenderTextWrapped(rect.Min + ImVec2(style.FramePadding.x, style.FramePadding.y), label, nullptr, wrapX - textPos.x);
		ImGui::Dummy(labelSize);
		ImGui::PopTextWrapPos();

		return clicked;
	}
}
