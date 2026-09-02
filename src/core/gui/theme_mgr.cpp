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


#include "theme_mgr.hpp"
#include "themes_default.hpp"


namespace YLP::Frontend
{
	void ThemeManager::InitImpl()
	{
		LoadThemesImpl();
		ImGui::StyleColorsDark();

		std::string name = Config().savedTheme.first;
		if (name.empty())
			name = "Catppuccin Mocha";

		ApplyTheme(name);
		m_IsReady = true;
	}

	void ThemeManager::LoadJsonThemesImpl()
	{
		const fs::path& jsonThemesPath = g_ProjectPath / "Themes";
		if (!fs::exists(jsonThemesPath))
		{
			fs::create_directory(jsonThemesPath);
			std::ofstream f(jsonThemesPath / "readme.txt");
			if (!f.is_open())
				return;

			f << "Visit https://github.com/xesdoog/YLP/blob/main/docs/themes/readme.md to read more about custom themes.";
			return;
		}

		for (const auto& entry : fs::directory_iterator(jsonThemesPath))
		{
			if (!entry.is_regular_file() || entry.path().extension() != ".json")
				continue;

			try
			{
				std::ifstream file(entry.path());
				if (!file.is_open())
					continue;

				json j;
				file >> j;
				const auto& name = j.value("name", "");
				if (name.empty())
					continue;

				Theme theme = j.get<Theme>();
				theme.m_FilePath = entry.path();
				m_Themes.emplace(theme.m_Name, std::move(theme));
			}
			catch (const std::exception& e)
			{
				LOG_WARN("Failed to load theme from {}: {}", entry.path().string(), e.what());
				continue;
			}
		}
	}

	void ThemeManager::LoadThemesImpl()
	{
		namespace fs = std::filesystem;
		using json = nlohmann::json;

		// PirateSoftware much?
		m_Themes.emplace("Nord", DefaultThemes::Nord());
		m_Themes.emplace("Catppuccin Mocha", DefaultThemes::CatppuccinMocha());
		m_Themes.emplace("Rose Quartz", DefaultThemes::RoseQuartz());
		m_Themes.emplace("Moonlight", DefaultThemes::Moonlight());
		m_Themes.emplace("CP2077", DefaultThemes::CP2077());
		m_Themes.emplace("Silverlight", DefaultThemes::Silverlight());
		m_Themes.emplace("Synthwave", DefaultThemes::Synthwave());
		m_Themes.emplace("Criminal Mastermind", DefaultThemes::CriminalMastermind());

		LoadJsonThemesImpl();
	}

	bool ThemeManager::ApplyThemeImpl(std::string_view name)
	{
		auto it = m_Themes.find(name.data());
		if (it == m_Themes.end())
			return false;

		Theme& theme = it->second;
		if (!theme.Apply())
			return false;

		auto& savedTheme = Config().savedTheme;
		savedTheme.first = theme.m_Name;
		savedTheme.second = theme.m_FilePath;
		m_CurrentTheme = &theme;
		return true;
	}
}