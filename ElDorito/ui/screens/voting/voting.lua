-- Port of screens/voting/voting.js

local votingType = "voting"
local interval = nil
local timeRemaining = 0
local isHost = false
local axisThreshold = 0.5
local stickTicks = { left = 0, right = 0, up = 0, down = 0 }
local repGP = nil
local lastHeldUpdated = 0
local itemNumber = 1

local settingsArray = { ["Settings.Gamepad"] = "0" }
local settingsOrder = { "Settings.Gamepad" }
local compactMode = false
local shown = false

-- KI values
local KI_SPACE, KI_RETURN, KI_ESCAPE, KI_OEM_3, KI_F1, KI_OEM_8, KI_SNAPSHOT = 1, 72, 81, 44, 107, 49, 97
local KI_UP, KI_DOWN, KI_T, KI_Y, KI_X, KI_HOME, KI_TAB = 91, 93, 31, 36, 35, 89, 70

local function el(id) return document:GetElementById(id) end

local function gamepadEnabled()
	return tonumber(settingsArray["Settings.Gamepad"]) == 1
end

local function nowMs()
	return dew_core.getTime() * 1000
end

dew.on("variable_update", function(e)
	for _, variable in ipairs(e.data or {}) do
		if settingsArray[variable.name] ~= nil then
			settingsArray[variable.name] = variable.value
		end
	end
end)

dew.on("voting_prior_stats", function(e)
	if dew.truthy((e.data or {})[1]) then
		jq("#scoreboardButton"):show()
	else
		jq("#scoreboardButton"):hide()
	end
end)

local function loadSettings(i)
	if i <= #settingsOrder then
		local name = settingsOrder[i]
		dew.command(name, {}):next(function(response)
			settingsArray[name] = response
			loadSettings(i + 1)
		end)
	end
end

-- the ::before rule of #vetoStatus follows it
local function showVetoStatus(show)
	jq("#vetoStatus"):toggle(show)
	jq("#vetoStatusRule"):toggle(show)
end

local function options()
	return document:QuerySelectorAll(".votingOption")
end

local function winnerChosen()
	return #document:QuerySelectorAll(".winner") > 0
end

-- Not in the original: in the main menu lobby the full voting window lets the game have the
-- mouse while the cursor is outside it, so the lobby's player cards stay usable.
local inLobby = false
local function applyPointerRegion()
	dew.setPointerRegion((inLobby and not compactMode) and "window" or nil)
end

local function onShow()
	applyPointerRegion()
	if compactMode then
		jq("#window"):fadeOut(200)
		jq(".window-compact"):fadeIn(200)
		dew.captureInput(false)
		dew.capturePointer(true)
	else
		jq("#window"):fadeIn(200)
		jq(".window-compact"):fadeOut(200)
		dew.captureInput(true)
		dew.capturePointer(true)
	end
end

local function hideScreen()
	if not compactMode then
		dew.playSound("b_button")
	end
	compactMode = true
	onShow()
end

local function vote(number)
	number = tonumber(number) or 0
	if number == 0 then
		return
	end
	dew.command("server.SubmitVote " .. number)
	local chosen = winnerChosen()
	if votingType ~= "veto" then
		if not chosen then
			jq(".myVote"):removeClass("myVote")
			local option = options()[number]
			if option then
				option:SetClass("myVote", true)
			end
		end
	else
		if jq("#vetoText"):html():find("Map", 1, true) then
			jq("#vetoText"):html("Voted to veto")
			jq("#vetoBox"):removeClass("veto-flash")
			jq("#vetoedX"):css("display", "block")
		else
			jq("#vetoedX"):css("display", "none")
			jq("#vetoText"):html("Veto Map and Game")
			jq("#vetoBox"):addClass("veto-flash")
		end
	end
	if not chosen then
		dew.playSound("a_button")
	end
end

local isThrottled = false
local throttleDuration = 1000
function veto()
	if isThrottled then
		return
	end
	isThrottled = true
	dew.setTimeout(function() isThrottled = false end, throttleDuration)
	vote(1)
end

