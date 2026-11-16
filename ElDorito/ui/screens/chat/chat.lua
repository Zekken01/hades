-- Port of screens/chat/chat.js

local isTeamChat = false
local hasTeams = false
local stayOpen = false
local hideTimer = nil
local hideDelay = 4500
local fadeTime = 800
local nameCardOpacity = 0.8
local teamArray = {
	[0] = { name = "red", color = "#852D2C" },
	{ name = "blue", color = "#2F5385" },
	{ name = "green", color = "#4E6513" },
	{ name = "orange", color = "#B27701" },
	{ name = "purple", color = "#4B377C" },
	{ name = "gold", color = "#A89127" },
	{ name = "brown", color = "#49310F" },
	{ name = "pink", color = "#CC789C" },
	{ name = "white", color = "#D8D8D8" },
	{ name = "black", color = "#0B0B0B" },
}
local playerName = nil -- lower-cased "@name", matched case-insensitively like the /ig RegExp
local playerTabIndex = -1
local playersMatchList = {}
local settingsOrder = { "Game.HideChat", "Player.Name", "Game.ChatMessageLimit" }
local settingsArray = { ["Game.HideChat"] = "0", ["Player.Name"] = "0", ["Game.ChatMessageLimit"] = "50" }
local cachedPlayerJSON = nil

local KI_TAB, KI_RETURN, KI_ESCAPE, KI_PRIOR, KI_NEXT, KI_SNAPSHOT, KI_LSHIFT, KI_RSHIFT = 70, 72, 81, 86, 87, 97, 138, 139

local function chatBox() return document:GetElementById("chatBox") end
local function chatWindow() return document:GetElementById("chatWindow") end

local function boxValue()
	local box = chatBox()
	return box and (box:GetAttribute("value") or "") or ""
end

local function setBoxValue(value)
	local box = chatBox()
	if box then box:SetAttribute("value", value) end
end

local function focusBox()
	local box = chatBox()
	if box and box.style.display ~= "none" then box:Focus() end
end

