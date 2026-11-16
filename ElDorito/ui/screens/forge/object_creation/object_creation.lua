--[[
	object_creation.lua -- port of screens/forge/object_creation/object_creation.js.

	The palette comes from callMethod('forgePalette') as JSON and becomes a Forge.node tree
	(categories with item children).  Fuse's fuzzy search is replaced by searchItems():
	substring hits first, then in-order character matches, best first.
]]

local KI_SNAPSHOT = 97

local screenManager
local itemDatasource
local containerElement, footerElement, titleElement, objectQuotaElement
local budget = {}
local hidden = false
local itemHistory = {}

local function q(selector, root)
	return (root or document):QuerySelector(selector)
end

-- the character a key produces for the search box (0-9, A-Z, numpad digits), or nil
local function keyChar(key)
	if key >= 2 and key <= 11 then return string.char(48 + key - 2) end
	if key >= 12 and key <= 37 then return string.char(65 + key - 12) end
	if key >= 51 and key <= 60 then return string.char(48 + key - 51) end
	return nil
end

-- the "rel" of the legend link an event hit
local function relOf(target)
	local node = target
	while node and node.tag_name ~= "body" do
		local rel = node:GetAttribute("rel")
		if rel then return rel end
		node = node.parent_node
	end
	return nil
end

local function setTitle(text)
	titleElement.inner_rml = Forge.escape(text or "")
end

local function hide()
	hidden = true
	dew.hide()
end

local function showToast(message)
	dew.toast({ body = '<div style="font-size: 1.2em; padding: 4dp">' .. Forge.escape(message) .. "</div>" })
end

local function updateObjectQuotaText()
	dew.command("Forge.Budget"):next(function(response)
		local quota = json.decode(response)
		if type(quota) ~= "table" then return end
		objectQuotaElement.inner_rml = string.format("%s / %s", tostring(quota.total_used), tostring(quota.total_available))
	end)
end

local function setInfoText(box, text)
	text = text or ""
	box:QuerySelector(".info-text").inner_rml = Forge.escape(text)
	box:SetClass("empty", text == "")
end