local function setTimer(amount, voting)
	if interval then
		dew.clearInterval(interval)
	end
	timeRemaining = amount
	interval = dew.setInterval(function()
		local id
		if compactMode then
			id = "timerCompact"
		elseif votingType ~= "veto" then
			if votingType ~= "ended" then id = "timer" else id = "vetoGameTimer" end
		else
			id = "vetoTimer"
		end
		local timerElement = el(id)
		local function setText(text)
			if timerElement then
				timerElement.inner_rml = text
			end
		end
		amount = amount - 1
		if voting then
			if votingType ~= "veto" then
				setText(" Voting ends in..." .. amount)
			elseif compactMode then
				setText(" Veto ends in..." .. amount)
			else
				setText(" " .. amount .. " seconds")
			end
			if amount == 0 then
				dew.playSound("alt_timer_sound_zero")
			elseif amount <= 3 and amount > 0 then
				dew.playSound("alt_timer_sound")
			end
		else
			if votingType ~= "ended" then
				setText(" Game starts in..." .. amount)
			else
				setText(" Game starting in " .. amount .. " seconds.")
			end
			if amount == 0 then
				dew.playSound("timer_sound_zero")
			elseif amount <= 3 and amount > 0 then
				dew.playSound("timer_sound")
			end
		end
		if amount < 0 then
			setText(voting and "" or "Starting...")
			timeRemaining = amount
			dew.clearInterval(interval)
			interval = nil
		end
		timeRemaining = amount
	end, 1000)
end

local function updateSelection(item, sound)
	jq(".selected"):removeClass("selected")
	if not winnerChosen() then
		local option = el(tostring(item))
		if option and option:IsClassSet("votingOption") then
			option:SetClass("selected", true)
		end
		if sound then
			dew.playSound("vertical_navigation")
		end
	end
end

local function upNav()
	if itemNumber > 1 then
		itemNumber = itemNumber - 1
		updateSelection(itemNumber, true)
	end
end

local function downNav()
	if itemNumber < #options() then
		itemNumber = itemNumber + 1
		updateSelection(itemNumber, true)
	end
end

local function checkGamepad()
	local shouldUpdateHeld = false
	if nowMs() - lastHeldUpdated > 100 then
		shouldUpdateHeld = true
		lastHeldUpdated = nowMs()
	end
	if stickTicks.up == 1 or (shouldUpdateHeld and stickTicks.up > 25) then
		upNav()
	end
	if stickTicks.down == 1 or (shouldUpdateHeld and stickTicks.down > 25) then
		downNav()
	end
end

local function initGamepad()
	jq("#scoreboardButton img"):attr("src", "dew://assets/buttons/360_Back.png")
	jq("#vetoButton img"):attr("src", "dew://assets/buttons/360_X.png")
	jq("#closeButton img"):attr("src", "dew://assets/buttons/360_B.png")
	jq(".vetoBoxBtn"):attr("src", "dew://assets/buttons/360_X.png")
	if gamepadEnabled() then
		if not repGP then
			repGP = dew.setInterval(checkGamepad, 1000 / 60)
		end
	elseif repGP then
		dew.clearInterval(repGP)
		repGP = nil
	end
end

-- element: a .mapImage div; the picture is its decorator (object-fit: cover on the options)
local function setImage(element, url)
	if not element then
		return
	end
	local fit = ""
	if element:IsClassSet("cover") then
		fit = " cover"
	end
	element.style.decorator = "image(" .. url .. fit .. ")"
end

local function getImageUrl(element, option)
	local image = tostring(option.image or "")
	if image:match("^https?://") and (image:match("%.png$") or image:match("%.jpg$")) then
		dew.fetchImage(image):next(function(url) setImage(element, url) end)
		return
	end
	local assetOptions = { pak = option.modhash, fileTypes = { "jpg", "png" }, searchBaseAssets = true }
	dew.getAssetUrl("assets/maps/small/" .. image, assetOptions):next(function(url)
		local imageURL = "dew://assets/maps/small/placeholder.jpg"
		if url ~= "" then
			imageURL = url
		else -- try the base scenario map name
			dew.getAssetUrl("assets/maps/small/" .. tostring(option.scnrname or ""), assetOptions):next(function(urlscnr)
				if urlscnr ~= "" then
					imageURL = urlscnr
				end
				setImage(element, imageURL)
			end)
			return
		end
		setImage(element, imageURL)
	end)
end

local function playerCount(res)
	local ok, players = pcall(json.decode, res)
	if ok and type(players) == "table" then
		return #players
	end
	return 0
end

dew.on("show", function(event)
	shown = true
	dew.notify("voting_update")
	dew.getSessionInfo():next(function(info)
		isHost = info.isHost
		inLobby = info.mapName == "mainmenu"
		applyPointerRegion()
	end)

	if gamepadEnabled() then itemNumber = 1 else itemNumber = 0 end
	initGamepad()

	local data = event.data or {}
	if dew.truthy(data.userInvoked) and compactMode and not dew.truthy(data.compact) then
		dew.playSound("x_button")
		compactMode = false
	end
	onShow()
end)

dew.on("hide", function()
	shown = false
	jq(".window-compact"):hide()
	if repGP then
		dew.clearInterval(repGP)
		repGP = nil
	end
end)

dew.on("VoteTimerUpdated", function(event)
	local data = event.data or {}
	if not dew.truthy(data.shouldUpdateTimer) and timeRemaining > 0 then
		return
	end
	if (tonumber(data.timeUntilGameStart) or 0) ~= 0 then
		setTimer(tonumber(data.timeUntilGameStart), false)
	end
end)

