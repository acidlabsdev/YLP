---@meta

-- Provides functions to run tasks in YLP's thread.
---@class Task
Task = {}

-- Run
---@param callback function The callback to execute
function Task.(callback) end

-- RunDelayed Execute a callback after a delay
---@param delay integer Delay in milliseconds
---@param callback function The function to execute
function Task.(delay, callback) end

-- Sleep
---@param ms integer Sleep time in milliseconds
function Task.(ms) end

-- Yield
---@param ms integer? Optional yield time in milliseconds
function Task.(ms) end
