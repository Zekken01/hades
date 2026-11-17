-- Port of screens/scoreboard/scoreboard.js.  The Vue app (rows, team rows, header) is
-- rendered from Lua into #window whenever its state changes.

local ingameVoteWidget = nil
local cachedPlayersInfo = nil
local repGP
local hasGP = false
local itemNumber = 0
local axisThreshold = 0.5
local stickTicks = { left = 0, right = 0, up = 0, down = 0 }
local medalSelection = 0
local cardOpacity = 0.9
local lastHeldUpdated = 0
local playerVolumes = {} -- voip activity per player name
local isVisible = false
local localPlayer = ""
local breakdownPlayer = ""
local cachedPlayerList = {}
local disconnectedPlayers = {}
local showDisconnectedPlayers = false

local showHideTimeout
local initalKeyboardKey = false
local initialShowTimout = false
local initialControllerKey = false
local animationStarted = false

local settingsArray = { ["Settings.Gamepad"] = "0" }
local settingsOrder = { "Settings.Gamepad" }

-- KI values
local KI_TAB, KI_T, KI_Y, KI_OEM_3, KI_F1, KI_OEM_8, KI_ESCAPE, KI_SNAPSHOT = 70, 31, 36, 44, 107, 49, 81, 97
local KI_F19 = 125

-- ----------- constants

local GAME_ENGINE_TYPE_CTF, GAME_ENGINE_TYPE_ODDBALL, GAME_ENGINE_TYPE_KOTH = 1, 3, 4
local GAME_ENGINE_TYPE_VIP, GAME_ENGINE_TYPE_JUGGERNAUT = 6, 7
local GAME_ENGINE_TYPE_ASSAULT, GAME_ENGINE_TYPE_INFECTION = 9, 10

local TEAM_DEFINITIONS = {
	{ name = "Red Team", color = "#620B0B" },
	{ name = "Blue Team", color = "#0B2362" },
	{ name = "Green Team", color = "#1F3602" },
	{ name = "Orange Team", color = "#BC4D00" },
	{ name = "Purple Team", color = "#1D1052" },
	{ name = "Gold Team", color = "#A77708" },
	{ name = "Brown Team", color = "#1C0D02" },
	{ name = "Pink Team", color = "#FF4D8A" },
}

local weaponDetails = {
	generic_melee = "Generic Melee", carbine = "Covenant Carbine", guardians_unknown = "Guardians",
	guardians = "Guardians", falling_damage = "Falling Damage", generic_collision = "Generic Collision",
	armor_lock_crush = "Armor Lock Crush", generic_explosion = "Generic Explosion", magnum = "Magnum",
	plasma_pistol = "Plasma Pistol", needler = "Needler", mauler = "Mauler", smg = "SMG",
	plasma_rifle = "Plasma Rifle", battle_rifle = "Battle Rifle", shotgun = "Shotgun",
	sniper_rifle = "Sniper Rifle", beam_rifle = "Beam Rifle", assault_rifle = "Assault Rifle",
	spiker = "Spiker", fuel_rod_cannon = "Fuel Rod Cannon", missile_pod = "Missile Pod",
	rocket_launcher = "Rocket Launcher", spartan_laser = "Spartan Laser", brute_shot = "Brute Shot",
	flamethrower = "Flamethrower", sentinel_gun = "Sentinel Gun", energy_sword = "Energy Sword",
	gravity_hammer = "Gravity Hammer", frag_grenade = "Frag Grenade", plasma_grenade = "Plasma Grenade",
	spike_grenade = "Spike Grenade", firebomb_grenade = "Firebomb Grenade", flag = "Flag", bomb = "Bomb",
	bomb_explosion = "Bomb Explosion", ball = "Ball", machinegun_turret = "Machinegun Turret",
	plasma_cannon = "Plasma Cannon", plasma_mortar = "Plasma Mortar", plasma_turret = "Plasma Turret",
	shade_turret = "Shade Turret", banshee = "Banshee", ghost = "Ghost", mongoose = "Mongoose",
	scorpion = "Scorpion", scorpion_gunner = "Scorpion Gunner", spectre = "Spectre",
	spectre_gunner = "Spectre Gunner", warthog = "Warthog", warthog_gunner = "Warthog Gunner",
	warthog_gauss_turret = "Warthog Gauss Turret", wraith = "Wraith", wraith_gunner = "Wraith Gunner",
	tank = "Tank", chopper = "Chopper", hornet = "Hornet", mantis = "Mantis", prowler = "Prowler",
	sentinel_beam = "Sentinel Beam", sentinel_rpg = "Sentinel RPG", teleporter = "Teleporter",
	tripmine = "Tripmine", dmr = "DMR",
}

local medalDetails = {
	Unknown1 = { "Unknown1", "Last Man Standing?" },
	Unknown4 = { "Unknown4", "Flag Kill?" },
	perfection = { "Perfection!", "Win a Slayer game without dying with at least 15 kills." },
	extermination = { "Extermination!", "Wipe out an enemy team with at least an overkill." },
	killing_spree = { "Killing Spree!", "Kill 5 opponents in a row without dying." },
	killing_frenzy = { "Killing Frenzy!", "Kill 10 opponents in a row without dying." },
	running_riot = { "Running Riot!", "Kill 15 opponents in a row without dying." },
	rampage = { "Rampage!", "Kill 20 opponents in a row without dying." },
	untouchable = { "Untouchable!", "Kill 25 opponents in a row without dying." },
	invincible = { "Invincible!", "Kill 30 opponents in a row without dying." },
	shotgun_spree = { "Shotgun Spree!", "Kill 5 opponents in a row with the shotgun without dying." },
	sword_spree = { "Sword Spree!", "Kill 5 opponents in a row with the Energy Sword without dying." },
	sniper_spree = { "Sniper Spree!", "Kill 5 opponents in a row with a sniper weapon without dying." },
	splatter_spree = { "Splatter Spree!", "Splatter 5 opponents in a row using a vehicle without dying." },
	open_season = { "Open Season!", "Kill 10 opponents in a row with the shotgun without dying." },
	slice_n_dice = { "Slice n Dice!", "Kill 10 opponents in a row with the Energy Sword without dying." },
	sharpshooter = { "Sharpshooter!", "Kill 10 opponents in a row with a sniper weapon without dying." },
	vehicular_manslaughter = { "Vehicular Manslaughter!", "Splatter 10 opponents in a row using a vehicle without dying." },
	double_kill = { "Double Kill!", "Kill 2 opponents within 4 seconds of each other." },
	triple_kill = { "Triple Kill!", "Kill 3 opponents within 4 seconds of each other." },
	overkill = { "Overkill!", "Kill 4 opponents within 4 seconds of each other." },
	killtacular = { "Killtacular!", "Kill 5 opponents within 4 seconds of each other." },
	killtrocity = { "Killtrocity!", "Kill 6 opponents within 4 seconds of each other." },
	killimanjaro = { "Killimanjaro!", "Kill 7 opponents within 4 seconds of each other." },
	killtastrophe = { "Killtastrophe!", "Kill 8 opponents within 4 seconds of each other." },
	killpocalypse = { "Killpocalypse!", "Kill 9 opponents within 4 seconds of each other." },
	killionaire = { "Killionaire!", "Kill 10 opponents within 4 seconds of each other." },
	beat_down = { "Beat Down!", "Hit and kill an opponent with a melee attack." },
	assassin = { "Assassin!", "Hit and kill an opponent with a melee attack from behind." },
	sniper_kill = { "Sniper Kill!", "Kill an opponent with a Sniper Rifle or the Beam Rifle." },
	grenade_stick = { "Grenade Stick!", "Kill an opponent by sticking them with a sticky or brute grenade." },
	laser_kill = { "Laser Kill!", "Kill an opponent by using the Spartan Laser." },
	oddball_kill = { "Oddball Kill!", "Get a melee kill when holding the oddball." },
	flag_kill = { "Flag Kill!", "Get a melee kill with the flag." },
	splatter = { "Splatter!", "Hit and kill an opponent with your vehicle." },
	incineration = { "Incineration!", "Kill an opponent with a flame-based weapon." },
	killjoy = { "Killjoy!", "End an opponents killing spree." },
	from_the_grave = { "Death from the Grave!", "Kill an opponent after you have died." },
	hijacker = { "Highjacker!", "Board a land-based vehicle by forcibly removing the opponent in it." },
	bulltrue = { "Bulltrue!", "Kill an opponent that is in the act of a sword lunge." },
	wheelman = { "Wheelman!", "Be the driver of a vehicle when a passenger kills an opponent." },
	skyjacker = { "Skyjacker!", "Board an aircraft by forcibly removing the opponent in it." },
	flag_carrier_kill = { "Killed Flag Carrier!", "Kill the opponent flag carrier in CTF." },
	flag_captured = { "Flag Score!", "Score the flag in CTF." },
	juggernaut_kill = { "Killed Juggernaut!", "Kill the Juggernaut in a Juggernaut game." },
	vip_kill = { "Killed VIP!", "Kill an opponents VIP in a VIP game." },
	bomb_carrier_kill = { "Killed Bomb Carrier!", "Kill an opponent bomb carrier in Assault." },
	bomb_planted = { "Bomb Planted!", "Plant the bomb in Assault." },
	last_man_standing = { "Last Man Standing!", "Be the last human in an infection game." },
	hail_to_the_king = { "Hail to the King!", "Kill 5 opponents in a row from inside the hill before it moves." },
	infection_spree = { "Infection Spree! ", "Kill 5 humans in a row as the zombie without dying." },
	zombie_killing_spree = { "Zombie Killing Spree!", "Kill 5 zombies in a row as the human without dying." },
	juggernaut_spree = { "Juggernaut Spree!", "Kill 5 opponents in a row as the Juggernaut without dying." },
	mmm_brains = { "Mmmm Brains!", "Kill 10 humans in a row as the zombie without dying." },
	hells_janitor = { "Hells Janitor!", "Kill 10 zombies in a row as the human without dying." },
	unstoppable = { "Unstoppable!", "Kill 10 opponents in a row as the Juggernaut without dying." },
	steaktacular = { "Steaktacular!", "Luke owes you a steak dinner." },
	linktacular = { "Linktacular!", "Play in a matchmade game comprised of all Bungie.net users." },
	vehicle_kill = { "Killed Vehicle!", "Destroy an enemy vehicle." },
	headshot = { "Headshot!", "Kill an enemy with a headshot." },
}

