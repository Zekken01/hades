--[[
	ingame_voting.lua -- port of lib/ingame_voting/ingame_voting.js.

		local widget = dew.ingameVoting.makeWidget(document:GetElementById("voteWidget"))
		widget.on("vote_started", function() dew.show() end)

	Renders "N more votes needed to <action>" and a Vote button from the chat vote
	variables (variable_update).
]]

dew.ingameVoting = {}

function dew.ingameVoting.makeWidget(containerElement)
	local voteAction = ""
	local votesNeeded = 0
	local hasFocus = false
	local isHidden = true
	local hasVoted = false
	local callbacks = {}
	local render, submitVote

	local function emit(eventName, data)
		for _, cb in ipairs(callbacks[eventName] or {}) do
			cb(data)
		end
	end

	render = function()
		local visible = not isHidden and voteAction ~= nil and #voteAction > 0
		local hideButton = (not hasFocus) or hasVoted
		containerElement.inner_rml = string.format([[
			<span>
				<span class="chat_vote_text_secondary">%s</span> more votes needed to
				<span class="chat_vote_text_secondary">%s</span>
			</span>
			<button data-target="chatVoteButton" class="chat_vote_button"%s><img src="dew://assets/buttons/360_Y.png"/> Vote</button>]],
			dew.escape(tostring(votesNeeded)), dew.escape(voteAction or ""), hideButton and ' style="display: none;"' or "")
		containerElement.style.display = visible and "flex" or "none"
		local button = containerElement:QuerySelector('button[data-target="chatVoteButton"]')
		if button then
			button:AddEventListener("click", function() submitVote() end)
		end
	end

	submitVote = function()
		hasVoted = true
		render()
		dew.sendChat("!yes", false)
	end

	render()

	dew.on("variable_update", function(message)
		for _, v in ipairs(message.data or {}) do
			if v.shortName == "chat_votes_needed_client" then
				votesNeeded = tonumber(v.value) or 0
				render()
			elseif v.shortName == "chat_vote_started_client" then
				isHidden = (tonumber(v.value) or 0) == 0
				render()
				emit(dew.truthy(v.value) and "vote_started" or "vote_ended")
			elseif v.shortName == "chat_vote_action_client" then
				voteAction = tostring(v.value or "")
				render()
			elseif v.shortName == "chat_vote_started_by_uid_client" then
				dew.getSessionInfo():next(function(result)
					hasVoted = result.playerInfo and result.playerInfo.Uid == v.value
					render()
				end)
			end
		end
	end)

	return {
		on = function(eventName, cb)
			callbacks[eventName] = callbacks[eventName] or {}
			table.insert(callbacks[eventName], cb)
		end,
		focus = function() hasFocus = true end,
		blur = function() hasFocus = false end,
		toggleVisibility = function(visible) isHidden = not visible end,
		vote = function() submitVote() end,
		render = function() render() end,
	}
end
