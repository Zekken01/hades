-- Port of screens/server_settings/settings.js (changes apply immediately)

local activePage = "#page1"
local selectedItem
local itemNumber = 0
local hasGP = false
local hiding = false

local KI_ESCAPE, KI_OEM_3, KI_OEM_8, KI_SNAPSHOT = 81, 44, 49, 97

local settingsToLoad = {
	{ "sName", "Server.Name" }, { "sMatchCountdown", "Server.CountdownLobby" }, { "sCountdown", "Server.Countdown" },
	{ "sMaxPlayers", "Server.MaxPlayers" }, { "sNumberTeams", "Server.NumberOfTeams" },
	{ "sShouldAnnounce", "Server.ShouldAnnounce" }, { "sShouldSubmitStats", "Server.ShouldSubmitStats" },
	{ "sDualWieldEnabled", "Server.DualWieldEnabled" }, { "sAssassinationEnabled", "Server.AssassinationEnabled" },
	{ "sPass", "Server.Password" }, { "sMessage", "Server.Message" }, { "sTeamShufflingEnabled", "Server.TeamShuffleEnabled" },
	{ "sMapVotingTime", "Voting.VoteTime" }, { "sNumOfRevotes", "Voting.MaxRevoteCount" },
	{ "sNumOfRematches", "Voting.MaxRematchCount" }, { "sNumberOfVotingOptions", "Voting.VoteOptionCount" },
	{ "sVotingDuplicationLevel", "Voting.DuplicationLevel" }, { "sTimeBetweenVoteEndAndGameStart", "Voting.VoteGameStartCountdown" },
	{ "sNumOfVetoes", "Voting.MaxVetoCount" }, { "sVetoVoteTime", "Voting.VoteTime" },
	{ "sVetoWinningShowTime", "Voting.VetoWinnerShowTime" }, { "sVetoPassPercentage", "Voting.VetoPassPercentage" },
	{ "sVetoSystemSelectionType", "Voting.VetoSelectionType" }, { "sUPNP", "UPnP.Enabled" },
	{ "sNetworkMode", "" }, { "sTagMod", "" }, { "sVotingStyle", "" },
	{ "sEmotesEnabled", "Server.EmotesEnabled" }, { "sKillCommandEnabled", "Server.KillCommandEnabled" },
	{ "sEndGameCommandEnabled", "Server.ChatCommandEndGameEnabled" }, { "sEndRoundCommandEnabled", "Server.ChatCommandEndRoundEnabled" },
	{ "sSprint", "Server.Sprint" }, { "sSprintUnlimited", "Server.UnlimitedSprint" },
	{ "sHitmarkersEnabled", "Server.HitMarkersEnabled" }, { "sWaypointType", "Server.HUDWaypointStyle" },
	{ "sDisconnectedPlayers", "Server.ShowDisconnectedPlayers" }, { "sPodiumEnabled", "Server.PodiumEnabled" },
	{ "sCampaignRepresentation", "Campaign.PlayerRepresentationEnabled" }, { "sFirefightRepresentation", "Campaign.PlayerRepresentationEnabled" },
	{ "sCampaignSprint", "Campaign.SprintEnabled" }, { "sFirefightSprint", "Campaign.SprintEnabled" },
	{ "sFallDamageEnabled", "Server.FallDamageMP" },
}

local function el(id) return document:GetElementById(id) end
local function decode(text)
	local ok, value = pcall(json.decode, text)
	if ok then return value end
end

-- ---- controls (see settings.lua: script writes raise change events too)

local written = {}
local settleAll, settleUntil, SETTLE_MS = 0, {}, 400
local function nowMs() return dew_core.getTime() * 1000 end
local function settling(id) return nowMs() < settleAll or nowMs() < (settleUntil[id] or 0) end

local function kind(element)
	if not element then return nil end
	if element:IsClassSet("toggle") then return "toggle" end
	if element.tag_name == "select" then return "select" end
	if element.tag_name == "input" then
		return element:GetAttribute("type") == "range" and "range" or "text"
	end
	return element.tag_name
end

local function isChecked(id)
	local element = el(id)
	return element ~= nil and element:GetAttribute("data-state") == "1"
end

local function setChecked(id, checked)
	local element = el(id)
	if not element then return end
	element:SetAttribute("data-state", checked and "1" or "0")
	element.inner_rml = checked and "Enabled" or "Disabled"
end

local function value(id)
	local element = el(id)
	if not element then return "" end
	if kind(element) == "toggle" then return isChecked(id) and "1" or "0" end
	return element:GetAttribute("value") or ""
end

local function setValue(id, newValue)
	local element = el(id)
	if not element then return end
	if kind(element) == "toggle" then
		setChecked(id, tostring(newValue) == "1")
		return
	end
	written[id] = tostring(newValue)
	element:SetAttribute("value", tostring(newValue))
	written[id] = element:GetAttribute("value") or ""
