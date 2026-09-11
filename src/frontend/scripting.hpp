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

#include "core/gui/gui_tab.hpp"
#include "core/lua_scripting/lua_mgr.hpp"
#include "thirdparty/ImGuiColorTextEditor/TextEditor.h"


namespace YLP::Frontend
{
	using namespace YLP;

	class ScriptingTab final : public GuiTab
	{
	public:
		ScriptingTab() :
		    GuiTab(eTabID::TAB_SCRIPTING, ICON_MS_CODE, "LuaJIT scripting")
		{
		}

		void Draw() override
		{
			if (!Config().enableScripting)
			{
				ImGui::TextCentered("Currently Unavailable", Fonts::Title);
				ImGui::Dummy(ImVec2(0, 20));
				ImGui::Text("The scripting feature is disabled. You can enable it in the Settings tab.");
				return;
			}

			if (!m_EditorInitialized)
			{
				m_Editor.SetLanguage(TextEditor::Language::Lua());
				m_Editor.SetPalette(TextEditor::GetDarkPalette());
				m_Editor.SetTabSize(4);
				m_Editor.SetAutoIndentEnabled(true);
				m_Editor.SetCompletePairedGlyphs(true);
				m_Editor.SetWordWrapEnabled(true);
				m_Editor.SetImGuiContext(ImGui::GetCurrentContext());
				m_Editor.SetShowSpacesEnabled(false);
				m_EditorInitialized = true;
			}

			ImGuiWindowFlags defaultFlags = 2052;
			m_Editor.Render("##luaEditor", ImVec2(0.0f, ImGui::GetContentRegionAvail().y - 60.0f), 0, defaultFlags | ImGuiWindowFlags_AlwaysUseWindowPadding);
			ImGui::Dummy(ImVec2(0, 5));
			ImGui::Separator();

			ImGui::BeginDisabled(m_Editor.IsEmpty());
			if (ImGui::Button(ICON_MS_TERMINAL " Execute"))
				LuaJIT::LuaManager::ExecuteCode(m_Editor.GetText().data());

			ImGui::SameLine();
			if (ImGui::Button(ICON_MS_BACKSPACE " Clear"))
				m_Editor.ClearText();
			ImGui::EndDisabled();
		}
	private:
		static inline std::shared_ptr<LuaJIT::LuaModule> selectedModule{nullptr};
		static inline std::string selectedDisabledModule{};
		static inline bool m_EditorInitialized{false};
		static inline TextEditor m_Editor;
	};

	inline ScriptingTab _ScriptingTab;
}
