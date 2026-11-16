--[[
	input.lua -- the Lua port of lib/input.js (dew.input).

	Turns the game's per-tick controller state (the "controllerinput" event) plus the
	keyboard into the same 'tick', 'scroll', 'right_scroll' and 'action' events the web
	screens used, with identical timing.  Use from a screen's <head>:

		<script src="dew://lib/input.lua"></script>
		dew.input.on("action", function(e) ... end)   -- e = { inputType, action }
		dew.input.on("scroll", function(type, axis, direction) ... end)
]]

local HOLD_DELAY = 0.9
local HELD_SCROLL_SPEED = 0.11
local SINGLE_SCROLL_SPEED = 0.325
local CONTROLLER_AXIS_THRESHOLD = 0.5

local UiAction = {
	LeftTrigger = 0, RightTrigger = 1, Up = 2, Down = 3, Left = 4, Right = 5, Start = 6,
	Select = 7, LeftStick = 8, RightStick = 9, A = 10, B = 11, X = 12, Y = 13,
	LeftBumper = 14, RightBumper = 15,
}

local UiSound = {
	Error = 0, VerticalNavigation = 1, HorizontalNavigation = 2, A = 3, B = 4, X = 5, Start = 7,
	Back = 8, LeftBumper = 9, RightBumper = 10, LeftTrigger = 11, RightTrigger = 12,
}

-- Rml::Input::KeyIdentifier values for the keys input.js watched.
local KI = {
	UP = 91, DOWN = 93, LEFT = 90, RIGHT = 92, SPACE = 1, RETURN = 72, ESCAPE = 81,
	PRIOR = 86, NEXT = 87, DELETE = 99, X = 35, Q = 28, E = 16,
}

local callbacks = {}
local leftStick, rightStick
local lastScrollHeldUpdate, lastRightStickHeldUpdate, lastScrollTime, lastRightScrollTime
local keyStates, keyTicks

local function reset()
	keyStates = {}
	keyTicks = {}
	leftStick = { left = 0, right = 0, up = 0, down = 0 }
	rightStick = { left = 0, right = 0, up = 0, down = 0 }
	lastScrollHeldUpdate = 0
	lastRightStickHeldUpdate = 0
	lastScrollTime = 0
	lastRightScrollTime = 0
end
reset()

local function emit(event, ...)
	local list = callbacks[event]
	if not list then
		return
	end
	-- copy: handlers may remove themselves
	local copy = { table.unpack(list) }
	for _, callback in ipairs(copy) do
		callback(...)
	end
end

local function kt(action)
	return keyTicks[action] or 0
end

local function bumpKey(action, down)
	if down then keyTicks[action] = kt(action) + 1 else keyTicks[action] = 0 end
end

local function clamp255(t)
	for k, v in pairs(t) do
		if v > 255 then t[k] = 255 end
	end
end

