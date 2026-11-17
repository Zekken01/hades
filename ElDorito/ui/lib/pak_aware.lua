--[[
	pak_aware.lua -- port of lib/pak-aware-context.js.

	Elements with a data-pak attribute get their src from the active mod package:
		<img data-pak="mainmenu" data-url="assets/maps/small/guardian"
		     data-fallback="dew://assets/maps/small/placeholder.jpg"/>
	Whenever that kind of mod changes (mod_changed), src is resolved again with
	dew.getAssetUrl; when nothing is found, or the file is missing, data-fallback is used.

		pakAwareContext.invalidateAll(kind)       -- kind nil: every element
		pakAwareContext.invalidateElement(element)
]]

local function split(text, separator)
	local parts = {}
	for part in tostring(text):gmatch("[^" .. separator .. "]+") do
		parts[#parts + 1] = part
	end
	return parts
end

local function maybeSetImage(img, newSrc)
	if newSrc == "" then
		-- nothing found and no fallback: no src at all (a browser's empty src shows nothing,
		-- RmlUi's draws a white box; img:not([src]) hides it)
		if img:HasAttribute("src") then img:RemoveAttribute("src") end
	elseif (img:GetAttribute("src") or "") ~= newSrc then
		img:SetAttribute("src", newSrc)
	end
end

local function invalidateImage(img)
	local url = img:GetAttribute("data-url") or ""
	local pak = img:GetAttribute("data-pak")
	local fallback = img:GetAttribute("data-fallback") or ""
	local fileTypes = img:GetAttribute("data-file-types")
	fileTypes = fileTypes and split(fileTypes, ",") or { "jpg", "png", "svg" }
	dew.getAssetUrl(url, { fileTypes = json.array(fileTypes), pak = pak }):next(function(resolved)
		-- the browser's onerror fallback: use it when nothing resolved or the file is missing
		if resolved == nil or resolved == "" or not dew.fileExists(resolved) then
			resolved = fallback
		end
		maybeSetImage(img, resolved)
	end, function()
		maybeSetImage(img, fallback)
	end)
end

local function invalidateElement(element)
	if element and element.tag_name == "img" then
		invalidateImage(element)
	end
end

local function invalidateAll(kind)
	for _, element in ipairs(document:QuerySelectorAll("[data-pak]")) do
		if not kind or kind == element:GetAttribute("data-pak") then
			invalidateElement(element)
		end
	end
end

dew.on("mod_changed", function(message)
	invalidateAll(message.data and message.data.kind)
end)

document:AddEventListener("load", function()
	invalidateAll()
end)

pakAwareContext = {
	invalidateAll = invalidateAll,
	invalidateElement = invalidateElement,
}
