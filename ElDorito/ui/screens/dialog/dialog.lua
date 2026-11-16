--[[
	dialog.lua -- port of screens/dialog/dialog.js (Vue app with `dew-dialog` and
	`dew-input-dialog` components) to plain Lua + RML.

	Dialogs arrive through the "dialog" event (from dew.dialog in any screen, or natively
	from Web::Ui::WebDialog with native = true) and are queued; one is on screen at a time.
]]

local DIALOG_TEMPLATES = {
	-- Unused debug dialog
	test = {
		title = "Lorem ipsum",
		body = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation.",
		options = {
			{ label = "Option A", value = "option_a", default = true },
			{ label = "Option B", value = "option_b" },
			{ label = "Option C", value = "option_c" },
			{ label = "Option D", value = "option_d" },
		},
		buttonkey = {
			{ label = "Ok", action = "select", type = "a_button" },
			{ label = "Cancel", action = "close", value = "cancel", type = "b_button" },
		},
	},
	-- ScreenLayer.cpp: ShowAlert
	alert_template = {
		title = "placeholder",
		body = "placeholder",
		icon = "warning",
		buttonkey = {
			-- Do not change value unless changed in WebDialog HandleDialogShowRequest
			{ label = "Ok", action = "close", value = "ok", type = "a_button" },
		},
	},
	-- ServerConnectStateHandler_Connect.cpp: OnEnter()
	attempting_join = {
		title = "JOINING GAME",
		body = "Attempting to join the selected game...",
		disableLinks = true,
		autoDismissable = true,
		dialogHeight = 26.388,
		buttonkey = {
			{ label = "Close", action = "close", value = "close", type = "b_button" },
		},
	},
	-- Ui.cpp: _show_service_record_hook; chat screen
	confirm_link = {
		title = "Warning",
		body = "Are you sure you want to open this?",
		disableLinks = true,
		dialogHeight = 33.333,
		icon = "warning",
		buttonkey = {
			{ label = "Yes", action = "close", value = "yes", type = "a_button" },
			{ label = "No", action = "close", value = "no", type = "b_button" },
		},
	},
	-- UI.cpp: _handle_list_item_chosen_hook, OnUiInputUpdated
	exit = {
		title = "EXIT?",
		body = "Are you sure you want to exit the game?",
		dialogHeight = 33.333,
		options = {
			{ label = "Exit", value = "exit" },
			{ label = "Cancel", value = "cancel", default = true },
		},
		buttonkey = {
			{ label = "Select", action = "select", type = "a_button", mouse = false },
			{ label = "Cancel", action = "close", value = "cancel", type = "b_button" },
		},
	},
	-- VirtualKeyboard.cpp: WebVirtualKeyboardHandler
	edit_variant_name = {
		type = "input",
		title = "Edit",
		body = "placeholder",
		maxLength = 15,
		numRows = 1,
		dialogHeight = 31.944,
		buttonkey = {
			{ label = "Save", action = "submit", type = "a_button" },
			{ label = "Cancel", action = "close", value = "cancel", type = "b_button" },
		},
	},
	-- VirtualKeyboard.cpp: WebVirtualKeyboardHandler
	edit_variant_description = {
		type = "input",
		title = "Edit",
		body = "placeholder",
		maxLength = 127,
		numRows = 4,
		dialogHeight = 37.5,
		buttonkey = {
			{ label = "Save", action = "submit", type = "a_button" },
			{ label = "Cancel", action = "close", value = "cancel", type = "b_button" },
		},
	},
	-- Settings screen
	unapplied_settings = {
		title = "ALERT",
		body = "You have unapplied settings. Close anyway?",
		dialogHeight = 33.333,
		icon = "warning",
		options = {
			{ label = "Yes", value = "ok" },
			{ label = "No", value = "no", default = true },
		},
		buttonkey = {
			{ label = "Select", action = "select", type = "a_button", mouse = false },
			{ label = "Cancel", action = "close", value = "cancel", type = "b_button" },
		},
	},
	weapon_offsets_not_supported = {
		title = "ALERT",
		body = "Weapon offsets are not supported for this weapon.",
		dialogHeight = 26.388,
		icon = "warning",
		buttonkey = { { label = "Ok", action = "close", value = "ok", type = "a_button" } },
	},
	weapon_offsets_in_game_warning = {
		title = "ALERT",
		body = "Weapon offsets can only be edited in-game.",
		dialogHeight = 26.388,
		icon = "warning",
		buttonkey = { { label = "Ok", action = "close", value = "ok", type = "a_button" } },
	},
	strain_system = {
		title = "ALERT",
		body = "Increasing this setting may strain lower end systems and could cause graphical issues on more intensive modded maps.",
		dialogHeight = 26.388,
		icon = "warning",
		buttonkey = { { label = "Ok", action = "close", value = "ok", type = "a_button" } },
	},
	requires_restart = {
		title = "ALERT",
		body = "This change requires a restart to take effect.",
		dialogHeight = 26.388,
		icon = "warning",
		buttonkey = { { label = "Ok", action = "close", value = "ok", type = "a_button" } },
	},
	confirm_reset = {
		title = "WARNING",
		body = "Are you sure you want to reset all settings? Bindings will not be affected.",
		icon = "warning",
		dialogHeight = 33.333,
		options = {
			{ label = "Yes", value = "yes" },
			{ label = "no", value = "no", default = true },
		},
		buttonkey = {
			{ label = "Select", action = "select", type = "a_button", mouse = false },
			{ label = "Cancel", action = "close", value = "no", type = "b_button" },
		},
	},
	confirm_reset_bindings = {
		title = "WARNING",
		body = "Are you sure you want to reset all bindings? Other settings will not be affected.",
		icon = "warning",
		dialogHeight = 33.333,
		options = {
			{ label = "Yes", value = "yes" },
			{ label = "no", value = "no", default = true },
		},
		buttonkey = {
			{ label = "Select", action = "select", type = "a_button", mouse = false },
			{ label = "Cancel", action = "close", value = "no", type = "b_button" },
		},
	},
	coop_sprint = {
		title = "ALERT",
		body = "Sprint will not be enabled during co-op.",
		dialogHeight = 26.388,
		icon = "warning",
		buttonkey = { { label = "Ok", action = "close", value = "ok", type = "a_button" } },
	},
	-- Customization screen
	confirm_reset_customization = {
		title = "WARNING",
		body = "Are you sure you want to reset the customization on this page?",
		icon = "warning",
		dialogHeight = 33.333,
		options = {
			{ label = "Yes", value = "yes" },
			{ label = "no", value = "no", default = true },
		},
		buttonkey = {
			{ label = "Select", action = "select", type = "a_button", mouse = false },
			{ label = "Cancel", action = "close", value = "no", type = "b_button" },
		},
	},
	-- Weapon offset editor screen
	new_weapon_offset = {
		type = "input",
		title = "Weapon Offset Config",
		body = "Enter the new config name below.",
		pattern = "^[%w%-_]+$",
		regexFailMessage = "Name must only contain letters, numbers, underscores and dashes",
		maxLength = 32,
		numRows = 1,
		dialogHeight = 31.944,
		buttonkey = {
			{ label = "Confirm", action = "submit", type = "a_button" },
			{ label = "Cancel", action = "close", value = "cancel", type = "b_button" },
		},
	},
	weapon_offset_exists = {
		title = "Warning",
		body = "That offset already exists.",
		dialogHeight = 26.388,
		icon = "warning",
		buttonkey = { { label = "Ok", action = "close", value = "ok", type = "a_button" } },
	},
	weapon_offset_delete = {
		title = "Warning",
		body = "Are you sure you want to delete this config?",
		icon = "warning",
		dialogHeight = 33.333,
		options = {
			{ label = "Yes", value = "yes" },
			{ label = "no", value = "no", default = true },
		},
		buttonkey = {
			{ label = "Select", action = "select", type = "a_button", mouse = false },
			{ label = "Cancel", action = "close", value = "cancel", type = "b_button" },
		},
	},
	weapon_offset_delete_error = {
		title = "Error",
		body = "There was an error while deleting the weapon offset config",
		dialogHeight = 26.388,
		icon = "warning",
		buttonkey = { { label = "Ok", action = "close", value = "ok", type = "a_button" } },
	},
	confirm_save_weapon_offset = {
		title = "WARNING",
		body = "Are you sure you want to save the weapon offsets?",
		icon = "warning",
		dialogHeight = 33.333,
		options = {
			{ label = "Yes", value = "yes" },
			{ label = "no", value = "no", default = true },
		},
		buttonkey = {
			{ label = "Select", action = "select", type = "a_button", mouse = false },
			{ label = "Cancel", action = "close", value = "no", type = "b_button" },
		},
	},
	confirm_reset_weapon_offset = {
		title = "WARNING",
		body = "Are you sure you want to reset this weapon offset?",
		icon = "warning",
		dialogHeight = 33.333,
		options = {
			{ label = "Yes", value = "yes" },
			{ label = "no", value = "no", default = true },
		},
		buttonkey = {
			{ label = "Select", action = "select", type = "a_button", mouse = false },
			{ label = "Cancel", action = "close", value = "no", type = "b_button" },
		},
	},
	-- Mod browser screen
	mod_options = {
		title = "OPTIONS",
		body = "Select an option:",
		dialogHeight = 33.333,
		options = {
			{ label = "Set as Lobby Default", value = "default", default = true },
			{ label = "Delete Mod", value = "delete" },
		},
		buttonkey = {
			{ label = "Select", action = "select", type = "a_button" },
			{ label = "Close", action = "close", value = "cancel", type = "b_button" },
		},
	},
	confirm_mod_delete = {
		title = "WARNING",
		body = "Are you sure you want to delete this mod?",
		icon = "warning",
		dialogHeight = 33.333,
		options = {
			{ label = "Yes", value = "yes" },
			{ label = "no", value = "no", default = true },
		},
		buttonkey = {
			{ label = "Select", action = "select", type = "a_button", mouse = false },
			{ label = "Cancel", action = "close", value = "no", type = "b_button" },
		},
	},
	-- Server browser screen
	server_password = {
		type = "input",
		title = "Private Server",
		body = "Please enter password.",
		inputType = "password",
		dialogHeight = 31.944,
		buttonkey = {
			{ label = "Confirm", action = "submit", type = "a_button" },
			{ label = "Cancel", action = "close", value = "", type = "b_button" },
		},
	},
	-- ServerConnect.cpp
	server_connect_error_retry = {
		title = "Failed to connect",
		body = "placeholder",
		icon = "warning",
		dialogHeight = 33.333,
		buttonkey = {
			{ label = "Retry", action = "close", value = "retry", type = "a_button" },
			{ label = "Cancel", action = "close", value = "cancel", type = "b_button" },
		},
	},
	server_connect_error = {
		title = "Failed to connect",
		body = "placeholder",
		icon = "warning",
		dialogHeight = 33.333,
		buttonkey = {
			{ label = "Close", action = "close", value = "cancel", type = "b_button" },
		},
	},
	-- ModBrowser.cpp
	mod_download_error = {
		title = "Failed to download",
		body = "placeholder",
		icon = "warning",
		dialogHeight = 33.333,
		buttonkey = {
			{ label = "Close", action = "close", value = "cancel", type = "b_button" },
		},
	},
	-- ModBrowser.cpp
	mod_already_installed = {
		title = "Mod already downloaded",
		body = "This mod has already been downloaded.",
		icon = "checkbox",
		dialogHeight = 33.333,
		buttonkey = {
			{ label = "Close", action = "close", value = "cancel", type = "b_button" },
		},
	},
	-- Customization screen (the JS object literal listed buttonkey twice; the second wins)
	edit_player_name = {
		type = "input",
		title = "Player name",
		body = "Enter a new player name.",
		dialogHeight = 31.944,
		regexFailMessage = "Name must only contain numbers, letters, spaces and underscores",
		maxLength = 15,
		pattern = "^[%w _%-]+$",
		validate = function(value) return not value:match("^%s") and not value:match("^ +$") end,
		buttonkey = {
			{ label = "Ok", action = "submit", type = "a_button" },
			{ label = "Cancel", action = "close", value = "-1", type = "b_button" },
		},
	},
	edit_service_tag = {
		type = "input",
		title = "Service Tag",
		body = "Enter a new service tag.",
		dialogHeight = 31.944,
		regexFailMessage = "Tag must be 3-4 characters long and can only contain numbers and letters",
		maxLength = 4,
		minLength = 3,
		forceUpperCase = true,
		pattern = "^[%w]+$",
		buttonkey = {
			{ label = "Ok", action = "submit", type = "a_button" },
			{ label = "Cancel", action = "close", value = "-1", type = "b_button" },
		},
	},
	update_available = {
		title = "UPDATE_AVAILABLE",
		body = "An update for ElDewrito is available!",
		dialogHeight = 33.333,
		buttonkey = {
			{ label = "Update", action = "select", type = "a_button" },
			{ label = "Close", action = "close", value = "cancel", type = "b_button" },
		},
	},
	missing_launcher = {
		title = "UPDATE FAILED",
		body = "launcher.exe not found. Please download launcher.exe to your game directory and run it to update",
		icon = "warning",
		dialogHeight = 33.333,
		buttonkey = {
			{ label = "Close", action = "close", value = "cancel", type = "b_button" },
		},
	},
}

