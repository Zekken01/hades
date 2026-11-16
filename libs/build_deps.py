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
