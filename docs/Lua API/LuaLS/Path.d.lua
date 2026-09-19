---@meta

-- A path object limited to the `/Plugins` folder
---@class Path
---@overload fun(path: string): Path
---@operator div(string): Path
Path = {}

---@return boolean 
function Path:Exists() end

---@return boolean 
function Path:IsFile() end

---@return boolean 
function Path:IsDir() end

---@return string 
function Path:GetFilename() end

---@return string ext The file extension including the leading dot. Ex: `.json`. Returns empty string for folders.
function Path:GetExtension() end

---@param subPath string 
---@return Path 
function Path:Join(subPath) end

---@param mode openmode? 
---@return file*? 
---@return string failReason An error message if the operation fails.
function Path:Open(mode) end

-- Recursive directory iterator.
---@return fun(): Path
function Path:IterDir() end

-- Calculates the file's SHA256 checksum. Throws if the path is not a file.
---@return string hash SHA256 checksum
function Path:Sha256Sum() end