-- ----------- app state (the Vue data)

local appState = {
	valid = false,
	gameId = -1,
	rows = {},
	playerRows = {},
	hasTeams = false,
	expanded = false,
	locked = false,
	multiround = false,
	roundCount = 0,
	currentRound = 0,
	roundOver = false,
	maxPlayers = 0,
	playerCount = 0,
	gameFinished = false,
	gameTied = false,
	gameType = 0,
	lobbyType = 0,
	isHost = false,
	selectedPlayer = nil,
	selectedPlayerVolume = 0,
	selectedPlayerMuted = false,
	playerVolumes = {}, -- "name|uid" -> level
	pregame = false,
}

local session = nil
local scores = nil

local function el(id) return document:GetElementById(id) end
local function esc(value) return dew.escape(tostring(value == nil and "" or value)) end
local function truthy(value) return dew.truthy(value) end

local function isLobby()
	return appState.lobbyType == 0 or appState.lobbyType == 5
end

local function breakdownVisible()
	return jq("#playerBreakdown"):isVisible()
end

local function getSessionInfo(callback)
	dew.getSessionInfo():next(callback)
end

local function playerUid(info)
	return info and info.playerInfo and info.playerInfo.Uid
end

-- ----------- rendering

local function statColumns()
	local gameType = appState.gameType
	if gameType == GAME_ENGINE_TYPE_CTF then
		return { { "Kills", "kills" }, { "Flag Kills", "flagKills" } }
	elseif gameType == GAME_ENGINE_TYPE_ODDBALL then
		return { { "Kills", "kills" }, { "Ball Kills", "ballKills" } }
	elseif gameType == GAME_ENGINE_TYPE_KOTH then
		return { { "Kills", "kills" }, { "King Kills", "kingsKilled" }, { "Time In Hill", "timeInHill" }, { "Controlling", "timeControllingHill" } }
	end
	return { { "Kills", "kills" }, { "Assists", "assists" }, { "Deaths", "deaths" }, { "Best Streak", "bestStreak" } }
end

local function showStats()
	return appState.expanded and not isLobby()
end

local function teamNameColumnSpan()
	local span = 3
	if appState.expanded then
		local gameType = appState.gameType
		if gameType == GAME_ENGINE_TYPE_KOTH then span = span + 4
		elseif gameType == GAME_ENGINE_TYPE_ODDBALL or gameType == GAME_ENGINE_TYPE_CTF then span = span + 2
		else span = span + 4 end
	end
	return span
end

local function hasSpoken(name)
	local voip = playerVolumes[name]
	return voip ~= nil and voip.hasSpoken == true
end

local OBJECTIVE_EMBLEMS = {
	[GAME_ENGINE_TYPE_ODDBALL] = "oddball", [GAME_ENGINE_TYPE_CTF] = "ctf", [GAME_ENGINE_TYPE_ASSAULT] = "assault",
	[GAME_ENGINE_TYPE_VIP] = "vip", [GAME_ENGINE_TYPE_JUGGERNAUT] = "juggernaut",
}

local function rowPlace(row, forTeams)
	if row.place == nil or (tonumber(row.place) or -1) < 0 then
		return ""
	end
	if appState.hasTeams ~= forTeams then
		return ""
	end
	return tostring(math.tointeger(row.place + 1) or (row.place + 1))
end

