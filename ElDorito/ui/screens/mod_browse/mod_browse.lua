-- Port of screens/mod_browse (mod_browse.js, list_controller.js)

local allMods = {}
local displayedMods = {}
local lobbyType = -1
local filterIndex = 1
local selectBlocked = false
local displayFilterIndex = 0 -- 0: unset
local requiresRefresh = true
local previousSearch = ""
local selectedIndex = 0 -- 1-based, 0: none
local visible = false

local displayFilters = { "all", "last used", "latest" }

local filters = {
	{ displayText = "Mainmenu", canSelect = function() return lobbyType == -1 end, modFilter = function(mod) return dew.truthy(mod.mainmenuType) end, defaultCommand = "Game.MainMenuMod" },
	{ displayText = "Character", alternateDisplayText = "Mainmenu", canSelect = function() return lobbyType == -1 end, modFilter = function(mod) return dew.truthy(mod.characterType) end, defaultCommand = "Game.MainMenuMod" },
	{ displayText = "Campaign", canSelect = function() return lobbyType == 0 end, modFilter = function(mod) return dew.truthy(mod.campaignType) end, defaultCommand = "Game.CampaignMod" },
	{ displayText = "Multiplayer", canSelect = function() return lobbyType == 2 or lobbyType == 3 end, modFilter = function(mod) return dew.truthy(mod.multiplayerType) end, defaultCommand = "Game.MultiplayerMod" },
	{ displayText = "Firefight", canSelect = function() return lobbyType == 5 end, modFilter = function(mod) return dew.truthy(mod.firefightType) end, defaultCommand = "Game.FirefightMod" },
}

local function el(id) return document:GetElementById(id) end
local function setText(id, text) el(id).inner_rml = dew.escape(tostring(text or "")) end
local function searchFocused() return document:QuerySelector("#searchbox:focus") ~= nil end
local function searchValue() return el("searchbox"):GetAttribute("value") or "" end

local websiteUrl = ""

local function formatSize(size)
	size = tonumber(size) or 0
	if size == 0 then return "0 bytes" end
	local i = math.floor(math.log(size) / math.log(1024))
	local text = string.format("%.2f", size / (1024 ^ i)):gsub("0+$", ""):gsub("%.$", "")
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

local function showModDetails(index)
	local preview = el("mod_preview_img")
	local mod = displayedMods[index]
	if mod and mod.hash ~= "" and mod.hash ~= nil then
		setText("mod_name", mod.name)
		setText("mod_description", mod.description)
		setText("mod_author", mod.author)
		setText("mod_version", mod.version)
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
		if mod.preview then
			preview:SetAttribute("src", mod.preview)
		else
			dew.getAssetUrl("preview", { pak = mod.hash, fileTypes = { "jpg", "png" }, searchBaseAssets = false }):next(function(url)
				mod.preview = url ~= "" and url or "dew://assets/maps/small/placeholder.jpg"
				if displayedMods[selectedIndex] == mod then preview:SetAttribute("src", mod.preview) end
			end)
		end
	else
		for _, id in ipairs({ "mod_name", "mod_description", "mod_author", "mod_version", "mod_website", "mod_filesize",
			"mod_source", "mod_dowloaddate", "mod_lastuseddate" }) do
			setText(id, "")
		end
		websiteUrl = ""
		preview:SetAttribute("src", "dew://assets/maps/small/placeholder.jpg")
	end
end

-- list controller
local function items() return el("mod_selection_list"):QuerySelectorAll(".li") end

local function setSelectedIndex(index)
	local list = items()
	for i, item in ipairs(list) do item:SetClass("selected", i == index) end
	selectedIndex = index
	showModDetails(index)
end

local function scrollIntoView()
	local item = items()[selectedIndex]
	if item then item:ScrollIntoView(false) end
end

local function navigateList(direction)
	local count = #items()
	local newIndex = selectedIndex + direction
	if newIndex < 1 then
		newIndex = math.abs(direction) == 1 and count or 1 -- wrapAround
	elseif newIndex > count then
		newIndex = math.abs(direction) == 1 and 1 or count
	end
	setSelectedIndex(newIndex)
end

