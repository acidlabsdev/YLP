# HorseMenu Implementation Demo

A very basic example demonstrating how the Lua API can be used to extended YLP's mod and game support. In this instance, we're adding support for RDR2 and [HorseMenu](https://github.com/YimMenu/HorseMenu).

>[!Note]
> This code relies on other dependencies. To use or modify it, please download the full [HorseMenuImpl](./HorseMenuImpl/) plugin folder.

```Lua
local version         = YLP.GetVersion()
local isDebug         = YLP.IsDebug()
local requiredVersion = VersionInfo(2, 0, 1, 4)

if (not isDebug && version < requiredVersion) then
	log.ferror("This plugin requires YLP v%s or newer.", requiredVersion)
	YLP.UnloadThisModule()
	return
end

local ok, ICONS = pcall(require, "icons")
if not (ok && ICONS) then
	log.warning(
		"Could not locate icon definitions table. Please download the file from YLP's repository at 'https://github.com/xesdoog/YLP/tree/main/docs/Lua%20API/shared/icons.lua' and place it in the '/Plugins/shared' directory.")

	ICONS = setmetatable({}, { __index = function(...) return "" end })
end

local f         = string.format
local Pair      = require("includes.Pair")
local buttonBig = ImVec2(-1, 45)


local modPath       = Filesystem.MyRoot() / "Downloads" / "HorseMenu.dll"
local modFile       = require("includes.ModFile")
local modURL        = Pair("github.com", "/YimMenu/HorseMenu/releases/download/nightly/HorseMenu.dll")
local targetProcess = "RDR2.exe"
local HorseMenu     = modFile:new(modPath, modURL, targetProcess)


local dummyAutoInject  = false
local dummyAutoUpdate  = false
local dummyInjectDelay = 0

local function DrawDownload()
	local isDownloading = HorseMenu:GetState() == Enums.eModViewState.Downloading
	ImGui.BeginDisabled(isDownloading)
	if (ImGui.Button(f("%s Download", ICONS.ICON_MS_DOWNLOAD), buttonBig)) then
		Task.Run(function() HorseMenu:Download() end)
	end
	ImGui.EndDisabled()

	if (isDownloading) then
		ImGui.YLPSpinner()
		ImGui.SameLine()
		ImGui.Text("Please Wait...")
	end
end

YLP.RegisterGui(function()
	ImGui.TitleText("HorseMenu", true)

	if (not HorseMenu:Exists()) then
		DrawDownload()
		return
	end

	dummyAutoUpdate = ImGui.Checkbox("Auto-Update", dummyAutoUpdate)
	dummyAutoInject = ImGui.Checkbox("Auto-Inject", dummyAutoInject)

	if (dummyAutoInject) then
		ImGui.Text("Auto-Inject Delay")
		dummyInjectDelay = ImGui.SliderInt("ms", dummyInjectDelay, 0, 6e4)
		ImGui.HelpMarker("Time in milliseconds to wait for after finding the process before injecting the DLL.")
	end

	ImGui.Spacing()
	ImGui.BeginDisabled(dummyAutoInject)
	if (ImGui.Button(f("%s Inject", ICONS.ICON_MS_SYRINGE), buttonBig)) then
		Task.Run(function()
			if (not Process(targetProcess):IsRunning()) then
				log.fwarning("Process %s is not running.", targetProcess)
				return
			end

			YLP.InjectDll(modPath, targetProcess, false)
		end)
	end
	ImGui.EndDisabled()
end)

YLP.RegisterProcessWatcher(targetProcess, function(process)
	if not (dummyAutoInject && modPath:Exists()) then
		return
	end

	Task.Sleep(dummyInjectDelay)
	YLP.InjectDll(modPath, targetProcess, false)
end)
```

## Preview

[HorseMenuImpl](../../img/screenshots/lua_1.jpg)