dew.on("Winner", function(event)
	jq("#votingDesc"):html('Your game will be starting shortly. <span id="timer"></span>')
	local winner = el(tostring((event.data or {}).Winner))
	if winner then
		winner:SetClass("winner", true)
	end
	for _, option in ipairs(options()) do
		if not option:IsClassSet("winner") then
			option.style.transition = "opacity 1s linear-in-out"
			option.style.opacity = "0.33"
		end
	end
	jq(".votingOption"):removeClass("selected")
end)

local function clearOptions()
	local container = el("votingOptions")
	for _, child in ipairs(container:QuerySelectorAll(".votingOption")) do
		container:RemoveChild(child)
	end
end

dew.on("VetoOptionsUpdated", function(event)
	local data = event.data or {}
	local option = data.vetoOption or {}
	clearOptions()
	jq("#vetoedX"):css("display", "none")
	jq("#vetoText"):html("Veto Map and Game")
	jq("#vetoBox"):addClass("veto-flash")

	jq("#vetoMapInfo"):empty()
	jq("#vetoMapInfo"):show()
	showVetoStatus(true)
	jq("#votingDesc"):hide()
	jq("#votingDescRule"):hide()
	local voting
	if dew.truthy(option.canveto) then
		votingType = "veto"
		voting = true
		jq("#vetoButton"):show(); jq("#vetoCount"):show(); jq("#vetoCountDown"):show(); jq(".vetoCountBox"):show()
		jq("#vetoCountDown"):html('VETO COUNTDOWN: <span id="vetoTimer"></span>')
		jq("#vetoStatus"):html("A new game and map will be chosen with a majority veto.")
		jq(".vetoBox"):show()
	else
		votingType = "ended"
		voting = false
		jq(".vetoBox"):hide()
		jq("#vetoButton"):hide(); jq("#vetoCount"):hide()
		jq("#vetoStatus"):html("")
		jq("#vetoCountDown"):html('Game accepted. <span id="vetoGameTimer"></span>')
	end
	local modname = ""
	if (option.modname or "") ~= "" then
		modname = "Mod: " .. option.modname
	end

	jq("#vetoMapInfo"):append('<div class="mapImage" id="vetoPreview"></div><span class="mapInfo">'
		.. dew.escape(tostring(option.typename or "")) .. " on " .. dew.escape(tostring(option.mapname or ""))
		.. '<span class="modInfo">' .. dew.escape(modname) .. "</span></span>")
	getImageUrl(el("vetoPreview"), option)

	local needed = tostring(data.votesNeededToPass or "")
	dew.command("Server.ListPlayersJSON"):next(function(res)
		jq("#voteCount"):html('<span id="1"><span class="selector">0</span> of ' .. playerCount(res) .. "</span> (" .. needed .. " needed)")
	end)
	if (tonumber(data.timeRemaining) or 0) > 0 then
		setTimer(tonumber(data.timeRemaining) - 1, voting)
	end
end)

local VOTEBOX = '<div class="hoverbar"></div><span class="votebox"><span class="votecheck"></span></span>'

dew.on("VotingOptionsUpdated", function(event)
	local data = event.data or {}
	votingType = "voting"

	jq("#vetoButton"):hide(); jq("#vetoCount"):hide(); jq("#vetoMapInfo"):hide(); jq("#vetoCountDown"):hide()
	jq(".vetoCountBox"):hide(); showVetoStatus(false); jq(".vetoBox"):hide()
	jq("#votingDesc"):html('Vote for game and map... <span id="timer"></span>')
	jq("#votingDesc"):show()
	jq("#votingDescRule"):show()
	clearOptions()

	local container = el("votingOptions")
	for _, entry in ipairs(data.votingOptions or {}) do
		local rml
		local classes = "votingOption"
		local hasImage = false
		if entry.mapname == "Revote" then
			classes = "votingOption none"
			rml = VOTEBOX .. 'None of the above<span class="selector">0</span>'
		elseif entry.mapname == "Rematch" then
			classes = "votingOption none"
			rml = VOTEBOX .. 'Rematch<span class="selector">0</span>'
		elseif (entry.mapname or "") ~= "" then
			local modname, center = "", "Centered"
			if (entry.modname or "") ~= "" then
				modname = "Mod: " .. entry.modname
				center = ""
			end
			hasImage = true
			rml = VOTEBOX
				.. '<div class="mapImage cover" id="votePreview' .. tostring(entry.index) .. '"></div>'
				.. '<span class="gameType' .. center .. '">' .. dew.escape(tostring(entry.typename or "")) .. "</span>"
				.. '<span class="mapName' .. center .. '">' .. dew.escape(tostring(entry.mapname or "")) .. "</span>"
				.. '<span class="modName">' .. dew.escape(modname) .. "</span>"
				.. '<span class="selector">0</span>'
		end
		if rml then
			local option = container:AppendChild(document:CreateElement("div"))
			option.class_name = classes
			option.id = tostring(entry.index)
			option.inner_rml = rml
			if hasImage then
				getImageUrl(el("votePreview" .. tostring(entry.index)), entry)
			end
		end
	end

	if gamepadEnabled() then itemNumber = 1 else itemNumber = 0 end
	updateSelection(itemNumber, false)

	for position, option in ipairs(options()) do
		option:AddEventListener("click", function()
			jq(".votingOption"):removeClass("selected")
			if not winnerChosen() then
				option:SetClass("selected", true)
			end
			vote(option.id)
		end)
		option:AddEventListener("mouseover", function()
			if not winnerChosen() then
				itemNumber = position
				updateSelection(itemNumber, false)
			end
		end)
	end

	if (tonumber(data.timeRemaining) or 0) > 0 then
		setTimer(tonumber(data.timeRemaining) - 1, true)
	end
end)