local function tick(message)
	local c = message.data or {}
	local spt = c.secondsPerTick or (1 / 60)
	local gameTicks = c.gameTicks or 0
	local function n(v) return v or 0 end

	if gameTicks == 0 then
		lastScrollTime = gameTicks
		lastRightScrollTime = gameTicks
	end

	emit("tick")

	bumpKey(UiAction.Down, keyStates[KI.DOWN])
	bumpKey(UiAction.Up, keyStates[KI.UP])
	bumpKey(UiAction.Left, keyStates[KI.LEFT])
	bumpKey(UiAction.Right, keyStates[KI.RIGHT])
	bumpKey(UiAction.A, keyStates[KI.SPACE] or keyStates[KI.RETURN])
	bumpKey(UiAction.B, keyStates[KI.ESCAPE])
	bumpKey(UiAction.LeftTrigger, keyStates[KI.PRIOR])
	bumpKey(UiAction.RightTrigger, keyStates[KI.NEXT])
	bumpKey(UiAction.Y, keyStates[KI.DELETE])
	bumpKey(UiAction.X, keyStates[KI.X])
	bumpKey(UiAction.LeftBumper, keyStates[KI.Q])
	bumpKey(UiAction.RightBumper, keyStates[KI.E])

	clamp255(leftStick)
	clamp255(rightStick)

	local ax, ay, rx, ry = n(c.AxisLeftX), n(c.AxisLeftY), n(c.AxisRightX), n(c.AxisRightY)
	leftStick.right = ax > CONTROLLER_AXIS_THRESHOLD and leftStick.right + 1 or 0
	leftStick.left = ax < -CONTROLLER_AXIS_THRESHOLD and leftStick.left + 1 or 0
	leftStick.up = ay > CONTROLLER_AXIS_THRESHOLD and leftStick.up + 1 or 0
	leftStick.down = ay < -CONTROLLER_AXIS_THRESHOLD and leftStick.down + 1 or 0
	rightStick.right = rx > CONTROLLER_AXIS_THRESHOLD and rightStick.right + 1 or 0
	rightStick.left = rx < -CONTROLLER_AXIS_THRESHOLD and rightStick.left + 1 or 0
	rightStick.up = ry > CONTROLLER_AXIS_THRESHOLD and rightStick.up + 1 or 0
	rightStick.down = ry < -CONTROLLER_AXIS_THRESHOLD and rightStick.down + 1 or 0

	local up, down, left, right = n(c.Up), n(c.Down), n(c.Left), n(c.Right)
	local kUp, kDown, kLeft, kRight = kt(UiAction.Up), kt(UiAction.Down), kt(UiAction.Left), kt(UiAction.Right)

	if n(c.LeftTrigger) == 1 or kt(UiAction.LeftTrigger) == 1 then
		emit("scroll", 2, 0, -1)
	end
	if n(c.RightTrigger) == 1 or kt(UiAction.RightTrigger) == 1 then
		emit("scroll", 2, 0, 1)
	end

	-- held: `a` held for longer than HOLD_DELAY without its opposite `b`
	local function held(a, b) return a > 1 and b == 0 and a * spt > HOLD_DELAY end
	-- short press repeats: held, but not yet past the hold delay
	local function early(a, b) return a > 1 and b == 0 and a * spt < HOLD_DELAY - HELD_SCROLL_SPEED end

	if (gameTicks - lastScrollHeldUpdate) * spt > HELD_SCROLL_SPEED then
		if held(leftStick.up, leftStick.down) or held(up, down) or held(kUp, kDown) then
			lastScrollHeldUpdate = gameTicks
			emit("scroll", 1, 0, -1)
		end
		if held(leftStick.down, leftStick.up) or held(down, up) or held(kDown, kUp) then
			lastScrollHeldUpdate = gameTicks
			emit("scroll", 1, 0, 1)
		end
		if held(leftStick.right, leftStick.left) or held(right, left) or held(kRight, kLeft) then
			lastScrollHeldUpdate = gameTicks
			emit("scroll", 1, 1, 1)
		end
		if held(leftStick.left, leftStick.right) or held(left, right) or held(kLeft, kRight) then
			lastScrollHeldUpdate = gameTicks
			emit("scroll", 1, 1, -1)
		end
	end

	if (gameTicks - lastRightStickHeldUpdate) * spt > HELD_SCROLL_SPEED then
		if held(rightStick.up, rightStick.down) then
			lastRightStickHeldUpdate = gameTicks
			emit("right_scroll", 1, 0, -1)
		end
		if held(rightStick.down, rightStick.up) then
			lastRightStickHeldUpdate = gameTicks
			emit("right_scroll", 1, 0, 1)
		end
		if held(rightStick.right, rightStick.left) then
			lastRightStickHeldUpdate = gameTicks
			emit("right_scroll", 1, 1, 1)
		end
		if held(rightStick.left, rightStick.right) then
			lastRightStickHeldUpdate = gameTicks
			emit("right_scroll", 1, 1, -1)
		end
	end

	if (gameTicks - lastScrollTime) * spt > SINGLE_SCROLL_SPEED then
		if early(leftStick.up, leftStick.down) or early(up, down) or early(kUp, kDown) then
			lastScrollTime = gameTicks
			emit("scroll", 1, 0, -1)
		end
		if early(leftStick.down, leftStick.up) or early(down, up) or early(kDown, kUp) then
			lastScrollTime = gameTicks
			emit("scroll", 1, 0, 1)
		end
		if early(leftStick.right, leftStick.left) or early(right, left) or early(kRight, kLeft) then
			lastScrollTime = gameTicks
			emit("scroll", 1, 1, 1)
		end
		if early(leftStick.left, leftStick.right) or early(left, right) or early(kLeft, kRight) then
			lastScrollTime = gameTicks
			emit("scroll", 1, 1, -1)
		end
	end

	if (gameTicks - lastRightScrollTime) * spt > SINGLE_SCROLL_SPEED then
		if early(rightStick.up, rightStick.down) then
			lastRightScrollTime = gameTicks
			emit("right_scroll", 1, 0, -1)
		end
		if early(rightStick.down, rightStick.up) then
			lastRightScrollTime = gameTicks
			emit("right_scroll", 1, 0, 1)
		end
		if early(rightStick.right, rightStick.left) then
			lastRightScrollTime = gameTicks
			emit("right_scroll", 1, 1, 1)
		end
		if early(rightStick.left, rightStick.right) then
			lastRightScrollTime = gameTicks
			emit("right_scroll", 1, 1, -1)
		end
	end

	-- first press of a direction
	if (gameTicks - lastScrollTime) * spt > SINGLE_SCROLL_SPEED then
		if (leftStick.up == 1 and leftStick.down == 0) or (up == 1 and down == 0) or (kUp == 1 and kDown == 0) then
			lastScrollTime = gameTicks
			emit("scroll", 0, 0, -1)
		end
		if (leftStick.down == 1 and leftStick.up == 0) or (down == 1 and up == 0) or (kDown == 1 and kUp == 0) then
			lastScrollTime = gameTicks
			emit("scroll", 0, 0, 1)
		end
		if (leftStick.right == 1 and leftStick.left == 0) or (right == 1 and left == 0) or (kRight == 1 and kLeft == 0) then
			lastScrollTime = gameTicks
			emit("scroll", 0, 1, 1)
		end
		if (leftStick.left == 1 and leftStick.right == 0) or (left == 1 and right == 0) or (kLeft == 1 and kRight == 0) then
			lastScrollTime = gameTicks
			emit("scroll", 0, 1, -1)
		end
	end

	if (gameTicks - lastRightScrollTime) * spt > SINGLE_SCROLL_SPEED then
		if rightStick.up == 1 and rightStick.down == 0 then
			lastRightScrollTime = gameTicks
			emit("right_scroll", 0, 0, -1)
		end
		if rightStick.down == 1 and rightStick.up == 0 then
			lastRightScrollTime = gameTicks
			emit("right_scroll", 0, 0, 1)
		end
		if rightStick.right == 1 and rightStick.left == 0 then
			lastRightScrollTime = gameTicks
			emit("right_scroll", 0, 1, 1)
		end
		if rightStick.left == 1 and rightStick.right == 0 then
			lastRightScrollTime = gameTicks
			emit("right_scroll", 0, 1, -1)
		end
	end

	if lastScrollTime ~= 0
		and leftStick.up == 0 and leftStick.down == 0 and leftStick.left == 0 and leftStick.right == 0
		and up == 0 and down == 0 and left == 0 and right == 0
		and kUp == 0 and kDown == 0 and kLeft == 0 and kRight == 0 then
		lastScrollTime = 0
	end
	if lastRightScrollTime ~= 0
		and rightStick.up == 0 and rightStick.down == 0 and rightStick.left == 0 and rightStick.right == 0 then
		lastRightScrollTime = 0
	end

	local function action(name, id)
		if n(c[name]) == 1 then
			emit("action", { inputType = "controller", action = id })
		end
	end
	action("A", UiAction.A)
	action("B", UiAction.B)
	action("X", UiAction.X)
	action("Y", UiAction.Y)
	action("Start", UiAction.Start)
	action("Select", UiAction.Select)
	action("LeftBumper", UiAction.LeftBumper)
	action("RightBumper", UiAction.RightBumper)

	for i = 0, 15 do
		if keyTicks[i] == 1 then
			emit("action", { inputType = "keyboard", action = i })
		end
	end
end

dew.input = {
	on = function(event, callback)
		local list = callbacks[event]
		if not list then
			list = {}
			callbacks[event] = list
		end
		list[#list + 1] = callback
	end,
	removeListener = function(event, callback)
		local list = callbacks[event]
		if not list then return end
		for i = #list, 1, -1 do
			if list[i] == callback then
				table.remove(list, i)
				return
			end
		end
	end,
	playSound = function(index)
		dew.command("Game.PlayUiSound " .. tostring(index))
	end,
	reset = reset,
	Actions = UiAction,
	Sounds = UiSound,
}

dew.on("controllerinput", tick)
dew.on("hide", reset)

document:AddEventListener("keydown", function(event)
	local key = tonumber(event.parameters.key_identifier)
	if key then keyStates[key] = true end
end, true)
document:AddEventListener("keyup", function(event)
	local key = tonumber(event.parameters.key_identifier)
	if key then keyStates[key] = nil end
end, true)
