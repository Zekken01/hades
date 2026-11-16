"""Build mtndew.dll from this tree.

usage: python build.py [--jobs N] [--out DIR] [--no-link] [--only TEXT] [--force] [--no-deps]

Needs Visual Studio 2022 with the MSVC v142 (14.29) x86 toolset, a Windows 10/11 SDK and
CMake (Visual Studio's own is used when none is on PATH); set HADES_VS_ROOT if the install
is not found. Clone with --recursive, or the submodules under libs/src are fetched on the
first build. Before compiling, the libraries built from those submodules (libs/CMakeLists.txt:
Lua, FreeType, lunasvg, RmlUi, mbedTLS, Opus, libdatachannel) are built into libs/ through
CMake when one is missing or the submodules, patches or CMake files changed since the last
deps build (build/deps); --no-deps skips that check. Every .cpp of ElDorito/Source and
blamlib/source is compiled with the flags the shipped binary was built with, and the
objects are linked with the libraries in libs/ into DIR/mtndew.dll (default: build/).

Copy the result over mtndew.dll in an ElDewrito 0.7.2 install to run it.

Flags (measured from the shipped binary, not chosen - changing them changes the code):
  /Od /Ob0 /ZI /GS /RTC1 /MTd /std:c++20; blamlib also /JMC /sdl and strict GS.
Link: dbghelp.dll is delay-loaded; Resources/mtndew.res holds the original's resources
and manifest; Exports.cpp carries its export table. The UI is RmlUi + Lua, which replaced
the CEF browser of the shipped binary.
"""
import argparse
import concurrent.futures
import glob
import hashlib
import os
import shutil
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
TREES = {
    "ElDorito/Source": [],
    # The original blamlib was built under `#pragma strict_gs_check(on)` (hades.h turns it
    # on for HADES_STRICT_GS) with /JMC and /sdl.
    "blamlib/source": ["/JMC", "/sdl", "/D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING", "/DHADES_STRICT_GS"],
}
COMMON = ["/nologo", "/c", "/W0", "/MTd", "/Od", "/Ob0", "/ZI", "/GS", "/RTC1", "/EHsc", "/std:c++20", "/permissive-"]
DEFINES = ["_WINDOWS", "_USRDLL", "WIN32", "_DEBUG", "MINIUPNP_STATICLIB", "NOMINMAX", "_CRT_SECURE_NO_WARNINGS",
           "_WINSOCK_DEPRECATED_NO_WARNINGS", "MATCHING", "RMLUI_STATIC_LIB", "LUNASVG_BUILD_STATIC", "RMLUI_LUA_AS_CXX",
           "RTC_STATIC", "RTC_ENABLE_WEBSOCKET=1", "RTC_ENABLE_MEDIA=1"]
INCLUDES = ["", "ElDorito/Source", "blamlib/source", "libs/boost-1.76/include", "libs/detours/include", "libs/directx/Include", "libs/discord-rpc/include", "libs/fmod/inc",
            "libs/miniupnpc/include", "libs/oggvorbis/include", "libs/openssl-1.1.0e/include", "libs/steam/Include",
            "libs/websocketpp/include", "libs/rmlui/include", "libs/lunasvg/include", "libs/lua-5.4/include", "libs/freetype/include/freetype2", "libs/voip/include"]
THIRD_PARTY = ["detours/lib.X86/detours.lib", "discord-rpc/lib/Debug/discord-rpc.lib",
               "miniupnpc/lib/miniupnpc.lib", "oggvorbis/lib/Debug/ogg.lib", "oggvorbis/lib/Debug/vorbis.lib",
               "oggvorbis/lib/Debug/vorbisfile.lib", "openssl-1.1.0e/lib/libeay32MTd.lib",
               "openssl-1.1.0e/lib/ssleay32MTd.lib", "rmlui/lib/rmlui.lib", "rmlui/lib/rmlui_debugger.lib",
               "rmlui/lib/rmlui_lua.lib", "freetype/lib/freetyped.lib", "lua-5.4/lib/lua.lib",
               "lunasvg/lib/lunasvg.lib", "lunasvg/lib/plutovg.lib",
               # native VoIP
               "voip/lib/datachannel.lib", "voip/lib/juice.lib", "voip/lib/usrsctp.lib", "voip/lib/srtp2.lib",
               "voip/lib/mbedtls.lib", "voip/lib/mbedx509.lib", "voip/lib/mbedcrypto.lib", "voip/lib/everest.lib",
               "voip/lib/p256m.lib", "voip/lib/opus.lib"]
WINDOWS = ("kernel32 user32 gdi32 advapi32 shell32 ole32 oleaut32 uuid ws2_32 winhttp wininet iphlpapi psapi "
           "shlwapi crypt32 winmm dbghelp version comctl32 bcrypt urlmon synchronization dwmapi").split()
