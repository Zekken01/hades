-- Port of screens/weapon_offset/weapons.js

local selectedItem
local itemNumber = 0
local hasGP = false
local axisThreshold = 0.5
local stickTicks = { left = 0, right = 0, up = 0, down = 0 }
local repGP
local lastHeldUpdated = 0
local currentWeaponType = ""
-- jQuery's .val() fired no input/change events, but RmlUi raises "change" for values set
-- from script, once at once and once more on the next update.  Remember what the page
-- wrote per control and ignore change events that still report it.
local written = {}
local rebuildingOptions = false

-- KI values
local KI_ESCAPE, KI_OEM_3, KI_F1, KI_OEM_8, KI_SNAPSHOT, KI_TAB = 81, 44, 107, 49, 97, 70
local KI_LEFT, KI_UP, KI_RIGHT, KI_DOWN = 90, 91, 92, 93

local AXES = { "weaponI", "weaponJ", "weaponK" }

local function el(id) return document:GetElementById(id) end

local function value(id)
	local element = el(id)
	return element and (element:GetAttribute("value") or "") or ""
end

local function setValue(id, newValue)
	local element = el(id)
	if element then
		written[id] = tostring(newValue)
		element:SetAttribute("value", tostring(newValue))
		written[id] = element:GetAttribute("value") or ""
	end
end

-- true when the control's change event reports a value the page wrote itself
local function isScriptChange(id)
	return written[id] ~= nil and written[id] == value(id)
end

local function fixed3(number)
	local text = string.format("%.3f", tonumber(number) or 0)
	if text == "-0.000" then
		text = "0.000"
	end
	return text
end

local function items()
	return document:QuerySelectorAll("#weaponOffsets .item")
end

local function isDisabled(element)
	return element ~= nil and element:IsClassSet("disabled")
end

local function sendOffset()
	dew.command("Weapon.Offset " .. currentWeaponType .. " " .. value("weaponIText") .. " " .. value("weaponJText") .. " " .. value("weaponKText"))
end

local function showOffsets(offsets)
	offsets = offsets or {}
	for i, id in ipairs(AXES) do
		local offset = tonumber(offsets[i]) or 0
		setValue(id, -offset)
		setValue(id .. "Text", fixed3(offset))
	end
end

local function closeWindow()
	dew.command("Weapon.JSON.Load " .. value("wOffsetConfigList"))
	dew.playSound("b_button")
	dew.hide()
end

local function updateSelection(item)
	jq(".selectedElement"):removeClass("selectedElement")
	local element = items()[item + 1]
	selectedItem = nil
	if element then
		element:SetClass("selectedElement", true)
		local setting = element:QuerySelector(".setting")
		selectedItem = setting and setting.id or nil
	end
end

local function upNav()
	if itemNumber > 0 then
		itemNumber = itemNumber - 1
		updateSelection(itemNumber)
		dew.playSound("vertical_navigation")
	end
end

local function downNav()
	if itemNumber < #items() - 1 then
		itemNumber = itemNumber + 1
		updateSelection(itemNumber)
		dew.playSound("vertical_navigation")
	end
end

-- GetElementById returns plain Elements; the select API (options, 1-based selection) needs
-- the cast.  Options live in RmlUi's internal select box, out of reach of QuerySelectorAll.
local function asSelect(element)
	return Element.As.ElementFormControlSelect(element)
end

local function optionCount(select)
	local count = 0
	for _ in ipairs(asSelect(select).options) do
		count = count + 1
	end
	return count
end

-- 0-based like jQuery's index(); -1 without a selection
local function selectIndex(select)
	return (tonumber(asSelect(select).selection) or 0) - 1
end

-- the select's change handler runs from the "change" event the selection raises
local function selectByIndex(select, index)
	asSelect(select).selection = index + 1
end

local function stepSlider(slider, direction)
	if isDisabled(slider) then
		dew.playSound("error")
		return
	end
	dew.playSound("a_button")
	local step = tonumber(slider:GetAttribute("step")) or 1
	local min = tonumber(slider:GetAttribute("min")) or 0
	local max = tonumber(slider:GetAttribute("max")) or 100
	local current = tonumber(slider:GetAttribute("value")) or 0
	local newValue = math.max(min, math.min(max, current + direction * step))
	-- snap to the step grid like stepUp/stepDown
	newValue = math.floor((newValue - min) / step + 0.5) * step + min
	setValue(slider.id, newValue)
	setValue(slider.id .. "Text", fixed3(-newValue))
	sendOffset() -- $(slider).trigger('change')
end

local function toggle(direction)
	local element = selectedItem and el(selectedItem)
	if not element then
		return
	end
	if element.tag_name == "select" then
		local index = selectIndex(element)
		local count = optionCount(element)
		local newIndex = index + direction
		if newIndex >= 0 and newIndex < count then
			selectByIndex(element, newIndex)
		end
	elseif element.tag_name == "input" then
		stepSlider(element, direction)
	end
end

local function leftToggle() toggle(-1) end
local function rightToggle() toggle(1) end

