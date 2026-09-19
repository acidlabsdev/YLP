---@meta

-- Provides file system functions. Paths are limited to the `/Plugins` folder only.
---@class Filesystem
---@field Path Path The Path class.
Filesystem = {}

-- Returns the module's root path.
---@return Path 
function Filesystem.MyRoot() end

-- Recursive directory iterator.
---@param path Path 
---@return fun(): Path
function Filesystem.IterDir(path) end

---@param oldPath Path 
---@param newPath Path 
---@return boolean successOrFailure
---@return string failReason
function Filesystem.Rename(oldPath, newPath) end

---@param path Path 
---@return boolean successOrFailure
---@return string failReason
function Filesystem.Remove(path) end
