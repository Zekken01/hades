"""Build the static x86 UI dependencies (Lua 5.4, FreeType, RmlUi) into libs/.

usage: python libs/build_deps.py [--src DIR] [--out DIR] [--jobs N]

The sources are cloned into DIR (default: libs/_deps_src, git-ignored) at pinned tags
unless they are already there.  Everything is built for Win32 with the v142 toolset and
the MultiThreadedDebug CRT, which is what build.py compiles mtndew.dll with (/MTd,
_DEBUG, _ITERATOR_DEBUG_LEVEL=2); a lib built with another CRT fails to link with
LNK2038.  Optimisation is enabled (/O2) because the UI runs in a debug game build;
debug info is embedded (/Z7) so no .pdb files need to travel with the .lib files.

Results:
  libs/lua-5.4/include, libs/lua-5.4/lib/lua.lib      Lua compiled as C++ (so lua_error
                                                       unwinds as a C++ exception)
  libs/freetype/include, libs/freetype/lib/freetyped.lib  internal zlib (WOFF works), no
                                                       png/bzip2/harfbuzz/brotli
  libs/lunasvg/lib/*.lib                               lunasvg + plutovg for RmlUi's SVG plugin
  libs/rmlui/include, libs/rmlui/lib/*.lib             RmlUi core (with the SVG plugin), debugger, Lua plugin
"""
import argparse
import glob
import os
import shutil
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
sys.path.insert(0, ROOT)
import build  # noqa: E402  (find_vs_root, run, SDK)

PINS = {
    "lua": ("https://github.com/lua/lua.git", "v5.4.8"),
    "freetype": ("https://github.com/freetype/freetype.git", "VER-2-13-3"),
    "lunasvg": ("https://github.com/sammycage/lunasvg.git", "v3.5.0"),
    "rmlui": ("https://github.com/mikke89/RmlUi.git", "6.3"),
}
GENERATOR = ["-G", "Visual Studio 17 2022", "-A", "Win32", "-T", "v142"]
CRT = ["-DCMAKE_POLICY_DEFAULT_CMP0091=NEW", "-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDebug",
       "-DBUILD_SHARED_LIBS=OFF", "-DCMAKE_POLICY_VERSION_MINIMUM=3.5",
       "-DCMAKE_C_FLAGS_DEBUG=/Z7 /O2 /Ob1", "-DCMAKE_CXX_FLAGS_DEBUG=/Z7 /O2 /Ob1"]
LUA_SKIP = {"lua.c", "luac.c", "onelua.c", "ltests.c"}
LUA_HEADERS = ["lua.h", "luaconf.h", "lualib.h", "lauxlib.h"]


def sh(args, cwd=None):
    print("+", " ".join(a if " " not in a else '"%s"' % a for a in args), flush=True)
    subprocess.run(args, cwd=cwd, check=True)


def fetch(src):
    for name, (url, tag) in PINS.items():
        dest = os.path.join(src, name)
        if os.path.isdir(os.path.join(dest, ".git")):
            continue
        sh(["git", "clone", "-q", "--depth", "1", "--branch", tag, "--recurse-submodules", "--shallow-submodules", url, dest])


def patch_lunasvg(src):
    """lunasvg 3.5.0 aborts the whole <style> sheet at an empty rule (`.a { }`): every rule
    after it is lost.  buttonhover.svg has one before `.ButtonGlow`, whose fill then falls
    back to black and darkens every hover bar.  Accept empty declaration blocks."""
    path = os.path.join(src, "lunasvg", "source", "svgparser.cpp")
    with open(path, encoding="utf-8") as f:
        text = f.read()
    old = """    skipOptionalSpaces(input);
    do {
        std::string name;
        if(!readCSSIdentifier(input, name))"""
    new = """    skipOptionalSpaces(input);
    while(!input.empty() && input.front() != '}') {
        std::string name;
        if(!readCSSIdentifier(input, name))"""
    old_end = """        skipOptionalSpacesOrDelimiter(input, ';');
    } while(!input.empty() && input.front() != '}');
    return skipDelimiter(input, '}');"""
    new_end = """        skipOptionalSpacesOrDelimiter(input, ';');
    }
    return skipDelimiter(input, '}');"""
    if new in text:
        return
    if old not in text or old_end not in text:
        sys.exit("could not patch " + path)
    with open(path, "w", encoding="utf-8", newline=chr(10)) as f:
        f.write(text.replace(old, new).replace(old_end, new_end))


