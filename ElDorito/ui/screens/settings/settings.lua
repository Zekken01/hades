-- Port of screens/settings/settings.js

local activePage
local selectedItem
local itemNumber = 0
local tabIndex = 0
local changeArray = {}
local commandValues = {}
local hasGP = false
local playSound = true
local preventCancel = false
local lodWarned = false
local rightclickKeybind = false
local hiding = false
local mapName = "mainmenu"
local lastSoundPlayedTime = 0

-- KI values
local KI_ESCAPE, KI_OEM_3, KI_OEM_8, KI_SNAPSHOT = 81, 44, 49, 97

local settingsToLoad = {
	{ "sControlsMethod", "Settings.Gamepad" },
	{ "sInfantryMouseSensV", "Settings.MouseSensitivityVertical" },
	{ "sInfantryMouseSensH", "Settings.MouseSensitivityHorizontal" },
	{ "sVehicleMouseSensV", "Settings.MouseSensitivityVehicleVertical" },
	{ "sVehicleMouseSensH", "Settings.MouseSensitivityVehicleHorizontal" },
	{ "sMouseAcceleration", "Settings.MouseAcceleration" },
	{ "sInvertMouse", "Settings.InvertMouse" },
	{ "sToggleCrouch", "Settings.ToggleCrouch" },
	{ "sScreenResolution", "Settings.ScreenResolution" },
	{ "sBrightness", "Settings.Brightness" },
	{ "sFullscreen", "Settings.Fullscreen" },
	{ "sVsync", "Settings.VSync" },
	{ "sAntiAliasing", "Settings.Antialiasing" },
	{ "sAnisotropicFiltering", "Settings.AnisotropicFiltering" },
	{ "sTextureResolution", "Settings.TextureResolution" },
	{ "sTextureFiltering", "Settings.TextureFilteringQuality" },
	{ "sLightningQuality", "Settings.LightingQuality" },
	{ "sEffectsQuality", "Settings.EffectsQuality" },
	{ "sShadowQuality", "Settings.ShadowQuality" },
	{ "sShadowResolution", "Settings.ShadowResolution" },
	{ "sDetailsLevel", "Settings.DetailsQuality" },
	{ "sPostprocessing", "Settings.PostprocessingQuality" },
	{ "sMotionBlur", "Settings.MotionBlur" },
	{ "sReflections", "Graphics.ReflectionsEnabled" },
	{ "sMasterVolume", "Settings.MasterVolume" },
	{ "sSFXVolume", "Settings.SfxVolume" },
	{ "sMusicVolume", "Settings.InGameMusicVolume" },
	{ "sMainMenuMusicVolume", "Settings.MainMenuMusicVolume" },
	{ "sHudShake", "Settings.HUDShake" },
	{ "sPlayerMarkerColors", "Settings.PlayerMarkerColors" },
	{ "sCameraFOV", "Camera.FOV" },
	{ "sVehiCameraFOV", "Camera.VehicleFOV" },
	{ "cCenteredCrosshairFirst", "Camera.CenteredCrosshairFirst" },
	{ "cCenteredCrosshairThird", "Camera.CenteredCrosshairThird" },
	{ "cHideHUD", "Camera.HideHUD" },
	{ "inputRaw", "Input.RawInput" },
	{ "aimingType", "Input.ControllerAimControl" },
	{ "axialDeadzone", "Input.ControllerAxialDeadzone" },
	{ "radialDeadzone", "Input.ControllerRadialDeadzone" },
	{ "lookSensitivity", "Input.ControllerSensitivityY" },
	{ "controllerPort", "Input.ControllerPort" },
	{ "gExpandScoreboard", "Game.ExpandedScoreboard" },
	{ "invertLook", "Input.ControllerInvertY" },
	{ "gHideChat", "Game.HideChat" },
	{ "gSuppressJuggling", "Game.SuppressJuggling" },
	{ "wOffsetConfig", "Weapon.JSON.File" },
	{ "iSpectateSens", "Input.SpectateSensitivity" },
	{ "iDisableSprint", "Input.ToggleSprint" },
	{ "vEnabled", "VoIP.Enabled" },
	{ "vMicrophoneID", "VoIP.MicrophoneID" },
	{ "vPTTEnable", "VoIP.PTT_Enabled" },
	{ "vAGC", "VoIP.AGC" },
	{ "vNoiseSupress", "VoIP.NoiseSupress" },
	{ "vEchoCancelation", "VoIP.EchoCancelation" },
	{ "vPTTSound", "VoIP.PTTSoundEnabled" },
	{ "vIncomingVolume", "VoIP.IncomingVolume" },
	{ "vOutgoingVolume", "VoIP.OutgoingVolume" },
	{ "vMaximumBitrate", "VoIP.MaximumBitrate" },
	{ "tDisableFog", "Tweaks.DisableReactorFog" },
	{ "tDisableWeapOutline", "Tweaks.DisableWeaponOutline" },
	{ "tDisableHitmarkers", "Tweaks.DisableHitMarkers" },
	{ "tGruntBirthdayParty", "Tweaks.GruntBirthdayParty" },
	{ "tReachFrags", "Tweaks.ReachStyleFrags" },
	{ "tExposureCpu", "Settings.ExposureCpu" },
	{ "sAudioDevice", "Settings.AudioOutputDevice" },
	{ "sContrast", "Settings.Contrast" },
	{ "controllerVibration", "Input.ControllerVibrationIntensity" },
	{ "stickLayout", "Input.ControllerStickLayout" },
	{ "xSens", "Input.ControllerSensitivityX" },
	{ "ySens", "Input.ControllerSensitivityY" },
	{ "sQualityPreset", "" },
	{ "presetMenu", "" },
	{ "gdEnabled", "Game.Discord.Enable" },
	{ "gdAutoAccept", "Game.Discord.AutoAccept" },
	{ "sMainmenuMod", "Game.MainMenuMod" },
	{ "sCampaignMod", "Game.CampaignMod" },
	{ "sFirefightMod", "Game.FirefightMod" },
	{ "sMultiplayerMod", "Game.MultiplayerMod" },
	{ "sGamma", "Graphics.Gamma" },
	{ "sMotionBlurStrength", "Settings.MotionBlurStrength" },
	{ "sMotionBlurAlways", "Settings.MotionBlurAlways" },
	{ "sCenteredHudScaling", "Graphics.CenteredHUD" },
	{ "sSkipTitleSplash", "Game.SkipTitleSplash" },
	{ "sSSAOEnabled", "Settings.SSAO" },
	{ "sDecoratorDistance", "Settings.DecoratorDistance" },
	{ "sLODDistance", "Settings.LODDistance" },
	{ "sChatMessageLimit", "Game.ChatMessageLimit" },
	{ "sSubtitlesDisplay", "Settings.Subtitles" },
	{ "sHoFpAnimations", "Settings.FirstPersonJumpAndLand" },
}