------------------------------------------------------------------------------------------
-- helpers
------------------------------------------------------------------------------------------

local function throttle(func, ms)
	local inThrottle = false
	return function(...)
		if not inThrottle then
			func(...)
			inThrottle = true
			dew.setTimeout(function() inThrottle = false end, ms)
		end
	end
end

local playSound = throttle(dew.playSound, 100)

local function find(list, predicate)
	for i, item in ipairs(list or {}) do
		if predicate(item) then
			return item, i
		end
	end
	return nil
end

local function shallowMerge(target, ...)
	for i = 1, select("#", ...) do
		local source = select(i, ...)
		if type(source) == "table" then
			for k, v in pairs(source) do
				target[k] = v
			end
		end
	end
	return target
end

-- dialog.js: escapeHtml + link wrapping + "|r|n" line breaks
local LINK_CHARS = "[%w%-+&@#/%%?=~_|!:,.;()]"
local function formatBody(text, disableLinks)
	local escaped = dew.escape(text or "")
	escaped = escaped:gsub("(https?://[^ |]+)", function(link)
		local raw = link:gsub("&amp;", "&"):gsub("&lt;", "<"):gsub("&gt;", ">"):gsub("&quot;", '"'):gsub("&#39;", "'")
		if raw:find("[^%w%-+&@#/%%?=~_|!:,.;()]") then
			return ""
		end
		if disableLinks then
			return '<span class="linkspan">' .. link .. "</span>"
		end
		return '<span class="link" data-href="' .. link .. '">' .. link .. "</span>"
	end)
	return (escaped:gsub("|r|n", "<br/>"))
