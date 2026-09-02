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
	enum class ImCalloutType : uint8_t
	{
		Note,
		Warning,
		Important
	};

	inline void InfoCallout(ImCalloutType type, const std::string& text, float wrapWidth = 0.0f)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (!window)
			return;

		ImVec4 accentColor;
		const char* label{};
		const char* icon{};

		switch (type)
		{
		case ImCalloutType::Note:
			accentColor = ImVec4(0.0f, 0.001f, 0.803f, 1.0f);
			label = "Note";
			icon = ICON_MD_MESSAGE;
			break;
		case ImCalloutType::Warning:
			accentColor = ImVec4(1.0f, 0.7568, 0.027f, 1.0f);
			label = "Warning";
			icon = ICON_MD_WARNING;
			break;
		case ImCalloutType::Important:
			accentColor = ImVec4(0.498f, 0.1f, 1.0f, 1.0f);
			label = "Important";
			icon = ICON_MD_PRIORITY_HIGH;
			break;
		}

		if (wrapWidth <= 0.0f)
			wrapWidth = ImGui::GetContentRegionAvail().x - 10.0f;

		ImDrawList* drawList = ImGui::GetWindowDrawList();
		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str(), nullptr, false, wrapWidth);
		float panelHeight = textSize.y + 30 + (ImGui::GetStyle().WindowPadding.y * 2);
		float barWidth = 5.0f;

		drawList->AddRectFilled(pos, ImVec2(pos.x + barWidth, pos.y + panelHeight), ImColor(accentColor));
		ImGui::SetCursorScreenPos(ImVec2(pos.x + barWidth, pos.y));
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.f);
		ImGui::SetNextWindowBgAlpha(0.1f);
		ImGui::BeginChild(("##panel_" + std::to_string(static_cast<int>(type)) + "_" + std::to_string(window->GetID(text.c_str()))).c_str(),
		    ImVec2(0, panelHeight),
		    ImGuiChildFlags_None,
		    ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_AlwaysUseWindowPadding);

		ImGui::PushFont(Fonts::Bold);
		ImGui::TextColored(accentColor, std::format("{} {}", icon, label).c_str());
		ImGui::PopFont();
		//ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + wrapWidth);
		ImGui::TextWrapped(text.c_str());
		//ImGui::PopTextWrapPos();

		ImGui::EndChild();
		ImGui::PopStyleVar();
		ImGui::Dummy(ImVec2(0, ImGui::GetStyle().ItemSpacing.y));
	}
}