local binds = {
	{ "Sprint", "Sprint", "Infantry" }, { "Jump", "Jump", "Infantry" }, { "Crouch", "Crouch", "Infantry" },
	{ "Use", "Use", "Infantry" }, { "DualWield", "Dual Wield", "Infantry" }, { "Fire", "Fire", "Infantry" },
	{ "FireLeft", "Fire Dual", "Infantry" }, { "Reload", "Reload", "Infantry" }, { "ReloadLeft", "Reload Dual", "Infantry" },
	{ "Zoom", "Zoom", "Infantry" }, { "SwitchWeapons", "Switch Weapons", "Infantry" }, { "Melee", "Melee", "Infantry" },
	{ "Grenade", "Grenade", "Infantry" }, { "SwitchGrenades", "Switch Grenades", "Infantry" },
	{ "VehicleAccelerate", "Vehicle Accelerate", "Vehicle" }, { "VehicleBrake", "Vehicle Brake", "Vehicle" },
	{ "VehicleBoost", "Vehicle Boost", "Vehicle" }, { "VehicleRaise", "Vehicle Raise", "Vehicle" },
	{ "VehicleDive", "Vehicle Dive", "Vehicle" }, { "VehicleFire", "Vehicle Fire", "Vehicle" },
	{ "VehicleAltFire", "Vehicle Alt Fire", "Vehicle" }, { "BansheeBomb", "Banshee Bomb", "Vehicle" },
	{ "Menu", "Menu", "UI" }, { "Scoreboard", "Scoreboard", "UI" }, { "Chat", "Chat", "UI" },
	{ "TeamChat", "Team Chat", "UI" }, { "Emote", "Emote", "UI" }, { "UseEquipment", "Use Equipment", "Infantry" },
	{ "VoiceChat", "Voice Chat PTT", "UI" }, { "Flashlight", "Toggle Flashlight", "Infantry" },
	{ "Forward", "Forward", "Infantry" }, { "Back", "Back", "Infantry" }, { "Left", "Left", "Infantry" },
	{ "Right", "Right", "Infantry" }, { "NextPlayer", "Spectate Next Player", "UI" },
	{ "PrevPlayer", "Spectate Prev Player", "UI" }, { "UiLeftBumper", "UiLeftBumper", "UI" },
	{ "UiRightBumper", "UiRightBumper", "UI" },
}
local CONTROLLER_BINDS = #binds - 8 -- the controller actions (binds.length - 8)

local buttons = { "", "A", "B", "X", "Y", "RB", "LB", "LT", "RT", "Start", "Back", "LS", "RS", "Left", "Right", "Up", "Down" }

local controllerPresets = {
	{ "Halo Online Default", "LS,A,X,RB,LB,RT,LT,RB,LB,RS,Y,B,LT,Right,,,A,A,X,RT,LT,B,Start,Back,,,Left,Down,Up,Up" },
	{ "Halo 3 Default", "Right,A,LS,RB,LB,RT,LT,RB,LB,RS,Y,B,LT,LB,,,LT,A,LS,RT,LT,B,Start,Back,,,Left,X,Up,Up" },
	{ "Halo 3 Southpaw", "Right,A,LS,RB,LB,LT,RT,RB,LB,RS,Y,B,RT,LB,,,RT,A,LS,LT,RT,B,Start,Back,,,Left,X,Up,Up" },
	{ "Halo 3 Boxer", "Right,A,LS,RB,LB,RT,LT,RB,LB,RS,Y,LT,B,LB,,,LT,A,LS,RT,LT,B,Start,Back,,,Left,X,Up,Up" },
	{ "Halo 3 Green Thumb", "Right,A,LS,RB,LB,RT,LT,RB,LB,B,Y,RS,LT,LB,,,LT,A,LS,RT,LT,B,Start,Back,,,Left,X,Up,Up" },
	{ "Halo 3 Bumper Jumper", "Right,LB,LS,B,A,RT,LT,B,A,RS,Y,RB,LT,A,,,LT,LB,LS,RT,LT,RB,Start,Back,,,Left,X,Up,Up" },
	{ "Halo 3 Walkie Talkie", "Right,A,LS,B,X,RT,LT,B,X,RS,Y,RB,LT,X,,,LT,A,LS,RT,LT,B,Start,Back,,,Left,Up,LB,Down" },
	{ "Halo Reach Default", "LB,A,LS,X,B,RT,LT,X,LB,RS,Y,RB,LT,B,,,LT,A,LS,RT,LT,B,Start,Back,,,Left,Down,Up,Up" },
	{ "Halo Reach Southpaw", "RB,A,LS,X,B,LT,RT,X,RB,RS,Y,LB,RT,B,,,RT,A,LS,LT,RT,B,Start,Back,,,Left,Down,Up,Up" },
	{ "Halo Reach Boxer", "LB,A,LS,X,B,RT,LT,X,LB,RS,Y,LT,RB,B,,,LT,A,LS,RT,LT,B,Start,Back,,,Left,Down,Up,Up" },
	{ "Halo Reach Green Thumb", "LB,A,LS,X,B,RT,LT,X,LB,RB,Y,RS,LT,B,,,LT,A,LS,RT,LT,B,Start,Back,,,Left,Down,Up,Up" },
	{ "Halo Reach Bumper Jumper", "X,LB,LS,B,A,RT,LT,B,A,RS,Y,RB,LT,A,,,LT,LB,LS,RT,LT,RB,Start,Back,,,Left,Down,Up,Up" },
	{ "Halo Reach Recon", "LB,A,LS,RB,X,RT,LT,RB,LB,RS,Y,B,LT,X,,,LT,A,LS,RT,LT,B,Start,Back,,,Left,Down,Up,Up" },
	{ "Halo 4 Default", "LS,A,B,X,LB,RT,LT,X,LB,RS,Y,RB,LT,Right,,,LT,A,B,RT,LT,RB,Start,Back,,,Left,Down,Up,Up" },
	{ "Halo 4 Southpaw", "LS,A,B,X,RB,LT,RT,X,RB,RS,Y,LB,RT,Right,,,RT,A,B,LT,RT,LB,Start,Back,,,Left,Down,Up,Up" },
	{ "Halo 4 Boxer", "B,A,LS,X,LB,RT,LT,X,LB,RS,Y,LT,RB,Right,,,LT,A,LS,RT,LT,B,Start,Back,,,Left,Down,Up,Up" },
	{ "Halo 4 Green Thumb", "LS,A,B,X,LB,RT,LT,X,LB,RB,Y,RS,LT,Right,,,LT,A,B,RT,LT,RB,Start,Back,,,Left,Down,Up,Up" },
	{ "Halo 4 Bumper Jumper", "A,LB,LS,B,X,RT,LT,B,X,RS,Y,RB,LT,Right,,,LT,LB,LS,RT,LT,RB,Start,Back,,,Left,Down,Up,Up" },
	{ "Halo 4 Recon", "X,A,LS,RB,LB,RT,LT,RB,LB,RS,Y,B,LT,Right,,,LT,A,LS,RT,LT,B,Start,Back,,,Left,Down,Up,Up" },
	{ "Halo 4 Fishstick", "LS,A,B,X,LB,RT,LT,X,LB,LT,Y,RS,RB,Right,,,LT,A,B,RT,LT,RS,Start,Back,,,Left,Down,Up,Up" },
}
local bindChangeArray = {}
local subPages = { ["#page4"] = true, ["#page5"] = true, ["#page8"] = true, ["#page9"] = true, ["#page11"] = true }

