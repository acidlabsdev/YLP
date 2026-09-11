---@meta

-- ### YLP namespace
---@class YLP
YLP = {}

---@return string version The current YLP version.
function YLP.GetVersion() end

-- Registers a callback to be executed once when a process is first seen.
--
-- You can call `Task.Yield` and `Task.Sleep` in your callback function.
---@param processName string The name of the process
---@param callback fun(process: Process) The function to execute. YLP will pass a Process object to the function as an argument.
---@param delay integer? Optional delay in milliseconds
---@return boolean success Whether the registration was successful or not.
function YLP.RegisterProcessWatcher(processName, callback, delay) end

-- Injects a dynamic link library into a target process.
---@param dllPath string Path to the DLL file.
---@param processName string Name of the target process.
---@return boolean status Success or failure.
---@return string? failReason Optional error message if injection fails.
function YLP.InjectDll(dllPath, processName) end

-- Registers a function to be executed when YLP is shutting down.
---@param callback function The function to execute
function YLP.OnShutdown(callback) end
