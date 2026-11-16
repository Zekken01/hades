--[[
	forge.lua -- Lua port of the forge screens' shared libraries:
	  shared/lib/constants.js            Forge.OBJECT_PROPERTY_TARGET_NAMES, Forge.PALETTE_ITEM_TYPE_NAMES
	  shared/lib/screen-manager.js       Forge.makeScreenManager()
	  shared/lib/list-widget.js          Forge.makeListWidget(element, settings)
	  shared/lib/tree-list-widget.js     Forge.makeTreeList(element)
	  shared/lib/property-grid-widget.js Forge.makePropertyGrid(element)

	The web versions walked XML DOM nodes; here a tree is plain tables:
		node = { tag = "category" | "item", attrs = { name = ..., ... }, children = { ... }, parent = node }
	(Forge.node / Forge.append build them, Forge.hasCategoryDescendant replaces
	getElementsByTagName('category').length.)

	Lua element handles are not comparable, so list items are found through the attributes
	"lw" (owning widget) and "idx" (0-based item index) stamped on them by the widget.
	Needs dew://lib/input.lua loaded first.
]]

Forge = {}

------------------------------------------------------------------------------------------
-- constants.js (0-based in JS; index with value + 1)
------------------------------------------------------------------------------------------

Forge.OBJECT_PROPERTY_TARGET_NAMES = {
	"on_map_at_start", "symmetry", "respawn_rate", "spare_clips", "spawn_order", "team",
	"teleporter_channel", "shape_type", "shape_radius", "shape_width", "shape_top", "shape_bottom",
	"shape_depth", "physics", "engine_flags", "reforge_material", "reforge_material_color_r",
	"reforge_material_color_g", "reforge_material_color_b", "reforge_material_texture_override",
	"reforge_material_texture_scale", "reforge_material_texture_offset_x",
	"reforge_material_texture_offset_y", "reforge_material_allows_projectiles",
	"reforge_mateiral_type", "light_type", "light_color_r", "light_color_g", "light_color_b",
	"light_intensity", "light_radius", "light_field_of_view", "light_near_width",
	"light_illumination_type", "light_illumination_base", "light_illumination_freq", "fx_range",
	"fx_light_intensity", "fx_hue", "fx_saturation", "fx_desaturation", "fx_gamma_increase",
	"fx_gamma_decrease", "fx_color_filter_r", "fx_color_filter_g", "fx_color_filter_b",
	"fx_color_floor_r", "fx_color_floor_g", "fx_color_floor_b", "fx_tracing",
	"garbage_volume_collect_dead_biped", "garbage_volume_collect_weapons",
	"garbage_volume_collect_objectives", "garbage_volume_collect_grenades",
	"garbage_volume_collect_equipment", "garbage_volume_collect_vehicles", "garbage_volume_interval",
	"kill_volume_always_visible", "kill_volume_destroy_vehicles", "kill_volume_damage_cause",
	"map_disable_push_barrier", "map_disable_death_barrier", "map_physics_gravity",
	"camera_fx_exposure", "camera_fx_light_intensity", "camera_fx_bloom", "camera_fx_light_bloom",
	"atmosphere_properties_enabled", "atmosphere_properties_weather",
	"atmosphere_properties_brightness", "atmosphere_properties_fog_density",
	"atmosphere_properties_fog_visibility", "atmosphere_properties_fog_color_r",
	"atmosphere_properties_fog_color_g", "atmosphere_properties_fog_color_b",
	"atmosphere_properties_skybox", "atmosphere_properties_skybox_offset_z",
	"atmosphere_properties_skybox_override_transform", "budget_minimum", "budget_maximum",
}

Forge.PALETTE_ITEM_TYPE_NAMES = {
	"general", "tool", "prop", "light", "effects", "structure", "equipment", "weapon", "vehicle",
	"teleporter", "game", "assault", "ctf", "infection", "juggernaut", "koth", "territories",
	"slayer", "vip",
}

function Forge.paletteTypeName(index)
	return Forge.PALETTE_ITEM_TYPE_NAMES[(tonumber(index) or -1) + 1]
end

------------------------------------------------------------------------------------------
-- helpers
------------------------------------------------------------------------------------------

function Forge.escape(text)
	return dew.escape(tostring(text == nil and "" or text))
end

