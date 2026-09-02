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

#include "theme.hpp"


namespace YLP::Frontend
{
	class ThemeManager : public Singleton<ThemeManager>
	{
		friend class Singleton<ThemeManager>;

	private:
		ThemeManager() = default;

		static ThemeManager& GetInstance()
		{
			static ThemeManager i{};
			return i;
		}

	public:
		~ThemeManager() = default;
		ThemeManager(const ThemeManager&) = delete;
		ThemeManager(ThemeManager&&) noexcept = delete;
		ThemeManager& operator=(const ThemeManager&) = delete;
		ThemeManager& operator=(ThemeManager&&) noexcept = delete;

		static bool ApplyTheme(std::string_view name)
		{
			return GetInstance().ApplyThemeImpl(name);
		}

		static void Init()
		{
			GetInstance().InitImpl();
		}

		static Theme* GetCurrentTheme()
		{
			return GetInstance().m_CurrentTheme;
		}

		static const std::unordered_map<std::string, Theme>& GetThemes()
		{
			return GetInstance().m_Themes;
		}

	private:
		std::unordered_map<std::string, Theme> m_Themes{};
		Theme* m_CurrentTheme{nullptr};
		bool m_IsReady{false};

		void InitImpl();
		void LoadJsonThemesImpl();
		void LoadThemesImpl();
		bool ApplyThemeImpl(std::string_view name);
	};
}