-- Port of screens/browser (browser.js, list-widget.js, ui.js, lib/version.js).
-- React rendered the table; here rows are RML, rebuilt (throttled) when the list changes.

local playlists = { "all", "social", "ranked", "customs", "private", "forge" }

local pingQueue = {}
local pingCounter = 0
local model = {
	currentSortKey = "numPlayers",
	currentSortDir = "desc",
	currentServerList = {},
	currentFilter = "",
	currentPlaylist = "social",
	playerCount = 0,
	serverCount = 0,
}

local masterServers = {}
local officialServerAPI = ""
local serverBlacklistAPI = ""
local serverBlacklist = {}
local officialServers = {}
local refreshVersion = 0
local refreshing = false
local visible = false
local serverPingInterval = nil
local quickJoinIgnore = {}
local allMastersSeen = false
local usedBrowserCamera = false
local pins = {}
local hasGP = false
local updateNeeded = false
local mutexLock = false
local renderPending = false
local selectedIp = nil
local listFocused = true

local function el(id) return document:GetElementById(id) end
local function nowMs() return dew_core.getTime() * 1000 end
local function decode(text)
	local ok, value = pcall(json.decode, text)
	if ok then return value end
end

------------------------------------------------------------------------------------------
-- SemanticVersion (lib/version.js)

local SemanticVersion = {}

function SemanticVersion.parse(version)
	local major, minor, patch, rest = tostring(version or ""):match("^(%d+)%.(%d+)%.(%d+)(.*)$")
	if not major then error("Invalid semantic version: " .. tostring(version)) end
	local prerelease = rest:match("^%-([0-9A-Za-z%-%.]+)") or ""
	return { major = tonumber(major), minor = tonumber(minor), patch = tonumber(patch), prerelease = prerelease }
end

