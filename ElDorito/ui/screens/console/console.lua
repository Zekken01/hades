-- Port of screens/console/console.js

local inputHistory = {}
local selectedHistoryIndex = 0
local commandList = {}
local suggestions = {}
local suggestionIndex = 0

local eAutoCompleteMode = { Prefix = 1, Substring = 2, Fuzzy = 3 }

local consoleSize = 2
local consoleDock = 1
local consoleInvert = 1
local consoleTransparency = 75
local consoleOpacity = 100
local consoleAutoCompleteMode = eAutoCompleteMode.Fuzzy
local memoryUsageInterval = nil
local suggestionMaxCount = 100
local maxConsoleHistory = 250
local maxConsoleInputHistory = 25
local versionText = ""

-- KI values
local KI_BACK, KI_TAB, KI_RETURN, KI_ESCAPE, KI_UP, KI_DOWN, KI_DELETE = 69, 70, 72, 81, 91, 93, 99
local KI_OEM_3, KI_F1, KI_OEM_8, KI_SNAPSHOT = 44, 107, 49, 97

local function isset(value)
	return value ~= nil and value ~= false and value ~= "" and value ~= 0 and value ~= json.null
end

local function el(id) return document:GetElementById(id) end
local function consoleEl() return el("console") end
local function outputBox() return el("output-box") end
local function commandBox() return el("command") end

local function inputValue()
	return commandBox():GetAttribute("value") or ""
end

local function focusInput()
	commandBox():Focus()
end

local function setInput(command)
	commandBox():SetAttribute("value", command)
	focusInput()
end

local function clearInput()
	setInput("")
end

