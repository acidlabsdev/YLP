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
	class LuaImGuiLib : public LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

	public:
		void Register(sol::state& L) override
		{
			/*@ylp.table ImGui
			* description: 
				A very basic API that exposes a few ImGui widgets.
			@*/
			auto imguiTable = L["ImGui"].get_or_create<sol::table>();

			/*@ylp.function ImGui.PushID
			* param id<integer>
			@*/
			imguiTable["PushID"] = [](int id) {
				ImGui::PushID(id);
			};

			/*@ylp.function ImGui.PopID
			*
			@*/
			imguiTable["PopID"] = []() {
				ImGui::PopID();
			};

			/*@ylp.function ImGui.Bullet
			* 
			@*/
			imguiTable["Bullet"] = []() {
				ImGui::Bullet();
			};

			/*@ylp.function ImGui.Text
			* param text<string> 
			@*/
			imguiTable["Text"] = [&](const std::string& fmt, sol::variadic_args args) {
				ImGui::Text(LuaStringFormat(L, fmt, args).c_str());
			};

			/*@ylp.function ImGui.TextDisabled
			* param text<string> 
			@*/
			imguiTable["TextDisabled"] = [&](const std::string& fmt, sol::variadic_args args) {
				ImGui::TextDisabled(LuaStringFormat(L, fmt, args).c_str());
			};

			/*@ylp.function ImGui.TextWrapped
			* param text<string> 
			@*/
			imguiTable["TextWrapped"] = [&](const std::string& fmt, sol::variadic_args args) {
				ImGui::TextWrapped(LuaStringFormat(L, fmt, args).c_str());
			};

			/*@ylp.function ImGui.TextUnformatted
			* param text<string> 
			@*/
			imguiTable["TextUnformatted"] = [](const std::string& text) {
				ImGui::TextUnformatted(text.c_str());
			};

			/*@ylp.function ImGui.BulletText
			* param text<string> 
			@*/
			imguiTable["BulletText"] = [&](const std::string& fmt, sol::variadic_args args) {
				ImGui::BulletText(LuaStringFormat(L, fmt, args).c_str());
			};

			/*@ylp.function ImGui.TextColored
			* param r<number> A number between `0.0` and `1.0` representing the `Red` component of the color.
			* param g<number> A number between `0.0` and `1.0` representing the `Green` component of the color.
			* param b<number> A number between `0.0` and `1.0` representing the `Blue` component of the color.
			* param a<number> A number between `0.0` and `1.0` representing the `Alpha` component of the color.
			* param text<string> 
			@*/
			imguiTable["TextColored"] = [&](float r, float g, float b, float a, const std::string& fmt, sol::variadic_args args) {
				ImGui::TextColored(ImVec4(r, g, b, a), LuaStringFormat(L, fmt, args).c_str());
			};

			/*@ylp.function ImGui.Button
			* param label<string> 
			* param sizeX<number?> Optional button width
			* param sizeY<number?> Optional button height
			* return boolean clicked
			@*/
			imguiTable["Button"] = [](const std::string& label, sol::optional<float> sizeX, sol::optional<float> sizeY) {
				return ImGui::Button(label.c_str(), ImVec2(sizeX.value_or(0.f), sizeY.value_or(0.f)));
			};

			/*@ylp.function ImGui.SmallButton
			* param label<string>
			* return boolean clicked
			@*/
			imguiTable["SmallButton"] = [](const std::string& label) {
				return ImGui::SmallButton(label.c_str());
			};

			/*@ylp.function ImGui.ArrowButton
			* param label<string> 
			* param direction<integer> [ImGuiDir](lua://ImGuiDir)
			* return boolean clicked
			@*/
			imguiTable["ArrowButton"] = [](const std::string& label, int direction) {
				return ImGui::ArrowButton(label.c_str(), static_cast<ImGuiDir>(direction));
			};

			/*@ylp.function ImGui.InvisibleButton
			* param label<string> 
			* param sizeX<number> Button width
			* param sizeY<number> Button height
			* return boolean clicked
			@*/
			imguiTable["InvisibleButton"] = [](const std::string& label, float sizeX, float sizeY) {
				return ImGui::InvisibleButton(label.c_str(), ImVec2(sizeX, sizeY));
			};

			/*@ylp.function ImGui.Checkbox
			* param label<string> 
			* param v<boolean>
			* return boolean value
			* return boolean clicked
			@*/
			imguiTable["Checkbox"] = [](const std::string& label, bool v) {
				bool value{v};
				bool clicked = ImGui::Checkbox(label.c_str(), &value);
				return std::make_tuple(value, clicked);
			};

			/*@ylp.function ImGui.RadioButton
			* param label<string> 
			* param active<boolean>
			* return boolean clicked
			@*/
			imguiTable["RadioButton"] = [](const std::string& label, bool active) {
				return ImGui::RadioButton(label.c_str(), active);
			};

			/*@ylp.function ImGui.RadioButton
			* param label<string> 
			* param v<integer> Current index
			* param vButton<integer> Index to change to
			* return integer newValue
			* return boolean clicked
			@*/
			imguiTable["RadioButton"] = [](const std::string& label, int v, int vButton) {
				bool ret{ImGui::RadioButton(label.c_str(), &v, vButton)};
				return std::make_tuple(v, ret);
			};

			/*@ylp.function ImGui.ProgressBar
			* param fraction<number> 
			* param sizeX<number?> Optional frame width
			* param sizeY<number?> Optional frame height
			* param overlayText<string?> Optional overlay text. Defaults to precentage.
			@*/
			imguiTable["ProgressBar"] = [](float fraction,
				sol::optional<float> sizeX,
				sol::optional<float> sizeY,
				sol::optional<std::string> overlay)
			{
				ImGui::ProgressBar(fraction, ImVec2(sizeX.value_or(0.f), sizeY.value_or(0.f)), overlay.value_or("").c_str());
			};

			/*@ylp.function ImGui.Combo
			* param label<string>
			* param currentItem<integer>
			* param itemsSeparatedByZeros<string> A string with items separated by null terminators. Ex: `"Item1\0Item2\0Item3"`
			* return integer currentItem
			* return boolean opened
			@*/
			imguiTable["Combo"] = [](const std::string& label, int currentItem, const std::string& itemsSeparatedByZeros)
			{
				bool clicked = ImGui::Combo(label.c_str(), &currentItem, itemsSeparatedByZeros.c_str());
				return std::make_tuple(currentItem, clicked);
			};

			/*@ylp.function ImGui.BeginCombo
			* param label<string> 
			* param preview<string> 
			* param flags<integer?> Optional [ImGuiComboFlags](lua://ImGuiComboFlags)
			* return boolean opened
			@*/
			imguiTable["BeginCombo"] = [](const std::string& label, const std::string& previewValue, sol::optional<int> flags)
			{
				return ImGui::BeginCombo(label.c_str(), previewValue.c_str(), static_cast<ImGuiComboFlags>(flags.value_or(0)));
			};

			/*@ylp.function ImGui.EndCombo
			* 
			@*/
			imguiTable["EndCombo"] = []() {
				ImGui::EndCombo();
			};

			/*@ylp.function ImGui.BeginChild
			* param name<string>
			* param sizeX<number?> Optional child width.
			* param sizeY<number?> Optional child height.
			* param childFlags<integer?> Optional [ImGuiChildFlags](lua://ImGuiChildFlags)
			* param windowFlags<integer?> Optional [ImGuiWindowFlags](lua://ImGuiWindowFlags)
			* return boolean visible
			@*/
			imguiTable["BeginChild"] = [](const std::string& name,
				sol::optional<float> sizeX,
				sol::optional<float> sizeY,
				sol::optional<int> childFlags,
				sol::optional<int> windowFlags)
			{
				return ImGui::BeginChild(name.c_str(),
					ImVec2(sizeX.value_or(0.f), sizeY.value_or(0.f)),
				    static_cast<ImGuiChildFlags>(childFlags.value_or(0)),
				    static_cast<ImGuiWindowFlags>(windowFlags.value_or(0))
				);
			};

			/*@ylp.function ImGui.EndChild
			* 
			@*/
			imguiTable["EndChild"] = []() {
				ImGui::EndChild();
			};

			// layout stuff

			/*@ylp.function ImGui.SameLine
			* param offsetX<number> Optional X position to start at. Defaults to `0`.
			* param spacing<number> Optional spacing after the previous item. Defaults to the current item spacing.
			@*/
			imguiTable["SameLine"] = [](sol::optional<float> offsetX, sol::optional<float> spacing) {
				ImGui::SameLine(offsetX.value_or(0), spacing.value_or(-1.0f));
			};

			/*@ylp.function ImGui.NewLine
			* 
			@*/
			imguiTable["NewLine"] = []() {
				ImGui::NewLine();
			};

			/*@ylp.function ImGui.Spacing
			* 
			@*/
			imguiTable["Spacing"] = []() {
				ImGui::Spacing();
			};

			/*@ylp.function ImGui.Separator
			* 
			@*/
			imguiTable["Separator"] = []() {
				ImGui::Separator();
			};

			/*@ylp.function ImGui.SeparatorEx
			* param flags<integer> [ImGuiSeparatorFlags](lua://ImGuiSeparatorFlags)
			* param thickness<number>
			@*/
			imguiTable["SeparatorEx"] = [](int flags, float thickness = 1.0f) {
				ImGui::SeparatorEx(static_cast<ImGuiSeparatorFlags>(flags), thickness);
			};

			/*@ylp.function ImGui.SeparatorEx
			* param flags<integer> [ImGuiSeparatorFlags](lua://ImGuiSeparatorFlags)
			* param thickness<number>
			@*/
			imguiTable["SeparatorText"] = [](const std::string& text) {
				ImGui::SeparatorText(text.c_str());
			};

			/*@ylp.function ImGui.Indent
			* param indentX<number?> Optional indentation width. Defaults to the current item spacing.
			@*/
			imguiTable["Indent"] = [](sol::optional<float> indentX) {
				ImGui::Indent(indentX.value_or(0.f));
			};

			/*@ylp.function ImGui.Unindent
			* param indentX<number?> Optional indentation width. Defaults to the current item spacing.
			@*/
			imguiTable["Unindent"] = [](sol::optional<float> indentX) {
				ImGui::Unindent(indentX.value_or(0.f));
			};

			/*@ylp.function ImGui.Dummy
			* param sizeX<number> Width of the dummy item.
			* param sizeY<number> Height of the dummy item.
			@*/
			imguiTable["Dummy"] = [](float sizeX, float sizeY) {
				ImGui::Dummy(ImVec2(sizeX, sizeY));
			};

			/*@ylp.function ImGui.SetCursorPos
			* param x<number> X position relative to the current window.
			* param y<number> Y position relative to the current window.
			@*/
			imguiTable["SetCursorPos"] = [](float x, float y) {
				ImGui::SetCursorPos(ImVec2(x, y));
			};

			/*@ylp.function ImGui.SetCursorPosX
			* param x<number> X position relative to the current window.
			@*/
			imguiTable["SetCursorPosX"] = [](float x) {
				ImGui::SetCursorPosX(x);
			};

			/*@ylp.function ImGui.SetCursorPosY
			* param y<number> Y position relative to the current window.
			@*/
			imguiTable["SetCursorPosY"] = [](float y) {
				ImGui::SetCursorPosY(y);
			};

			/*@ylp.function ImGui.GetCursorPos
			* return number x Current X position relative to the current window.
			* return number y Current Y position relative to the current window.
			@*/
			imguiTable["GetCursorPos"] = []() {
				const ImVec2 pos = ImGui::GetCursorPos();
				return std::make_tuple(pos.x, pos.y);
			};

			/*@ylp.function ImGui.GetCursorPosX
			* return number x Current X position relative to the current window.
			@*/
			imguiTable["GetCursorPosX"] = []() {
				return ImGui::GetCursorPosX();
			};

			/*@ylp.function ImGui.GetCursorPosY
			* return number y Current Y position relative to the current window.
			@*/
			imguiTable["GetCursorPosY"] = []() {
				return ImGui::GetCursorPosY();
			};

			/*@ylp.function ImGui.GetContentRegionAvail
			* return number x Available width in the current content region.
			* return number y Available height in the current content region.
			@*/
			imguiTable["GetContentRegionAvail"] = []() {
				const ImVec2 size = ImGui::GetContentRegionAvail();
				return std::make_tuple(size.x, size.y);
			};

			/*@ylp.function ImGui.GetWindowSize
			* return number x Current window width.
			* return number y Current window height.
			@*/
			imguiTable["GetWindowSize"] = []() {
				const ImVec2 size = ImGui::GetWindowSize();
				return std::make_tuple(size.x, size.y);
			};

			/*@ylp.function ImGui.GetWindowPos
			* return number x Current window X position.
			* return number y Current window Y position.
			@*/
			imguiTable["GetWindowPos"] = []() {
				const ImVec2 pos = ImGui::GetWindowPos();
				return std::make_tuple(pos.x, pos.y);
			};

			/*@ylp.function ImGui.SetNextItemWidth
			* param width<number> Width of the next item.
			@*/
			imguiTable["SetNextItemWidth"] = [](float width) {
				ImGui::SetNextItemWidth(width);
			};

			/*@ylp.function ImGui.PushItemWidth
			* param width<number> Width of subsequent items.
			@*/
			imguiTable["PushItemWidth"] = [](float width) {
				ImGui::PushItemWidth(width);
			};

			/*@ylp.function ImGui.PopItemWidth
			* 
			@*/
			imguiTable["PopItemWidth"] = []() {
				ImGui::PopItemWidth();
			};

			// style stuff

			/*@ylp.function ImGui.PushStyleVar
			* param styleVar<integer> [ImGuiStyleVar](lua://ImGuiStyleVar) index
			* param v<number> style value
			@*/
			imguiTable["PushStyleVar"] = [](int styleVar, float v) {
				ImGui::PushStyleVar(static_cast<ImGuiStyleVar>(styleVar), v);
			};

			/*@ylp.function ImGui.PushStyleVar
			* param styleVar<integer> [ImGuiStyleVar](lua://ImGuiStyleVar) index
			* param vX<number> x value
			* param vY<number> y value
			@*/
			imguiTable["PushStyleVar"] = [](int styleVar, float vX, float vY) {
				ImGui::PushStyleVar(static_cast<ImGuiStyleVar>(styleVar), ImVec2(vX, vY));
			};

			/*@ylp.function ImGui.PopStyleVar
			* param count<integer?> Count of pushed style variables to pop. Defaults to 1; Must match the number of pushed style vars.
			@*/
			imguiTable["PopStyleVar"] = [](sol::optional<int> count) {
				ImGui::PopStyleVar(std::max(count.value_or(1), 1));
			};

			/*@ylp.function ImGui.PushStyleColor
			* param colIdx<integer> [ImGuiCol](lua://ImGuiCol) index
			* param r<number> A number between `0.0` and `1.0` representing the `Red` component of the color.
			* param g<number> A number between `0.0` and `1.0` representing the `Green` component of the color.
			* param b<number> A number between `0.0` and `1.0` representing the `Blue` component of the color.
			* param a<number> A number between `0.0` and `1.0` representing the `Alpha` component of the color.
			@*/
			imguiTable["PushStyleColor"] = [](int colIdx, float r, float g, float b, float a) {
				ImGui::PushStyleColor(static_cast<ImGuiCol>(colIdx), ImVec4(r, g, b, a));
			};

			/*@ylp.function ImGui.PopStyleColor
			* param count<integer?> Count of pushed style colors to pop. Defaults to 1; Must match the number of pushed style cols.
			@*/
			imguiTable["PopStyleColor"] = [](sol::optional<int> count) {
				ImGui::PopStyleColor(std::max(count.value_or(1), 1));
			};

			/*@ylp.function ImGui.PopStyleColor
			* param cursorIdx<integer> [ImGuiMouseCursor](lua://ImGuiMouseCursor) index
			@*/
			imguiTable["SetMouseCursor"] = [](int cursorIdx) {
				ImGui::SetMouseCursor(static_cast<ImGuiMouseCursor>(cursorIdx));
			};
		}
	};

	LuaImGuiLib _LuaImGuiLib;
}
