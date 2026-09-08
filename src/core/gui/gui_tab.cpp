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
#include "gui_tab.hpp"


namespace YLP
{
	GuiTab::GuiTab(eTabID id, std::string_view name, std::optional<std::string_view> hint) :
	    m_ID(id),
	    m_Name(name),
	    m_Hint(hint)
	{
		GUI::RegisterTab(this);
	}
}
