"""Compile the RmlUi D3D9 backend shaders into C headers.

usage: python ElDorito/Shaders/Rml/build_shaders.py

Runs fxc.exe from the newest installed Windows 10/11 SDK and writes one header per shader
to ElDorito/Source/Web/Rml/Shaders/.  The headers are committed, so the game never needs
a runtime HLSL compiler; rerun this after editing any .hlsl here.
"""
import glob
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
OUT = os.path.normpath(os.path.join(HERE, "..", "..", "Source", "Web", "Rml", "Shaders"))
SHADERS = [
    ("rml_vs.hlsl", "vs_3_0", "g_rml_vs"),
    ("rml_ps_color.hlsl", "ps_3_0", "g_rml_ps_color"),
    ("rml_ps_texture.hlsl", "ps_3_0", "g_rml_ps_texture"),
    ("rml_ps_gradient.hlsl", "ps_3_0", "g_rml_ps_gradient"),
]


def find_fxc():
    if os.environ.get("FXC"):
        return os.environ["FXC"]
    candidates = sorted(glob.glob(r"C:\Program Files (x86)\Windows Kits\10\bin\10.*\x64\fxc.exe"))
    if not candidates:
        sys.exit("fxc.exe not found; set FXC")
    return candidates[-1]


def main():
    fxc = find_fxc()
    os.makedirs(OUT, exist_ok=True)
    for src, profile, name in SHADERS:
        out = os.path.join(OUT, os.path.splitext(src)[0] + ".h")
        cmd = [fxc, "/nologo", "/T", profile, "/E", "main", "/O3", "/Fh", out, "/Vn", name, os.path.join(HERE, src)]
        print(" ".join(cmd[1:]))
        subprocess.run(cmd, check=True)
    print("wrote", OUT)


if __name__ == "__main__":
    main()
