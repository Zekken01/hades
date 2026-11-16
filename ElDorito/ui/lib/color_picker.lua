--[[
	color_picker.lua -- port of lib/color-picker.js (dew.makeColorPicker) and ColorUtil.

	The canvas palette becomes stacked elements: the hue colour, a white-to-transparent and a
	transparent-to-black gradient.  Styles live in style-global.rcss.

		local picker = dew.makeColorPicker(containerElement)
		picker.on("select", function(color) ... end)   -- color = { h, s, v }
		picker.setColor({ h = 240, s = 1, v = 1 })
		picker.controllerInput(data)
]]

ColorUtil = {}

function ColorUtil.hsvToRgb(h, s, v)
	h = h / 360
	v = math.floor(v * 255 + 0.5)
	local i = math.floor(h * 6)
	local f = h * 6 - i
	local p = math.floor(v * (1 - s) + 0.5)
	local q = math.floor(v * (1 - f * s) + 0.5)
	local t = math.floor(v * (1 - (1 - f) * s) + 0.5)
	local mod = i % 6
	if mod == 0 then return { v, t, p }
	elseif mod == 1 then return { q, v, p }
	elseif mod == 2 then return { p, v, t }
	elseif mod == 3 then return { p, q, v }
	elseif mod == 4 then return { t, p, v }
	end
	return { v, p, q }
end

function ColorUtil.rgbToHsv(r, g, b)
	local max, min = math.max(r, g, b), math.min(r, g, b)
	local d = max - min
	local h
	local s = max == 0 and 0 or d / max
	local v = max / 255
	if max == min then h = 0
	elseif max == r then h = ((g - b) + d * (g < b and 6 or 0)) / (6 * d)
	elseif max == g then h = ((b - r) + d * 2) / (6 * d)
	else h = ((r - g) + d * 4) / (6 * d) end
	return { h = h, s = s, v = v }
end

function ColorUtil.hexToHsv(hex)
	if type(hex) ~= "string" or #hex ~= 6 then return nil end
	local n = tonumber(hex, 16)
	if not n then return nil end
	local hsv = ColorUtil.rgbToHsv((n >> 16) & 255, (n >> 8) & 255, n & 255)
	return { h = hsv.h * 360, s = hsv.s, v = hsv.v }
end

function ColorUtil.rgbToHex(r, g, b)
	return string.format("%x", ((r & 255) << 16) | ((g & 255) << 8) | (b & 255))
end

local function clamp(value, min, max)
	if value < min then return min end
	if value > max then return max end
	return value
end

-- the element's on-screen box (transforms and scrolling applied)
local function screenBox(element)
	local box = dew_core.debugBox(element)
	if box and box.w > 0 and box.h > 0 then
		return box.x, box.y, box.w, box.h
	end
	return 0, 0, element.client_width, element.client_height
end

