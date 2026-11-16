--[[
	jq.lua -- a small jQuery-style helper for porting the web screens.

		<script src="dew://lib/jq.lua"></script>
		jq("#title"):text("Hello"):show()
		jq(".row"):each(function(el, i) ... end)
		jq(element):fadeIn(200, done)

	Selections hold Rml elements of this screen's document.  Only what the ported
	screens use is here: show/hide/toggle, text/html/attr/css, classes, fades, events.
]]

local Selection = {}
Selection.__index = Selection

-- display value to restore on show(), per element
local savedDisplay = setmetatable({}, { __mode = "k" })
-- element -> pending fade timer id
local fadeTimers = setmetatable({}, { __mode = "k" })

local function wrap(list)
	return setmetatable({ elements = list }, Selection)
end

function jq(target, context)
	if target == nil then
		return wrap({})
	end
	if type(target) == "table" and getmetatable(target) == Selection then
		return target
	end
	if type(target) == "string" then
		local root = context or document
		if target:sub(1, 1) == "#" and not target:find("[%s,.%[:>]", 2) then
			local element = document:GetElementById(target:sub(2))
			return wrap(element and { element } or {})
		end
		local list = {}
		for _, element in ipairs(root:QuerySelectorAll(target)) do
			list[#list + 1] = element
		end
		return wrap(list)
	end
	if type(target) == "table" and target.elements == nil and #target > 0 then
		return wrap(target)
	end
	return wrap({ target })
end

function Selection:each(fn)
	for i, element in ipairs(self.elements) do
		fn(element, i)
	end
	return self
end

function Selection:get(index)
	return self.elements[(index or 0) + 1]
end

function Selection:first()
	return wrap(self.elements[1] and { self.elements[1] } or {})
end

function Selection:length()
	return #self.elements
end

function Selection:find(selector)
	local list = {}
	for _, element in ipairs(self.elements) do
		for _, child in ipairs(element:QuerySelectorAll(selector)) do
			list[#list + 1] = child
		end
	end
	return wrap(list)
end

local function computedDisplay(element)
	local display = element.style.display
	return display ~= nil and display ~= "" and display or "block"
end

local function isHidden(element)
	return element.style.display == "none"
end

local function cancelFade(element)
	local id = fadeTimers[element]
	if id then
		dew.clearTimeout(id)
		fadeTimers[element] = nil
	end
end

function Selection:show(display)
	return self:each(function(element)
		cancelFade(element)
		element.style.opacity = "1"
		if isHidden(element) or display then
			element.style.display = display or savedDisplay[element] or element:GetAttribute("data-display") or "block"
		end
	end)
end

function Selection:hide()
	return self:each(function(element)
		cancelFade(element)
		if not isHidden(element) then
			savedDisplay[element] = computedDisplay(element)
		end
		element.style.display = "none"
	end)
end

function Selection:toggle(visible)
	return self:each(function(element)
		local show = visible
		if show == nil then show = isHidden(element) end
		if show then jq(element):show() else jq(element):hide() end
	end)
end

function Selection:isVisible()
	local element = self.elements[1]
	return element ~= nil and not isHidden(element)
end

-- jQuery fadeIn/fadeOut: opacity transitions; done() runs once, after the last element.
local function fade(self, show, milliseconds, done)
	milliseconds = milliseconds or 400
	local count = #self.elements
	if count == 0 then
		if done then done() end
		return self
	end
	for _, element in ipairs(self.elements) do
		cancelFade(element)
		if show then
			local wasHidden = isHidden(element)
			if wasHidden then
				element.style.transition = "none"
				element.style.opacity = "0"
				element.style.display = savedDisplay[element] or element:GetAttribute("data-display") or "block"
			end
			dew.requestAnimationFrame(function()
				element.style.transition = string.format("opacity %.3fs linear-in-out", milliseconds / 1000)
				element.style.opacity = "1"
			end)
		else
			if not isHidden(element) then
				savedDisplay[element] = computedDisplay(element)
			end
			element.style.transition = string.format("opacity %.3fs linear-in-out", milliseconds / 1000)
			element.style.opacity = "0"
		end
		fadeTimers[element] = dew.setTimeout(function()
			fadeTimers[element] = nil
			if not show then
				element.style.display = "none"
			end
			element.style.transition = "none"
			count = count - 1
			if count == 0 and done then
				done()
			end
		end, milliseconds + 16)
	end
	return self
end

function Selection:fadeIn(milliseconds, done)
	return fade(self, true, milliseconds, done)
end

function Selection:fadeOut(milliseconds, done)
	return fade(self, false, milliseconds, done)
end

function Selection:text(value)
	if value == nil then
		local element = self.elements[1]
		return element and element.inner_rml or ""
	end
	local escaped = dew.escape(tostring(value))
	return self:each(function(element) element.inner_rml = escaped end)
end

function Selection:html(value)
	if value == nil then
		local element = self.elements[1]
		return element and element.inner_rml or ""
	end
	return self:each(function(element) element.inner_rml = tostring(value) end)
end

function Selection:attr(name, value)
	if value == nil then
		local element = self.elements[1]
		return element and element:GetAttribute(name) or nil
	end
	return self:each(function(element) element:SetAttribute(name, tostring(value)) end)
end

function Selection:removeAttr(name)
	return self:each(function(element) element:RemoveAttribute(name) end)
end

function Selection:css(name, value)
	if type(name) == "table" then
		return self:each(function(element)
			for k, v in pairs(name) do element.style[k] = tostring(v) end
		end)
	end
	if value == nil then
		local element = self.elements[1]
		return element and element.style[name] or nil
	end
	return self:each(function(element) element.style[name] = tostring(value) end)
end

function Selection:addClass(names)
	return self:each(function(element)
		for name in tostring(names):gmatch("%S+") do element:SetClass(name, true) end
	end)
end

function Selection:removeClass(names)
	return self:each(function(element)
		for name in tostring(names):gmatch("%S+") do element:SetClass(name, false) end
	end)
end

function Selection:toggleClass(name, state)
	return self:each(function(element)
		local on = state
		if on == nil then on = not element:IsClassSet(name) end
		element:SetClass(name, on)
	end)
end

function Selection:hasClass(name)
	local element = self.elements[1]
	return element ~= nil and element:IsClassSet(name)
end

function Selection:on(event, handler)
	return self:each(function(element)
		element:AddEventListener(event, function(e) handler(e, element) end)
	end)
end

function Selection:click(handler)
	return self:on("click", handler)
end

function Selection:empty()
	return self:each(function(element) element.inner_rml = "" end)
end

function Selection:append(rml)
	return self:each(function(element) element.inner_rml = element.inner_rml .. rml end)
end

function Selection:prepend(rml)
	return self:each(function(element) element.inner_rml = rml .. element.inner_rml end)
end

function Selection:remove()
	return self:each(function(element)
		local parent = element.parent_node
		if parent then parent:RemoveChild(element) end
	end)
end

function Selection:val(value)
	if value == nil then
		local element = self.elements[1]
		return element and (element:GetAttribute("value") or "") or ""
	end
	return self:each(function(element) element:SetAttribute("value", tostring(value)) end)
end
