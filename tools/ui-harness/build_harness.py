"""Build tools/ui-harness/ui-harness.exe: the real UI host outside the game.

usage: python tools/ui-harness/build_harness.py

Compiles the UI host sources (Web/WebRenderer.cpp, Web/Rml/*, the bridge registry,
Utils/Uri.cpp) with the same toolset and flags as build.py, plus the harness and its
stand-ins for game functions, and links a console exe into build/ui-harness/.
"""
import glob
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.normpath(os.path.join(HERE, "..", ".."))
sys.path.insert(0, ROOT)
import build  # noqa: E402

TREE_SOURCES = [
    "ElDorito/Source/Web/WebRenderer.cpp",
    "ElDorito/Source/Web/Bridge/WebRendererQueryHandler.cpp",
    "ElDorito/Source/Utils/Uri.cpp",
    "ElDorito/Source/Common/Http/HttpHeaders.cpp",
] + sorted(os.path.relpath(p, ROOT).replace("\\", "/") for p in glob.glob(os.path.join(ROOT, "ElDorito", "Source", "Web", "Rml", "*.cpp")))
HARNESS_SOURCES = ["tools/ui-harness/harness_main.cpp", "tools/ui-harness/harness_stubs.cpp"]
LIBS = ["rmlui/lib/rmlui.lib", "rmlui/lib/rmlui_debugger.lib", "rmlui/lib/rmlui_lua.lib",
        "freetype/lib/freetyped.lib", "lua-5.4/lib/lua.lib", "lunasvg/lib/lunasvg.lib", "lunasvg/lib/plutovg.lib"]
WINDOWS = "kernel32 user32 gdi32 advapi32 shell32 ole32 psapi d3d9 dbghelp".split()


def main():
    vcvars = os.path.join(build.find_vs_root(), "VC", "Auxiliary", "Build", "vcvarsall.bat")
    out = os.path.join(ROOT, "build", "ui-harness")
    objdir = os.path.join(out, "obj")
    os.makedirs(objdir, exist_ok=True)
    includes = " ".join('/I"%s"' % os.path.join(ROOT, i).rstrip("\\/") for i in build.INCLUDES + ["tools/ui-harness"])
    defines = " ".join("/D" + d for d in build.DEFINES)
    objs = []
    failed = False
    for rel in TREE_SOURCES + HARNESS_SOURCES:
        full = os.path.join(ROOT, rel)
        obj = os.path.join(objdir, rel.replace("/", "_")[:-4] + ".obj")
        objs.append(obj)
        if os.path.isfile(obj) and os.path.getmtime(obj) > os.path.getmtime(full) and "--force" not in sys.argv:
            continue
        cmd = 'cl %s %s %s /Fo"%s" /Fd"%s.pdb" "%s"' % (" ".join(build.COMMON), defines, includes, obj, obj, full)
        code, text = build.run(vcvars, objdir, cmd)
        if code:
            failed = True
            print("FAILED", rel)
            print("\n".join(l for l in text.splitlines() if "error" in l.lower())[:3000])
    if failed:
        sys.exit(1)
    libs = " ".join('"%s"' % os.path.join(ROOT, "libs", l) for l in LIBS)
    dx = " ".join('"%s"' % p for p in glob.glob(os.path.join(ROOT, "libs", "directx", "lib.X86", "d3dx9*.lib"))[:1])
    exe = os.path.join(out, "ui-harness.exe")
    cmd = 'link /NOLOGO /MACHINE:X86 /SUBSYSTEM:CONSOLE /DEBUG:FULL /NODEFAULTLIB:libboost_date_time-vc142-mt-sgd-x32-1_76.lib /OUT:"%s" %s %s %s %s /IGNORE:4099' % (
        exe, " ".join('"%s"' % o for o in objs), libs, dx, " ".join(w + ".lib" for w in WINDOWS))
    code, text = build.run(vcvars, out, cmd)
    if code:
        print("\n".join(l for l in text.splitlines() if "error" in l.lower())[:6000])
        sys.exit("link failed")
    print("built", exe)


if __name__ == "__main__":
    main()
