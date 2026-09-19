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


#include "imgui_helpers.hpp"

namespace ImGui
{
	using namespace YLP;

	void SameLineIfAvail(float itemwidth, float region)
	{
		if (region <= 0.f)
			region = GetContentRegionAvail().x;

		SameLine();
		if (itemwidth >= GetContentRegionAvail().x)
			NewLine();
	}

	void ToolTip(const char* text, ImFont* font, bool delayed, float textWrapWidth)
	{
		if (Config().disableTooltips)
			return;

		ImGuiHoveredFlags flags = ImGuiHoveredFlags_AllowWhenDisabled;

		if (delayed)
			flags |= ImGuiHoveredFlags_DelayNormal;

		if (!IsItemHovered(flags))
			return;

		if (!font)
			font = Fonts::Regular;

		PushStyleVar(ImGuiStyleVar_WindowRounding, 8.f);
		SetNextWindowBgAlpha(0.848f);
		PushFont(font);
		BeginTooltip();
		PushTextWrapPos(textWrapWidth >= 0.f ? textWrapWidth : GetFontSize() * 25);
		Text(text);
		PopTextWrapPos();
		EndTooltip();
		PopFont();
		PopStyleVar();
	}

	void TooltipIcon(const char* icon, const char* text, ImFont* font)
	{
		if (Config().disableTooltips)
			return;

		SameLine();
		TextDisabled(icon);
		ToolTip(text, font, false);
	}

	void HelpMarker(const char* text, ImFont* font)
	{
		TooltipIcon(ICON_MS_HELP, text);
	}

	void WarningMarker(const char* text, ImFont* font)
	{
		ImGui::PushStyleColor(ImGuiCol_TextDisabled, ImVec4(0.5, 0.5, 0, 0.75));
		TooltipIcon(ICON_MS_WARNING, text);
		ImGui::PopStyleColor();
	}

	void ErrorMarker(const char* text, ImFont* font)
	{
		ImGui::PushStyleColor(ImGuiCol_TextDisabled, ImVec4(0.9, 0, 0, 0.75));
		TooltipIcon(ICON_MS_ERROR, text);
		ImGui::PopStyleColor();
	}

	void WarningMessage(const char* text)
	{
		PushFont(Fonts::Title);
		PushTextWrapPos(GetFontSize() * 35);
		TextColored(ImVec4(1.0f, 0.7568, 0.027f, 1.0f), ICON_MS_WARNING);
		SameLine();
		Text("Warning");
		PopFont();
		PopTextWrapPos();

		Dummy(ImVec2(0, 2.f));
		TextWrapped(text);
		Spacing();
	}

	void TitleText(const char* text, bool separator)
	{
		PushFont(Fonts::Title);
		if (separator)
			SeparatorText(text);
		else
			Text(text);
		PopFont();
	}

	ImButtonColorScheme MakeButtonColors(ImVec4 baseColor, float hoverFactor, float activeFactor)
	{
		auto Mul = [](ImVec4 c, float f) {
			return ImVec4(c.x * f, c.y * f, c.z * f, c.w);
		};

		ImButtonColorScheme s;
		s.Base   = baseColor;
		s.Hover  = Mul(baseColor, hoverFactor);
		s.Active = Mul(baseColor, activeFactor);
		return s;
	}

	bool ColoredButton(const char* label, ImVec4 baseColor, float hoverFactor, float activeFactor)
	{
		bool ret = false;
		ImButtonColorScheme scheme = MakeButtonColors(baseColor);

		PushStyleColor(ImGuiCol_Button, scheme.Base);
		PushStyleColor(ImGuiCol_ButtonHovered, scheme.Hover);
		PushStyleColor(ImGuiCol_ButtonActive, scheme.Active);
		ret = Button(label);
		PopStyleColor(3);

		return ret;
	}

	void ImageRounded(
	    ImTextureID texture_id,
	    float diameter,
	    const ImVec2& uv0,
	    const ImVec2& uv1,
	    const ImVec4& tint_col)
	{
		ImVec2 p_min = GetCursorScreenPos();
		ImVec2 p_max = ImVec2(p_min.x + diameter, p_min.y + diameter);
		GetWindowDrawList()->AddImageRounded(texture_id, p_min, p_max, uv0, uv1, GetColorU32(tint_col), diameter * 0.5f);
		Dummy(ImVec2(diameter, diameter));
	}