# THIRD_PARTY entries that libs/CMakeLists.txt builds from the submodules under libs/src.
BUILT_DEPS = [l for l in THIRD_PARTY if l.split("/")[0] in ("rmlui", "freetype", "lua-5.4", "lunasvg", "voip")]
# The Windows SDK the matching build uses, when it is installed.
SDK = "10.0.22621.0" if os.path.isdir(r"C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0") else ""


def find_vs_root():
    if os.environ.get("HADES_VS_ROOT"):
        return os.environ["HADES_VS_ROOT"]
    for base in (r"C:\Program Files\Microsoft Visual Studio", r"C:\Program Files (x86)\Microsoft Visual Studio"):
        if not os.path.isdir(base):
            continue
        for version in sorted(os.listdir(base), reverse=True):
            vdir = os.path.join(base, version)
            for edition in sorted(os.listdir(vdir)) if os.path.isdir(vdir) else []:
                tools = os.path.join(vdir, edition, "VC", "Tools", "MSVC")
                if os.path.isdir(tools) and any(n.startswith("14.29") for n in os.listdir(tools)):
                    return os.path.join(vdir, edition)
    sys.exit("no Visual Studio with the 14.29 (v142) toolset found; set HADES_VS_ROOT")


def run(vcvars, workdir, command):
    bat = os.path.join(workdir, "run_%d.bat" % (abs(hash(command)) % 10 ** 9))
    with open(bat, "w", newline="") as f:
        f.write('@echo off\r\ncall "%s" x86 %s -vcvars_ver=14.29 >nul 2>&1\r\n%s\r\nexit /b %%errorlevel%%\r\n' % (vcvars, SDK, command))
    try:
        done = subprocess.run(["cmd.exe", "/c", bat], capture_output=True)
    finally:
        os.remove(bat)
    return done.returncode, (done.stdout + done.stderr).decode("utf-8", "replace")


def find_cmake():
    found = shutil.which("cmake")
    if found:
        return found
    for vs in glob.glob(r"C:\Program Files*\Microsoft Visual Studio\2022\*"):
        bundled = os.path.join(vs, "Common7", "IDE", "CommonExtensions", "Microsoft", "CMake", "CMake", "bin", "cmake.exe")
        if os.path.isfile(bundled):
            return bundled
    sys.exit("CMake not found; install it or add it to PATH")


def deps_stamp():
    """What the deps build depends on: the submodule commits, the patches and CMake files."""
    status = subprocess.run(["git", "submodule", "status", "--recursive", "libs/src"], cwd=HERE,
                            capture_output=True, text=True, check=True).stdout
    digest = hashlib.sha1(status.encode())
    inputs = [os.path.join(HERE, "libs", "CMakeLists.txt")] + sorted(
        glob.glob(os.path.join(HERE, "libs", "cmake", "**", "*"), recursive=True) +
        glob.glob(os.path.join(HERE, "libs", "patches", "*")))
    for path in inputs:
        if os.path.isfile(path):
            digest.update(path.encode())
            with open(path, "rb") as f:
                digest.update(f.read())
    return digest.hexdigest()


def ensure_deps(jobs):
    """Build the submodule libraries (libs/CMakeLists.txt) when one is missing or stale."""
    status = subprocess.run(["git", "submodule", "status", "--recursive", "libs/src"], cwd=HERE,
                            capture_output=True, text=True, check=True).stdout
    if any(line.startswith("-") for line in status.splitlines()):  # a submodule is not checked out
        print("fetching submodules")
        # core.longpaths: libdatachannel's nested nlohmann/json has test files past MAX_PATH.
        subprocess.run(["git", "-c", "core.longpaths=true", "submodule", "update", "--init", "--recursive", "--depth", "1"],
                       cwd=HERE, check=True)
    bdir = os.path.join(HERE, "build", "deps")
    stamp_path = os.path.join(bdir, "hades_deps.stamp")
    stamp = deps_stamp()
    old = open(stamp_path).read().strip() if os.path.isfile(stamp_path) else None
    missing = [l for l in BUILT_DEPS if not os.path.isfile(os.path.join(HERE, "libs", l))]
    if old == stamp and not missing:
        return
    if old is not None and old != stamp:
        # ExternalProject does not notice a moved submodule; start the deps build over.
        shutil.rmtree(bdir)
    print("building dependencies -> libs/ (build/deps)")
    cmake = find_cmake()
    env = dict(os.environ, CMAKE_BUILD_PARALLEL_LEVEL=str(jobs))
    subprocess.run([cmake, "-S", os.path.join(HERE, "libs"), "-B", bdir,
                    "-G", "Visual Studio 17 2022", "-A", "Win32", "-T", "v142"], check=True, env=env)
    subprocess.run([cmake, "--build", bdir, "--config", "Debug", "--parallel", "4"], check=True, env=env)
    missing = [l for l in BUILT_DEPS if not os.path.isfile(os.path.join(HERE, "libs", l))]
    if missing:
        sys.exit("the deps build did not produce: " + ", ".join(missing))
    with open(stamp_path, "w") as f:
        f.write(stamp + "\n")