local function el(id) return document:GetElementById(id) end
local function nowMs() return dew_core.getTime() * 1000 end

local function split(text, separator)
	local parts = {}
	for part in (tostring(text) .. separator):gmatch("(.-)" .. separator:gsub("%p", "%%%0")) do
		parts[#parts + 1] = part
	end
	return parts
end

local function decode(text)
	local ok, value = pcall(json.decode, text)
	if ok then return value end
	return nil
end

------------------------------------------------------------------------------------------
-- controls: select / range / text / toggle behind one value API

-- jQuery's .val()/.prop() fired no change events, but RmlUi raises "change" for values set
-- from script (at once and again on the next update): remember what the page wrote.
local written = {}
-- New or rebuilt selects pick their first option and report it a few updates later: ignore
-- change events for a moment after load (all controls) and after a list rebuild (that one).
local settleAll = 0
local settleUntil = {}
local SETTLE_MS = 400

local function settling(id)
	local now = dew_core.getTime() * 1000
	return now < settleAll or now < (settleUntil[id] or 0)
end

local function kind(element)
	if not element then return nil end
	if element:IsClassSet("toggle") then return "toggle" end
	local tag = element.tag_name
	if tag == "select" then return "select" end
	if tag == "input" then
		return element:GetAttribute("type") == "range" and "range" or "text"
	end
	return tag
end

local function isChecked(id)
	local element = el(id)
	return element ~= nil and element:GetAttribute("data-state") == "1"
end

local function setChecked(id, checked)
	local element = el(id)
	if not element then return end
	element:SetAttribute("data-state", checked and "1" or "0")
	local enabled = checked
	if element:IsClassSet("inverted-checkbox") then
		enabled = not checked
	end
	element.inner_rml = enabled and "Enabled" or "Disabled"
end

local function value(id)
	local element = el(id)
	if not element then return "" end
	if kind(element) == "toggle" then
		return isChecked(id) and "1" or "0"
	end
	return element:GetAttribute("value") or ""
end

function selectValue(id)
	return value(id)
end

local function setValue(id, newValue)
	local element = el(id)
	if not element then return end
	if kind(element) == "toggle" then
		setChecked(id, tostring(newValue) == "1" or newValue == true)
		return
	end
	written[id] = tostring(newValue)
	element:SetAttribute("value", tostring(newValue))
	written[id] = element:GetAttribute("value") or ""
end

local function isScriptChange(id)
	return written[id] ~= nil and written[id] == value(id)
end

local function asSelect(element)
	return Element.As.ElementFormControlSelect(element)
end

local function optionCount(element)
	local count = 0
	for _ in ipairs(asSelect(element).options) do count = count + 1 end
	return count
end

local function hasOption(id, optionValue)
	for _, option in ipairs(asSelect(el(id)).options) do
		if option.value == optionValue then return true end
	end
	return false
end

local function setOptionList(elementId, list)
	local rml = {}
	for _, entry in ipairs(list) do
		rml[#rml + 1] = '<option value="' .. dew.escape(tostring(entry[2])) .. '">' .. dew.escape(tostring(entry[1])) .. "</option>"
	end
	local select = el(elementId)
	settleUntil[elementId] = dew_core.getTime() * 1000 + SETTLE_MS
	select.inner_rml = table.concat(rml)
	written[elementId] = value(elementId)
end

-- the row a control lives in
local function rowOf(element)
	while element and not element:IsClassSet("row") do
		element = element.parent_node
	end
	return element
end

-- jQuery :visible (fresh styles: called right after the page's `active` class changes)
local function isVisible(element)
	return dew_core.isDisplayed(element)
end

------------------------------------------------------------------------------------------
-- change queue

local function showApply(show)
	jq("#applyButton"):toggle(show)
end

local function queueChange(changeBlock)
	jq("#cancelButtonText"):text("Cancel")
	showApply(true)
	for i = #changeArray, 1, -1 do
		if changeArray[i][1] == changeBlock[1] then
			table.remove(changeArray, i)
		end
	end
	changeArray[#changeArray + 1] = changeBlock
end

local function queueBindChange(changeBlock)
	jq("#cancelButtonText"):text("Cancel")
	showApply(true)
	for i = #bindChangeArray, 1, -1 do
		if bindChangeArray[i][1] == changeBlock[1] then
			table.remove(bindChangeArray, i)
		end
	end
	bindChangeArray[#bindChangeArray + 1] = changeBlock
end

-- $('#settingsWindow input, select, textarea').on('change'): queue the cvar for the control
local function settingChanged(id)
	local elementId = id
	local element = el(id)
	if element and element:IsClassSet("tinySetting") and id:sub(-4) == "Text" then
		elementId = id:sub(1, -5)
	end
	local newValue = value(id)
	for _, entry in ipairs(settingsToLoad) do
		if entry[1] == elementId then
			queueChange({ entry[2], newValue })
		end
	end
	if playSound and not hiding then
		local now = nowMs()
		if now - lastSoundPlayedTime > 100 then
			lastSoundPlayedTime = now
			dew.playSound("a_button")
		end
	end
end

local onSpecialChange = {} -- id -> extra handler (the page's other change listeners)

local function fireChange(id)
	if id ~= "lookSensitivity" and id ~= "lookSensitivityText" and not el(id):IsClassSet("bind") then
		settingChanged(id)
	end
	local special = onSpecialChange[id]
	if special then
		special(id)
	end
end

------------------------------------------------------------------------------------------
-- pages and selection

local function pageElement()
	return activePage and el(activePage:sub(2)) or nil
end

-- the rows of the active page with a visible label (JS: activePage + ' label:visible')
local function selectableRows()
	local page = pageElement()
	local rows = {}
	if not page then return rows end
	for _, row in ipairs(page:QuerySelectorAll(".row")) do
		if row:QuerySelector("label") and isVisible(row) then
			rows[#rows + 1] = row
		end
	end
	return rows
end

-- the control a row edits (the .setting that is not the text box)
local function rowControl(row)
	if not row then return nil end
	local wrap = row:QuerySelector(".selectWrap")
	if wrap then return wrap:GetAttribute("data-control") end
	local range = row:QuerySelector("input.hasTiny")
	if range then return range.id end
	local setting = row:QuerySelector(".setting")
	return setting and setting.id or nil
end

local function updateSelection(item, sound, move, controller)
	local rows = selectableRows()
	if controller then
		jq(".selectedElement"):removeClass("selectedElement")
		if rows[item + 1] then
			rows[item + 1]:SetClass("selectedElement", true)
		end
	end
	selectedItem = rowControl(rows[itemNumber + 1])
	if move and rows[item + 1] then
		rows[item + 1]:ScrollIntoView(false)
	end
	if sound then
		dew.playSound("vertical_navigation")
	end
end

local function tabs()
	return document:QuerySelectorAll(".tabs li")
end

local initGamepad -- forward

local function showPage(pageHash)
	for _, page in ipairs(document:QuerySelectorAll(".page")) do
		page:SetClass("active", "#" .. page.id == pageHash)
	end
	activePage = pageHash
end

function switchPage(pageHash, isCancel)
	if not isCancel then
		dew.playSound("x_button")
	end
	itemNumber = 0
	showPage(pageHash)
	if hasGP then
		updateSelection(0, true, true, true)
	end
	if subPages[pageHash] then
		jq("#cancelButtonText"):text("Back")
	elseif #changeArray > 0 or #bindChangeArray > 0 then
		jq("#cancelButtonText"):text("Cancel")
	else
		jq("#cancelButtonText"):text("Close")
	end
	initGamepad()
end

local function selectTab(index, sound)
	local list = tabs()
	local tab = list[index + 1]
	if not tab then return end
	for _, other in ipairs(list) do
		other:SetClass("selected", false)
	end
	tab:SetClass("selected", true)
	showPage(tab:QuerySelector("a"):GetAttribute("data-page"))
	itemNumber = 0
	tabIndex = index
	updateSelection(0, false, true, true)
	if sound then
		dew.playSound("horizontal_navigation")
	end
end

local function initActive()
	selectTab(tabIndex, false)
end

local function prevPage()
	if tabIndex > 0 then
		selectTab(tabIndex - 1, true)
	end
end

local function nextPage()
	if tabIndex < #tabs() - 1 then
		selectTab(tabIndex + 1, true)
	end
end

local function upNav()
	if itemNumber > 0 then
		itemNumber = itemNumber - 1
		updateSelection(itemNumber, true, true, true)
	end
end

local function downNav()
	if itemNumber < #selectableRows() - 1 then
		itemNumber = itemNumber + 1
		updateSelection(itemNumber, true, true, true)
	end
end

local function onControllerConnect()
	updateSelection(itemNumber, false, true, true)
end

local function onControllerDisconnect()
	jq(".selectedItem"):removeClass("selectedItem")
end

initGamepad = function()
	dew.command("Settings.Gamepad", {}):next(function(result)
		if tonumber(result) == 1 then
			hasGP = true
			onControllerConnect()
		else
			onControllerDisconnect()
			hasGP = false
		end
	end)
end

local function formatNumber(number)
	if number == math.floor(number) then
		return string.format("%d", number)
	end
	return (string.format("%.3f", number):gsub("0+$", ""):gsub("%.$", ""))
end

local function stepRange(id, direction)
	local slider = el(id)
	local step = tonumber(slider:GetAttribute("step")) or 1
	local min = tonumber(slider:GetAttribute("min")) or 0
	local max = tonumber(slider:GetAttribute("max")) or 100
	local current = tonumber(value(id)) or 0
	if (direction < 0 and current <= min) or (direction > 0 and current >= max) then
		return
	end
	local newValue = math.max(min, math.min(max, current + direction * step))
	newValue = math.floor((newValue - min) / step + 0.5) * step + min
	setValue(id, formatNumber(newValue))
	setValue(id .. "Text", formatNumber(newValue))
	fireChange(id)
end

local function toggleSelect(id, direction)
	local select = asSelect(el(id))
	local index = (tonumber(select.selection) or 1) - 1
	local newIndex = index + direction
	if newIndex >= 0 and newIndex < optionCount(el(id)) then
		select.selection = newIndex + 1
		written[id] = value(id) -- handled here, not by the change event
		fireChange(id)
	end
end

local function leftToggle()
	local k = kind(el(selectedItem or ""))
	if k == "select" then toggleSelect(selectedItem, -1)
	elseif k == "range" then stepRange(selectedItem, -1) end
end

local function rightToggle()
	local k = kind(el(selectedItem or ""))
	if k == "select" then toggleSelect(selectedItem, 1)
	elseif k == "range" then stepRange(selectedItem, 1) end
end

local function toggleSetting()
	if kind(el(selectedItem or "")) == "toggle" then
		setChecked(selectedItem, not isChecked(selectedItem))
		fireChange(selectedItem)
	end
end

local function editButtonOf(id)
	local row = rowOf(el(id or ""))
	return row and row:QuerySelector("button.tinySetting") or nil
end

local function selectButton()
	local button = editButtonOf(selectedItem)
	if button then
		button:Click()
	else
		toggleSetting()
	end
end

------------------------------------------------------------------------------------------
-- values from the game

local function qualityMatches(setValueText)
	for _, id in ipairs({ "sTextureResolution", "sTextureFiltering", "sLightningQuality", "sEffectsQuality", "sShadowQuality", "sDetailsLevel", "sPostprocessing" }) do
		if value(id) ~= setValueText then return false end
	end
	return true
end

local function setControlValues()
	commandValues = {}
	dew.getCommands():next(function(commands)
		for _, command in ipairs(commands or {}) do
			local setValueText = tostring(command.value == nil and "" or command.value)
			for _, entry in ipairs(settingsToLoad) do
				if entry[2] == command.name then
					commandValues[#commandValues + 1] = { entry[1], command.name, setValueText }
					if entry[2]:sub(1, #"Input.ControllerSensitivityY") == "Input.ControllerSensitivityY" then
						setValue("ySens", setValueText); setValue("ySensText", setValueText)
						local h3Val = ((tonumber(setValueText) or 30) - 30) / 10
						setValue("lookSensitivity", formatNumber(h3Val)); setValue("lookSensitivityText", formatNumber(h3Val))
					elseif entry[2] == "Settings.PostprocessingQuality" then
						setValue(entry[1], setValueText)
						if qualityMatches(setValueText) then
							setValue("sQualityPreset", setValueText)
						else
							setValue("sQualityPreset", "custom")
						end
					else
						local element = el(entry[1])
						if element then
							setValue(entry[1], setValueText)
							if element:IsClassSet("hasTiny") or element:IsClassSet("hasEdit") then
								local number = tonumber(setValueText)
								if number and number ~= math.floor(number) then
									setValue(entry[1] .. "Text", formatNumber(tonumber(string.format("%.3f", number))))
								else
									setValue(entry[1] .. "Text", setValueText)
								end
							end
						end
					end
				end
			end
		end
	end)
end

------------------------------------------------------------------------------------------
-- controller binds

local function updateBindLabels()
	local graphic = el("controllerGraphic")
	local labels = {}
	for i = 1, CONTROLLER_BINDS do
		local bind = value(binds[i][1])
		if bind ~= "" and graphic:QuerySelector("#" .. bind) then
			labels[bind] = labels[bind] and (labels[bind] .. ", " .. binds[i][2]) or binds[i][2]
		end
	end
	for _, div in ipairs(graphic:QuerySelectorAll("div")) do
		div.inner_rml = dew.escape(labels[div.id] or "")
	end
end

local function getCurrentBindString()
	local parts = {}
	for i = 1, CONTROLLER_BINDS do
		parts[#parts + 1] = value(binds[i][1])
	end
	setValue("presetMenu", table.concat(parts, ","))
end

local function setButtonLists()
	local rml = {}
	for _, button in ipairs(buttons) do
		rml[#rml + 1] = '<option value="' .. button .. '">' .. button .. "</option>"
	end
	rml = table.concat(rml)
	for i = 1, CONTROLLER_BINDS do
		local select = el(binds[i][1])
		if select then
			select.inner_rml = rml
		end
	end
end

local function applyBindString(bindString)
	local bindArray = split(bindString, ",")
	for i, bind in ipairs(bindArray) do
		if binds[i] and el(binds[i][1]) then
			setValue(binds[i][1], bind)
			queueBindChange({ binds[i][1], bind })
		end
	end
	updateBindLabels()
end

------------------------------------------------------------------------------------------
-- keyboard binds (page5): a focused .keybind captures the next key or mouse button

local KEY_NAMES = {
	[69] = "Back", [70] = "Tab", [72] = "Enter", [61] = "NumpadEnter", [138] = "LShift", [139] = "RShift",
	[140] = "LControl", [141] = "RControl", [142] = "LAlt", [143] = "RAlt", [74] = "CapsLock", [1] = "Space",
	[90] = "Left", [91] = "Up", [92] = "Right", [93] = "Down", [99] = "Delete", [62] = "Multiply", [63] = "Add",
	[65] = "Subtract", [66] = "Decimal", [67] = "Divide", [38] = "Colon", [39] = "Plus", [40] = "Comma",
	[41] = "Minus", [42] = "Period", [43] = "Question", [45] = "LBracket", [46] = "Pipe", [47] = "RBracket",
	[48] = "Quote",
}
for i = 0, 9 do KEY_NAMES[2 + i] = tostring(i) end
for i = 0, 25 do KEY_NAMES[12 + i] = string.char(65 + i) end
for i = 0, 9 do KEY_NAMES[51 + i] = "Numpad" .. i end

local capturing = nil   -- the focused .keybind element's action and column
local captureStarted = 0

local function keybindElement()
	if not capturing then return nil end
	local row = el("bindBox"):QuerySelector('tr[data-action="' .. capturing.action .. '"]')
	return row and row:QuerySelectorAll(".keybind")[capturing.column] or nil
end

local function setKeybind(element, name)
	element:SetAttribute("data-key", name)
	element.inner_rml = dew.escape(name)
end

local function endCapture()
	local element = keybindElement()
	capturing = nil
	if element then
		element:Blur()
	end
	jq("#cancelButtonText"):text("Cancel")
	showApply(true)
end

local function captureValue(name)
	local element = keybindElement()
	if element and name then
		setKeybind(element, name)
	end
	endCapture()
end

local function onKeybindKey(key)
	local element = keybindElement()
	if not element then return end
	if key == KI_ESCAPE then
		preventCancel = true
		local initial = element:GetAttribute("data-initialvalue")
		if initial and initial ~= "" then
			if initial == element:GetAttribute("data-key") then
				setKeybind(element, "none")
			else
				setKeybind(element, initial)
			end
		end
		endCapture()
		return
	end
	captureValue(KEY_NAMES[key])
end

local function initializeBindings()
	dew.command("Input.DumpBindingsJson", {}):next(function(response)
		local bindDump = decode(response) or {}
		local groups = { Infantry = {}, Vehicle = {}, UI = {} }
		for _, dump in ipairs(bindDump) do
			if dump.controllerButton == "Select" then
				dump.controllerButton = "Back"
			end
			if el(dump.actionName) and el(dump.actionName):IsClassSet("bind") then
				setValue(dump.actionName, dump.controllerButton)
			end
			for _, bind in ipairs(binds) do
				if bind[1] == dump.actionName then
					local primaryBind = dump.primaryKey
					if dump.primaryMouseButton ~= "none" then primaryBind = dump.primaryMouseButton end
					local secondaryBind = dump.secondaryKey
					if dump.secondaryMouseButton ~= "none" then secondaryBind = dump.secondaryMouseButton end
					local group = groups[bind[3]]
					group[#group + 1] = string.format(
						'<tr data-action="%s"><td class="action">%s</td><td class="primary"><div class="keybind" tabindex="-1" data-key="%s" data-initialvalue="%s">%s</div></td><td><div class="keybind" tabindex="-1" data-key="%s" data-initialvalue="%s">%s</div></td></tr>',
						dew.escape(bind[1]), dew.escape(bind[2]),
						dew.escape(primaryBind), dew.escape(primaryBind), dew.escape(primaryBind),
						dew.escape(secondaryBind), dew.escape(secondaryBind), dew.escape(secondaryBind))
				end
			end
		end
		local spacer = '<tr class="bindSpacer"><th colspan="3"></th></tr>'
		local box = el("bindBox")
		box:QuerySelector("tbody.Infantry").inner_rml = table.concat(groups.Infantry)
		box:QuerySelector("tbody.Vehicle").inner_rml = spacer .. table.concat(groups.Vehicle)
		box:QuerySelector("tbody.UI").inner_rml = spacer .. table.concat(groups.UI)

		for _, row in ipairs(box:QuerySelectorAll("tr[data-action]")) do
			local action = row:GetAttribute("data-action")
			for column, keybind in ipairs(row:QuerySelectorAll(".keybind")) do
				keybind:AddEventListener("click", function()
					capturing = { action = action, column = column }
					captureStarted = nowMs()
					keybind:Focus()
				end)
			end
		end

		updateBindLabels()
		getCurrentBindString()
	end)
end

local function applyBinds()
	for _, row in ipairs(el("bindBox"):QuerySelectorAll("tr[data-action]")) do
		local keys = row:QuerySelectorAll(".keybind")
		local primaryKey = keys[1] and keys[1]:GetAttribute("data-key") or "none"
		local secondaryKey = keys[2] and keys[2]:GetAttribute("data-key") or "none"
		dew.command("Input.KeyboardAction " .. row:GetAttribute("data-action") .. " " .. primaryKey .. " " .. secondaryKey)
	end
	dew.command("writeconfig")
end

------------------------------------------------------------------------------------------
-- buttons

local function hideScreen()
	hiding = true
	-- only want to listen while in settings
	if isChecked("vListenToMicrophone") then
		setChecked("vListenToMicrophone", false)
		dew.command("VoIP.ListenToMicrophone 0")
	end
	dew.GameBlur("settings", false)
	jq("#overlay"):fadeOut(150)
	jq("#settingsWindow"):fadeOut(150, function()
		dew.hide()
	end)
end

local function effectReset()
	playSound = false
	dew.playSound("b_button")
	hideScreen()
	playSound = true
end

local function applySettings()
	local mainmenuChanged = false
	local voipReload = false
	for _, change in ipairs(changeArray) do
		if change[1] == "Game.MainMenuMod" then
			mainmenuChanged = true
		end
		if change[1] == "VoIP.MicrophoneID" or change[1] == "VoIP.AGC" or change[1] == "VoIP.NoiseSupress" or change[1] == "VoIP.EchoCancelation" then
			voipReload = true
		end
		dew.command(change[1] .. ' "' .. tostring(change[2]) .. '"', {}):catch(function(err)
			console.error(err)
		end)
	end
	local notified = {}
	for i, change in ipairs(changeArray) do
		notified[i] = json.array({ change[1], change[2] })
	end
	dew.notify("settings-update", json.array(notified))
	changeArray = {}
	dew.command("writeconfig")
	dew.command("VoIP.Update"):next(function()
		if voipReload then
			dew.notify("voip-reload")
		end
	end)
	if subPages[activePage] then
		jq("#cancelButtonText"):text("Back")
	else
		jq("#cancelButtonText"):text("Close")
	end
	showApply(false)
	initGamepad()
	return mainmenuChanged
end

local cancelButton -- forward

local function applyBindChanges(i)
	if i <= #bindChangeArray then
		local change = bindChangeArray[i]
		local button = change[2]
		if button == "Back" then button = "Select" end
		if button ~= "" then button = '"' .. button .. '"' end
		dew.command('Input.ControllerAction "' .. change[1] .. '" ' .. button, {}):next(function()
			applyBindChanges(i + 1)
		end, function(err)
			console.error(err)
			applyBindChanges(i + 1)
		end)
	else
		bindChangeArray = {}
		dew.command("writeconfig")
		if subPages[activePage] then
			jq("#cancelButtonText"):text("Back")
		else
			jq("#cancelButtonText"):text("Close")
		end
		initGamepad()
	end
end

local function applyButton()
	dew.playSound("a_button")
	if activePage == "#page5" then
		applyBinds()
		switchPage("#page2", true)
		if #changeArray == 0 and #bindChangeArray == 0 then
			showApply(false)
		end
	elseif activePage == "#page4" then
		if applySettings() then cancelButton() end
		switchPage("#page3", true)
	elseif activePage == "#page11" then
		switchPage("#page8", true)
	elseif #changeArray > 0 or #bindChangeArray > 0 then
		local mainmenuChanged = applySettings()
		applyBindChanges(1)
		if mainmenuChanged then cancelButton() end
	else
		effectReset()
	end
end

local function resetButton()
	dew.playSound("x_button")
	if activePage == "#page5" or activePage == "#page8" or activePage == "#page9" then
		dew.dialog("confirm_reset_bindings"):next(function(result)
			if result == "yes" then
				dew.command("Input.ResetBindings"):next(function() initializeBindings() end)
			end
		end)
	else
		dew.dialog("confirm_reset"):next(function(result)
			if result == "yes" then
				dew.command("Settings.Reset"):next(function()
					setControlValues()
					initGamepad()
				end)
			end
		end)
	end
end

local function dismissButton()
	itemNumber = 0
	hideScreen()
	setControlValues()
	changeArray = {}
	if #bindChangeArray > 0 then
		initializeBindings()
		bindChangeArray = {}
	end
	showApply(false)
end

cancelButton = function()
	if activePage == "#page5" then
		initializeBindings()
		dew.playSound("b_button")
		switchPage("#page2", true)
		jq("#cancelButtonText"):text("Close")
		if #changeArray == 0 then showApply(false) end
	elseif activePage == "#page4" then
		setControlValues()
		dew.playSound("b_button")
		switchPage("#page3", true)
	elseif activePage == "#page9" then
		dew.playSound("b_button")
		switchPage("#page8", true)
	elseif activePage == "#page8" then
		dew.playSound("b_button")
		switchPage("#page2", true)
	elseif activePage == "#page11" then
		dew.playSound("b_button")
		switchPage("#page8", true)
	elseif #changeArray > 0 or #bindChangeArray > 0 then
		dew.playSound("a_button")
		dew.dialog("unapplied_settings"):next(function(result)
			if result == "ok" then
				dismissButton()
			end
		end)
	else
		itemNumber = 0
		effectReset()
	end
end

function editControls(which)
	if tonumber(which) == 0 then
		switchPage("#page5")
	else
		switchPage("#page8")
	end
end

function showWeaponOffsets()
	if mapName ~= "mainmenu" then
		dew.command("Weapon.Equipped", {}):next(function(response)
			local weaponInfo = decode(response) or {}
			if (weaponInfo.Type or "") == "" then
				dew.playSound("a_button")
				dew.dialog("weapon_offsets_not_supported")
			else
				hideScreen()
				dew.show("weapon_offset")
			end
		end)
	else
		dew.playSound("a_button")
		dew.dialog("weapon_offsets_in_game_warning")
	end
end

local function setButtons()
	jq("#resetButton img"):attr("src", "dew://assets/buttons/360_Y.png")
	jq("#applyButton img"):attr("src", "dew://assets/buttons/360_Start.png")
	jq("#cancelButton img"):attr("src", "dew://assets/buttons/360_B.png")
	local tabImages = document:QuerySelectorAll(".tabs img")
	if tabImages[1] then tabImages[1]:SetAttribute("src", "dew://assets/buttons/360_LB.png") end
	if tabImages[2] then tabImages[2]:SetAttribute("src", "dew://assets/buttons/360_RB.png") end
end

local function loadWeaponOffsets()
	dew.command("Weapon.JSON.List", {}):next(function(response)
		local offsetArray = {}
		for _, name in ipairs(split(response, ",")) do
			if not name:find(" ", 1, true) then
				offsetArray[#offsetArray + 1] = { name, name }
			end
		end
		setOptionList("wOffsetConfig", offsetArray)
	end)
end

local function loadMicrophones()
	local deviceArray = { { "Default", "" } }
	for _, name in ipairs(dew.enumerateAudioInputs() or {}) do
		deviceArray[#deviceArray + 1] = { name, name }
	end
	setOptionList("vMicrophoneID", deviceArray)
end

------------------------------------------------------------------------------------------
-- events

dew.on("show", function(e)
	hiding = false
	local page = e.data
	if type(page) == "string" and page ~= "" then
		local tabsByName = { game = 0, controls = 1, video = 2, sound = 3 }
		if tabsByName[page] then tabIndex = tabsByName[page] end
	else
		tabIndex = 0
	end

	dew.getSessionInfo():next(function(info)
		mapName = info and info.mapName or "mainmenu"
		dew.GameBlur("settings", true)
		jq("#overlay"):fadeIn(150)
		jq("#settingsWindow"):fadeIn(150)
		initActive()
		initGamepad()
	end)

	loadWeaponOffsets()
	setControlValues()

	dew.command("Server.ListMods", {}):next(function(response)
		local mods = decode(response) or {}
		local lists = { sMainmenuMod = {}, sMultiplayerMod = {}, sCampaignMod = {}, sFirefightMod = {} }
		for id in pairs(lists) do lists[id][1] = { "None", "" } end
		for _, mod in ipairs(mods) do
			local label = tostring(mod.name) .. " " .. tostring(mod.version)
			if dew.truthy(mod.mainmenuType) then table.insert(lists.sMainmenuMod, { label, mod.filename }) end
			if dew.truthy(mod.multiplayerType) then table.insert(lists.sMultiplayerMod, { label, mod.filename }) end
			if dew.truthy(mod.campaignType) then table.insert(lists.sCampaignMod, { label, mod.filename }) end
			if dew.truthy(mod.firefightType) then table.insert(lists.sFirefightMod, { label, mod.filename }) end
		end
		for id, list in pairs(lists) do
			setOptionList(id, list)
		end
		for id, command in pairs({ sMainmenuMod = "Game.MainMenuMod", sCampaignMod = "Game.CampaignMod", sFirefightMod = "Game.FirefightMod", sMultiplayerMod = "Game.MultiplayerMod" }) do
			dew.command(command, {}):next(function(current)
				if hasOption(id, current) then
					setValue(id, current)
				else
					setValue(id, "")
				end
			end)
		end
		dew.command("Settings.AudioOutputDeviceList", {}):next(function(devices)
			local audioDevArray = {}
			for i, name in ipairs(decode(devices) or {}) do
				audioDevArray[#audioDevArray + 1] = { name, i - 1 }
			end
			setOptionList("sAudioDevice", audioDevArray)
		end)
	end)

	dew.command("Input.ControllerAimControl"):next(function(response)
		jq(".ModernAimingType"):toggle(response == "1")
	end)
	dew.command("Input.RawInput"):next(function(response)
		jq(".NormalInput"):toggle(response ~= "1")
	end)
end)

dew.input.on("action", function(evt)
	local Actions = dew.input.Actions
	if evt.action == Actions.LeftBumper then
		prevPage()
	elseif evt.action == Actions.RightBumper then
		nextPage()
	elseif evt.action == Actions.Y then
		resetButton()
	elseif evt.action == Actions.Start then
		applyButton()
	elseif evt.action == Actions.X then
		local button = editButtonOf(selectedItem)
		if button then button:Click() end
	elseif evt.action == Actions.A then
		selectButton()
	elseif evt.action == Actions.B then
		if evt.inputType ~= "keyboard" then
			cancelButton()
		end
	end
end)

dew.input.on("scroll", function(type, axis, direction)
	if capturing then return end
	if type == 0 or type == 1 then -- dpad/joystick
		if axis == 0 then
			if direction == -1 then upNav() end
			if direction == 1 then downNav() end
		end
		if axis == 1 then
			if direction == -1 then leftToggle() end
			if direction == 1 then rightToggle() end
		end
	end
	if type == 2 and axis == 0 then -- left/right trigger
		if direction == -1 and itemNumber > 0 then
			itemNumber = 0
			updateSelection(itemNumber, true, true, true)
		end
		local last = #selectableRows() - 1
		if direction == 1 and itemNumber < last then
			itemNumber = last
			updateSelection(itemNumber, true, true, true)
		end
	end
end)

document:AddEventListener("keyup", function(event)
	local key = tonumber(event.parameters.key_identifier)
	if key == KI_ESCAPE then
		if preventCancel then
			preventCancel = false
			return
		end
		cancelButton()
	end
	if key == KI_SNAPSHOT then
		dew.command("Game.TakeScreenshot")
	end
end)

document:AddEventListener("keydown", function(event)
	local key = tonumber(event.parameters.key_identifier)
	if capturing then
		event:StopPropagation()
		onKeybindKey(key)
		return
	end
	if key == KI_OEM_3 or key == KI_OEM_8 then
		dew.show("console")
	end
	-- keep arrows/space/tab from moving focus or stepping controls (input.lua navigates)
	if activePage ~= "#page5" then
		local target = event.target_element
		local typing = target and target.tag_name == "input" and target:GetAttribute("type") ~= "range"
		if key == 91 or key == 93 or key == 70 or ((key == 90 or key == 92 or key == 1) and not typing) then
			event:StopPropagation()
		end
	end
end)

local MOUSE_NAMES = { [0] = "MouseLeft", [1] = "MouseRight", [2] = "MouseMiddle" }

document:AddEventListener("mousedown", function(event)
	if capturing and nowMs() - captureStarted > 50 then
		local button = tonumber(event.parameters.button) or 0
		if button == 1 then
			rightclickKeybind = true
		end
		event:StopPropagation()
		captureValue(MOUSE_NAMES[button] or ("Mouse" .. (button + 1)))
	end
end)

document:AddEventListener("mousescroll", function(event)
	if capturing then
		event:StopPropagation()
		local delta = tonumber(event.parameters.wheel_delta_y) or 0
		captureValue(delta < 0 and "MouseWheelUp" or "MouseWheelDown")
	end
end)

document:AddEventListener("mouseup", function(event)
	if tonumber(event.parameters.button) == 1 then
		if rightclickKeybind then
			rightclickKeybind = false
			return
		end
		if not (activePage == "#page5" and capturing) then
			cancelButton()
		end
	end
end)

dew.on("mouse-xbutton-event", function(m)
	if not capturing then return end
	if tonumber((m.data or {}).xbutton) == 1 then
		captureValue("Mouse4")
	else
		captureValue("Mouse5")
	end
end)

document:AddEventListener("load", function()
	settleAll = dew_core.getTime() * 1000 + SETTLE_MS
	setButtonLists()
	setOptionList("presetMenu", (function()
		local list = {}
		for i, preset in ipairs(controllerPresets) do list[i] = { preset[1], preset[2] } end
		return list
	end)())
	loadWeaponOffsets()

	for index, tab in ipairs(tabs()) do
		tab:QuerySelector("a"):AddEventListener("click", function()
			selectTab(index - 1, true)
		end)
	end

	-- every control raises change; user changes only (script writes are filtered)
	local controls = {}
	for _, element in ipairs(el("settingsWindow"):QuerySelectorAll("select, input")) do
		controls[#controls + 1] = element
	end
	for _, control in ipairs(controls) do
		local id = control.id
		if id and id ~= "" then
			control:AddEventListener("change", function()
				if settling(id) or isScriptChange(id) then
					written[id] = value(id)
					return
				end
				written[id] = value(id)
				local k = kind(control)
				-- range <-> text box mirroring
				if k == "range" and el(id .. "Text") then
					setValue(id .. "Text", value(id))
				elseif k == "text" and control:IsClassSet("tinySetting") and id:sub(-4) == "Text" then
					local target = id:sub(1, -5)
					local slider = el(target)
					-- 'input' sanitiser: numbers and points only, clamped to the slider range
					local text = value(id)
					local sanitized = text:gsub("[^0-9.]", "")
					local number = tonumber(sanitized)
					if slider and number then
						local min, max = tonumber(slider:GetAttribute("min")), tonumber(slider:GetAttribute("max"))
						if min and number < min then sanitized = formatNumber(min) end
						if max and number > max then sanitized = formatNumber(max) end
					end
					if sanitized ~= text then
						setValue(id, sanitized)
					end
					if slider then
						setValue(target, sanitized)
					end
				end
				fireChange(id)
			end)
		end
	end

	-- toggles: the control and its label flip the value
	for _, toggle in ipairs(el("settingsWindow"):QuerySelectorAll(".toggle")) do
		local id = toggle.id
		local function flip()
			setChecked(id, not isChecked(id))
			fireChange(id)
		end
		toggle:AddEventListener("click", flip)
		local row = rowOf(toggle)
		local label = row and row:QuerySelector("label")
		if label then
			label:AddEventListener("click", flip)
		end
	end

	-- the page's other change listeners
	onSpecialChange.aimingType = function()
		jq(".ModernAimingType"):toggle(value("aimingType") == "1")
	end
	onSpecialChange.inputRaw = function()
		jq(".NormalInput"):toggle(not isChecked("inputRaw"))
	end
	local function lookSensitivity(id)
		local yVal = 30 + ((tonumber(value(id)) or 0) * 10)
		queueChange({ "Input.ControllerSensitivityX", yVal * 2 })
		queueChange({ "Input.ControllerSensitivityY", yVal })
	end
	onSpecialChange.lookSensitivity = lookSensitivity
	onSpecialChange.lookSensitivityText = lookSensitivity
	local function vibration(id)
		dew.command("Input.ControllerVibrationIntensity " .. value(id), {}):next(function()
			dew.command("Input.ControllerVibrationTest")
		end)
	end
	onSpecialChange.controllerVibration = vibration
	onSpecialChange.controllerVibrationText = vibration
	local qualityIds = { "sTextureResolution", "sTextureFiltering", "sLightningQuality", "sEffectsQuality", "sShadowQuality", "sDetailsLevel", "sPostprocessing" }
	for _, id in ipairs(qualityIds) do
		onSpecialChange[id] = function()
			local current = value(id)
			if value("sTextureResolution") == current and value("sTextureFiltering") == current and value("sLightningQuality") == current
				and value("sEffectsQuality") == current and value("sDetailsLevel") == current and value("sPostprocessing") == current then
				setValue("sQualityPreset", current)
			else
				setValue("sQualityPreset", "custom")
			end
		end
	end
	onSpecialChange.sQualityPreset = function()
		local preset = value("sQualityPreset")
		if preset == "custom" then return end
		for _, id in ipairs(qualityIds) do setValue(id, preset) end
		if preset == "high" then
			setChecked("sMotionBlur", true)
			setChecked("sSSAOEnabled", true)
			setValue("sLODDistance", "10")
			setValue("sDecoratorDistance", "1")
			setValue("sShadowResolution", "4096")
		else
			setChecked("sMotionBlur", false)
			setValue("sLODDistance", "2")
			setValue("sDecoratorDistance", "1")
			setValue("sShadowResolution", "2048")
		end
		if preset == "low" then
			setChecked("sSSAOEnabled", false)
			setValue("sLODDistance", "1")
			setValue("sDecoratorDistance", "0")
			setValue("sShadowResolution", "1024")
		end
		-- $('.video').trigger('change')
		playSound = false
		for _, element in ipairs(el("settingsWindow"):QuerySelectorAll(".video")) do
			local id = element.id
			if element:IsClassSet("selectWrap") then
				id = element:GetAttribute("data-control")
			end
			if id and id ~= "" then
				settingChanged(id)
			end
		end
		playSound = true
	end
	onSpecialChange.presetMenu = function()
		applyBindString(value("presetMenu"))
	end
	onSpecialChange.wOffsetConfig = function()
		changeArray[#changeArray + 1] = { "Weapon.JSON.Load", "" }
	end
	onSpecialChange.sLODDistance = function()
		if lodWarned then return end
		dew.dialog("strain_system")
		lodWarned = true
	end
	onSpecialChange.vListenToMicrophone = function()
		dew.command("VoIP.ListenToMicrophone " .. (isChecked("vListenToMicrophone") and "1" or "0"))
	end
	for i = 1, CONTROLLER_BINDS do
		local id = binds[i][1]
		if el(id) then
			onSpecialChange[id] = function()
				queueBindChange({ id, value(id) })
				updateBindLabels()
			end
		end
	end

	dew.command("Graphics.SupportedResolutions", {}):next(function(response)
		local resolutionArray = { { "Default", "default" } }
		for _, resolution in ipairs(decode(response) or {}) do
			resolutionArray[#resolutionArray + 1] = { resolution, resolution }
		end
		setOptionList("sScreenResolution", resolutionArray)
	end)

	el("applyButton"):AddEventListener("click", function() applyButton() end)
	el("resetButton"):AddEventListener("click", function() resetButton() end)
	el("cancelButton"):AddEventListener("click", function() cancelButton() end)

	loadMicrophones()
	setControlValues()
	initializeBindings()

	-- rows follow the mouse (rows carry an index: element userdata do not compare equal)
	for index, row in ipairs(el("settingsWindow"):QuerySelectorAll(".row")) do
		row:SetAttribute("data-row", tostring(index))
	end
	for _, row in ipairs(el("settingsWindow"):QuerySelectorAll(".row")) do
		if row:QuerySelector(".setting") then
			local uid = row:GetAttribute("data-row")
			row:AddEventListener("mouseover", function()
				local rows = selectableRows()
				for i, candidate in ipairs(rows) do
					if candidate:GetAttribute("data-row") == uid then
						itemNumber = i - 1
					end
				end
				jq(".selectedElement"):removeClass("selectedElement")
				row:SetClass("selectedElement", true)
				updateSelection(itemNumber, false, false, false)
			end)
		end
	end

	setButtons()
end)

-- debugging aid (harness `lua settings return pendingChanges()`)
function pendingChanges()
	local parts = {}
	for _, change in ipairs(changeArray) do parts[#parts + 1] = tostring(change[1]) .. "=" .. tostring(change[2]) end
	for _, change in ipairs(bindChangeArray) do parts[#parts + 1] = "bind:" .. tostring(change[1]) .. "=" .. tostring(change[2]) end
	return table.concat(parts, ", ") .. " [sel=" .. tostring(selectedItem) .. " item=" .. itemNumber .. " page=" .. tostring(activePage) .. "]"
end
