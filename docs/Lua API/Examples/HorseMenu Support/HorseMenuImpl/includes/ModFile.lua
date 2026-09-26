Enums = Enums or {}

---@enum eModViewState
local eModViewState = {
	Idle          = 0,
	Error         = 1,
	Checking      = 2,
	Downloading   = 3,
	PendingUpdate = 4,
}; Enums.eModViewState = eModViewState


---@class ModFile
---@field private m_path Path
---@field private m_name string
---@field private m_checksum string SHA256
---@field private m_remote_url Pair<string, string> host, path
---@field private m_state eModViewState
---@field private m_target_exe string
---@field private m_download_progress number
local ModFile   = {}
ModFile.__index = ModFile

---@param savePath Path -- DLL file save path.
---@param remoteUrl Pair<string, string>
---@param targetExe string
---@param name? string Optional custom mod name. Defaults to the filename without the extension.
function ModFile:new(savePath, remoteUrl, targetExe, name)
	return setmetatable({
		m_path       = savePath,
		m_remote_url = remoteUrl,
		m_state      = eModViewState.Idle,
		m_target_exe = targetExe,
		m_name       = name or savePath:GetStem(),
	}, self)
end

---@return boolean
function ModFile:Exists()
	return self.m_path:Exists()
end

---@return eModViewState
function ModFile:GetState()
	return self.m_state
end

---@return string
function ModFile:GetName()
	return self.m_name
end

---@return string
function ModFile:GetTargetProcess()
	return self.m_target_exe
end

function ModFile:Download()
	if (self.m_state == eModViewState.Downloading) then
		return
	end

	self.m_state = eModViewState.Downloading
	local url    = self.m_remote_url
	if (not url) then
		log.error("This ModFile instance was incorrectly setup! Missing 'URL' parameter.")
		self.m_state = eModViewState.Error
		return
	end

	local filePath = self.m_path
	if (not filePath) then
		log.error("This ModFile instance was incorrectly setup! Missing 'save folder' parameter.")
		self.m_state = eModViewState.Error
		return
	end

	local parentDir = filePath:GetParent()
	if (not parentDir:Exists()) then
		parentDir:MakeDirs()
	end

	log.finfo("[%s]: Starting download...", self.m_name)
	local resp = HTTP.Get(url.first, url.second, {}, filePath)
	if (not resp.success) then
		log.ferror("[%s]: Download failed with HTTP status: %d", self.m_name, resp.status)
		self.m_state = eModViewState.Error
		return
	end

	local exists = filePath:Exists()
	self.m_state = exists ? eModViewState.Idle : eModViewState.Error

	if (exists) then
		log.finfo("[%s]: Donwload complete.", self.m_name)
	end
end

return ModFile