--[[
	dew.lua -- the Lua port of lib/dew.js.

	Loaded once by the host (Web/Rml/UiRoot.cpp) in the global environment.  It defines the
	shared globals (Promise, DewError, the enums, console, json) and returns a factory that
	builds the `dew` table each screen sees in its own environment:

		dew = factory(screenId, document)

	Calls that returned a JS Promise return a Promise here; chain with :next(ok, err),
	:catch(err) and :finally(fn) (`then` is a Lua keyword).
]]

local core = dew_core
local json = dew_json

------------------------------------------------------------------------------------------
-- Promise (enough of A+ for the screens: next/catch/finally, all, resolve, reject)
------------------------------------------------------------------------------------------

local PENDING, FULFILLED, REJECTED = 0, 1, 2

local Promise = {}
Promise.__index = Promise

local function isPromise(value)
	return type(value) == "table" and getmetatable(value) == Promise
end

local function settle(promise, state, value)
	if promise._state ~= PENDING then
		return
	end
	promise._state = state
	promise._value = value
	local callbacks = promise._callbacks
	promise._callbacks = nil
	for _, callback in ipairs(callbacks) do
		callback()
	end
	if state == REJECTED and #callbacks == 0 then
		-- Mirror the browser's "Uncaught (in promise)" so failures are not silent.
		core.setTimer(nil, function()
			if not promise._handled then
				core.log("warn", "unhandled promise rejection: " .. tostring(type(value) == "table" and value.message or value))
			end
		end, 0, false)
	end
end

local function resolvePromise(promise, value)
	if isPromise(value) then
		value:next(function(v) resolvePromise(promise, v) end, function(e) settle(promise, REJECTED, e) end)
	else
		settle(promise, FULFILLED, value)
	end
end

function Promise.new(executor)
	local promise = setmetatable({ _state = PENDING, _callbacks = {} }, Promise)
	local ok, err = pcall(executor,
		function(value) resolvePromise(promise, value) end,
		function(reason) settle(promise, REJECTED, reason) end)
	if not ok then
		settle(promise, REJECTED, err)
	end
	return promise
end

function Promise.resolve(value)
	if isPromise(value) then
		return value
	end
	return Promise.new(function(resolve) resolve(value) end)
end

function Promise.reject(reason)
	return Promise.new(function(_, reject) reject(reason) end)
end

function Promise:next(onFulfilled, onRejected)
	self._handled = true
	return Promise.new(function(resolve, reject)
		local function run()
			local handler = self._state == FULFILLED and onFulfilled or onRejected
			if type(handler) ~= "function" then
				if self._state == FULFILLED then resolve(self._value) else reject(self._value) end
				return
			end
			local ok, result = pcall(handler, self._value)
			if ok then resolve(result) else reject(result) end
		end
		if self._state == PENDING then
			table.insert(self._callbacks, run)
		else
			run()
		end
	end)
end

function Promise:catch(onRejected)
	return self:next(nil, onRejected)
end

function Promise:finally(onFinally)
	return self:next(function(value)
		onFinally()
		return value
	end, function(reason)
		onFinally()
		error(reason, 0)
	end)
end

function Promise.all(promises)
	return Promise.new(function(resolve, reject)
		local results, remaining = {}, #promises
		if remaining == 0 then
			resolve(json.array(results))
			return
		end
		for i, p in ipairs(promises) do
			Promise.resolve(p):next(function(value)
				results[i] = value
				remaining = remaining - 1
				if remaining == 0 then
					resolve(json.array(results))
				end
			end, reject)
		end
	end)
end

Promise.isPromise = isPromise
_G.Promise = Promise

------------------------------------------------------------------------------------------
-- Errors and enums (globals in dew.js)
------------------------------------------------------------------------------------------

DewErrorCode = {
	OK = 0,
	UNKNOWN_ERROR = 1,
	JS_EXCEPTION = 2,
	BAD_QUERY = 3,
	UNSUPPORTED_METHOD = 4,
	INVALID_ARGUMENT = 5,
	NETWORK_ERROR = 6,
	NOT_AVAILABLE = 7,
	COMMAND_FAILED = 8,
}

MPEventAudience = { CAUSE_PLAYER = 0, CAUSE_TEAM = 1, EFFECT_PLAYER = 2, EFFECT_TEAM = 3, ALL = 4 }

