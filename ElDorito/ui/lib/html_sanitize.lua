--[[
	html_sanitize.lua -- turns HTML from outside the UI (announcements, readmes, server
	text) into RML that RmlUi's strict XML parser accepts.

		local rml = htmlToRml('<p>Hi<br>there &nbsp; <a href="https://x">x</a></p>')

	Keeps a small set of tags, drops the rest (keeping their text), closes void tags,
	converts named entities to numeric ones and turns <a href> into
	<span class="link" data-href="...">, which screens wire to dew.openUrl.
]]

local ALLOWED = {
	p = true, div = true, span = true, b = true, strong = true, i = true, em = true, u = true,
	br = true, ul = true, ol = true, li = true, h1 = true, h2 = true, h3 = true, h4 = true,
	h5 = true, h6 = true, img = true, a = true, small = true, hr = true, code = true, pre = true,
}
local VOID = { br = true, img = true, hr = true }
local ATTRIBUTES = { class = true, style = true, id = true, src = true }

local ENTITIES = {
	nbsp = "&#160;", amp = "&amp;", lt = "&lt;", gt = "&gt;", quot = "&quot;", apos = "&apos;",
	copy = "&#169;", reg = "&#174;", trade = "&#8482;", hellip = "&#8230;", mdash = "&#8212;",
	ndash = "&#8211;", lsquo = "&#8216;", rsquo = "&#8217;", ldquo = "&#8220;", rdquo = "&#8221;",
	bull = "&#8226;", middot = "&#183;", deg = "&#176;", times = "&#215;",
}

local function fixEntities(text)
	-- named entities to numeric/XML ones; stray ampersands escaped
	return (text:gsub("&(#?%w*);?", function(name)
		if name:sub(1, 1) == "#" and #name > 1 then
			return "&" .. name .. ";"
		end
		local entity = ENTITIES[name:lower()]
		if entity then
			return entity
		end
		return "&amp;" .. name
	end))
end

local function escapeText(text)
	return fixEntities(text):gsub("<", "&lt;"):gsub(">", "&gt;")
end

local function parseAttributes(source)
	local attributes = {}
	-- Lua patterns have no alternation; parse the three quoting styles one by one
	for name, value in source:gmatch("([%w%-:]+)%s*=%s*\"([^\"]*)\"") do attributes[name:lower()] = value end
	for name, value in source:gmatch("([%w%-:]+)%s*=%s*'([^']*)'") do attributes[name:lower()] = value end
	for name, value in source:gmatch("([%w%-:]+)%s*=%s*([^%s\"'>]+)") do
		if attributes[name:lower()] == nil then attributes[name:lower()] = value end
	end
	return attributes
end

local function attributeString(attributes, allowed)
	local parts = {}
	for name, value in pairs(attributes) do
		if allowed[name] and not name:match("^on") then
			parts[#parts + 1] = string.format(' %s="%s"', name, escapeText(value):gsub('"', "&quot;"))
		end
	end
	table.sort(parts)
	return table.concat(parts)
end

function htmlToRml(html)
	html = tostring(html or "")
	-- comments, scripts and styles go entirely
	html = html:gsub("<!%-%-.-%-%->", "")
	html = html:gsub("<[Ss][Cc][Rr][Ii][Pp][Tt].-</[Ss][Cc][Rr][Ii][Pp][Tt]%s*>", "")
	html = html:gsub("<[Ss][Tt][Yy][Ll][Ee].-</[Ss][Tt][Yy][Ll][Ee]%s*>", "")

	local out = {}
	local stack = {}
	local position = 1
	while position <= #html do
		local tagStart, tagEnd, closing, name, rest = html:find("<(/?)([%a][%w]*)([^>]*)>", position)
		if not tagStart then
			out[#out + 1] = escapeText(html:sub(position))
			break
		end
		out[#out + 1] = escapeText(html:sub(position, tagStart - 1))
		position = tagEnd + 1
		name = name:lower()
		if ALLOWED[name] then
			local outName = name == "a" and "span" or name
			if closing == "/" then
				-- close back to the matching open tag, closing anything left open inside it
				for i = #stack, 1, -1 do
					if stack[i] == outName then
						for j = #stack, i, -1 do
							out[#out + 1] = "</" .. stack[j] .. ">"
							stack[j] = nil
						end
						break
					end
				end
			elseif VOID[name] then
				local attributes = parseAttributes(rest)
				out[#out + 1] = "<" .. name .. attributeString(attributes, ATTRIBUTES) .. "/>"
			else
				local attributes = parseAttributes(rest)
				local extra = ""
				if name == "a" then
					local href = attributes.href or ""
					extra = string.format(' class="link" data-href="%s"', escapeText(href):gsub('"', "&quot;"))
					attributes.class = nil
				end
				out[#out + 1] = "<" .. outName .. attributeString(attributes, ATTRIBUTES) .. extra .. ">"
				if not rest:match("/%s*$") then
					stack[#stack + 1] = outName
				else
					out[#out + 1] = "</" .. outName .. ">"
				end
			end
		end
	end
	for i = #stack, 1, -1 do
		out[#out + 1] = "</" .. stack[i] .. ">"
	end
	return table.concat(out)
end

-- Wires every .link under `root` to open in the system browser.
function wireLinks(root, beforeOpen)
	for _, link in ipairs(root:QuerySelectorAll(".link")) do
		link:AddEventListener("click", function()
			local href = link:GetAttribute("data-href")
			if href and href ~= "" then
				if beforeOpen then beforeOpen(href) else dew.openUrl(href) end
			end
		end)
	end
end
