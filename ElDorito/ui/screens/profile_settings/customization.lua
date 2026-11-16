-- Port of screens/profile_settings/customization.js
--
-- The jQuery page kept its state in radio buttons and classes; here each list of tiles is a
-- "form" model ({ kind, items, chosen, custom }) rendered into its element.

local activePage = ""   -- "#page1", or "#page1 #races" while a side list is open
local itemNumber = -1
local tabIndex = 0
local hasGP = false
local axisThreshold = 0.5
local emblemToggle = 1
local emblemNeedsToApply = false
local resetCharacters = false
local subCamera = false
local subForm = ""
local userCanRotate = false
local firstRun = true
local cachedEmblemEndpoint = ""
local bipedRotate = 0
local showing = false
local isVisible = false
local exiting = false
local needSetEmblem = false
local controllerSetEmblem = false
local lastEmblem = ""
local mapName = "mainmenu"

local KI_SNAPSHOT, KI_OEM_3, KI_OEM_8 = 97, 44, 49

local h3ColorArray = {
	{ "Steel", "#282828" }, { "Silver", "#7C7C7C" }, { "White", "#C3C3C3" }, { "Red", "#620B0B" },
	{ "Mauve", "#BD2B2B" }, { "Salmon", "#E24444" }, { "Orange", "#BC4D00" }, { "Coral", "#F4791F" },
	{ "Peach", "#FFA362" }, { "Gold", "#A77708" }, { "Yellow", "#DD9A08" }, { "Pale", "#FFBC3B" },
	{ "Sage", "#1F3602" }, { "Green", "#546E26" }, { "Olive", "#B3E164" }, { "Teal", "#0A3B3F" },
	{ "Aqua", "#178C95" }, { "Cyan", "#54DDDB" }, { "Blue", "#0B2156" }, { "Cobalt", "#1D4BBC" },
	{ "Sapphire", "#5D85EB" }, { "Violet", "#1D1052" }, { "Orchid", "#5438CF" }, { "Lavender", "#A18CFF" },
	{ "Crimson", "#460014" }, { "Rubine", "#AF0E46" }, { "Pink", "#FF4D8A" }, { "Brown", "#1C0D02" },
	{ "Tan", "#774D31" }, { "Khaki", "#C69069" },
}

-- the tiles show a lighter shade of each colour (color-picker.css input[value=...] rules)
local TILE_COLORS = {
	["#282828"] = "#585758", ["#7C7C7C"] = "#A7A6A7", ["#C3C3C3"] = "#D7D8D7", ["#620B0B"] = "#93353D",
	["#BD2B2B"] = "#D26163", ["#E24444"] = "#EA7D7D", ["#BC4D00"] = "#D28800", ["#F4791F"] = "#F7A34B",
	["#FFA362"] = "#FBBE93", ["#A77708"] = "#C2A32B", ["#DD9A08"] = "#EAB62B", ["#FFBC3B"] = "#FBD375",
	["#1F3602"] = "#4B702B", ["#546E26"] = "#8C9C58", ["#B3E164"] = "#CDEA93", ["#0A3B3F"] = "#2B7475",
	["#178C95"] = "#4BAFB2", ["#54DDDB"] = "#8CE8E5", ["#0B2156"] = "#3D518C", ["#1D4BBC"] = "#4B84D2",
	["#5D85EB"] = "#93A9F3", ["#1D1052"] = "#4B3D8C", ["#5438CF"] = "#8C70E1", ["#A18CFF"] = "#BDACFB",
	["#460014"] = "#7D003D", ["#AF0E46"] = "#C83D7D", ["#FF4D8A"] = "#FB88AD", ["#1C0D02"] = "#4B352B",
	["#774D31"] = "#A1886C", ["#C69069"] = "#D7AF9B",
}

local settingsToLoad = {
	{ "playerName", "Player.Name" },
	{ "serviceTag", "Player.ServiceTag" },
	{ "races", "Player.PreferredCharacter" },
	{ "gender", "Player.Gender" },
	{ "colorsPrimary", "Player.Customization.Color primary" },
	{ "colorsSecondary", "Player.Customization.Color secondary" },
	{ "colorsTertiary", "Player.Customization.Color tertiary" },
	{ "colorsQuaternary", "Player.Customization.Color quaternary" },
	{ "colorsQuinary", "Player.Customization.Color quinary" },
}

local genderList = {
	{ "Male", "male", "State your gender. This will not be displayed to other players, but combat effects will be tailored to your gender.", "gender" },
	{ "Female", "female", "State your gender. This will not be displayed to other players, but combat effects will be tailored to your gender.", "gender" },
}

local nameplateList = {}
for i, name in ipairs({ "None", "Seventh Column", "Pro", "Bungie", "Mark of Shame", "Blue Team", "Red Team", "Halo CE",
	"Halo 2", "Halo 3", "ODST", "Reach", "Marathon", "Forerunner", "UNSC", "Covenant", "ONI", "Anvil", "Virgil", "Forge",
	"Legendary", "Eldewrito" }) do
	nameplateList[i] = { name, tostring(i - 1), "dew://assets/emblems/nameplate/" .. (i - 1) .. ".png" }
end

local EMBLEM_COLOR_FORMS = { "colorsEmblemPrimary", "colorsEmblemSecondary", "colorsEmblemImage" }
local ARMOR_COLOR_FORMS = { "colorsPrimary", "colorsSecondary", "colorsTertiary", "colorsQuaternary", "colorsQuinary" }

local repName = ""
local characters = {}
local characterColors = {}   -- form id -> description
local regionList = {}        -- { formId, permutations, regionType }
local defaultColorList = {}  -- form id -> default colour
local colorPicker
local colorLocation

local function el(id) return document:GetElementById(id) end
local function decode(text)
	local ok, value = pcall(json.decode, text)
	if ok then return value end
end

local function commandFor(formId)
	for _, entry in ipairs(settingsToLoad) do
		if entry[1] == formId then return entry[2] end
	end
end

------------------------------------------------------------------------------------------
-- forms

local forms = {}

local function newForm(id, kind)
	forms[id] = forms[id] or { kind = kind, items = {}, chosen = nil, custom = "#FFFFFF" }
	forms[id].kind = kind
	return forms[id]
end

local wireForm -- forward