function Forge.node(tag, attrs)
	return { tag = tag, attrs = attrs or {}, children = {} }
end

function Forge.append(parent, child)
	child.parent = parent
	parent.children[#parent.children + 1] = child
	return child
end

function Forge.hasCategoryDescendant(node)
	for _, child in ipairs(node.children) do
		if child.tag == "category" or Forge.hasCategoryDescendant(child) then
			return true
		end
	end
	return false
end

-- every descendant with the given tag, document order (getElementsByTagName)
function Forge.descendants(node, tag, out)
	out = out or {}
	for _, child in ipairs(node.children) do
		if child.tag == tag then out[#out + 1] = child end
		Forge.descendants(child, tag, out)
	end
	return out
end

-- blur whatever has keyboard focus (document.activeElement.blur())
function Forge.blurActive()
	local context = document.context
	local focused = context and context.focus_element
	if focused then focused:Blur() end
end

local function nowMs()
	return dew_core.getTime() * 1000
end

local function addClass(element, name) if element then element:SetClass(name, true) end end
local function removeClass(element, name) if element then element:SetClass(name, false) end end
Forge.addClass, Forge.removeClass = addClass, removeClass

------------------------------------------------------------------------------------------
-- screen-manager.js
------------------------------------------------------------------------------------------

function Forge.makeScreenManager()
	local stack = {}
	local screensByName = {}
	local queue = {}
	local lastTimeRequestHandled = 0

	dew.input.on("action", function(action)
		local active = stack[#stack]
		if active and active.onAction then
			active.onAction(action)
		end
	end)

	dew.input.on("tick", function()
		if nowMs() - lastTimeRequestHandled < 70 then
			return
		end
		lastTimeRequestHandled = nowMs()
		while #queue > 0 do
			table.remove(queue, 1)()
		end
	end)

	local manager = {}

	function manager.count() return #stack end
	function manager.any() return #stack > 0 end
	function manager.currentScreen() return stack[#stack] end
	function manager.setModel(model) screensByName = model end

	function manager.push(name, props)
		props = props or {}
		queue[#queue + 1] = function()
			local screen = screensByName[name]
			if not screen then
				console.error("failed to find screen '" .. tostring(name) .. "'")
				return
			end
			screen.name = name
			if #stack > 0 then
				stack[#stack].deactivate(props)
			end
			stack[#stack + 1] = screen
			screen.activate(props)
		end
	end

	function manager.pop()
		queue[#queue + 1] = function()
			if #stack < 2 then
				return
			end
			local screen = table.remove(stack)
			if screen then
				screen.deactivate({})
			end
			stack[#stack].activate(nil)
		end
	end

	function manager.popAll(includeRoot)
		if includeRoot == nil then includeRoot = true end
		while #stack > (includeRoot and 0 or 1) do
			local screen = table.remove(stack)
			if screen then
				screen.deactivate({})
			end
		end
		if not includeRoot and #stack > 0 then
			stack[#stack].activate({})
		end
	end

	-- the queue drains on the input tick; tests can force it
	function manager.flush()
		while #queue > 0 do
			table.remove(queue, 1)()
		end
	end

	return manager
end

------------------------------------------------------------------------------------------
-- list-widget.js
------------------------------------------------------------------------------------------

local widgetCounter = 0

function Forge.makeListWidget(elem, settings)
	widgetCounter = widgetCounter + 1
	local wid = "lw" .. widgetCounter
	local callbacks = {}
	local itemNodes = {}      -- 1-based array of elements
	local current = nil       -- 0-based index of the current item, nil = none
	local hasFocus = false

	settings = settings or {}
	settings.pageSize = settings.pageSize or 4
	settings.hoverClass = settings.hoverClass or "selected"

	local function emit(eventType, data)
		for _, callback in ipairs(callbacks[eventType] or {}) do
			callback(data)
		end
	end

	local function cacheItemNodes()
		itemNodes = {}
		local nodes
		if settings.itemSelector then
			nodes = elem:QuerySelectorAll(settings.itemSelector)
		else
			nodes = elem.child_nodes
		end
		for _, node in ipairs(nodes) do
			itemNodes[#itemNodes + 1] = node
			node:SetAttribute("lw", wid)
			node:SetAttribute("idx", tostring(#itemNodes - 1))
		end
	end

	local function render()
		for i, node in ipairs(itemNodes) do
			node:SetClass(settings.hoverClass, current ~= nil and current == i - 1)
		end
	end

	local function setCurrent(index, notify)
		if current == index then
			return
		end
		current = index
		render()
		if notify and index ~= nil then
			emit("selectionChange", { index = index, element = itemNodes[index + 1] })
		end
	end

	local function setSelectedIndex(index, notify, scrollTo)
		local count = #itemNodes
		if index >= count then
			index = settings.wrapAround and 0 or (count - 1)
		end
		if index < 0 then
			index = settings.wrapAround and (count - 1) or 0
		end
		if count == 0 then
			setCurrent(nil, notify)
			return -1
		end
		setCurrent(index, notify)
		if scrollTo and itemNodes[index + 1] then
			itemNodes[index + 1]:ScrollIntoView(false)
		end
		return index
	end

	local function navigate(count)
		local oldIndex = current or -1
		local newIndex = setSelectedIndex(oldIndex + count, true, true)
		if oldIndex ~= -1 and newIndex ~= -1 and oldIndex ~= newIndex then
			dew.input.playSound(dew.input.Sounds.VerticalNavigation)
		end
	end

	-- the item an event target belongs to (0-based index), and whether the target sits in a
	-- form control (mouseDownFilterSelector 'select,input')
	local function itemOf(target)
		local inControl = false
		local node = target
		while node do
			local tag = node.tag_name
			if tag == "select" or tag == "input" or tag == "selectbox" then
				inControl = true
			end
			if node:GetAttribute("lw") == wid then
				return tonumber(node:GetAttribute("idx")), inControl
			end
			if tag == "body" then break end
			node = node.parent_node
		end
		return nil, inControl
	end

	elem:AddEventListener("mousemove", function(event)
		if not hasFocus or not settings.hoverSelection then
			return
		end
		local index = itemOf(event.target_element)
		if index then
			setCurrent(index, true)
		end
	end)

	elem:AddEventListener("mousedown", function(event)
		if not hasFocus or tonumber(event.parameters.button) ~= 0 then
			return
		end
		local index, inControl = itemOf(event.target_element)
		if index then
			setCurrent(index, false)
			if not (settings.mouseDownFilter and inControl) then
				dew.input.playSound(dew.input.Sounds.A)
				emit("select", { index = index, element = itemNodes[index + 1] })
			end
		end
	end)

	dew.input.on("scroll", function(type, axis, direction)
		if not hasFocus or axis ~= 0 then
			return
		end
		if type < 2 then
			navigate(direction)
		elseif type == 2 then
			local index = current or -1
			if (direction < 0 and index == 0) or (direction > 0 and index == #itemNodes - 1) then
				return
			end
			local newIndex = index + settings.pageSize * direction
			if newIndex >= #itemNodes then newIndex = #itemNodes - 1 end
			if newIndex < 0 then newIndex = 0 end
			dew.input.playSound(dew.input.Sounds.LeftTrigger + (direction > 0 and 1 or 0))
			setSelectedIndex(newIndex, true, true)
		end
	end)

	dew.input.on("action", function(e)
		if not hasFocus then
			return
		end
		if e.action == dew.input.Actions.A and current ~= nil and itemNodes[current + 1] then
			dew.input.playSound(dew.input.Sounds.A)
			emit("select", { index = current, element = itemNodes[current + 1] })
		end
	end)

	cacheItemNodes()
	render()

	return {
		navigate = navigate,
		setSelected = function(index, scrollTo)
			if index == -1 then
				setCurrent(nil)
				render()
				return -1
			end
			return setSelectedIndex(index, false, scrollTo)
		end,
		getSelected = function()
			if current == nil then return nil end
			return { index = current, element = itemNodes[current + 1] }
		end,
		itemCount = function() return #itemNodes end,
		on = function(eventType, callback)
			callbacks[eventType] = callbacks[eventType] or {}
			table.insert(callbacks[eventType], callback)
		end,
		focus = function()
			cacheItemNodes()
			hasFocus = true
			elem:SetClass("has-focus", true)
		end,
		blur = function()
			hasFocus = false
			elem:SetClass("has-focus", false)
		end,
		hasFocus = function() return hasFocus end,
		refresh = function()
			cacheItemNodes()
			if current ~= nil and current >= #itemNodes then
				current = nil
			end
			render()
		end,
	}
end

------------------------------------------------------------------------------------------
-- tree-list-widget.js
------------------------------------------------------------------------------------------

function Forge.makeTreeList(element)
	local stack = {}
	local paths = {}
	local callbacks = {}
	local hasFocus = false

	local listWidget = Forge.makeListWidget(element, {
		itemSelector = "li",
		hoverSelection = true,
		hoverClass = "selected",
		wrapAround = true,
	})

	local function emit(eventType, data)
		for _, callback in ipairs(callbacks[eventType] or {}) do
			callback(data)
		end
	end

	local function render()
		local top = stack[#stack]
		if not top then return end
		local html = {}
		paths = {}
		for _, n in ipairs(top.node.children) do
			if n.tag == "category" then
				paths[#paths + 1] = n
				html[#html + 1] = '<li class="item"><span>' .. Forge.escape(n.attrs.name) .. "</span></li>"
			end
		end
		element.inner_rml = table.concat(html)
	end

	local function push(node)
		if not node or not Forge.hasCategoryDescendant(node) then
			return
		end
		local selected = listWidget.getSelected()
		stack[#stack + 1] = { node = node, index = selected and selected.index or 0 }
		render()
		listWidget.refresh()
		listWidget.setSelected(0)
		emit("push", node)
		emit("change", { index = 0, path = node })
	end

	local function pop()
		if #stack < 2 then
			return
		end
		local lastIndex = stack[#stack].index
		table.remove(stack)
		render()
		listWidget.refresh()
		listWidget.setSelected(lastIndex)
		emit("pop")
		local current = stack[#stack]
		if current then
			emit("change", { index = lastIndex, path = current.node })
		end
	end

	listWidget.on("selectionChange", function(e)
		emit("selectionChange", { index = e.index, element = e.element, path = paths[e.index + 1] })
	end)

	listWidget.on("select", function(e)
		emit("select", { index = e.index, element = e.element, path = paths[e.index + 1] })
		push(paths[e.index + 1])
	end)

	dew.input.on("action", function(e)
		if hasFocus and e.action == dew.input.Actions.B then
			dew.input.playSound(dew.input.Sounds.B)
			pop()
		end
	end)

	return {
		focus = function()
			hasFocus = true
			listWidget.focus()
		end,
		blur = function()
			hasFocus = false
			listWidget.blur()
		end,
		on = function(eventType, callback)
			callbacks[eventType] = callbacks[eventType] or {}
			table.insert(callbacks[eventType], callback)
		end,
		atRoot = function() return #stack == 1 end,
		setSource = function(node)
			stack = {}
			paths = {}
			push(node)
			render()
		end,
		gotoRoot = function()
			while #stack > 1 do
				pop()
			end
			render()
			listWidget.refresh()
			listWidget.setSelected(0)
		end,
		pop = pop,
	}
end

------------------------------------------------------------------------------------------
-- property-grid-widget.js
------------------------------------------------------------------------------------------

local KI_UP, KI_DOWN = 91, 93
local uidCounter = 0

local function uid()
	uidCounter = uidCounter + 1
	return "pg" .. uidCounter
end

local function fixed(value, digits)
	return string.format("%." .. digits .. "f", value)
end

local function makeGridModel()
	local properties = {}
	local model = { properties = properties }
	function model.add(data)
		properties[#properties + 1] = data
	end
	function model.group(label, build)
		local group = { label = label, data = makeGridModel() }
		build(group.data)
		properties[#properties + 1] = group
	end
	return model
end

-- Each factory returns { model, rml, bind(), setValue(value, notify), scroll(type, dir), refresh() };
-- bind() runs once the RML is in the document.
local PropertyItemViewFactory = {}

function PropertyItemViewFactory.action(model)
	return {
		model = model,
		rml = "",
		bind = function() end,
		setValue = function() end,
		scroll = function() end,
		refresh = function() end,
	}
end

function PropertyItemViewFactory.static(model)
	local id = uid()
	local data = { model = model }
	data.rml = '<div class="item-editor"><div id="' .. id .. '"></div></div>'
	local node
	function data.bind()
		node = document:GetElementById(id)
		data.setValue(model.getValue(), false)
	end
	function data.setValue(value)
		if node then node.inner_rml = Forge.escape(value) end
	end
	data.scroll = function() end
	function data.refresh() data.setValue(model.getValue(), false) end
	return data
end

function PropertyItemViewFactory.color(model)
	local id = uid()
	local data = { model = model }
	data.rml = '<div class="item-editor"><div class="color-preview" id="' .. id .. '"></div></div>'
	local preview
	function data.bind()
		preview = document:GetElementById(id)
		data.setValue(model.getValue(), false)
	end
	function data.setValue(value, notifyModel)
		if value == nil then return end
		if notifyModel == nil then notifyModel = true end
		if preview then
			preview.style["background-color"] = string.format("rgb(%d,%d,%d)", value.r, value.g, value.b)
		end
		if notifyModel then
			model.setValue(value)
		end
	end
	data.scroll = function() end
	function data.refresh() data.setValue(model.getValue(), false) end
	return data
end

function PropertyItemViewFactory.spinner(model)
	local id = uid()
	local data = { model = model }
	local options = {}
	for _, option in ipairs(model.meta) do
		local value, label
		if type(option) == "table" then
			value, label = option.value, option.label
		else
			value, label = option, option
		end
		options[#options + 1] = '<option value="' .. Forge.escape(value) .. '">' .. Forge.escape(label) .. "</option>"
	end
	data.rml = '<div class="item-editor"><select id="' .. id .. '">' .. table.concat(options) .. "</select></div>"

	local select
	local written

	local function selectedIndex()
		local current = select:GetAttribute("value")
		for i, option in ipairs(model.meta) do
			local value = type(option) == "table" and option.value or option
			if tostring(value) == current then return i end
		end
		return 1
	end

	local function write(value)
		select:SetAttribute("value", tostring(value))
		written = select:GetAttribute("value")
	end

	function data.bind()
		select = document:GetElementById(id)
		data.setValue(model.getValue(), false)
		select:AddEventListener("change", function()
			local value = select:GetAttribute("value")
			if value == written then return end
			written = value
			model.setValue(math.tointeger(tonumber(value)) or tonumber(value))
		end)
	end

	function data.setValue(value, notifyModel)
		if notifyModel == nil then notifyModel = true end
		value = math.tointeger(tonumber(value)) or tonumber(value) or 0
		if select then write(value) end
		if notifyModel then model.setValue(value) end
	end

	function data.scroll(_, direction)
		if not select then return end
		local count = #model.meta
		local index = selectedIndex() + direction
		if index > count then index = 1 end
		if index < 1 then index = count end
		local option = model.meta[index]
		local value = type(option) == "table" and option.value or option
		write(value)
		model.setValue(math.tointeger(tonumber(value)) or tonumber(value))
		dew.input.playSound(dew.input.Sounds.HorizontalNavigation)
	end

	function data.refresh() data.setValue(model.getValue(), false) end
	return data
end

function PropertyItemViewFactory.range(model)
	local meta = model.meta
	local textId, rangeId = uid(), uid()
	local data = { model = model }
	data.rml = string.format(
		'<div class="item-editor"><input type="text" id="%s"/><input type="range" min="%s" max="%s" step="%s" id="%s"/></div>',
		textId, tostring(meta.min), tostring(meta.max), tostring(meta.step), rangeId)

	local text, range
	local writtenRange, writtenText
	local current = tonumber(model.getValue()) or meta.min

	local function apply(value, notifyModel)
		if type(value) == "string" then value = tonumber(value) end
		local isNan = value == nil or value ~= value
		if not meta.allowUnboundedInput then
			if not isNan and value > meta.max then value = meta.max end
			if isNan or value < meta.min then value = meta.min end
		end
		if value == nil or value ~= value then value = meta.min end

		local display
		if meta.isInteger then
			value = math.floor(value)
			display = meta.displayTextOverride and meta.displayTextOverride(value) or tostring(math.tointeger(value) or value)
		else
			display = meta.displayTextOverride and meta.displayTextOverride(value) or fixed(value, 2)
		end
		current = value
		if range then
			range:SetAttribute("value", tostring(value))
			writtenRange = range:GetAttribute("value")
		end
		if text then
			text:SetAttribute("value", display)
			writtenText = text:GetAttribute("value")
		end
		if notifyModel then model.setValue(value) end
	end

	function data.bind()
		text = document:GetElementById(textId)
		range = document:GetElementById(rangeId)
		apply(model.getValue(), false)

		range:AddEventListener("change", function()
			local value = range:GetAttribute("value")
			if value == writtenRange then return end
			apply(value, true)
		end)

		local function commitText()
			local value = text:GetAttribute("value")
			if value == writtenText then return end
			apply(value, true)
		end
		text:AddEventListener("change", function(event)
			if dew.truthy(event.parameters.linebreak) then commitText() end
		end)
		text:AddEventListener("blur", commitText)
		text:AddEventListener("keydown", function(event)
			local key = tonumber(event.parameters.key_identifier)
			if key == KI_UP or key == KI_DOWN then
				commitText()
				event:StopPropagation()
			end
		end)
	end

	function data.setValue(value, notifyModel)
		if notifyModel == nil then notifyModel = true end
		apply(value, notifyModel)
	end

	function data.scroll(type, direction)
		local amount = type == 1 and meta.step * 4 or meta.step
		apply(current + amount * direction, true)
		dew.input.playSound(dew.input.Sounds.HorizontalNavigation)
	end

	function data.refresh() apply(model.getValue(), false) end
	return data
end

function Forge.makePropertyGrid(elem)
	local items = {}
	local hasFocus = false
	local callbacks = {}
	local currentModel = nil

	local listWidget = Forge.makeListWidget(elem, {
		itemSelector = ".item",
		hoverClass = "selected",
		wrapAround = true,
		hoverSelection = true,
		mouseDownFilter = true,
	})

	local function emit(event, data)
		for _, callback in ipairs(callbacks[event] or {}) do
			callback(data)
		end
	end

	local function renderItem(html, views, model)
		if not model.type then
			html[#html + 1] = '<div class="heading"><span>' .. Forge.escape(model.label) .. "</span></div>"
			for _, child in ipairs(model.data.properties) do
				renderItem(html, views, child)
			end
			return
		end
		local view = PropertyItemViewFactory[model.type](model)
		html[#html + 1] = '<div class="item"><div class="label">' .. Forge.escape(model.label) .. "</div>" .. view.rml .. "</div>"
		views[#views + 1] = view
	end

	local function render()
		if not currentModel then return end
		local html, views = {}, {}
		for _, model in ipairs(currentModel.properties) do
			renderItem(html, views, model)
		end
		elem.inner_rml = table.concat(html)
		items = views
		for _, view in ipairs(items) do
			view.bind()
		end
	end

	local function setModel(model)
		local selected = listWidget.getSelected()
		local selectedIndex = selected and selected.index or 0
		currentModel = model
		items = {}
		render()
		listWidget.refresh()
		listWidget.setSelected(selectedIndex, false)
		if selectedIndex < 0 or selectedIndex >= #items then
			return
		end
		if hasFocus then
			emit("selectionChange", items[selectedIndex + 1])
		end
	end

	dew.input.on("scroll", function(type, axis, direction)
		if not hasFocus then
			return
		end
		Forge.blurActive()
		if type < 2 and axis == 1 then
			local selected = listWidget.getSelected()
			if not selected then return end
			local item = items[selected.index + 1]
			if item then item.scroll(type, direction) end
		end
	end)

	listWidget.on("selectionChange", function(e)
		local item = items[e.index + 1]
		if item then
			emit("selectionChange", item)
		end
	end)

	listWidget.on("select", function()
		if not hasFocus then return end
		Forge.blurActive()
		local selected = listWidget.getSelected()
		if not selected then return end
		local item = items[selected.index + 1]
		if item and item.model.action then
			item.model.action(item)
		end
	end)

	return {
		blur = function()
			hasFocus = false
			listWidget.blur()
		end,
		focus = function()
			hasFocus = true
			listWidget.focus()
		end,
		hasFocus = function() return hasFocus end,
		createModel = makeGridModel,
		setModel = setModel,
		refresh = function()
			for _, item in ipairs(items) do
				item.refresh()
			end
		end,
		on = function(event, callback)
			callbacks[event] = callbacks[event] or {}
			table.insert(callbacks[event], callback)
		end,
		list = listWidget,
	}
end
