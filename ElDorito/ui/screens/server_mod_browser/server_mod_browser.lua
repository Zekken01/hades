-- Port of screens/server_mod_browser/server_mod_browser.js: lists the mods offered by the
-- servers on the master lists (http://<server>/mods) for download.

local allMods = {}
local allLocalMods = {}
local displayedMods = {}
local previousSearch = ""
local selectedIndex = 0

local masterServers = {}
local serverBlacklistAPI = ""
local serverBlacklist = {}
local serverPingInterval = nil
local refreshVersion = 0
local refreshing = false
local visible = false
local mutexLock = false
local pingQueue = {}
local pingCounter = 0
local allMastersSeen = false
local gameVersion, gameVersionCompat = nil, nil
local websiteUrl = ""

local function el(id) return document:GetElementById(id) end
local function setText(id, text) el(id).inner_rml = dew.escape(tostring(text or "")) end
local function nowMs() return dew_core.getTime() * 1000 end
local function decode(text)
	local ok, value = pcall(json.decode, text)
	if ok then return value end
end
local function searchFocused() return document:QuerySelector("#searchbox:focus") ~= nil end
local function searchValue() return el("searchbox"):GetAttribute("value") or "" end

-- semantic versions (lib/version.js), compared without pre-release tags beyond the basics
local function parseSemver(version)
	local major, minor, patch, rest = tostring(version or ""):match("^(%d+)%.(%d+)%.(%d+)(.*)$")
	if not major then return nil end
	return { tonumber(major), tonumber(minor), tonumber(patch), rest:match("^%-([0-9A-Za-z%-%.]+)") or "" }
end

local function compareSemver(a, b)
	for i = 1, 3 do
		if a[i] ~= b[i] then return a[i] < b[i] and -1 or 1 end
	end
	if a[4] == b[4] then return 0 end
	if a[4] == "" then return 1 end
	if b[4] == "" then return -1 end
	return a[4] < b[4] and -1 or 1
end

local function isVersionCompatible(version)
	local v = parseSemver(version)
	if not v or not gameVersion or not gameVersionCompat then return false end
	return compareSemver(v, gameVersionCompat) >= 0 and compareSemver(v, gameVersion) <= 0
end

------------------------------------------------------------------------------------------
-- list

local function formatSize(size)
	size = tonumber(size) or 0
	if size == 0 then return "0 bytes" end
	local i = math.floor(math.log(size) / math.log(1024))
	local text = string.format("%.2f", size / (1024 ^ i)):gsub("0+$", ""):gsub("%.$", "")
	return text .. " " .. ({ "B", "kB", "MB", "GB", "TB" })[i + 1]
end

local function showModDetails(index)
	local mod = displayedMods[index]
	if mod and mod.hash and mod.hash ~= "" then
		setText("mod_name", mod.name)
		setText("mod_description", mod.description)
		setText("mod_author", mod.author)
		setText("mod_version", mod.version)
		setText("mod_source", mod.source)
		if not dew.truthy(mod.website) then
			setText("mod_website", "N/A")
			websiteUrl = ""
		else
			setText("mod_website", mod.website)
			websiteUrl = tostring(mod.website)
		end
		setText("mod_filesize", formatSize(mod.filesize))
	else
		for _, id in ipairs({ "mod_name", "mod_description", "mod_author", "mod_version", "mod_website", "mod_filesize", "mod_source" }) do
			setText(id, "")
		end
		websiteUrl = ""
	end
end

local function items() return el("mod_selection_list"):QuerySelectorAll(".li") end

local function setSelectedIndex(index)
	for i, item in ipairs(items()) do item:SetClass("selected", i == index) end
	selectedIndex = index
	showModDetails(index)
end

local function navigateList(direction)
	local count = #items()
	local newIndex = selectedIndex + direction
	if newIndex < 1 then
		newIndex = math.abs(direction) == 1 and count or 1
	elseif newIndex > count then
		newIndex = math.abs(direction) == 1 and 1 or count
	end
	setSelectedIndex(newIndex)
	local item = items()[newIndex]
	if item then item:ScrollIntoView(false) end
end

local function renderModList(mods)
	local parts = {}
	for i, mod in ipairs(mods) do
		parts[#parts + 1] = string.format('<div class="li" data-index="%d">%s<span class="name%s">%s</span>%s</div>', i,
			mod.downloaded and '<img class="downloadedIcon" src="dew://assets/dialog/checkbox.png"/>' or "",
			mod.downloaded and " downloaded" or "", dew.escape(tostring(mod.name or "")),
			(mod.hash and mod.hash ~= "") and ('<span class="version">v' .. dew.escape(tostring(mod.version or "")) .. "</span>") or "")
	end
	el("mod_selection_list").inner_rml = table.concat(parts)
	if selectedIndex > #mods then selectedIndex = 0 end
	for i, item in ipairs(items()) do item:SetClass("selected", i == selectedIndex) end
end

-- numbers/symbols first, then letters, case-insensitively
local function sortModsByName()
	table.sort(displayedMods, function(a, b)
		local nameA, nameB = tostring(a.name):lower(), tostring(b.name):lower()
		local aSpecial, bSpecial = not nameA:match("^%a"), not nameB:match("^%a")
		if aSpecial ~= bSpecial then return aSpecial end
		return nameA < nameB
	end)
end

local function populateMods()
	local search = searchValue():upper()
	displayedMods = {}
	for _, mod in ipairs(allMods) do
		if search == "" or tostring(mod.name):upper():find(search, 1, true) then
			displayedMods[#displayedMods + 1] = mod
		end
	end
	previousSearch = search
	for _, mod in ipairs(displayedMods) do
		mod.downloaded = false
		for _, localMod in ipairs(allLocalMods) do
			if localMod.hash == mod.hash then mod.downloaded = true end
		end
	end
	sortModsByName()
	renderModList(displayedMods)
end

------------------------------------------------------------------------------------------
-- servers

local function fetchJson(url, timeout)
	return dew.http(url, { timeout = timeout or 2000 }):next(function(response) return decode(response.body) end)
end

local function addModsToList(server, modList)
	for _, mod in pairs(modList or {}) do
		if type(mod) == "table" and mod.mod_name ~= nil and mod.mod_author ~= nil then
			local duplicate = false
			for _, existing in ipairs(allMods) do
				if existing.hash == mod.hash then duplicate = true end
			end
			if not duplicate then
				allMods[#allMods + 1] = {
					name = mod.mod_name, author = mod.mod_author, description = mod.mod_description, version = mod.mod_version,
					website = mod.mod_website, hash = mod.hash, source = server.name, filesize = mod.package_size,
					package_url = mod.package_url, source_ip = server.IP, host_player = server.hostPlayer,
				}
			end
		end
	end
	populateMods()
end

local function addServer(server)
	if not isVersionCompatible(server.version) then return end
	fetchJson("http://" .. server.IP .. "/mods", 4500):next(function(modList)
		if type(modList) == "table" then addModsToList(server, modList) end
	end):catch(function(err)
		console.error("Failed to fetch mod list from " .. tostring(server.IP) .. ": " .. tostring(err))
	end)
end

local function onRefreshStarted()
	el("refresh"):SetClass("refreshing", true)
	el("refreshLegendLink").inner_rml = "Stop"
	refreshing = true
end

local function onRefreshEnded()
	el("refresh"):SetClass("refreshing", false)
	el("refreshLegendLink").inner_rml = "Refresh"
	refreshing = false
	if serverPingInterval then
		dew.clearInterval(serverPingInterval)
		serverPingInterval = nil
	end
end

local function cancelRefresh()
	pingCounter = 0
	pingQueue = {}
	refreshVersion = refreshVersion + 1
	onRefreshEnded()
end

local function isBlacklisted(address)
	local host = address:match("^([^:]+)")
	for _, entry in ipairs(serverBlacklist) do
		entry = tostring(entry)
		if entry == host or (entry:find(":", 1, true) and address:find(entry, 1, true)) then return true end
	end
	return false
end

local function ping(info)
	return Promise.new(function(resolve, reject)
		dew.http("http://" .. info.server .. "/", { timeout = 4500 }):next(function(response)
			local data = decode(response.body)
			if type(data) ~= "table" or isBlacklisted(info.server) then reject() return end
			local numPlayers = tonumber(data.numPlayers) or -1
			if numPlayers < 0 or numPlayers > 16 or (type(data.players) == "table" and #data.players ~= numPlayers) then
				reject()
				return
			end
			local name = data.name
			if type(name) == "string" then name = name:gsub("[Hh][Tt][Tt][Pp]%S*", "") end
			resolve({
				type = dew.truthy(data.passworded) and "private" or "",
				IP = info.server,
				hostPlayer = data.hostPlayer,
				name = name,
				version = tostring(data.eldewritoVersion or ""):match("^(%d+%.%d+%.%d+)"),
			})
		end, reject)
	end)
end

local function serverPingProc()
	if allMastersSeen and pingCounter <= 0 then
		onRefreshEnded()
		return
	end
	local serverInfo = table.remove(pingQueue)
	if not serverInfo then return end
	ping(serverInfo):next(function(info)
		if refreshVersion == serverInfo.refreshVersion then addServer(info) end
	end):catch(function() end):finally(function() pingCounter = pingCounter - 1 end)
end

local function fetchMasters()
	local visited = {}
	local pending = #masterServers
	return Promise.new(function(resolve)
		if pending == 0 then resolve() return end
		for _, master in ipairs(masterServers) do
			fetchJson(master):next(function(data)
				for _, server in ipairs(data and data.result and data.result.servers or {}) do
					if not visited[server] then
						visited[server] = true
						pingCounter = pingCounter + 1
						pingQueue[#pingQueue + 1] = { server = server, refreshVersion = refreshVersion }
					end
				end
			end):catch(function(err) console.error(tostring(err)) end):finally(function()
				pending = pending - 1
				if pending == 0 then resolve() end
			end)
		end
	end)
end

local function refresh()
	if mutexLock then return end
	mutexLock = true
	cancelRefresh()
	refreshVersion = refreshVersion + 1
	serverBlacklist = {}
	onRefreshStarted()
	fetchJson(serverBlacklistAPI):next(function(resp)
		for _, server in ipairs((resp or {}).list or {}) do serverBlacklist[#serverBlacklist + 1] = server end
	end):catch(function(err) console.error(tostring(err)) end):finally(function()
		if not serverPingInterval and refreshing then
			serverPingInterval = dew.setInterval(serverPingProc, 25)
		end
		allMastersSeen = false
		fetchMasters():finally(function() allMastersSeen = true end)
		mutexLock = false
	end)
end

local function fetchAllServersAndMods()
	dew.command("Server.ListMods"):next(function(response)
		allLocalMods = decode(response) or {}
		allMods = {}
		dew.getVersion():next(function(version)
			dew.getVersionCompat():next(function(versionCompat)
				gameVersion = parseSemver(version)
				gameVersionCompat = parseSemver(versionCompat)
				refresh()
			end)
		end)
	end)
end

------------------------------------------------------------------------------------------
-- actions

local function hideScreen()
	dew.GameBlur("servermodbrowser", false)
	jq("#overlay"):fadeOut(150)
	jq("#screen_widget"):fadeOut(150, function() dew.hide() end)
end

local function handleBack()
	dew.playSound("b_button")
	hideScreen()
end

local function handleSelect(index)
	if index == -1 then index = selectedIndex end
	local mod = displayedMods[index]
	if not mod then return end
	if mod.downloaded then
		dew.playSound("error")
	else
		local payload = {}
		for k, v in pairs(mod) do payload[k] = v end
		dew.callMethod("modDownloadOption", { mod = payload })
		dew.playSound("a_button")
	end
end

local function handleUserRefresh()
	dew.playSound("x_button")
	if refreshing then cancelRefresh() else fetchAllServersAndMods() end
end

dew.input.on("action", function(e)
	local Actions = dew.input.Actions
	local typing = searchFocused()
	if e.action == Actions.X then
		if not typing then handleUserRefresh() end
	elseif e.action == Actions.A then
		if not typing then handleSelect(-1) end
	elseif e.action == Actions.B then
		if typing then el("searchbox"):Blur() else handleBack() end
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
	if axis == 0 then navigateList(((type == 2) and 4 or 1) * value) end
end)

dew.on("show", function()
	visible = true
	dew.GameBlur("servermodbrowser", true)
	jq("#overlay"):fadeIn(150)
	jq("#screen_widget"):fadeIn(150)
	fetchAllServersAndMods()
end)

dew.on("hide", function()
	el("mod_selection_list").inner_rml = ""
	selectedIndex = 0
	visible = false
end)

dew.on("modsEnumerated", function()
	if not visible then return end
	dew.command("Server.ListMods"):next(function(response)
		local mods = decode(response) or {}
		local before, after = {}, {}
		for _, mod in ipairs(allLocalMods) do before[mod.hash] = true end
		for _, mod in ipairs(mods) do after[mod.hash] = true end
		local changed = false
		for hash in pairs(before) do if not after[hash] then changed = true end end
		for hash in pairs(after) do if not before[hash] then changed = true end end
		if changed then fetchAllServersAndMods() end
	end)
end)

local function itemIndexOf(element)
	while element do
		if element:IsClassSet("li") then return tonumber(element:GetAttribute("data-index")) end
		if element.id == "mod_selection_list" then return nil end
		element = element.parent_node
	end
end

document:AddEventListener("keydown", function(event)
	local key = tonumber(event.parameters.key_identifier)
	if key == 91 or key == 93 or key == 86 or key == 87 then event:StopPropagation() end
	if visible and key ~= 35 and not searchFocused() and ((key >= 2 and key <= 37) or key == 69) then
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
	if tonumber(event.parameters.button) == 1 then handleBack() end
end)

document:AddEventListener("load", function()
	dew.command("server.getendpoint serverBlacklist"):next(function(resp)
		serverBlacklistAPI = resp .. "?t=" .. math.floor(nowMs())
	end)
	dew.command("server.getendpoint masterServers"):next(function(resp)
		masterServers = decode(resp) or {}
	end)
	el("mod_selection_list"):AddEventListener("mouseover", function(event)
		local index = itemIndexOf(event.target_element)
		if index and index ~= selectedIndex then setSelectedIndex(index) end
	end)
	el("searchbox"):AddEventListener("change", function()
		if searchValue():upper() ~= previousSearch then populateMods() end
	end)
	el("refresh"):AddEventListener("click", function()
		dew.playSound("x_button")
		if refreshing then cancelRefresh() else fetchAllServersAndMods() end
	end)
	el("button_key_select"):AddEventListener("click", function() handleSelect(-1) end)
	el("button_key_back"):AddEventListener("click", handleBack)
	el("button_key_refresh"):AddEventListener("click", handleUserRefresh)
	el("mod_website"):AddEventListener("click", function()
		if websiteUrl == "" or websiteUrl:sub(1, 6) == "dew://" then return end
		local url = websiteUrl
		dew.dialog("confirm_link", { body = "This link goes to " .. url .. "|r|nAre you sure you want to open this?" }):next(function(result)
			if result == "yes" then dew.openUrl(url) end
		end)
	end)
end)

-- debugging aid (harness)
function serverModsAdd(server, list) addModsToList(server, list) end