local function checkGamepad()
	local now = dew_core.getTime() * 1000
	local shouldUpdateHeld = false
	if now - lastHeldUpdated > 100 then
		shouldUpdateHeld = true
		lastHeldUpdated = now
	end
	if stickTicks.up == 1 or (shouldUpdateHeld and stickTicks.up > 25) then upNav() end
	if stickTicks.down == 1 or (shouldUpdateHeld and stickTicks.down > 25) then downNav() end
	if stickTicks.left == 1 or (shouldUpdateHeld and stickTicks.left > 25) then leftToggle() end
	if stickTicks.right == 1 or (shouldUpdateHeld and stickTicks.right > 25) then rightToggle() end
end

local function onControllerConnect()
	updateSelection(itemNumber)
end

local function onControllerDisconnect()
	jq(".selected"):removeClass("selected")
end

local function initGamepad()
	dew.command("Settings.Gamepad", {}):next(function(result)
		if tonumber(result) == 1 then
			hasGP = true
			if not repGP then
				repGP = dew.setInterval(checkGamepad, 1000 / 60)
			end
			onControllerConnect()
		else
			onControllerDisconnect()
			hasGP = false
			if repGP then
				dew.clearInterval(repGP)
				repGP = nil
			end
		end
	end)
end

local function setInputsDisabled(disabled)
	local function apply(element)
		element:SetClass("disabled", disabled)
		if disabled then
			element:SetAttribute("disabled", "")
		else
			element:RemoveAttribute("disabled")
		end
	end
	for _, element in ipairs(document:QuerySelectorAll("input")) do apply(element) end
	for _, id in ipairs({ "resetButton", "deleteButton", "saveButton" }) do apply(el(id)) end
end