local function renderForm(id)
	local form = forms[id]
	local element = el(id)
	if not form or not element then return end
	local parts = {}
	if form.kind == "color" then
		parts[#parts + 1] = string.format('<span class="tile customColor" data-index="0"><span class="caption">Custom Color</span><span class="hex">%s</span></span>',
			dew.escape(form.custom))
		for i, item in ipairs(form.items) do
			parts[#parts + 1] = string.format('<span class="tile color%s" data-index="%d" style="background-color: %s;"></span>',
				i % 3 == 0 and " third" or "", i, TILE_COLORS[item[2]:upper()] or item[2])
		end
	else
		for i, item in ipairs(form.items) do
			parts[#parts + 1] = string.format('<span class="tile" data-index="%d" id="%s_%s"><label>%s</label><img%s/></span>',
				i, dew.escape(id), dew.escape(tostring(item[2])), dew.escape(item[1]),
				(item.img and item.img ~= "") and (' src="' .. dew.escape(item.img) .. '"') or "")
		end
	end
	element.inner_rml = table.concat(parts)
	for _, tile in ipairs(element:QuerySelectorAll("span.tile")) do
		local index = tonumber(tile:GetAttribute("data-index"))
		tile:SetClass("chosenElement", form.chosen == index)
	end
	wireForm(id)
end

local function setChosenClass(id)
	local form, element = forms[id], el(id)
	if not form or not element then return end
	for _, tile in ipairs(element:QuerySelectorAll("span.tile")) do
		tile:SetClass("chosenElement", tonumber(tile:GetAttribute("data-index")) == form.chosen)
	end
	local hex = element:QuerySelector(".customColor .hex")
	if hex then hex.inner_rml = dew.escape(form.custom) end
end

-- setRadioList(ElementID, ArrayVar, radioType, shouldReset, path)
local function setRadioList(id, list, kind, path)
	local form = newForm(id, kind)
	form.items = {}
	for i, entry in ipairs(list) do
		local item = { entry[1], tostring(entry[2]), entry[3], entry[4] }
		if kind == "emblem" then
			item.img = entry[3]
			item[3] = nil
		end
		form.items[i] = item
	end
	renderForm(id)
	if kind == "armor" then
		for _, item in ipairs(form.items) do
			local imgId = id .. "_" .. item[2]
			dew.getAssetUrl(path .. "/" .. tostring(item[4]) .. "/" .. item[2], { pak = "mainmenu", fileTypes = { "jpg", "png" } }):next(function(url)
				if url ~= "" then
					item.img = url
					local tile = el(imgId)
					local img = tile and tile:QuerySelector("img")
					if img then img:SetAttribute("src", url) end
				end
			end)
		end
	end
end

local function indexOfValue(id, value)
	local form = forms[id]
	if not form then return nil end
	for i, item in ipairs(form.items) do
		if item[2]:upper() == tostring(value):upper() then return i end
	end
end

-- setDivValue / setItemValues: choose the tile with this value (armor: else "base"; colors: else custom)
local function setDivValue(id, value, isArmor)
	local form = forms[id]
	if not form then return end
	local index = indexOfValue(id, value)
	if index then
		form.chosen = index
	elseif isArmor then
		form.chosen = indexOfValue(id, "base")
	else
		form.chosen = 0
		if type(value) == "string" and value:match("^#%x%x%x%x%x%x$") then
			form.custom = value:upper()
		end
	end
	setChosenClass(id)
end

local function chosenValue(id)
	local form = forms[id]
	if not form or not form.chosen then return nil end
	if form.chosen == 0 then return form.custom end
	local item = form.items[form.chosen]
	return item and item[2]
end

------------------------------------------------------------------------------------------
-- info box / selection

local function pageId() return activePage:match("^#(page%d)") end

local function infoBox()
	local page = pageId()
	return page and el(page .. "Info")
end

local function setInfo(header, text)
	local box = infoBox()
	if not box then return end
	local h = box:QuerySelector(".infobox-header")
	local c = box:QuerySelector(".infobox-content")
	if h and header ~= nil then h.inner_rml = dew.escape(tostring(header)) end
	if c and text ~= nil then c.inner_rml = dew.escape(tostring(text)) end
end

local function showInfo(show)
	local box = infoBox()
	if box and box:IsClassSet("infoBox") then box:SetClass("hide", not show) end
end