	void TextCentered(const char* text, ImFont* font, float availWidth)
	{
		if (!font)
			font = Fonts::Regular;

		PushFont(font);
		float windowWidth = availWidth ? availWidth : GetWindowSize().x;
		float textWidth   = CalcTextSize(text).x;
		float textPosX    = (windowWidth - textWidth) * 0.5f;
		SetCursorPosX(textPosX > 0 ? textPosX : 0);
		Text(text);
		PopFont();
	}

	bool SelectableLabel(const char* icon, bool selected)
	{
		BeginGroup();
		const ImVec2 framePadding = GetStyle().FramePadding;
		const ImVec2 cursorPos    = GetCursorPos();
		float frameHeight         = GetFrameHeight();
		bool clicked              = InvisibleButton(icon, ImVec2(frameHeight, frameHeight));
		bool hovered              = IsItemHovered();
		auto colIdx               = selected ? ImGuiCol_ButtonActive : (hovered ? ImGuiCol_ButtonHovered : (clicked ? ImGuiCol_Button : ImGuiCol_Text));

		if (hovered and IsMouseDown(0))
			colIdx = ImGuiCol_Button;

		SameLine();
		SetCursorPos(ImVec2(cursorPos.x + framePadding.x, cursorPos.y + framePadding.y));
		TextColored(GetStyleColorVec4(colIdx), icon);
		EndGroup();
		if (IsItemHovered())
			SetMouseCursor(ImGuiMouseCursor_Hand);

		return clicked;
	}

	void DrawKeyValue(const char* key,
	    const std::string& value,
	    bool copyable,
	    ImVec4 valueColor,
	    ImKVflags valueDrawFlags,
	    std::string optionalUrl)
	{
		TextUnformatted(key);
		auto valsize = CalcTextSize(value.c_str());
		auto offset  = GetContentRegionAvail().x - valsize.x - (copyable ? 40 : 5);
		if (offset > 0)
			SameLine(offset);
		else
			Indent();

		PushStyleColor(ImGuiCol_Text, valueColor);

		switch (valueDrawFlags)
		{
		case KVflagsHyperlink:
			TextLinkOpenURL(value.c_str(), optionalUrl.c_str());
			break;
		case KVflagsBullet:
			BulletText(value.c_str());
			break;
		default:
			TextUnformatted(value.c_str());
			break;
		}

		PopStyleColor();
		if (copyable)
		{
			SameLine();
			if (SmallButton(ICON_MS_FILE_COPY))
				SetClipboardText(value.c_str());
			ToolTip("Copy");
		}
		if (offset <= 0)
			Unindent();
	};

	ImFont* GetScaledFont()
	{
		return Renderer::GetWindowSize().x >= 1200 ? Fonts::Regular : Fonts::Small;
	}

	bool SearchBar(const char* label, char* searchBuffer, ImGuiInputTextFlags flags)
	{
		Utils::CharToLower(searchBuffer);
		PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(16, 8));
		bool out = InputTextWithHint("##SearchBox", ICON_MS_SEARCH, searchBuffer, sizeof(searchBuffer), flags);
		PopStyleVar();
		return out;
	}

	void DrawRotatingImage(ImDrawList* drawList, ImTextureID texture, ImVec2 centrePos, ImVec2 size, float angle)
	{
		const ImVec2 halfSize	= size * 0.5f;
		const ImVec2 corners[]	= {
		    {-halfSize.x, -halfSize.y},
		    {halfSize.x, -halfSize.y},
		    {halfSize.x, halfSize.y},
		    {-halfSize.x, halfSize.y}};

		const float cos = std::cos(angle);
		const float sin = std::sin(angle);

		ImVec2 rotated[4];
		for (int i = 0; i < 4; ++i)
		{
			rotated[i] = {
			    centrePos.x + corners[i].x * cos - corners[i].y * sin,
			    centrePos.y + corners[i].x * sin + corners[i].y * cos
			};
		}

		drawList->AddImageQuad(
		    texture,
		    rotated[0],
		    rotated[1],
		    rotated[2],
		    rotated[3],
		    {0, 0},
		    {1, 0},
		    {1, 1},
		    {0, 1});
	}

	float GetFrameWidth()
	{
		ImGuiContext& g = *GImGui;
		return g.FontSize + g.Style.FramePadding.x * 2.0f;
	}

	float GetFrameWidthWithSpacing()
	{
		ImGuiContext& g = *GImGui;
		return g.FontSize + g.Style.FramePadding.x * 2.0f + g.Style.ItemSpacing.x;
	}
}
