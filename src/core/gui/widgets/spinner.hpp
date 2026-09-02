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
	inline void Spinner(const char* label, float radius = 10.0f, float thickness = 2.0f)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return;

		ImGuiStyle& style = ImGui::GetStyle();
		ImGuiContext& g = *GImGui;
		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImVec2 center = ImVec2(pos.x + thickness + radius, pos.y + thickness + radius);

		const int num_segments = 30;
		const float speed = 8.0f;
		float time = static_cast<float>(ImGui::GetTime());
		float start = fmodf(time * speed, IM_PI * 2.0f);
		float a_min = start;
		float a_max = start + IM_PI * 1.5f;

		ImVec4 plotCol = style.Colors[ImGuiCol_PlotHistogram];
		ImVec4 col2 = plotCol - ImVec4(0.01f, 0.01f, 0.01f, 0.5f);
		float phase = fmodf(time * 1.5f, 1.0f);
		ImVec4 col = ImLerp(plotCol, col2, (sinf(phase * IM_PI * 2.0f) * 0.5f) + 0.5f);
		ImU32 color = ImGui::ColorConvertFloat4ToU32(col);
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		draw_list->PathClear();

		for (int i = 0; i <= num_segments; i++)
		{
			float a = a_min + (i / (float)num_segments) * (a_max - a_min);
			draw_list->PathLineTo(ImVec2(center.x + cosf(a) * radius,
			    center.y + sinf(a) * radius));
		}

		draw_list->PathStroke(color, 0, thickness);

		if (label && label[0] && strncmp(label, "##", 2) != 0)
		{
			ImVec2 text_pos = ImVec2(center.x + radius + thickness + style.ItemSpacing.x, pos.y + (radius * 0.5));
			draw_list->AddText(text_pos, ImGui::ColorConvertFloat4ToU32(style.Colors[ImGuiCol_Text]), label);
		}

		ImGui::Dummy(ImVec2(radius * 2 + style.FramePadding.x + thickness, radius * 2 + style.FramePadding.y + thickness));
	}
}