def replace_once(path, pairs):
    """Apply (old, new) text replacements to path; already-patched files are left alone."""
    with open(path, encoding="utf-8") as f:
        text = f.read()
    changed = text
    for old, new in pairs:
        if new in changed:
            continue
        if old not in changed:
            sys.exit("could not patch " + path)
        changed = changed.replace(old, new, 1)
    if changed != text:
        with open(path, "w", encoding="utf-8", newline=chr(10)) as f:
            f.write(changed)


def patch_rmlui(src):
    """Synthetic bold, like Chromium: a face registered for weight >= 600 whose font file is
    not bold itself (the UI's only font, Conduit ITC, is a single regular face) gets its
    glyph outlines emboldened (FT_GlyphSlot_Embolden, the same em/24 strength Skia uses).
    Without it every font-weight: bold/700 header in the UI rendered at regular weight."""
    base = os.path.join(src, "rmlui", "Source", "Core", "FontEngineDefault")
    replace_once(os.path.join(base, "FreeTypeInterface.h"), [(
        "\tFontFaceHandleFreetype LoadFace(",
        "\t// hades: embolden this face's glyphs when they are built (synthetic bold).\n"
        "\tvoid SetSyntheticBold(FontFaceHandleFreetype face);\n\n"
        "\tFontFaceHandleFreetype LoadFace(")])
    replace_once(os.path.join(base, "FreeTypeInterface.cpp"), [
        ("#include FT_TRUETYPE_TABLES_H\n",
         "#include FT_TRUETYPE_TABLES_H\n#include FT_SYNTHESIS_H\n"),
        ("static FT_Library ft_library = nullptr;\n",
         "static FT_Library ft_library = nullptr;\nstatic char synthetic_bold_tag;\n\n"
         "void FreeType::SetSyntheticBold(FontFaceHandleFreetype face)\n{\n"
         "\treinterpret_cast<FT_Face>(face)->generic.data = &synthetic_bold_tag;\n}\n"),
        ("\terror = FT_Render_Glyph(ft_face->glyph, FT_RENDER_MODE_NORMAL);",
         "\tif (ft_face->generic.data == &synthetic_bold_tag && ft_face->glyph->format == FT_GLYPH_FORMAT_OUTLINE)\n"
         "\t\tFT_GlyphSlot_Embolden(ft_face->glyph);\n\n"
         "\terror = FT_Render_Glyph(ft_face->glyph, FT_RENDER_MODE_NORMAL);"),
    ])
    # Browser semantics for keydown in text fields: it always bubbles.  RmlUi's text widget
    # stopped it for every key it handled (Enter, arrows, Backspace...), so a screen's
    # document-level keydown handler never saw Enter typed in its chat or search box.
    replace_once(os.path.join(src, "rmlui", "Source", "Core", "Elements", "WidgetTextInput.cpp"), [(
        "\t\tif (shift || ctrl || !out_of_bounds || selection_changed)\n\t\t\tevent.StopPropagation();\n",
        "\t\t// hades: keydown keeps bubbling, like in a browser (was: stopped when handled here).\n"
        "\t\t(void)out_of_bounds;\n")])
    # Vertical metrics as Chromium on Windows reads them (DirectWrite, GDI-compatible): the
    # OS/2 win ascent/descent unless the font sets USE_TYPO_METRICS, with the line gap
    # folded in.  FreeType's hhea values put Conduit ITC's baseline 0.138em higher than the
    # CEF UI had it (6px on a page title).
    replace_once(os.path.join(base, "FreeTypeInterface.cpp"), [(
        "\tmetrics.line_spacing = ft_face->size->metrics.height * bitmap_scaling_factor / float(1 << 6);\n",
        "\tmetrics.line_spacing = ft_face->size->metrics.height * bitmap_scaling_factor / float(1 << 6);\n"
        "\tif (const TT_OS2* os2 = static_cast<TT_OS2*>(FT_Get_Sfnt_Table(ft_face, FT_SFNT_OS2));\n"
        "\t\tos2 && os2->version != 0xFFFF && (os2->fsSelection & (1 << 7)) == 0 && os2->usWinAscent + os2->usWinDescent > 0)\n"
        "\t{\n"
        "\t\tconst float scale = bitmap_scaling_factor / float(1 << 6);\n"
        "\t\tconst float win_ascent = FT_MulFix(os2->usWinAscent, ft_face->size->metrics.y_scale) * scale;\n"
        "\t\tconst float win_descent = FT_MulFix(os2->usWinDescent, ft_face->size->metrics.y_scale) * scale;\n"
        "\t\tconst float hhea_height = metrics.line_spacing;\n"
        "\t\tmetrics.ascent = win_ascent;\n"
        "\t\tmetrics.descent = win_descent;\n"
        "\t\tmetrics.line_spacing = win_ascent + win_descent + Math::Max(0.f, hhea_height - (win_ascent + win_descent));\n"
        "\t}\n")])
    # An open <select> list sits above the whole page, like the browser's native popup.  RmlUi
    # gave the box an inline z-index: 1 (a stylesheet cannot raise it) inside whatever stacking
    # context holds the select, so z-index: 2 sliders of later rows drew over it.  While open,
    # the box and every ancestor below the document that has a z-index are raised, then restored.
    elements = os.path.join(src, "rmlui", "Source", "Core", "Elements")
    replace_once(os.path.join(elements, "WidgetDropDown.h"), [(
        "#include \"../../../Include/RmlUi/Core/EventListener.h\"\n",
        "#include \"../../../Include/RmlUi/Core/EventListener.h\"\n"
        "#include \"../../../Include/RmlUi/Core/Property.h\"\n"), (
        "\tbool box_visible = false;\n",
        "\tbool box_visible = false;\n"
        "\t// hades: ancestors raised while the box is open, with their previous inline z-index\n"
        "\tstruct RaisedAncestor { Element* element; bool had_local; Property previous; };\n"
        "\tVector<RaisedAncestor> raised_ancestors;\n")])
    replace_once(os.path.join(elements, "WidgetDropDown.cpp"), [
        ("\tselection_element->SetProperty(PropertyId::ZIndex, Property(1.0f, Unit::NUMBER));\n",
         "\tselection_element->SetProperty(PropertyId::ZIndex, Property(1000000.0f, Unit::NUMBER));\n"),
        ("\tbox_layout_dirty = true;\n\tbox_opened_since_last_format = true;\n\tAttachScrollEvent();\n\n\tbox_visible = true;\n",
         "\tbox_layout_dirty = true;\n\tbox_opened_since_last_format = true;\n\tAttachScrollEvent();\n\n"
         "\tElementDocument* document = parent_element->GetOwnerDocument();\n"
         "\tfor (Element* e = parent_element; e && e != document; e = e->GetParentNode())\n"
         "\t{\n"
         "\t\tif (e->GetComputedValues().z_index().type == Style::ZIndex::Auto)\n"
         "\t\t\tcontinue;\n"
         "\t\tconst PropertyMap& local = e->GetLocalStyleProperties();\n"
         "\t\tauto it = local.find(PropertyId::ZIndex);\n"
         "\t\traised_ancestors.push_back({e, it != local.end(), it != local.end() ? it->second : Property()});\n"
         "\t\te->SetProperty(PropertyId::ZIndex, Property(1000000.0f, Unit::NUMBER));\n"
         "\t}\n\n"
         "\tbox_visible = true;\n"),
        ("\tDetachScrollEvent();\n\n\tbox_visible = false;\n",
         "\tDetachScrollEvent();\n\n"
         "\tfor (auto& raised : raised_ancestors)\n"
         "\t{\n"
         "\t\tif (raised.had_local)\n"
         "\t\t\traised.element->SetProperty(PropertyId::ZIndex, raised.previous);\n"
         "\t\telse\n"
         "\t\t\traised.element->RemoveProperty(PropertyId::ZIndex);\n"
         "\t}\n"
         "\traised_ancestors.clear();\n\n"
         "\tbox_visible = false;\n"),
    ])
    # opacity multiplies down the tree, as in CSS.  RmlUi inherited it as a plain value, so a
    # child with its own opacity (a row faded in by script) stayed fully visible while its
    # screen faded out around it.
    replace_once(os.path.join(src, "rmlui", "Source", "Core", "ElementStyle.cpp"), [(
        "\t\tComputeValue(values, dp_ratio, vp_dimensions, font_size, document_font_size, dirty_font_face_handle, id, property);\n",
        "\t\tComputeValue(values, dp_ratio, vp_dimensions, font_size, document_font_size, dirty_font_face_handle, id, property);\n"
        "\t\tif (id == PropertyId::Opacity && parent_values) // hades: multiplied, as in CSS\n"
        "\t\t\tvalues.opacity(values.opacity() * parent_values->opacity());\n")])
    # A value set by script puts the caret at the end, as in a browser (the console's tab
    # completion and history, chat).  The widget's own edits (typing, deleting, clamping) place
    # the caret themselves; they are flagged so they keep doing that.
    replace_once(os.path.join(elements, "WidgetTextInput.h"), [(
        "\tint absolute_cursor_index;\n",
        "\tint absolute_cursor_index;\n"
        "\tbool hades_internal_value = false; // hades: the value is being set by the widget itself\n")])
    replace_once(os.path.join(elements, "WidgetTextInput.cpp"), [
        ("\t\t// Sanitizer changed the value. Set the attribute with the new value, the current function will be re-entered.\n"
         "\t\tparent->SetAttribute(\"value\", value);\n",
         "\t\t// Sanitizer changed the value. Set the attribute with the new value, the current function will be re-entered.\n"
         "\t\thades_internal_value = true;\n"
         "\t\tparent->SetAttribute(\"value\", value);\n"
         "\t\thades_internal_value = false;\n"),
        ("\t\t\tGetElement()->SetAttribute(\"value\", value);\n",
         "\t\t\thades_internal_value = true;\n"
         "\t\t\tGetElement()->SetAttribute(\"value\", value);\n"
         "\t\t\thades_internal_value = false;\n"),
        ("\tabsolute_cursor_index = new_cursor_attribute_index;\n\tparent->SetAttribute(\"value\", value);\n",
         "\tabsolute_cursor_index = new_cursor_attribute_index;\n"
         "\thades_internal_value = true;\n"
         "\tparent->SetAttribute(\"value\", value);\n"
         "\thades_internal_value = false;\n"),
        ("\t\tGetElement()->SetAttribute(\"value\", new_value);\n",
         "\t\thades_internal_value = true;\n"
         "\t\tGetElement()->SetAttribute(\"value\", new_value);\n"
         "\t\thades_internal_value = false;\n"),
        ("\tSetValueOrPlaceholder(value, GetAttributePlaceholder());\n}\n",
         "\tif (!hades_internal_value)\n"
         "\t{\n"
         "\t\tabsolute_cursor_index = (int)value.size();\n"
         "\t\tcursor_wrap_down = true;\n"
         "\t\tUpdateSelection(false);\n"
         "\t}\n\n"
         "\tSetValueOrPlaceholder(value, GetAttributePlaceholder());\n}\n"),
    ])
    # Spaces between inline tags (`<b>a</b> <i>b</i>`, the console's suggestion gaps) are text,
    # as in HTML.  RmlUi dropped every whitespace-only text node; keep the ones that follow a
    # sibling on the same line (markup indentation always contains a line break).
    replace_once(os.path.join(src, "rmlui", "Source", "Core", "Factory.cpp"), [(
        "\tif (only_white_space)\n\t\treturn true;\n",
        "\tif (only_white_space && (parent->GetNumChildren() == 0 || text.find('\\n') != String::npos || text.find('\\r') != String::npos))\n"
        "\t\treturn true; // hades: keep same-line gaps between inline siblings\n"
        "\tif (only_white_space) // hades: a whitespace-only run vanishes in layout; lead with a zero-width space\n"
        "\t\ttext = \"\\xE2\\x80\\x8B\" + text; // U+200B: no width, not whitespace, so the run is laid out\n")])
    replace_once(os.path.join(base, "FontProvider.cpp"), [(
        "\t\tconst String font_face_description = GetFontFaceDescription(font_family, style, variation_weight);\n",
        "\t\tconst String font_face_description = GetFontFaceDescription(font_family, style, variation_weight);\n"
        "\t\t{\n"
        "\t\t\tFontWeight file_weight = FontWeight::Normal;\n"
        "\t\t\tFreeType::GetFaceStyle(ft_face, nullptr, nullptr, &file_weight);\n"
        "\t\t\tif ((int)variation_weight >= 600 && (int)file_weight < 600)\n"
        "\t\t\t\tFreeType::SetSyntheticBold(ft_face);\n"
        "\t\t}\n")])


