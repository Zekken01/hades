-- Port of screens/loading/loading.js

local mapName = ""
local gameModes = { [0] = "slayer", "ctf", "slayer", "oddball", "koth", "forge", "vip", "juggernaut", "territories", "assault", "infection" }
local firstRun = true

-- KI values: T, Y, `~ (OEM_3), F1, Print Screen
local KI_T, KI_Y, KI_OEM_3, KI_F1, KI_SNAPSHOT = 31, 36, 44, 107, 97

document:AddEventListener("keydown", function(event)
	local key = tonumber(event.parameters.key_identifier)
	if key == KI_T or key == KI_Y then
		dew.show("chat", { captureInput = true, teamChat = key == KI_Y })
	end
	if key == KI_OEM_3 or key == KI_F1 then
		dew.show("console")
	end
end)

document:AddEventListener("keyup", function(event)
	if tonumber(event.parameters.key_identifier) == KI_SNAPSHOT then
		dew.command("Game.TakeScreenshot")
	end
end)

-- text.split("\\n") on the literal two characters, each line trimmed and escaped
local function textWithNewLines(text)
	local lines, start = {}, 1
	while true do
		local i, j = text:find("\\n", start, true) -- the two characters \ and n, as split("\\n")
		local line = i and text:sub(start, i - 1) or text:sub(start)
		lines[#lines + 1] = dew.escape((line:gsub("^%s+", ""):gsub("%s+$", "")))
		if not i then
			break
		end
		start = j + 1
	end
	return table.concat(lines, "<br/>")
end

local function aWrap(link)
	local raw = link:gsub("&amp;", "&"):gsub("&lt;", "<"):gsub("&gt;", ">"):gsub("&quot;", '"'):gsub("&#39;", "'")
	if raw:find("[^%w%-+&@#/%%?=~_|!:,.;()]") then
		return ""
	end
	return '<span class="link" style="color: #1e90ff;" data-href="' .. link .. '">' .. link .. "</span>"
end

local function updateProgress(progress)
	jq("#progressvalue"):css("width", string.format("%.2f%%", progress))
	-- clip-path: inset(progress% 0 0 0) on the blue logo
	jq("#logoclip"):css("height", string.format("%.2f%%", 100 - progress))
end

local function setPakImage(selector, pak, url, fallback)
	local element = jq(selector):get(0)
	if not element then return end
	element:SetAttribute("data-pak", pak)
	element:SetAttribute("data-url", url)
	element:SetAttribute("data-fallback", fallback)
	pakAwareContext.invalidateElement(element)
end

local function loadMap(info)
	local hasMod = type(info.modHash) == "string" and #info.modHash > 0
	jq("#blackLayer"):hide()
	jq(".genericLoader"):hide()

	setPakImage("#mapImage", "game", "assets/maps/large/" .. tostring(info.map), "dew://assets/maps/large/unknown.jpg")

	jq("#blackLayer"):fadeIn(100, function()
		jq(".mapLoader"):show()
		dew.setTimeout(function()
			jq("#blackLayer"):fadeOut(600)
		end, 200)
	end)

	jq("#title"):addClass("title"):removeClass("titleMod")
	jq("#author"):addClass("mapauthor"):removeClass("mapauthorMod")

	jq("#title"):text(info.mapName or "")
	jq("#desc"):text(info.mapDescription or "")

	if info.gameMode == 1 then
		if info.insertionPointDescription == info.mapDescription then
			jq("#desc"):text("")
		end
		jq("#pointdesc"):text(info.insertionPointDescription or "")
		jq("#point"):text(info.insertionPointName or "")

		local skulls = {}
		for i, skull in ipairs(info.skulls or {}) do
			-- insertAdjacentHTML('afterbegin'): each skull goes in front of the previous ones
			table.insert(skulls, 1, string.format('<img id="skull%d" class="skulls" data-pak="game" data-url="assets/skulls/%s" data-fallback="dew://assets/skulls/blank.png"/>', i - 1, dew.escape(skull)))
		end
		jq("#skulls"):html(table.concat(skulls))
		for i = 1, #(info.skulls or {}) do
			pakAwareContext.invalidateElement(jq("#skull" .. (i - 1)):get(0))
		end

		setPakImage("#difficulty", "mainmenu", "assets/difficulty/" .. tostring(info.difficulty), "dew://assets/difficulty/easy.png")

		jq("#pointdesc"):show()
		jq("#point"):show()
		jq("#skulls"):show()
		jq(".gamerounds"):hide()
		jq(".gamescore"):hide()
		jq(".timelimit"):hide()
		jq(".serverName"):hide()
		jq("#gametype"):hide()
		jq("#gametypeicon"):hide()
		jq(".serverMessage"):hide()
		jq("#difficulty"):show()
		jq(".modname"):hide()
		jq(".modauthor"):hide()
		jq("#author"):hide()
	else
		jq("#difficulty"):hide()
		jq(".gamerounds"):show()
		jq(".gamescore"):show()
		jq(".timelimit"):show()
		jq(".serverName"):show()
		jq("#skulls"):hide()
		jq("#pointdesc"):hide()
		jq("#point"):hide()
		jq("#gametype"):show()
		jq("#gametypeicon"):show()
		jq("#author"):show()

		local author = info.mapAuthor or ""
		jq("#mapauthor"):text(#author > 0 and author or "None")

		if hasMod then
			jq("#title"):addClass("titleMod"):removeClass("title")
			jq("#author"):addClass("mapauthorMod"):removeClass("mapauthor")
			jq("#modname"):text(tostring(info.modName) .. " " .. tostring(info.modVersion))
			jq("#modauthor"):text(info.modAuthor or "")
			jq(".modname"):show()
			jq(".modauthor"):show()
		else
			jq(".modname"):hide()
			jq(".modauthor"):hide()
		end

		setPakImage("#gametypeicon", "game", "assets/gametypes/" .. tostring(gameModes[info.mode or 0]), "dew://assets/gametypes/slayer.png")

		jq("#gametype"):text(info.gameType or "")
		jq("#gamerounds"):text((info.rounds or 0) > 0 and tostring(info.rounds) or "Unlimited")
		jq("#gamescore"):text((info.scoreToWin or -1) > -1 and tostring(info.scoreToWin) or "Unlimited")
		jq("#timelimit"):text((info.timeLimit or 0) > 0 and (tostring(info.timeLimit) .. ":00") or "Unlimited")

		jq(".serverName"):text(info.serverName or "")

		local message = info.serverMessage or ""
		if #message > 0 then
			message = message:sub(1, 512)
			local html = textWithNewLines(message):gsub("(https?://[^ ]+)", aWrap)
			jq(".serverMessage"):html(html):show()
			jq(".serverMessage .link"):on("click", function(_, element)
				dew.openUrl(element:GetAttribute("data-href"))
			end)
		else
			jq(".serverMessage"):hide()
		end
	end
end

local function loadGeneric()
	if firstRun then
		jq(".genericLoader"):fadeIn(1000)
		firstRun = false
	else
		jq(".genericLoader"):fadeIn(200)
	end
	jq("#blackLayer"):hide()
	jq(".mapLoader"):hide()
end

local function resetLoader()
	jq("#blackLayer"):hide()
	jq(".genericLoader"):hide()
	jq(".mapLoader"):hide()
	for _, selector in ipairs({ "#gametype", "#gamerounds", "#gamescore", "#timelimit", ".serverName", ".serverMessage", ".title", ".desc" }) do
		jq(selector):text("")
	end
	jq("#gametypeicon"):attr("src", "")
end

dew.on("show", function(event)
	local data = event.data or {}
	mapName = data.map or ""
	if mapName ~= "mainmenu" and mapName ~= "" then
		loadMap(data)
		dew.captureInput(true)
	else
		loadGeneric()
		dew.captureInput(false)
	end
	updateProgress(0)
end)

dew.on("hide", function()
	resetLoader()
end)

dew.on("loadprogress", function(event)
	local data = event.data or {}
	local total = tonumber(data.totalBytes) or 0
	local progress = total > 0 and (tonumber(data.currentBytes) or 0) / total * 100 or 0
	updateProgress(progress)
end)
