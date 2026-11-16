--[[
	voip.lua -- the overlay half of screens/voip (rtc.js speaking list + voip_stats.js).

	The WebRTC transport of rtc.js moves to native code (Phase 5).  That module feeds this
	screen with two events and leaves the presentation logic of rtc.js here:

	  voip-peer-speaking { user, isSpeaking, volume, muted }
	      speak()/stopSpeak(): notify "voip-speaking", call playerSpeaking, and show the
	      name on this overlay when on the main menu, while a map loads, or when
	      VoIP.SpeakingPlayerOnHUD is 0.
	  voip-stats { peers = [ { uid, connectionState, iceConnectionState, iceType,
	      outgoingBitrate, incomingBitrate, packetsSent, packetsReceived, packetsLost } ] }
	      one table refresh (the native module sends it every second while VoIP.Stats is 1).
]]

local speaking = {}                        -- users currently speaking (rtc.js `speaking`)
local previouslyDisplayedSpeakersOnHUD = false
local statsEnabled = false
local speakingElement, statsElement

local function indexOf(list, value)
	for i, v in ipairs(list) do
		if v == value then return i end
	end
	return nil
end

------------------------------------------------------------------------------------------
-- speaking list (jQuery transforms -> inline transforms with an RCSS transition)
------------------------------------------------------------------------------------------

