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


#include "gui.hpp"
#include "theme_mgr.hpp"
#include "notifier.hpp"
#include <core/memory/pointers.hpp>


namespace YLP
{
	using namespace Frontend;

	void GUI::InitImpl()
	{
		Fonts::Load(ImGui::GetIO());
		ThemeManager::Init();

		AddTabImpl(eTabID::TAB_MAIN, ICON_MD_HOME, &YimMenuUI::Draw, "Dashboard");
		AddTabImpl(eTabID::TAB_YIMMENU_LUA, ICON_MD_EXTENSION, &LuaScriptsUI::Draw, "YimMenu-Lua");
		AddTabImpl(eTabID::TAB_INJECTOR, ICON_MD_STORAGE, &InjectorUI::Draw, "Standalone Injector");

		/*
			TODO: Implement LuaJIT and allow power users to extend YLP however they like.
			This can be a powerful feature but I'm currently the only maintainer of this project 
			and I don't want to deal with the headache of potential risks that may arise from using arbitrary scripts.
		*/
		//AddTabImpl(eTabID::TAB_SCRIPTING, ICON_MD_CODE, &ScriptingUI::Draw "Scripting");

		AddTabImpl(eTabID::TAB_SETTINGS, ICON_MD_SETTINGS, DrawSettings, "Settings");
		AddTabImpl(eTabID::TAB_INFO, ICON_MD_INFO, DrawAboutSection, "About");

		eTabID lastTabIdx = eTabID::TAB_MAIN;
		if (Config().restoreLastTab)
		{
			lastTabIdx = static_cast<eTabID>(Config().lastTabIndex);
			if (lastTabIdx >= eTabID::__COUNT || lastTabIdx < eTabID::TAB_MAIN)
				lastTabIdx = eTabID::TAB_MAIN;
		}
		m_ActiveTab = m_Tabs[TabIDToIndex(lastTabIdx)].get();
	}

	void GUI::AddTabImpl(const eTabID& id, const std::string_view& name, GuiCallback&& callback, std::optional<std::string_view> hint)
	{
		size_t idx = TabIDToIndex(id);
		if (idx >= m_Tabs.size())
			return;

		if (m_Tabs[idx] != nullptr)
			LOG_ERROR("[GUI]: Duplicate tab ID {}", static_cast<int>(id));

		for (auto& t : m_Tabs)
			if (t && t->m_Name == name)
				LOG_ERROR("[GUI]: Duplicate tab name {}", name);

		m_Tabs[idx] = std::make_unique<Tab>(Tab{ id, name, std::move(callback), hint });
	}

	void GUI::OnTabSwitchImpl()
	{
		if (m_ActiveTab == m_NextTab)
		{
			m_IsTabSwitchInProgress = false;
			m_NextTab = nullptr;
			m_CallbackChildAlpha = 1.f;
			return;
		}

		const float fadeSpeed = 3.86f;
		auto& io = ImGui::GetIO();

		if (m_IsTabSwitchInProgress)
		{
			m_CallbackChildAlpha -= io.DeltaTime * fadeSpeed;
			if (m_CallbackChildAlpha <= 0.0f)
			{
				m_ActiveTab = m_NextTab;
				m_NextTab = nullptr;
				m_CallbackChildAlpha = 0.0f;
				m_IsTabSwitchInProgress = false;
			}
		}
		else if (m_CallbackChildAlpha < 1.0f)
		{
			m_CallbackChildAlpha += io.DeltaTime * fadeSpeed;
			if (m_CallbackChildAlpha > 1.0f)
				m_CallbackChildAlpha = 1.0f;
		}
	}

	void GUI::SetActiveTabImpl(const eTabID& id)
	{
		if (id < eTabID::TAB_MAIN || id >= eTabID::__COUNT)
			return;

		if (m_ActiveTab && m_ActiveTab->m_ID == id)
			return;

		auto* tab = m_Tabs[TabIDToIndex(id)].get();
		if (tab)
		{
			m_IsTabSwitchInProgress = true;
			m_NextTab = tab;
		}
	}

	void GUI::RefreshCurrentTabImpl()
	{
		if (!m_ActiveTab)
			return;

		m_NextTab = m_ActiveTab;
		m_ActiveTab = nullptr;
		m_IsTabSwitchInProgress = true;
	}

