-- Port of screens/mod_info/mod_info.js

local currentModHash = ""
local locked = false
local websiteUrl = ""

local function el(id) return document:GetElementById(id) end
local function setText(id, text) el(id).inner_rml = dew.escape(tostring(text or "")) end

local function hideScreen()
	if locked then
		dew.notify("mod_browser_restore")
		locked = false
	end
	dew.GameBlur("modinfo", false)
	jq("#overlay"):fadeOut(150)
	jq("#screen_widget"):fadeOut(150, function() dew.hide() end)
end

local function handleBack()
	dew.playSound("b_button")
	hideScreen()
end

local function formatSize(size)
	size = tonumber(size) or 0
	if size == 0 then return "0 bytes" end
	local i = math.floor(math.log(size) / math.log(1024))
	local value = size / (1024 ^ i)
	local text = string.format("%.2f", value):gsub("0+$", ""):gsub("%.$", "")
	return text .. " " .. ({ "B", "kB", "MB", "GB", "TB" })[i + 1]
end

local function convertTimestampToDisplay(timestamp)
	timestamp = tonumber(timestamp) or 0
	if timestamp == 0 then return "Never" end
	local d = os.date("*t", timestamp)
	local hours = d.hour % 12
	if hours == 0 then hours = 12 end
	return string.format("%02d/%02d/%04d %02d:%02d %s", d.month, d.day, d.year, hours, d.min, d.hour >= 12 and "pm" or "am")
end

local function showModDetails(mod)
	local preview = el("mod_preview_img")
	if type(mod) == "table" and mod.hash then
		setText("mod_name", tostring(mod.name or ""):upper())
		setText("mod_description", mod.description)
		setText("mod_author", mod.author)
		setText("mod_version", mod.version)
		setText("mod_types", (dew.truthy(mod.mainmenuType) and "Mainmenu " or "") .. (dew.truthy(mod.characterType) and "Character " or "")
			.. (dew.truthy(mod.multiplayerType) and "Multiplayer " or "") .. (dew.truthy(mod.campaignType) and "Campaign " or "")
			.. (dew.truthy(mod.firefightType) and "Firefight" or ""))
		setText("mod_lastuseddate", convertTimestampToDisplay(mod.lastUsedDate))
		if not dew.truthy(mod.website) then
			setText("mod_website", "N/A")
			websiteUrl = ""
		else
			setText("mod_website", mod.website)
			websiteUrl = tostring(mod.website)
		end
		setText("mod_filesize", formatSize(mod.filesize))
		setText("mod_source", dew.truthy(mod.source) and mod.source or "User Downloaded")
		setText("mod_dowloaddate", mod.downloadDate)
		dew.getAssetUrl("preview", { pak = mod.hash, fileTypes = { "jpg", "png" }, searchBaseAssets = false }):next(function(url)
			preview:SetAttribute("src", url ~= "" and url or "dew://assets/maps/small/placeholder.jpg")
		end)
	else
		for _, id in ipairs({ "mod_name", "mod_description", "mod_author", "mod_version", "mod_types", "mod_website",
			"mod_filesize", "mod_source", "mod_dowloaddate", "mod_lastuseddate" }) do
			setText(id, "")
		end
		websiteUrl = ""
		preview:SetAttribute("src", "dew://assets/maps/small/placeholder.jpg")
	end
end

-- the small markdown subset the web page rendered (headings, bold, italic, bullets) as RML
local function renderMarkdown(markdown)
	markdown = dew.escape(markdown):gsub("\r", "")
	local lines = {}
	for line in (markdown .. "\n"):gmatch("(.-)\n") do
		local level, text = line:match("^(#+) (.+)$")
		if level and #level <= 4 then
			line = string.format("<h%d>%s</h%d>", #level, text, #level)
		end
		lines[#lines + 1] = line
	end
	markdown = table.concat(lines, "<br/>")
	markdown = markdown:gsub("%*%*(.-)%*%*", "<b>%1</b>"):gsub("%*(.-)%*", "<i>%1</i>"):gsub("<br/>%-", "<br/>&#x2022;")

	dew.command("Input.DumpBindingsJson"):next(function(response)
		local ok, bindDump = pcall(json.decode, response)
		dew.command("Settings.Gamepad"):next(function(gamepad)
			if ok and type(bindDump) == "table" then
				for _, bind in ipairs(bindDump) do
					local key = gamepad == "1" and bind.controllerButton or bind.primaryKey
					local pattern = "&lt;" .. tostring(bind.actionName):gsub("%p", "%%%0") .. "&gt;"
					markdown = markdown:gsub(pattern, "&lt;" .. tostring(key):gsub("%%", "%%%%") .. "&gt;")
				end
			end
			el("mod_description").inner_rml = markdown
		end)
	end)
end

local function updateCurrentMod(hash, done)
	hash = hash or ""
	dew.command("Server.ListModInfo" .. (hash ~= "" and (" " .. hash) or "")):next(function(modInfo)
		local mod = ""
		if modInfo ~= "" then
			local ok, value = pcall(json.decode, modInfo)
			if ok then mod = value end
		end
		currentModHash = type(mod) == "table" and tostring(mod.hash or "") or ""
		showModDetails(mod)
		if currentModHash ~= "" then
			dew.getAssetUrl("readme", { pak = mod.hash, fileTypes = { "md" }, searchBaseAssets = false }):next(function(readmePath)
				if readmePath ~= "" then
					local text = dew.readFile(readmePath)
					if text then
						renderMarkdown(text)
					else
						console.error("There was a problem fetching the mod readme: " .. readmePath)
					end
				end
			end)
		end
		if done then done() end
	end)
end

dew.on("show", function(e)
	local data = e.data or {}
	locked = false
	local function reveal()
		dew.GameBlur("modinfo", true)
		jq("#overlay"):fadeIn(150)
		jq("#screen_widget"):fadeIn(150)
	end
	if dew.truthy(data.hash) then
		locked = true
		updateCurrentMod(data.hash, reveal)
	else
		updateCurrentMod("", function()
			if currentModHash == "" then -- no mod loaded
				dew.hide()
				return
			end
			dew.playSound("a_button")
			reveal()
		end)
	end
end)

dew.input.on("action", function(e)
	if e.action == dew.input.Actions.B then handleBack() end
end)

local deadzone = 0.3
dew.on("controllerinput", function(e)
	local c = e.data or {}
	local ly, ry = tonumber(c.AxisLeftY) or 0, tonumber(c.AxisRightY) or 0
	local amount
	if math.abs(ly) > deadzone then amount = ly elseif math.abs(ry) > deadzone then amount = ry end
	if amount then
		local section = el("description_section")
		section.scroll_top = section.scroll_top - math.floor(amount * 100 + 0.5) / 100 * 7
	end
end)

document:AddEventListener("keyup", function(event)
	if tonumber(event.parameters.key_identifier) == 97 then dew.command("Game.TakeScreenshot") end
end)

document:AddEventListener("mouseup", function(event)
	if tonumber(event.parameters.button) == 1 then handleBack() end
end)

document:AddEventListener("load", function()
	el("backButton"):AddEventListener("click", handleBack)
	el("mod_website"):AddEventListener("click", function()
		if websiteUrl == "" or websiteUrl:sub(1, 6) == "dew://" then return end
		local url = websiteUrl
		dew.dialog("confirm_link", { body = "This link goes to " .. url .. "|r|nAre you sure you want to open this?" }):next(function(result)
			if result == "yes" then dew.openUrl(url) end
		end)
	end)
end)
