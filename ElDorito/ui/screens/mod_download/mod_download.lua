-- Port of screens/mod_download/mod_download.js

local settingsArray = { ["Settings.Gamepad"] = "0" }
local packageList = {}
local startTime, previousSize = 0, 0
local isDetailsCollapsed = true
local packageCount = 0
local packageIndex = 0
local compactMode = false
local mouseCaptured = false
local readyToJoin = false
local singleDownloadMode = false
local websiteUrl = ""

local function el(id) return document:GetElementById(id) end
local function setText(id, text) el(id).inner_rml = dew.escape(tostring(text or "")) end
local function nowMs() return dew_core.getTime() * 1000 end

dew.on("variable_update", function(e)
	for _, variable in ipairs(e.data or {}) do
		if settingsArray[variable.name] ~= nil then settingsArray[variable.name] = variable.value end
	end
end)

local function bytesToSize(bytes)
	bytes = tonumber(bytes) or 0
	if bytes == 0 then return "0 Byte" end
	local i = math.floor(math.log(bytes) / math.log(1024))
	return string.format("%.1f %s", bytes / (1024 ^ i), ({ "Bytes", "KB", "MB", "GB", "TB" })[i + 1])
end

local function packages()
	local list = {}
	for _, pkg in pairs(packageList or {}) do
		if type(pkg) == "table" then list[#list + 1] = pkg end
	end
	return list
end

local function prettyPrintPackages()
	local parts = {}
	for _, pkg in ipairs(packages()) do
		parts[#parts + 1] = tostring(pkg.mod_name) .. "\n"
			.. "- Hash: " .. tostring(pkg.hash) .. "\n"
			.. "- Author: " .. tostring(pkg.mod_author) .. "\n"
			.. "- Version: " .. tostring(pkg.mod_version) .. "\n"
			.. "- Size: " .. bytesToSize(pkg.package_size) .. "\n"
			.. "- Website: " .. ((pkg.mod_website == nil or pkg.mod_website == "") and "N/A" or tostring(pkg.mod_website)) .. "\n"
			.. "- " .. tostring(pkg.mod_description or "") .. "\n\n"
	end
	return (table.concat(parts):gsub("%s+$", ""))
end

local function getTotalPackageSize()
	local total = 0
	for _, pkg in ipairs(packages()) do total = total + (tonumber(pkg.package_size) or 0) end
	return bytesToSize(total)
end

local function resetDialogSize()
	for _, detail in ipairs(document:QuerySelectorAll(".detail")) do
		detail.scroll_top = 0
		detail:SetClass("collapsed", true)
	end
	el("dialog"):SetClass("details", false)
	isDetailsCollapsed = true
end

local function onShow()
	local dialog = el("dialog")
	if compactMode then
		dew.GameBlur("moddownloader", false, 15)
		jq(".dialog_container"):fadeOut(200)
		jq("#windowCompact"):fadeIn(200)
		document:QuerySelector(".backdrop"):SetClass("visible", false)
		dialog:SetClass("show", false)
		dew.captureInput(false)
		mouseCaptured = false
	else
		dew.GameBlur("moddownloader", true)
		jq(".dialog_container"):fadeIn(200)
		jq("#windowCompact"):fadeOut(200)
		dew.requestAnimationFrame(function()
			dialog:SetClass("show", true)
			document:QuerySelector(".backdrop"):SetClass("visible", true)
		end)
		dew.captureInput(true)
		mouseCaptured = true
	end
end

local function maximize()
	dew.playSound("x_button")
	compactMode = false
	onShow()
end

local function hideScreen()
	el("dialog"):SetClass("show", false)
	document:QuerySelector(".backdrop"):SetClass("visible", false)
	dew.setTimeout(function() dew.hide() end, 500)
end

local function submitAction(action, data)
	local method = singleDownloadMode and "modDownloadActionSingle" or "modDownloadAction"
	dew.callMethod(method, { action = action, data = data })
end

local actions = {}
function actions.rejectDownload() dew.playSound("b_button"); submitAction("reject") end
function actions.confirmDownload()
	dew.playSound("a_button")
	setProgressStatus("Preparing to download...", 0)
	submitAction("confirm")
end
function actions.retryDownload() dew.playSound("a_button"); submitAction("retry") end
function actions.cancelDownload() dew.playSound("b_button"); submitAction("reject") end
function actions.confirmJoin() dew.playSound("a_button"); submitAction("joinServer") end
function actions.confirmFinished() dew.playSound("a_button"); submitAction("confirmFinished") end
function actions.detail()
	dew.playSound("a_button")
	local text = dew.escape(prettyPrintPackages())
	for _, detail in ipairs(document:QuerySelectorAll(".detail")) do
		detail.inner_rml = text
		detail:SetClass("collapsed", not detail:IsClassSet("collapsed"))
	end
	isDetailsCollapsed = not isDetailsCollapsed
	el("dialog"):SetClass("details", not isDetailsCollapsed)
end

function setProgressStatus(text, percent)
	setText("download_status", text)
	el("progress").style.width = string.format("%.2f%%", percent)
	el("compact_progress").style.width = string.format("%.2f%%", percent)
end

local function setProgress(text, percent, version, website, name, shortName, speed, secondsRemaining)
	setText("download_name", "Mod: " .. name)
	setText("download_desc", "Version: " .. version)
	websiteUrl = website or ""
	setText("mod_website", websiteUrl == "" and "N/A" or websiteUrl)
	if singleDownloadMode then
		setText("download_count", "")
		setText("compact_download_count", "")
	else
		setText("download_count", (packageIndex + 1) .. "/" .. packageCount)
		setText("compact_download_count", (packageIndex + 1) .. "/" .. packageCount)
	end
	setText("compact_download_name", "Mod: " .. shortName .. " @ " .. tostring(speed) .. " - " .. tostring(secondsRemaining))
	setProgressStatus(text, percent)
end

local function updateProgress(index, name, current, total, speed, secondsRemaining, description, website)
	packageIndex = tonumber(index) or 0
	local percent = current / total * 100
	local remaining = #secondsRemaining > 0 and (" - " .. secondsRemaining .. " remaining") or ""
	setProgress(string.format("Downloading %s/%s @ %s%s", bytesToSize(current), bytesToSize(total), tostring(speed), remaining),
		percent, tostring(description or ""):sub(1, 127), website, tostring(name):sub(1, 32), tostring(name):sub(1, 15), speed, secondsRemaining)
end

-- speed and remaining time as the web page formatted them
local function speedInfo(data, zeroEnding)
	local total, current = tonumber(data.total) or 0, tonumber(data.current) or 0
	if previousSize ~= total then
		startTime = nowMs()
		previousSize = total
	end
	local speedBps = tonumber(data.speed) or 0
	local speedKBps = speedBps ~= 0 and math.floor(speedBps / 1024 + 0.5) or 0
	local speedMBps = speedKBps ~= 0 and math.floor(speedKBps / 1024 + 0.5) or 0
	local estimated = speedBps ~= 0 and math.floor((total - current) / speedBps + 0.5) or 0
	local ending = estimated ~= 0 and ((estimated / 60 > 1) and " min" or " s") or zeroEnding
	if estimated / 60 > 1 then estimated = math.floor(estimated / 60 + 0.5) end
	local speed
	if speedMBps <= 0 then
		speed = speedKBps .. " KB/s"
	elseif speedKBps <= 0 then
		speed = speedBps .. " B/s"
	else
		speed = speedMBps .. " MB/s"
	end
	return speed, speedMBps, speedBps, estimated .. ending
end

------------------------------------------------------------------------------------------
-- screens

local screens = {}
local currentScreen = ""

local function showButtons(id, show) el(id).style.display = show and "flex" or "none" end

local function simple(screenId, title, buttons, extraEnter, extraExit)
	return {
		enter = function()
			if title then setText("dialog-title", type(title) == "function" and title() or title) end
			el(screenId):SetClass("active", true)
			if buttons then showButtons(buttons, true) end
			if extraEnter then extraEnter() end
		end,
		exit = function()
			el(screenId):SetClass("active", false)
			if buttons then showButtons(buttons, false) end
			if extraExit then extraExit() end
		end,
	}
end

screens.awaiting_confirmation = simple("screen_awaiting_confirmation", "THIS SERVER HAS MODS", "confirm_dialog")
screens.awaiting_confirmation_single = simple("screen_awaiting_confirmation_single", "DOWNLOAD MOD", "confirm_dialog",
	function() singleDownloadMode = true end)
screens.downloading = simple("screen_downloading", function() return singleDownloadMode and "DOWNLOADING MOD" or "DOWNLOADING MODS" end, "download_progress")
screens.download_failed = simple("screen_download_failed", "DOWNLOAD FAILED", "download_failed")
screens.download_cancelling = simple("screen_download_cancelling", "DOWNLOAD CANCELLED")
screens.download_finished = {
	enter = function()
		setText("dialog-title", "DOWNLOAD FINISHED")
		el("compact_progress").style.width = "100%"
		setText("compact_download_name", "Download Completed. Click to Join")
		if compactMode then
			el("screen_download_finished"):SetClass("active", true)
			showButtons("download_finished", true)
			readyToJoin = true
		else
			actions.confirmJoin()
		end
	end,
	exit = function()
		el("screen_download_finished"):SetClass("active", false)
		showButtons("download_finished", false)
	end,
}
screens.download_single_finished = {
	enter = function()
		setText("dialog-title", "DOWNLOAD FINISHED")
		el("compact_progress").style.width = "100%"
		setText("compact_download_name", "Download Completed.")
		showButtons("download_single_finished", true)
		el("screen_download_single_finished"):SetClass("active", true)
		actions.confirmFinished()
	end,
	exit = function()
		el("screen_download_single_finished"):SetClass("active", false)
		showButtons("download_single_finished", false)
	end,
}
screens.download_finalizing = {
	enter = function()
		setText("dialog-title", "DOWNLOAD FINALIZING")
		el("screen_download_finalizing"):SetClass("active", true)
		el("compact_progress").style.width = "100%"
		setText("compact_download_name", "Preparing files...")
		showButtons("download_progress", true)
		el("compact_download_count").style.display = "none"
	end,
	exit = function()
		el("screen_download_finalizing"):SetClass("active", false)
		showButtons("download_progress", false)
	end,
}

local function transitionTo(name)
	resetDialogSize()
	local from, to = screens[currentScreen], screens[name]
	if from and from.exit then from.exit() end
	if to and to.enter then to.enter() end
	currentScreen = name
end

local function isActive(id) return el(id):IsClassSet("active") end

------------------------------------------------------------------------------------------
-- events

dew.on("show", function(e)
	readyToJoin = false
	compactMode = false
	onShow()
	previousSize = 0
	if type(e.data) == "table" and next(e.data) ~= nil then
		packageList = e.data
	end
	packageCount = #packages()
	local size = getTotalPackageSize()
	setText("total_size", size)
	setText("total_size_single", size)
	resetDialogSize()
end)

dew.on("hide_moddownloader", function() hideScreen() end)

dew.on("hide", function()
	dew.GameBlur("moddownloader", false, 15)
	resetDialogSize()
	singleDownloadMode = false
	el("dialog"):SetClass("show", false)
end)

dew.on("modDownloadStatus", function(e)
	local data = e.data or {}
	local total, current = tonumber(data.total) or 0, tonumber(data.current) or 0
	if total > 0 and current < total then
		local speed, _, speedBps, remaining = speedInfo(data, " s")
		updateProgress(data.index, tostring(data.name or ""), current, total, speed, speedBps > 0 and remaining or "", data.version, data.website)
	end
end)

dew.on("singleModDownloadProgress", function(e)
	local data = e.data or {}
	local total, current = tonumber(data.total) or 0, tonumber(data.current) or 0
	if total > 0 and current < total then
		local _, speedMBps, _, remaining = speedInfo(data, "0 s")
		updateProgress(data.index, tostring(data.name or ""), current, total, speedMBps, remaining, data.desc, data.website)
	end
end)

local FAILURE_REASONS = {
	Cancelled = "Download cancelled", NotEnoughDiskSpace = "Not enough disk space", BadResponse = "Server returned bad response",
	RequestError = "Server request error", FileError = "Error writing to file", NetworkError = "Network error",
}
dew.on("modDownloadFailed", function(e)
	previousSize = 0
	setText("download_error_reason", FAILURE_REASONS[(e.data or {}).reason] or "Unknown error")
end)

dew.on("mouseCapture", function(e)
	if compactMode then
		local blocked = dew.truthy((e.data or {}).blocked)
		mouseCaptured = blocked
		el("windowCompact").style.opacity = blocked and "0.8" or "0.5"
		dew.capturePointer(blocked)
		el("windowCompact"):SetClass("active", blocked)
	end
end)

dew.on("modDownloadStateChange", function(e) transitionTo((e.data or {}).toState) end)

dew.on("singleModDownloadStateChange", function(e)
	local state = (e.data or {}).state
	if state == "downloading" then
		transitionTo("downloading")
		setProgressStatus("Preparing to download...", 0)
		dew.show()
	elseif state == "cancelling" then
		setProgressStatus("Cancelling...", 0)
	elseif state == "completed" or state == "none" then
		hideScreen()
	end
end)

dew.on("modDownloadFinished", function(e)
	local data = e.data or {}
	local modsCompleted = packageCount .. (packageCount == 1 and " Mod" or " Mods")
	setText("finished_description", modsCompleted .. " has been downloaded successfully. Ready to join Server: \n"
		.. "Name: " .. tostring(data.serverName) .. "\n" .. "Host: " .. tostring(data.serverHost))
end)

dew.on("menuMaximizedByController", function()
	if compactMode and mouseCaptured then maximize() end
end)

dew.on("controllerinput", function(e)
	if tonumber(settingsArray["Settings.Gamepad"]) ~= 1 then return end
	local c = e.data or {}
	local awaiting = isActive("screen_awaiting_confirmation") or isActive("screen_awaiting_confirmation_single")
	if c.A == 1 and awaiting then actions.confirmDownload() end
	if awaiting and not isDetailsCollapsed then
		local delta = (c.Up == 1 and -20) or (c.Down == 1 and 20) or 0
		if delta ~= 0 then
			for _, detail in ipairs(document:QuerySelectorAll(".detail")) do detail.scroll_top = detail.scroll_top + delta end
		end
	end
	if c.A == 1 and isActive("screen_download_failed") then actions.retryDownload() end
	if c.A == 1 and isActive("screen_download_finished") then actions.confirmJoin() end
	if c.A == 1 and isActive("screen_download_single_finished") then actions.confirmFinished() end
	if c.B == 1 and (isActive("screen_download_finished") or isActive("screen_download_single_finished")) then actions.rejectDownload() end
	if c.B == 1 and (isActive("screen_downloading") or isActive("screen_download_failed")) then actions.cancelDownload() end
	if c.B == 1 and awaiting then actions.rejectDownload() end
	if c.Y == 1 and awaiting then actions.detail() end
end)

document:AddEventListener("keyup", function(event)
	if tonumber(event.parameters.key_identifier) == 97 then dew.command("Game.TakeScreenshot") end
end)

document:AddEventListener("load", function()
	dew.command("Settings.Gamepad", {}):next(function(response) settingsArray["Settings.Gamepad"] = response end)
	for _, button in ipairs(document:QuerySelectorAll(".button[data-action]")) do
		local action = button:GetAttribute("data-action")
		button:AddEventListener("click", function() actions[action]() end)
	end
	el("windowCompact"):AddEventListener("click", maximize)
	el("mod_website"):AddEventListener("click", function()
		if websiteUrl == "" or websiteUrl:sub(1, 6) == "dew://" then return end
		local url = websiteUrl
		dew.dialog("confirm_link", { body = "This link goes to " .. url .. "|r|nAre you sure you want to open this?" }):next(function(result)
			if result == "yes" then dew.openUrl(url) end
		end)
	end)
end)
