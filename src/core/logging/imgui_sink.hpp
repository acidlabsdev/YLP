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

#include <deque>

#include "log_sink.hpp"
#include "../../thirdparty/ImGuiColorTextEditor/TextEditor.h"


namespace YLP
{
	class ImGuiSink final : public ILogSink
	{
	public:
		void Init()
		{
			m_TextEditor.SetLanguage(&m_ConsoleDef);
			m_TextEditor.SetPalette(m_EditorPalette);
			m_TextEditor.SetReadOnlyEnabled(true);
			m_TextEditor.SetWordWrapEnabled(true);
			m_TextEditor.SetShowSpacesEnabled(false);
			m_TextEditor.SetShowTabsEnabled(false);
			m_TextEditor.SetShowLineNumbersEnabled(false);
			m_TextEditor.SetShowMatchingBrackets(false);
			m_TextEditor.SetShowWhitespacesEnabled(false);
			m_TextEditor.SetShowMiniMapEnabled(false);
			m_TextEditor.SetShowPanScrollIndicatorEnabled(false);
			m_TextEditor.SetShowScrollbarMiniMapEnabled(false);
		}

		void Write(const LogEntry& entry) override
		{
			std::scoped_lock lock(m_EntriesMutex);

			m_Entries.push_back(entry);
			if (m_Entries.size() > m_MaxEntries)
				m_Entries.pop_front();

			m_Dirty = true;
		}

		void Draw()
		{
			if (!m_TexEditortInitialized)
			{
				m_TexEditortInitialized = true;
				m_TextEditor.SetImGuiContext(ImGui::GetCurrentContext());
			}

			if (m_Dirty)
			{
				std::string text;
				{
					std::scoped_lock lock(m_EntriesMutex);
					for (const auto& entry : m_Entries)
					{
						if (!text.empty())
							text += '\n';

						text += FormatEntry(entry);
					}
					m_Dirty = false;
				}
				m_TextEditor.SetText(text);
				m_TextEditor.ScrollToLine(m_TextEditor.GetLineCount(), TextEditor::Scroll::alignBottom);
			}

			m_TextEditor.Render("##internalConsole");
		}

		const auto& GetEntries() const noexcept
		{
			return m_Entries;
		}

		std::string GetText()
		{
			return m_TextEditor.GetText();
		}

		void Clear()
		{
			std::scoped_lock lock(m_EntriesMutex);
			m_Entries.clear();
			m_Dirty = true;
		}

	private:
		std::deque<LogEntry> m_Entries;
		std::mutex m_EntriesMutex;
		size_t m_MaxEntries{100};

		TextEditor m_TextEditor{};
		bool m_TexEditortInitialized{false};
		bool m_Dirty{false};

		static inline const TextEditor::Palette m_EditorPalette = {{
		    IM_COL32(224, 224, 224, 255), // text
		    IM_COL32(197, 134, 192, 255), // keyword
		    IM_COL32(90, 179, 155, 255),  // declaration
		    IM_COL32(181, 206, 168, 255), // number
		    IM_COL32(206, 145, 120, 255), // string
		    IM_COL32(255, 255, 153, 255), // punctuation
		    IM_COL32(64, 192, 128, 255),  // preprocessor
		    IM_COL32(156, 220, 254, 255), // identifier
		    IM_COL32(79, 193, 255, 255),  // known identifier
		    IM_COL32(106, 153, 85, 255),  // comment
		    IM_COL32(5, 5, 5, 255),       // background
		    IM_COL32(224, 224, 224, 255), // cursor
		    IM_COL32(32, 96, 160, 255),   // selection
		    IM_COL32(80, 80, 80, 255),    // whitespace
		    IM_COL32(70, 70, 70, 255),    // matchingBracketBackground
		    IM_COL32(140, 140, 140, 255), // matchingBracketActive
		    IM_COL32(80, 220, 120, 255),  // matchingBracketLevel1
		    IM_COL32(90, 160, 255, 255),  // matchingBracketLevel2
		    IM_COL32(255, 210, 70, 255),  // matchingBracketLevel3
		    IM_COL32(255, 90, 90, 255),   // matchingBracketError
		    IM_COL32(128, 128, 144, 255), // line number
		    IM_COL32(224, 224, 240, 255), // current line number
		}};

		static inline const TextEditor::Language m_ConsoleDef = {
			.name = "ImGuiSink",
			.customTokenizer = [](TextEditor::Iterator start, TextEditor::Iterator end, TextEditor::Color& color) {
			    if (start == end || *start != '[')
				    return start;

			    auto it = start;

			    if (it == end || *it != '[')
				    return start;

			    ++it;

			    while (it != end && *it != ']')
				    ++it;

			    if (it == end)
				    return start;

			    ++it;
			    TextEditor::Color logColor = TextEditor::Color::string;
			    while (it != end && *it == ' ')
			    {
				    ++it;
				    if (it == end || *it != '[')
					    break;

				    auto fieldStart = it;
				    ++it;

				    auto contentStart = it;
				    while (it != end && *it != ']')
					    ++it;

				    if (it == end)
					    return start;

				    auto contentEnd = it;
				    std::string field(contentStart, contentEnd);
				    if (field == "INFO")
					    logColor = TextEditor::Color::matchingBracketLevel1;
				    else if (field == "DEBUG")
					    logColor = TextEditor::Color::matchingBracketLevel2;
				    else if (field == "WARN")
					    logColor = TextEditor::Color::matchingBracketLevel3;
				    else if (field == "ERROR")
					    logColor = TextEditor::Color::matchingBracketError;

				    ++it;
			    }

			    if (logColor == TextEditor::Color::string)
				    return start;

			    color = logColor;
			    return it;
			}
		};
	};
}