local function split(text, separator)
	local parts = {}
	for part in (text .. separator):gmatch("(.-)" .. separator) do
		parts[#parts + 1] = part
	end
	return parts
end

local function startsWithNoCase(text, prefix)
	return text:lower():sub(1, #prefix) == prefix:lower()
end

-- output

local function isScrolledToBottom()
	local box = outputBox()
	return box.scroll_height - box.scroll_top - box.offset_height < 1
end

local function scrollToBottom()
	local box = outputBox()
	box.scroll_top = box.scroll_height
end

local function limitConsoleHistory()
	local lines = outputBox():QuerySelectorAll("pre")
	for i = 1, #lines - maxConsoleHistory do
		outputBox():RemoveChild(lines[i])
	end
end

local function appendRml(cssClass, rml)
	local atBottom = isScrolledToBottom()
	local pre = outputBox():AppendChild(document:CreateElement("pre"))
	if cssClass ~= "" then
		pre.class_name = cssClass
	end
	pre.inner_rml = rml
	if atBottom then
		scrollToBottom()
	end
	limitConsoleHistory()
	return pre
end

local function appendLine(cssClass, line)
	return appendRml(cssClass, dew.escape(tostring(line)))
end

-- html contains $1..$n placeholders filled with escaped contents
local function appendHTMLLine(cssClass, html, contents)
	for i, value in ipairs(contents) do
		html = html:gsub("%$" .. i, function() return dew.escape(tostring(value)) end, 1)
	end
	return appendRml(cssClass, html)
end

local function clearConsole()
	outputBox().inner_rml = ""
end

-- history (localStorage "console.history")

local function persistInputHistory()
	dew.storage.set("console.history", json.encode(json.array(inputHistory)))
end

local function fetchInputHistory()
	local historyJson = dew.storage.get("console.history")
	if historyJson then
		return json.decode(historyJson) or {}
	end
	return {}
end

local function pushInputHistory(command)
	if command ~= inputHistory[#inputHistory] then
		while #inputHistory >= maxConsoleInputHistory do
			table.remove(inputHistory, 1)
		end
		inputHistory[#inputHistory + 1] = command
		persistInputHistory()
	end
end

local function getInputHistory()
	appendLine("debug-line", "History: {" .. table.concat(inputHistory, ",") .. "}")
	appendLine("debug-line", "Count: " .. #inputHistory)
end

local function selectInputHistoryIndex(direction)
	-- 0-based index into inputHistory; == #inputHistory means "past the end"
	if selectedHistoryIndex + direction <= #inputHistory and selectedHistoryIndex + direction >= 0 then
		selectedHistoryIndex = selectedHistoryIndex + direction
		commandBox():SetAttribute("value", inputHistory[selectedHistoryIndex + 1] or "")
	end
end

local function resetInputHistoryIndex()
	selectedHistoryIndex = #inputHistory
end

-- the console's own commands

local function getConsoleHelp()
	return {
		{ module = "", name = "Variables", shortName = "variables", description = "Display all game variables with current values and a description", hidden = false, arguments = {} },
		{ module = "Console", name = "Console.AutoCompleteMode", shortName = "console_autocompletemode", description = "Toggle between the Console auto complete modes. Options: 0, 1, 2, Prefix, or Substring. Setting it to 0 will toggle between Prefix and Substring modes", value = consoleAutoCompleteMode, defaultValue = eAutoCompleteMode.Substring, hidden = false, arguments = { "autocompletemode(int) Options: 0, 1, 2, prefix, substring. 1 = prefix, 2 = substring, 0 toggles between 1 and 2." } },
		{ module = "Console", name = "Clear", shortName = "console_clear", description = "Clear the Console's input and output areas", hidden = false, arguments = {} },
		{ module = "Console", name = "Console.Dock", shortName = "console_dock", description = "Toggle Console docking, allows you to drag and resize the console if undocked. Options: 0, 1 or 2. Setting it to 0 will do the same as the Dock button", value = consoleDock, defaultValue = 1, hidden = false, arguments = { "dockmode(int) Options: 0, 1 or 2. 1 = docked, 2 = undocked, 0 toggles between 1 and 2." } },
		{ module = "Console", name = "Console.History", shortName = "console_history", description = "Display the commands in the Console's command history, you can navigate the command history using the arrow up/down keys", hidden = false, arguments = {} },
		{ module = "Console", name = "Console.Invert", shortName = "console_invert", description = "Inverts the Console input box and drag handle", value = consoleInvert, defaultValue = 1, hidden = false, arguments = { "inverted(int) Options: 0, 1 or 2. 1 = not inverted, 2 = inverted, 0 toggles between 1 and 2." } },
		{ module = "Console", name = "Console.Opacity", shortName = "console_opacity", description = "Set the Console's overall opacity. Range: 0 - 100. Do not set below 40", value = consoleOpacity, defaultValue = 100, hidden = false, arguments = { "opacityPercentage(int) Range: 0 - 100" } },
		{ module = "Console", name = "Console.Reset", shortName = "console_reset", description = "Reset the Console, useful if something goes wrong and you can no longer properly use the console", hidden = false, arguments = {} },
		{ module = "Console", name = "Console.Size", shortName = "console_size", description = "Set the Console's output box size manually. Options: 1, 2, 3 or 4. Setting it to 0 will do the same as Console.ToggleSize", value = consoleSize, defaultValue = 2, hidden = false, arguments = { "sizeIndex(int) Options: 0, 1, 2, 3 or 4. 1 = 25%, 2 = 50%, 3 = 75%, 4 = 100%, 0 toggles 1, 2, 3 and 4." } },
		{ module = "Console", name = "Console.Transparency", shortName = "console_transparency", description = "Set the Console's background transparency. Range: 0 - 100", value = consoleTransparency, defaultValue = 75, hidden = false, arguments = { "transparencyPercentage(int) Range: 0 - 100" } },
		{ module = "Console", name = "Console.MaxHistory", shortName = "console_maxhistory", description = "Set the Console's maximum history", value = maxConsoleHistory, defaultValue = 250, hidden = false, arguments = { "maxHistory(int) Range: 0 - 1000" } },
	}
end

local function sortCommands(commands)
	table.sort(commands, function(a, b)
		local am, bm = tostring(a.module or ""), tostring(b.module or "")
		if am ~= bm then return am < bm end
		return tostring(a.name or "") < tostring(b.name or "")
	end)
	return commands
end

local function showHelp(command)
	if not isset(command) then
		sortCommands(commandList)
		appendLine("", "Left click on a command to set it in the input box, right click for help related to the command and ctrl + click to directly execute command.")
		for _, value in ipairs(commandList) do
			if not value.hidden and not value.hideValue and not value.internal then
				appendHTMLLine("", '<span class="command"><b>$1</b></span>  -  <span class="description">$2</span>', { value.name, value.description })
			end
		end
	else
		local commandItem
		for _, item in ipairs(commandList) do
			if tostring(item.name):lower() == command:lower() then
				commandItem = item
				break
			end
		end
		if commandItem and not commandItem.hidden and not commandItem.hideValue and not commandItem.internal then
			local name = commandItem.name
			local usage = ""
			local parameters = {}
			for _, value in ipairs(commandItem.arguments or {}) do
				local argument = split(value, " ")
				local description = value:gsub(argument[1]:gsub("%p", "%%%0") .. " ", "", 1)
				usage = usage .. "<" .. argument[1] .. "> "
				parameters[#parameters + 1] = { name = argument[1], description = description }
			end
			appendHTMLLine("", '<span class="command"><b>$1</b></span>  -  <span class="description">$2</span>', { name, commandItem.description })
			if isset(commandItem.defaultValue) then
				appendLine("", "Default: " .. tostring(commandItem.defaultValue))
				if not isset(usage) then
					usage = tostring(commandItem.defaultValue)
				end
			end
			if isset(commandItem.value) and commandItem.value ~= commandItem.defaultValue then
				appendLine("", "Current value: " .. tostring(commandItem.value))
			end
			appendLine("", "Usage: " .. name .. " " .. usage)
			for _, value in ipairs(parameters) do
				appendHTMLLine("", "       <i>$1</i>: <span class=\"description\">$2</span>", { value.name, value.description })
			end
		else
			appendLine("error-line", "Command/Variable '" .. command .. "' not found")
		end
	end
end

local function showVariables()
	sortCommands(commandList)
	for _, value in ipairs(commandList) do
		if (isset(value.value) or isset(value.defaultValue)) and not value.hidden and not value.hideValue and not value.internal then
			local varValue = value.value
			if value.name == "Player.PrivKey" then
				varValue = "Enter the variable manually to check this value"
			end
			appendHTMLLine("", '<span class="command"><b>$1</b></span> = $2    <span class="description">$3</span>', { value.name, varValue == nil and "undefined" or varValue, value.description })
		end
	end
end

local function removeSuggestions()
	for _, element in ipairs(outputBox():QuerySelectorAll(".suggestion")) do
		outputBox():RemoveChild(element)
	end
end

local function getSuggestedCommands(partial)
	suggestions = {}
	suggestionIndex = -1
	removeSuggestions()
	if not isset(partial) then
		return
	end
	local commands = {}
	for _, item in ipairs(commandList) do commands[#commands + 1] = item end
	for _, item in ipairs(getConsoleHelp()) do commands[#commands + 1] = item end

	local needle = partial:lower()
	for _, item in ipairs(commands) do
		if not item.hidden and not item.internal then
			local pos = tostring(item.name):lower():find(needle, 1, true)
			pos = pos and pos - 1 or -1
			if (consoleAutoCompleteMode == eAutoCompleteMode.Prefix and pos ~= 0) or pos >= 0 then
				suggestions[#suggestions + 1] = item.name
			end
		end
	end
	while #suggestions > suggestionMaxCount do
		table.remove(suggestions)
	end
	if #suggestions > 0 then
		local parts = {}
		for _, suggestion in ipairs(suggestions) do
			parts[#parts + 1] = dew.escape(suggestion)
		end
		appendRml("debug-line suggestion", '<span class="command"><b>' .. table.concat(parts, '</b></span>       <span class="command"><b>') .. "</b></span>")
	end
end

local function advanceSuggestionIndex(amount)
	if #suggestions > 0 then
		if suggestionIndex + amount < 0 then
			suggestionIndex = 0
		else
			suggestionIndex = (suggestionIndex + amount) % #suggestions
		end
		local suggestion = suggestions[suggestionIndex + 1]
		if isset(suggestion) then
			setInput(suggestion)
		end
	end
end

-- size / dock / invert / transparency / opacity

local function sizeConsole(size, silent)
	local n = tonumber(size)
	if n == nil then
		appendLine("", consoleSize)
		return
	elseif n ~= 0 and n ~= 1 and n ~= 2 and n ~= 3 and n ~= 4 then
		appendLine("error-line", "Parameter is invalid! Options: 0, 1, 2, 3 or 4")
	end
	if n == 0 then
		n = (consoleSize % 4) + 1
	end
	if not silent then
		appendLine("", consoleSize .. " -> " .. n)
	end
	consoleSize = n
	consoleEl().style.height = (consoleSize * 25) .. "%"
end

local function dockConsole(toggle, silent)
	local n = tonumber(toggle)
	if n == nil then
		if not isset(toggle) then
			appendLine("", consoleDock)
		else
			appendLine("error-line", "Parameter is not an integer! Options: 0, 1 or 2")
		end
		return
	elseif n ~= 0 and n ~= 1 and n ~= 2 then
		appendLine("error-line", "Parameter is invalid! Options: 0, 1 or 2")
		return
	end
	local c = consoleEl()
	if n == 1 then
		c:SetClass("undocked", false)
		sizeConsole(consoleSize, silent)
		c.style.left = "0px"
		c.style.top = "0px"
		c.style.width = "100%"
		if not silent then appendLine("", consoleDock .. " -> 1") end
		consoleDock = 1
	elseif n == 2 then
		c:SetClass("undocked", true)
		c.style.left = "15px"
		c.style.top = "15px"
		c.style.width = (document.offset_width - 30) .. "px"
		if not silent then appendLine("", consoleDock .. " -> 2") end
		consoleDock = 2
	else
		dockConsole(consoleDock == 1 and 2 or 1, silent)
	end
end

local function invertConsole(toggle, silent)
	local n = tonumber(toggle)
	if n == nil then
		if not isset(toggle) then
			appendLine("", consoleInvert)
		else
			appendLine("error-line", "Parameter is not an integer! Options: 0, 1 or 2")
		end
		return
	elseif n ~= 0 and n ~= 1 and n ~= 2 then
		appendLine("error-line", "Parameter is invalid! Options: 0, 1 or 2")
		return
	end
	if n == 1 then
		consoleEl():SetClass("inverted", false)
		if not silent then appendLine("", consoleInvert .. " -> 1") end
		consoleInvert = 1
	elseif n == 2 then
		consoleEl():SetClass("inverted", true)
		if not silent then appendLine("", consoleInvert .. " -> 2") end
		consoleInvert = 2
	else
		-- as console.js: toggling invert with 0 toggles the dock mode
		dockConsole(consoleInvert == 1 and 2 or 1, silent)
	end
end

local function transparencyConsole(percentage, silent)
	local n = tonumber(percentage)
	if n == nil then
		if not isset(percentage) then
			appendLine("", consoleTransparency)
		else
			appendLine("error-line", "Parameter is not an integer! Range 0 - 100")
		end
		return
	elseif n < 0 or n > 100 then
		appendLine("error-line", "Parameter is out of range! Range 0 - 100")
		return
	end
	if not silent then appendLine("", consoleTransparency .. " -> " .. n) end
	consoleTransparency = n
	consoleEl().style["background-color"] = string.format("rgba(20, 31, 55, %d)", math.floor(n / 100 * 255 + 0.5))
end

local function opacityConsole(percentage, silent)
	local n = tonumber(percentage)
	if n == nil then
		if not isset(percentage) then
			appendLine("", consoleOpacity)
		else
			appendLine("error-line", "Parameter is not an integer! Range 0 - 100")
		end
		return
	elseif n < 0 or n > 100 then
		appendLine("error-line", "Parameter is out of range! Range 0 - 100")
		return
	end
	if not silent then appendLine("", consoleOpacity .. " -> " .. n) end
	consoleOpacity = n
	document.style.opacity = tostring(n / 100)
end

local function autoCompleteModeToString(mode)
	mode = tonumber(mode) or consoleAutoCompleteMode
	if mode == eAutoCompleteMode.Prefix then return "Prefix" end
	if mode == eAutoCompleteMode.Substring then return "Substring" end
	return "Error"
end

local function autoCompleteModeConsole(toggle, silent)
	local text = tostring(toggle or ""):lower()
	if text == "prefix" then toggle = 1 elseif text == "substring" then toggle = 2 end
	local n = tonumber(toggle)
	if n == nil then
		if not isset(toggle) then
			appendLine("", "[" .. consoleAutoCompleteMode .. "] " .. autoCompleteModeToString())
		else
			appendLine("error-line", "Parameter is not an integer! Options: 0, 1 or 2")
		end
		return
	elseif n ~= 0 and n ~= eAutoCompleteMode.Prefix and n ~= eAutoCompleteMode.Substring then
		appendLine("error-line", "Parameter is invalid! Options: 0, 1 or 2")
		return
	end
	if n == eAutoCompleteMode.Prefix or n == eAutoCompleteMode.Substring then
		if not silent then
			appendLine("", consoleAutoCompleteMode .. " -> [" .. n .. "] " .. autoCompleteModeToString(n))
		end
		consoleAutoCompleteMode = n
	else
		autoCompleteModeConsole(consoleAutoCompleteMode == eAutoCompleteMode.Prefix and eAutoCompleteMode.Substring or eAutoCompleteMode.Prefix, silent)
	end
end

local function resetConsole()
	sizeConsole(2, true)
	dockConsole(1, true)
	invertConsole(1, true)
	transparencyConsole(85, true)
	opacityConsole(100, true)
	autoCompleteModeConsole(eAutoCompleteMode.Substring, true)
	clearConsole()
	clearInput()
end

-- running commands

local function runCommand(command)
	if not isset((command:gsub("^%s+", ""):gsub("%s+$", ""))) then
		return
	end
	local lower = command:lower()
	local args = split(command, " ")
	local function prefixed(name)
		return lower:sub(1, #name) == name
	end
	if lower == "clear" then
		clearConsole()
	elseif lower == "console.reset" then
		resetConsole()
	elseif lower == "console.history" then
		appendLine("command-line", "> " .. command)
		getInputHistory()
	elseif lower == "variables" then
		appendLine("command-line", "> " .. command)
		showVariables()
	elseif prefixed("console.size") then
		appendLine("command-line", "> " .. command)
		sizeConsole(args[2])
	elseif prefixed("console.dock") then
		appendLine("command-line", "> " .. command)
		dockConsole(args[2])
	elseif prefixed("console.invert") then
		appendLine("command-line", "> " .. command)
		invertConsole(args[2])
	elseif prefixed("console.transparency") then
		appendLine("command-line", "> " .. command)
		transparencyConsole(args[2])
	elseif prefixed("console.opacity") then
		appendLine("command-line", "> " .. command)
		opacityConsole(args[2])
	elseif prefixed("console.autocompletemode") then
		appendLine("command-line", "> " .. command)
		autoCompleteModeConsole(args[2])
	elseif prefixed("help") then
		appendLine("command-line", "> " .. command)
		showHelp(args[2])
	elseif prefixed("console.maxhistory") then
		appendLine("command-line", "> " .. command)
		if #args == 1 then
			appendLine("command-line", maxConsoleHistory)
		else
			local value = tonumber(args[2])
			if value and value >= 0 then
				maxConsoleHistory = math.floor(value)
				limitConsoleHistory()
			else
				appendLine("error-line", "Argument was not of type integer")
			end
		end
	else
		dew.command(command):next(function(output)
			appendLine("command-line", "> " .. command)
			if output ~= "" then
				appendLine("", output)
			end
			scrollToBottom()
		end):catch(function(err)
			appendLine("command-line", "> " .. command)
			appendLine("error-line", type(err) == "table" and err.message or tostring(err))
		end)
	end
	scrollToBottom()
	clearInput()
	pushInputHistory(command)
	resetInputHistoryIndex()
	removeSuggestions()
end

-- memory usage (performance.memory.usedJSHeapSize -> the Lua heap)

local function formatBytes(bytes, decimals)
	if bytes == 0 then return "0 Bytes" end
	local k = 1000
	local dm = decimals or 2
	local sizes = { "Bytes", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" }
	local i = math.floor(math.log(bytes) / math.log(k))
	local value = bytes / k ^ i
	local text = string.format("%." .. dm .. "f", value):gsub("%.?0+$", "")
	return text .. " " .. sizes[i + 1]
end

local function showMemoryUsage()
	local stats = dew.getMemoryStats()
	jq("#memory-usage"):text(formatBytes(stats.luaBytes or 0))
end

-- dragging and resizing when undocked

local drag = nil

local function initDraggable()
	local c = consoleEl()
	c:AddEventListener("mousedown", function(event)
		if consoleDock ~= 2 or tonumber(event.parameters.button) ~= 0 then
			return
		end
		local x, y = tonumber(event.parameters.mouse_x), tonumber(event.parameters.mouse_y)
		local target = event.target_element
		local function within(id)
			local e = target
			while e do
				if e.id == id then return true end
				e = e.parent_node
			end
			return false
		end
		if within("resize-handle") then
			drag = { mode = "resize", left = c.absolute_left or c.offset_left, top = c.absolute_top or c.offset_top }
		elseif within("titlebar") then
			drag = { mode = "move", dx = x - c.offset_left, dy = y - c.offset_top }
		end
	end)
	document:AddEventListener("mousemove", function(event)
		if not drag then return end
		local x, y = tonumber(event.parameters.mouse_x), tonumber(event.parameters.mouse_y)
		if drag.mode == "resize" then
			c.style.width = (x - c.offset_left) .. "px"
			c.style.height = (y - c.offset_top) .. "px"
		else
			c.style.left = (x - drag.dx) .. "px"
			c.style.top = (y - drag.dy) .. "px"
		end
	end)
	document:AddEventListener("mouseup", function()
		drag = nil
	end)
end

-- wiring

local function commandText(element)
	-- the text of a .command span (it wraps a <b>)
	return (element.inner_rml:gsub("<[^>]+>", ""):gsub("&lt;", "<"):gsub("&gt;", ">"):gsub("&amp;", "&"))
end

document:AddEventListener("load", function()
	dew.getVersion():next(function(version)
		versionText = version
		jq("#version"):text(version)
	end)

	dew.getCommands():next(function(commands)
		commandList = commands
		for _, item in ipairs(getConsoleHelp()) do
			commandList[#commandList + 1] = item
		end
	end):catch(function()
		appendLine("error-line", "Could not retrieve list of commands!")
	end)

	focusInput()
	el("input-box"):AddEventListener("click", focusInput)
	initDraggable()
	dockConsole(1, true) -- HACK: Fix default positioning of the console

	document:AddEventListener("keyup", function(event)
		local key = tonumber(event.parameters.key_identifier)
		if key == KI_ESCAPE then
			-- hide when escape is released (keeps from triggering the pause menu)
			dew.hide()
		end
		if key == KI_SNAPSHOT then
			dew.command("Game.TakeScreenshot")
		end
	end)
	document:AddEventListener("keydown", function(event)
		local key = tonumber(event.parameters.key_identifier)
		if key == KI_OEM_3 or key == KI_F1 or key == KI_OEM_8 then
			-- hide when tilde is pressed and the input is empty
			if #inputValue() == 0 then
				dew.hide()
			end
		end
	end)

	local box = commandBox()
	box:AddEventListener("keyup", function(event)
		local key = tonumber(event.parameters.key_identifier)
		if key == KI_RETURN then
			runCommand(inputValue())
			clearInput()
		elseif key == KI_UP then
			selectInputHistoryIndex(-1)
		elseif key == KI_DOWN then
			selectInputHistoryIndex(1)
		elseif (key >= 2 and key <= 37) or key == KI_BACK or key == KI_DELETE then
			-- 0-9 and A-Z: refresh the suggestions while typing
			getSuggestedCommands(inputValue())
		end
	end)
	box:AddEventListener("keydown", function(event)
		local key = tonumber(event.parameters.key_identifier)
		if key == KI_TAB then
			event:StopPropagation() -- keep focus in the input (no tab navigation)
			advanceSuggestionIndex(tonumber(event.parameters.shift_key) == 1 and -1 or 1)
		end
	end)

	-- clicks on .command spans anywhere in the output (delegated, as $("html").on)
	outputBox():AddEventListener("click", function(event)
		local e = event.target_element
		while e and e ~= outputBox() do
			if e:IsClassSet("command") then
				if tonumber(event.parameters.ctrl_key) == 1 then
					runCommand(commandText(e))
				else
					setInput(commandText(e))
				end
				focusInput()
				return
			end
			e = e.parent_node
		end
	end)
	outputBox():AddEventListener("mousedown", function(event)
		if tonumber(event.parameters.button) ~= 1 then return end -- contextmenu
		local e = event.target_element
		while e and e ~= outputBox() do
			if e:IsClassSet("command") then
				setInput("help " .. commandText(e))
				focusInput()
				return
			end
			e = e.parent_node
		end
	end)

	el("button-help"):AddEventListener("click", function() runCommand("Help"); focusInput() end)
	el("button-clear"):AddEventListener("click", function() clearConsole(); clearInput(); focusInput() end)
	el("button-reset"):AddEventListener("click", function() resetConsole() end)
	el("button-size"):AddEventListener("click", function() sizeConsole(0, true); focusInput() end)
	el("button-dock"):AddEventListener("click", function() dockConsole(0, true); focusInput() end)
	el("button-hide"):AddEventListener("click", function() dew.hide() end)

	sizeConsole(consoleSize, true)
	inputHistory = fetchInputHistory()
	resetInputHistoryIndex()
	showMemoryUsage()
end)

dew.on("show", function()
	focusInput()
	if not memoryUsageInterval then
		memoryUsageInterval = dew.setInterval(showMemoryUsage, 1000)
	end
end)

dew.on("hide", function()
	clearInput()
	scrollToBottom()
	if memoryUsageInterval then
		dew.clearInterval(memoryUsageInterval)
		memoryUsageInterval = nil
	end
end)

dew.on("console", function(e)
	appendLine("", (e.data or {}).line or "")
end)