function SemanticVersion.compare(a, b)
	if a.major ~= b.major then return a.major < b.major and -1 or 1 end
	if a.minor ~= b.minor then return a.minor < b.minor and -1 or 1 end
	if a.patch ~= b.patch then return a.patch < b.patch and -1 or 1 end
	if a.prerelease == "" and b.prerelease == "" then return 0 end
	if a.prerelease ~= "" and b.prerelease == "" then return -1 end
	if a.prerelease == "" and b.prerelease ~= "" then return 1 end
	local i1, i2 = {}, {}
	for part in a.prerelease:gmatch("[^%.]+") do i1[#i1 + 1] = part end
	for part in b.prerelease:gmatch("[^%.]+") do i2[#i2 + 1] = part end
	for i = 1, math.min(#i1, #i2) do
		local x, y = i1[i], i2[i]
		local xn, yn = tonumber(x), tonumber(y)
		if (xn ~= nil) ~= (yn ~= nil) then return xn and -1 or 1 end
		local cmp
		if xn then cmp = xn - yn else cmp = (x < y and -1) or (x > y and 1) or 0 end
		if cmp ~= 0 then return cmp < 0 and -1 or 1 end
	end
	local cmp = #i1 - #i2
	if cmp == 0 then return 0 end
	return cmp < 0 and -1 or 1
end

------------------------------------------------------------------------------------------
-- dew.ui (ui.js): the browser's own input timings

local ui = { callbacks = {} }
ui.Actions = { LeftTrigger = 0, RightTrigger = 1, Up = 2, Down = 3, Left = 4, Right = 5, Start = 6, Select = 7,
	LeftStick = 8, RightStick = 9, A = 10, B = 11, X = 12, Y = 13, LeftBumper = 14, RightBumper = 15 }
do
	local HOLD_DELAY, HELD_SCROLL_SPEED, SINGLE_SCROLL_SPEED, AXIS = 0.5, 0.1, 0.125, 0.5
	local stickTicks = { left = 0, right = 0, up = 0, down = 0 }
	local lastHeldUpdate, lastScrollTime = 0, 0
	local keyStates, keyTicks = {}, {}
	-- Rml key identifiers: DOWN 93, UP 91, LEFT 90, RIGHT 92, SPACE 1, RETURN 72, ESCAPE 81,
	-- PRIOR 86, NEXT 87, DELETE 99, Q 28, E 16
	local KEYS = { [ui.Actions.Down] = { 93 }, [ui.Actions.Up] = { 91 }, [ui.Actions.Left] = { 90 }, [ui.Actions.Right] = { 92 },
		[ui.Actions.A] = { 1, 72 }, [ui.Actions.B] = { 81 }, [ui.Actions.LeftTrigger] = { 86 }, [ui.Actions.RightTrigger] = { 87 },
		[ui.Actions.Y] = { 99 }, [ui.Actions.LeftBumper] = { 28 }, [ui.Actions.RightBumper] = { 16 } }

	local function emit(eventName, ...)
		for _, cb in ipairs(ui.callbacks[eventName] or {}) do cb(...) end
	end

	function ui.on(eventName, callback)
		ui.callbacks[eventName] = ui.callbacks[eventName] or {}
		table.insert(ui.callbacks[eventName], callback)
	end

	function ui.keyDown(key) keyStates[key] = true end
	function ui.keyUp(key) keyStates[key] = false end

	function ui.reset()
		keyStates, keyTicks = {}, {}
		stickTicks = { left = 0, right = 0, up = 0, down = 0 }
		lastHeldUpdate, lastScrollTime = 0, 0
	end

	dew.on("controllerinput", function(e)
		local c = e.data or {}
		local spt = tonumber(c.secondsPerTick) or (1 / 60)
		local gameTicks = tonumber(c.gameTicks) or 0
		local function n(v) return tonumber(v) or 0 end
		emit("tick")
		for action, keys in pairs(KEYS) do
			local down = false
			for _, key in ipairs(keys) do if keyStates[key] then down = true end end
			if down then keyTicks[action] = (keyTicks[action] or 0) + 1 else keyTicks[action] = 0 end
		end
		local function kt(action) return keyTicks[action] or 0 end
		for k, v in pairs(stickTicks) do if v > 255 then stickTicks[k] = 255 end end
		local ax, ay = n(c.AxisLeftX), n(c.AxisLeftY)
		stickTicks.right = ax > AXIS and stickTicks.right + 1 or 0
		stickTicks.left = ax < -AXIS and stickTicks.left + 1 or 0
		stickTicks.up = ay > AXIS and stickTicks.up + 1 or 0
		stickTicks.down = ay < -AXIS and stickTicks.down + 1 or 0

		if n(c.LeftTrigger) == 1 or kt(ui.Actions.LeftTrigger) == 1 then emit("scroll", 2, 0, -1) end
		if n(c.RightTrigger) == 1 or kt(ui.Actions.RightTrigger) == 1 then emit("scroll", 2, 0, 1) end

		if (gameTicks - lastScrollTime) * spt > SINGLE_SCROLL_SPEED then
			if stickTicks.up == 1 or n(c.Up) == 1 or kt(ui.Actions.Up) == 1 then lastScrollTime = gameTicks; emit("scroll", 0, 0, -1) end
			if stickTicks.down == 1 or n(c.Down) == 1 or kt(ui.Actions.Down) == 1 then lastScrollTime = gameTicks; emit("scroll", 0, 0, 1) end
			if stickTicks.right == 1 or n(c.Right) == 1 or kt(ui.Actions.Right) == 1 then lastScrollTime = gameTicks; emit("scroll", 0, 1, 1) end
			if stickTicks.left == 1 or n(c.Left) == 1 or kt(ui.Actions.Left) == 1 then lastScrollTime = gameTicks; emit("scroll", 0, 1, -1) end
		end

		local function held(stick, button, action)
			return (stick > 1 and stick * spt > HOLD_DELAY) or (button > 1 and button * spt > HOLD_DELAY) or kt(action) * spt > HOLD_DELAY
		end
		if (gameTicks - lastHeldUpdate) * spt > HELD_SCROLL_SPEED then
			if held(stickTicks.up, n(c.Up), ui.Actions.Up) then lastHeldUpdate = gameTicks; emit("scroll", 1, 0, -1) end
			if held(stickTicks.down, n(c.Down), ui.Actions.Down) then lastHeldUpdate = gameTicks; emit("scroll", 1, 0, 1) end
			if held(stickTicks.right, n(c.Right), ui.Actions.Right) then lastHeldUpdate = gameTicks; emit("scroll", 1, 1, 1) end
			if held(stickTicks.left, n(c.Left), ui.Actions.Left) then lastHeldUpdate = gameTicks; emit("scroll", 1, 1, -1) end
		end

		for _, name in ipairs({ "A", "B", "X", "Y", "LeftBumper", "RightBumper", "Start", "Select" }) do
			if n(c[name]) == 1 then emit("action", { inputType = "controller", action = ui.Actions[name] }) end
		end
		for i = 0, 15 do
			if kt(i) == 1 then emit("action", { inputType = "keyboard", action = i }) end
		end
	end)

	dew.on("hide", function() ui.reset() end)
end

------------------------------------------------------------------------------------------
-- list widget (list-widget.js): selection over the rendered rows

local function rows() return el("serverListBody"):QuerySelectorAll(".tr") end

local function rowIndex(ip)
	for i, row in ipairs(rows()) do
		if row:GetAttribute("data-ip") == ip then return i end
	end
end

local function renderSelection()
	for _, row in ipairs(rows()) do
		row:SetClass("selected", selectedIp ~= nil and row:GetAttribute("data-ip") == selectedIp)
	end
end

local function setSelectedIndex(index, scrollTo)
	local list = rows()
	if #list == 0 then return -1 end
	if index > #list then index = 1 end -- wrapAround
	if index < 1 then index = #list end
	selectedIp = list[index]:GetAttribute("data-ip")
	renderSelection()
	if scrollTo then list[index]:ScrollIntoView(false) end
	return index
end

local function navigate(count)
	local oldIndex = selectedIp and rowIndex(selectedIp) or 0
	local newIndex = setSelectedIndex(oldIndex + count, true)
	if oldIndex ~= 0 and newIndex ~= -1 and oldIndex ~= newIndex then
		dew.playSound("vertical_navigation")
	end
end

------------------------------------------------------------------------------------------
-- rendering

local function sanitize(str)
	if str == nil or str == "" or str == json.null then return "Blam!" end
	str = tostring(str)
	if #str > 80 then str = str:sub(1, 80) .. "..." end
	return dew.escape(str)
end

local playlistFilters = {
	all = function(server) return server.type ~= "private" end,
	social = function(server) return server.type == "social" end,
	ranked = function(server) return server.type == "ranked" end,
	customs = function(server) return server.type ~= "ranked" and server.type ~= "social" and server.type ~= "private" end,
	private = function(server) return server.type == "private" end,
	forge = function(server)
		return server.type ~= "ranked" and server.type ~= "social" and server.type ~= "private" and server.variantType == "forge"
	end,
}

local function getServerView()
	local filter = playlistFilters[model.currentPlaylist]
	local list = {}
	for _, server in ipairs(model.currentServerList) do
		local haystack = (tostring(server.name) .. tostring(server.map) .. tostring(server.variant) .. tostring(server.variantType)):lower()
		if filter(server) and haystack:find(model.currentFilter, 1, true) then
			list[#list + 1] = server
		end
	end
	return list
end

local COLUMNS = {
	{ "name", "NAME" }, { "hostPlayer", "HOST" }, { "ping", "PING" }, { "map", "MAP" },
	{ "variantType", "GAMETYPE" }, { "variant", "VARIANT" }, { "numPlayers", "Players" }, { "version", "VERSION" },
}

local onSort -- forward

local function renderHead()
	local parts = {}
	for i, column in ipairs(COLUMNS) do
		local arrow = ""
		if model.currentSortKey == column[1] then
			-- the up/down triangle glyphs are not in the UI fonts: the arrow icon instead
			arrow = string.format('<img class="sortArrow%s" src="dew://assets/ux/arrow_down.svg"/>', model.currentSortDir == "asc" and " asc" or "")
		end
		parts[#parts + 1] = string.format('<div class="th c%d" data-key="%s">%s%s</div>', i, column[1], column[2], arrow)
	end
	local head = el("serverListHead")
	head.inner_rml = table.concat(parts)
	for _, th in ipairs(head:QuerySelectorAll(".th")) do
		local key = th:GetAttribute("data-key")
		th:AddEventListener("mousedown", function() onSort(key) end)
	end
end

local function render()
	renderPending = false
	local parts = {}
	for _, server in ipairs(getServerView()) do
		parts[#parts + 1] = string.format(
			'<div class="tr%s" data-ip="%s" data-type="%s"><div class="td c1">%s</div><div class="td c2">%s</div><div class="td c3">%s</div><div class="td c4">%s</div><div class="td c5">%s</div><div class="td c6">%s</div><div class="td c7">%s/%s</div><div class="td c8">%s</div></div>',
			server.pinned and " pinned" or "", dew.escape(server.IP), dew.escape(server.type),
			sanitize(server.name), sanitize(server.hostPlayer), tostring(server.ping), sanitize(server.map),
			sanitize(server.variantType), sanitize(server.variant), tostring(server.numPlayers), tostring(server.maxPlayers),
			sanitize(server.version))
	end
	el("serverListBody").inner_rml = table.concat(parts)
	renderHead()
	renderSelection()
	el("population").inner_rml = string.format("%d Players / %d Servers", model.playerCount, model.serverCount)
end

-- servers arrive every 25ms: rebuild the list at most every 200ms
local function scheduleRender()
	if renderPending then return end
	renderPending = true
	dew.setTimeout(render, 200)
end

local function compareServers(a, b)
	local key = model.currentSortKey
	local av, bv = a[key], b[key]
	if type(av) ~= type(bv) then av, bv = tostring(av), tostring(bv) end
	if av ~= bv then
		if model.currentSortDir == "asc" then return av < bv end
		return av > bv
	end
	return tostring(a.IP) > tostring(b.IP)
end

local function sortme(immediate)
	table.sort(model.currentServerList, compareServers)
	local top, rest = {}, {}
	for _, server in ipairs(model.currentServerList) do
		if server.pinned then top[#top + 1] = server else rest[#rest + 1] = server end
	end
	for _, server in ipairs(rest) do top[#top + 1] = server end
	model.currentServerList = top
	if immediate then render() else scheduleRender() end
end

onSort = function(key)
	if model.currentSortKey == key then
		model.currentSortDir = model.currentSortDir == "asc" and "desc" or "asc"
	else
		model.currentSortDir = "asc"
	end
	model.currentSortKey = key
	sortme(true)
end

local function selectPlaylist(playlist)
	for _, tab in ipairs(document:QuerySelectorAll("#playlistTabs a")) do
		tab:SetClass("active", tab:GetAttribute("data-playlist") == playlist)
	end
	model.currentPlaylist = playlist
	render()
end

local function navigatePlaylists(dir)
	local index
	for i, name in ipairs(playlists) do
		if name == model.currentPlaylist then index = i end
	end
	if not index then return end
	index = math.max(1, math.min(#playlists, index + dir))
	selectPlaylist(playlists[index])
	dew.playSound("horizontal_navigation")
end

------------------------------------------------------------------------------------------
-- refreshing

local function isVersionCompatible(version)
	local ok, v = pcall(SemanticVersion.parse, version)
	if not ok or not model.gameVersion or not model.gameVersionCompat then return false end
	return SemanticVersion.compare(v, model.gameVersionCompat) >= 0 and SemanticVersion.compare(v, model.gameVersion) <= 0
end

local function addServer(server)
	if not isVersionCompatible(server.version) then return end
	model.serverCount = model.serverCount + 1
	model.playerCount = model.playerCount + (tonumber(server.numPlayers) or 0)
	model.currentServerList[#model.currentServerList + 1] = server
	sortme(false)
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
	refreshVersion = refreshVersion + 1 -- answers still in flight are dropped
	onRefreshEnded()
end

local function isBlacklisted(address)
	local host = address:match("^([^:]+)")
	for _, entry in ipairs(serverBlacklist) do
		entry = tostring(entry)
		if entry == host then return true end
		if entry:find(":", 1, true) and address:find(entry, 1, true) then return true end
	end
	return false
end

local function parseVersion(str)
	return tostring(str or ""):match("^(%d+%.%d+%.%d+)")
end

local function ping(info)
	return Promise.new(function(resolve, reject)
		local startTime = nowMs()
		dew.http("http://" .. info.server .. "/", { timeout = 4500 }):next(function(response)
			local data = decode(response.body)
			if type(data) ~= "table" then reject("bad response") return end
			local pingMs = math.floor((nowMs() - startTime) * 0.45 + 0.5)
			local officialStatus = officialServers[info.server]
			if isBlacklisted(info.server) then reject("blacklisted") return end
			local numPlayers = tonumber(data.numPlayers) or -1
			if numPlayers < 0 or numPlayers > 16 or (type(data.players) == "table" and #data.players ~= numPlayers) then
				reject("bad player count")
				return
			end
			local name = data.name
			if type(name) == "string" then name = name:gsub("[Hh][Tt][Tt][Pp]%S*", "") end
			local serverType = ""
			if dew.truthy(data.passworded) then
				serverType = "private"
			elseif officialStatus then
				serverType = dew.truthy(officialStatus.ranked) and "ranked" or "social"
			end
			resolve({
				type = serverType,
				ping = pingMs,
				IP = info.server,
				hostPlayer = data.hostPlayer,
				map = data.map,
				variant = data.variant,
				variantType = data.variantType,
				name = name,
				numPlayers = numPlayers,
				maxPlayers = data.maxPlayers,
				pinned = pins[info.server] and true or false,
				version = parseVersion(data.eldewritoVersion),
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
	end):catch(function() end):finally(function()
		pingCounter = pingCounter - 1
	end)
end

local function fetchJson(url, timeout)
	return dew.http(url, { timeout = timeout or 2000 }):next(function(response)
		return decode(response.body)
	end)
end

local function fetchMasters()
	local visited = {}
	local pending = #masterServers
	return Promise.new(function(resolve)
		if pending == 0 then resolve() return end
		for _, master in ipairs(masterServers) do
			fetchJson(master, 4500):next(function(data)
				local servers = data and data.result and data.result.servers or {}
				for _, server in ipairs(servers) do
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
	model.currentServerList = {}
	model.playerCount = 0
	model.serverCount = 0
	serverBlacklist = {}
	officialServers = {}
	quickJoinIgnore = {}
	onRefreshStarted()

	local version = refreshVersion
	fetchJson(serverBlacklistAPI):next(function(resp)
		for _, server in ipairs((resp or {}).list or {}) do serverBlacklist[#serverBlacklist + 1] = server end
	end):catch(function(err) console.error(tostring(err)) end):finally(function()
		fetchJson(officialServerAPI):next(function(resp)
			for _, server in ipairs(resp or {}) do officialServers[server.address] = server end
		end):catch(function(err) console.error(tostring(err)) end):finally(function()
			if version ~= refreshVersion then mutexLock = false return end
			if not serverPingInterval and refreshing then
				serverPingInterval = dew.setInterval(serverPingProc, 25)
			end
			render()
			allMastersSeen = false
			fetchMasters():finally(function() allMastersSeen = true end)
			mutexLock = false
		end)
	end)
end

local function handleUserRefresh()
	dew.playSound("x_button")
	if refreshing then cancelRefresh() else refresh() end
end

local function closeBrowser()
	dew.hide()
end

local function handleUserCloseBrowser()
	dew.playSound("b_button")
	closeBrowser()
end

local function handleUserOpenLanBrowser()
	dew.playSound("a_button")
	dew.command("Game.ShowLocalServersUI")
	closeBrowser()
end

local function handleUserOpenServerModBrowser()
	dew.playSound("a_button")
	dew.command("Game.ShowServerModBrowser")
end

local function promptPassword(server)
	dew.dialog("server_password"):next(function(password)
		if password and #tostring(password) > 0 then
			dew.command("Server.connect " .. server .. ' "' .. tostring(password) .. '"')
			dew.playSound("a_button")
		end
	end)
end

local function joinSelected()
	local index = selectedIp and rowIndex(selectedIp)
	if not index then return end
	local row = rows()[index]
	if row:GetAttribute("data-type") == "private" then
		promptPassword(selectedIp)
	else
		dew.command("Server.connect " .. selectedIp)
		dew.playSound("a_button")
	end
end

local function quickJoin()
	local chosenServer, maxScore = nil, -1
	local list = {}
	for _, server in ipairs(getServerView()) do
		if (tonumber(server.numPlayers) or 0) < 16 and not quickJoinIgnore[server.IP] then list[#list + 1] = server end
	end
	table.sort(list, function(a, b) return a.ping < b.ping end)
	for _, server in ipairs(list) do
		local score = 1.0 - (server.ping / 3000.0) * 2.0 + server.numPlayers
		if score > maxScore then
			maxScore = score
			chosenServer = server
		end
	end
	if not chosenServer then return end
	quickJoinIgnore[chosenServer.IP] = true
	dew.command("Server.connect " .. chosenServer.IP)
	dew.playSound("a_button")
end

local function showUpdateDialog(info)
	dew.dialog("update_available"):next(function(result)
		if result == "" then
			dew.command("update"):catch(function()
				if info.updateUrl then
					dew.setTimeout(function() dew.openUrl(info.updateUrl) end, 450)
				end
				dew.dialog("missing_launcher")
			end)
		end
	end)
end

local function fetchNotice()
	dew.command("server.getendpoint browserNotice"):next(function(endpoint)
		return fetchJson(endpoint .. "?t=" .. math.floor(nowMs()), 4500)
	end):next(function(response)
		if type(response) ~= "table" then return end
		local ok, latest = pcall(SemanticVersion.parse, response.version)
		if ok and model.gameVersion and SemanticVersion.compare(latest, model.gameVersion) > 0 and not updateNeeded then
			updateNeeded = true
			showUpdateDialog(response)
		end
		local notice = el("notice")
		for _, kind in ipairs({ "info", "success", "warn", "error" }) do notice:SetClass(kind, false) end
		if type(response.notice) == "table" and response.notice.message then
			notice.inner_rml = dew.escape(tostring(response.notice.message))
			notice:SetClass("empty", false)
			notice:SetClass(response.notice.type or "info", true)
		else
			notice.inner_rml = ""
			notice:SetClass("empty", true)
		end
	end):catch(function(err) console.error("Failed to get status " .. tostring(err)) end)
end

------------------------------------------------------------------------------------------
-- events

ui.on("scroll", function(type, axis, direction)
	if not listFocused then return end
	if axis == 0 then
		if type < 2 then
			navigate(direction)
		elseif type == 2 then
			local list = rows()
			local index = selectedIp and rowIndex(selectedIp) or 1
			if (direction < 0 and index == 1) or (direction > 0 and index == #list) then return end
			local newIndex = math.max(1, math.min(#list, index + 4 * direction))
			dew.playSound("left_trigger")
			setSelectedIndex(newIndex, true)
		end
	end
end)

ui.on("action", function(evt)
	if not listFocused then return end -- typing in the search box
	local Actions = ui.Actions
	if evt.action == Actions.A then
		joinSelected()
	elseif evt.action == Actions.X then
		if evt.inputType ~= "keyboard" then handleUserRefresh() end
	elseif evt.action == Actions.B then
		closeBrowser()
		dew.playSound("b_button")
	elseif evt.action == Actions.Y then
		quickJoin()
	elseif evt.action == Actions.LeftBumper then
		navigatePlaylists(-1)
	elseif evt.action == Actions.RightBumper then
		navigatePlaylists(1)
	elseif evt.action == Actions.Start then
		handleUserOpenServerModBrowser()
	elseif evt.action == Actions.Select then
		handleUserOpenLanBrowser()
	end
end)

dew.on("show", function()
	visible = true
	usedBrowserCamera = false
	dew.getVersion():next(function(version)
		dew.getVersionCompat():next(function(versionCompat)
			local ok1, v = pcall(SemanticVersion.parse, version)
			local ok2, vc = pcall(SemanticVersion.parse, versionCompat)
			model.gameVersion = ok1 and v or nil
			model.gameVersionCompat = ok2 and vc or nil
			refresh()
			selectPlaylist(playlists[1])
			el("current_version").inner_rml = "Version: " .. dew.escape(tostring(version))
			fetchNotice()
		end)
	end)
	dew.command("Game.HideH3UI 1")
	document:SetClass("gamepad-enabled", true)
	dew.command("Server.LobbyType"):next(function(result)
		if tonumber(result) == -1 then
			dew.command("Game.ScenarioScript server_browser_cam")
			usedBrowserCamera = true
		end
	end)
	dew.command("Settings.Gamepad", {}):next(function(result) hasGP = tonumber(result) == 1 end)
end)

dew.on("hide", function()
	visible = false
	cancelRefresh()
	dew.command("Game.HideH3UI 0")
	dew.command("Server.LobbyType"):next(function(result)
		if tonumber(result) == -1 then dew.command("Game.ScenarioScript leave_server_browser") end
	end)
	usedBrowserCamera = false
end)

dew.on("serverconnect", function(event)
	local data = event.data or {}
	if data.connecting == false then dew.closeDialog("attempting_join") end
	if visible and dew.truthy(data.success) then
		if usedBrowserCamera then dew.command("Game.ScenarioScript leave_server_browser") end
		closeBrowser()
	end
end)

document:AddEventListener("keydown", function(event)
	local key = tonumber(event.parameters.key_identifier)
	ui.keyDown(key)
	local target = event.target_element
	if target and target.tag_name == "input" then return end
	-- space, arrows, page up/down: no scrolling or focus moves
	if key == 1 or (key >= 90 and key <= 93) or key == 86 or key == 87 then
		event:StopPropagation()
	end
end)

document:AddEventListener("keyup", function(event)
	local key = tonumber(event.parameters.key_identifier)
	ui.keyUp(key)
	if key == 97 then dew.command("Game.TakeScreenshot") end
end)

document:AddEventListener("mousedown", function(event)
	if visible and tonumber(event.parameters.button) == 1 then
		handleUserCloseBrowser()
	end
end)

document:AddEventListener("load", function()
	dew.command("server.getendpoint serverBlacklist"):next(function(resp)
		serverBlacklistAPI = resp .. "?t=" .. math.floor(nowMs())
	end)
	dew.command("server.getendpoint officialServers"):next(function(resp)
		officialServerAPI = resp .. "?t=" .. math.floor(nowMs())
	end)
	dew.command("server.getendpoint masterServers"):next(function(resp)
		masterServers = decode(resp) or {}
	end)

	-- rows: hover selects, left click joins (list-widget mousedown)
	local body = el("serverListBody")
	local function rowOf(element)
		while element and not element:IsClassSet("tr") do
			if element.id == "serverListBody" then return nil end
			element = element.parent_node
		end
		return element
	end
	body:AddEventListener("mousemove", function(event)
		if not listFocused then return end
		local row = rowOf(event.target_element)
		if row and row:GetAttribute("data-ip") ~= selectedIp then
			selectedIp = row:GetAttribute("data-ip")
			renderSelection()
		end
	end)
	body:AddEventListener("mousedown", function(event)
		if not listFocused or tonumber(event.parameters.button) ~= 0 then return end
		local row = rowOf(event.target_element)
		if row then
			selectedIp = row:GetAttribute("data-ip")
			renderSelection()
			joinSelected()
		end
	end)

	local filter = el("server-list-filter")
	filter:AddEventListener("change", function()
		model.currentFilter = (filter:GetAttribute("value") or ""):lower()
		sortme(true)
	end)
	filter:AddEventListener("focus", function() listFocused = false end)
	filter:AddEventListener("blur", function() listFocused = true end)

	el("refresh"):AddEventListener("click", function()
		dew.playSound("x_button")
		if refreshing then cancelRefresh() else refresh() end
	end)

	for _, tab in ipairs(document:QuerySelectorAll("#playlistTabs a")) do
		local playlist = tab:GetAttribute("data-playlist")
		tab:AddEventListener("mousedown", function(event)
			event:StopPropagation()
			if playlist == model.currentPlaylist then return end
			selectPlaylist(playlist)
			dew.playSound("horizontal_navigation")
		end)
	end

	el("joinBtn"):AddEventListener("click", joinSelected)
	el("refreshBtn"):AddEventListener("click", handleUserRefresh)
	el("quickjoinBtn"):AddEventListener("click", quickJoin)
	el("closeBtn"):AddEventListener("click", handleUserCloseBrowser)
	el("lanBtn"):AddEventListener("click", handleUserOpenLanBrowser)
	el("serverModBrowserBtn"):AddEventListener("click", handleUserOpenServerModBrowser)

	jq("#joinBtn img"):attr("src", "dew://assets/buttons/360_A.png")
	jq("#refreshBtn img"):attr("src", "dew://assets/buttons/360_X.png")
	jq("#quickjoinBtn img"):attr("src", "dew://assets/buttons/360_Y.png")
	jq("#closeBtn img"):attr("src", "dew://assets/buttons/360_B.png")
	jq("#lanBtn img"):attr("src", "dew://assets/buttons/360_Back.png")
	jq("#serverModBrowserBtn img"):attr("src", "dew://assets/buttons/360_Start.png")

	el("notice"):SetClass("empty", true)
	renderHead()
end)

-- debugging aid (harness)
function browserAddServer(server) addServer(server); render() end