local function renderBreadcrumbs(screenElement, path)
	local header = q(".category-header", screenElement)
	if #path == 0 then
		header.inner_rml = '<div class="hline"></div>'
		header:SetClass("filled", false)
		return
	end
	local html = {}
	for i, p in ipairs(path) do
		local last = i == #path and #path > 1
		html[#html + 1] = '<span class="crumb' .. (last and " last" or "") .. '">' .. Forge.escape(p) .. "</span>"
		if i < #path then
			html[#html + 1] = '<span class="sep">&gt;</span>'
		end
	end
	header.inner_rml = '<div class="crumbs">' .. table.concat(html) .. '</div><div class="hline"></div>'
	header:SetClass("filled", true)
end

------------------------------------------------------------------------------------------
-- palette data
------------------------------------------------------------------------------------------

local function makeItem(node)
	if node.item then
		return node.item
	end
	local help = ""
	local properties = nil
	for _, child in ipairs(node.children) do
		if child.tag == "help" then
			help = child.text or ""
		elseif child.tag == "setter" then
			properties = properties or {}
			properties[child.attrs.target] = child.attrs.value
		end
	end
	node.item = {
		type = node.attrs.type,
		name = node.attrs.name,
		tagIndex = node.attrs.tagindex,
		help = help,
		properties = properties,
		maxAllowed = node.attrs.max_allowed,
	}
	return node.item
end

local function buildItemsTree(data)
	local root = Forge.node("root")
	local categories = data.paletteCategories or {}
	local descriptions = data.descriptions or {}
	local categoryNodes = {}
	local itemsByCategory = {}

	local function description(index)
		if index and index >= 0 and index < #descriptions then
			return descriptions[index + 1]
		end
		return nil
	end

	for _, item in ipairs(data.palette or {}) do
		local list = itemsByCategory[item.categoryIndex]
		if not list then
			list = {}
			itemsByCategory[item.categoryIndex] = list
		end
		list[#list + 1] = item
	end

	for i, category in ipairs(categories) do
		local index = i - 1
		local node = Forge.node("category", { name = category.name, help = description(category.descriptionIndex) })
		categoryNodes[index] = node
		for _, entry in ipairs(itemsByCategory[index] or {}) do
			local itemNode = Forge.node("item", {
				name = entry.name,
				tagindex = entry.tagIndex,
				type = Forge.paletteTypeName(entry.type),
				max_allowed = (entry.maxAllowed or 0) > 0 and entry.maxAllowed or nil,
			})
			for _, setter in ipairs(entry.setters or {}) do
				local value = tonumber(setter.value) or 0
				if setter.type == "int" then value = math.tointeger(value) or math.floor(value) end
				Forge.append(itemNode, Forge.node("setter", {
					target = Forge.OBJECT_PROPERTY_TARGET_NAMES[(setter.target or -1) + 1],
					type = setter.type,
					value = value,
					hidden = setter.hidden,
				}))
			end
			local help = description(entry.descriptionIndex)
			if help then
				local helpNode = Forge.node("help")
				helpNode.text = help
				Forge.append(itemNode, helpNode)
			end
			Forge.append(node, itemNode)
		end
	end

	for i, category in ipairs(categories) do
		local index = i - 1
		if (category.parentCategoryIndex or -1) >= 0 then
			local parent = categoryNodes[category.parentCategoryIndex]
			if parent then
				Forge.append(parent, categoryNodes[index])
			end
		else
			Forge.append(root, categoryNodes[index])
		end
	end

	Forge.append(root, Forge.node("category", { id = "prefabs", name = "PREFABS" }))
	Forge.append(root, Forge.node("category", { id = "recent", name = "RECENTLY USED" }))
	Forge.append(root, Forge.node("category", { id = "map_options", name = "MAP OPTIONS" }))
	return root
end

-- Fuse stand-in over name and type: lower score is better, nil = no match
local function matchScore(text, query)
	text = string.lower(text or "")
	if text == "" then return nil end
	local position = string.find(text, query, 1, true)
	if position then
		return (position - 1) * 0.01 + (#text - #query) * 0.001
	end
	local score, at = 0.5, 1
	for i = 1, #query do
		local found = string.find(text, query:sub(i, i), at, true)
		if not found then return nil end
		score = score + (found - at) * 0.02
		at = found + 1
	end
	return score
end

local function makeItemDatasource()
	local itemsFlat = {}

	local function flatten(root)
		local result, pathStack = {}, {}
		local function visit(node)
			for _, child in ipairs(node.children) do
				if child.tag == "item" then
					local item = makeItem(child)
					local path = {}
					for i, p in ipairs(pathStack) do path[i] = p end
					item.path = path
					result[#result + 1] = item
				elseif child.tag == "category" then
					pathStack[#pathStack + 1] = child.attrs.name
					visit(child)
					pathStack[#pathStack] = nil
				end
			end
		end
		visit(root)
		return result
	end

	return {
		search = function(query)
			query = string.lower(query or "")
			if query == "" then return {} end
			local scored = {}
			for _, item in ipairs(itemsFlat) do
				local a = matchScore(item.name, query)
				local b = matchScore(item.type, query)
				local score = a and b and math.min(a, b + 0.3) or a or (b and b + 0.3)
				if score and score <= 0.9 then
					scored[#scored + 1] = { item = item, score = score }
				end
			end
			table.sort(scored, function(x, y) return x.score < y.score end)
			local results = {}
			for i, entry in ipairs(scored) do
				results[i] = entry.item
			end
			return results
		end,
		fetch = function(callback)
			dew.callMethod("forgePalette"):next(function(r)
				local root = buildItemsTree(json.decode(r))
				itemsFlat = flatten(root)
				if callback then callback(nil, root) end
			end):catch(function(err)
				console.error("forgePalette failed: " .. tostring(err))
			end)
		end,
	}
end

local function spawnItem(item)
	local known = false
	for _, h in ipairs(itemHistory) do
		if h == item then known = true break end
	end
	if not known then
		table.insert(itemHistory, 1, item)
	end
	if item.properties then
		dew.callMethod("forgeaction", { type = 2, data = item.properties })
	end
	dew.command(string.format("Forge.SpawnItem 0x%x", item.tagIndex))
	hide()
end

------------------------------------------------------------------------------------------
-- screens
------------------------------------------------------------------------------------------

local function makeMainScreen(manager)
	local screenElement = q(".main-screen")
	local categoryTreeElement = q(".category-tree", screenElement)
	local infoBoxElement = q(".window-info-box", screenElement)
	local legendElement = q(".main-legend", footerElement)
	local categoryTree = Forge.makeTreeList(categoryTreeElement)
	local active = false
	local path = {}
	local itemsLoaded = false

	categoryTree.on("change", function(e)
		setInfoText(infoBoxElement, e.path.attrs.help)
	end)
	categoryTree.on("push", function(node)
		if node.attrs.name then
			path[#path + 1] = node.attrs.name
		end
		renderBreadcrumbs(screenElement, path)
	end)
	categoryTree.on("pop", function()
		path[#path] = nil
		renderBreadcrumbs(screenElement, path)
	end)
	categoryTree.on("select", function(e)
		local node = e.path
		if not node or Forge.hasCategoryDescendant(node) then
			return
		end
		local id = node.attrs.id
		if id == "prefabs" then
			manager.push("prefabs")
		elseif id == "recent" then
			manager.push("items", { path = { "RECENTLY USED ITEMS" }, items = itemHistory, shouldDisplayType = true })
		elseif id == "map_options" then
			dew.hide()
			dew.command("Forge.MapOptions")
		else
			local items = {}
			for _, itemNode in ipairs(Forge.descendants(node, "item")) do
				items[#items + 1] = makeItem(itemNode)
			end
			local itemPath = {}
			for i, p in ipairs(path) do itemPath[i] = p end
			itemPath[#itemPath + 1] = node.attrs.name
			manager.push("items", { path = itemPath, items = items })
		end
	end)

	document:AddEventListener("keydown", function(event)
		if not active then return end
		local char = keyChar(tonumber(event.parameters.key_identifier) or -1)
		if char then
			manager.push("search", { initialQuery = char })
		end
	end)

	dew.on("forge_init", function()
		itemsLoaded = false
		manager.popAll(false)
	end)

	local function transitionIn()
		categoryTree.focus()
		screenElement:SetClass("active", true)
		legendElement:SetClass("hidden", false)
	end

	legendElement:AddEventListener("mousedown", function(event)
		if not active then return end
		local rel = relOf(event.target_element)
		if rel == "back" then
			if categoryTree.atRoot() then
				hide()
				dew.playSound("b_button")
			else
				categoryTree.pop()
			end
		elseif rel == "hide" then
			dew.playSound("b_button")
			hide()
		elseif rel == "tool_settings" then
			dew.playSound("a_button")
			manager.push("tool_settings")
		else
			return
		end
		event:StopPropagation()
	end)

	return {
		activate = function()
			setTitle("Object Browser")
			active = true
			if not itemsLoaded then
				itemDatasource.fetch(function(_, root)
					itemsLoaded = true
					categoryTree.setSource(root)
					categoryTree.gotoRoot()
					path = {}
					renderBreadcrumbs(screenElement, path)
					transitionIn()
				end)
			else
				transitionIn()
			end
		end,
		deactivate = function()
			active = false
			legendElement:SetClass("hidden", true)
			screenElement:SetClass("active", false)
			categoryTree.blur()
		end,
		onAction = function(e)
			if not active then return end
			local action = e.action
			if action == dew.input.Actions.X then
				hide()
				dew.playSound("b_button")
			elseif action == dew.input.Actions.B then
				if categoryTree.atRoot() then
					hide()
				end
			elseif action == dew.input.Actions.Y then
				manager.push("tool_settings")
				dew.playSound("x_button")
			end
		end,
	}
end

local function makeItemsScreen(manager)
	local screenElement = q(".items-screen")
	local itemListElement = q(".item-list", screenElement)
	local legendElement = q(".list-legend", footerElement)
	local infoBoxElement = q(".window-info-box", screenElement)
	local itemList = Forge.makeListWidget(itemListElement, {
		itemSelector = ".item",
		hoverSelection = true,
		hoverClass = "selected",
		wrapAround = true,
	})
	local items = {}
	local active = false
	local shouldDisplayType = false

	local function renderItemList(list)
		local html = {}
		for _, item in ipairs(list) do
			local entry = budget[item.tagIndex] or { max_allowed = 255, count_on_map = 0 }
			local maxAllowed = item.maxAllowed or entry.max_allowed or 255
			local remaining = maxAllowed - (entry.count_on_map or 0)
			html[#html + 1] = '<div class="item">'
				.. (shouldDisplayType and ('<span class="type">' .. Forge.escape(item.type) .. "</span>") or "")
				.. '<span class="title">' .. Forge.escape(item.name) .. '</span><span class="quota">' .. tostring(remaining) .. "</span></div>"
		end
		itemListElement.inner_rml = table.concat(html)
	end

	itemList.on("select", function(e)
		local item = items[e.index + 1]
		if item then spawnItem(item) end
	end)
	itemList.on("selectionChange", function(e)
		local item = items[e.index + 1]
		setInfoText(infoBoxElement, item and item.help or "")
	end)

	dew.on("show", function()
		if active then
			-- wait a tick: the budget is updated by the root show handler
			dew.setTimeout(function()
				local selected = itemList.getSelected()
				if not selected then return end
				renderItemList(items)
				itemList.refresh()
				itemList.setSelected(selected.index)
			end, 1)
		end
	end)

	document:AddEventListener("keydown", function(event)
		if not active then return end
		local char = keyChar(tonumber(event.parameters.key_identifier) or -1)
		if char then
			manager.push("search", { initialQuery = char })
		end
	end)

	legendElement:AddEventListener("mousedown", function(event)
		if not active then return end
		local rel = relOf(event.target_element)
		if rel == "back" then
			dew.playSound("b_button")
			manager.pop()
		elseif rel == "hide" then
			dew.playSound("b_button")
			hide()
		else
			return
		end
		event:StopPropagation()
	end)

	return {
		activate = function(props)
			active = true
			legendElement:SetClass("hidden", false)
			screenElement:SetClass("active", true)
			itemList.focus()
			if props and props.items then
				shouldDisplayType = props.shouldDisplayType == true
				items = props.items
				renderItemList(items)
				itemList.refresh()
				itemList.setSelected(0)
				renderBreadcrumbs(screenElement, props.path or {})
			end
		end,
		deactivate = function()
			active = false
			legendElement:SetClass("hidden", true)
			screenElement:SetClass("active", false)
			itemList.blur()
		end,
		onAction = function(e)
			if not active then return end
			if e.action == dew.input.Actions.X then
				hide()
				dew.playSound("b_button")
			elseif e.action == dew.input.Actions.B then
				setInfoText(infoBoxElement, "")
				dew.playSound("b_button")
				manager.pop()
			end
		end,
	}
end

local function makeSearchScreen(manager)
	local screenElement = q(".search-screen")
	local resultListElement = q(".search-results", screenElement)
	local inputElement = q(".search-textbox", screenElement)
	local placeholder = q(".search-placeholder", screenElement)
	local resultList = Forge.makeListWidget(resultListElement, {
		itemSelector = ".item",
		hoverSelection = true,
		hoverClass = "selected",
		wrapAround = true,
	})
	local results = {}
	local active = false
	local inputFocused = false
	local written = ""

	local function renderSearchResults(list)
		local html = {}
		for _, result in ipairs(list) do
			html[#html + 1] = '<div class="item"><span class="type">' .. Forge.escape(result.type)
				.. '</span><span class="title">' .. Forge.escape(result.name) .. "</span></div>"
		end
		resultListElement.inner_rml = table.concat(html)
		resultList.refresh()
	end

	local function runSearch()
		local value = inputElement:GetAttribute("value") or ""
		placeholder:SetClass("hidden", value ~= "")
		local all = itemDatasource.search(value)
		results = {}
		for i = 1, math.min(#all, 100) do results[i] = all[i] end
		renderSearchResults(results)
	end

	local function setInput(value)
		inputElement:SetAttribute("value", value)
		written = inputElement:GetAttribute("value") or ""
		dew_core.setSelectionRange(inputElement, #written, #written)
		runSearch()
	end

	resultList.on("select", function(e)
		local item = results[e.index + 1]
		if item then spawnItem(item) end
	end)

	resultListElement:AddEventListener("mousemove", function()
		if active and inputFocused then
			inputElement:Blur()
			resultList.focus()
		end
	end)

	inputElement:AddEventListener("change", function()
		local value = inputElement:GetAttribute("value") or ""
		if value == written then return end
		written = value
		runSearch()
	end)

	inputElement:AddEventListener("focus", function()
		inputFocused = true
		resultList.setSelected(-1)
		resultList.blur()
	end)
	inputElement:AddEventListener("blur", function()
		inputFocused = false
	end)

	document:AddEventListener("keydown", function(event)
		if not active or not resultList.hasFocus() then return end
		if keyChar(tonumber(event.parameters.key_identifier) or -1) then
			inputElement:Focus()
		end
	end)

	dew.input.on("scroll", function(_, axis, direction)
		if not active then return end
		if axis == 0 and direction == 1 and inputFocused then
			inputElement:Blur()
			resultList.focus()
			if resultList.setSelected(0) ~= -1 then
				dew.playSound("vertical_navigation")
			end
		end
	end)

	return {
		activate = function(props)
			q(".list-legend", footerElement):SetClass("hidden", false)
			active = true
			screenElement:SetClass("active", true)
			if props and props.initialQuery then
				inputElement:Focus()
				setInput(props.initialQuery)
				resultList.refresh()
			else
				resultList.refresh()
				resultList.focus()
			end
		end,
		deactivate = function()
			q(".list-legend", footerElement):SetClass("hidden", true)
			active = false
			screenElement:SetClass("active", false)
			resultList.blur()
			inputElement:Blur()
			setInput("")
		end,
		onAction = function(e)
			if not active then return end
			if e.action == dew.input.Actions.X then
				if not inputFocused then
					hide()
					dew.playSound("b_button")
				end
			elseif e.action == dew.input.Actions.B then
				dew.playSound("b_button")
				manager.pop()
			end
		end,
		state = function() return { focused = inputFocused, results = #results } end,
	}
end

local function makePrefabsScreen(manager)
	local screenElement = q(".prefabs-screen")
	local prefabListElement = q(".prefab-list", screenElement)
	local legendElement = q(".prefab-legend", footerElement)
	local prefabList = Forge.makeListWidget(prefabListElement, {
		wrapAround = true,
		hoverClass = "selected",
		hoverSelection = true,
	})
	local prefabs = nil
	local lastSelectedIndex = -1
	local active = false

	local function renderPrefabList()
		local html = {}
		for _, prefab in ipairs(prefabs) do
			html[#html + 1] = '<div class="item"><div class="left-side"><span class="item-name">' .. Forge.escape(prefab.name)
				.. '</span><span class="item-author">' .. Forge.escape(prefab.author)
				.. '</span></div><div class="right-side"><span class="item-object-count">' .. tostring(prefab.object_count)
				.. "</span></div></div>"
		end
		prefabListElement.inner_rml = table.concat(html)
	end

	local function fetchPrefabs(callback)
		if prefabs then return callback(prefabs) end
		dew.command("Forge.DumpPrefabs"):next(function(result)
			prefabs = json.decode(result) or {}
			callback(prefabs)
		end)
	end

	local function confirmDelete(index)
		local prefab = prefabs[index + 1]
		prefabs = nil
		lastSelectedIndex = index
		dew.command('Forge.DeletePrefab "' .. prefab.filename .. '"'):next(function()
			showToast('Prefab "' .. prefab.name .. '" deleted')
		end):catch(function(response)
			showToast(type(response) == "table" and response.message or tostring(response))
		end)
	end

	local function handleDelete()
		local selected = prefabList.getSelected()
		if not selected or not prefabs then return end
		local prefab = prefabs[selected.index + 1]
		manager.push("modal", {
			noHide = true,
			type = 0,
			title = "Confirm Delete",
			body = "You are about to delete prefab &quot;" .. Forge.escape(prefab.name) .. "&quot;",
			onAction = function(e)
				if e.action == dew.input.Actions.A then
					confirmDelete(selected.index)
					dew.playSound("a_button")
					manager.pop()
				elseif e.action == dew.input.Actions.B then
					dew.playSound("b_button")
					manager.pop()
				end
			end,
		})
		dew.playSound("x_button")
	end

	prefabList.on("select", function(e)
		local prefab = prefabs and prefabs[e.index + 1]
		if prefab then
			dew.command('Forge.LoadPrefab "' .. prefab.filename .. '"'):next(hide)
		end
	end)

	legendElement:AddEventListener("mousedown", function(event)
		if not active then return end
		local rel = relOf(event.target_element)
		if rel == "back" then
			dew.playSound("b_button")
			manager.pop()
		elseif rel == "hide" then
			dew.playSound("b_button")
			hide()
		elseif rel == "delete" then
			handleDelete()
		end
		event:StopPropagation()
	end)

	return {
		activate = function(props)
			active = true
			setTitle("Prefabs")
			if props and not props.noHide then
				prefabs = nil
			end
			if not prefabs then
				fetchPrefabs(function()
					renderPrefabList()
					screenElement:SetClass("active", true)
					prefabList.refresh()
					prefabList.focus()
					prefabList.setSelected(lastSelectedIndex == -1 and 0 or lastSelectedIndex)
					lastSelectedIndex = -1
				end)
			else
				screenElement:SetClass("active", true)
				prefabList.focus()
			end
			legendElement:SetClass("hidden", false)
		end,
		deactivate = function(props)
			active = false
			if not (props and props.noHide) then
				screenElement:SetClass("active", false)
			end
			prefabList.blur()
			legendElement:SetClass("hidden", true)
		end,
		onAction = function(e)
			if e.action == dew.input.Actions.X then
				hide()
				dew.playSound("b_button")
			elseif e.action == dew.input.Actions.B then
				dew.playSound("b_button")
				manager.pop()
			elseif e.action == dew.input.Actions.Y then
				handleDelete()
			end
		end,
	}
end

local function makeModalScreen()
	local screenElement = q(".modal-screen", containerElement)
	local modalTitle = q(".modal-title", screenElement)
	local modalBody = q(".modal-body", screenElement)
	local legendElement = q(".confirm-legend", containerElement)
	local onAction = nil
	local active = false

	legendElement:AddEventListener("mousedown", function(event)
		if not active or not onAction then return end
		local rel = relOf(event.target_element)
		if rel == "confirm" then
			onAction({ inputType = "legend", action = dew.input.Actions.A })
		elseif rel == "cancel" then
			onAction({ inputType = "legend", action = dew.input.Actions.B })
		end
		event:StopPropagation()
	end)

	return {
		activate = function(props)
			active = true
			modalTitle.inner_rml = Forge.escape(props.title)
			modalBody.inner_rml = props.body
			onAction = props.onAction
			screenElement:SetClass("active", true)
			legendElement:SetClass("hidden", false)
		end,
		deactivate = function()
			active = false
			screenElement:SetClass("active", false)
			legendElement:SetClass("hidden", true)
		end,
		onAction = function(action)
			if onAction then onAction(action) end
		end,
	}
end

local function makeToolSettingsScreen(manager)
	local toggleOptions = { { label = "Enabled", value = 1 }, { label = "Disabled", value = 0 } }
	local screenElement = q(".tool-settings-screen", containerElement)
	local legendElement = q(".tool-settings-legend", containerElement)
	local infoBoxElement = q(".window-info-box", screenElement)
	local propertyGrid = Forge.makePropertyGrid(q(".property-grid", screenElement))
	local saving = false
	local active = false
	local data = {}

	local preload = {
		["Forge.MonitorSpeed"] = true, ["Forge.MonitorNoclip"] = true, ["Forge.SelectionRenderer"] = true,
		["Forge.ShowInvisibles"] = true, ["Forge.GrabDistance"] = true, ["Forge.RotationSensitivity"] = true,
		["Forge.RotationSnap"] = true, ["Forge.Magnets"] = true, ["Forge.MagnetsStrength"] = true,
		["Forge.CloneDepth"] = true, ["Forge.CloneMultiplier"] = true, ["Forge.ShowWorldBounds"] = true,
	}

	local function makeDewProperty(variable, label, type, meta, description)
		return {
			label = label,
			type = type,
			getValue = function() return tonumber(data[variable]) or 0 end,
			setValue = function(value)
				data[variable] = value
				dew.command(variable .. " " .. tostring(value))
			end,
			meta = meta,
			description = description,
		}
	end

	local model = propertyGrid.createModel()
	model.group("Monitor", function(m)
		m.add(makeDewProperty("Forge.MonitorSpeed", "Monitor Speed", "spinner", {
			{ label = "Z-Fight Fixer", value = 0 }, { label = "Slower", value = 1 }, { label = "Slow", value = 2 },
			{ label = "Normal", value = 3 }, { label = "Fast", value = 4 }, { label = "Faster", value = 5 },
			{ label = "Fastest", value = 6 },
		}))
		m.add(makeDewProperty("Forge.MonitorNoclip", "Noclip", "spinner", {
			{ label = "Disabled", value = 0 }, { label = "Enabled", value = 1 },
		}))
		m.add(makeDewProperty("Forge.GrabDistance", "Grab Distance", "range", { min = 1, max = 60, step = 0.1 }))
		m.add(makeDewProperty("Forge.RotationSensitivity", "Rotation Sensitvity", "range", { min = 0, max = 4, step = 0.05 }))
		m.add(makeDewProperty("Forge.RotationSnap", "Rotation Snap", "spinner", {
			{ label = "Off", value = 0 }, { label = "3", value = 1 }, { label = "5", value = 2 }, { label = "15", value = 3 },
			{ label = "30", value = 4 }, { label = "45", value = 5 }, { label = "90", value = 6 },
		}))
		m.add(makeDewProperty("Forge.SelectionRenderer", "Selection Renderer", "spinner", {
			{ label = "Default", value = 0 }, { label = "Box", value = 1 },
		}))
		m.add(makeDewProperty("Forge.ShowInvisibles", "Show Invisibles", "spinner", toggleOptions))
		m.add(makeDewProperty("Forge.ShowWorldBounds", "World Bounds", "spinner", {
			{ label = "Hidden", value = 0 }, { label = "Visible", value = 1 },
		}))
	end)
	model.group("Magnets", function(m)
		m.add(makeDewProperty("Forge.Magnets", "Magnets", "spinner", toggleOptions))
		m.add(makeDewProperty("Forge.MagnetsStrength", "Magnet Strength", "range", { min = 0, max = 5, step = 0.01 }))
	end)
	model.group("Duplicating", function(m)
		m.add(makeDewProperty("Forge.CloneMultiplier", "Multiplier", "range", { min = 1, max = 50, step = 1, isInteger = true }))
		m.add(makeDewProperty("Forge.CloneDepth", "Depth", "range", { min = 0, max = 5, step = 0.01 }))
	end)
	propertyGrid.setModel(model)

	propertyGrid.on("selectionChange", function(item)
		setInfoText(infoBoxElement, item.model.description)
	end)

	local function saveSettings()
		if saving then return end
		saving = true
		dew.command("WriteConfig"):next(function()
			showToast("Settings Saved")
		end):catch(function(response)
			showToast(type(response) == "table" and response.message or tostring(response))
		end):next(function()
			dew.setTimeout(function() saving = false end, 3500)
		end)
	end

	legendElement:AddEventListener("mousedown", function(event)
		if not active then return end
		local rel = relOf(event.target_element)
		if rel == "back" then
			dew.playSound("b_button")
			manager.pop()
		elseif rel == "hide" then
			dew.playSound("b_button")
			hide()
		elseif rel == "save_settings" then
			dew.playSound("a_button")
			saveSettings()
		else
			return
		end
		event:StopPropagation()
	end)

	return {
		activate = function()
			active = true
			setTitle("Tool Settings")
			dew.getCommands():next(function(commands)
				for _, cmd in ipairs(commands or {}) do
					if preload[cmd.name] then
						data[cmd.name] = cmd.value
					end
				end
				screenElement:SetClass("active", true)
				legendElement:SetClass("hidden", false)
				propertyGrid.refresh()
			end):catch(function(err)
				console.error(tostring(err))
			end)
			propertyGrid.focus()
		end,
		deactivate = function()
			active = false
			screenElement:SetClass("active", false)
			legendElement:SetClass("hidden", true)
			propertyGrid.blur()
		end,
		onAction = function(e)
			if e.action == dew.input.Actions.B then
				manager.pop()
				dew.playSound("b_button")
			elseif e.action == dew.input.Actions.X then
				hide()
				dew.playSound("b_button")
			elseif e.action == dew.input.Actions.Y then
				saveSettings()
				dew.playSound("a_button")
			end
		end,
	}
end

------------------------------------------------------------------------------------------

local screens

function init()
	containerElement = document:GetElementById("container")
	footerElement = q(".window-footer", containerElement)
	titleElement = q(".window-title", containerElement)
	objectQuotaElement = q(".object-quota", containerElement)

	screenManager = Forge.makeScreenManager()
	itemDatasource = makeItemDatasource()

	screens = {
		main = makeMainScreen(screenManager),
		items = makeItemsScreen(screenManager),
		search = makeSearchScreen(screenManager),
		prefabs = makePrefabsScreen(screenManager),
		modal = makeModalScreen(screenManager),
		tool_settings = makeToolSettingsScreen(screenManager),
	}
	screenManager.setModel(screens)

	document:AddEventListener("keyup", function(event)
		if tonumber(event.parameters.key_identifier) == KI_SNAPSHOT then
			dew.command("Game.TakeScreenshot")
		end
	end)

	containerElement:AddEventListener("mousedown", function(event)
		if event.target_element.id == "container" then
			event:StopPropagation()
			dew.playSound("b_button")
			hide()
		end
	end)

	screenManager.push("main")

	dew.on("show", function(e)
		updateObjectQuotaText()
		hidden = false
		budget = {}
		local data = e.data or {}
		for _, item in ipairs(data.budget or {}) do
			local tagIndex = tonumber(item.tagindex)
			if tagIndex then budget[tagIndex] = item end
		end
		dew.command("Settings.Gamepad"):next(function(response)
			containerElement:SetClass("using-controller", tonumber(response) == 1)
		end)
	end)
end

-- debug helper for the harness: current screen name and search state
function forgeCreationState()
	local current = screenManager.currentScreen()
	return {
		screen = current and current.name or "",
		count = screenManager.count(),
		search = screens.search.state(),
	}
end