end

local function vh(value)
	return string.format("%.5fvh", value)
end

------------------------------------------------------------------------------------------
-- state
------------------------------------------------------------------------------------------

local currentDialog = nil  -- head of a linked list (dialog.next)
local view = nil           -- per-dialog view state: hiliteOption, selectedOption, value, errorMessage
local listenersBound = false

local onDialogClose

local function host()
	return document:GetElementById("dialog_host")
end

local function dialogElement()
	return document:GetElementById("dialog")
end

------------------------------------------------------------------------------------------
-- rendering
------------------------------------------------------------------------------------------

local function renderButtons(buttonkey)
	local parts = {}
	for i, button in ipairs(buttonkey or {}) do
		local mouse = button.mouse
		if mouse == nil then mouse = true end
		parts[#parts + 1] = string.format(
			'<span class="button" data-btn="%s"><span class="button-icon"></span><span class="%s" data-button-index="%d">%s</span></span>',
			dew.escape(button.type or ""), mouse and "button-label" or "", i, dew.escape(button.label or ""))
	end
	return table.concat(parts)
end

local function charCountText()
	local d = currentDialog
	if d.maxLength == nil then
		return ""
	end
	return string.format("%d/%d", #(view.value or ""), d.maxLength)
end

local function updateCharCount()
	local element = document:GetElementById("charCount")
	if not element then
		return
	end
	element.inner_rml = charCountText()
	element:SetClass("countError", #(view.value or "") < (currentDialog.minLength or 0))
end

local function updateError()
	local element = document:GetElementById("inputError")
	if element then
		element.inner_rml = dew.escape(view.errorMessage or "")
		element.style.display = (view.errorMessage and #view.errorMessage > 0) and "block" or "none"
	end
end

local function updateHilite()
	local list = document:GetElementById("dialogList")
	if not list then
		return
	end
	for i, option in ipairs(currentDialog.options or {}) do
		local item = document:GetElementById("dialog_option_" .. i)
		if item then
			item:SetClass("hilite", view.hiliteOption == option.value)
			item:SetClass("selected", view.selectedOption == option.value)
		end
	end
end

local function render()
	local target = host()
	if not target then
		return
	end
	local d = currentDialog
	if not d then
		target.inner_rml = ""
		return
	end

	local icon = ""
	if d.icon and d.icon ~= "" then
		icon = string.format('<img class="dialog-icon" src="dew://assets/dialog/%s.png"/>', dew.escape(d.icon))
	end
	local iconOffset = (d.icon and d.icon ~= "") and " dialog-icon-offset" or ""

	local content
	if d.type == "input" then
		local inputMarkup
		local maxLength = d.maxLength and string.format(' maxlength="%d"', d.maxLength) or ""
		if (d.numRows or 1) > 1 then
			inputMarkup = string.format('<textarea id="inputBox" class="dialog_input" rows="%d"%s></textarea><div id="charCount" class="charCountTextarea"></div>', d.numRows, maxLength)
		else
			inputMarkup = string.format('<input id="inputBox" class="dialog_input" type="%s"%s/><div id="charCount" class="charCountInput"></div>', d.inputType == "password" and "password" or "text", maxLength)
		end
		content = string.format([[
			<div class="dialog-message-input%s"><div>%s</div></div>
			<div class="dialog_input_container">
				<div>%s</div>
				<div id="inputError" class="dialog_input_error" style="display: none;"></div>
			</div>]], iconOffset, d.formattedBody, inputMarkup)
	else
		local options = {}
		for i, option in ipairs(d.options or {}) do
			options[#options + 1] = string.format(
				'<li id="dialog_option_%d" class="dialog_option" data-option-index="%d"><div class="focusbar"></div><span class="option-label">%s</span></li>',
				i, i, dew.escape(option.label or ""))
		end
		local list = ""
		if #options > 0 then
			list = '<ul id="dialogList" class="dialog-list">' .. table.concat(options) .. "</ul>"
		end
		content = string.format('<div class="dialog-message%s"><div>%s</div></div><div>%s</div>', iconOffset, d.formattedBody, list)
	end

	target.inner_rml = string.format([[
		<div id="dialog">
			<div class="dialog-header">
				<div class="dialog-title slide-right">%s</div>
			</div>
			<div id="dialogBody" class="dialog-body">
				<div class="dialog-content slide-left">%s%s</div>
			</div>
			<div class="dialog-footer">
				<div class="button-key slide-right">%s</div>
			</div>
		</div>]], dew.escape(string.upper(d.title or "")), icon, content, renderButtons(d.buttonkey))

	local dialog = dialogElement()
	if d.dialogHeight and d.dialogHeight > 0 then
		dialog.style.height = vh(d.dialogHeight)
		dialog.style.top = vh(27.638 + (44.444 - d.dialogHeight) / 2)
		document:GetElementById("dialogBody").style.height = vh(37.083 - (44.444 - d.dialogHeight))
	end

	-- buttons
	for i, button in ipairs(d.buttonkey or {}) do
		local label = dialog:QuerySelector('[data-button-index="' .. i .. '"]')
		if label and label.class_name == "button-label" then
			label:AddEventListener("click", function()
				onButtonPress(button)
			end)
		end
	end

	-- options
	for i, option in ipairs(d.options or {}) do
		local item = document:GetElementById("dialog_option_" .. i)
		if item then
			item:AddEventListener("mouseover", function()
				if not view.selectedOption then
					view.hiliteOption = option.value
					updateHilite()
				end
			end)
			item:AddEventListener("click", function()
				selectOption(option.value)
				dew.playSound("a_button") -- avoid the throttle
			end)
		end
	end

	-- links in the body
	for _, link in ipairs(dialog:QuerySelectorAll(".link")) do
		link:AddEventListener("click", function()
			dew.playSound("a_button")
			onDialogClose(nil)
			local href = link:GetAttribute("data-href")
			dew.setTimeout(function() visitUrl(href) end, 650)
		end)
	end

	-- input box
	local input = document:GetElementById("inputBox")
	if input then
		if view.value and view.value ~= "" then
			input:SetAttribute("value", view.value)
		end
		input:AddEventListener("change", function(event)
			local value = event.parameters.value or input:GetAttribute("value") or ""
			local cleaned = value
			if d.forceUpperCase then
				cleaned = string.upper(cleaned)
			end
			cleaned = cleaned:gsub("[\r\n]", "")
			view.value = cleaned
			if cleaned ~= value then
				input:SetAttribute("value", cleaned)
			end
			updateCharCount()
		end)
		input:AddEventListener("keydown", function(event)
			local key = tonumber(event.parameters.key_identifier)
			if key == 72 then -- KI_RETURN
				if not d.allowReturn then
					onButtonPress(find(d.buttonkey, function(b) return b.type == "a_button" end))
				end
			elseif key == 81 then -- KI_ESCAPE
				onButtonPress(find(d.buttonkey, function(b) return b.type == "b_button" end))
			end
		end)
		updateCharCount()
		dew.setTimeout(function() input:Focus() end, 25) -- v-autofocus
	end

	updateHilite()

	-- enter animation (class added next frame so the transition runs)
	dew.requestAnimationFrame(function()
		local element = dialogElement()
		if element then
			element:SetClass("show", true)
		end
	end)
end

------------------------------------------------------------------------------------------
-- behaviour (dew-dialog / dew-input-dialog methods)
------------------------------------------------------------------------------------------

local function close(result)
	onDialogClose(result)
end

local function shakeAnimate()
	local element = dialogElement()
	if not element then return end
	element:SetClass("shake", true)
	dew.setTimeout(function()
		local e = dialogElement()
		if e then e:SetClass("shake", false) end
	end, 100)
end

local function submit()
	local d = currentDialog
	local value = view.value or ""
	if (d.pattern and not value:match(d.pattern)) or (d.validate and not d.validate(value)) or #value < (d.minLength or 0) then
		view.errorMessage = d.regexFailMessage or "Invalid input"
		updateError()
		playSound("error")
		shakeAnimate()
	else
		close((value:gsub("%s+$", ""))) -- strip trailing spaces
	end
end

function selectOption(option)
	view.selectedOption = option
	close(option)
end

function onButtonPress(button)
	if not button or not button.action then
		return
	end
	local d = currentDialog
	if button.action == "select" and d.type ~= "input" then
		selectOption(view.hiliteOption)
	elseif button.action == "close" then
		close(button.value)
	elseif button.action == "submit" and d.type == "input" then
		submit()
	end
	if button.type == "a_button" then
		playSound("a_button")
	elseif button.type == "b_button" then
		playSound("b_button")
	end
end

local function navigateOptions(dir)
	local options = currentDialog.options or {}
	local _, currentIndex = find(options, function(o) return o.value == view.hiliteOption end)
	currentIndex = (currentIndex or 0) - 1 -- 0-based like the JS
	if (dir > 0 and currentIndex == #options - 1) or (dir < 0 and currentIndex == 0) then
		return
	end
	currentIndex = currentIndex + dir
	if currentIndex < 0 then
		currentIndex = currentIndex + #options
	end
	view.hiliteOption = options[(currentIndex % #options) + 1].value
	updateHilite()
end

local function onInputAction(evt)
	if not currentDialog then
		return
	end
	local d = currentDialog
	if evt.action == dew.input.Actions.A then
		if d.type == "input" and evt.inputType == "keyboard" then
			local input = document:GetElementById("inputBox")
			if input and document.context and document.context.focus_element == input then
				return
			end
		end
		onButtonPress(find(d.buttonkey, function(b) return b.type == "a_button" end))
	elseif evt.action == dew.input.Actions.B then
		onButtonPress(find(d.buttonkey, function(b) return b.type == "b_button" end))
	end
end

local function onInputScroll(scrollType, axis, direction)
	if not currentDialog or currentDialog.type == "input" then
		return
	end
	if axis == 0 and #(currentDialog.options or {}) > 0 then
		playSound("vertical_navigation")
		navigateOptions(direction)
	end
end

local function onMouseDown(event)
	if not currentDialog then
		return
	end
	if tonumber(event.parameters.button) == 1 then -- right button
		onButtonPress(find(currentDialog.buttonkey, function(b) return b.type == "b_button" end))
	end
end

------------------------------------------------------------------------------------------
-- the dialog queue (the Vue root app)
------------------------------------------------------------------------------------------

local function setBackdrop(visible)
	local backdrop = document:GetElementById("backdrop")
	if backdrop then
		backdrop:SetClass("visible", visible)
	end
end

local function newView(d)
	view = { hiliteOption = nil, selectedOption = nil, value = "", errorMessage = "" }
	if d.type == "input" then
		if d.initialValue then
			view.value = tostring(d.initialValue)
		end
	else
		for _, option in ipairs(d.options or {}) do
			if option.default then
				view.hiliteOption = option.value
				break
			end
		end
	end
end

local function showCurrent()
	if currentDialog then
		newView(currentDialog)
		setBackdrop(true)
	else
		view = nil
		setBackdrop(false)
	end
	render()
end

local function pushDialog(d)
	if currentDialog then
		local tail = currentDialog
		while tail.next do
			tail = tail.next
		end
		tail.next = d
	else
		currentDialog = d
		if currentDialog.fullScreenBlur then
			dew.GameBlur("dialog", true)
		end
		showCurrent()
	end
end

local function popDialog()
	if not currentDialog.next and currentDialog.fullScreenBlur then
		dew.GameBlur("dialog", false)
	end
	currentDialog = currentDialog.next
	showCurrent()
end

onDialogClose = function(result)
	local d = currentDialog
	if not d then
		return
	end
	popDialog()
	d.onClose(result)
end

local function closeAndPopDialog(result)
	onDialogClose(result)
end

local function onDialogCloseRequest(message)
	if currentDialog and message.data == currentDialog.templateName then
		closeAndPopDialog()
	end
end

local function onNativeDialogRequest(data)
	dew.dialog(data.template, data.data or {}):next(function(result)
		dew.callMethod("submitDialogResult", { id = data.nativeId, result = result })
	end)
end

local function onDialogRequest(message)
	local data = message.data or {}
	local template = data.template
	if type(template) == "string" then
		template = DIALOG_TEMPLATES[template]
	end

	if data.native then
		if template == nil then
			dew.callMethod("submitDialogResult", { id = data.nativeId, result = "" })
			return
		end
		return onNativeDialogRequest(data)
	end

	if template == nil then
		return
	end

	local d = shallowMerge({
		templateName = data.template,
		type = "none",
		options = {},
		buttonkey = {},
		fullScreenBlur = true,
		inputType = "text",
		minLength = 0,
		forceUpperCase = false,
		dialogHeight = 0,
		icon = "",
	}, template, {
		id = data.id,
		onClose = function(result)
			result = result or ""
			dew.notifyDialogResult(data.id, data.screen, result)
			-- if there are no more dialogs to show, hide the screen once the animation ends
			dew.setTimeout(function()
				if not currentDialog then
					dew.hide()
				end
			end, 400)
		end,
	}, data.data)
	d.next = nil

	local disableLinks = d.disableLinks == true
	d.formattedBody = formatBody(d.body, disableLinks)

	if currentDialog and currentDialog.autoDismissable then
		local id = currentDialog.id
		dew.setTimeout(function()
			if currentDialog and currentDialog.id == id then
				closeAndPopDialog()
			end
		end, 700)
	end

	pushDialog(d)
	dew.show()
end

function visitUrl(url)
	dew.dialog("confirm_link", {
		body = "This link goes to " .. url .. "|r|nAre you sure you want to open this?",
	}):next(function(result)
		if result == "yes" then
			dew.setTimeout(function() dew.openUrl(url) end, 450)
		end
	end)
end

dew.on("dialog", onDialogRequest)
dew.on("dialogClose", onDialogCloseRequest)
dew.input.on("action", onInputAction)
dew.input.on("scroll", onInputScroll)
document:AddEventListener("mousedown", onMouseDown)

-- Print Screen takes a screenshot while the dialog has focus
document:AddEventListener("keyup", function(event)
	if tonumber(event.parameters.key_identifier) == 97 then -- KI_SNAPSHOT
		dew.command("Game.TakeScreenshot")
	end
end)