def build_lua(vcvars, src, out, jobs):
    srcdir = os.path.join(src, "lua")
    objdir = os.path.join(out, "lua-obj")
    os.makedirs(objdir, exist_ok=True)
    files = sorted(f for f in os.listdir(srcdir) if f.endswith(".c") and f not in LUA_SKIP)
    # /TP compiles the C sources as C++; /EHsc lets ldo.c use throw/catch for lua_error.
    cmd = 'cl /nologo /c /TP /EHsc /W0 /MTd /Z7 /O2 /Ob1 /D_DEBUG /DWIN32 /Fo"%s/" %s' % (
        objdir.replace("\\", "/"), " ".join('"%s"' % os.path.join(srcdir, f) for f in files))
    code, text = build.run(vcvars, objdir, cmd)
    if code:
        print(text)
        sys.exit("lua compile failed")
    libdir = os.path.join(ROOT, "libs", "lua-5.4", "lib")
    incdir = os.path.join(ROOT, "libs", "lua-5.4", "include")
    os.makedirs(libdir, exist_ok=True)
    os.makedirs(incdir, exist_ok=True)
    code, text = build.run(vcvars, objdir, 'lib /nologo /OUT:"%s" "%s/*.obj"' % (os.path.join(libdir, "lua.lib"), objdir.replace("\\", "/")))
    if code:
        print(text)
        sys.exit("lua lib failed")
    for h in LUA_HEADERS:
        shutil.copy(os.path.join(srcdir, h), incdir)
    print("built", os.path.join(libdir, "lua.lib"))