local function renderModList(mods)
	local parts = {}
	for i, mod in ipairs(mods) do
		parts[#parts + 1] = string.format('<div class="li" data-index="%d"><span class="name">%s</span>%s</div>', i,
			dew.escape(tostring(mod.name or "")), (mod.hash and mod.hash ~= "") and ('<span class="version">v' .. dew.escape(tostring(mod.version or "")) .. "</span>") or "")
	end
	el("mod_selection_list").inner_rml = table.concat(parts)
	if #mods > 0 then setSelectedIndex(1) else selectedIndex = 0 end
	scrollIntoView()
end

local function compareVersion(a, b)
	if a == b then return 0 end
	local av, bv = {}, {}
	for part in tostring(a):gmatch("[^%.]+") do av[#av + 1] = part end
	for part in tostring(b):gmatch("[^%.]+") do bv[#bv + 1] = part end
	for i = 1, math.min(#av, #bv) do
		local x, y = tonumber(av[i]) or 0, tonumber(bv[i]) or 0
		if x > y then return 1 end
		if x < y then return -1 end
	end
	if #av > #bv then return 1 end
	if #av < #bv then return -1 end
	return 0
end

local function populateMods()
	local none = { name = "NONE", description = "", version = "", website = "", author = "", hash = "", filename = "", filesize = 0,
		mainmenuType = true, multiplayerType = true, campaignType = true, firefightType = true }
	local filter = filters[filterIndex]
	local search = searchValue():upper()
	local filtered = {}
	for _, mod in ipairs(allMods) do
		if filter.modFilter(mod) and (search == "" or tostring(mod.name):upper():find(search, 1, true)) then
			filtered[#filtered + 1] = mod
		end
	end
	previousSearch = search

	displayedMods = {}
	if filter.canSelect() then displayedMods[1] = none end
	for _, mod in ipairs(filtered) do displayedMods[#displayedMods + 1] = mod end

	if displayFilters[displayFilterIndex] == "latest" then
		-- one entry per name+author: the newest version, in order of first appearance
		local groups, order = {}, {}
		for _, mod in ipairs(displayedMods) do
			local key = tostring(mod.name) .. tostring(mod.authorUid)
			if not groups[key] then
				groups[key] = mod
				order[#order + 1] = key
			elseif compareVersion(groups[key].version, mod.version) ~= 1 then
				groups[key] = mod
			end
		end
		displayedMods = {}
		for _, key in ipairs(order) do displayedMods[#displayedMods + 1] = groups[key] end
	end
	if displayFilters[displayFilterIndex] == "last used" then
		for i, mod in ipairs(displayedMods) do mod._order = i end
		table.sort(displayedMods, function(a, b)
			local at, bt = tonumber(a.lastUsedDate) or 0, tonumber(b.lastUsedDate) or 0
			if at ~= bt then return at > bt end
			return a._order < b._order
		end)
	end
	renderModList(displayedMods)
end

local function fetchAndDisplayMods(done)
	dew.command("Server.ListMods"):next(function(response)
		local ok, mods = pcall(json.decode, response)
		allMods = ok and type(mods) == "table" and mods or {}
		populateMods()
		if done then done() end
	end)
end

local function setFilter(index)
	filterIndex = index
	setText("screen_widget_mod_type", filters[index].displayText)
	if filters[index].canSelect() then
		el("button_key_select").style.display = "flex"
		selectBlocked = false
	else
		el("button_key_select").style.display = "none"
		selectBlocked = true
	end
end

local function setDisplayFilter(index)
	displayFilterIndex = index
	setText("current_display_filter", "[" .. displayFilters[index % #displayFilters + 1] .. "]")
end

local function rotateModFilter(direction)
	dew.playSound("left_bumper")
	local index = filterIndex + direction
	if index < 1 then index = #filters elseif index > #filters then index = 1 end
	setFilter(index)
	populateMods()
end

local function rotateDisplayFilter()
	dew.playSound("a_button")
	setDisplayFilter(displayFilterIndex % #displayFilters + 1)
	populateMods()
end

local function hideScreen()
	dew.GameBlur("modbrowser", false)
	jq("#overlay"):fadeOut(150)
	jq("#screen_widget"):fadeOut(150, function() dew.hide() end)
end

local function tempHideScreen()
	dew.GameBlur("modbrowser", false)
	dew.captureInput(false)
	jq("#overlay"):fadeOut(150)
	jq("#screen_widget"):fadeOut(150)
end

local function restoreScreen()
	dew.captureInput(true)
	dew.GameBlur("modbrowser", true)
	jq("#overlay"):fadeIn(150)
	jq("#screen_widget"):fadeIn(150)
end

local function label(filter) return filter.alternateDisplayText or filter.displayText end

local function handleOptions(index)
	local mod = displayedMods[index]
	if not mod then return end
	dew.playSound("x_button")
	local filter = filters[filterIndex]
	if mod.hash == "" then
		dew.dialog("mod_options", {
			body = "You can remove the default mod package.",
			options = json.array({ { label = "Remove " .. label(filter) .. " Default", value = "default", default = true } }),
		}):next(function(result)
			if result == "default" then
				dew.command(filter.defaultCommand .. " none")
				dew.command("WriteConfig")
			end
		end)
		return
	end
	dew.command(filter.defaultCommand):next(function(response)
		local modIsDefault = response == mod.filename
		local defaultString = (modIsDefault and "Remove " or "Set as ") .. label(filter) .. " Default"
		dew.dialog("mod_options", {
			body = "You can set this mod package as default or delete it from your PC.",
			options = json.array({
				{ label = defaultString, value = "default", default = true },
				{ label = "View Mod Info", value = "modinfo" },
				{ label = "Delete " .. tostring(mod.name), value = "delete" },
			}),
		}):next(function(result)
			if result == "delete" then
				dew.dialog("confirm_mod_delete", { body = 'Are you sure you want to delete "' .. tostring(mod.name) .. '"?' }):next(function(answer)
					if answer == "yes" then
						dew.command('Server.DeleteMod "' .. tostring(mod.filename) .. '"'):next(function()
							fetchAndDisplayMods(function()
								if modIsDefault then
									dew.command(filter.defaultCommand .. " none")
									dew.command("WriteConfig")
								end
							end)
						end)
					end
				end)
			elseif result == "default" then
				if modIsDefault then
					dew.command(filter.defaultCommand .. " none")
				else
					dew.command(filter.defaultCommand .. ' "' .. tostring(mod.filename) .. '"')
				end
				dew.command("WriteConfig")
			elseif result == "modinfo" then
				tempHideScreen()
				dew.show("mod_info", { hash = mod.hash })
			end
		end)
	end)
end

local function handleSelect(index)
	if selectBlocked then
		handleOptions(index == -1 and selectedIndex or index)
		return
	end
	dew.playSound("a_button")
	if index == -1 then index = selectedIndex end
	local mod = displayedMods[index]
	if mod then
		if filterIndex == 1 or filterIndex == 2 then
			dew.command('Game.MainMenuMod "' .. tostring(mod.filename) .. '"')
			dew.command("WriteConfig")
		else
			dew.command('Server.Mod "' .. tostring(mod.filename) .. '"')
		end
		hideScreen()
	end
end

local function handleBack()
	dew.playSound("b_button")
	hideScreen()
end

dew.input.on("action", function(e)
	local Actions = dew.input.Actions
	local typing = searchFocused()
	if e.action == Actions.A then
		if not typing then handleSelect(-1) end
	elseif e.action == Actions.B then
		if typing then el("searchbox"):Blur() else handleBack() end
	elseif e.action == Actions.X then
		if not typing then handleOptions(selectedIndex) end
	elseif e.action == Actions.Left or e.action == Actions.LeftBumper then
		if not typing then rotateModFilter(-1) end
	elseif e.action == Actions.Right or e.action == Actions.RightBumper then
		if not typing then rotateModFilter(1) end
	elseif e.action == Actions.Y then
		if not typing then rotateDisplayFilter() end
	end
end)

dew.input.on("scroll", function(type, axis, value)
	if #items() == 0 then return end
	local sounds = { "vertical_navigation", "horizontal_navigation", "left_bumper", "right_bumper" }
	if type == 2 then
		dew.playSound(sounds[type + axis + 1])
	elseif axis ~= 1 then
		dew.playSound(sounds[axis + 1])
	end
	if searchFocused() then el("searchbox"):Blur() end
	if axis == 0 then
		navigateList(((type == 2) and 4 or 1) * value)
		scrollIntoView()
	end
end)

dew.on("show", function()
	visible = true
	dew.GameBlur("modbrowser", true)
	jq("#overlay"):fadeIn(150)
	jq("#screen_widget"):fadeIn(150)
	dew.command("Server.LobbyType"):next(function(response)
		local newLobbyType = tonumber(response) or -1
		local lobbyChanged = newLobbyType ~= lobbyType
		lobbyType = newLobbyType
		if requiresRefresh or lobbyChanged then
			requiresRefresh = false
			if lobbyType == 2 or lobbyType == 3 then setFilter(4)
			elseif lobbyType == 0 then setFilter(3)
			elseif lobbyType == 5 then setFilter(5)
			else setFilter(1) end
			if displayFilterIndex == 0 then setDisplayFilter(3) end
			fetchAndDisplayMods()
		end
	end)
	dew.command("Settings.gamepad"):next(function(gamepad)
		local controller = tonumber(gamepad) == 1
		el("mod_filter"):SetClass("ctrlr", controller)
		el("mod_filter"):SetClass("kbm", not controller)
		el("filterLeft"):SetAttribute("src", controller and "dew://assets/buttons/360_LB.png" or "dew://assets/ux/arrow_left.svg")
		el("filterRight"):SetAttribute("src", controller and "dew://assets/buttons/360_RB.png" or "dew://assets/ux/arrow_right.svg")
	end)
end)

dew.on("hide", function() visible = false end)
dew.on("modsEnumerated", function() requiresRefresh = true end)
dew.on("mod_changed", function() requiresRefresh = true end)
dew.on("mod_browser_restore", function() restoreScreen() end)

local function itemIndexOf(element)
	while element do
		if element:IsClassSet("li") then return tonumber(element:GetAttribute("data-index")) end
		if element.id == "mod_selection_list" then return nil end
		element = element.parent_node
	end
end

document:AddEventListener("keydown", function(event)
	local key = tonumber(event.parameters.key_identifier)
	-- arrows/page keys only navigate
	if key == 91 or key == 93 or key == 86 or key == 87 then event:StopPropagation() end
	-- any other key types into the search box
	local ignore = { [1] = true, [93] = true, [90] = true, [92] = true, [91] = true, [99] = true, [72] = true, [81] = true,
		[87] = true, [86] = true, [35] = true, [70] = true, [97] = true }
	if visible and not ignore[key] and not searchFocused() and ((key >= 2 and key <= 37) or key == 69) then
		el("searchbox"):Focus()
	end
end)

document:AddEventListener("keyup", function(event)
	if tonumber(event.parameters.key_identifier) == 97 then dew.command("Game.TakeScreenshot") end
end)

document:AddEventListener("mousedown", function(event)
	if tonumber(event.parameters.button) == 0 then
		local index = itemIndexOf(event.target_element)
		if index then handleSelect(index) end
	end
end)

document:AddEventListener("mouseup", function(event)
	if tonumber(event.parameters.button) == 1 then
		local index = itemIndexOf(event.target_element)
		if index then handleOptions(index) else handleBack() end
	end
end)

document:AddEventListener("load", function()
	local list = el("mod_selection_list")
	list:AddEventListener("mouseover", function(event)
		local index = itemIndexOf(event.target_element)
		if index and index ~= selectedIndex then setSelectedIndex(index) end
	end)
	el("searchbox"):AddEventListener("change", function()
		if searchValue():upper() ~= previousSearch then populateMods() end
	end)
	el("filterLeft"):AddEventListener("click", function() rotateModFilter(-1) end)
	el("filterRight"):AddEventListener("click", function() rotateModFilter(1) end)
	el("button_key_select"):AddEventListener("click", function() handleSelect(-1) end)
	el("button_key_back"):AddEventListener("click", handleBack)
	el("button_key_options"):AddEventListener("click", function() handleOptions(selectedIndex) end)
	el("button_key_display"):AddEventListener("click", rotateDisplayFilter)
	el("mod_website"):AddEventListener("click", function()
		if websiteUrl == "" or websiteUrl:sub(1, 6) == "dew://" then return end
		local url = websiteUrl
		dew.dialog("confirm_link", { body = "This link goes to " .. url .. "|r|nAre you sure you want to open this?" }):next(function(result)
			if result == "yes" then dew.openUrl(url) end
		end)
	end)
end)
