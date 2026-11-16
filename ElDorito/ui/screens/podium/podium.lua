-- Port of screens/podium/podium.js

local valid = false
local hideTimer = nil

local ALL = { "player1", "player2", "player3", "kills", "assists", "deaths", "streak" }
-- streak is the last box out: delay 0.35s + 0.4s (its animationend)
local OUT_DURATION_MS = 750

local function el(id) return document:GetElementById(id) end

-- start the "In" slide: the start state now, the end state next frame (transition)
local function slideIn(id)
	local element = el(id)
	if not element then
		return
	end
	element:SetClass("out", false)
	element:SetClass("in", false)
	element.style.display = "block"
	dew.requestAnimationFrame(function()
		dew.requestAnimationFrame(function()
			if element.style.display ~= "none" then
				element:SetClass("in", true)
			end
		end)
	end)
end

local function setEmblem(imageId, data, playersInfo)
	local emblemPath = "dew://assets/emblems/generic.png"
	local info = playersInfo[(tonumber(data.playerIndex) or -1) + 1]
	if info then
		if dew.truthy(info.e) then
			emblemPath = info.e
		else
			emblemPath = data.emblem
		end
	end
	if not dew.truthy(emblemPath) then
		emblemPath = "dew://assets/emblems/generic.png"
	end
	jq("#" .. imageId):attr("src", tostring(emblemPath))
end

dew.on("podium", function(e)
	local data = e.data or {}
	valid = true
	if hideTimer then
		dew.clearTimeout(hideTimer)
		hideTimer = nil
	end
	dew.show()

	local playersInfo = data.playersInfo or {}
	local place = tonumber(data.place) or -1
	if place ~= -1 then
		if place == 2 then
			jq("#player3_score"):text(data.score)
			jq("#player3_name"):text(data.playername)
			setEmblem("third_emblem", data, playersInfo)
			slideIn("player3")
		end
		if place == 1 then
			jq("#player2_score"):text(data.score)
			jq("#player2_name"):text(data.playername)
			setEmblem("second_emblem", data, playersInfo)
			slideIn("player2")
		end
		if place == 0 then
			jq("#player1_score"):text(data.score)
			jq("#player1_name"):text(data.playername)
			setEmblem("first_emblem", data, playersInfo)
			slideIn("player1")
		end
	end

	if dew.truthy(data.extraStats) then
		jq("#killsText"):text(data.kills)
		jq("#assistsText"):text(data.assists)
		jq("#deathsText"):text(data.deaths)
		jq("#streakText"):text(data.streak)
		for _, id in ipairs({ "kills", "assists", "deaths", "streak" }) do
			slideIn(id)
		end
	end
end)

dew.on("podium_hide", function()
	if valid then
		for _, id in ipairs(ALL) do
			local element = el(id)
			if element then
				element:SetClass("in", false)
				element:SetClass("out", true)
			end
		end
		hideTimer = dew.setTimeout(function()
			hideTimer = nil
			dew.hide()
			dew.notify("script-show-scoreboard", { animate = true })
		end, OUT_DURATION_MS)
		valid = false
	end
end)

dew.on("show", function()
	if not valid then
		for _, id in ipairs(ALL) do
			slideIn(id)
		end
	end
end)

dew.on("hide", function()
	for _, id in ipairs(ALL) do
		local element = el(id)
		if element then
			element.style.display = "none"
			element:SetClass("in", false)
			element:SetClass("out", false)
		end
	end
	if hideTimer then
		dew.clearTimeout(hideTimer)
		hideTimer = nil
	end
end)

dew.on("mouseCapture", function(e)
	local data = e.data or {}
	local visibility
	if dew.truthy(data.blocked) then
		visibility = "hidden"
	elseif not dew.truthy(data.tagMenuOpen) then
		visibility = "visible"
	end
	if visibility then
		for _, id in ipairs(ALL) do
			jq("#" .. id):css("visibility", visibility)
		end
	end
end)
