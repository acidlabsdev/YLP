---@meta

-- Provides file system functions. Paths are limited to the `/Plugins` folder only.
---@class Filesystem
---@field Path Path The Path class.
Filesystem = {}

-- MyRoot Returns the module's root path.
---@return Path 
function Filesystem.() end

-- IterDir Recursive directory iterator.
---@param path Path 
---@return fun(): Path
function Filesystem.(path) end

-- Rename
---@param oldPath Path 
---@param newPath Path 
---@return boolean successOrFailure
---@return string failReason
function Filesystem.(oldPath, newPath) end

-- Remove
---@param path Path 
---@return boolean successOrFailure
---@return string failReason
function Filesystem.(path) end
