"""Build the static x86 VoIP dependencies (mbedTLS, Opus, libdatachannel) into libs/voip/.

usage: python libs/build_voip_deps.py [--src DIR] [--out DIR] [--jobs N]

Same conventions as build_deps.py: sources cloned at pinned tags into DIR (default
libs/_deps_src), Win32 / v142 / MultiThreadedDebug CRT, /O2 with embedded debug info.

  mbedTLS        TLS/DTLS for libdatachannel (the tree's OpenSSL 1.1.0e is too old for it);
                 built with MBEDTLS_SSL_DTLS_SRTP, which WebRTC media needs.
  Opus           the voice codec (48 kHz, what browsers negotiate for WebRTC audio).
  libdatachannel WebRTC peer connections, data channels and the WebSocket client used for the
                 signaling server (bundles libjuice, usrsctp, libsrtp and plog).

Results: libs/voip/include, libs/voip/lib/*.lib
"""
import argparse
import glob
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)

PINS = {
    "mbedtls": ("https://github.com/Mbed-TLS/mbedtls.git", "v3.6.5"),
    "opus": ("https://github.com/xiph/opus.git", "v1.5.2"),
    "libdatachannel": ("https://github.com/paullouisageneau/libdatachannel.git", "v0.24.6"),
}
GENERATOR = ["-G", "Visual Studio 17 2022", "-A", "Win32", "-T", "v142"]
CRT = ["-DCMAKE_POLICY_DEFAULT_CMP0091=NEW", "-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDebug",
       "-DBUILD_SHARED_LIBS=OFF", "-DCMAKE_POLICY_VERSION_MINIMUM=3.5",
       "-DCMAKE_C_FLAGS_DEBUG=/Z7 /O2 /Ob1", "-DCMAKE_CXX_FLAGS_DEBUG=/Z7 /O2 /Ob1",
       "-DCMAKE_BUILD_TYPE=Debug"]


def sh(args, cwd=None):
    print("+", " ".join(a if " " not in a else '"%s"' % a for a in args), flush=True)
    subprocess.run(args, cwd=cwd, check=True)


def fetch(src):
    for name, (url, tag) in PINS.items():
        dest = os.path.join(src, name)
        if os.path.isdir(os.path.join(dest, ".git")):
            continue
        sh(["git", "clone", "-q", "--depth", "1", "--branch", tag, "--recurse-submodules",
            "--shallow-submodules", url, dest])


def enable_dtls_srtp(src):
    path = os.path.join(src, "mbedtls", "include", "mbedtls", "mbedtls_config.h")
    with open(path, encoding="utf-8") as f:
        text = f.read()
    patched = re.sub(r"^//\s*#define MBEDTLS_SSL_DTLS_SRTP\b", "#define MBEDTLS_SSL_DTLS_SRTP", text, flags=re.M)
    if "\n#define MBEDTLS_SSL_DTLS_SRTP" not in patched:
        sys.exit("could not enable MBEDTLS_SSL_DTLS_SRTP in " + path)
    if patched != text:
        with open(path, "w", encoding="utf-8", newline="\n") as f:
            f.write(patched)


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
    enable_dtls_srtp(args.src)

    prefix = os.path.join(ROOT, "libs", "voip")
    cmake_build(os.path.join(args.src, "mbedtls"), args.out, prefix, [
        "-DENABLE_PROGRAMS=OFF", "-DENABLE_TESTING=OFF", "-DMBEDTLS_FATAL_WARNINGS=OFF"], args.jobs)

    # opus picks its CRT from OPUS_STATIC_RUNTIME, not CMAKE_MSVC_RUNTIME_LIBRARY
    cmake_build(os.path.join(args.src, "opus"), args.out, prefix, [
        "-DOPUS_BUILD_PROGRAMS=OFF", "-DOPUS_BUILD_TESTING=OFF", "-DOPUS_INSTALL_PKG_CONFIG_MODULE=OFF",
        "-DOPUS_STATIC_RUNTIME=ON"], args.jobs)

    cmake_build(os.path.join(args.src, "libdatachannel"), args.out, prefix, [
        "-DUSE_MBEDTLS=ON", "-DUSE_NICE=OFF", "-DNO_EXAMPLES=ON", "-DNO_TESTS=ON",
        "-DCMAKE_PREFIX_PATH=" + prefix, "-DMbedTLS_ROOT=" + prefix,
        "-DCMAKE_CXX_STANDARD=20"], args.jobs)

    for lib in sorted(glob.glob(os.path.join(prefix, "lib", "*.lib"))):
        print("built", lib)


if __name__ == "__main__":
    main()
