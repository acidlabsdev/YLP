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


namespace YLP
{
	class PathWatcher
	{
	public:
		enum class ePathStatus : uint8_t
		{
			Created,
			Modified,
			Erased
		};

		using WatchCallback = std::function<void(const fs::path&, ePathStatus)>;
		PathWatcher() = default;

		explicit PathWatcher(fs::path root, std::chrono::duration<int, std::milli> pollInterval, const std::vector<std::string>& ignoreList = {}) :
		    m_Root(std::move(root)),
		    m_PollInterval(pollInterval)
		{
			if (!IO::Exists(m_Root))
				return;

			std::error_code ec;
			if (IO::IsFile(m_Root))
			{
				m_Snapshot[m_Root] = fs::last_write_time(m_Root, ec);
			}
			else if (IO::IsDir(m_Root))
			{
				for (const auto& entry : fs::recursive_directory_iterator(m_Root))
				{
					if (std::find(ignoreList.begin(), ignoreList.end(), entry.path().filename().string()) != ignoreList.end())
					{
						LOG_DEBUG("Ignored path {}", entry.path().filename().string());
						continue;
					}

					m_Snapshot[entry.path()] = fs::last_write_time(entry, ec);
				}
			}
		}

		~PathWatcher()
		{
			Stop();
		}

		void PollOnce(const WatchCallback& callback)
		{
			auto now = std::chrono::steady_clock::now();
			if (now - m_LastPollTime < m_PollInterval)
				return;

			if (IO::Exists(m_Root))
			{
				if (IO::IsFile(m_Root))
					HandleWriteTime(m_Root, callback);
				else if (IO::IsDir(m_Root))
				{
					for (const auto& entry : fs::recursive_directory_iterator(m_Root))
						HandleWriteTime(entry.path(), callback);
				}
			}

			for (auto it = m_Snapshot.begin(); it != m_Snapshot.end();)
			{
				if (!IO::Exists(it->first))
				{
					callback(it->first, ePathStatus::Erased);
					it = m_Snapshot.erase(it);
				}
				else
					++it;
			}
			m_LastPollTime = now;
		}

		void PollContinuous(const WatchCallback& callback, std::chrono::milliseconds delay = 1ms)
		{
			if (m_IsRunning)
				return;

			m_IsRunning = true;
			ThreadManager::RunDelayed([this, callback]() {
				while (m_IsRunning)
				{
					PollOnce(callback);
					std::this_thread::sleep_for(m_PollInterval);
				}
			}, delay);
		}

		void Stop()
		{
			m_IsRunning = false;
		}

	private:
		fs::path m_Root{};

		std::chrono::milliseconds m_PollInterval{1s};
		std::chrono::steady_clock::time_point m_LastPollTime{};
		std::unordered_map<fs::path, fs::file_time_type> m_Snapshot{};

		bool m_IsRunning{false};

		void HandleWriteTime(const fs::path& _path, const WatchCallback& callback)
		{
			std::error_code ec;
			auto lwt = fs::last_write_time(_path, ec);
			if (m_Snapshot.find(_path) == m_Snapshot.end())
			{
				m_Snapshot[_path] = lwt;
				callback(_path, ePathStatus::Created);
			}
			else if (m_Snapshot[_path] != lwt)
			{
				m_Snapshot[_path] = lwt;
				callback(_path, ePathStatus::Modified);
			}
		}
	};
}