local function rows()
	local list = {}
	for _, child in ipairs(speakingElement.child_nodes) do
		list[#list + 1] = child
	end
	return list
end

local function translate(element, x, y)
	element.style.transform = string.format("translate(%.1fpx, %.1fpx)", x, y)
end

local function addToSpeakingPlayersList(user)
	local existing = rows()
	for i, row in ipairs(existing) do
		translate(row, 0, row.offset_height * i)
	end
	-- CreateElement hands back an owning pointer: insert it, then style the element
	local pointer = document:CreateElement("p")
	local added
	if existing[1] then
		added = speakingElement:InsertBefore(pointer, existing[1])
	else
		added = speakingElement:AppendChild(pointer)
	end
	added:SetAttribute("user", user)
	added.inner_rml = dew.escape(user)
	added.style.transform = "translate(0px, -100dp)"
	dew.setTimeout(function()
		for _, row in ipairs(rows()) do
			if row:GetAttribute("user") == user and not row:IsClassSet("leaving") then
				translate(row, 0, 0)
			end
		end
	end, 25)
	return added
end

local function removeFromSpeakingPlayersList(user)
	local list = rows()
	local index
	for i, row in ipairs(list) do
		if row:GetAttribute("user") == user and not row:IsClassSet("leaving") then
			index = i
			break
		end
	end
	if not index then return end
	for i, row in ipairs(list) do
		local height = row.offset_height
		if i > index then
			translate(row, 0, height * (i - 1) - height)
		elseif i == index then
			row:SetClass("leaving", true)
			translate(row, -200, height * i - height)
			dew.setTimeout(function()
				for _, r in ipairs(rows()) do
					if r:GetAttribute("user") == user and r:IsClassSet("leaving") then
						speakingElement:RemoveChild(r)
						break
					end
				end
			end, 300)
		end
	end
end

local function populateSpeakingPlayersList()
	for _, user in ipairs(speaking) do
		addToSpeakingPlayersList(user)
	end
end

local function destroySpeakingPlayersList()
	speakingElement.inner_rml = ""
end

-- rtc.js speak()/stopSpeak() after the peer bookkeeping
local function onPeerSpeaking(data)
	local user = tostring(data.user or "")
	local isSpeaking = data.isSpeaking == true
	dew.notify("voip-speaking", { user = user, volume = data.volume or 0, isSpeaking = isSpeaking })

	if isSpeaking and data.muted then
		return -- prevent the name from showing if they are muted
	end

	dew.getSessionInfo():next(function(info)
		dew.callMethod("isMapLoading", {}):next(function(mapLoadingRes)
			dew.command("VoIP.SpeakingPlayerOnHUD"):next(function(hudToggleRes)
				dew.callMethod("playerSpeaking", { name = user, value = isSpeaking })

				local loading = false
				local ok, decoded = pcall(json.decode, mapLoadingRes)
				if ok and type(decoded) == "table" then loading = decoded.loading == true end
				local useOverlay = (info and info.mapName == "mainmenu") or loading or tonumber(hudToggleRes) == 0

				if isSpeaking then
					if indexOf(speaking, user) then return end
					speaking[#speaking + 1] = user
				else
					local index = indexOf(speaking, user)
					if index then table.remove(speaking, index) end
				end

				if useOverlay then
					if previouslyDisplayedSpeakersOnHUD then
						populateSpeakingPlayersList()
					elseif isSpeaking then
						addToSpeakingPlayersList(user)
					else
						removeFromSpeakingPlayersList(user)
					end
					previouslyDisplayedSpeakersOnHUD = false
				else
					if not previouslyDisplayedSpeakersOnHUD then
						destroySpeakingPlayersList()
					end
					previouslyDisplayedSpeakersOnHUD = true
				end
			end)
		end)
	end)
end

------------------------------------------------------------------------------------------
-- voip_stats.js
------------------------------------------------------------------------------------------

local function formatBitrate(bitrate)
	bitrate = tonumber(bitrate) or 0
	if bitrate >= 1000000000 then
		return string.format("%.2f Gbps", bitrate / 1000000000)
	elseif bitrate >= 1000000 then
		return string.format("%.2f Mbps", bitrate / 1000000)
	elseif bitrate >= 1000 then
		return string.format("%.2f kbps", bitrate / 1000)
	end
	return string.format("%.2f bps", bitrate)
end

local function displayStats(peers)
	local rowsHtml = {}
	for _, peer in ipairs(peers or {}) do
		local cells = {
			dew.escape(tostring(peer.uid or "")),
			dew.escape(tostring(peer.connectionState or "-")),
			dew.escape(tostring(peer.iceConnectionState or "-")),
			dew.escape(tostring(peer.iceType or "- / -")),
			formatBitrate(peer.outgoingBitrate),
			formatBitrate(peer.incomingBitrate),
			tostring(peer.packetsSent or 0),
			tostring(peer.packetsReceived or 0),
			tostring(peer.packetsLost or 0),
		}
		rowsHtml[#rowsHtml + 1] = "<tr><td>" .. table.concat(cells, "</td><td>") .. "</td></tr>"
	end
	statsElement.inner_rml = "<table><thead><tr><th>User</th><th>Connection State</th><th>Ice State</th>"
		.. "<th>Ice Type</th><th>Out Bitrate</th><th>In Bitrate</th><th>Packets Sent</th><th>Packets Recv</th>"
		.. "<th>Packets Lost</th></tr></thead><tbody>" .. table.concat(rowsHtml) .. "</tbody></table>"
end

local function toggleStats(enable)
	statsEnabled = enable
	statsElement:SetClass("hidden", not enable)
	if enable then
		displayStats({})
	end
end

------------------------------------------------------------------------------------------

function init()
	speakingElement = document:GetElementById("speaking")
	statsElement = document:GetElementById("stats")

	dew.on("voip-peer-speaking", function(e)
		onPeerSpeaking(e.data or {})
	end)

	dew.on("voip-stats", function(e)
		if statsEnabled then
			displayStats((e.data or {}).peers)
		end
	end)

	dew.on("variable_update", function(e)
		for _, variable in ipairs(e.data or {}) do
			if variable.name == "VoIP.Stats" then
				toggleStats(tonumber(variable.value) == 1)
			end
		end
	end)

	dew.command("voip.update", {})
	dew.show()

	dew.command("VoIP.Stats"):next(function(value)
		toggleStats(tonumber(value) == 1)
	end)
end
