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

#include "scanner.hpp"
#include "core/YimMenu/yimmenu.hpp"


namespace YLP
{
	using OnProcessFoundCallback = std::function<void(ProcessScanner&)>;
	using namespace Memory;

	class ProcessMonitor
	{
	public:
		ProcessMonitor(const std::string& processName,
			uint8_t targetMonitorMode = 0,
		    std::chrono::milliseconds startDelay = 0ms,
		    OnProcessFoundCallback onFound = nullptr,
		    YimMenu& menu = g_YimV1);

		~ProcessMonitor();

		void Start(std::chrono::milliseconds delay = 1s);
		void Stop();
		bool IsRunning() const;
		bool IsProcessRunning() const;
		bool IsBattlEyeRunning() const;
		bool WaitForProcessStart(int timeoutMs = 10000);
		bool WaitForModuleLoad(const std::string& dllName, int timeoutMs);
		bool WaitForGameReady(int timeoutMs);
		bool AutoInject();
		bool OnPostInject();

		void CheckBE();

		uintptr_t GetBaseAddress() const
		{
			if (!m_Scanner)
				return 0;

			return m_Scanner->GetBaseAddress();
		}

		bool IsModuleLoaded(const std::string& name) const
		{
			if (!m_Scanner)
				return false;

			return m_Scanner->IsModuleLoaded(name);
		}

		bool IsHeWatchin() const
		{
			return m_HeBeWatchin.load();
		}

	private:
		void MonitorLoop();

		OnProcessFoundCallback m_OnFound;

		uint8_t m_MonitorMode;

		std::chrono::milliseconds m_CallbackDelay{0};
		std::chrono::system_clock::time_point m_LastBEcheckTime{};

		std::atomic<bool> m_Running{false};
		std::atomic<bool> m_Found{false};
		std::atomic<bool> m_HeBeWatchin{false};

		std::thread m_Thread;

		std::string m_ProcessName;

		std::unique_ptr<ProcessScanner> m_Scanner;
	
		std::mutex m_Mutex;

		YimMenu* m_Menu;
	};
}
