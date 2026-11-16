--[[
	object_properties.lua -- port of screens/forge/object_properties/object_properties.js.

	materials.xml is materials.lua (ForgeMaterials()), thumbnails are the "materials"
	spritesheet in materials.rcss.  The unused items.xml loader of the web version is gone.
]]

local KI_SNAPSHOT, KI_RETURN, KI_NUMPADENTER = 97, 72, 61

local containerElement, windowElement, descriptionElement, titleElement, subtitleElement
local screenManager
local hidden = false
local lastObjectIndex = -1
local recentMaterials = {}
local typing = false -- a text input has focus (keyboard X must not hide the screen)

local CHANGE_COLOR_MATERIALS = {
	[119] = true, [120] = true, [162] = true, [163] = true, [165] = true, [166] = true, [167] = true,
	[168] = true, [169] = true, [174] = true, [175] = true, [176] = true,
}
local SPECIAL_MATERIALS = {
	[119] = true, [120] = true, [121] = true, [162] = true, [163] = true, [165] = true, [166] = true,
	[167] = true, [168] = true, [169] = true, [174] = true, [175] = true, [176] = true,
}

local function q(selector, root)
	return (root or document):QuerySelector(selector)
end

local function materialSupportsChangeColor(materialIndex)
	return CHANGE_COLOR_MATERIALS[materialIndex] == true
end

local function setTitle(text)
	titleElement.inner_rml = Forge.escape("Object Properties " .. ((text and text ~= "") and (" - " .. text) or ""))
end

local function setSubtitle(text)
	subtitleElement.inner_rml = Forge.escape(text or "")
end

local function setDescription(text)
	q(".info-text", descriptionElement).inner_rml = Forge.escape(text or "")
end

local function hide()
	hidden = true
	dew.playSound("b_button")
	dew.hide()
end

local toastTimer
local function showToast(message)
	local toastElement = q(".toast")
	q(".toast-content", toastElement).inner_rml = Forge.escape(message)
	toastElement:SetClass("toast-show", true)
	if toastTimer then dew.clearTimeout(toastTimer) end
	toastTimer = dew.setTimeout(function()
		toastTimer = nil
		toastElement:SetClass("toast-show", false)
	end, 3000)
end

local function floor255(value)
	return math.floor((tonumber(value) or 0) * 255)
end

local function colorOf(properties, prefix)
	return {
		r = floor255(properties[prefix .. "_r"]),
		g = floor255(properties[prefix .. "_g"]),
		b = floor255(properties[prefix .. "_b"]),
	}
end

local function colorProps(prefix, color)
	return {
		[prefix .. "_r"] = color.r / 255,
		[prefix .. "_g"] = color.g / 255,
		[prefix .. "_b"] = color.b / 255,
	}
end