def sources():
    out = []
    for tree, flags in TREES.items():
        root = os.path.join(HERE, tree)
        for r, _d, fs in os.walk(root):
            for f in fs:
                if f.lower().endswith(".cpp"):
                    full = os.path.join(r, f)
                    rel = os.path.relpath(full, HERE).replace("\\", "/")
                    out.append((full, rel, flags))
    return sorted(out, key=lambda x: x[1])


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--jobs", type=int, default=max(1, (os.cpu_count() or 4) // 2))
    ap.add_argument("--out", default=os.path.join(HERE, "build"))
    ap.add_argument("--no-link", action="store_true")
    ap.add_argument("--only", help="compile only sources whose path contains this text (implies --no-link)")
    ap.add_argument("--force", action="store_true", help="recompile even when the object is newer than the source")
    ap.add_argument("--no-deps", action="store_true", help="do not check or build the submodule libraries")
    args = ap.parse_args()
    if args.only:
        args.no_link = True
    if not args.no_deps:
        ensure_deps(args.jobs)
    vcvars = os.path.join(find_vs_root(), "VC", "Auxiliary", "Build", "vcvarsall.bat")
    out = os.path.abspath(args.out)
    objdir = os.path.join(out, "obj")
    os.makedirs(objdir, exist_ok=True)

    srcs = sources()
    if args.only:
        srcs = [s for s in srcs if args.only.replace("\\", "/") in s[1]]
    includes = " ".join('/I"%s"' % os.path.join(HERE, i).rstrip("\\/") for i in INCLUDES)  # a trailing \ would escape the quote
    defines = " ".join("/D" + d for d in DEFINES)

    def compile_one(item):
        full, rel, flags = item
        obj = os.path.join(objdir, rel[:-4].replace("/", "_") + ".obj")
        if not args.force and os.path.isfile(obj) and os.path.getmtime(obj) > os.path.getmtime(full):
            return rel, 0, ""
        cmd = 'cl %s %s %s /Fo"%s" /Fd"%s.pdb" "%s"' % (" ".join(COMMON + flags), defines, includes, obj, obj, full)
        code, text = run(vcvars, objdir, cmd)
        return rel, code, text

    print("compiling %d files with %d jobs -> %s" % (len(srcs), args.jobs, objdir))
    failed = []
    with concurrent.futures.ThreadPoolExecutor(args.jobs) as pool:
        for n, (rel, code, text) in enumerate(pool.map(compile_one, srcs), 1):
            if code:
                failed.append(rel)
                print("FAILED", rel)
                print("\n".join(l for l in text.splitlines() if " error " in l)[:2000])
            if n % 50 == 0:
                print("  %d/%d" % (n, len(srcs)))
    if failed:
        sys.exit("%d file(s) failed to compile" % len(failed))
    if args.no_link:
        return

    libs = os.path.join(HERE, "libs")
    objs = [os.path.join(objdir, rel[:-4].replace("/", "_") + ".obj") for _f, rel, _fl in srcs]
    inputs = objs + [os.path.join(libs, l) for l in THIRD_PARTY] + glob.glob(os.path.join(libs, "directx", "lib.X86", "*.lib"))
    rsp = os.path.join(out, "mtndew.rsp")
    with open(rsp, "w", encoding="utf-8") as f:
        f.write("\n".join('"%s"' % p for p in inputs) + "\n" + "\n".join(w + ".lib" for w in WINDOWS) + "\n")
    dll = os.path.join(out, "mtndew.dll")
    res = os.path.join(HERE, "ElDorito", "Source", "Resources", "mtndew.res")
    cmd = ('link /NOLOGO /DLL /MACHINE:X86 /OUT:"%s" /MAP /DEBUG:FULL /MANIFEST:NO /IGNORE:4099 '
           '/NODEFAULTLIB:libboost_date_time-vc142-mt-sgd-x32-1_76.lib /DELAYLOAD:dbghelp.dll '
           'delayimp.lib "%s" @"%s"' % (dll, res, rsp))
    code, text = run(vcvars, out, cmd)
    if code:
        print("\n".join(l for l in text.splitlines() if "error" in l)[:4000])
        sys.exit("link failed")
    print("built", dll)


if __name__ == "__main__":
    main()