local function rowClasses(row, base)
	local classes = { base }
	if row.startHidden and not animationStarted then
		classes[#classes + 1] = "hidden"
	end
	return table.concat(classes, " ")
end

-- A <tr> background in the browser paints only behind its cells (the border-spacing gaps stay
-- clear); RmlUi paints the whole row.  Move the row's inline colour onto its cells.
local function spreadRowColor(rml)
	local attrs, color, rest = rml:match('^<tr([^>]-) style="background%-color: ([^;"]+);">(.*)$')
	if not color then return rml end
	return '<tr' .. attrs .. '>' .. (rest:gsub('<td', '<td style="background-color: ' .. color .. ';"'))
end

local function renderTeamRow(row)
	local parts = {}
	parts[#parts + 1] = string.format('<tr class="%s" style="background-color: %s;">', rowClasses(row, "player teamHeader"), row.color)
	parts[#parts + 1] = '<td class="rank">' .. esc(rowPlace(row, true)) .. "</td>"
	parts[#parts + 1] = string.format('<td class="name teamName" colspan="%d">%s</td>', teamNameColumnSpan(), esc(row.name))
	parts[#parts + 1] = '<td class="score">' .. esc(appState.multiround and row.total or row.score) .. "</td>"
	if appState.multiround then
		parts[#parts + 1] = '<td class="score">' .. esc(row.score) .. "</td>"
	end
	parts[#parts + 1] = "</tr>"
	return table.concat(parts)
end

local function renderPlayerRow(row, clickIndex)
	local color = appState.hasTeams and (TEAM_DEFINITIONS[(tonumber(row.teamIndex) or 0) + 1] or {}).color or row.color
	local classes
	if row.disconnected then
		classes = "disconnected player"
	else
		classes = "player clickable"
	end
	if appState.selectedPlayer and appState.selectedPlayer.id == row.id then
		classes = classes .. " selected"
	end
	local parts = {}
	parts[#parts + 1] = string.format('<tr class="%s" data-row="%s" style="background-color: %s;">',
		rowClasses(row, classes), esc(row.id), tostring(color or "transparent"))
	parts[#parts + 1] = '<td class="rank">' .. (isLobby() and "" or esc(rowPlace(row, false))) .. "</td>"
	parts[#parts + 1] = string.format('<td class="playerName name" colspan="%d">', row.rank ~= -1 and 1 or 2)

	if row.hasObjective then
		local gameType = appState.gameType
		local objective = OBJECTIVE_EMBLEMS[gameType]
		if gameType == GAME_ENGINE_TYPE_INFECTION then
			objective = row.isAlpha and "alpha" or "infected"
		end
		if objective then
			parts[#parts + 1] = '<img class="emblem gameObjective" src="dew://assets/emblems/' .. objective .. '.png"/>'
		end
	end
	if row.isDead then
		parts[#parts + 1] = '<img class="emblem player-emblem" src="dew://assets/emblems/dead.png"/>'
	else
		local emblem = tostring(row.emblem or "")
		if emblem == "" then
			emblem = "dew://assets/emblems/generic.png"
		end
		parts[#parts + 1] = '<img class="emblem player-emblem" src="' .. esc(emblem) .. '"/>'
	end
	parts[#parts + 1] = esc(row.name)

	local voip = playerVolumes[row.name]
	local speakerClass = "emblem speaker"
	if hasSpoken(row.name) then
		speakerClass = speakerClass .. " talking"
	end
	if row.hasObjective then
		speakerClass = "hasSpokenObjective " .. speakerClass
	end
	parts[#parts + 1] = string.format('<img class="%s" data-name="%s" src="%s"/>', speakerClass, esc(row.name),
		esc(voip and voip.speaker or "dew://assets/emblems/speaker-off.png"))
	if row.isHost then
		parts[#parts + 1] = '<img class="emblem crown" src="dew://assets/emblems/crown.png"/>'
	end
	parts[#parts + 1] = "</td>"

	parts[#parts + 1] = '<td class="serviceTag">' .. esc(row.stag) .. "</td>"
	if row.rank ~= -1 then
		parts[#parts + 1] = string.format('<td class="playerRank"><img class="rankimg" data-pak="game" data-url="assets/ranks/%s" data-fallback="dew://assets/ranks/%s.svg"/></td>',
			esc(row.rank), esc(row.rank))
	end
	if showStats() then
		for _, column in ipairs(statColumns()) do
			parts[#parts + 1] = '<td class="stat">' .. esc(row[column[2]]) .. "</td>"
		end
	end
	local ping = ""
	if row.showPing and row.ping ~= "" then
		ping = '<img class="player-ping" src="' .. esc(row.ping) .. '"/>'
	end
	if not isLobby() then
		parts[#parts + 1] = '<td class="score">' .. esc(appState.multiround and row.total or row.score) .. (appState.multiround and "" or ping) .. "</td>"
	end
	if appState.multiround then
		parts[#parts + 1] = '<td class="score">' .. esc(row.score) .. ping .. "</td>"
	end
	parts[#parts + 1] = "</tr>"
	return table.concat(parts)
end

local wireRows -- forward

local function renderWindow()
	local window = el("window")
	if not appState.valid then
		window.style.display = "none"
		return
	end
	window.style.display = "block"
	window:SetClass("expanded", appState.expanded)
	local parts = {}
	if appState.gameFinished then
		if appState.gameTied then
			parts[#parts + 1] = '<div id="winnerText"><span class="winner">Tie!</span></div>'
		else
			local first = appState.rows[1]
			parts[#parts + 1] = '<div id="winnerText"><span class="winner">' .. esc(first and first.name or "") .. " wins!</span></div>"
		end
	elseif appState.multiround then
		if appState.roundOver then
			parts[#parts + 1] = '<div id="roundText"><span class="round">ROUND OVER</span></div>'
		else
			parts[#parts + 1] = string.format('<div id="roundText"><span class="round">Round %s of %s</span></div>', esc(appState.currentRound), esc(appState.roundCount))
		end
	end
	-- column widths: RmlUi takes them from <col>s (the header's first cells span columns); the
	-- CSS widths were content widths, + the 1px cell padding on each side.  An HTML table widens
	-- a column to fit its content (a 4-letter service tag needs ~68px); RmlUi's do not, so the
	-- service tag column takes 10dp from the name column.  A row without a rank image spans
	-- its name over the service tag column and puts the tag in the rank column, so when no row
	-- has a rank that column is the tag's.
	local anyRank = false
	for _, row in ipairs(appState.rows) do
		if row.type ~= 1 and row.rank ~= -1 then anyRank = true end
	end
	if anyRank then
		parts[#parts + 1] = '<table class="scoreboard"><col style="width: 27dp;"/><col style="width: 256dp;"/><col style="width: 70dp;"/><col style="width: 32dp;"/>'
	else
		parts[#parts + 1] = '<table class="scoreboard"><col style="width: 27dp;"/><col style="width: 254dp;"/><col style="width: 0dp;"/><col style="width: 70dp;"/>'
	end
	if showStats() then
		parts[#parts + 1] = string.rep('<col style="width: 72dp;"/>', #statColumns())
	end
	parts[#parts + 1] = '<thead><tr id="header"><th class="rank"></th>'
	parts[#parts + 1] = string.format('<th class="headerText name" colspan="3" style="padding-left: 5dp;">Players (%s/%s)</th>', esc(appState.playerCount), esc(appState.maxPlayers))
	if showStats() then
		for _, column in ipairs(statColumns()) do
			parts[#parts + 1] = '<th class="headerText">' .. column[1] .. "</th>"
		end
	end
	if not isLobby() then
		parts[#parts + 1] = '<th class="headerText score">Score</th>'
	end
	if appState.multiround then
		parts[#parts + 1] = '<th class="headerText score">Round</th>'
	end
	parts[#parts + 1] = '</tr></thead><tbody id="playerList">'
	for _, row in ipairs(appState.rows) do
		if row.type == 1 then
			parts[#parts + 1] = spreadRowColor(renderTeamRow(row))
		else
			parts[#parts + 1] = spreadRowColor(renderPlayerRow(row))
		end
	end
	parts[#parts + 1] = "</tbody></table>"
	el("windowContent").inner_rml = table.concat(parts)
	el("gameStarting").style.display = appState.pregame and "block" or "none"
	wireRows()
	for _, image in ipairs(window:QuerySelectorAll(".rankimg")) do
		pakAwareContext.invalidateElement(image)
	end
	if hasGP and appState.locked then
		local rows = window:QuerySelectorAll(".clickable")
		local row = rows[itemNumber + 1]
		if row then
			row:SetClass("gpselected", true)
		end
	end
end

local function findRow(id)
	for _, row in ipairs(appState.rows) do
		if row.id == id then
			return row
		end
	end
end

-- ----------- voip volume

local function setPlayerVolume(name, uid, level)
	local id = name .. "|" .. uid
	dew.show("voip", { volume = { uid = id, vol = level / 100.0 } })
	appState.playerVolumes[id] = level
	local currentVol = -100
	if playerVolumes[name] then
		currentVol = math.max(tonumber(playerVolumes[name].currentVoice) or -100, -100)
	end
	appState.selectedPlayerMuted = (tonumber(level) == 0)
	appState.selectedPlayerVolume = level
	dew.callMethod("playerVoipLevelChanged", { name = name, uid = uid, peerLevel = level / 100.0, currentVolume = currentVol })
end

local function toggleMuteSelectedPlayer(row)
	getSessionInfo(function(result)
		if playerUid(result) == row.uid then
			dew.playSound("error")
			return
		end
		local id = row.name .. "|" .. row.uid
		local vol = 0
		if tostring(appState.playerVolumes[id]) == "0" then
			vol = 100
		end
		dew.show("voip", { volume = { uid = id, vol = vol / 100.0 } })
		appState.playerVolumes[id] = vol
		local currentVol = -100
		if playerVolumes[row.name] then
			currentVol = math.max(tonumber(playerVolumes[row.name].currentVoice) or -100, -100)
		end
		dew.callMethod("playerVoipLevelChanged", { name = row.name, uid = row.uid, peerLevel = vol / 100.0, currentVolume = currentVol })
	end)
end

-- ----------- context menu

local function closePlayerContextMenu()
	appState.selectedPlayer = nil
	jq("#contextMenuOverlay"):hide()
	renderWindow()
end

-- page coordinates (dp) of a context mouse position
local function pageCoordinates(x, y)
	local width, height = document.offset_width, document.offset_height
	local ratio = math.min(width / 1280, height / 720)
	if ratio <= 0 then
		ratio = 1
	end
	return (x - (width - 1280 * ratio) / 2) / ratio, (y - (height - 720 * ratio) / 2) / ratio
end

local function openPlayerContextMenu(event, row)
	if row.disconnected then
		dew.playSound("error")
		return
	end
	local mouseX, mouseY = tonumber(event.parameters.mouse_x) or 0, tonumber(event.parameters.mouse_y) or 0
	getSessionInfo(function(result)
		if playerUid(result) == row.uid then
			dew.playSound("error")
			return
		end
		appState.selectedPlayer = row
		local voipID = row.name .. "|" .. row.uid
		appState.selectedPlayerVolume = appState.playerVolumes[voipID] or 100
		appState.selectedPlayerMuted = tonumber(appState.selectedPlayerVolume) == 0

		jq("#menuBan"):toggle(appState.isHost)
		jq("#menuKick"):toggle(appState.isHost)
		jq("#menuVoteKick"):toggle(not appState.isHost)
		jq("#menuMute"):text(appState.selectedPlayerMuted and "Unmute" or "Mute")
		el("menuVolumeSlider"):SetAttribute("value", tostring(appState.selectedPlayerVolume))
		local x, y = pageCoordinates(mouseX, mouseY)
		local menu = el("scoreboardContextMenu")
		menu.style.left = string.format("%.1fdp", x)
		menu.style.top = string.format("%.1fdp", y)
		jq("#contextMenuOverlay"):show()
		renderWindow()
	end)
end

-- ----------- player breakdown

local function closePlayerBreakdown(sound)
	breakdownPlayer = ""
	jq("#playerBreakdown"):hide()
	if sound then
		dew.playSound("b_button")
	end
end

local function getPlayerIndex(name)
	for x, player in ipairs(appState.playerRows) do
		if player.name == name then
			return x - 1
		end
	end
end

local function hexToRgb(hex, opacity)
	hex = tostring(hex or "#000000")
	local r = tonumber(hex:sub(2, 3), 16) or 0
	local g = tonumber(hex:sub(4, 5), 16) or 0
	local b = tonumber(hex:sub(6, 7), 16) or 0
	return string.format("rgba(%d, %d, %d, %d)", r, g, b, math.floor(opacity * 255 + 0.5))
end

local function sortedByCount(map, valueKey)
	local list = {}
	for key, value in pairs(map or {}) do
		list[#list + 1] = { key = key, value = value }
	end
	table.sort(list, function(a, b)
		local av = valueKey and tonumber(a.value[valueKey]) or tonumber(a.value) or 0
		local bv = valueKey and tonumber(b.value[valueKey]) or tonumber(b.value) or 0
		if av ~= bv then
			return av > bv
		end
		return tostring(a.key) < tostring(b.key)
	end)
	return list
end

local function setBigMedal(name, withFallback)
	local image = el("bigMedalImage")
	image:SetAttribute("data-pak", "game")
	image:SetAttribute("data-url", "assets/medals/" .. name)
	if withFallback then
		image:SetAttribute("data-fallback", "dew://assets/emblems/generic.png")
	end
	pakAwareContext.invalidateElement(image)
	local details = medalDetails[name] or { name, "" }
	jq(".medalName"):text(details[1])
	jq(".medalDesc"):text(details[2])
end

local playerBreakdown -- forward

local function killTableRow(tableId, entry)
	local enemyIndex = getPlayerIndex(entry.PlayerName)
	local bgColor = "#C0C0C0"
	if enemyIndex then
		bgColor = appState.playerRows[enemyIndex + 1].color or bgColor
	end
	local body = el(tableId):QuerySelector("tbody")
	body.inner_rml = string.format('<tr class="player" style="background-color: %s;"><td class="killName">%s</td><td class="killCount">%s</td></tr>',
		hexToRgb(bgColor, 0.9), esc(entry.PlayerName), esc(entry.Kills))
	local name = entry.PlayerName
	body:QuerySelector("tr"):AddEventListener("click", function()
		playerBreakdown(name)
	end)
end

local breakdownNavigation = { previous = nil, next = nil }

playerBreakdown = function(name)
	breakdownPlayer = name
	local playerIndex = getPlayerIndex(name)
	if not playerIndex then
		return
	end
	local currentPlayer = appState.playerRows[playerIndex + 1]
	local color = hexToRgb(currentPlayer.color, cardOpacity)
	local emblemPath = currentPlayer.emblem
	local info = cachedPlayersInfo and cachedPlayersInfo[(tonumber(currentPlayer.playerIndex) or -1) + 1]
	if info and truthy(info.e) then
		emblemPath = info.e
	end
	if not truthy(emblemPath) then
		emblemPath = "dew://assets/emblems/generic.png"
	end

	breakdownNavigation.previous = nil
	breakdownNavigation.next = nil
	el("previousPlayer"):SetClass("disabled", playerIndex == 0)
	if playerIndex > 0 then
		breakdownNavigation.previous = appState.playerRows[playerIndex].name
	end
	el("nextPlayer"):SetClass("disabled", playerIndex == #appState.playerRows - 1)
	if playerIndex < #appState.playerRows - 1 then
		breakdownNavigation.next = appState.playerRows[playerIndex + 2].name
	end

	dew.getStats(name):next(function(stats)
		stats = stats or {}
		jq("#playerBreakdown"):show()
		medalSelection = 0
		local rank = tonumber(stats.playerrank) or -1
		local nameElement = el("playerName")
		nameElement.inner_rml = '<img class="emblem player-emblem" src="' .. esc(emblemPath) .. '"/>'
			.. (rank ~= -1 and ('<img class="player-rank" src="dew://assets/ranks/' .. rank .. '.svg"/>') or "")
			.. esc(name)
		nameElement.style["background-color"] = color

		local weapons = sortedByCount(stats.weapons, "Kills")
		local kills, deaths, suicides = 0, 0, 0
		for _, weapon in ipairs(weapons) do
			kills = kills + (tonumber(weapon.value.Kills) or 0)
			deaths = deaths + (tonumber(weapon.value.KilledBy) or 0)
			suicides = suicides + (tonumber(weapon.value.SuicidesWith) or 0)
		end
		jq("#playerKills"):text("Kills: " .. kills)
		jq("#playerDeaths"):text("Deaths: " .. deaths)
		jq("#playerKDSpread"):text("K/D Spread: " .. (kills - deaths))
		jq("#playerSuicides"):text("Suicides: " .. suicides)

		local tool = el("toolOfDestruction"):QuerySelector("tbody")
		local top = weapons[1]
		if top and (tonumber(top.value.Kills) or 0) ~= 0 then
			tool.inner_rml = string.format("<tr><td>%s</td><td>Kills: %s</td></tr>", esc(weaponDetails[top.key] or top.key), esc(top.value.Kills))
		else
			tool.inner_rml = "<tr><td>None</td></tr>"
		end

		local function bestOf(list)
			local best
			for _, entry in ipairs(list or {}) do
				if not best or (tonumber(entry.Kills) or 0) > (tonumber(best.Kills) or 0) then
					best = entry
				end
			end
			return best
		end
		local killed = bestOf(stats.playerkilledplayer)
		jq("#killedMost"):toggle(killed ~= nil)
		if killed then killTableRow("killedMost", killed) end
		local killedBy = bestOf(stats.playerkilledby)
		jq("#killedMostBy"):toggle(killedBy ~= nil)
		if killedBy then killTableRow("killedMostBy", killedBy) end

		local medals = sortedByCount(stats.medals)
		if medals[1] and (tonumber(medals[1].value) or 0) ~= 0 then
			setBigMedal(medals[1].key, false)
		else
			local image = el("bigMedalImage")
			image:RemoveAttribute("data-pak")
			image:RemoveAttribute("data-url")
			image:RemoveAttribute("data-fallback")
			image:RemoveAttribute("src")
			jq(".medalName"):text("")
			jq(".medalDesc"):text("")
		end

		local box = el("medalBox")
		local rml = {}
		local count = 0
		for i = 1, 10 do
			local medal = medals[i]
			if medal and (tonumber(medal.value) or 0) ~= 0 then
				count = count + 1
				rml[#rml + 1] = string.format('<div class="medal" data-medal="%s"><span class="medalCount">x %s</span><img class="medalImage" data-pak="game" data-url="assets/medals/%s"/></div>',
					esc(medal.key), esc(medal.value), esc(medal.key))
			end
		end
		for _ = 1, 10 - count do
			rml[#rml + 1] = '<div class="medal empty"></div>'
		end
		box.inner_rml = table.concat(rml)
		for _, medal in ipairs(box:QuerySelectorAll(".medal")) do
			local key = medal:GetAttribute("data-medal")
			if key then
				medal:AddEventListener("mouseover", function() setBigMedal(key, false) end)
			end
		end
		for _, image in ipairs(box:QuerySelectorAll(".medalImage")) do
			pakAwareContext.invalidateElement(image)
		end
	end)
end

-- ----------- rows: click / right click / speaker

wireRows = function()
	for _, rowElement in ipairs(el("window"):QuerySelectorAll("tr[data-row]")) do
		local id = rowElement:GetAttribute("data-row")
		rowElement:AddEventListener("click", function()
			local row = findRow(id)
			if not row or row.disconnected then
				return
			end
			if breakdownVisible() and breakdownPlayer == row.name then
				return -- prevent opening after the same screen has already been opened
			end
			playerBreakdown(row.name)
			dew.playSound("a_button")
		end)
		rowElement:AddEventListener("mousedown", function(event)
			if tonumber(event.parameters.button) == 1 then
				local row = findRow(id)
				if row then
					openPlayerContextMenu(event, row)
				end
			end
		end)
		local speaker = rowElement:QuerySelector(".speaker")
		if speaker then
			speaker:AddEventListener("click", function(event)
				event:StopPropagation()
				local row = findRow(id)
				if row then
					toggleMuteSelectedPlayer(row)
				end
			end)
		end
	end
end

-- ----------- update

local function merge(...)
	local result = {}
	for i = 1, select("#", ...) do
		for k, v in pairs(select(i, ...) or {}) do
			result[k] = v
		end
	end
	return result
end

local function compareScoreboardTeams(a, b)
	if not session.hasTeams then
		return b - a
	end
	local teamScores = scores.teamScores or {}
	local scoreA, scoreB = teamScores[a + 1], teamScores[b + 1]
	if showDisconnectedPlayers then
		if scoreA == nil or scoreA == json.null then scoreA = { place = 0, score = 0, total = 0 } end
		if scoreB == nil or scoreB == json.null then scoreB = { place = 0, score = 0, total = 0 } end
	end
	if type(scoreA) ~= "table" or type(scoreB) ~= "table" then
		return b - a
	end
	if appState.gameFinished and appState.multiround then
		return (tonumber(scoreB.total) or 0) - (tonumber(scoreA.total) or 0)
	end
	return (tonumber(scoreB.score) or 0) - (tonumber(scoreA.score) or 0)
end

local function compareScoreboardRows(a, b)
	local hasTeams = appState.hasTeams
	local aTeam, bTeam = tonumber(a.teamIndex) or -1, tonumber(b.teamIndex) or -1
	local aValid = hasTeams and aTeam >= 0 and aTeam < 8
	local bValid = hasTeams and bTeam >= 0 and bTeam < 8
	local result

	if a.type == 1 then
		if b.type == 1 then
			if aValid and bValid then
				result = compareScoreboardTeams(aTeam, bTeam)
				if result ~= 0 then return result end
			end
			return aTeam - bTeam
		end
		if b.type == 0 then
			if aTeam == bTeam then return -1 end
			if aValid and bValid then
				result = compareScoreboardTeams(aTeam, bTeam)
				if result ~= 0 then return result end
			end
			return aTeam - bTeam
		end
	end

	if a.type == 0 and b.type == 1 then
		if aTeam == bTeam then return 1 end
		if aValid and bValid then
			result = compareScoreboardTeams(aTeam, bTeam)
			if result ~= 0 then return result end
		end
		return aTeam - bTeam
	end

	if hasTeams and aTeam ~= bTeam then
		if aValid and bValid then
			result = compareScoreboardTeams(aTeam, bTeam)
			if result ~= 0 then return result end
		end
		return aTeam - bTeam
	end

	local aIndex, bIndex = tonumber(a.playerIndex) or -1, tonumber(b.playerIndex) or -1
	if aIndex == -1 then
		if bIndex == -1 then return 0 end
		return 1
	elseif bIndex == -1 then
		return -1
	end
	return (tonumber(a.place) or 0) - (tonumber(b.place) or 0)
end

-- stable insertion sort with a JS-style comparator (table.sort rejects inconsistent ones)
local function sortRows(list)
	for i = 2, #list do
		local item = list[i]
		local j = i - 1
		while j >= 1 and compareScoreboardRows(list[j], item) > 0 do
			list[j + 1] = list[j]
			j = j - 1
		end
		list[j + 1] = item
	end
end

local function pingImage(playerPing)
	playerPing = tonumber(playerPing) or -1
	if playerPing >= 0 and playerPing < 50 then return "dew://assets/scoreboard/ping5.png" end
	if playerPing >= 50 and playerPing < 100 then return "dew://assets/scoreboard/ping4.png" end
	if playerPing >= 100 and playerPing < 150 then return "dew://assets/scoreboard/ping3.png" end
	if playerPing >= 150 and playerPing < 200 then return "dew://assets/scoreboard/ping2.png" end
	if playerPing >= 200 and playerPing < 250 then return "dew://assets/scoreboard/ping1.png" end
	if playerPing >= 250 then return "dew://assets/scoreboard/ping0.png" end
	return ""
end

local function bit(mask, index)
	mask = math.tointeger(tonumber(mask) or 0) or 0
	return (mask & (1 << index)) ~= 0
end

local function samePlayer(a, b)
	return a[1].uid == b[1].uid and a[1].name == b[1].name
end

local function handleUpdate(update, animate)
	update = update or {}
	if type(update.session) == "table" then session = update.session end
	if type(update.scores) == "table" then scores = update.scores end
	if not session or type(update.scores) ~= "table" then
		return
	end

	appState.gameId = session.gameId
	appState.gameType = tonumber(session.gameType) or 0
	appState.lobbyType = tonumber(session.lobbyType) -- nil when missing: not a lobby, as in the JS
	appState.multiround = (tonumber(session.numRounds) or 0) > 1
	appState.roundCount = session.numRounds
	appState.currentRound = session.currentRound
	appState.hasTeams = truthy(session.hasTeams)
	appState.isHost = truthy(session.isHost)
	local sessionMaxPlayers = tonumber(session.sessionMaxPlayers) or 0
	if isLobby() and sessionMaxPlayers > 4 then
		appState.maxPlayers = 4
	else
		appState.maxPlayers = sessionMaxPlayers
	end
	local players = session.players or {}
	appState.playerCount = #players
	appState.gameFinished = truthy(scores.gameFinished)
	appState.gameTied = truthy(scores.gameTied)
	appState.roundOver = truthy(scores.roundOver)

	cachedPlayersInfo = session.playersInfo or {}

	local newCachedPlayerList = {}
	local rows, playerRows = {}, {}
	local activeTeamMask = 0
	local pingPlayers = type(session.playersPingInfo) == "table" and session.playersPingInfo.players or nil
	for x, player in ipairs(players) do
		local playerScores = (update.scores.playerScores or {})[x] or {}
		local playerIndex = tonumber(player.playerIndex) or -1
		local playersInfo = cachedPlayersInfo[playerIndex + 1]
		if type(playersInfo) ~= "table" then playersInfo = nil end

		local showPing, ping = false, ""
		if type(pingPlayers) == "table" then
			local pingInfo = pingPlayers[playerIndex + 1]
			showPing = true
			ping = pingImage(type(pingInfo) == "table" and pingInfo.ping or nil)
		end

		local teamIndex = tonumber(player.teamIndex) or -1
		-- don't show players that don't have valid team
		if teamIndex ~= -1 and playerIndex ~= -1 then
			activeTeamMask = activeTeamMask | (1 << teamIndex)
			local row = merge(player, playerScores, {
				type = 0,
				id = "p" .. playerIndex,
				emblem = (playersInfo and truthy(playersInfo.e)) and playersInfo.e or player.emblem,
				showPing = showPing,
				ping = ping,
				rank = playersInfo and (playersInfo.r ~= nil and playersInfo.r or -1) or -1,
				isDead = bit(update.scores.deadPlayerMask, playerIndex),
				hasObjective = bit(update.scores.objectivePlayerMask, playerIndex),
				isAlpha = bit(update.scores.alphaPlayerMask, playerIndex),
				startHidden = animate and true or false,
			})
			rows[#rows + 1] = row
			playerRows[#playerRows + 1] = row
			if player.uid ~= "0000000000000000" and #(tostring(player.name or "")) > 0 then
				newCachedPlayerList[#newCachedPlayerList + 1] = { player, playerScores, playersInfo }
			end
		end
	end

	if showDisconnectedPlayers then
		for _, playerItem in ipairs(cachedPlayerList) do
			local inNewCache = false
			for _, newItem in ipairs(newCachedPlayerList) do
				if samePlayer(playerItem, newItem) then inNewCache = true break end
			end
			if not inNewCache then
				local known = false
				for _, item in ipairs(disconnectedPlayers) do
					if samePlayer(playerItem, item) then known = true break end
				end
				if not known then
					disconnectedPlayers[#disconnectedPlayers + 1] = playerItem
				end
			end
		end

		local i = 1
		while i <= #disconnectedPlayers do
			local item = disconnectedPlayers[i]
			local rejoined = false
			for _, newItem in ipairs(newCachedPlayerList) do
				if samePlayer(item, newItem) then rejoined = true break end
			end
			if rejoined then
				table.remove(disconnectedPlayers, i) -- they rejoined
			else
				i = i + 1
				local player, playerScores, playersInfo = item[1], item[2], item[3]
				local teamIndex = tonumber(player.teamIndex) or -1
				if #rows < appState.maxPlayers and teamIndex ~= -1 then
					activeTeamMask = activeTeamMask | (1 << teamIndex)
					local row = merge(player, playerScores, {
						playerIndex = -1,
						type = 0,
						id = "d" .. tostring(player.name) .. ":" .. tostring(player.uid),
						emblem = (playersInfo and truthy(playersInfo.e)) and playersInfo.e or player.emblem,
						rank = playersInfo and (playersInfo.r ~= nil and playersInfo.r or -1) or -1,
						isDead = false,
						hasObjective = false,
						isAlpha = false,
						disconnected = true,
						startHidden = animate and true or false,
					})
					rows[#rows + 1] = row
					playerRows[#playerRows + 1] = row
				end
			end
		end
		cachedPlayerList = newCachedPlayerList
	end

	-- if it's a team game, add the team rows
	if appState.hasTeams then
		for i = 0, 7 do
			if (activeTeamMask >> i) & 1 == 1 then
				local teamScores = (update.scores.teamScores or {})[i + 1]
				if showDisconnectedPlayers and (teamScores == nil or teamScores == json.null) then
					teamScores = { place = 0, score = 0, total = 0 }
				end
				if type(teamScores) ~= "table" then teamScores = {} end
				rows[#rows + 1] = merge(teamScores, TEAM_DEFINITIONS[i + 1], {
					type = 1, id = "t" .. i, teamIndex = i, startHidden = animate and true or false,
				})
			end
		end
	end

	sortRows(rows)
	sortRows(playerRows)
	appState.rows = rows
	appState.playerRows = playerRows
	appState.valid = true
	if appState.selectedPlayer then
		appState.selectedPlayer = findRow(appState.selectedPlayer.id)
	end
	renderWindow()
end

local function hideScoreboard()
	jq("#playerBreakdown"):hide()
	jq(document):fadeOut(100, function()
		dew.callMethod("scoreboardHide", {})
	end)
end

local function animatePlayerList()
	animationStarted = false
	dew.setTimeout(function()
		animationStarted = true
		local maxWait = 0
		for i, rowElement in ipairs(el("window"):QuerySelectorAll("#playerList tr")) do
			local delay = 0.04 * (i - 1)
			maxWait = delay
			rowElement.style.transition = string.format("opacity 0.25s %.2fs linear-in-out", delay)
			rowElement:SetClass("hidden", false)
		end
		dew.setTimeout(function()
			for _, row in ipairs(appState.rows) do
				row.startHidden = false
			end
		end, (maxWait + 0.50) * 1000)
	end, 150)
end

-- ----------- controller navigation

local function updateSelection(item)
	if breakdownVisible() then
		local medals = el("medalBox"):QuerySelectorAll(".medal")
		for _, medal in ipairs(medals) do
			medal:SetClass("gpselected", false)
		end
		local medal = medals[item + 1]
		if medal then
			medal:SetClass("gpselected", true)
			local key = medal:GetAttribute("data-medal")
			if key then
				setBigMedal(key, true)
			end
		end
	else
		local rows = el("window"):QuerySelectorAll(".clickable")
		for _, row in ipairs(rows) do
			row:SetClass("gpselected", false)
		end
		if rows[item + 1] then
			rows[item + 1]:SetClass("gpselected", true)
		end
	end
end

local function upNav()
	if breakdownVisible() then
		if medalSelection > 4 then
			medalSelection = medalSelection - 5
			updateSelection(medalSelection)
		end
	elseif itemNumber > 0 then
		itemNumber = itemNumber - 1
		updateSelection(itemNumber)
	end
end

local function downNav()
	if breakdownVisible() then
		if medalSelection < 5 then
			medalSelection = medalSelection + 5
			updateSelection(medalSelection)
		end
	elseif itemNumber < #el("window"):QuerySelectorAll(".clickable") - 1 then
		itemNumber = itemNumber + 1
		updateSelection(itemNumber)
	end
end

local function leftNav()
	if breakdownVisible() and medalSelection % 5 ~= 0 then
		medalSelection = medalSelection - 1
		updateSelection(medalSelection)
	end
end

local function rightNav()
	if breakdownVisible() and medalSelection % 5 ~= 4 then
		medalSelection = medalSelection + 1
		updateSelection(medalSelection)
	end
end

local function checkGamepad()
	local now = dew_core.getTime() * 1000
	local shouldUpdateHeld = false
	if now - lastHeldUpdated > 100 then
		shouldUpdateHeld = true
		lastHeldUpdated = now
	end
	if stickTicks.up == 1 or (shouldUpdateHeld and stickTicks.up > 25) then upNav() end
	if stickTicks.down == 1 or (shouldUpdateHeld and stickTicks.down > 25) then downNav() end
	if stickTicks.left == 1 or (shouldUpdateHeld and stickTicks.left > 25) then leftNav() end
	if stickTicks.right == 1 or (shouldUpdateHeld and stickTicks.right > 25) then rightNav() end
end

local function onControllerConnect()
	jq("#closeButton .button"):attr("src", "dew://assets/buttons/360_Back.png")
	jq("#modInfoButton .button"):attr("src", "dew://assets/buttons/360_X.png")
	jq("#previousPlayer .button"):attr("src", "dew://assets/buttons/360_LB.png")
	jq("#nextPlayer .button"):attr("src", "dew://assets/buttons/360_RB.png")
	jq("#windowClose .button"):attr("src", "dew://assets/buttons/360_B.png")
	-- 0.8vw / 0.95vw of the 1280-wide page the original scaled
	jq("#closeButton"):css({ ["padding-left"] = "10.24dp", width = "4%" })
	jq("#modInfoButton"):css({ ["padding-left"] = "12.16dp", right = "11.7%", width = "5%" })
	jq(".button"):show()
end

local function onControllerDisconnect()
	jq("#closeButton"):css({ ["padding-left"] = "0", width = "5%" })
	jq("#closeButton .button"):hide()
	jq("#modInfoButton"):css({ ["padding-left"] = "0", right = "11%", width = "6%" })
	jq("#modInfoButton .button"):hide()
	jq("#previousPlayer .button"):hide()
	jq("#nextPlayer .button"):hide()
	jq("#windowClose .button"):hide()
	jq(".gpselected"):removeClass("gpselected")
end

local function loadSettings(i)
	if i <= #settingsOrder then
		local name = settingsOrder[i]
		dew.command(name, {}):next(function(response)
			settingsArray[name] = response
			loadSettings(i + 1)
		end)
	end
end

-- ----------- dew events

dew.on("variable_update", function(e)
	for _, variable in ipairs(e.data or {}) do
		if settingsArray[variable.name] ~= nil then
			settingsArray[variable.name] = variable.value
		end
	end
end)

dew.on("scoreboard_update", function(e)
	handleUpdate(e.data)
end)

dew.on("scoreboard_reset", function()
	-- prevent the scoreboard showing stale data
	appState.valid = false
	appState.selectedPlayer = nil
	appState.rows = {}
	appState.playerRows = {}
	jq("#contextMenuOverlay"):hide()
	cachedPlayerList = {}
	disconnectedPlayers = {}
	renderWindow()
end)

dew.on("scoreboard_hide", function()
	hideScoreboard()
end)

dew.on("voting_update", function()
	dew.notify("voting_prior_stats", json.array({ appState.valid }))
end)

dew.on("show", function(e)
	if isVisible then
		return
	end
	local data = e.data or {}

	initialShowTimout = false
	showHideTimeout = dew.setTimeout(function() initialShowTimout = true end, 400)
	initalKeyboardKey = true
	isVisible = true

	dew.command("Player.name"):next(function(result) localPlayer = result end)
	dew.command("Server.ShowDisconnectedPlayersClient"):next(function(result)
		showDisconnectedPlayers = result == "1"
	end)

	dew.hide("ingame_voting")
	local locked = truthy(data.locked)
	dew.captureInput(locked)
	if data.update ~= nil then
		handleUpdate(data.update, truthy(data.animate))
	end

	if isLobby() then
		appState.expanded = false
	else
		appState.expanded = locked
	end
	appState.locked = locked

	dew.command("Game.ExpandedScoreboard"):next(function(result)
		if result == "1" and not isLobby() then
			appState.expanded = true
			renderWindow()
		end
	end)

	if not appState.valid then
		dew.hide("scoreboard")
		return
	end

	appState.pregame = truthy(data.pregame)
	renderWindow()

	jq(document):hide()
	jq(document):fadeIn(100)
	if locked then
		jq("#closeButton"):show()
		if session and (session.modName or "") ~= "" then
			jq("#modInfoButton"):show()
		end
		ingameVoteWidget.focus()
		if tonumber(settingsArray["Settings.Gamepad"]) == 1 then
			onControllerConnect()
			hasGP = true
			if not repGP then
				repGP = dew.setInterval(checkGamepad, 1000 / 60)
			end
		else
			onControllerDisconnect()
			hasGP = false
			if repGP then
				dew.clearInterval(repGP)
				repGP = nil
			end
		end
	else
		ingameVoteWidget.blur()
		jq("#closeButton"):hide()
		jq("#modInfoButton"):hide()
	end
	ingameVoteWidget.render()

	dew.command("Server.NameClient", { internal = true }):next(function(name)
		jq("#serverName"):text(name)
	end)
	dew.getMapVariantInfo():next(function(info)
		jq("#mapName"):text(info and info.name or "")
	end)

	if session ~= nil and (session.modName or "") ~= "" then
		jq("#modName"):text(tostring(session.modName) .. " v" .. tostring(session.modVersion or ""))
		jq("#serverName"):addClass("serverNameOffset")
		jq("#mapName"):addClass("mapNameOffset")
	else
		jq("#modName"):text("")
		jq("#serverName"):removeClass("serverNameOffset")
		jq("#mapName"):removeClass("mapNameOffset")
	end

	if hasGP and appState.locked then
		updateSelection(itemNumber)
	elseif hasGP then
		jq(".gpselected"):removeClass("gpselected")
	end

	if truthy(data.animate) then
		animatePlayerList()
	else
		animationStarted = true
		for _, rowElement in ipairs(el("window"):QuerySelectorAll("#playerList tr")) do
			rowElement.style.transition = nil
			rowElement:SetClass("hidden", false)
		end
	end
end)

dew.on("hide", function()
	if showHideTimeout then
		dew.clearTimeout(showHideTimeout)
		showHideTimeout = nil
	end
	initalKeyboardKey = false
	initialShowTimout = false
	isVisible = false
	dew.show("ingame_voting")
	dew.captureInput(false)
	appState.selectedPlayer = nil
	jq("#contextMenuOverlay"):hide()
	appState.expanded = false
	appState.locked = false
	closePlayerBreakdown(false)
end)

dew.on("controllerinput", function(e)
	if not hasGP then
		return
	end
	local c = e.data or {}
	if c.A == 1 and not breakdownVisible() then
		local rows = el("window"):QuerySelectorAll(".clickable")
		if rows[itemNumber + 1] then
			rows[itemNumber + 1]:Click()
		end
	end
	if c.B == 1 then
		if breakdownVisible() then
			closePlayerBreakdown(true)
		else
			hideScoreboard()
		end
	end
	if c.X == 1 and session and (session.modName or "") ~= "" then
		dew.show("mod_info")
		hideScoreboard()
	end
	if c.Y == 1 and appState.locked then
		ingameVoteWidget.vote()
	end
	if c.Up == 1 then upNav() end
	if c.Down == 1 then downNav() end
	if c.Left == 1 then leftNav() end
	if c.Right == 1 then rightNav() end
	if c.LeftBumper == 1 and breakdownVisible() then el("previousPlayer"):Click() end
	if c.RightBumper == 1 and breakdownVisible() then el("nextPlayer"):Click() end
	if c.Select == 1 then
		hideScoreboard()
	end

	local select = tonumber(c.Select) or 0
	if select == 0 and initialControllerKey and initalKeyboardKey and initialShowTimout then
		initalKeyboardKey = false
		hideScoreboard()
	end
	initialControllerKey = select > 1

	local x, y = tonumber(c.AxisLeftX) or 0, tonumber(c.AxisLeftY) or 0
	if x > axisThreshold then stickTicks.right = stickTicks.right + 1 else stickTicks.right = 0 end
	if x < -axisThreshold then stickTicks.left = stickTicks.left + 1 else stickTicks.left = 0 end
	if y > axisThreshold then stickTicks.up = stickTicks.up + 1 else stickTicks.up = 0 end
	if y < -axisThreshold then stickTicks.down = stickTicks.down + 1 else stickTicks.down = 0 end
end)

-- ----------- voip

local function updateSpeaker(name, url)
	local voip = playerVolumes[name]
	if voip then
		voip.speaker = url
	end
	for _, speaker in ipairs(el("window"):QuerySelectorAll(".speaker")) do
		if speaker:GetAttribute("data-name") == name then
			if speaker:GetAttribute("src") ~= url then
				speaker:SetAttribute("src", url)
			end
		end
	end
end

local function speakerFor(volume, peerLevel)
	if peerLevel ~= nil and tonumber(peerLevel) == 0 then
		return "dew://assets/emblems/speaker-mute.png"
	elseif volume < -75 then
		return "dew://assets/emblems/speaker-off.png"
	elseif volume < -50 then
		return "dew://assets/emblems/speaker-low.png"
	end
	return "dew://assets/emblems/speaker-full.png"
end

local function voiceActivity(name, volume, peerLevel)
	local now = dew_core.getTime() * 1000
	volume = tonumber(volume) or -100
	local voip = playerVolumes[name]
	if voip then
		voip.currentVoice = volume
		if volume > -60 then
			voip.hasSpoken = true
		end
		if (now - voip.lastUpdate >= 1500) or (voip.lastUpdateVolume < volume) then
			if isVisible then
				updateSpeaker(name, speakerFor(volume, peerLevel))
				voip.lastUpdate = now
				voip.lastUpdateVolume = volume
			end
		end
	else
		playerVolumes[name] = { volume = 100.0, currentVoice = volume, lastUpdate = now, lastUpdateVolume = volume }
	end
end

dew.on("voip-user-volume", function(e)
	local data = e.data or {}
	voiceActivity(data.user, data.volume, data.peerLevel)
end)

dew.on("voip-self-volume", function(e)
	local volume = (e.data or {}).volume
	getSessionInfo(function(info)
		if localPlayer ~= "" and info and info.established == true then
			voiceActivity(localPlayer, volume, nil)
		end
	end)
end)

dew.on("voip-user-leave", function(e)
	playerVolumes[(e.data or {}).user] = nil
end)

dew.on("mute-voip-player", function(response)
	local data = response.data or {}
	local id = tostring(data.name) .. "|" .. tostring(data.uid)
	local level = truthy(data.muted) and 0 or 100
	dew.show("voip", { volume = { uid = id, vol = level / 100.0 } })
	appState.playerVolumes[id] = level
	local currentVol = -100
	if playerVolumes[data.name] then
		currentVol = math.max(tonumber(playerVolumes[data.name].currentVoice) or -100, -100)
	end
	dew.callMethod("playerVoipLevelChanged", { name = data.name, uid = data.uid, peerLevel = level / 100.0, currentVolume = currentVol })
end)

dew.on("script-show-scoreboard", function(e)
	if not isVisible then
		dew.callMethod("showScoreboard", { locked = true, preGame = false, animate = truthy((e.data or {}).animate) })
	end
end)

-- ----------- DOM events

document:AddEventListener("keyup", function(event)
	local key = tonumber(event.parameters.key_identifier)
	if key == KI_SNAPSHOT then
		dew.command("Game.TakeScreenshot")
	end
	if key == KI_TAB and initalKeyboardKey and initialShowTimout then
		initalKeyboardKey = false
		hideScoreboard()
	end
end)

document:AddEventListener("keydown", function(event)
	local key = tonumber(event.parameters.key_identifier)
	if key == KI_TAB then
		event:StopPropagation()
	end
	if (key == KI_TAB and not initalKeyboardKey) or key == KI_F19 then -- F19: keyCode 130
		hideScoreboard()
	end
	if key == KI_T or key == KI_Y then
		dew.show("chat", { captureInput = true, teamChat = key == KI_Y })
	end
	if key == KI_OEM_3 or key == KI_F1 or key == KI_OEM_8 then
		dew.show("console")
	end
	if key == KI_ESCAPE then
		if breakdownVisible() then
			closePlayerBreakdown(true)
		else
			hideScoreboard()
		end
	end
end)

document:AddEventListener("mousedown", function(event)
	if isVisible and tonumber(event.parameters.button) == 1 and breakdownVisible() then
		closePlayerBreakdown(true)
	end
end)

document:AddEventListener("load", function()
	el("closeButton"):AddEventListener("click", function() hideScoreboard() end)
	el("modInfoButton"):AddEventListener("click", function()
		dew.show("mod_info")
		hideScoreboard()
	end)
	el("windowClose"):AddEventListener("click", function() closePlayerBreakdown(true) end)
	el("previousPlayer"):AddEventListener("click", function()
		if breakdownNavigation.previous then
			dew.playSound("horizontal_navigation")
			playerBreakdown(breakdownNavigation.previous)
		end
	end)
	el("nextPlayer"):AddEventListener("click", function()
		if breakdownNavigation.next then
			dew.playSound("horizontal_navigation")
			playerBreakdown(breakdownNavigation.next)
		end
	end)

	-- context menu: the overlay closes it; items act on the selected player
	el("contextMenuOverlay"):AddEventListener("click", function(event)
		if event.target_element.id == "contextMenuOverlay" then
			closePlayerContextMenu()
		end
	end)
	el("contextMenuOverlay"):AddEventListener("mousedown", function(event)
		if tonumber(event.parameters.button) == 1 then
			closePlayerContextMenu()
		end
	end)
	local function withSelected(action, keepOpen)
		return function()
			local player = appState.selectedPlayer
			if not player then
				return
			end
			action(player)
			if not keepOpen then
				closePlayerContextMenu()
			end
		end
	end
	el("menuBan"):AddEventListener("click", withSelected(function(player)
		getSessionInfo(function(result)
			if playerUid(result) == player.uid then
				dew.playSound("error")
				return
			end
			dew.command("Server.KickBanUid " .. tostring(player.uid))
		end)
	end))
	local function kick(player)
		getSessionInfo(function(result)
			if playerUid(result) == player.uid then
				dew.playSound("error")
				return
			end
			if appState.isHost then
				dew.command("Server.KickUid " .. tostring(player.uid))
			else
				dew.sendChat("!kickindex " .. tostring(player.playerIndex), false)
			end
		end)
	end
	el("menuKick"):AddEventListener("click", withSelected(kick))
	el("menuVoteKick"):AddEventListener("click", withSelected(kick))
	el("menuMute"):AddEventListener("click", withSelected(function(player)
		setPlayerVolume(player.name, player.uid, appState.selectedPlayerMuted and 100 or 0)
		jq("#menuMute"):text(appState.selectedPlayerMuted and "Unmute" or "Mute")
		el("menuVolumeSlider"):SetAttribute("value", tostring(appState.selectedPlayerVolume))
	end, true))
	el("menuVolume"):AddEventListener("click", function(event) event:StopPropagation() end)
	el("menuVolumeSlider"):AddEventListener("change", function()
		local player = appState.selectedPlayer
		if not player then
			return
		end
		local level = math.floor((tonumber(el("menuVolumeSlider"):GetAttribute("value")) or 100) + 0.5)
		if tostring(level) == tostring(appState.selectedPlayerVolume) then
			return -- the value the menu itself set
		end
		setPlayerVolume(player.name, player.uid, level)
		jq("#menuMute"):text(appState.selectedPlayerMuted and "Unmute" or "Mute")
	end)

	ingameVoteWidget = dew.ingameVoting.makeWidget(el("chatVoteWidget"))
	loadSettings(1)
end)
