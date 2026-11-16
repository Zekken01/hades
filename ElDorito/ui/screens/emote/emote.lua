-- Port of screens/emote/emote.js

local items = {}
local widgetType = 0
local widgetStyle = {}
local wheelRadius = 250
local controllerbind = ""
local keyboardbinds = {}
local initalKeyboardKey = false
local initalControllerKey = false
local maxEmoteCount = 20
local hasGP = false
local currentPosition = { 0, 0 }
local selectedIndex = nil -- wheel slice (0-based), nil when none
local colors = {}
local iconSize = 100
local showToken = 0

local KI_SNAPSHOT, KI_ESCAPE = 97, 81
local WHEEL_DP = 270
local GRID_CELL = 90

local function el(id) return document:GetElementById(id) end

-- Rml key identifiers -> the key names Input.DumpBindingsJson uses (ModuleInput keyCodes)
local KEY_NAMES = {
	[1] = "Space", [44] = "Tilde", [69] = "Back", [70] = "Tab", [72] = "Enter", [81] = "Escape",
	[86] = "PageUp", [87] = "PageDown", [88] = "End", [89] = "Home", [90] = "Left", [91] = "Up",
	[92] = "Right", [93] = "Down", [98] = "Insert", [99] = "Delete",
	[138] = "LShift", [139] = "RShift", [140] = "LControl", [141] = "RControl",
}
for i = 0, 9 do KEY_NAMES[2 + i] = tostring(i) end
for i = 0, 25 do KEY_NAMES[12 + i] = string.char(65 + i) end
for i = 1, 12 do KEY_NAMES[106 + i] = "F" .. i end

local function isKeyboardBind(key)
	local name = KEY_NAMES[key]
	if not name then
		return false
	end
	for _, bind in ipairs(keyboardbinds) do
		if bind == name then
			return true
		end
	end
	return false
end

-- 0xAARRGGBB -> hex colour and 0..1 alpha (SVG) / #rrggbbaa (RCSS)
local function pixel32(argb)
	argb = math.tointeger(tonumber(argb) or 0) or 0
	local a = (argb >> 24) & 0xFF
	local r = (argb >> 16) & 0xFF
	local g = (argb >> 8) & 0xFF
	local b = argb & 0xFF
	return {
		svg = string.format("#%02x%02x%02x", r, g, b),
		alpha = a / 255,
		rcss = string.format("#%02x%02x%02x%02x", r, g, b, a),
	}
end

local function calculateRowsAndColumns(itemCount)
	local maxColumns = 5
	local cols = math.min(itemCount, maxColumns)
	local rows = cols > 0 and math.ceil(itemCount / cols) or 0
	return rows, cols
end

------------------------------------------------------------------------------------------
-- wheel

local function point(angle, r)
	return math.cos(angle) * r + wheelRadius, math.sin(angle) * r + wheelRadius
end

local function fill(color)
	return string.format('fill="%s" fill-opacity="%.3f"', color.svg, color.alpha)
end

local function stroke(color)
	return string.format('stroke="%s" stroke-opacity="%.3f" stroke-width="2"', color.svg, color.alpha)
end