	void GUI::DrawImpl()
	{
		m_WindowSize = Renderer::GetWindowSize();
		ImGui::SetNextWindowSize(m_WindowSize, ImGuiCond_Always);
		ImGui::SetNextWindowPos(ImVec2(0.f, 0.f), ImGuiCond_Always);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::Begin(
		    "YLP",
		    nullptr,
		    ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoTitleBar);

		ImGui::PopStyleVar();
		ImGui::BeginDisabled(m_ShouldDisableUI);
		const float consoleChildHeight = std::min(m_WindowSize.y * 0.3f, 240.0f);
		float mainChildHeight = Config().internalConsole ? m_WindowSize.y - consoleChildHeight : ImGui::GetContentRegionAvail().y;
		ImGui::SetNextWindowBgAlpha(0.175f);
		ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, .1f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.0f, 8.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8.0f, 8.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(8.0f, 8.0f));
		ImGui::BeginChild("##sidebar", ImVec2(m_SidebarWidth, mainChildHeight), 
			ImGuiChildFlags_Borders, 
			ImGuiWindowFlags_AlwaysUseWindowPadding 
			| ImGuiWindowFlags_NoScrollbar);
		DrawSideBarImpl();
		ImGui::EndChild();
		ImGui::PopStyleVar(4);

		ImGui::SameLine();
		ImGui::BeginChild("##main", ImVec2(0, mainChildHeight), 0, ImGuiWindowFlags_AlwaysUseWindowPadding);
		DrawTopBarImpl();

		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, m_CallbackChildAlpha);
		ImGui::BeginChild("##main_scroll_region", ImVec2(0, 0), 0, ImGuiWindowFlags_NoBackground);
		if (m_ActiveTab && m_ActiveTab->m_Callback)
			m_ActiveTab->m_Callback();
		ImGui::EndChild();
		ImGui::PopStyleVar();

		ImGui::EndChild();

		DrawDebugConsoleImpl();
		ImGui::EndDisabled();

		OnTabSwitchImpl();
		Notifier::DrawToast();
		ImGui::End();
	}

	void GUI::DrawTopBarImpl()
	{
		auto version = YLPUpdater.GetLocalVersion();
		ImGui::PushFont(Fonts::Small);
		ImGui::TextDisabled("v%s", version.ToString().c_str());
		ImGui::PopFont();

		ImGuiStyle& style = ImGui::GetStyle();
		const bool isSnoozed = Notifier::IsSnoozed();
		const char* notifIcon = isSnoozed ? ICON_MD_NOTIFICATIONS_OFF : (Notifier::IsViewed() ? ICON_MD_NOTIFICATIONS : ICON_MD_NOTIFICATIONS_ACTIVE);
		ImVec4 notifColor = Notifier::IsViewed() ? style.Colors[ImGuiCol_Text] : style.Colors[ImGuiCol_CheckMark];
		ImGui::SetCursorPos(ImVec2(ImGui::GetContentRegionAvail().x - 10.f, 10.f));
		ImGui::TextColored(Notifier::IsOpen() ? style.Colors[ImGuiCol_ButtonActive] : notifColor, notifIcon);

		if (ImGui::IsItemHovered())
			ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

		if (ImGui::IsItemClicked())
			Notifier::Toggle();

		ImGui::PushStyleVar(ImGuiStyleVar_PopupBorderSize, 0.f);
		Notifier::Draw();
		ImGui::PopStyleVar();
		ImGui::Dummy(ImVec2(-1, 10));
	}

	void GUI::DrawSideBarImpl()
	{
		size_t tabCount = m_Tabs.size();
		if (tabCount == 0)
			return;

		const float frameH = ImGui::GetFrameHeight();
		static float padding = 8.0f;
		static float accentY = 0.0f;
		static float accentHeight = 0.0f;
		static float accentTargetY = 0.0f;
		static float accentTargetHeight = 0.0f;

		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::SetCursorPosY(60);
		ImGui::PushFont(Fonts::Title);
		float iconWidth = ImGui::CalcTextSize(ICON_MD_EXTENSION).x;
		float offsetX = (ImGui::GetContentRegionAvail().x - iconWidth) * 0.5f;
		for (size_t i = 0; i < tabCount; i++)
		{
			auto& tab = *m_Tabs[i];
			bool selected = (m_ActiveTab == &tab || m_NextTab == &tab);
			ImGui::SetCursorPosX(offsetX);
			if (ImGui::SelectableLabel(tab.m_Name.data(), selected))
			{
				m_IsTabSwitchInProgress = true;
				m_NextTab = &tab;
				Config().lastTabIndex = i;
			}
			auto tooltip = tab.m_Hint ? *tab.m_Hint : tab.m_Name;
			ImGui::ToolTip(tooltip.data());

			if (selected)
			{
				accentTargetY = ImGui::GetItemRectMin().y;
				accentTargetHeight = frameH;
			}

			ImGui::Dummy(ImVec2(0, padding));
		};
		ImGui::PopFont();

		ImDrawList* drawList = ImGui::GetWindowDrawList();
		const ImVec2 childMin = ImGui::GetWindowPos();
		const ImVec2 childMax = childMin + ImGui::GetWindowSize();
		const float accentWidth = 4.0f;
		float speed = ImGui::GetIO().DeltaTime * 12.0f;
		float accentPosX = childMax.x - accentWidth;
		accentY = ImLerp(accentY, accentTargetY, speed);
		accentHeight = ImLerp(accentHeight, accentTargetHeight, speed);
		ImVec2 accentMin(accentPosX, accentY);
		ImVec2 accentMax(accentPosX + accentWidth, accentY + accentHeight);
		drawList->AddRectFilled(
			accentMin, 
			accentMax, 
			ImGui::GetColorU32(ImGuiCol_ButtonActive), 
			style.FrameRounding
		);
	}

	void GUI::DrawDebugConsoleImpl()
	{
		if (!Config().internalConsole)
			return;

		ImGui::Spacing();
		if (ImGui::BeginChild("##console", ImVec2(0, 0), ImGuiChildFlags_Border))
		{
			auto& logEntries = Logger::Entries();
			ImGui::PushFont(Fonts::Small);
			ImGui::BeginDisabled(logEntries.empty());
			if (ImGui::Button(ICON_MD_CONTENT_COPY))
			{
				std::string text;
				for (const auto& e : Logger::Entries())
					text += "[" + e.timestamp + "] " + Logger::ToString(e.level) + " " + e.message + "\n";
				ImGui::SetClipboardText(text.c_str());
			}
			ImGui::ToolTip("Copy all log entries");

			ImGui::SameLine();
			if (ImGui::Button(ICON_MD_DELETE))
				Logger::Clear();
			ImGui::ToolTip("Clear all log entries");
			ImGui::EndDisabled();

			ImGui::SetNextWindowBgAlpha(1.f);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.01f, 0.01f, 0.01f, 1.0f));
			if (ImGui::BeginChild("##debug_output", ImVec2(0, 0), ImGuiChildFlags_Borders))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));
				ImGui::PushTextWrapPos(0.0f);

				for (int i = 0; i < logEntries.size(); ++i)
				{
					auto& entry = logEntries[i];
					ImVec4 color;

					switch (entry.level)
					{
					case Logger::eLogLevel::Info: color = ImVec4(0.7f, 0.7f, 0.7f, 1.f); break;
					case Logger::eLogLevel::Warn: color = ImVec4(1.f, 0.8f, 0.f, 1.f); break;
					case Logger::eLogLevel::Error: color = ImVec4(1.f, 0.3f, 0.3f, 1.f); break;
					case Logger::eLogLevel::Debug: color = ImVec4(0.5f, 0.8f, 1.f, 1.f); break;
					default: color = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
					}

					auto text = std::format("[{}] {}: {}\n", entry.timestamp, Logger::ToString(entry.level), entry.message);
					ImGui::PushStyleColor(ImGuiCol_Text, color);
					ImGui::PushID(i);
					ImGui::WrappedSelectable(text.c_str());
					ImGui::PopID();
					ImGui::PopStyleColor();
					ImGui::Spacing();

					ImGui::ToolTip("Right click to copy"); // was left click. gaslighting much?
					if (ImGui::IsItemHovered() && ImGui::IsItemClicked(ImGuiMouseButton_Right))
						ImGui::SetClipboardText(text.c_str());
				}

				ImGui::PopTextWrapPos();
				ImGui::PopStyleVar();

				if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
					ImGui::SetScrollHereY(1.0f);
			}
			ImGui::EndChild();
			ImGui::PopStyleColor();
			ImGui::PopFont();
		}
		ImGui::EndChild();
	}

	const char* style_names[] = {"Dark", "Light", "Classic"};
	const char* autoModes[] = {"None", "Legacy Only", "Enhanced Only", "Legacy & Enhanced"};

	static void SetTheme(int index)
	{
		switch (index)
		{
		case 0: ImGui::StyleColorsDark(); break;
		case 1: ImGui::StyleColorsLight(); break;
		case 2: ImGui::StyleColorsClassic(); break;
		default: ImGui::StyleColorsClassic();
		}	
	}

	static void DrawThemes()
	{
		ImVec2 previewSize(200, 220);
		Theme* currentTheme = ThemeManager::GetCurrentTheme();
		auto& themes = ThemeManager::GetThemes();
		std::string_view preview = currentTheme ? currentTheme->m_Name : "";
		for (auto& [name, theme] : themes)
		{
			if (ImGui::ThemePreview(theme, currentTheme == &theme, previewSize))
				ThemeManager::ApplyTheme(name);
			if (!theme.m_AuthorName.empty())
				ImGui::ToolTip(std::format("Theme by {}", theme.m_AuthorName).c_str());

			ImGui::SameLineIfAvail(previewSize.x);
		}
	}

	void GUI::DrawSettingsImpl()
	{
		auto& cfg = Config();
		ImGui::TitleText("General", true);
		auto updateState = YLPUpdater.GetState();
		ImGui::BeginDisabled(updateState == Updater::UpdateState::Error);
		switch (updateState)
		{
		case Updater::UpdateState::Idle:
		{
			if (ImGui::Button(ICON_MD_SYNC))
				YLPUpdater.Check();
			ImGui::SameLine();
			ImGui::Text("Check For Updates");
			break;
		}
		case Updater::UpdateState::Checking:
			ImGui::Spinner("Please Wait...");
			break;
		case Updater::UpdateState::Pending:
		{
			if (ImGui::Button(ICON_MD_DOWNLOAD))
				YLPUpdater.Download();
			ImGui::ToolTip("Update");
			ImGui::SameLine();
			ImGui::Text("A new version of YLP is out!");
			break;
		}
		case Updater::UpdateState::Downloading:
		{
			ImGui::ProgressBar(YLPUpdater.GetProgress(), ImVec2(160, 25));
			ImGui::SameLine();
			ImGui::Text("Downloading...");
			break;
		}
		}
		ImGui::EndDisabled();

		ImGui::Spacing();
		ImGui::Checkbox("Internal Debug Console", &cfg.internalConsole);
		ImGui::HelpMarker("Toggle the internal debug console at the bottom of the UI.");

		//ImGui::Checkbox("External Debug Console", &cfg.externalConsole);
		//ImGui::HelpMarker("Toggle the external debug console.");

		ImGui::Checkbox("Restore Last Tab", &cfg.restoreLastTab);
		ImGui::HelpMarker("Your last selected tab will be restored when the program starts.");

		ImGui::BeginDisabled(cfg.autoMonitorFlags == MonitorNone);
		ImGui::Checkbox("Auto-Exit", &cfg.autoExit);
		ImGui::HelpMarker("Automatically exit after injecting a dll. This only works if Auto-Inject is enabled for either YimMenu Legacy or V2 or both.");
		ImGui::EndDisabled();

		ImGui::Spacing();
		ImGui::TitleText("Themes", true);
		DrawThemes();
	}

	static void DrawHeaderAndText(const char* header, const char* text, std::initializer_list<const char*> bullets = {})
	{
		ImGui::PushFont(Fonts::Title);
		ImGui::Text(header);
		ImGui::PopFont();
		ImGui::Separator();
		ImGui::TextWrapped(text);
		if (bullets.size() > 0)
		{
			for (auto& c : bullets)
			{
				ImGui::Bullet();
				ImGui::TextWrapped(c);
			}
		}
		ImGui::Spacing();
	}

	void GUI::DrawAboutSection()
	{
		DrawHeaderAndText("About",
		    R"(
YLP (formerly YimLaunchpad) is a free and open-source companion application created by a member of the community, for the community.

The software and author are not affiliated, associated, or endorsed by any mod menu or third-party commercial tool.

YLP exists solely to enhance the player's experience through transparency and convenience.
)");

		ImGui::InfoCallout(ImGui::ImCalloutType::Important,
		    R"(YLP is provided "as is", without any warranty of any kind, express or implied.
The author shall not be held liable for any damages, data loss, or issues arising from the use or misuse of this software.
)");
		DrawHeaderAndText("Licenses and Acknowledgements",
		    R"(
YLP makes use of several open-source libraries and assets that are licensed under their respective terms.

Full license texts and credits are available in the Third-Party Licenses document in the source repository.
)");

		////////////////////////////////////////////////////////

		ImGui::NewLine();
		ImGui::TitleText("Useful Links", true);
		ImGui::Spacing();
		ImGui::TextLinkOpenURL("Source Code " ICON_MD_OPEN_IN_NEW, "https://github.com/xesdoog/YLP");
		ImGui::TextLinkOpenURL("Report a Bug " ICON_MD_OPEN_IN_NEW, "https://github.com/xesdoog/ylp/issues/new/choose");
		ImGui::TextLinkOpenURL("Start a Discussion " ICON_MD_OPEN_IN_NEW, "https://github.com/xesdoog/YLP/discussions/new/choose");
	}
}
