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
	enum ImCalloutType : uint8_t
	{
		ImCalloutType_Note,
		ImCalloutType_Warning,
		ImCalloutType_Important
	};

	inline void InfoCallout(ImCalloutType type, const std::string& text, float wrapWidth = 0.0f)
	{
		ImGuiWindow* window = GetCurrentWindow();
		if (!window)
			return;

		ImVec4 accentColor;
		const char* label{};
		const char* icon{};

		switch (type)
		{
		case ImCalloutType_Note:
			accentColor = ImVec4(0.0f, 0.001f, 0.803f, 1.0f);
			label       = "Note";
			icon        = ICON_MS_MESSAGE;
			break;
		case ImCalloutType_Warning:
			accentColor = ImVec4(1.0f, 0.7568, 0.027f, 1.0f);
			label       = "Warning";
			icon        = ICON_MS_WARNING;
			break;
		case ImCalloutType_Important:
			accentColor = ImVec4(0.498f, 0.1f, 1.0f, 1.0f);
			label       = "Important";
			icon        = ICON_MS_PRIORITY_HIGH;
			break;
		}

		if (wrapWidth <= 0.0f)
			wrapWidth = GetContentRegionAvail().x - 10.0f;

		ImDrawList* drawList = GetWindowDrawList();
		ImVec2 pos           = GetCursorScreenPos();
		ImVec2 textSize      = CalcTextSize(text.c_str(), nullptr, false, wrapWidth);
		float panelHeight    = textSize.y + 30 + (GetStyle().WindowPadding.y * 2);
		float barWidth       = 5.0f;

		drawList->AddRectFilled(pos, ImVec2(pos.x + barWidth, pos.y + panelHeight), ImColor(accentColor));
		SetCursorScreenPos(ImVec2(pos.x + barWidth, pos.y));
		PushStyleVar(ImGuiStyleVar_ChildRounding, 0.f);
		SetNextWindowBgAlpha(0.1f);
		BeginChild(("##panel_" + std::to_string(static_cast<int>(type)) + "_" + std::to_string(window->GetID(text.c_str()))).c_str(),
		    ImVec2(0, panelHeight),
		    ImGuiChildFlags_None,
		    ImGuiWindowFlags_NoScrollbar
			| ImGuiWindowFlags_NoScrollWithMouse
			| ImGuiWindowFlags_AlwaysUseWindowPadding);

		PushFont(Fonts::Bold);
		TextColored(accentColor, std::format("{} {}", icon, label).c_str());
		PopFont();
		//PushTextWrapPos(GetCursorPos().x + wrapWidth);
		TextWrapped(text.c_str());
		//PopTextWrapPos();

		EndChild();
		PopStyleVar();
		Dummy(ImVec2(0, GetStyle().ItemSpacing.y));
	}
}
