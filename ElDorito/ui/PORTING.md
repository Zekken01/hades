# Porting web screens to RML/RCSS/Lua

Source of truth: the web UI at `C:\Users\zekken\Desktop\ui`. Each screen becomes
`screens/<id>/index.rml`, `<id>.rcss` and `<id>.lua`, with the same behaviour.

## Shared code (`ui/lib`)
- `dew.lua` — the `dew` table (port of dew.js); promises use `:next(ok, err)`, `:catch`, `:finally`.
- `input.lua` — `dew.input` (port of input.js).
- `jq.lua` — `jq(selector)`: show/hide/fadeIn/fadeOut/text/html/attr/css/addClass/on/...
- `pak_aware.lua` — `pakAwareContext` for `img[data-pak]`.
- `window-resize.rcss` — the scaled 1280x720 `.page_content` (author in `dp` inside it).
- `html.rcss` — browser-like defaults; link it first in every screen.

## RmlUi rules learned the hard way
- Scripts in `<head>` run before `<body>` exists: touch the DOM from `document:AddEventListener("load", ...)`
  or from event handlers.
- Never give an element an id equal to a screen id lookup you rely on (UiRoot does not set document ids).
- Keyframe animations drop their values when they end (no `animation-fill-mode`). For states that must
  persist, use class toggles + `transition`; add the class on the next frame (`dew.requestAnimationFrame`).
- Percentage `max-width` on shrink-to-fit boxes (absolute/float/inline-block with auto width) resolves to 0:
  use a fixed `dp` value computed from the containing block.
- No `calc()`, CSS grid, `clip-path`, `filter`/`backdrop-filter`/`box-shadow`/`mask-image` (not yet), `::before`/
  `::after`, `<progress>`, `zoom`. Use extra elements, flex, and Lua.
- Units: pages scaled by window-resize use `dp`; unscaled pages (root/toasts) use `px`; `vh`/`vw` work.
- `<img src>` accepts PNG/JPG/BMP/TGA/DDS and SVG (rasterised); `<svg src>` and `decorator: svg(...)` draw
  vectors directly. Never convert PNGs to SVG.
- Colours: `rgba()` alpha is 0-255 in RCSS (not 0-1); hex with alpha (`#rrggbbaa`) and `hsl()` work.
- Lua `a and b or c` returns c when b is nil or false: use if/else for handler selection.
- RML is strict XML: close every tag, quote attributes, `&#160;` not `&nbsp;`.
- Never use RmlUi's data-binding attribute names for your own data: `data-for`, `data-if`, `data-visible`,
  `data-value`, `data-checked`, `data-rml`, `data-model`, `data-alias`, `data-attr-*`, `data-class-*`,
  `data-style-*`, `data-event-*`. A `data-for` element silently loses its children.
- Lua element userdata are new objects on every access: never key tables by element or compare elements
  with `==`; put an id or attribute on them instead.
- `<select>`/`<input>` raise "change" for values set from script too (once at once, once on the next
  update). Remember what the page wrote and ignore change events that report it. The select API
  (options, 1-based `selection`) needs `Element.As.ElementFormControlSelect(element)`.
- Setting an input's `value` leaves the caret at 0; the Lua bindings have no selection API, so use
  `dew_core.setSelectionRange(input, start, end)`.
- `document:CreateElement(tag)` returns an owning pointer, not an element: insert it with
  `AppendChild`/`InsertBefore` and use the element those return.
- Input actions (`dew.input`) come from the per-tick "controllerinput" stream; the harness sends it
  only after `ticks 1`, and held keys need `keydown`/`keyup`.

## Testing
`python tools/ui-harness/build_harness.py`, then
`build/ui-harness/ui-harness.exe ElDorito <script>` (see harness_main.cpp for the script ops);
`python tools/deploy_test.py F:\ElDewrito` to try it in the game.