local function renderWheel()
	local innerScale = 2.2
	local radius = wheelRadius
	local inner = radius / innerScale
	local slices = #items
	local parts = {}
	local function slice(index, d)
		local color = index == selectedIndex and colors.highlight or colors.background
		parts[#parts + 1] = string.format('<path d="%s" %s %s/>', d, fill(color), stroke(colors.border))
	end
	if slices == 1 then
		local a1 = math.pi * 2 / 4 * 3 - math.pi
		local a2 = math.pi * 2 / 4 * (1.9999 + 1) - math.pi
		local x1, y1 = point(a1, radius)
		local x2, y2 = point(a2, radius)
		local x4, y4 = point(a1, inner)
		local x3, y3 = point(a2, inner)
		slice(0, string.format("M %f %f A %f %f 0 1 1 %f %f L %f %f A %f %f 0 1 0 %f %f z",
			x1, y1, radius, radius, x2, y2, x3, y3, inner, inner, x4, y4))
	else
		for i = 0, slices - 1 do
			local a1 = math.pi * 2 / slices * i - math.pi
			local a2 = math.pi * 2 / slices * (i + 1) - math.pi
			local x1, y1 = point(a1, radius)
			local x2, y2 = point(a2, radius)
			local x4, y4 = point(a1, inner)
			local x3, y3 = point(a2, inner)
			slice(i, string.format("M %f %f A %f %f 0 0 1 %f %f L %f %f A %f %f 0 0 0 %f %f z",
				x1, y1, radius, radius, x2, y2, x3, y3, inner, inner, x4, y4))
		end
	end
	parts[#parts + 1] = string.format('<circle cx="250" cy="250" r="250" fill="none" %s/>', stroke(colors.border))
	parts[#parts + 1] = string.format('<circle cx="250" cy="250" r="113" fill="none" %s/>', stroke(colors.border))
	el("wheelSvg").inner_rml = table.concat(parts)
end

local function iconCenter(i, slices)
	local angle
	if slices == 1 then
		angle = math.pi * 2 / 2 * 0 - math.pi + math.pi / 2
	else
		angle = math.pi * 2 / slices * i - math.pi + math.pi / slices
	end
	return point(angle, wheelRadius / 1.38)
end

local function placeWheelIcons()
	local scale = WHEEL_DP / (wheelRadius * 2)
	local parts = {}
	for i, item in ipairs(items) do
		local cx, cy = iconCenter(i - 1, #items)
		parts[#parts + 1] = string.format(
			'<img class="emote-icon" src="%s" style="left: %.2fdp; top: %.2fdp; width: %.2fdp; height: %.2fdp;"/>',
			dew.escape(item.icon), (cx - iconSize / 2) * scale, (cy - iconSize / 2) * scale, iconSize * scale, iconSize * scale)
	end
	el("wheelIcons").inner_rml = table.concat(parts)
end

local function setWheelSelection(index)
	if index ~= selectedIndex then
		selectedIndex = index
		renderWheel()
	end
end

-- theta from a direction (x right, y up), as the web page computed it
local function sliceFromDirection(x, y)
	local theta = math.atan(x, y) + math.pi / 2
	if theta < 0 then
		theta = theta + 2 * math.pi
	end
	local index = math.floor(theta / (math.pi * 2) * #items)
	if index >= 0 and index < #items then
		return index
	end
	return nil
end

------------------------------------------------------------------------------------------
-- grid

local function gridCells()
	return el("emoteGrid"):QuerySelectorAll(".emote-cell")
end

local function selectGridCell(cell)
	for _, other in ipairs(gridCells()) do
		other:SetClass("selected", false)
		other.style["background-color"] = colors.background.rcss
	end
	if cell then
		cell:SetClass("selected", true)
		cell.style["background-color"] = colors.highlight.rcss
	end
end

local function createGrid(cellSize)
	local rows, cols = calculateRowsAndColumns(#items)
	local borderSize = 1
	local cellSizeWithBorder = cellSize - borderSize + (borderSize * 2)
	local parts = {}
	local itemIndex = 0
	for i = 0, rows - 1 do
		for j = 0, cols - 1 do
			if itemIndex >= #items then
				break
			end
			local item = items[itemIndex + 1]
			local hasName = item.title ~= nil and item.title ~= ""
			local imageSize = cellSize - (hasName and 20 or 10)
			-- grid tracks of cellSize, cells one border wider and centred in their track
			local x = j * cellSize - (cellSizeWithBorder - cellSize) / 2
			local y = i * cellSize - (cellSizeWithBorder - cellSize) / 2
			local cell = string.format(
				'<div class="emote-cell" data-index="%d" data-position="%d-%d" style="left: %.1fdp; top: %.1fdp; width: %ddp; height: %ddp; background-color: %s; border-color: %s;">'
				.. '<img class="emote-icon" src="%s" style="width: %ddp; height: %ddp;"/>',
				itemIndex, i, j, x, y, cellSizeWithBorder, cellSizeWithBorder, colors.background.rcss, colors.border.rcss,
				dew.escape(item.icon), imageSize, imageSize)
			if hasName then
				cell = cell .. string.format('<span class="emote-name" style="color: %s;">%s</span>', colors.text.rcss, dew.escape(item.title))
			end
			parts[#parts + 1] = cell .. "</div>"
			itemIndex = itemIndex + 1
		end
	end
	local width, height = cols * cellSize, rows * cellSize
	return string.format('<div id="emoteGridCells" style="left: %.1fdp; top: %.1fdp; width: %ddp; height: %ddp;">%s</div>',
		(570 - width) / 2, (570 - height) / 2, width, height, table.concat(parts))
end

local function wireGridCells()
	for _, cell in ipairs(gridCells()) do
		cell:AddEventListener("mouseover", function()
			if widgetType == 1 then
				selectGridCell(cell)
			end
		end)
	end
end

------------------------------------------------------------------------------------------

local function grow(element)
	element:SetClass("grow", false)
	dew.requestAnimationFrame(function()
		dew.requestAnimationFrame(function() element:SetClass("grow", true) end)
	end)
end

local function drawSelector()
	if widgetType == 0 then
		el("emoteWheel").style.display = "block"
		iconSize = 100
		if #items > 8 then
			iconSize = iconSize - 4 * (#items - 8) -- start scaling icons down if too many emotes
		end
		selectedIndex = nil
		renderWheel()
		placeWheelIcons()
		grow(el("emoteWheel"))
	end
	if widgetType == 1 then
		el("emoteGrid").style.display = "block"
		el("emoteGrid").inner_rml = createGrid(GRID_CELL)
		wireGridCells()
		grow(el("emoteGrid"))
	end
end

local function selectedGridCell()
	return el("emoteGrid"):QuerySelector(".emote-cell.selected")
end

local function selectEmote(index)
	index = tonumber(index)
	local item = index and items[index + 1]
	if widgetType == 0 then
		selectedIndex = nil
	end
	if widgetType == 1 then
		selectGridCell(nil)
	end
	if item then
		dew.command("Player.Emote " .. tostring(item.index))
	end
	dew.hide()
end

local function selectCurrent()
	if widgetType == 0 then
		if selectedIndex then
			selectEmote(selectedIndex)
		end
	elseif widgetType == 1 then
		local cell = selectedGridCell()
		if cell then
			selectEmote(cell:GetAttribute("data-index"))
		end
	end
end

local function fetchEmoteIcons(emotes, done)
	local icons, pending = {}, #emotes
	if pending == 0 then
		done(icons)
		return
	end
	for i, emoteItem in ipairs(emotes) do
		dew.getAssetUrl("assets/emotes/" .. tostring(emoteItem.iconName or ""), { pak = "game", fileTypes = { "jpg", "png" } }):next(function(url)
			icons[i] = url or ""
		end, function()
			icons[i] = ""
		end):finally(function()
			pending = pending - 1
			if pending == 0 then
				done(icons)
			end
		end)
	end
end

dew.on("show", function(event)
	local data = event.data or {}
	showToken = showToken + 1
	local token = showToken
	if widgetType == 1 then
		currentPosition = { 0, 0 }
	end

	dew.command("Settings.gamepad"):next(function(response)
		hasGP = tonumber(response) == 1
	end)
	keyboardbinds = {}
	dew.command("Input.DumpBindingsJson", {}):next(function(response)
		local ok, bindDump = pcall(json.decode, response)
		if not ok or type(bindDump) ~= "table" then
			return
		end
		for _, bind in ipairs(bindDump) do
			if bind.actionName == "Emote" then
				controllerbind = bind.controllerButton
				keyboardbinds[#keyboardbinds + 1] = bind.primaryKey
				keyboardbinds[#keyboardbinds + 1] = bind.secondaryKey
			end
		end
	end)

	initalKeyboardKey = true
	initalControllerKey = true

	items = {}
	widgetType = tonumber(data.widgetType) or 0
	widgetStyle = data.style or {}
	colors = {
		background = pixel32(widgetStyle.backgroundColor),
		highlight = pixel32(widgetStyle.highlightColor),
		border = pixel32(widgetStyle.borderColor),
		text = pixel32(widgetStyle.textColor),
	}

	local emotes = {}
	for i, emote in ipairs(data.emotes or {}) do
		if i > maxEmoteCount then
			break -- limit the number of emotes that can be displayed
		end
		emotes[i] = emote
	end

	fetchEmoteIcons(emotes, function(emoteIcons)
		if token ~= showToken then
			return
		end
		for i, emoteItem in ipairs(emotes) do
			local url = emoteIcons[i]
			local imageURL = "dew://assets/emblems/generic.png"
			if url and url ~= "" then
				imageURL = url
			end
			items[#items + 1] = { title = emoteItem.title, name = emoteItem.animationName, icon = imageURL, index = emoteItem.emoteIndex }
		end
		drawSelector()
		if hasGP and widgetType == 1 then
			selectGridCell(el("emoteGrid"):QuerySelector('[data-position="0-0"]'))
		end
	end)
end)

dew.on("hide", function()
	el("emoteWheel"):SetClass("grow", false)
	el("emoteGrid"):SetClass("grow", false)
	el("emoteWheel").style.display = "none"
	el("emoteGrid").style.display = "none"
end)

dew.on("controllerinput", function(e)
	if not hasGP then
		return
	end
	local c = e.data or {}
	local axisThreshold = 8689 / 32767.0

	if tonumber(c[controllerbind]) == 0 and initalControllerKey then -- key is up
		initalControllerKey = false
		if widgetType == 0 and selectedIndex then
			selectEmote(selectedIndex)
		end
	end

	if (tonumber(c[controllerbind]) or 0) > 0 and not initalControllerKey then -- key is down
		dew.hide()
	end

	if widgetType == 0 then
		local lx, ly = tonumber(c.AxisLeftX) or 0, tonumber(c.AxisLeftY) or 0
		local rx, ry = tonumber(c.AxisRightX) or 0, tonumber(c.AxisRightY) or 0
		if math.abs(lx) >= axisThreshold or math.abs(ly) >= axisThreshold then
			setWheelSelection(sliceFromDirection(lx, ly))
		elseif math.abs(rx) >= axisThreshold or math.abs(ry) >= axisThreshold then
			setWheelSelection(sliceFromDirection(rx, ry))
		end
	end

	if c.B == 1 then
		dew.hide()
	elseif c.A == 1 then
		selectCurrent()
	end
end)

local function handleVirtualScroll(_, axis, value)
	if widgetType ~= 1 then
		return
	end
	local tmpPosition = { currentPosition[1], currentPosition[2] }
	if axis == 0 then
		tmpPosition[2] = currentPosition[2] + value
	end
	if axis == 1 then
		tmpPosition[1] = currentPosition[1] + value
	end
	local pos = string.format("%d-%d", tmpPosition[2], tmpPosition[1])
	local cell = el("emoteGrid"):QuerySelector('[data-position="' .. pos .. '"]')
	if cell then
		currentPosition = tmpPosition
		selectGridCell(cell)
	end
end

dew.input.on("scroll", handleVirtualScroll)
dew.input.on("right_scroll", handleVirtualScroll)

-- the page is centred in the window and scaled by min(w/1280, h/720)
local function pageMetrics()
	local width, height = document.offset_width, document.offset_height
	local ratio = math.min(width / 1280, height / 720)
	return width / 2, height / 2, math.min(1280 * ratio, 720 * ratio)
end

document:AddEventListener("mousemove", function(event)
	if widgetType ~= 0 or #items == 0 then
		return
	end
	local cx, cy, size = pageMetrics()
	local deltaX = (tonumber(event.parameters.mouse_x) or 0) - cx
	local deltaY = -((tonumber(event.parameters.mouse_y) or 0) - cy)
	local distance = math.sqrt(deltaX * deltaX + deltaY * deltaY)
	local radius = size * 0.084
	if distance >= radius then
		setWheelSelection(sliceFromDirection(deltaX, deltaY))
	else
		setWheelSelection(nil)
	end
end)

document:AddEventListener("mousedown", function(event)
	local button = tonumber(event.parameters.button)
	if button == 0 then
		selectCurrent()
	elseif button == 1 then
		dew.hide()
	end
end)

document:AddEventListener("keyup", function(event)
	local key = tonumber(event.parameters.key_identifier)
	if key == KI_SNAPSHOT then
		dew.command("Game.TakeScreenshot")
	end
	if isKeyboardBind(key) and initalKeyboardKey then
		initalKeyboardKey = false
		selectCurrent()
	end
end)

document:AddEventListener("keydown", function(event)
	local key = tonumber(event.parameters.key_identifier)
	if key == KI_ESCAPE then
		dew.hide()
	end
	if isKeyboardBind(key) and not initalKeyboardKey then
		dew.hide()
	end
end)
