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
	enum ImSegmentedCtrlPos : uint8_t
	{
		ImSegmentedCtrlPos_Left,
		ImSegmentedCtrlPos_Center,
		ImSegmentedCtrlPos_Right,
	};

	inline bool SegmentedControl(int* current, std::vector<const char*> items, ImSegmentedCtrlPos anchorPos = ImSegmentedCtrlPos_Left)
	{
		PushID(&items);
		ImGuiStyle& style	 = GetStyle();
		ImDrawList* drawList = GetWindowDrawList();
		const float height	 = GetFrameHeight();
		const float rounding = style.FrameRounding;

		float width = 0.0f;
		for (const char* item : items)
			width += CalcTextSize(item).x + style.FramePadding.x * 2.0f;

		ImVec2 cursorPos = GetCursorScreenPos();
		ImVec2 size(width, height);
		ImVec2 startPos{};
		switch (anchorPos)
		{
		case ImSegmentedCtrlPos_Left:
			startPos = cursorPos;
			break;
		case ImSegmentedCtrlPos_Center:
			startPos = cursorPos + ImVec2((GetContentRegionAvail().x - size.x) * 0.5f, 0);
			break;
		case ImSegmentedCtrlPos_Right:
			startPos = GetCursorScreenPos() + ImVec2(GetContentRegionAvail().x - size.x, 0);
			break;
		default:
			startPos = cursorPos;
			break;
		}

		drawList->AddRectFilled(
		    startPos,
		    startPos + size,
		    GetColorU32(ImGuiCol_FrameBg),
		    rounding);

		float x   = startPos.x;
		int index = 0;

		for (const char* item : items)
		{
			float itemWidth = CalcTextSize(item).x + style.FramePadding.x * 2.0f;
			ImVec2 itemPos(x, startPos.y);
			ImVec2 itemSize(itemWidth, height);
			SetCursorScreenPos(itemPos);

			bool pressed = InvisibleButton(item, itemSize);
			bool hovered = IsItemHovered();
			bool selected = (*current == index);
			if (selected)
			{
				drawList->AddRectFilled(
				    itemPos,
				    itemPos + itemSize,
				    GetColorU32(ImGuiCol_ButtonActive),
				    rounding);
			}

			ImVec2 textSize = CalcTextSize(item);
			drawList->AddText(
			    itemPos + ImVec2((itemWidth - textSize.x) * 0.5f, (height - textSize.y) * 0.5f),
			    GetColorU32(selected || hovered ? ImGuiCol_Text : ImGuiCol_TextDisabled), 
				item);

			if (hovered && !selected)
				SetMouseCursor(ImGuiMouseCursor_Hand);

			if (pressed)
				*current = index;

			x += itemWidth;
			index++;
		}

		SetCursorScreenPos(startPos);
		Dummy(size);
		PopID();

		return true;
	}
}
