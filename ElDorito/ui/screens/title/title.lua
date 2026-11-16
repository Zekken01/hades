-- Port of screens/title/title.js

local announcementShown = false
local isVisible = false
local inputReady = false

-- KI values
local KI_SPACE, KI_RETURN, KI_ESCAPE, KI_OEM_3, KI_F1, KI_OEM_8, KI_SNAPSHOT = 1, 72, 81, 44, 107, 49, 97

-- announcement dates: ISO (2024-05-01[T...]) or MM.DD.YYYY / MM/DD/YYYY; invalid -> 03.01.2015
local DEFAULT_DATE = os.time({ year = 2015, month = 3, day = 1, hour = 0 })
local function parseDate(text)
	if type(text) ~= "string" then
		return nil
	end
	local y, m, d, hh, mm, ss = text:match("^(%d%d%d%d)%-(%d%d?)%-(%d%d?)[T ]?(%d*):?(%d*):?(%d*)")
	if not y then
		m, d, y = text:match("^(%d%d?)[%./%-](%d%d?)[%./%-](%d%d%d%d)")
	end
	if not y then
		return nil
	end
	return os.time({ year = tonumber(y), month = tonumber(m), day = tonumber(d),
		hour = tonumber(hh) or 0, min = tonumber(mm) or 0, sec = tonumber(ss) or 0 })
end

local function isNewerDate(date1, date2)
	return (parseDate(date1) or DEFAULT_DATE) > (parseDate(date2) or DEFAULT_DATE)
end

local function hideScreen()
	if isVisible then
		isVisible = false
		dew.GameBlur("title", false)
		dew.command("game.hideh3ui 0")
		jq(document):fadeOut(500, function()
			dew.hide()
		end)
		dew.playSound("a_button")
	end
end

local function announcements()
	return document:QuerySelectorAll(".announcement")
end

function closeAnnounce()
	if not inputReady then
		return
	end
	local list = announcements()
	local last = list[#list]
	if last then
		local lastdate = last:GetAttribute("data-date")
		if lastdate then
			dew.command('Game.AnnoucementViewed "' .. tostring(lastdate) .. '"')
		end
		last.parent_node:RemoveChild(last)
	end
	if #announcements() == 0 then
		jq("#announcementBox"):hide()
		jq("#announcementBG"):hide()
		announcementShown = false
		dew.command("Game.FirstRun 0", {}):next(function()
			dew.command("writeconfig")
		end)
	end
	dew.playSound("a_button")
end

local function addAnnouncement(entry)
	local box = document:GetElementById("announcementBox")
	local first = box.first_child
	local created = document:CreateElement("div")
	-- $('#announcementBox').prepend(...)
	local element = first and box:InsertBefore(created, first) or box:AppendChild(created)
	element:SetClass("announcement", true)
	element:SetAttribute("data-date", tostring(entry.date or ""))
	element.inner_rml = string.format(
		'<p class="announceTitle">%s<p class="announcesubTitle">%s</p><p class="announceContent">%s</p></p>',
		dew.escape(entry.title or ""), dew.escape(entry.subtitle or ""), htmlToRml(entry.content or ""))
	wireLinks(element)
	-- background-image: url(remote); downloaded into the UI cache first
	if type(entry.background) == "string" and entry.background ~= "" then
		local function apply(url)
			element.style.decorator = "image(" .. url .. " cover)"
		end
		if entry.background:match("^https?://") then
			dew.fetchImage(entry.background):next(apply)
		else
			apply(entry.background)
		end
	end
end

local function showAnnouncements()
	dew.command("server.getendpoint announcements"):next(function(announcementUrl)
		local endpoint = announcementUrl .. "?t=" .. tostring(math.floor(dew_core.getTime() * 1000))
		dew.fetchJson(endpoint):next(function(data)
			dew.command("Game.AnnoucementViewed"):next(function(announcementViewed)
				local list = data.announcements or {}
				if #list == 0 then
					return
				end
				local shouldShow = false
				for _, entry in ipairs(list) do
					if isNewerDate(entry.date, announcementViewed) then
						shouldShow = true
						addAnnouncement(entry)
					end
				end
				if shouldShow then
					announcementShown = true
					jq("#announcementBox"):show()
					jq("#announcementBG"):show()
				end
			end)
		end)
	end)
end

local function setControlsLegend()
	dew.command("Settings.Gamepad"):next(function(gamepadEnabled)
		if tonumber(gamepadEnabled) == 1 then
			jq(".instructionText"):text("Press any button to continue")
			jq("#dpad"):attr("src", "dew://assets/buttons/360_Dpad.png"):show()
			jq("#up"):hide(); jq("#down"):hide(); jq("#left"):hide(); jq("#right"):hide()
			jq("#esc"):attr("src", "dew://assets/buttons/360_B.png")
			jq("#enter"):attr("src", "dew://assets/buttons/360_A.png")
			jq("#mouse"):hide()
		else
			jq(".instructionText"):text("Press any key to continue")
			jq("#mouse"):show()
			jq("#dpad"):hide()
			jq("#up"):show(); jq("#down"):show(); jq("#left"):show(); jq("#right"):show()
			jq("#esc"):attr("src", "dew://assets/buttons/Keyboard_White_Esc.png")
			jq("#enter"):attr("src", "dew://assets/buttons/Keyboard_White_Enter.png")
		end
	end)
end

document:AddEventListener("keyup", function(event)
	if tonumber(event.parameters.key_identifier) == KI_SNAPSHOT then
		dew.command("Game.TakeScreenshot")
	end
end)

document:AddEventListener("mouseup", function()
	if not inputReady then
		return
	end
	if not announcementShown then
		hideScreen()
	end
end)

document:AddEventListener("keydown", function(event)
	if not inputReady then
		return
	end
	local key = tonumber(event.parameters.key_identifier)
	if key == KI_OEM_3 or key == KI_F1 or key == KI_OEM_8 then
		hideScreen()
		dew.show("console")
	elseif key == KI_SPACE or key == KI_RETURN or key == KI_ESCAPE then
		if not announcementShown then
			hideScreen()
		else
			closeAnnounce()
		end
	end
end)

dew.on("hide", function()
	dew.GameBlur("title", false)
	dew.command("game.hideh3ui 0")
end)

dew.on("show", function(e)
	isVisible = true
	jq(document):show()
	if (e.data or {}).firstBoot == nil then
		inputReady = true
		dew.captureInput(true)
	else
		dew.captureInput(false)
	end

	dew.command("Game.SkipTitleSplash"):next(function(skipTitleSplash)
		if tonumber(skipTitleSplash) == 1 then
			dew.hide()
		else
			dew.GameBlur("title", true)
			dew.command("game.hideh3ui 1")
			showAnnouncements()
			setControlsLegend()
		end
	end)
end)

dew.on("serverconnect", function()
	hideScreen()
end)

dew.on("controllerinput", function(e)
	if not isVisible or not inputReady then
		return
	end
	local c = e.data or {}
	if announcementShown then
		if c.A == 1 then
			closeAnnounce()
		end
	elseif c.Start == 1 or c.Select == 1 or c.A == 1 or c.B == 1 or c.X == 1 or c.Y == 1 or c.LeftBumper == 1
		or c.RightBumper == 1 or c.Up == 1 or c.Down == 1 or c.Left == 1 or c.Right == 1 then
		hideScreen()
	end
end)

dew.on("loadingFinished", function()
	if isVisible then
		dew.setTimeout(function()
			inputReady = true
		end, 1000)
		dew.captureInput(true)
	end
end)