MPEventCategory = {
	GENERAL = 0, FLAVOR = 1, SLAYER = 2, CTF = 3, ODDBALL = 4, FORGE = 5, KOTH = 6, VIP = 7,
	JUGGERNAUT = 8, TERRITORIES = 9, ASSAULT = 10, INFECTION = 11, SURVIVAL = 12, WP = 13,
}

GameMode = {
	NONE = 0, CTF = 1, SLAYER = 2, ODDBALL = 3, KOTH = 4, FORGE = 5, VIP = 6, JUGGERNAUT = 7,
	TERRITORIES = 8, ASSAULT = 9, INFECTION = 10,
}

CommandType = { COMMAND = 0, INT = 1, INT64 = 2, FLOAT = 3, STRING = 4 }

local DewError = {}
DewError.__index = DewError
DewError.__tostring = function(e)
	return string.format("DewError(%s): %s%s", e:getCodeName(), e.message, e.method ~= "" and (" [" .. e.method .. "]") or "")
end

function DewError.new(message, code, method)
	return setmetatable({
		name = "DewError",
		message = message or "",
		code = type(code) == "number" and code or DewErrorCode.UNKNOWN_ERROR,
		method = method or "",
	}, DewError)
end

function DewError:getCodeName()
	for name, value in pairs(DewErrorCode) do
		if value == self.code then
			return name
		end
	end
	return tostring(self.code)
end

_G.DewError = DewError

------------------------------------------------------------------------------------------
-- console and json
------------------------------------------------------------------------------------------

