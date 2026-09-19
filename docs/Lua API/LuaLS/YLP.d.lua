---@meta

-- ### YLP namespace
---@class YLP
YLP = {}

-- GetVersion
---@return string version The current YLP version.
function YLP.() end

-- RegisterProcessWatcher Registers a callback to be executed once when a process is first seen.
--
-- You can call `Task.Yield` and `Task.Sleep` in your callback function.
---@param processName string The name of the process
---@param callback fun(process: Process) The function to execute. YLP will pass a Process object to the function as an argument.
---@param delay integer? Optional delay in milliseconds
---@return boolean success Whether the registration was successful or not.
function YLP.(processName, callback, delay) end

-- RegisterGui Registers an ImGui callback to be drawn in the 'Lua Scripting' tab.
---@param callback function The UI to draw. ImGui functions can only be called here.
function YLP.(callback) end

-- InjectDll Injects a dynamic link library into a target process.
---@param dllPath Path DLL file path. Must be a [Path](lua://Path) object.
---@param processName string Name of the target process.
---@param manualMap boolean? Use manual mapping instead of standard `LoadLibrary`
---@param manualMapArgs { eraseHeaders: boolean?, enableSEH: boolean?, randomizeBaseAddress: boolean?}? Optional manual mapping configuration.
---@return boolean status Success or failure.
---@return string? failReason Optional error message if injection fails.
function YLP.(dllPath, processName, manualMap, manualMapArgs) end

-- OnShutdown Registers a function to be executed when YLP is shutting down.
---@param callback function The function to execute
function YLP.(callback) end

-- UnloadThisModule Unloads the caller module.
--
-- The module can only be loaded again from the Settings tab in YLP's UI.
function YLP.() end