function dew.makeColorPicker(container)
	local callbacks = {}
	local state = { selectedColor = { h = 240, s = 1, v = 1 }, isDragging = false }
	local writtenHue, writtenHex = nil, nil

	container.inner_rml = [[
		<div class="ed-color-picker">
			<div class="ed-color-picker__palette-wrapper">
				<div class="ed-color-picker__palette"></div>
				<div class="ed-color-picker__palette-white"></div>
				<div class="ed-color-picker__palette-black"></div>
				<div class="ed-color-picker__palette-thumb"></div>
			</div>
			<div class="ed-color-picker__hue-slider-wrapper">
				<input class="ed-color-picker__hue-slider" type="range" min="0" max="360" value="240"/>
			</div>
			<div class="ed-color-picker__detail">
				<div class="ed-color-picker_rgb_output"><div>R: 0</div><div>G: 0</div><div>B: 0</div></div>
				<div>HEX: <input class="ed-color-picker__detail_hex-input" type="text" maxlength="7" value=""/></div>
			</div>
		</div>]]

	local wrapper = container:QuerySelector(".ed-color-picker__palette-wrapper")
	local palette = container:QuerySelector(".ed-color-picker__palette")
	local thumb = container:QuerySelector(".ed-color-picker__palette-thumb")
	local hueSlider = container:QuerySelector(".ed-color-picker__hue-slider")
	local hueWrapper = container:QuerySelector(".ed-color-picker__hue-slider-wrapper")
	local hexInput = container:QuerySelector(".ed-color-picker__detail_hex-input")
	local outputs = container:QuerySelectorAll(".ed-color-picker_rgb_output div")

	local function emit(eventName, data)
		for _, cb in ipairs(callbacks[eventName] or {}) do
			cb(data)
		end
	end

	local function render()
		local color = state.selectedColor
		local hueRgb = ColorUtil.hsvToRgb(color.h, 1, 1)
		palette.style["background-color"] = string.format("#%02x%02x%02x", hueRgb[1], hueRgb[2], hueRgb[3])
		-- percentages, centred by the thumb's negative margins: right even before layout
		thumb.style.left = string.format("%.3f%%", color.s * 100)
		thumb.style.top = string.format("%.3f%%", (1 - color.v) * 100)
		writtenHue = tostring(math.floor(color.h + 0.5))
		hueSlider:SetAttribute("value", writtenHue)
		writtenHue = hueSlider:GetAttribute("value")
		local rgb = ColorUtil.hsvToRgb(color.h, color.s, color.v)
		outputs[1].inner_rml = "R: " .. rgb[1]
		outputs[2].inner_rml = "G: " .. rgb[2]
		outputs[3].inner_rml = "B: " .. rgb[3]
		writtenHex = string.format("#%02X%02X%02X", rgb[1], rgb[2], rgb[3])
		hexInput:SetAttribute("value", writtenHex)
	end

	local function setColorInternal(color, shouldEmit)
		local newColor = { h = state.selectedColor.h, s = state.selectedColor.s, v = state.selectedColor.v }
		for k, v in pairs(color) do newColor[k] = tonumber(v) end
		if not newColor.h or not newColor.s or not newColor.v then return end
		state.selectedColor = newColor
		render()
		if shouldEmit then
			emit("select", state.selectedColor)
		end
	end

	-- Palette and hue bar follow the mouse with RmlUi's drag events, which stay with the element
	-- the drag started on until the button is released (like the browser's pointer capture);
	-- `drag: drag` on both in style-global.rcss.
	local function mouseFraction(element, event)
		local x0, y0, width, height = screenBox(element)
		local x = clamp((tonumber(event.parameters.mouse_x) or 0) - x0, 0, width)
		local y = clamp((tonumber(event.parameters.mouse_y) or 0) - y0, 0, height)
		return x / width, y / height
	end

	local function paletteAt(event)
		local fx, fy = mouseFraction(wrapper, event)
		setColorInternal({ s = fx, v = 1 - fy }, true)
	end

	local function hueAt(event)
		local fx = mouseFraction(hueWrapper, event)
		setColorInternal({ h = fx * 360 }, true)
	end

	local function isLeft(event)
		return (tonumber(event.parameters.button) or 0) == 0
	end

	wrapper:AddEventListener("mousedown", function(event) if isLeft(event) then paletteAt(event) end end)
	wrapper:AddEventListener("drag", paletteAt)
	hueWrapper:AddEventListener("mousedown", function(event) if isLeft(event) then hueAt(event) end end)
	hueWrapper:AddEventListener("drag", hueAt)

	hueSlider:AddEventListener("change", function()
		local value = hueSlider:GetAttribute("value")
		if value == writtenHue then return end
		setColorInternal({ h = tonumber(value) }, true)
	end)

	hexInput:AddEventListener("change", function()
		local text = hexInput:GetAttribute("value") or ""
		if text == writtenHex then return end
		local value = "#" .. text:gsub("[^a-fA-F0-9]", ""):upper()
		if value ~= text then
			hexInput:SetAttribute("value", value)
		end
		local hsv = ColorUtil.hexToHsv(value:sub(2))
		if hsv then setColorInternal(hsv, true) end
	end)

	render()
	-- the first render runs before layout (no size yet): place the thumb again once laid out
	dew.requestAnimationFrame(function() render() end)

	return {
		on = function(eventName, callback)
			callbacks[eventName] = callbacks[eventName] or {}
			table.insert(callbacks[eventName], callback)
		end,
		setColor = function(color)
			setColorInternal(color or {}, false)
			dew.requestAnimationFrame(function() render() end)
		end,
		getColor = function() return state.selectedColor end,
		controllerInput = function(data)
			local axisThreshold, paletteSpeed, hueSliderSpeed = 0.08, 0.02, 2
			local c = state.selectedColor
			local h, s, v = c.h, c.s, c.v
			local changed = false
			local rx, ry, lx = tonumber(data.AxisRightX) or 0, tonumber(data.AxisRightY) or 0, tonumber(data.AxisLeftX) or 0
			if math.abs(rx) > axisThreshold then s = clamp(s + paletteSpeed * rx, 0, 1); changed = true end
			if math.abs(ry) > axisThreshold then v = clamp(v + paletteSpeed * ry, 0, 1); changed = true end
			if math.abs(lx) > axisThreshold then h = clamp(h + hueSliderSpeed * lx, 0, 360); changed = true end
			if changed then setColorInternal({ h = h, s = s, v = v }, true) end
		end,
		refresh = function() render() end,
	}
end
