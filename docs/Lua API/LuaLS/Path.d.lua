---@meta

-- A path object limited to the `/Plugins` folder
---@class Path
---@operator (string): Path
Path = {}

-- __call
---@param path string 
function Path:(path) end

-- Exists
---@return boolean 
function Path:() end

-- IsFile
---@return boolean 
function Path:() end

-- IsDir
---@return boolean 
function Path:() end

-- GetFilename
---@return string 
function Path:() end

-- GetExtension
---@return string ext The file extension including the leading dot. Ex: `.json`. Returns empty string for folders.
function Path:() end

-- Join
---@param subPath string 
---@return Path 
function Path:(subPath) end

-- Open
---@param mode openmode? 
---@return file*? 
---@return string failReason An error message if the operation fails.
function Path:(mode) end

-- IterDir Recursive directory iterator.
---@return fun(): Path
function Path:() end

-- Sha256Sum Calculates the file's SHA256 checksum. Throws if the path is not a file.
---@return string hash SHA256 checksum
function Path:() end
