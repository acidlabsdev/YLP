---@meta

-- A process abstraction providing basic process interactions.
---@class Process
Process = {}

-- __call
---@param processName string 
function Process:(processName) end

-- IsRunning
---@return boolean 
function Process:() end

-- IsModuleLoaded
---@param moduleName string Name of the module. Example: `"kernelbase.dll"`
---@return boolean 
function Process:(moduleName) end

-- GetModuleSize
---@return integer 
function Process:() end

-- GetModuleBase
---@return integer -- The module's base address
function Process:() end

-- Update Updates the process object's internal state. This is useful because the `Process` class does not poll for status on its own.
function Process:() end

-- FindPattern
---@param pattern string IDA-style byte signature. Example: `"8B 88 C0 ?? ?? ?? 89 8F"`
---@param name string? Optional name of the pattern to scan. Purely for logging purposes.
---@param chunkSize integer? Optional memory chunk size. Defaults to 4096
---@return Pointer ptr A pointer at the found address or a null pointer if the scan fails. This is guaranteed to always return a Pointer object.
function Process:(pattern, name, chunkSize) end