local function setOptionList(elementId, list)
	local select = el(elementId)
	local rml = {}
	for _, entry in ipairs(list) do
		rml[#rml + 1] = '<option value="' .. dew.escape(entry[2]) .. '">' .. dew.escape(entry[1]) .. "</option>"
	end
	-- the rebuilt select picks its first option and reports it on a later update
	rebuildingOptions = true
	select.inner_rml = table.concat(rml)
	dew.requestAnimationFrame(function()
		dew.requestAnimationFrame(function() rebuildingOptions = false end)
	end)
end

local function decode(response)
	local ok, result = pcall(json.decode, response)
	if ok and type(result) == "table" then
		return result
	end
	return {}
end

local function showEquipped(response)
	local weaponInfo = decode(response)
	currentWeaponType = tostring(weaponInfo.Type or "")
	jq("#weaponTypeName"):text(weaponInfo.DisplayName or "")
	showOffsets(weaponInfo.FirstPersonWeaponOffset)
end

local function resetEquipped()
	dew.command("Weapon.Equipped", {}):next(showEquipped)
end

local function displayOffset(weapon)
	dew.command("Weapon.Offset " .. weapon, {}):next(function(response)
		showOffsets(decode(response).FirstPersonWeaponOffset)
	end)
end

local function initializeWeaponOffsetList()
	dew.command("Weapon.JSON.List", {}):next(function(response)
		local offsetArray = {}
		for name in (tostring(response) .. ","):gmatch("([^,]*),") do
			if not name:find(" ", 1, true) then
				offsetArray[#offsetArray + 1] = { name, name }
			end
		end
		setOptionList("wOffsetConfigList", offsetArray)

		dew.command("Weapon.JSON.File", {}):next(function(file)
			setInputsDisabled(file == "default")
			setValue("wOffsetConfigList", file)
		end)
	end)

	dew.command("Weapon.Equipped", {}):next(showEquipped)
end

local function setButtons()
	jq("#newButton img"):attr("src", "dew://assets/buttons/360_Back.png")
	jq("#deleteButton img"):attr("src", "dew://assets/buttons/360_Y.png")
	jq("#resetButton img"):attr("src", "dew://assets/buttons/360_X.png")
	jq("#saveButton img"):attr("src", "dew://assets/buttons/360_A.png")
	jq("#closeButton img"):attr("src", "dew://assets/buttons/360_B.png")
end

-- disabled buttons ignore clicks, as in the browser
local function onButton(id, handler)
	el(id):AddEventListener("click", function()
		if not isDisabled(el(id)) then
			handler()
		end
	end)
end

local function newConfig()
	dew.playSound("a_button")
	dew.dialog("new_weapon_offset"):next(function(result)
		if result ~= "" and result ~= "cancel" and result ~= nil then
			dew.command("Weapon.Json.New " .. tostring(result)):next(function(saveResult)
				if saveResult == "Config Already Exists" then
					dew.dialog("weapon_offset_exists")
				end
				if saveResult == "Weapons offset config saved successfully." then
					initializeWeaponOffsetList()
				end
			end)
		end
	end)
end

local function deleteConfig()
	dew.playSound("x_button")
	dew.dialog("weapon_offset_delete", { body = "Are you sure you want to delete the weapon offset config named: " .. value("wOffsetConfigList") }):next(function(result)
		if result == "yes" then
			dew.command("Weapon.Json.Delete " .. value("wOffsetConfigList")):next(function(deleteResult)
				if deleteResult == "Weapons offset deleted successfully." then
					initializeWeaponOffsetList()
				end
				if deleteResult == "Failed to delete weapon offiset config file." then
					dew.dialog("weapon_offset_delete_error")
				end
			end)
		end
	end)
end

local function saveConfig()
	dew.playSound("a_button")
	dew.dialog("confirm_save_weapon_offset"):next(function(result)
		if result == "yes" then
			dew.command("Weapon.JSON.Save")
		end
	end)
end

local function resetConfig()
	dew.playSound("x_button")
	dew.dialog("confirm_reset_weapon_offset"):next(function(result)
		if result == "yes" then
			dew.command("Weapon.Offset.Reset " .. currentWeaponType, {}):next(function()
				resetEquipped()
			end)
		end
	end)
end

local function click(id)
	local element = el(id)
	if element and not isDisabled(element) then
		element:Click()
	end
end

document:AddEventListener("keyup", function(event)
	local key = tonumber(event.parameters.key_identifier)
	if key == KI_ESCAPE then
		closeWindow()
	end
	if key == KI_SNAPSHOT then
		dew.command("Game.TakeScreenshot")
	end
end)

document:AddEventListener("keydown", function(event)
	local key = tonumber(event.parameters.key_identifier)
	if key == KI_OEM_3 or key == KI_F1 or key == KI_OEM_8 then
		dew.show("console")
	end
	-- StopPropagation also skips the default action (focus moves, slider steps)
	if key == KI_UP then event:StopPropagation(); upNav() end
	if key == KI_DOWN then event:StopPropagation(); downNav() end
	if key == KI_LEFT then event:StopPropagation(); leftToggle() end
	if key == KI_RIGHT then event:StopPropagation(); rightToggle() end
	if key == KI_TAB then event:StopPropagation() end
end)

dew.on("show", function()
	dew.command("Weapon.Equipped", {}):next(function(response)
		if tostring(decode(response).Type or "") == "" then
			dew.playSound("error")
			dew.hide()
			return
		end

		initializeWeaponOffsetList()

		dew.command("Settings.Gamepad", {}):next(function(result)
			if tonumber(result) == 1 then
				onControllerConnect()
				hasGP = true
			else
				onControllerDisconnect()
				hasGP = false
			end
		end)

		dew.command("Game.unpause")
	end)
end)

dew.on("controllerinput", function(e)
	if not hasGP then
		return
	end
	local c = e.data or {}
	if c.Select == 1 then click("newButton") end
	if c.Y == 1 then click("deleteButton") end
	if c.B == 1 then closeWindow() end
	if c.X == 1 then click("resetButton") end
	if c.A == 1 then click("saveButton") end
	if c.Up == 1 then upNav() end
	if c.Down == 1 then downNav() end
	if c.Left == 1 then leftToggle() end
	if c.Right == 1 then rightToggle() end
	local x, y = tonumber(c.AxisLeftX) or 0, tonumber(c.AxisLeftY) or 0
	if x > axisThreshold then stickTicks.right = stickTicks.right + 1 else stickTicks.right = 0 end
	if x < -axisThreshold then stickTicks.left = stickTicks.left + 1 else stickTicks.left = 0 end
	if y > axisThreshold then stickTicks.up = stickTicks.up + 1 else stickTicks.up = 0 end
	if y < -axisThreshold then stickTicks.down = stickTicks.down + 1 else stickTicks.down = 0 end
end)

document:AddEventListener("load", function()
	initGamepad()

	for position, item in ipairs(items()) do
		item:AddEventListener("mouseover", function()
			itemNumber = position - 1
			updateSelection(itemNumber)
		end)
	end

	for _, id in ipairs(AXES) do
		-- slider moved by the user: mirror into the text box and apply ('input change')
		el(id):AddEventListener("change", function()
			if isScriptChange(id) then
				return
			end
			written[id] = value(id) -- handled; ignore the deferred repeat
			local number = tonumber(value(id)) or 0
			setValue(id .. "Text", fixed3(-number))
			sendOffset()
		end)
		-- text box edited: mirror into the slider and apply
		el(id .. "Text"):AddEventListener("change", function()
			if isScriptChange(id .. "Text") then
				return
			end
			written[id .. "Text"] = value(id .. "Text")
			local number = tonumber(value(id .. "Text"))
			if number then
				setValue(id, -number)
				sendOffset()
			end
		end)
	end

	onButton("newButton", newConfig)
	onButton("deleteButton", deleteConfig)
	onButton("saveButton", saveConfig)
	onButton("resetButton", resetConfig)
	el("closeButton"):AddEventListener("click", closeWindow)

	el("wOffsetConfigList"):AddEventListener("change", function()
		if rebuildingOptions or isScriptChange("wOffsetConfigList") then
			written["wOffsetConfigList"] = value("wOffsetConfigList")
			return
		end
		local config = value("wOffsetConfigList")
		written["wOffsetConfigList"] = config -- handled; ignore the deferred repeat
		setInputsDisabled(config == "default")
		dew.command("Weapon.JSON.Load " .. config, {}):next(function()
			displayOffset(currentWeaponType)
			dew.playSound("a_button")
		end)
	end)

	setButtons()
end)
