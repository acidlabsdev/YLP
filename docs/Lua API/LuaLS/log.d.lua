---@meta

-- Provides functions to output text to console and log file.
---@class log
log = {}

-- info Logs an information message.
---@param ... any Any number of arguments of any type.
function log.(...) end

-- warning Logs a warning message.
---@param ... any Any number of arguments of any type.
function log.(...) end

-- debug Logs a debug message.
---@param ... any Any number of arguments of any type.
function log.(...) end

-- error Logs an error message.
---@param ... any Any number of arguments of any type.
function log.(...) end

-- finfo Logs a formatted information message. Arguments are the same as `string.format`
---@param msg string Message.
---@param ... any Optional format arguments.
function log.(msg, ...) end

-- fwarning Logs a formatted warning message. Arguments are the same as `string.format`
---@param msg string Message.
---@param ... any Optional format arguments.
function log.(msg, ...) end

-- fdebug Logs a formatted debug message. Arguments are the same as `string.format`
---@param msg string Message.
---@param ... any Optional format arguments.
function log.(msg, ...) end

-- ferror Logs a formatted error message. Arguments are the same as `string.format`
---@param msg string Message.
---@param ... any Optional format arguments.
function log.(msg, ...) end