dew.on("VoteCountsUpdated", function(event)
	local data = event.data or {}
	local counts = data.voteCounts or {}
	if votingType == "veto" then
		local count = tostring((counts[1] or {}).Count or 0)
		local needed = tostring(data.votesNeededToPass or "")
		dew.command("Server.ListPlayersJSON"):next(function(res)
			jq("#voteCount"):html('<span id="1"><span class="selector">' .. count .. "</span> of " .. playerCount(res) .. "</span> (" .. needed .. " needed)")
		end)
		return
	end
	for _, entry in ipairs(counts) do
		local option = el(tostring(entry.OptionIndex))
		local selector = option and option:QuerySelector(".selector")
		if selector then
			selector.inner_rml = tostring(tonumber(entry.Count) or 0)
		end
	end
end)

dew.on("VoteEnded", function()
	if interval then
		dew.clearInterval(interval)
		interval = nil
	end
	compactMode = false
end)

dew.on("controllerinput", function(e)
	if not gamepadEnabled() then
		return
	end
	local c = e.data or {}
	if c.A == 1 then vote(itemNumber) end
	if c.Start == 1 then dew.show("settings") end
	if c.Select == 1 then dew.show("scoreboard", { locked = true }) end
	if c.Up == 1 then upNav() end
	if c.Down == 1 then downNav() end
	local axisY = tonumber(c.AxisLeftY) or 0
	if axisY > axisThreshold then stickTicks.up = stickTicks.up + 1 else stickTicks.up = 0 end
	if axisY < -axisThreshold then stickTicks.down = stickTicks.down + 1 else stickTicks.down = 0 end
	if c.X == 1 and votingType == "veto" then veto() end
	if c.B == 1 then hideScreen() end
end)

function cancelVote()
	if isHost then
		dew.command("Voting.CancelVote")
	end
end

document:AddEventListener("keyup", function(event)
	if tonumber(event.parameters.key_identifier) == KI_SNAPSHOT then
		dew.command("Game.TakeScreenshot")
	end
end)

document:AddEventListener("keydown", function(event)
	local key = tonumber(event.parameters.key_identifier)
	if key == KI_ESCAPE then
		hideScreen()
	end
	if key == KI_OEM_3 or key == KI_F1 or key == KI_OEM_8 then
		dew.show("console")
	end
	if key == KI_UP then upNav() end
	if key == KI_DOWN then downNav() end
	if key == KI_RETURN or key == KI_SPACE then vote(itemNumber) end
	if key == KI_T or key == KI_Y then
		dew.show("chat", { captureInput = true, teamChat = key == KI_Y })
	end
	if key == KI_X and votingType == "veto" then veto() end
	if key == KI_HOME then dew.show("settings") end
	if key == KI_TAB then
		event:StopPropagation()
		dew.show("scoreboard", { locked = "true" })
	end
end)

-- window mouseup: right click collapses to the compact bar
document:AddEventListener("mouseup", function(event)
	if shown and tonumber(event.parameters.button) == 1 and not compactMode then
		hideScreen()
	end
end)

document:AddEventListener("load", function()
	jq(".window-compact"):hide()
	jq("#scoreboardButton"):on("click", function() dew.show("scoreboard", { locked = "true" }) end)
	jq("#closeButton"):on("click", function() hideScreen() end)
	jq("#vetoButton"):on("click", function() veto() end)
	jq("#showButton"):on("click", function()
		dew.playSound("x_button")
		compactMode = false
		onShow()
	end)
	jq("#votingOptions"):on("mouseout", function()
		jq(".votingOption"):removeClass("selected")
	end)
	loadSettings(1)
end)