local function range(from, to)
	local list = {}
	for i = from, to do list[#list + 1] = i end
	return list
end

------------------------------------------------------------------------------------------
-- main screen
------------------------------------------------------------------------------------------

local function makeMainScreen(manager)
	local screenElement = document:GetElementById("main_screen")
	local propertyGrid = Forge.makePropertyGrid(q(".main-property-grid"))
	local materialsTree = nil
	local data = nil
	local items = nil
	local lastSelected = false
	local buildModel

	local function buildPalette(palette)
		items = {}
		for _, item in ipairs(palette.palette or {}) do
			items[item.tagIndex] = item
		end
	end

	local function updateSubtitle()
		local item = items and items[data.tag_index] or { name = "Unknown", type = "Unknown", tagIndex = data.tag_index }
		local typeName = Forge.paletteTypeName(item.type) or "undefined"
		local tagIndex = math.tointeger(tonumber(item.tagIndex) or 0) or 0
		setSubtitle(string.format("%s [%s] [%x]", tostring(item.name), typeName, tagIndex))
	end

	local function fetchMaterials(callback)
		if not materialsTree then
			materialsTree = ForgeMaterials()
		end
		callback(nil, materialsTree)
	end

	local function getMaterialName(materialIndex)
		for _, item in ipairs(Forge.descendants(materialsTree, "item")) do
			if item.attrs.value == materialIndex then
				return item.attrs.name or "Unknown"
			end
		end
		return nil
	end

	local function addRecentMaterial()
		if not data or not materialsTree then return end
		local properties = data.properties or {}
		local material = properties.reforge_material
		local materialColor = colorOf(properties, "reforge_material_color")
		for _, x in ipairs(recentMaterials) do
			if x.value == material and (not x.color or (x.color.r == materialColor.r and x.color.g == materialColor.g and x.color.b == materialColor.b)) then
				return
			end
		end
		local materialName = getMaterialName(material)
		if not materialName then return end
		local recentItem = { label = materialName, value = material }
		if materialSupportsChangeColor(recentItem.value) then
			recentItem.color = materialColor
		end
		table.insert(recentMaterials, 1, recentItem)
	end

	local function onPropertyChange(changes)
		for k, v in pairs(changes) do
			data.properties[k] = v
		end
		dew.callMethod("forgeaction", { type = 1, data = changes })
	end

	local function rebuild()
		propertyGrid.setModel(buildModel(data))
	end

	buildModel = function(d)
		if not d then return end
		local properties = d.properties

		local function makeProperty(name, label, type, meta, description)
			return {
				label = label,
				type = type,
				getValue = function() return properties[name] end,
				setValue = function(value) onPropertyChange({ [name] = value }) end,
				meta = meta,
				description = description,
			}
		end

		local function colorProperty(label, description, prefix, title)
			return {
				type = "color",
				label = label,
				description = description,
				meta = {},
				getValue = function() return colorOf(properties, prefix) end,
				setValue = function(color) onPropertyChange(colorProps(prefix, color)) end,
				action = function(item)
					manager.push("color_picker", {
						title = title or label,
						initialColor = item.model.getValue(),
						onColorSelected = function(color) item.setValue(color) end,
					})
				end,
			}
		end

		local function rebuildingSpinner(name, label, meta, description)
			return {
				type = "spinner",
				label = label,
				description = description or "",
				meta = meta,
				getValue = function() return properties[name] end,
				setValue = function(value)
					onPropertyChange({ [name] = value })
					rebuild()
				end,
			}
		end

		local truthy = function(v) return v ~= nil and v ~= false and v ~= 0 end

		local isGarbageVolume = truthy(d.is_garbage_volume)
		local isKillVolume = truthy(d.is_kill_volume)
		local isMapModifier = truthy(d.is_map_modifier)
		local isPrematchCamera = truthy(d.is_prematch_camera)
		local isPodiumPoint = truthy(d.is_podium_point)
		local hasSpawn, hasSymmetry, hasZone, hasTeam, hasSpawnOrder, isTeleporter = false, false, false, false, false, false
		local hasChangeColors = false

		local t = d.object_type_mp
		if t and t >= 0x0 and t <= 0x8 then
			hasSpawn = true
			hasSymmetry = true
			hasChangeColors = (tonumber(d.change_color_count) or 0) > 0
		elseif t == 0x9 or t == 0xA or t == 0xB then
			hasZone = true
			isTeleporter = true
			hasSymmetry = true
		elseif t == 0xF or t == 0xC or t == 0x15 then
			hasTeam = true
			hasSymmetry = true
		elseif t == 0xD then
			hasSpawnOrder = true
			hasZone = true
			hasTeam = true
			hasSymmetry = true
		elseif t == 0xE then
			hasSpawnOrder = true
		elseif t == 0x11 then
			hasZone = true
			hasTeam = true
			hasSymmetry = true
		elseif t == 0x10 or t == 0x13 or t == 0x12 then
			if t ~= 0x12 then hasSpawn = true end
			hasZone = true
			hasSpawnOrder = true
		elseif t == 0x14 then
			hasZone = true
			hasSpawnOrder = true
			hasSymmetry = true
		elseif t == 0x16 or t == 0x17 then
			if t == 0x16 then hasSymmetry = true end
			hasZone = true
			hasSpawnOrder = true
		end

		if isGarbageVolume or isKillVolume then hasZone = true end
		if isKillVolume then hasTeam = true end
		if isPrematchCamera then
			hasSpawn = false
			hasTeam = true
			hasChangeColors = false
		end
		if isPodiumPoint then
			hasSpawnOrder, hasSpawn, hasZone, hasTeam, hasSymmetry, hasChangeColors = false, false, false, false, false, false
		end
		if truthy(d.is_screenfx) then hasTeam = true end
		if (tonumber(d.device_type) or -1) > -1 then hasTeam = true end
		if truthy(d.has_material) or isMapModifier then hasSpawn = false end
		if d.object_type == 0 or d.object_type == 13 then hasTeam = true end

		local model = propertyGrid.createModel()

		model.add({
			type = "action", label = "{Summary}", meta = {},
			action = function()
				manager.push("summary", { data = d.budget })
			end,
		})

		if not truthy(d.is_selected) then
			model.add({
				type = "action", label = "{Select All}", meta = {},
				action = function()
					dew.command("Forge.SelectAll")
					d.is_selected = true
					rebuild()
				end,
				description = "Select every instance of this item on the map.",
			})
		else
			model.add({
				type = "action", label = "{Deselect All}", meta = {},
				action = function()
					dew.command("Forge.DeselectAllOf")
					d.is_selected = false
					rebuild()
				end,
				description = "Deselect every instance this item on the map.",
			})
			model.add({
				type = "action", label = "{Save Prefab}", meta = {},
				action = function()
					manager.push("save_prefab", { noHide = true })
				end,
				description = "Save the selected objects to a prefab.",
			})
		end

		model.group("General", function(m)
			m.add({
				type = "action", label = "{Gametypes}", meta = {},
				action = function()
					manager.push("engine_flags", {
						engineFlags = properties.engine_flags or 0,
						onChange = function(flags) onPropertyChange({ engine_flags = flags }) end,
					})
				end,
				description = "Choose the gametypes for which this item will spawn.",
			})

			if hasSpawn then
				m.add(makeProperty("respawn_rate", "Respawn Rate", "spinner", {
					{ label = "Never", value = 0 }, { label = "1", value = 1 }, { label = "3", value = 3 },
					{ label = "5", value = 5 }, { label = "10", value = 10 }, { label = "15", value = 15 },
					{ label = "20", value = 20 }, { label = "30", value = 30 }, { label = "45", value = 45 },
					{ label = "60", value = 60 }, { label = "90", value = 90 }, { label = "120", value = 120 },
					{ label = "150", value = 150 }, { label = "180", value = 180 },
				}, " This controls how many seconds it will take for this type of item to respawn on the map."))
				m.add(makeProperty("on_map_at_start", "Placed at Start", "spinner",
					{ { label = "No", value = 0 }, { label = "Yes", value = 1 } },
					"This controls whether the item is on the map from the start of the game."))
			end

			if truthy(d.has_spare_clips) then
				m.add(makeProperty("spare_clips", "Spare Clips", "spinner", { 0, 1, 2, 3, 4 },
					"This controls how many clips of ammunition are available for this item."))
			end

			if hasTeam then
				m.add(makeProperty("team_affiliation", "Team", "spinner", {
					{ label = "Neutral", value = 8 }, { label = "Defender", value = 0 }, { label = "Attacker", value = 1 },
					{ label = "3rd Team", value = 2 }, { label = "4th Team", value = 3 }, { label = "5th Team", value = 4 },
					{ label = "6th Team", value = 5 }, { label = "7th Team", value = 6 }, { label = "8th Team", value = 7 },
				}, "This item will belong to the selected team."))
			end

			if hasSpawnOrder then
				m.add(makeProperty("spawn_order", "Spawn Order", "spinner", range(0, 10),
					"This allows you to set the order in which this item becomes active."))
			end

			if hasSymmetry then
				m.add(makeProperty("symmetry", "Symmetry", "spinner", {
					{ label = "Both", value = 0 }, { label = "Symmetric", value = 1 }, { label = "Asymmetric", value = 2 },
				}, "This controls whether this object spawns in symmetric games, asymmetric games, or both."))
			end
		end)

		if not hasZone and not truthy(d.has_material) and not isPrematchCamera then
			model.add(makeProperty("physics", "Physics", "spinner",
				{ { label = "Default", value = 0 }, { label = "Phased", value = 1 } },
				"Overrides the default physical properties of this item."))
		end

		if truthy(d.is_forge_scenery) then
			model.add(makeProperty("scale", "Scale", "range", {
				min = 0.001, max = 10, step = 0.001, allowUnboundedInput = true,
				displayTextOverride = function(value) return string.format("%.4f", value) end,
			}, "This determines the scale of the object."))
		end

		if isMapModifier then
			local barrierOptions = { { label = "Disabled", value = 1 }, { label = "Enabled", value = 0 } }
			model.group("Map options", function(m)
				m.add(makeProperty("map_disable_push_barrier", "Push Barriers", "spinner", barrierOptions,
					"Toggle the default push barriers for this scenario."))
				m.add(makeProperty("map_disable_death_barrier", "Death Barriers", "spinner", barrierOptions,
					"Toggle the default death barriers for this scenario."))
				m.add({
					type = "range",
					label = "Gravity",
					description = "Adjusts the strength of gravity on the map.",
					meta = { min = 0, max = 1, step = 0.01 },
					getValue = function() return 1.0 - (tonumber(properties.map_physics_gravity) or 0) end,
					setValue = function(value) onPropertyChange({ map_physics_gravity = 1.0 - value }) end,
				})
			end)

			local cameraFxRange = { min = 0, max = 1.0, step = 0.01 }
			model.group("Camera FX", function(m)
				m.add(makeProperty("camera_fx_exposure", "Exposure", "range", cameraFxRange,
					"Adjusts the overall brightness of the map."))
				m.add(makeProperty("camera_fx_light_intensity", "Dynamic Light Intensity", "range", cameraFxRange,
					"Adjusts the intensity of reforge lights, player flashlights, and other dynamic lights."))
				m.add(makeProperty("camera_fx_bloom", "Emissive Bloom", "range", cameraFxRange,
					"Adjusts bloom of shaders and particles with self-illum properties."))
				m.add(makeProperty("camera_fx_light_bloom", "Ambient Bloom", "range", { min = 0, max = 2.0, step = 0.01 },
					"Adjusts overall bloom of the map."))
			end)

			model.group("Atmosphere", function(m)
				local options = d.options or {}
				local skyOptions = { { label = "Map Default", value = 0 } }
				local weatherEffectOptions = { { label = "Map Default", value = 0 } }
				for i, sky in ipairs(options.skies or {}) do
					skyOptions[#skyOptions + 1] = { label = sky, value = i }
				end

				m.add(rebuildingSpinner("atmosphere_properties_skybox", "Skybox", skyOptions))

				if truthy(properties.atmosphere_properties_skybox) then
					m.add(rebuildingSpinner("atmosphere_properties_skybox_override_transform", "Skybox Transform",
						{ { label = "Default", value = 0 }, { label = "Custom", value = 1 } }))

					if truthy(properties.atmosphere_properties_skybox_override_transform) then
						m.add({
							type = "range",
							label = "Skybox Z",
							description = "",
							meta = { min = -500.0, max = 500.0, step = 0.1 },
							getValue = function() return (tonumber(properties.atmosphere_properties_skybox_offset_z) or 0) * 500 end,
							setValue = function(value)
								onPropertyChange({ atmosphere_properties_skybox_offset_z = value / 500 })
							end,
						})
					end
				end

				for i, effect in ipairs(options.weather_effects or {}) do
					weatherEffectOptions[#weatherEffectOptions + 1] = { label = effect, value = i }
				end
				m.add(makeProperty("atmosphere_properties_weather", "Weather", "spinner", weatherEffectOptions))

				m.add(rebuildingSpinner("atmosphere_properties_enabled", "Fog",
					{ { label = "Map Default", value = 0 }, { label = "Custom", value = 1 } }))

				if truthy(properties.atmosphere_properties_enabled) then
					m.add(makeProperty("atmosphere_properties_brightness", "Fog Brightness", "range", { min = 0, max = 1, step = 0.01 }))
					m.add(makeProperty("atmosphere_properties_fog_density", "Fog Density", "range", { min = 0, max = 1, step = 0.01 }))
					m.add(makeProperty("atmosphere_properties_fog_visibility", "Fog Visibility", "range", { min = 0, max = 1, step = 0.01 }))
					m.add(colorProperty("Fog Color", "", "atmosphere_properties_fog_color"))
				end
			end)
		end

		if isTeleporter then
			model.add(makeProperty("teleporter_channel", "Channel", "spinner", range(0, 15)))
		end

		if hasChangeColors and not truthy(d.has_material) then
			model.group("Colors", function(m)
				m.add(colorProperty("Primary Color", "Primary Color", "primary_change_color"))
			end)
		end

		if truthy(d.has_material) then
			model.group("Material", function(m)
				local supportsColor = materialSupportsChangeColor(properties.reforge_material)
				local oldMaterialIndex = properties.reforge_material

				local allMaterials = {}
				for _, node in ipairs(Forge.descendants(materialsTree, "item")) do
					allMaterials[#allMaterials + 1] = { label = node.attrs.name, value = node.attrs.value }
				end

				local material = makeProperty("reforge_material", "Material", "spinner", allMaterials,
					"Choose the shader used by this object.")
				material.action = function()
					addRecentMaterial()
					manager.push("material_picker", {
						materials = materialsTree,
						onMaterialSelected = function(selected)
							local changes = { reforge_material = selected.value }
							if selected.color then
								for k, v in pairs(colorProps("reforge_material_color", selected.color)) do changes[k] = v end
							end
							onPropertyChange(changes)
							rebuild()
						end,
					})
				end
				material.setValue = function(value)
					onPropertyChange({ reforge_material = value })
					if SPECIAL_MATERIALS[properties.reforge_material] or SPECIAL_MATERIALS[oldMaterialIndex] then
						rebuild()
					end
				end
				m.add(material)

				local materialTypeOptions = { { label = "Default", value = 0 } }
				for i, materialType in ipairs((d.options or {}).material_types or {}) do
					materialTypeOptions[#materialTypeOptions + 1] = { label = materialType, value = i }
				end
				m.add(makeProperty("reforge_material_type", "Impact Type", "spinner", materialTypeOptions,
					"Choose the particle and sound interactions for this object."))

				if supportsColor then
					m.add(colorProperty("Material Color", "Select the color of this object.", "reforge_material_color"))
				end

				m.add(rebuildingSpinner("reforge_material_tex_override", "Texture Scale",
					{ { label = "Default", value = 0 }, { label = "Custom", value = 1 } },
					"Choose between default or custom texture scaling."))

				if truthy(properties.reforge_material_tex_override) then
					m.add(makeProperty("reforge_material_tex_scale", "Texture Scale", "range", { min = 0, max = 4.0, step = 0.01 }))
					m.add(makeProperty("reforge_material_tex_offset_x", "Texture Offset X", "range", { min = 0, max = 1.0, step = 0.01 }))
					m.add(makeProperty("reforge_material_tex_offset_y", "Texture Offset Y", "range", { min = 0, max = 1.0, step = 0.01 }))
				end

				m.add(makeProperty("reforge_material_allows_projectiles", "Projectile Passthrough", "spinner",
					{ { label = "Disabled", value = 0 }, { label = "Enabled", value = 1 } },
					"Determines whether projectiles (bullets, grenades) will pass through this item."))

				m.add(makeProperty("reforge_material_climbable", "Climbable", "spinner",
					{ { label = "No", value = 0 }, { label = "Yes", value = 1 } },
					"This determines whether this surface will be climbable."))

				m.add({
					type = "action", label = "{Team Barrier}", meta = {},
					action = function()
						manager.push("team_flags", {
							teamFlags = (tonumber(properties.reforge_material_team_barrier) or 0) & 0xff,
							title = "Team Barrier",
							onChange = function(flags)
								onPropertyChange({ reforge_material_team_barrier = flags & 0xff })
							end,
						})
					end,
					description = "Blocks entry to all but the selected teams.",
				})
			end)
		end

		if hasZone then
			model.group("Zone", function(m)
				m.add(rebuildingSpinner("shape_type", "Shape",
					{ { label = "Sphere", value = 1 }, { label = "Cylinder", value = 2 }, { label = "Box", value = 3 } },
					"Determines the shape of the zone for this item."))

				local function zoneRange(name, label, min, description)
					return makeProperty(name, label, "range", { min = min, max = 100, step = 0.1, allowUnboundedInput = true }, description)
				end
				local shape = properties.shape_type
				if shape == 3 then
					m.add(zoneRange("shape_width", "Width", 0.1, "This determines how wide the zone is for this item."))
					m.add(zoneRange("shape_depth", "Depth", 0.1, "This determines how deep the zone is for this item."))
					m.add(zoneRange("shape_top", "Top", 0.0, "This determines where the top of zone is for this item."))
					m.add(zoneRange("shape_bottom", "Bottom", 0.0, "This determines where the bottom of zone is for this item."))
				elseif shape == 2 or shape == 1 then
					if shape == 2 then
						m.add(zoneRange("shape_top", "Top", 0.0, "This determines where the top of zone is for this item."))
						m.add(zoneRange("shape_bottom", "Bottom", 0.0, "This determines where the bottom of the zone is for this item."))
					end
					m.add(zoneRange("shape_radius", "Radius", 0.1, "This determines the radius of the zone for this item."))
				end
			end)
		end

		local deviceType = tonumber(d.device_type) or -1
		if deviceType > -1 then
			model.group("Device", function(m)
				m.add(makeProperty("teleporter_channel", "Channel", "spinner", range(0, 31)))
				if deviceType == 1 then -- door
					m.add(makeProperty("device_delay_time", "Delay Time", "range", { min = 0, max = 60, step = 0.25 }, ""))
					m.add(makeProperty("device_door_open_time", "Open Time", "range", { min = 0, max = 60, step = 0.25 }, ""))
					m.add(makeProperty("device_trigger_radius", "Trigger Radius", "range", { min = 0, max = 60, step = 0.25 }, ""))
				elseif deviceType == 2 then -- gear
					m.add(makeProperty("device_turn_rate", "Turn Rate", "range", {
						min = 0, max = 5, step = 0.025,
						displayTextOverride = function(value) return string.format("%.3f", value) end,
					}, ""))
				end
			end)
		end

		if truthy(d.is_light) then
			model.group("Light", function(m)
				m.add(rebuildingSpinner("light_type", "Type", { { label = "Point", value = 0 }, { label = "Directional", value = 1 } }))
				if truthy(properties.light_type) then
					m.add(makeProperty("light_field_of_view", "Field of View", "range", { min = 0, max = 180, step = 0.01 }))
				end
				m.add(makeProperty("light_radius", "Radius", "range", { min = 0, max = 50, step = 0.01 }))
				m.add(makeProperty("light_intensity", "Intensity", "range", { min = 0, max = 2.0, step = 0.01 }))
				m.add(colorProperty("Light Color", "", "light_color"))
				m.add(rebuildingSpinner("light_illumination_function_type", "Function",
					{ { label = "None", value = 0 }, { label = "Pulse", value = 1 }, { label = "Flicker", value = 2 } },
					"Illumination function"))
				if truthy(properties.light_illumination_function_type) then
					m.add(makeProperty("light_illumination_function_base", "Base", "range", { min = 0.0, max = 1.0, step = 0.01 },
						"The minumum percentage of intensity"))
					m.add(makeProperty("light_illumination_function_freq", "Frequency", "range", { min = 0.0, max = 2.0, step = 0.01 },
						"The rate of change"))
				end
			end)
		end

		if truthy(d.is_screenfx) then
			model.group("Screen Fx", function(m)
				local normalRange = { min = 0, max = 1, step = 0.01 }
				m.add(makeProperty("fx_range", "Range", "range", { min = 0, max = 255, step = 1 }))
				m.add(makeProperty("fx_light_intensity", "Light Intensity", "range", normalRange))
				m.add(makeProperty("fx_saturation", "Saturation", "range", normalRange))
				m.add(makeProperty("fx_desaturation", "Desaturation", "range", normalRange))
				m.add(makeProperty("fx_gamma_decrease", "Gamma Decrease", "range", normalRange))
				m.add(makeProperty("fx_gamma_increase", "Gamma Increase", "range", normalRange))
				m.add(makeProperty("fx_tracing", "Tracing", "range", normalRange))
				m.add(colorProperty("Filter Color", "", "fx_color_filter"))
				m.add(colorProperty("Floor Color", "", "fx_color_floor"))
			end)
		end

		if isGarbageVolume then
			local collectionOptions = { { label = "Collect", value = 1 }, { label = "Ignore", value = 0 } }
			model.group("Garbage Collection", function(m)
				m.add(makeProperty("garbage_volume_interval", "Delay", "spinner", {
					{ label = "Instant", value = 0 }, { label = "3 Seconds", value = 1 },
					{ label = "5 Seconds", value = 2 }, { label = "10 Seconds", value = 3 },
				}, "Adjusts the time delay before garbage collection."))
				m.add(makeProperty("garbage_volume_collect_dead_biped", "Dead Bodies", "spinner", collectionOptions))
				m.add(makeProperty("garbage_volume_collect_weapons", "weapons", "spinner", collectionOptions))
				m.add(makeProperty("garbage_volume_collect_objectives", "Objectives", "spinner", collectionOptions))
				m.add(makeProperty("garbage_volume_collect_grenades", "Grenades", "spinner", collectionOptions))
				m.add(makeProperty("garbage_volume_collect_equipment", "Equipment", "spinner", collectionOptions))
				m.add(makeProperty("garbage_volume_collect_vehicles", "Vehicles", "spinner", collectionOptions))
			end)
		end

		if isKillVolume then
			model.group("Kill Volume", function(m)
				m.add(makeProperty("kill_volume_always_visible", "Visibility", "spinner",
					{ { label = "Never", value = 0 }, { label = "Always", value = 1 } },
					"Determines whether the volume will be visible outside of forge."))
				m.add(makeProperty("kill_volume_destroy_vehicles", "Vehicles", "spinner",
					{ { label = "Ignore", value = 0 }, { label = "Destroy", value = 1 } },
					"Toggle whether the kill volume destroys vehicles."))
				m.add(makeProperty("kill_volume_damage_cause", "Damage Cause", "spinner",
					{ { label = "Default", value = 0 }, { label = "Guardians", value = 1 }, { label = "Falling", value = 2 } },
					"Determines the reported cause of damage."))
			end)
		end

		return model
	end

	dew.on("forge_init", function(e)
		buildPalette(e.data or {})
	end)

	dew.on("show", function(e)
		local eventData = e.data or {}
		if hidden and lastObjectIndex == eventData.object_index and lastSelected == eventData.is_selected then
			return
		end
		lastSelected = eventData.is_selected
		hidden = false
		lastObjectIndex = eventData.object_index

		manager.popAll(false)

		data = eventData
		data.properties = data.properties or {}
		fetchMaterials(function()
			propertyGrid.setModel(buildModel(data))
		end)

		if not items then
			dew.callMethod("forgePalette"):next(function(r)
				buildPalette(json.decode(r) or {})
				updateSubtitle()
			end)
		else
			updateSubtitle()
		end
	end)

	propertyGrid.on("selectionChange", function(item)
		setDescription(item.model.description)
	end)

	return {
		activate = function()
			screenElement:SetClass("active", true)
			setTitle("")
			propertyGrid.focus()
		end,
		deactivate = function(props)
			if not (props and props.noHide) then
				screenElement:SetClass("active", false)
			end
			propertyGrid.blur()
		end,
		onAction = function(e)
			if e.action == dew.input.Actions.X then
				if not typing then hide() end
			elseif e.action == dew.input.Actions.B then
				dew.playSound("b_button")
				addRecentMaterial()
				dew.hide()
			end
		end,
	}
end

------------------------------------------------------------------------------------------
-- other screens
------------------------------------------------------------------------------------------

local function makeColorPickerScreen(manager)
	local screenElement = document:GetElementById("color_picker_screen")
	local active = false
	local onColorSelected
	local colorPicker = dew.makeColorPicker(q(".color-picker", screenElement))

	dew.on("controllerinput", function(e)
		if active then
			colorPicker.controllerInput(e.data or {})
		end
	end)

	colorPicker.on("select", function(color)
		local rgb = ColorUtil.hsvToRgb(color.h, color.s, color.v)
		if onColorSelected then
			onColorSelected({ r = rgb[1], g = rgb[2], b = rgb[3] })
		end
	end)

	return {
		activate = function(props)
			active = true
			if props and props.onColorSelected then
				onColorSelected = props.onColorSelected
				local c = ColorUtil.rgbToHsv(props.initialColor.r, props.initialColor.g, props.initialColor.b)
				colorPicker.setColor({ h = c.h * 360, s = c.s, v = c.v })
			end
			screenElement:SetClass("active", true)
			colorPicker.refresh()
			if props and props.title then
				setTitle(props.title)
			end
		end,
		deactivate = function()
			active = false
			screenElement:SetClass("active", false)
		end,
		onAction = function(e)
			if e.action == dew.input.Actions.B then
				dew.playSound("b_button")
				manager.pop()
			elseif e.action == dew.input.Actions.X then
				if not typing then hide() end
			end
		end,
	}
end

local function makeSummaryScreen(manager)
	local screenElement = q(".summary-screen")
	local grid = Forge.makePropertyGrid(q(".summary-property-grid", screenElement))
	local summaryData = {}

	grid.on("selectionChange", function(item)
		setDescription(item.model.description)
	end)

	local function onPropertyChange(changes)
		for k, v in pairs(changes) do summaryData[k] = v end
		dew.callMethod("forgeaction", { type = 1, data = changes })
	end

	local function makeProperty(name, label, type, meta, description)
		return {
			label = label,
			type = type,
			getValue = function() return summaryData[name] end,
			setValue = function(value) onPropertyChange({ [name] = value }) end,
			meta = meta,
			description = description,
		}
	end

	local function buildModel()
		local model = grid.createModel()
		local placed = tonumber(summaryData.summary_placed_on_map) or 0
		local maximum = tonumber(summaryData.summary_maximum_allowed) or 0
		model.add(makeProperty("summary_runtime_minimum", "Runtime Min", "range", { min = 0, max = placed, step = 1, isInteger = true },
			"The item will automatically spawn if the number of this type of item ever falls below the minimum."))
		model.add(makeProperty("summary_runtime_maximum", "Runtime Max", "range", { min = placed, max = maximum, step = 1, isInteger = true },
			"This sets the maximum number of this type of item that can be on the map."))
		model.add(makeProperty("summary_placed_on_map", "Placed On Map", "static", {},
			"This displays how many of this type of item are currently placed on the map."))
		model.add(makeProperty("summary_maximum_allowed", "Design Time Max", "static", {},
			"This displays the maximum number of this type of item that can ever be on the map."))
		model.add(makeProperty("summary_total_cost", "Total Cost", "static", {},
			"This displays the total amount of budget that you are using for this type of item."))
		return model
	end

	return {
		activate = function(props)
			screenElement:SetClass("active", true)
			grid.focus()
			if props and props.data then
				summaryData = props.data
			end
			grid.setModel(buildModel())
			setTitle("Summary")
		end,
		deactivate = function()
			screenElement:SetClass("active", false)
			grid.blur()
		end,
		onAction = function(e)
			if e.action == dew.input.Actions.X then
				if not typing then hide() end
			elseif e.action == dew.input.Actions.B then
				dew.playSound("b_button")
				manager.pop()
			end
		end,
	}
end

local function makeMaterialCategoryScreen(manager)
	local screenElement = document:GetElementById("material_picker_screen")
	local treeList = Forge.makeTreeList(q(".material-category-tree", screenElement))
	local onMaterialSelected = nil

	treeList.on("select", function(e)
		local node = e.path
		if not node or Forge.hasCategoryDescendant(node) then
			return
		end
		local list
		if node.attrs.id == "recent" then
			list = recentMaterials
		else
			list = {}
			for _, child in ipairs(node.children) do
				list[#list + 1] = { label = child.attrs.name, value = child.attrs.value }
			end
		end
		manager.push("material_picker_list", { materials = list, onMaterialSelected = onMaterialSelected })
	end)

	return {
		activate = function(props)
			screenElement:SetClass("active", true)
			if props and props.materials then
				onMaterialSelected = props.onMaterialSelected
				treeList.setSource(props.materials)
				treeList.gotoRoot()
			end
			treeList.focus()
			setTitle("Material")
		end,
		deactivate = function()
			screenElement:SetClass("active", false)
			treeList.blur()
		end,
		onAction = function(e)
			if e.action == dew.input.Actions.B then
				if treeList.atRoot() then manager.pop() end
			elseif e.action == dew.input.Actions.X then
				if not typing then hide() end
			end
		end,
	}
end

local function makeMaterialListScreen(manager)
	local screenElement = q(".material-picker-list-screen")
	local listElement = q(".material-list", screenElement)
	local materials = {}
	local materialList = Forge.makeListWidget(listElement, {
		itemSelector = ".item",
		hoverClass = "selected",
		hoverSelection = true,
		wrapAround = true,
	})
	local onMaterialSelected = nil

	materialList.on("select", function(e)
		if onMaterialSelected and materials[e.index + 1] then
			onMaterialSelected(materials[e.index + 1])
		end
	end)

	local function renderMaterialList()
		local html = {}
		for _, item in ipairs(materials) do
			html[#html + 1] = '<div class="item">'
			if item.color then
				local colorHex = string.format("%06x", (item.color.r << 16) | (item.color.g << 8) | item.color.b)
				html[#html + 1] = '<div class="name">' .. Forge.escape(item.label) .. ' - <span class="mute">#' .. colorHex
					.. '</span></div><div class="preview" style="background-color: #' .. colorHex .. '"></div>'
			else
				html[#html + 1] = '<div class="name">' .. Forge.escape(item.label) .. '</div><div class="preview material-thumb-'
					.. tostring(item.value) .. '"></div>'
			end
			html[#html + 1] = "</div>"
		end
		listElement.inner_rml = table.concat(html)
	end

	return {
		activate = function(props)
			screenElement:SetClass("active", true)
			if props and props.materials then
				onMaterialSelected = props.onMaterialSelected
				materials = props.materials
				renderMaterialList()
				materialList.focus()
				materialList.setSelected(0)
			else
				materialList.focus()
			end
		end,
		deactivate = function()
			screenElement:SetClass("active", false)
			materialList.blur()
		end,
		onAction = function(e)
			if e.action == dew.input.Actions.B then
				dew.playSound("b_button")
				manager.pop()
			elseif e.action == dew.input.Actions.X then
				if not typing then hide() end
			end
		end,
	}
end

-- engine flags and team flags are the same checkbox list
local function makeFlagsScreen(manager, screenId, listSelector, names, propsKey, fixedTitle)
	local screenElement = document:GetElementById(screenId)
	local listElement = q(listSelector, screenElement)
	local onChange = nil
	local flags = 0
	local list = Forge.makeListWidget(listElement, {
		itemSelector = ".item",
		hoverClass = "selected",
		hoverSelection = true,
		wrapAround = true,
	})

	local function render()
		local html = {}
		for i, name in ipairs(names) do
			local checked = ((1 << (i - 1)) & flags) ~= 0
			html[#html + 1] = '<div class="item' .. (checked and " checked" or "") .. '"><div class="checkbox"><div class="mark"></div></div><div>'
				.. Forge.escape(name) .. "</div></div>"
		end
		listElement.inner_rml = table.concat(html)
	end

	list.on("select", function(e)
		local mask = 1 << e.index
		if flags & mask ~= 0 then flags = flags & ~mask else flags = flags | mask end
		render()
		list.refresh()
		list.setSelected(e.index)
		if onChange then onChange(flags) end
	end)

	return {
		activate = function(props)
			props = props or {}
			flags = math.tointeger(tonumber(props[propsKey]) or 0) or 0
			onChange = props.onChange
			screenElement:SetClass("active", true)
			render()
			list.focus()
			list.setSelected(0)
			setTitle(fixedTitle or props.title)
		end,
		deactivate = function()
			screenElement:SetClass("active", false)
			list.blur()
		end,
		onAction = function(e)
			if e.action == dew.input.Actions.B then
				dew.playSound("b_button")
				manager.pop()
			elseif e.action == dew.input.Actions.X then
				if not typing then hide() end
			end
		end,
	}
end

local function makeSavePrefabScreen(manager)
	local screenElement = document:GetElementById("save_prefab_screen")
	local overlay = q(".modal-overlay")
	local nameInput = q("input", screenElement)
	local errorStatus = q(".error", screenElement)
	local active = false

	local function displayError(message)
		errorStatus.inner_rml = Forge.escape(message)
		screenElement:SetClass("shake", true)
		dew.setTimeout(function() screenElement:SetClass("shake", false) end, 250)
		errorStatus:SetClass("hidden", false)
		dew.playSound("error")
	end

	local function onConfirm()
		local raw = nameInput:GetAttribute("value") or ""
		local value = raw:match("^%s*(.-)%s*$")
		if #value == 0 then
			displayError("Prefab name can't be empty")
			return
		end
		if value:find('[\\/:%*%?"<>|]') then
			displayError("Prefab name can't contain \\/:*?\"<>|")
			return
		end
		dew.command('Forge.SavePrefab "' .. raw .. '"'):next(function()
			showToast("Prefab Saved")
			dew.setTimeout(function() manager.pop() end, 1)
		end):catch(function(err)
			displayError(type(err) == "table" and err.message or tostring(err))
		end)
	end

	local function onReject()
		dew.playSound("b_button")
		manager.pop()
	end

	nameInput:AddEventListener("keydown", function(event)
		if not active then return end
		local key = tonumber(event.parameters.key_identifier)
		if key == KI_RETURN or key == KI_NUMPADENTER then
			onConfirm()
		end
	end)
	nameInput:AddEventListener("focus", function() typing = true end)
	nameInput:AddEventListener("blur", function() typing = false end)

	return {
		activate = function()
			active = true
			screenElement:SetClass("inactive", false)
			overlay:SetClass("hidden", false)
			errorStatus:SetClass("hidden", true)
			nameInput:Focus()
		end,
		deactivate = function()
			active = false
			screenElement:SetClass("inactive", true)
			overlay:SetClass("hidden", true)
			nameInput:SetAttribute("value", "")
			nameInput:Blur()
		end,
		onAction = function(e)
			if e.action == dew.input.Actions.A then
				if e.inputType == "controller" then onConfirm() end
			elseif e.action == dew.input.Actions.B then
				onReject()
			end
		end,
		confirm = onConfirm,
	}
end

------------------------------------------------------------------------------------------

local screens

function init()
	containerElement = document:GetElementById("main_container")
	windowElement = document:GetElementById("main_window")
	descriptionElement = q(".window-info-box", windowElement)
	titleElement = q(".window-title", windowElement)
	subtitleElement = q(".window-subtitle", windowElement)
	q("#save_prefab_screen"):SetClass("inactive", true)

	screenManager = Forge.makeScreenManager()
	screens = {
		main = makeMainScreen(screenManager),
		color_picker = makeColorPickerScreen(screenManager),
		summary = makeSummaryScreen(screenManager),
		material_picker = makeMaterialCategoryScreen(screenManager),
		material_picker_list = makeMaterialListScreen(screenManager),
		engine_flags = makeFlagsScreen(screenManager, "engine_flags_screen", ".engine-list", {
			"Capture The Flag", "Slayer", "Oddball", "King Of The Hill", "Juggernaut", "Territories",
			"Assault", "VIP", "Infection",
		}, "engineFlags", "Gametypes"),
		save_prefab = makeSavePrefabScreen(screenManager),
		team_flags = makeFlagsScreen(screenManager, "team_flags_screen", ".team_list", {
			"Red Team (Defender)", "Blue Team (Attacker)", "Green Team", "Orange Team", "Purple Team",
			"Gold Team", "Brown Team", "Pink Team",
		}, "teamFlags", nil),
	}
	screenManager.setModel(screens)
	screenManager.push("main")

	document:AddEventListener("keyup", function(event)
		if tonumber(event.parameters.key_identifier) == KI_SNAPSHOT then
			dew.command("Game.TakeScreenshot")
		end
	end)

	containerElement:AddEventListener("mousedown", function(event)
		if event.target_element.id == "main_container" then
			event:StopPropagation()
			hide()
		end
	end)

	dew.input.on("action", function(e)
		if e.action == dew.input.Actions.X and not typing then
			hide()
		end
	end)
end

-- debug helper for the harness
function forgePropertiesState()
	local current = screenManager.currentScreen()
	return { screen = current and current.name or "", count = screenManager.count(), recent = #recentMaterials }
end