local function startsWith(text, prefix)
	return text:sub(1, #prefix) == prefix
end

local function splitWords(text)
	local words = {}
	for word in (text .. " "):gmatch("(.-) ") do
		words[#words + 1] = word
	end
	return words
end

local function anyPlayerMentioned(text)
	local lower = text:lower()
	for _, player in ipairs(cachedPlayerJSON or {}) do
		if lower:find("@" .. tostring(player.name):lower(), 1, true) then
			return true
		end
	end
	return false
end

-- U+0300-036F, 1AB0-1AFF, 1DC0-1DFF, 20D0-20FF, FE20-FE2F, 200B-200D, 2060-2064
local function removeCombiningCharacters(input)
	local out = {}
	for _, code in utf8.codes(input) do
		local drop = (code >= 0x0300 and code <= 0x036F) or (code >= 0x1AB0 and code <= 0x1AFF)
			or (code >= 0x1DC0 and code <= 0x1DFF) or (code >= 0x20D0 and code <= 0x20FF)
			or (code >= 0xFE20 and code <= 0xFE2F) or (code >= 0x200B and code <= 0x200D)
			or (code >= 0x2060 and code <= 0x2064)
		if not drop then
			out[#out + 1] = utf8.char(code)
		end
	end
	return table.concat(out)
end

local function utf8Sub(text, count)
	local ok, offset = pcall(utf8.offset, text, count + 1)
	if not ok or not offset then
		return text
	end
	return text:sub(1, offset - 1)
end

local function adjustColor(color, amount)
	local hex = tostring(color):gsub("#", "")
	local parts = {}
	for i = 0, 2 do
		local e = (tonumber(hex:sub(i * 2 + 1, i * 2 + 2), 16) or 0) + amount
		e = math.max(0, math.min(255, e))
		parts[#parts + 1] = string.format("%02x", e)
	end
	return "#" .. table.concat(parts)
end

local function hexToRgba(hex, opacity)
	local r = tonumber(hex:sub(2, 3), 16) or 0
	local g = tonumber(hex:sub(4, 5), 16) or 0
	local b = tonumber(hex:sub(6, 7), 16) or 0
	return string.format("rgba(%d,%d,%d,%d)", r, g, b, math.floor(opacity * 255 + 0.5))
end

local function aWrap(link)
	local raw = link:gsub("&amp;", "&"):gsub("&lt;", "<"):gsub("&gt;", ">"):gsub("&quot;", '"'):gsub("&#39;", "'")
	if raw:find("[^%w%-+&@#/%%?=~_|!:,.;()]") then
		return ""
	end
	return '<span class="link" style="color: #1e90ff;" data-href="' .. link .. '">' .. link .. "</span>"
end

local function loadSettings(i)
	if i <= #settingsOrder then
		dew.command(settingsOrder[i], {}):next(function(response)
			settingsArray[settingsOrder[i]] = response
			loadSettings(i + 1)
		end)
	end
end

local function fadeAway()
	if hideTimer then dew.clearTimeout(hideTimer) end
	hideTimer = dew.setTimeout(function()
		jq("#chat"):fadeOut(fadeTime, function()
			dew.hide()
		end)
	end, hideDelay)
end

local function chatboxHide()
	dew.captureInput(false)
	dew.callMethod("chatBoxOpened", { opened = false })
	fadeAway()
	stayOpen = false
	setBoxValue("")
	jq("#chatBox"):hide()
	jq("#chatWindow"):css("bottom", "0px"):addClass("hide-scrollbar")
end

local function scrollToLast()
	local window = chatWindow()
	local last = window and window.last_child
	if last then
		last:ScrollIntoView(false)
	end
end

local function lineHeight()
	local first = chatWindow() and chatWindow().first_child
	return first and first.offset_height or 20
end

local function onChatBoxKeyUp(event)
	local box = chatBox()
	box:SetClass("mentions", false)
	local key = tonumber(event.parameters.key_identifier)
	local value = boxValue()
	local wordArray = splitWords(value)
	if key == KI_TAB then
		if #value == 0 then -- switch between team chat and global chat
			if not isTeamChat and hasTeams then
				isTeamChat = true
				box:SetAttribute("placeholder", "TEAM")
			else
				isTeamChat = false
				box:SetAttribute("placeholder", "GLOBAL")
			end
		elseif playerTabIndex == -1 then
			local lastWord = wordArray[#wordArray] or ""
			if lastWord ~= "" and startsWith(lastWord, "@") then
				playersMatchList = {}
				local prefix = lastWord:sub(2):lower()
				for _, player in ipairs(cachedPlayerJSON or {}) do
					if startsWith(tostring(player.name):lower(), prefix) then
						playersMatchList[#playersMatchList + 1] = player.name
					end
				end
				playerTabIndex = 0
				if playersMatchList[playerTabIndex + 1] ~= nil then
					wordArray[#wordArray] = "@" .. playersMatchList[playerTabIndex + 1]
					setBoxValue(table.concat(wordArray, " "))
				end
			end
		else
			if tonumber(event.parameters.shift_key) == 1 then
				if playerTabIndex == 0 then
					playerTabIndex = #playersMatchList - 1
				else
					playerTabIndex = playerTabIndex - 1
				end
			else
				playerTabIndex = playerTabIndex + 1
				if playerTabIndex > #playersMatchList - 1 then
					playerTabIndex = 0
				end
			end
			if playersMatchList[playerTabIndex + 1] ~= nil then
				wordArray[#wordArray] = "@" .. playersMatchList[playerTabIndex + 1]
				setBoxValue(table.concat(wordArray, " "))
			end
		end
	elseif key ~= KI_LSHIFT and key ~= KI_RSHIFT then
		playerTabIndex = -1
	end

	if boxValue():find("@", 1, true) and anyPlayerMentioned(boxValue()) then
		box:SetClass("mentions", true)
	end
end

local function handleMouseDown(event)
	if tonumber(event.parameters.button) == 1 then
		chatboxHide()
	end
end

local mouseHandlerActive = false

document:AddEventListener("load", function()
	document:AddEventListener("keyup", function(event)
		local key = tonumber(event.parameters.key_identifier)
		if key == KI_ESCAPE then
			chatboxHide()
		end
		if key == KI_SNAPSHOT then
			dew.command("Game.TakeScreenshot")
		end
	end)
	document:AddEventListener("keydown", function(event)
		local key = tonumber(event.parameters.key_identifier)
		if key == KI_RETURN then
			dew.sendChat(boxValue(), isTeamChat)
			chatboxHide()
		else
			focusBox()
		end
	end)

	local box = chatBox()
	box:AddEventListener("keydown", function(event)
		local key = tonumber(event.parameters.key_identifier)
		local window = chatWindow()
		if key == KI_PRIOR then
			window.scroll_top = window.scroll_top - lineHeight() * 6
		elseif key == KI_NEXT then
			window.scroll_top = window.scroll_top + lineHeight() * 6
		end
	end)
	box:AddEventListener("keyup", onChatBoxKeyUp)

	document:AddEventListener("click", function()
		focusBox()
	end)

	document:AddEventListener("mousedown", function(event)
		if mouseHandlerActive then
			handleMouseDown(event)
		end
	end)

	loadSettings(1)
end)

dew.on("show", function(e)
	local data = e.data or {}
	if (tonumber(settingsArray["Game.HideChat"]) or 0) == 0 then -- JS: == 0, so "" counts too
		playerName = "@" .. tostring(settingsArray["Player.Name"]):lower()
		if data.teamChat ~= nil then
			isTeamChat = data.teamChat == true
		end

		local infectionTeams = false
		dew.getGameVariantInfo():next(function(v)
			if v.mode == 10 then -- Infection
				infectionTeams = true
			end
		end):catch(function() end)

		dew.getSessionInfo():next(function(i)
			if not i.established then
				return
			end
			hasTeams = i.hasTeams == true
			if not hasTeams and infectionTeams and i.mapName ~= "mainmenu" then
				hasTeams = true
			end
			if isTeamChat and not hasTeams then
				isTeamChat = false
			end

			document:SetClass("inGame", i.mapName ~= "mainmenu")
			document:SetClass("inLobby", i.mapName == "mainmenu")
			chatBox():SetAttribute("placeholder", (isTeamChat and hasTeams) and "TEAM" or "GLOBAL")

			if hideTimer then dew.clearTimeout(hideTimer) end
			jq("#chat"):fadeIn(fadeTime / 3)

			if not stayOpen then
				dew.captureInput(data.captureInput)
				if data.captureInput then
					-- opened by the user
					stayOpen = true
					dew.callMethod("chatBoxOpened", { opened = true })
					jq("#chatBox"):show()
					focusBox()
					jq("#chatWindow"):css("bottom", "19.5dp"):removeClass("hide-scrollbar")
					dew.command("Server.ListPlayersJSON", {}):next(function(result)
						cachedPlayerJSON = json.decode(result)
					end)
				else
					-- opened by a chat message arriving
					jq("#chatBox"):hide()
					jq("#chatWindow"):css("bottom", "0px"):addClass("hide-scrollbar")
					fadeAway()
				end
			end
			scrollToLast()
		end)
	end
	mouseHandlerActive = true
end)

dew.on("hide", function()
	dew.callMethod("chatBoxOpened", { opened = false })
	mouseHandlerActive = false
end)

dew.on("chat", function(e)
	local data = e.data or {}
	if playerName == nil then
		playerName = "@" .. tostring(settingsArray["Player.Name"]):lower()
	end

	local bgColor = nil
	if data.color ~= nil then
		bgColor = data.color
		if data.hasTeams and data.teamIndex ~= nil and teamArray[data.teamIndex] then
			bgColor = teamArray[data.teamIndex].color
		end
		bgColor = hexToRgba(adjustColor(bgColor, 20), nameCardOpacity)
	end
	local messageClass = "nameCard"
	local chatClass = tostring(data.chatType or "")
	local message = removeCombiningCharacters(tostring(data.message or ""))

	if message:find("@", 1, true) then
		-- when you are the sender of a mention, highlight your own message
		if anyPlayerMentioned(message) and data.sender == settingsArray["Player.Name"] then
			chatClass = chatClass .. " mentions"
		end
	end

	if playerName and message:lower():find(playerName, 1, true) then
		chatClass = chatClass .. " mention"
	end

	if startsWith(message, "/me ") then
		messageClass = messageClass .. " emote"
		chatClass = chatClass .. " emote"
		message = message:sub(5)
	end

	local maxMessageLength = data.chatType == "SERVER" and 512 or 128
	message = utf8Sub(message, maxMessageLength)

	local messageHtml = dew.escape(message):gsub("(https?://[^ ]+)", aWrap)
	-- ".TEAM span::after { content: ' (TEAM)' }", ".WHISPER span::after { content: ' (TO YOU)' }"
	local suffix = ""
	if data.chatType == "TEAM" then suffix = " (TEAM)" elseif data.chatType == "WHISPER" then suffix = " (TO YOU)" end
	local style = bgColor and string.format(' style="background-color: %s;"', bgColor) or ""
	local window = chatWindow()
	local p = window:AppendChild(document:CreateElement("p"))
	p.class_name = chatClass
	p.inner_rml = string.format('<span class="%s"%s>%s%s</span>%s', messageClass, style, dew.escape(data.sender or ""), suffix, messageHtml)
	for _, link in ipairs(p:QuerySelectorAll(".link")) do
		link:AddEventListener("click", function()
			dew.playSound("a_button")
			local href = link:GetAttribute("data-href")
			dew.dialog("confirm_link", {
				body = "This link goes to " .. href .. "|r|nAre you sure you want to open this?",
			}):next(function(result)
				if result == "yes" then
					dew.openUrl(href)
				end
			end)
		end)
	end

	local messageLimit = tonumber(settingsArray["Game.ChatMessageLimit"]) or 50
	local children = window:QuerySelectorAll("#chatWindow > p")
	for i = 1, #children - messageLimit do
		window:RemoveChild(children[i])
	end

	if (tonumber(settingsArray["Game.HideChat"]) or 0) == 0 then -- JS: == 0, so "" counts too
		dew.show()
	end
	scrollToLast()
end)

dew.on("controllerinput", function(e)
	if (e.data or {}).B == 1 then
		chatboxHide()
	end
end)

dew.on("variable_update", function(e)
	for _, v in ipairs(e.data or {}) do
		if settingsArray[v.name] ~= nil then
			settingsArray[v.name] = v.value
		end
	end
end)