local function joinArgs(...)
	local parts = {}
	for i = 1, select("#", ...) do
		local value = select(i, ...)
		if type(value) == "table" and getmetatable(value) == nil then
			value = json.encode(value)
		end
		parts[#parts + 1] = tostring(value)
	end
	return table.concat(parts, " ")
end

console = {
	log = function(...) core.log("info", joinArgs(...)) end,
	info = function(...) core.log("info", joinArgs(...)) end,
	debug = function(...) core.log("debug", joinArgs(...)) end,
	warn = function(...) core.log("warn", joinArgs(...)) end,
	error = function(...) core.log("error", joinArgs(...)) end,
}

_G.json = json

------------------------------------------------------------------------------------------
-- The per-screen `dew` table
------------------------------------------------------------------------------------------

local uiSounds = {
	error = 0, vertical_navigation = 1, horizontal_navigation = 2, a_button = 3, b_button = 4,
	x_button = 5, y_button = 6, start_button = 7, back_button = 8, left_bumper = 9,
	right_bumper = 10, left_trigger = 11, right_trigger = 12, timer_sound = 13,
	timer_sound_zero = 14, alt_timer_sound = 15, alt_timer_sound_zero = 16,
	matchmaking_advance_sound = 17, rank_up = 18, matchmaking_party_up_sound = 19,
}

local function defaultMapping(result)
	return result
end

local function jsonMapping(result)
	local value, err = json.decode(result)
	if value == nil and err then
		error(DewError.new("invalid JSON result: " .. tostring(err), DewErrorCode.BAD_QUERY), 0)
	end
	return value
end

local nextRequestId = 0
local function uniqueId()
	nextRequestId = nextRequestId + 1
	return string.format("%x%x", math.floor(core.getTime() * 1000) % 0xFFFFFF, nextRequestId)
end

return function(screenId, document)
	local dew = {
		screenId = screenId,
		document = document,
		json = json,
		Promise = Promise,
		ErrorCode = DewErrorCode,
		null = json.null,
	}

	-- Native methods ------------------------------------------------------------------

	-- Calls a native method; returns a Promise for the (mapped) result string.
	function dew.callMethod(method, args, resultMapping)
		resultMapping = resultMapping or defaultMapping
		return Promise.new(function(resolve, reject)
			if type(args) == "function" then
				args = args()
			end
			core.callMethod(screenId, method, args or {}, function(result)
				local ok, value = pcall(resultMapping, result)
				if ok then resolve(value) else reject(value) end
			end, function(message, code)
				local name = method
				if method == "command" and type(args) == "table" and args.command then
					name = method .. ": " .. tostring(args.command)
				end
				reject(DewError.new(message, code, name))
			end)
		end)
	end

	-- Synchronous variant for code that cannot wait a frame: returns ok, result|DewError.
	function dew.callMethodSync(method, args)
		local ok, result, code = core.callMethodSync(screenId, method, args or {})
		if ok then
			return true, result
		end
		return false, DewError.new(result, code, method)
	end

	function dew.command(command, options)
		options = options or {}
		return dew.callMethod("command", {
			command = tostring(command),
			internal = options.internal == true,
		})
	end

	function dew.commandSync(command, options)
		options = options or {}
		return dew.callMethodSync("command", { command = tostring(command), internal = options.internal == true })
	end

	function dew.setVariables(variables, options)
		options = options or {}
		return dew.callMethod("setVariables", { variables = variables, save = options.save == true })
	end

	function dew.setVariable(variable, value, options)
		options = options or {}
		return dew.callMethod("setVariables", { variables = { [variable] = value }, save = options.save == true })
	end

	function dew.playSound(name)
		local id = uiSounds[name]
		if not id then
			console.error("ui sound not found '" .. tostring(name) .. "'")
			return
		end
		dew.command("Game.PlayUiSound " .. id)
	end

	function dew.getVersion() return dew.callMethod("version") end
	function dew.getVersionCompat() return dew.command("Game.VersionCompat") end

	function dew.GameBlur(layer, enabled, speed)
		speed = speed or 6
		dew.command("game.FullscreenBlurTime " .. speed .. "f")
		return dew.command("Game.FullScreenBlurLayer " .. layer .. " " .. (enabled and "1" or "0"))
	end

	function dew.getEndpoint(name) return dew.command("Server.GetEndpoint " .. name) end

	function dew.ping(address, port)
		return dew.callMethod("ping", { address = tostring(address), port = port or 11774 })
	end

	function dew.getMapVariantInfo() return dew.callMethod("mapVariantInfo", {}, jsonMapping) end
	function dew.getGameVariantInfo() return dew.callMethod("gameVariantInfo", {}, jsonMapping) end
	function dew.getCommands() return dew.callMethod("commands", {}, jsonMapping) end
	function dew.getSessionInfo() return dew.callMethod("sessionInfo", {}, jsonMapping) end
	function dew.getStats(playerName) return dew.callMethod("stats", { playerName = playerName }, jsonMapping) end
	function dew.getScoreboard() return dew.callMethod("scoreboard", {}, jsonMapping) end

	function dew.sendChat(message, teamChat)
		return dew.callMethod("sendChat", { message = tostring(message), teamChat = teamChat == true })
	end

	function dew.getAssetUrl(path, options)
		local args = {}
		for k, v in pairs(options or {}) do
			args[k] = v
		end
		args.path = path
		return dew.callMethod("getAssetUrl", args)
	end

	-- Screens and events ---------------------------------------------------------------

	-- Handlers receive the message the iframes used to get: { event, screen, data }.
	function dew.on(event, callback)
		return core.on(screenId, event, callback)
	end

	function dew.off(token)
		core.off(screenId, token)
	end

	function dew.show(id, data)
		core.show(screenId, id, data or {})
	end

	function dew.hide(id)
		core.hide(screenId, id)
	end

	function dew.notify(eventName, data)
		core.notify(screenId, eventName, data == nil and {} or data)
	end

	function dew.captureInput(capture)
		core.captureInput(screenId, capture and true or false)
	end

	function dew.capturePointer(capture)
		core.capturePointer(screenId, capture and true or false)
	end

	-- dew.toast({ body = "<b>Hello World</b>" })
	function dew.toast(toast)
		core.toast(toast)
	end

	function dew.dialog(template, data)
		return Promise.new(function(resolve)
			local id = uniqueId()
			local token
			token = dew.on("dialogResult", function(message)
				local result = message.data
				if type(result) ~= "table" or result.requestId ~= id then
					return
				end
				dew.off(token)
				resolve(result.result)
			end)
			core.notify(screenId, "dialog", { id = id, template = template, data = data or {}, screen = screenId })
		end)
	end

	function dew.closeDialog(dialogName)
		core.notify(screenId, "dialogClose", dialogName)
	end

	function dew.notifyDialogResult(requestId, screen, result)
		if screen then
			core.notifyScreen(screen, "dialogResult", { requestId = requestId, screen = screen, result = result })
		end
	end

	-- Browser replacements ------------------------------------------------------------

	function dew.setTimeout(callback, milliseconds, ...)
		local args = table.pack(...)
		return core.setTimer(screenId, function() callback(table.unpack(args, 1, args.n)) end, milliseconds or 0, false)
	end

	function dew.setInterval(callback, milliseconds, ...)
		local args = table.pack(...)
		return core.setTimer(screenId, function() callback(table.unpack(args, 1, args.n)) end, milliseconds or 0, true)
	end

	dew.clearTimeout = core.clearTimer
	dew.clearInterval = core.clearTimer

	-- Runs once on the next frame, like requestAnimationFrame.
	function dew.requestAnimationFrame(callback)
		local id
		id = core.onFrame(screenId, function(now)
			core.clearTimer(id)
			callback(now * 1000)
		end)
		return id
	end
	dew.cancelAnimationFrame = core.clearTimer

	-- Runs every frame until cleared with dew.clearTimeout(id).
	function dew.onFrame(callback)
		return core.onFrame(screenId, callback)
	end

	-- fetch()/XHR: resolves with { ok, status, body, headers }, rejects on network errors.
	function dew.http(url, options)
		options = options or {}
		return Promise.new(function(resolve, reject)
			core.http(screenId, {
				url = url,
				method = options.method or "GET",
				body = options.body,
				headers = options.headers,
				timeout = options.timeout,
			}, function(ok, response)
				if not ok and (response.status or 0) == 0 then
					reject(DewError.new("request to " .. url .. " failed", DewErrorCode.NETWORK_ERROR, "http"))
					return
				end
				response.ok = response.status >= 200 and response.status < 300
				function response.json()
					return json.decode(response.body)
				end
				resolve(response)
			end)
		end)
	end

	function dew.fetchJson(url, options)
		return dew.http(url, options):next(function(response)
			if not response.ok then
				error(DewError.new("HTTP " .. response.status .. " from " .. url, DewErrorCode.NETWORK_ERROR, "http"), 0)
			end
			local value = json.decode(response.body)
			if value == nil then
				error(DewError.new("invalid JSON from " .. url, DewErrorCode.BAD_QUERY, "http"), 0)
			end
			return value
		end)
	end

	-- Downloads an image into the UI cache; resolves with a dew://cache/ url for `src`.
	function dew.fetchImage(url)
		return Promise.new(function(resolve, reject)
			core.fetchImage(screenId, url, function(ok, cacheUrl)
				if ok then resolve(cacheUrl) else reject(DewError.new("image download failed: " .. url, DewErrorCode.NETWORK_ERROR, "fetchImage")) end
			end)
		end)
	end

	dew.openUrl = core.openUrl
	dew.readFile = core.readFile
	dew.fileExists = core.fileExists
	dew.getMemoryStats = core.getMemoryStats
	dew.enumerateAudioInputs = core.enumerateAudioInputs

	dew.storage = {
		get = function(key) return core.storageGet(key) end,
		set = function(key, value) core.storageSet(key, value ~= nil and tostring(value) or nil) end,
		remove = function(key) core.storageSet(key, nil) end,
	}

	-- DOM helpers ---------------------------------------------------------------------

	function dew.getElementById(id)
		return document:GetElementById(id)
	end

	function dew.querySelector(selector)
		return document:QuerySelector(selector)
	end

	function dew.querySelectorAll(selector)
		return document:QuerySelectorAll(selector)
	end

	-- jQuery fadeIn/fadeOut replacement: toggles `fade-hidden` (opacity transition in
	-- lib/html.rcss) and sets `display` at the right moment.
	function dew.fade(element, show, milliseconds, done)
		if not element then
			return
		end
		milliseconds = milliseconds or 400
		local display = element:GetAttribute("data-display") or "block"
		if show then
			element.style.display = display
			element:SetClass("fade-hidden", true)
			dew.requestAnimationFrame(function()
				element.style["transition"] = string.format("opacity %.3fs linear-in-out", milliseconds / 1000)
				element:SetClass("fade-hidden", false)
				if done then dew.setTimeout(done, milliseconds) end
			end)
		else
			element.style["transition"] = string.format("opacity %.3fs linear-in-out", milliseconds / 1000)
			element:SetClass("fade-hidden", true)
			dew.setTimeout(function()
				element.style.display = "none"
				if done then done() end
			end, milliseconds)
		end
	end

	-- JavaScript truthiness (0, "", nil, false and json null are false; "0" is true).
	function dew.truthy(value)
		return value ~= nil and value ~= false and value ~= 0 and value ~= "" and value ~= json.null
	end

	function dew.escape(text)
		return (tostring(text or ""):gsub("[&<>\"']", {
			["&"] = "&amp;", ["<"] = "&lt;", [">"] = "&gt;", ['"'] = "&quot;", ["'"] = "&#39;",
		}))
	end

	return dew
end
