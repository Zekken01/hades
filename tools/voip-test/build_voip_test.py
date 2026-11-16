"""Build tools/voip-test/peer_test.cpp against libs/voip into build/voip-test/peer_test.exe."""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, ROOT)
import build  # noqa: E402

LIBS = ["datachannel", "juice", "usrsctp", "srtp2", "mbedtls", "mbedx509", "mbedcrypto", "everest", "p256m", "opus"]


def main():
    out = os.path.join(ROOT, "build", "voip-test")
    os.makedirs(out, exist_ok=True)
    vcvars = os.path.join(build.find_vs_root(), "VC", "Auxiliary", "Build", "vcvarsall.bat")
    libdir = os.path.join(ROOT, "libs", "voip", "lib")
    cmd = ('cl /nologo /EHsc /MTd /Z7 /std:c++20 /D_DEBUG /DRTC_STATIC /DRTC_ENABLE_WEBSOCKET=1 /DRTC_ENABLE_MEDIA=1 '
           '/Fo"%s/" /I"%s" "%s" /Fe"%s" /link %s ws2_32.lib iphlpapi.lib bcrypt.lib advapi32.lib') % (
        out.replace("\\", "/"), os.path.join(ROOT, "libs", "voip", "include"), os.path.join(HERE, "peer_test.cpp"),
        os.path.join(out, "peer_test.exe"), " ".join('"%s"' % os.path.join(libdir, l + ".lib") for l in LIBS))
    code, text = build.run(vcvars, out, cmd)
    print(text)
    sys.exit(code)


if __name__ == "__main__":
    main()