def cmake_build(src, out, prefix, extra, jobs):
    bdir = os.path.join(out, os.path.basename(src))
    sh(["cmake", "-S", src, "-B", bdir] + GENERATOR + CRT + ["-DCMAKE_INSTALL_PREFIX=" + prefix] + extra)
    sh(["cmake", "--build", bdir, "--config", "Debug", "--parallel", str(jobs)])
    sh(["cmake", "--install", bdir, "--config", "Debug"])


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--src", default=os.path.join(HERE, "_deps_src"))
    ap.add_argument("--out", default=os.path.join(ROOT, "build", "deps"))
    ap.add_argument("--jobs", type=int, default=max(1, (os.cpu_count() or 4) - 1))
    args = ap.parse_args()
    os.makedirs(args.src, exist_ok=True)
    os.makedirs(args.out, exist_ok=True)
    fetch(args.src)
    patch_lunasvg(args.src)
    patch_rmlui(args.src)
    vcvars = os.path.join(build.find_vs_root(), "VC", "Auxiliary", "Build", "vcvarsall.bat")

    build_lua(vcvars, args.src, args.out, args.jobs)

    ft_prefix = os.path.join(ROOT, "libs", "freetype")
    cmake_build(os.path.join(args.src, "freetype"), args.out, ft_prefix, [
        "-DFT_DISABLE_ZLIB=ON", "-DFT_DISABLE_BZIP2=ON", "-DFT_DISABLE_PNG=ON",
        "-DFT_DISABLE_HARFBUZZ=ON", "-DFT_DISABLE_BROTLI=ON"], args.jobs)

    # lunasvg (with its plutovg submodule) backs RmlUi's SVG plugin: <svg src> and decorator: svg().
    svg_prefix = os.path.join(ROOT, "libs", "lunasvg")
    cmake_build(os.path.join(args.src, "lunasvg"), args.out, svg_prefix, [
        "-DLUNASVG_BUILD_EXAMPLES=OFF", "-DLUNASVG_DISABLE_LOAD_SYSTEM_FONTS=ON", "-DUSE_SYSTEM_PLUTOVG=OFF"], args.jobs)

    # plutovg's installed config links Threads::Threads without finding it; declare it first.
    threads = os.path.join(args.out, "find_threads.cmake")
    with open(threads, "w") as f:
        f.write("find_package(Threads REQUIRED)\n")

    lua_dir = os.path.join(ROOT, "libs", "lua-5.4")
    cmake_build(os.path.join(args.src, "rmlui"), args.out, os.path.join(ROOT, "libs", "rmlui"), [
        "-DCMAKE_PROJECT_INCLUDE=" + threads.replace("\\", "/"),
        "-DCMAKE_PREFIX_PATH=" + ft_prefix + ";" + svg_prefix,
        "-DLUA_INCLUDE_DIR=" + os.path.join(lua_dir, "include"),
        "-DLUA_LIBRARY=" + os.path.join(lua_dir, "lib", "lua.lib"),
        "-DLUA_LIBRARIES=" + os.path.join(lua_dir, "lib", "lua.lib"),
        "-DRMLUI_LUA_BINDINGS=ON", "-DRMLUI_LUA_BINDINGS_LIBRARY=lua_as_cxx",
        "-DRMLUI_FONT_ENGINE=freetype", "-DRMLUI_SAMPLES=OFF", "-DRMLUI_PRECOMPILED_HEADERS=OFF",
        "-DRMLUI_SVG_PLUGIN=ON", "-DCMAKE_CXX_STANDARD=20"], args.jobs)

    for lib in glob.glob(os.path.join(ROOT, "libs", "rmlui", "lib", "*.lib")) + \
            glob.glob(os.path.join(ft_prefix, "lib", "*.lib")) + glob.glob(os.path.join(svg_prefix, "lib", "*.lib")):
        print("built", lib)


if __name__ == "__main__":
    main()