end

local function setOptions(id, list)
	local rml = {}
	for _, entry in ipairs(list) do
		rml[#rml + 1] = '<option value="' .. dew.escape(tostring(entry[2])) .. '">' .. dew.escape(tostring(entry[1])) .. "</option>"
	end
	settleUntil[id] = nowMs() + SETTLE_MS
	el(id).inner_rml = table.concat(rml)
	written[id] = value(id)
end

local function asSelect(element) return Element.As.ElementFormControlSelect(element) end

local function rowOf(element)
	while element and not element:IsClassSet("row") do element = element.parent_node end
	return element
end

local function isVisible(element)
	return dew_core.isDisplayed(element)
end

-- ---- applying

local onSpecialChange = {}

local function settingChanged(id)
	local elementId = id
	if el(id):IsClassSet("tinySetting") and id:sub(-4) == "Text" then
		elementId = id:sub(1, -5)
	end
	local newValue = value(id)
	for _, entry in ipairs(settingsToLoad) do
		if entry[1] == elementId and entry[2] ~= "" then
			dew.command(entry[2] .. ' "' .. newValue .. '"')
		end
	end
	if not hiding then
		dew.playSound("a_button")
	end
end

local function fireChange(id)
	settingChanged(id)
	if onSpecialChange[id] then onSpecialChange[id](id) end
end

-- ---- selection

local function selectableRows()
	local rows = {}
	for _, row in ipairs(el("page1"):QuerySelectorAll(".row")) do
		if row:QuerySelector("label") and isVisible(row) then rows[#rows + 1] = row end
	end
	return rows
end

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
		if rows[item + 1] then rows[item + 1]:SetClass("selectedElement", true) end
	end
	if itemNumber < 0 or itemNumber >= #rows then itemNumber = 0 end
	selectedItem = rowControl(rows[itemNumber + 1])
	if move and rows[item + 1] then rows[item + 1]:ScrollIntoView(false) end
	if sound then dew.playSound("vertical_navigation") end
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

local function formatNumber(number)
	if number == math.floor(number) then return string.format("%d", number) end
	return (string.format("%.3f", number):gsub("0+$", ""):gsub("%.$", ""))
end

local function stepRange(id, direction)
	local slider = el(id)
	local step = tonumber(slider:GetAttribute("step")) or 1
	local min = tonumber(slider:GetAttribute("min")) or 0
	local max = tonumber(slider:GetAttribute("max")) or 100
	local current = tonumber(value(id)) or 0
	if (direction < 0 and current <= min) or (direction > 0 and current >= max) then return end
	local newValue = math.max(min, math.min(max, current + direction * step))
	setValue(id, formatNumber(newValue))
	setValue(id .. "Text", formatNumber(newValue))
	fireChange(id)
end

local function toggleSelect(id, direction)
	local select = asSelect(el(id))
	local count = 0
	for _ in ipairs(select.options) do count = count + 1 end
	local newIndex = (tonumber(select.selection) or 1) - 1 + direction
	if newIndex >= 0 and newIndex < count then
		select.selection = newIndex + 1
		written[id] = value(id)
		fireChange(id)
	end
end

local function toggleControl(direction)
	local k = kind(el(selectedItem or ""))
	if k == "select" then toggleSelect(selectedItem, direction)
	elseif k == "range" then stepRange(selectedItem, direction) end
end

local function toggleSetting()
	if kind(el(selectedItem or "")) == "toggle" then
		setChecked(selectedItem, not isChecked(selectedItem))
		fireChange(selectedItem)
	end
end

local function selectButton()
	local row = rowOf(el(selectedItem or ""))
	local button = row and row:QuerySelector("button.tinySetting")
	if button then button:Click() else toggleSetting() end
end

local function initGamepad()
	dew.command("Settings.Gamepad", {}):next(function(result)
		hasGP = tonumber(result) == 1
		if hasGP then updateSelection(itemNumber, false, true, true) end
	end)
end

local function hideScreen()
	hiding = true
	dew.GameBlur("serversettings", false)
	jq("#overlay"):fadeOut(150)
	jq("#settingsWindow"):fadeOut(150, function() dew.hide() end)
end

local function closeButton()
	dew.playSound("b_button")
	hideScreen()
	dew.command("writeconfig")
end

local function showVoting(votetype)
	if votetype == "2" then
		setValue("sVotingStyle", "2")
		jq(".VoteType"):hide(); jq(".VetoType"):show()
	elseif votetype == "1" then
		setValue("sVotingStyle", "1")
		jq(".VoteType"):show(); jq(".VetoType"):hide()
	else
		setValue("sVotingStyle", "0")
		jq(".VoteType"):hide(); jq(".VetoType"):hide()
	end
end

local function updateVotingStyle(style)
	if style == "0" then
		dew.command("Voting.SystemType 0")
		jq(".VoteType"):hide(); jq(".VetoType"):hide()
	elseif style == "1" then
		dew.command("Voting.SystemType 1")
		jq(".VetoType"):hide(); jq(".VoteType"):show()
	else
		dew.command("Voting.SystemType 2")
		jq(".VoteType"):hide(); jq(".VetoType"):show()
	end
end

local function setControlValues()
	dew.getCommands():next(function(commands)
		for _, command in ipairs(commands or {}) do
			for _, entry in ipairs(settingsToLoad) do
				if entry[2] == command.name and el(entry[1]) then
					local setValueText = tostring(command.value == nil and "" or command.value)
					setValue(entry[1], setValueText)
					if el(entry[1]):IsClassSet("hasTiny") then
						setValue(entry[1] .. "Text", setValueText)
					end
				end
			end
		end
	end)
end

local MULTIPLAYER_OPTIONS = { "#NumberTeamsOption", "#TeamShuffleOption", "#RoundStartOption", "#AssassinationsOption",
	"#EmotesOption", "#KillCommandOption", "#EndgameOption", "#EndRoundOption", "#DisconnectedPlayersOption", "#PodiumOption", ".MultiplayerType" }

dew.on("show", function()
	hiding = false
	dew.GameBlur("serversettings", true)
	jq("#overlay"):fadeIn(150)
	jq("#settingsWindow"):fadeIn(150)
	updateSelection(0, false, true, true)
	initGamepad()
	setControlValues()

	dew.command("Voting.SystemType", {}):next(function(votetype)
		dew.command("Server.lobbyType", {}):next(function(lobbytype)
			showVoting(votetype)
			if lobbytype ~= "2" then
				jq(".VoteType"):hide(); jq(".VetoType"):hide(); jq("#votingHeader"):hide(); jq("#votingMode"):hide()
			end
		end)
	end)

	dew.command("Server.lobbyType", {}):next(function(lobbytype)
		if lobbytype == "0" then -- campaign
			dew.command("Campaign.MetagameScoring", {}):next(function(response) setValue("sCampaignScoring", response) end)
			jq("#campaignHeader"):show(); jq(".CampaignType"):show()
		else
			jq("#campaignHeader"):hide(); jq(".CampaignType"):hide()
		end
		jq("#firefightHeader"):toggle(lobbytype == "5")
		jq(".FirefightType"):toggle(lobbytype == "5")
		if lobbytype == "2" then -- customs
			jq(".VoteType"):show(); jq(".VetoType"):show(); jq("#votingHeader"):show(); jq("#votingMode"):show()
		else
			jq(".VoteType"):hide(); jq(".VetoType"):hide(); jq("#votingHeader"):hide(); jq("#votingMode"):hide()
		end
		local multiplayer = lobbytype == "2" or lobbytype == "3" -- customs, forge
		for _, selector in ipairs(MULTIPLAYER_OPTIONS) do
			jq(selector):toggle(multiplayer)
		end
	end)

	dew.command("Server.Mode", {}):next(function(response) setValue("sNetworkMode", response) end)

	dew.command("Server.ListMods", {}):next(function(response)
		local list = { { "None", "" } }
		for _, mod in ipairs(decode(response) or {}) do
			if dew.truthy(mod.multiplayerType) or dew.truthy(mod.campaignType) or dew.truthy(mod.firefightType) then
				list[#list + 1] = { tostring(mod.name) .. " " .. tostring(mod.version), mod.filename }
			end
		end
		setOptions("sTagMod", list)
		dew.command("Server.Mod", {}):next(function(current) setValue("sTagMod", current) end)
	end)

	dew.command("Campaign.GetRallyPoints", {}):next(function(response)
		local rallyPoints = decode(response) or {}
		local list = {}
		for index, point in ipairs(rallyPoints.points or {}) do
			list[#list + 1] = { point, index - 1 }
		end
		setOptions("sCampaignRallyPoint", list)
		if rallyPoints.points then
			dew.command("Campaign.InsertionPoint", {}):next(function(current) setValue("sCampaignRallyPoint", current) end)
		end
	end)
end)

dew.input.on("action", function(evt)
	local Actions = dew.input.Actions
	if evt.action == Actions.X then
		local row = rowOf(el(selectedItem or ""))
		local button = row and row:QuerySelector("button.tinySetting")
		if button then button:Click() end
	elseif evt.action == Actions.A then
		selectButton()
	elseif evt.action == Actions.B and evt.inputType ~= "keyboard" then
		closeButton()
	end
end)

dew.input.on("scroll", function(type, axis, direction)
	if type == 0 or type == 1 then
		if axis == 0 then
			if direction == -1 then upNav() end
			if direction == 1 then downNav() end
		end
		if axis == 1 then toggleControl(direction) end
	end
	if type == 2 and axis == 0 then
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
	if key == KI_ESCAPE then closeButton() end
	if key == KI_SNAPSHOT then dew.command("Game.TakeScreenshot") end
end)

document:AddEventListener("keydown", function(event)
	local key = tonumber(event.parameters.key_identifier)
	if key == KI_OEM_3 or key == KI_OEM_8 then
		dew.show("console")
	end
	local target = event.target_element
	local typing = target and (target.tag_name == "textarea" or (target.tag_name == "input" and target:GetAttribute("type") ~= "range"))
	if key == 91 or key == 93 or ((key == 90 or key == 92 or key == 1) and not typing) then
		event:StopPropagation()
	end
end)

document:AddEventListener("mouseup", function(event)
	if tonumber(event.parameters.button) == 1 then closeButton() end
end)

document:AddEventListener("load", function()
	settleAll = nowMs() + SETTLE_MS
	jq("#closeButton img"):attr("src", "dew://assets/buttons/360_B.png")
	el("closeButton"):AddEventListener("click", closeButton)

	for _, control in ipairs(el("settingsWindow"):QuerySelectorAll("select, input, textarea")) do
		local id = control.id
		if id and id ~= "" then
			control:AddEventListener("change", function()
				if settling(id) or (written[id] ~= nil and written[id] == value(id)) then
					written[id] = value(id)
					return
				end
				written[id] = value(id)
				local k = kind(control)
				if k == "range" and el(id .. "Text") then
					setValue(id .. "Text", value(id))
				elseif control:IsClassSet("tinySetting") and id:sub(-4) == "Text" and el(id:sub(1, -5)) then
					setValue(id:sub(1, -5), value(id))
				end
				fireChange(id)
			end)
		end
	end

	for _, toggle in ipairs(el("settingsWindow"):QuerySelectorAll(".toggle")) do
		local id = toggle.id
		local function flip()
			setChecked(id, not isChecked(id))
			fireChange(id)
		end
		toggle:AddEventListener("click", flip)
		local label = rowOf(toggle) and rowOf(toggle):QuerySelector("label")
		if label then label:AddEventListener("click", flip) end
	end

	onSpecialChange.sVotingStyle = function()
		updateVotingStyle(value("sVotingStyle"))
		if hasGP then
			local last = #selectableRows() - 1
			if itemNumber > last then itemNumber = last end
			updateSelection(itemNumber, true, true, true)
		end
	end
	local function coopSprint(id)
		if isChecked(id) then dew.dialog("coop_sprint") end
	end
	onSpecialChange.sCampaignSprint = coopSprint
	onSpecialChange.sFirefightSprint = coopSprint
	onSpecialChange.sCampaignScoring = function() dew.command("Campaign.MetagameScoring " .. value("sCampaignScoring")) end
	onSpecialChange.sNetworkMode = function()
		dew.command("Server.Mode " .. value("sNetworkMode"))
		dew.command('Server.Mod "' .. value("sTagMod") .. '"')
	end
	onSpecialChange.sTagMod = function() dew.command('Server.Mod "' .. value("sTagMod") .. '"') end
	onSpecialChange.sCampaignRallyPoint = function() dew.command("Campaign.InsertionPoint " .. value("sCampaignRallyPoint")) end

	-- textarea rows are taller
	local message = rowOf(el("sMessage"))
	if message then message:SetClass("tall", true) end

	el("showPasswordBtn"):AddEventListener("click", function()
		local password = el("sPass")
		if password:GetAttribute("type") == "password" then
			password:SetAttribute("type", "text")
			el("showPasswordBtn").inner_rml = "HIDE"
		else
			password:SetAttribute("type", "password")
			el("showPasswordBtn").inner_rml = "SHOW"
		end
	end)

	for index, row in ipairs(el("settingsWindow"):QuerySelectorAll(".row")) do
		row:SetAttribute("data-row", tostring(index))
	end
	for _, row in ipairs(el("settingsWindow"):QuerySelectorAll(".row")) do
		if row:QuerySelector(".setting") then
			local uid = row:GetAttribute("data-row")
			row:AddEventListener("mouseover", function()
				for i, candidate in ipairs(selectableRows()) do
					if candidate:GetAttribute("data-row") == uid then itemNumber = i - 1 end
				end
				jq(".selectedElement"):removeClass("selectedElement")
				row:SetClass("selectedElement", true)
				updateSelection(itemNumber, false, false, false)
			end)
		end
	end

	setControlValues()
	dew.command("Voting.SystemType", {}):next(showVoting)
end)