-- the navigable items of activePage: button rows, or a side list's tiles
local function navItems(page)
	page = page or activePage
	local formId = page:match("#page%d #(%w+)")
	if formId then
		if formId == "colorPicker" or formId == "emblemColorPicker" then return {} end
		local element = el(formId)
		return element and element:QuerySelectorAll("span.tile") or {}
	end
	local list = el((pageId() or "page1") .. "Buttons")
	local items = {}
	if list then
		for _, item in ipairs(list:QuerySelectorAll(".baseNav")) do
			if dew_core.isDisplayed(item) then
				items[#items + 1] = item
			end
		end
	end
	return items
end

local function clearSelected(scope)
	for _, element in ipairs((scope or document):QuerySelectorAll(".selectedElement")) do
		element:SetClass("selectedElement", false)
	end
end

local function updateSelection(item, sound, move, direct)
	local page = direct or activePage
	if item > -1 then
		local items = navItems(page)
		local formId = page:match("#page%d #(%w+)")
		clearSelected(formId and el(formId) or el((pageId() or "page1") .. "Buttons"))
		local target = items[item + 1]
		if target then
			target:SetClass("selectedElement", true)
			if move then target:ScrollIntoView(false) end
		end
		if sound then dew.playSound("vertical_navigation") end
	end
end

------------------------------------------------------------------------------------------
-- biped / camera

local function adjustBiped(smoothRotation)
	return dew.command("Player.Armor.SetCustomizationUI " .. (smoothRotation and "exit_subcamera" or "")):next(function(response)
		if tostring(response):sub(1, 5) == "ERROR" then
			console.error("Customization failed to load with error: " .. tostring(response))
			return
		end
		local obj = decode(response) or {}
		bipedRotate = tonumber(obj.rotation) or 0
		userCanRotate = dew.truthy(obj.rotatable)
	end)
end

local function exitSubCamera()
	subCamera = false
	dew.command("Player.Armor.SetRegionCamera exit")
	adjustBiped(true)
end

local function enterSubCamera(region)
	dew.command("Player.Armor.SetRegionCamera " .. region, {}):next(function(response)
		local result = decode(response) or {}
		local prevStatus = subCamera
		subCamera = result.success == "true"
		if not subCamera and prevStatus then
			exitSubCamera()
		end
		if result.rotation ~= nil then
			bipedRotate = tonumber(result.rotation) or bipedRotate
		end
	end)
end

local function normalize(a)
	a = a % 360
	if a > 180 then a = a - 360 end
	return a
end

local function rotateBiped(direction)
	bipedRotate = bipedRotate + (direction == "right" and 2 or -2)
	dew.command("Player.Armor.SetUiModelRotation " .. bipedRotate)
end

------------------------------------------------------------------------------------------
-- emblem / nameplate

local function emblemColorPart(formId)
	local form = forms[formId]
	if not form then return 0 end
	if form.chosen == 0 then return (form.custom:gsub("#", "")) end
	return math.max((form.chosen or 1) - 1, 0)
end

local function emblemUrl()
	local icon = chosenValue("emblemIcon") or "0"
	local background = chosenValue("emblemBackgroundImage") or "0"
	return "?1=" .. emblemColorPart("colorsEmblemImage")
		.. "&2=" .. emblemColorPart("colorsEmblemSecondary")
		.. "&3=" .. emblemColorPart("colorsEmblemPrimary")
		.. "&fi=" .. icon
		.. "&bi=" .. background
		.. "&fl=" .. math.max(emblemToggle, 0)
end

local function setEmblemPreview(url)
	local function apply(src)
		for _, id in ipairs({ "emblemPreviewBig", "nameplateEmblem" }) do
			if el(id) then el(id):SetAttribute("src", src) end
		end
	end
	-- the endpoint is normally emblems://emblem, rendered by the game (AsyncTextures)
	if tostring(url):match("^emblems://") then
		apply(url)
		return
	end
	if not tostring(url):match("^https?://") then
		apply("dew://assets/emblems/generic.png")
		return
	end
	dew.fetchImage(url):next(apply, function() apply("dew://assets/emblems/generic.png") end)
end

local function tint(id, hexColor, amount, opacity)
	local hex = tostring(hexColor):gsub("#", "")
	local r = tonumber(hex:sub(1, 2), 16) or 255
	local g = tonumber(hex:sub(3, 4), 16) or 255
	local b = tonumber(hex:sub(5, 6), 16) or 255
	local function scale(c) return math.max(0, math.min(255, math.floor(c * amount + 0.5))) end
	if el(id) then
		el(id).style["image-color"] = string.format("rgba(%d, %d, %d, %d)", scale(r), scale(g), scale(b),
			math.max(0, math.min(255, math.floor(opacity * 255 + 0.5))))
	end
end

local function updateNameplateDisplay()
	dew.command("Player.name"):next(function(name)
		if el("playerNamePlateName") then el("playerNamePlateName").inner_rml = dew.escape(name) end
	end)
	dew.command("Player.NameplateColor"):next(function(hexColor)
		local index
		for i, color in ipairs(h3ColorArray) do
			if color[2]:upper() == tostring(hexColor):upper() then index = i end
		end
		local form = forms.colorsNameplate
		if form then
			if index then
				form.chosen = index
			else
				form.chosen = 0
				form.custom = tostring(hexColor):upper()
			end
			setChosenClass("colorsNameplate")
		end
		dew.command("Player.Nameplate"):next(function(nameplate)
			if el("nameplatePreview") then
				el("nameplatePreview"):SetAttribute("src", "dew://assets/emblems/nameplate/" .. tostring(nameplate) .. ".png")
			end
			tint("nameplatePreview", hexColor, 0.8, 0.45)
			tint("nameplateBase", hexColor, 1.8, 1.0)
		end)
	end)
end

local function updateEmblemDisplay(isLastEmblem)
	local url = emblemUrl()
	if isLastEmblem then lastEmblem = url end
	if lastEmblem == url then emblemNeedsToApply = false end
	if cachedEmblemEndpoint == "" then
		dew.getEndpoint("emblemgenerator"):next(function(endpointUrl)
			cachedEmblemEndpoint = endpointUrl
			setEmblemPreview(endpointUrl .. url)
		end)
	else
		setEmblemPreview(cachedEmblemEndpoint .. url)
	end
	dew.command("Player.Emblem " .. url)
	updateNameplateDisplay()
end

local function saveEmblem()
	dew.command('Player.Emblem "' .. emblemUrl() .. '"')
end

local function submitEmblemToStatsServer()
	emblemNeedsToApply = false
	local function part(formId)
		local value = emblemColorPart(formId)
		return value
	end
	dew.getEndpoint("changeemblem"):next(function(endpointUrl)
		dew.command("Player.Name"):next(function(name)
			dew.command("Player.ServiceTag"):next(function(serviceTag)
				dew.command("Player.PrintUID"):next(function(uid)
					dew.command("Player.PubKey"):next(function(publicKey)
						dew.command("Player.EncryptGMTTimestamp"):next(function(encrypted)
							local body = json.encode({
								playerName = name,
								serviceTag = serviceTag,
								uid = tostring(uid):sub(15),
								publicKey = publicKey,
								encryptedTimestamp = encrypted,
								emblem = {
									one = part("colorsEmblemImage"),
									two = part("colorsEmblemSecondary"),
									three = part("colorsEmblemPrimary"),
									fi = chosenValue("emblemIcon") or 0,
									bi = chosenValue("emblemBackgroundImage") or 0,
									fl = math.max(emblemToggle, 0),
								},
							})
							dew.http(endpointUrl, { method = "POST", body = body, headers = { ["Content-Type"] = "application/json" } })
								:catch(function() console.log("Emblem Submit Failed") end)
						end)
					end)
				end)
			end)
		end)
	end)
end

local function queryVariable(url, variable)
	for pair in (tostring(url):gsub("^%?", "") .. "&"):gmatch("([^&]*)&") do
		local key, value = pair:match("^([^=]*)=(.*)$")
		if key and key:gsub("[^%w%s]", "") == variable then return value end
	end
end

local function setupEmblems(initializeEmblemSettings, onFinish)
	local data = decode(dew.readFile("dew://screens/profile_settings/emblem_list.json") or "") or {}
	dew.command("Player.Emblem"):next(function(playerEmblem)
		if playerEmblem == "" then playerEmblem = "?1=0&2=0&3=0&fi=0&bi=0&fl=1" end
		if firstRun then
			setRadioList("emblemIcon", data.emblemList or {}, "emblem")
			setRadioList("emblemBackgroundImage", data.backgroundEmblems or {}, "emblem")
			setRadioList("nameplateImage", nameplateList, "emblem")
			firstRun = false
		end
		if initializeEmblemSettings then
			setDivValue("emblemIcon", tostring(tonumber(queryVariable(playerEmblem, "fi")) or 0), true)
			setDivValue("emblemBackgroundImage", tostring(tonumber(queryVariable(playerEmblem, "bi")) or 0), true)
			dew.command("Player.Nameplate"):next(function(index)
				setDivValue("nameplateImage", tostring(tonumber(index) or 0), true)
			end)
			for formId, key in pairs({ colorsEmblemPrimary = "3", colorsEmblemSecondary = "2", colorsEmblemImage = "1" }) do
				local value = queryVariable(playerEmblem, key) or "0"
				if #value == 6 then
					forms[formId].chosen = 0
					forms[formId].custom = "#" .. value:upper()
				else
					local color = h3ColorArray[(tonumber(value) or 0) + 1]
					forms[formId].chosen = color and ((tonumber(value) or 0) + 1) or 1
				end
				setChosenClass(formId)
			end
			emblemToggle = tonumber(queryVariable(playerEmblem, "fl")) or 1
		end
		if onFinish then onFinish() end
	end)
end

------------------------------------------------------------------------------------------
-- armor / colours

local function setArmorPrefs()
	for _, region in ipairs(regionList) do
		local value = chosenValue(region[1])
		if value then
			dew.command("Player.Customization.Armor " .. region[3] .. " " .. value)
		end
	end
	dew.command("Game.ScenarioScript character_updated") -- if the modder wants to do something when the armor is updated
end

local function getArmorPrefs()
	for _, region in ipairs(regionList) do
		dew.command("Player.Customization.Armor " .. region[3]):next(function(permutation)
			if permutation == "Failed to get character" or permutation == "" then permutation = "base" end
			setDivValue(region[1], permutation, true)
		end)
	end
end

local function getColorPrefs()
	for _, formId in ipairs(ARMOR_COLOR_FORMS) do
		local command = commandFor(formId)
		dew.command(command):next(function(color)
			if color == "Failed to get character" or color == "" then
				if defaultColorList[formId] then
					color = defaultColorList[formId]
					dew.command(command .. " " .. color)
				else
					color = "#000000"
				end
			end
			setDivValue(formId, color, false)
		end)
	end
end

local function setControlValues()
	dew.getCommands():next(function(commands)
		for _, command in ipairs(commands or {}) do
			for _, entry in ipairs(settingsToLoad) do
				if entry[2] == command.name and forms[entry[1]] then
					setDivValue(entry[1], tostring(command.value or ""), forms[entry[1]].kind == "armor")
				end
			end
		end
	end)
	getArmorPrefs()
	getColorPrefs()
end

local wireButtons -- forward

local function setRepresentation()
	dew.command("Player.Armor.ListCustomizationPermutation", {}):next(function(response)
		local obj = decode(response) or {}
		repName = tostring(obj.name or "")
		regionList = {}
		characterColors = {}
		defaultColorList = {}
		local colors = obj.colors or {}
		for _, slot in ipairs({ "primary", "secondary", "tertiary", "quaternary", "quinary" }) do
			local formId = "colors" .. slot:sub(1, 1):upper() .. slot:sub(2)
			if colors[slot .. "Default"] then defaultColorList[formId] = colors[slot .. "Default"] end
			local label = el(slot .. "Button")
			local row = label and label.parent_node
			if colors[slot] and colors[slot] ~= "" then
				characterColors[formId] = colors[slot .. "Desc"] or ""
				label.inner_rml = dew.escape(colors[slot])
				row.style.display = "block"
			elseif row then
				row.style.display = "none"
			end
		end

		-- close the colour page's side list
		for _, formId in ipairs(ARMOR_COLOR_FORMS) do el(formId):SetClass("hide", true) end
		el("colorPicker"):SetClass("hide", true)
		el("page2Info"):SetClass("hide", true)
		colorPicker, colorLocation = nil, nil

		if resetCharacters then
			characters = {}
			for _, character in ipairs(obj.characters or {}) do
				characters[#characters + 1] = { character.name, character.type, character.description, "races" }
			end
		end

		-- rebuild the per-region buttons and side lists
		local buttons = el("page1Buttons")
		for _, dynamic in ipairs(document:QuerySelectorAll(".dynamicItem")) do
			dynamic.parent_node:RemoveChild(dynamic)
		end
		local buttonRml, formRml = {}, {}
		for r, region in ipairs(obj.regions or {}) do
			local formId = "armor" .. (r - 1)
			buttonRml[#buttonRml + 1] = string.format('<div class="row dynamicItem"><div class="setting baseNav button-list" data-action="armor" data-arg="%s" data-region="%s"><label>%s</label></div></div>',
				formId, dew.escape(tostring(region.type)), dew.escape(tostring(region.name)))
			formRml[#formRml + 1] = string.format('<div class="armorForm form hide tile-button tile-large dynamicItem" id="%s"></div>', formId)
			local permutations = {}
			for _, entry in ipairs(region.permutations or {}) do
				permutations[#permutations + 1] = { entry.name, entry.permutation, entry.desc, region.type }
			end
			regionList[#regionList + 1] = { formId, permutations, region.type }
		end
		buttonRml[#buttonRml + 1] = '<div class="row dynamicItem"><div class="setting baseNav button-list" data-action="armor" data-arg="gender" data-region="gender"><label>Gender</label></div></div>'
		buttons.inner_rml = buttons.inner_rml .. table.concat(buttonRml)
		local side = el("armorSideList")
		side.inner_rml = table.concat(formRml)
			.. '<div class="armorForm form hide tile-button tile-large" id="gender"></div>'
			.. '<div class="armorForm form hide tile-button tile-large" id="races"></div>'

		setRadioList("gender", genderList, "armor", "assets/armor")
		setRadioList("races", characters, "armor", "assets/armor")
		resetCharacters = false
		for _, region in ipairs(regionList) do
			setRadioList(region[1], region[2], "armor", "assets/armor/" .. repName)
		end
		wireButtons()
		setControlValues()
		dew.command("Player.PreferredCharacter", {}):next(function(current)
			setDivValue("races", current, true)
		end)
	end)
end

------------------------------------------------------------------------------------------
-- side lists

local function hideForms(selector)
	for _, element in ipairs(document:QuerySelectorAll(selector)) do
		element:SetClass("hide", true)
	end
end

local function markClicked(button)
	for _, element in ipairs(document:QuerySelectorAll(".clickedElement")) do
		element:SetClass("clickedElement", false)
	end
	if button then button:SetClass("clickedElement", true) end
end

local function chosenIndex(formId)
	local form = forms[formId]
	return form and form.chosen or 0
end

local function armorShow(showMe, button, region)
	activePage = "#page1 #" .. showMe
	if subForm == activePage then return end
	markClicked(button)
	hideForms(".armorForm")
	el(showMe):SetClass("hide", false)
	itemNumber = math.max(chosenIndex(showMe) - 1, 0)
	updateSelection(itemNumber, false, true)
	local item = forms[showMe] and forms[showMe].items[chosenIndex(showMe)]
	setInfo(item and item[1] or "", item and item[3] or "")
	showInfo(true)
	dew.playSound("a_button")
	if subForm ~= activePage and region then
		enterSubCamera(region)
	elseif not region and subCamera then
		exitSubCamera()
	end
	subForm = activePage
end

local function colorShow(showMe, button, region)
	activePage = "#page2 #" .. showMe
	if subForm == activePage then return end
	markClicked(button)
	hideForms("#page2 .colorForm")
	el("colorPicker"):SetClass("hide", true)
	el(showMe):SetClass("hide", false)
	itemNumber = chosenIndex(showMe)
	updateSelection(itemNumber, false, true)
	local form = forms[showMe]
	local item = form and form.items[form.chosen or 0]
	setInfo(item and item[1] or (form and form.custom or ""), characterColors[showMe] or "")
	showInfo(true)
	dew.playSound("a_button")
	if subForm ~= activePage and region then
		enterSubCamera(region)
	elseif not region and subCamera then
		exitSubCamera()
	end
	subForm = activePage
end

local function emblemShowList(showMe, button, colorGrid)
	activePage = "#page3 #" .. showMe
	if subForm == activePage then return end
	markClicked(button)
	hideForms(".emblemColorForm")
	hideForms(".emblemForm")
	el("emblemColorPicker"):SetClass("hide", true)
	el(showMe):SetClass("hide", false)
	el("emblemImages").style.display = colorGrid and "none" or "block"
	el("emblemColors").style.display = colorGrid and "block" or "none"
	itemNumber = chosenIndex(showMe) - (colorGrid and 0 or 1)
	dew.playSound("a_button")
	updateSelection(itemNumber, false, true)
	subForm = activePage
end

local function exitSubform(quiet)
	local page = subForm ~= "" and subForm or activePage
	if page:find(" ", 1, true) then
		local base = page:match("^(#page%d)")
		local formId = page:match("#page%d #(%w+)")
		clearSelected(formId and el(formId))
		markClicked(nil)
		activePage = base
		-- back on the list: select the button that opened it
		itemNumber = 0
		for i, item in ipairs(navItems(base)) do
			if item:GetAttribute("data-arg") == formId then itemNumber = i - 1 end
		end
		colorPicker, colorLocation = nil, nil
		if not quiet then dew.playSound("b_button") end
		if base == "#page1" then
			hideForms(".armorForm")
		elseif base == "#page2" then
			hideForms("#page2 .colorForm")
			el("colorPicker"):SetClass("hide", true)
		else
			hideForms(".emblemForm")
			hideForms(".emblemColorForm")
			el("emblemColorPicker"):SetClass("hide", true)
		end
		if base ~= "#page3" then el(base:sub(2) .. "Info"):SetClass("hide", true) end
		if hasGP then updateSelection(itemNumber, false, true) end
	end
	if subCamera and pageId() ~= "page3" then
		exitSubCamera()
	end
	subForm = ""
end

------------------------------------------------------------------------------------------
-- choosing tiles

local function openColorPicker(formId)
	local isEmblem = el(formId):IsClassSet("emblemColorForm")
	local host = isEmblem and el("emblemColorPicker") or el("colorPicker")
	hideForms(isEmblem and ".emblemColorForm" or "#page2 .colorForm")
	host:SetClass("hide", false)
	colorPicker = dew.makeColorPicker(host)
	colorLocation = formId
	local form = forms[formId]
	form.chosen = 0
	setChosenClass(formId)
	activePage = "#" .. pageId() .. (isEmblem and " #emblemColorPicker" or " #colorPicker")
	if not isEmblem then setInfo(form.custom, nil) end
	colorPicker.setColor(ColorUtil.hexToHsv(form.custom:sub(2)) or {})
	colorPicker.on("select", function(color)
		local rgb = ColorUtil.hsvToRgb(color.h, color.s, color.v)
		form.custom = string.format("#%02X%02X%02X", rgb[1], rgb[2], rgb[3])
		form.chosen = 0
		setChosenClass(formId)
		if formId == "colorsNameplate" then
			dew.command("Player.NameplateColor " .. form.custom)
			updateNameplateDisplay()
		elseif isEmblem then
			needSetEmblem = true
			emblemNeedsToApply = true
		else
			dew.command(commandFor(formId) .. " " .. form.custom)
			setInfo(form.custom, nil)
		end
	end)
end

local function chooseTile(formId, index, fromMouse)
	local form = forms[formId]
	if not form then return end
	if form.kind == "color" and index == 0 then
		if fromMouse then dew.playSound("a_button") end
		openColorPicker(formId)
		return
	end
	local item = form.items[index]
	if not item then return end
	form.chosen = index
	setChosenClass(formId)
	clearSelected(el(formId))
	local tiles = el(formId):QuerySelectorAll("span.tile")
	local tileIndex = form.kind == "color" and index + 1 or index
	if tiles[tileIndex] then tiles[tileIndex]:SetClass("selectedElement", true) end

	if form.kind == "armor" then
		dew.playSound("a_button")
		local command = commandFor(formId)
		if command == "Player.PreferredCharacter" then
			dew.command("Player.PreferredCharacter", {}):next(function(current)
				if current ~= item[2] then
					dew.command("Player.Armor.ReturnCustomizationBiped", {}):next(function()
						dew.command(command .. " " .. item[2], {}):next(function()
							dew.command("Game.ScenarioScript character_changed")
							setRepresentation()
							adjustBiped()
						end)
					end)
				end
			end)
		elseif command then
			dew.command(command .. " " .. item[2])
		end
		setInfo(item[1], item[3] or "")
		setArmorPrefs()
	elseif form.kind == "color" then
		if itemNumber ~= 0 then dew.playSound("a_button") end
		if formId == "colorsNameplate" then
			dew.command("Player.NameplateColor " .. item[2])
			updateNameplateDisplay()
		elseif el(formId):IsClassSet("emblemColorForm") then
			emblemNeedsToApply = true
			updateEmblemDisplay(false)
		else
			dew.command(commandFor(formId) .. " " .. item[2])
			setInfo(item[1], characterColors[formId] or "")
		end
	elseif form.kind == "emblem" then
		dew.playSound("a_button")
		if formId == "nameplateImage" then
			dew.command("Player.Nameplate " .. item[2])
			updateNameplateDisplay()
		else
			emblemNeedsToApply = true
			updateEmblemDisplay(false)
		end
	end
end

wireForm = function(formId)
	for _, tile in ipairs(el(formId):QuerySelectorAll("span.tile")) do
		local index = tonumber(tile:GetAttribute("data-index"))
		tile:AddEventListener("click", function()
			activePage = "#" .. pageId() .. " #" .. formId
			chooseTile(formId, index, true)
		end)
		tile:AddEventListener("mouseover", function()
			activePage = "#" .. (pageId() or "page1") .. " #" .. formId
			local form = forms[formId]
			itemNumber = form.kind == "color" and index or index - 1
			updateSelection(itemNumber, false, false)
		end)
		tile:AddEventListener("mouseout", function()
			if not hasGP then tile:SetClass("selectedElement", false) end
		end)
	end
end

------------------------------------------------------------------------------------------
-- buttons

local function inputBox(kind)
	dew.playSound("a_button")
	local command = kind == "playerName" and "Player.Name" or "Player.ServiceTag"
	local dialog = kind == "playerName" and "edit_player_name" or "edit_service_tag"
	dew.command(command, {}):next(function(current)
		dew.dialog(dialog, { initialValue = current }):next(function(result)
			if result ~= "-1" and result ~= nil then
				local value = kind == "playerName" and tostring(result) or tostring(result):upper()
				if kind == "playerName" then
					dew.command('Player.Name "' .. value .. '"')
				else
					dew.command("Player.ServiceTag " .. value)
				end
				dew.notify("settings-update", json.array({ json.array({ command, value }) }))
				setupEmblems(false, submitEmblemToStatsServer)
			end
		end)
	end)
end

-- delegated: the lists are rebuilt (inner_rml) when the character changes
local function baseNavOf(element)
	while element and not element:IsClassSet("baseNav") do
		if element:IsClassSet("buttonContainer") then return nil end
		element = element.parent_node
	end
	return element
end

local function onBaseNavClick(button)
	local action, arg = button:GetAttribute("data-action"), button:GetAttribute("data-arg")
	local region = button:GetAttribute("data-region")
	if action == "input" then
		inputBox(arg)
	elseif action == "armor" then
		armorShow(arg, button, region)
	elseif action == "color" then
		colorShow(arg, button, region)
	elseif action == "emblem" then
		emblemShowList(arg, button, button:GetAttribute("data-grid") == "1")
	end
end

local function onBaseNavOver(button)
	local arg = button:GetAttribute("data-arg")
	activePage = "#" .. (pageId() or "page1")
	for i, item in ipairs(navItems()) do
		if item:GetAttribute("data-arg") == arg then itemNumber = i - 1 end
	end
	updateSelection(itemNumber, false, false)
end

wireButtons = function()
	for _, list in ipairs(document:QuerySelectorAll(".buttonContainer")) do
		if not list:HasAttribute("data-wired") then
			list:SetAttribute("data-wired", "1")
			list:AddEventListener("click", function(event)
				local button = baseNavOf(event.target_element)
				if button then onBaseNavClick(button) end
			end)
			list:AddEventListener("mouseover", function(event)
				local button = baseNavOf(event.target_element)
				if button then onBaseNavOver(button) end
			end)
			list:AddEventListener("mouseout", function(event)
				local button = baseNavOf(event.target_element)
				if button and not hasGP then button:SetClass("selectedElement", false) end
			end)
		end
	end
end

local function showButtons(ids, show)
	for _, id in ipairs(ids) do jq("#" .. id):toggle(show) end
end

local function leavePage()
	if subForm:find(" ", 1, true) then
		exitSubform(true)
	elseif subCamera then
		exitSubCamera()
	end
	if emblemNeedsToApply then
		saveEmblem()
		submitEmblemToStatsServer()
	end
end

local function page1()
	leavePage()
	showButtons({ "toggleIconButton", "randomColors", "randomEmblem" }, false)
	showButtons({ "randomArmor", "reset" }, true)
end

local function page2()
	leavePage()
	showButtons({ "toggleIconButton", "randomArmor", "randomEmblem" }, false)
	showButtons({ "randomColors", "reset" }, true)
end

local function page3()
	leavePage()
	showButtons({ "randomArmor", "randomColors" }, false)
	showButtons({ "randomEmblem", "toggleIconButton", "reset" }, true)
	setupEmblems(false)
	updateEmblemDisplay(true)
	updateNameplateDisplay()
	enterSubCamera("emblem")
end

local PAGE_HOOKS = { page1, page2, page3 }

local function selectTab(index, sound)
	local tabs = document:QuerySelectorAll(".tabs li")
	local tab = tabs[index + 1]
	if not tab then return end
	PAGE_HOOKS[index + 1]()
	for i, other in ipairs(tabs) do
		other:SetClass("selected", i == index + 1)
		other:SetClass("right", i > index + 1)
	end
	activePage = tab:GetAttribute("data-page")
	for i = 1, 3 do
		el("page" .. i):SetClass("hide", "#page" .. i ~= activePage)
	end
	tabIndex = index
	itemNumber = -1
	updateSelection(itemNumber, false, true)
	if sound then dew.playSound("horizontal_navigation") end
end

local function prevPage()
	clearSelected()
	if tabIndex > 0 then selectTab(tabIndex - 1, true) end
end

local function nextPage()
	clearSelected()
	if tabIndex < 2 then selectTab(tabIndex + 1, true) end
end

local function effectReset(quick)
	if exiting then return end -- prevent escape spamming
	exiting = true
	if not quick then dew.playSound("back_button") end
	dew.getSessionInfo():next(function(info)
		if info.mapName == "mainmenu" then
			el("blackLayer").style.display = "block"
			jq("#blackLayer"):fadeIn(quick and 0 or 170, function()
				jq("#background"):hide()
				if not quick then
					dew.command("Game.ScenarioScript leave_settings")
					dew.command("Player.Armor.ReturnCustomizationBiped")
				end
				jq("#settingsWindow"):hide()
				dew.setTimeout(function()
					dew.command("Game.DisableScreenEffect 0 0")
					dew.command("game.hideh3ui 0")
					jq("#blackLayer"):fadeOut(quick and 0 or 170, function()
						dew.hide()
						exiting = false
					end)
				end, 170)
			end)
		else
			dew.hide()
			exiting = false
		end
	end)
end

local function cancelButton()
	local function run()
		itemNumber = 0
		effectReset(false)
		subCamera = false
		page1()
		if emblemNeedsToApply then
			saveEmblem()
			submitEmblemToStatsServer()
		end
		dew.command("writeconfig")
	end
	if not isVisible or showing then
		-- wait until the show sequence has finished setting things up
		local waited = 0
		local timer
		timer = dew.setInterval(function()
			waited = waited + 50
			if (isVisible and not showing) or waited >= 400 then
				dew.clearInterval(timer)
				run()
			end
		end, 50)
	else
		run()
	end
end

local resetDelayed = false
local function reset()
	dew.dialog("confirm_reset_customization"):next(function(result)
		if result ~= "yes" then return end
		if activePage:sub(1, 6) == "#page1" then
			for _, region in ipairs(regionList) do setDivValue(region[1], "base", true) end
			setArmorPrefs()
		elseif activePage:sub(1, 6) == "#page2" then
			for _, formId in ipairs(ARMOR_COLOR_FORMS) do
				local color = defaultColorList[formId]
				if color then
					dew.command(commandFor(formId) .. " " .. color)
				else
					color = "#000000"
				end
				setDivValue(formId, color, false)
			end
		elseif activePage:sub(1, 6) == "#page3" and not resetDelayed then
			setDivValue("emblemIcon", forms.emblemIcon.items[1] and forms.emblemIcon.items[1][2] or "0", true)
			setDivValue("emblemBackgroundImage", forms.emblemBackgroundImage.items[1] and forms.emblemBackgroundImage.items[1][2] or "0", true)
			for _, formId in ipairs(EMBLEM_COLOR_FORMS) do
				forms[formId].custom = "#C3C3C3"
				forms[formId].chosen = 0
				setChosenClass(formId)
			end
			forms.colorsNameplate.custom = "#546E26"
			forms.colorsNameplate.chosen = 0
			setChosenClass("colorsNameplate")
			dew.command("Player.NameplateColor #546e26")
			emblemToggle = 1
			emblemNeedsToApply = true
			updateEmblemDisplay(false)
			resetDelayed = true
			dew.setTimeout(function() resetDelayed = false end, 200)
		end
	end)
	dew.playSound("a_button")
end

local function randomColorHex()
	return string.format("#%06X", math.random(0, 16777214))
end

local function randomArmor()
	for _, region in ipairs(regionList) do
		local form = forms[region[1]]
		if form and #form.items > 0 then
			local random = math.random(1, #form.items)
			form.chosen = random
			setChosenClass(region[1])
		end
	end
	setArmorPrefs()
	dew.playSound("a_button")
end

local function randomEmblem()
	for _, formId in ipairs({ "emblemIcon", "emblemBackgroundImage" }) do
		local form = forms[formId]
		if form and #form.items > 0 then
			form.chosen = math.random(1, #form.items)
			setChosenClass(formId)
		end
	end
	for _, formId in ipairs({ "colorsEmblemPrimary", "colorsEmblemSecondary", "colorsEmblemImage", "colorsNameplate" }) do
		local color = randomColorHex()
		forms[formId].custom = color
		forms[formId].chosen = 0
		setChosenClass(formId)
		if colorLocation == formId and colorPicker then
			colorPicker.setColor(ColorUtil.hexToHsv(color:sub(2)))
		end
		if formId == "colorsNameplate" then
			dew.command("Player.NameplateColor " .. color)
		end
	end
	emblemNeedsToApply = true
	updateEmblemDisplay(false)
	dew.playSound("a_button")
end

local function randomColors()
	for _, formId in ipairs(ARMOR_COLOR_FORMS) do
		local color = randomColorHex()
		forms[formId].custom = color
		forms[formId].chosen = 0
		setChosenClass(formId)
		if colorLocation == formId and colorPicker then
			colorPicker.setColor(ColorUtil.hexToHsv(color:sub(2)))
		end
		dew.command(commandFor(formId) .. " " .. color)
	end
	dew.playSound("a_button")
end

local function toggleIcon()
	emblemToggle = 1 - emblemToggle
	emblemNeedsToApply = true
	updateEmblemDisplay(false)
	dew.playSound("a_button")
end

local function openModBrowser()
	dew.playSound("a_button")
	dew.command("game.showscreen mod_browse")
end

------------------------------------------------------------------------------------------
-- navigation

local function isColorGrid()
	return (activePage:sub(1, 13) == "#page2 #color" or activePage:sub(1, 13) == "#page3 #color")
		and not activePage:find("colorPicker", 1, true) and not activePage:find("ColorPicker", 1, true)
end

local function upNav()
	if isColorGrid() then
		if itemNumber > 3 then
			itemNumber = itemNumber - 3
			updateSelection(itemNumber, true, true)
		elseif itemNumber > 0 then
			itemNumber = 0
			updateSelection(itemNumber, true, true)
		end
	elseif activePage:find("olorPicker", 1, true) then
		return
	elseif itemNumber > 0 then
		itemNumber = itemNumber - 1
		updateSelection(itemNumber, true, true)
	elseif itemNumber < #navItems() - 1 then
		itemNumber = #navItems() - 1
		updateSelection(itemNumber, true, true)
	end
end

local function downNav()
	if isColorGrid() then
		if itemNumber < #navItems() - 3 then
			itemNumber = itemNumber == 0 and 1 or itemNumber + 3
			updateSelection(itemNumber, true, true)
		end
	elseif activePage:find("olorPicker", 1, true) then
		return
	elseif itemNumber < #navItems() - 1 then
		itemNumber = itemNumber + 1
		updateSelection(itemNumber, true, true)
	else
		itemNumber = 0
		updateSelection(itemNumber, true, true)
	end
end

local function leftNav()
	if isColorGrid() and itemNumber > 0 and itemNumber % 3 ~= 1 then
		itemNumber = itemNumber - 1
		updateSelection(itemNumber, true, true)
	end
end

local function rightNav()
	if isColorGrid() and itemNumber % 3 ~= 0 then
		itemNumber = itemNumber + 1
		updateSelection(itemNumber, true, true)
	end
end

local function selectElement()
	local formId = activePage:match("#page%d #(%w+)")
	if formId and forms[formId] then
		local index = forms[formId].kind == "color" and itemNumber or itemNumber + 1
		chooseTile(formId, index, false)
	else
		local item = navItems()[itemNumber + 1]
		if item then onBaseNavClick(item) end
	end
end

local function handleRightClick()
	if activePage:find(" ", 1, true) or subForm:find(" ", 1, true) then
		exitSubform()
	else
		cancelButton()
	end
end

dew.input.on("scroll", function(type, axis, value)
	local step = ((type == 2) and 4 or 1) * value
	if axis == 0 then
		if step == -1 then upNav() end
		if step == 1 then downNav() end
	elseif axis == 1 then
		if step == -1 then leftNav() end
		if step == 1 then rightNav() end
	end
	if type == 2 and activePage:sub(1, 13) ~= "#page3 #color" and activePage:sub(1, 13) ~= "#page2 #color" then
		if value == -1 and itemNumber > 0 then
			itemNumber = 0
			updateSelection(itemNumber, true, true)
		elseif value == 1 and itemNumber < #navItems() - 1 then
			itemNumber = #navItems() - 1
			updateSelection(itemNumber, true, true)
		end
	end
end)

dew.input.on("action", function(e)
	local Actions = dew.input.Actions
	if e.action == Actions.A then
		selectElement()
	elseif e.action == Actions.B then
		handleRightClick()
	elseif e.action == Actions.X then
		if activePage:sub(1, 6) == "#page3" then toggleIcon() end
	elseif e.action == Actions.Y then
		if activePage:sub(1, 6) == "#page1" then randomArmor()
		elseif activePage:sub(1, 6) == "#page2" then randomColors()
		elseif activePage:sub(1, 6) == "#page3" then randomEmblem() end
	elseif e.action == Actions.Select then
		reset()
	elseif e.action == Actions.Start then
		openModBrowser()
	elseif e.action == Actions.LeftBumper then
		prevPage()
	elseif e.action == Actions.RightBumper then
		nextPage()
	end
end)

dew.on("controllerinput", function(e)
	if not hasGP then return end
	local c = e.data or {}
	local lx, ly, rx, ry = tonumber(c.AxisLeftX) or 0, tonumber(c.AxisLeftY) or 0, tonumber(c.AxisRightX) or 0, tonumber(c.AxisRightY) or 0
	if activePage:find("olorPicker", 1, true) and colorPicker then
		if math.abs(lx) > 0.8 or math.abs(ly) > 0.8 or math.abs(rx) > 0.8 or math.abs(ry) > 0.8 then
			controllerSetEmblem = true
		end
		local within = math.abs(lx) < axisThreshold and math.abs(ly) < axisThreshold and math.abs(rx) < axisThreshold and math.abs(ry) < axisThreshold
		if within and controllerSetEmblem then
			controllerSetEmblem = false
			updateEmblemDisplay(false)
		end
		colorPicker.controllerInput(c)
	elseif rx ~= 0 then
		if rx > axisThreshold then rotateBiped("right") end
		if rx < -axisThreshold then rotateBiped("left") end
	end
end)

local function initGamepad()
	dew.command("Settings.Gamepad", {}):next(function(result)
		hasGP = tonumber(result) == 1
		el("settingsWindow"):SetClass("gamepad", hasGP)
		if hasGP then
			jq("#reset img"):attr("src", "dew://assets/buttons/360_Back.png")
			jq("#randomArmor img"):attr("src", "dew://assets/buttons/360_Y.png")
			jq("#randomColors img"):attr("src", "dew://assets/buttons/360_Y.png")
			jq("#modBrowser img"):attr("src", "dew://assets/buttons/360_Start.png")
			jq("#cancelButton img"):attr("src", "dew://assets/buttons/360_B.png")
			jq("#toggleIconButton img"):attr("src", "dew://assets/buttons/360_X.png")
			jq("#randomEmblem img"):attr("src", "dew://assets/buttons/360_Y.png")
			local tabImages = document:QuerySelectorAll(".tabs img")
			if tabImages[1] then tabImages[1]:SetAttribute("src", "dew://assets/buttons/360_LB.png") end
			if tabImages[2] then tabImages[2]:SetAttribute("src", "dew://assets/buttons/360_RB.png") end
			updateSelection(itemNumber, false, true)
		else
			clearSelected()
		end
	end)
end

------------------------------------------------------------------------------------------
-- show / hide

dew.on("show", function()
	isVisible = true
	showing = true
	resetCharacters = true
	setRepresentation()

	jq("#background"):hide()
	jq("#settingsWindow"):hide()
	hideForms(".form")
	for i = 1, 3 do
		local box = el("page" .. i .. "Info")
		if box and box:IsClassSet("infoBox") then box:SetClass("hide", true) end
	end
	dew.getSessionInfo():next(function(info)
		mapName = info.mapName
		if info.mapName == "mainmenu" then
			el("blackLayer").style.display = "block"
			jq("#blackLayer"):fadeIn(170, function()
				dew.command("Game.ScenarioScript settings_cam"):next(function()
					dew.command("Player.Armor.Update"):next(function()
						adjustBiped():next(function()
							jq("#settingsWindow"):show()
							selectTab(0, false)
							initGamepad()
							updateEmblemDisplay(true)
							jq("#background"):show()
							showing = false
							dew.setTimeout(function()
								dew.command("Game.DisableScreenEffect 0 1")
								dew.command("game.hideh3ui 1")
								jq("#blackLayer"):fadeOut(170)
							end, 100)
						end)
					end)
				end)
			end)
		else
			dew.hide()
			showing = false
		end
	end)
end)

dew.on("hide", function()
	markClicked(nil)
	dew.command("Game.HideH3UI 0")
	isVisible = false
end)

dew.on("serverconnect", function()
	if not isVisible then return end
	itemNumber = 0
	effectReset(true)
	page1()
	dew.command("writeconfig")
end)

dew.on("mod_changed", function(e)
	if (e.data or {}).kind == "mainmenu" and isVisible then
		if emblemNeedsToApply then
			saveEmblem()
			submitEmblemToStatsServer()
		end
		dew.command("writeconfig")
		dew.hide()
	end
end)

------------------------------------------------------------------------------------------
-- DOM events

document:AddEventListener("keyup", function(event)
	if tonumber(event.parameters.key_identifier) == KI_SNAPSHOT then
		dew.command("Game.TakeScreenshot")
	end
end)

document:AddEventListener("keydown", function(event)
	local key = tonumber(event.parameters.key_identifier)
	if key == KI_OEM_3 or key == KI_OEM_8 then
		dew.show("console")
	elseif key == 28 or key == 16 or (key >= 90 and key <= 93) or key == 1 then
		event:StopPropagation() -- Q, E, arrows, space: navigation only
	end
end)

local dragging = false
local lastX = 0
document:AddEventListener("mousedown", function(event)
	if tonumber(event.parameters.button) == 1 then
		handleRightClick()
	end
end)
document:AddEventListener("mouseup", function()
	dragging = false
	-- the colour picker applies the emblem when the mouse is released
	if needSetEmblem then
		updateEmblemDisplay(false)
		needSetEmblem = false
	end
end)
document:AddEventListener("mousemove", function(event)
	local x = tonumber(event.parameters.mouse_x) or 0
	if dragging and userCanRotate then
		local xDiff = lastX - x
		bipedRotate = bipedRotate - xDiff * 0.6
		dew.command("Player.Armor.SetUiModelRotation " .. normalize(bipedRotate))
	end
	lastX = x
end)

document:AddEventListener("load", function()
	el("playerWindow"):AddEventListener("mousedown", function(event)
		if tonumber(event.parameters.button) == 0 then
			lastX = tonumber(event.parameters.mouse_x) or 0
			dragging = true
		end
	end)

	jq("#toggleIconButton"):hide()
	jq("#randomEmblem"):hide()
	jq("#randomColors"):hide()
	jq("#reset"):show()

	for _, formId in ipairs({ "colorsEmblemPrimary", "colorsEmblemSecondary", "colorsEmblemImage", "colorsNameplate",
		"colorsPrimary", "colorsSecondary", "colorsTertiary", "colorsQuaternary", "colorsQuinary" }) do
		setRadioList(formId, h3ColorArray, "color")
	end
	setRadioList("gender", genderList, "armor", "assets/armor")

	-- always submit the emblem on boot, in case it changed before the game started or the stats
	-- server was offline the last time the player edited it
	setupEmblems(true, function()
		dew.setTimeout(submitEmblemToStatsServer, 5000)
	end)

	for index, tab in ipairs(document:QuerySelectorAll(".tabs li")) do
		tab:AddEventListener("click", function() selectTab(index - 1, true) end)
	end

	el("cancelButton"):AddEventListener("click", cancelButton)
	el("toggleIconButton"):AddEventListener("click", toggleIcon)
	el("randomEmblem"):AddEventListener("click", randomEmblem)
	el("randomColors"):AddEventListener("click", randomColors)
	el("randomArmor"):AddEventListener("click", randomArmor)
	el("reset"):AddEventListener("click", reset)
	el("modBrowser"):AddEventListener("click", openModBrowser)

	for _, list in ipairs(document:QuerySelectorAll(".buttonContainer")) do
		list:AddEventListener("mouseout", function(event)
			if event.target_element and event.target_element.id == list.id then clearSelected(list) end
		end)
	end

	wireButtons()
	setControlValues()
end)

-- debugging aid (harness `lua profile_settings return profileState()`)
function profileState()
	return "page=" .. activePage .. " sub=" .. subForm .. " item=" .. itemNumber .. " primary=" .. tostring(forms.colorsPrimary and forms.colorsPrimary.chosen)
end
