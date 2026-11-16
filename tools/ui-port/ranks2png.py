"""Rasterise the rank icons (tools/ui-port/sources/ranks/<n>.svg) to
ElDorito/ui/assets/ranks/<n>.png at 4x their intrinsic size.

The game decodes UI images with D3DX (no SVG), so the vector ranks ship as PNGs.
usage: python tools/ui-port/ranks2png.py   (needs: pip install resvg-py)
"""
from pathlib import Path

import resvg_py

ROOT = Path(__file__).resolve().parents[2]
SRC = ROOT / "tools" / "ui-port" / "sources" / "ranks"
DST = ROOT / "ElDorito" / "ui" / "assets" / "ranks"
ZOOM = 4

for svg in sorted(SRC.glob("*.svg"), key=lambda p: int(p.stem) if p.stem.isdigit() else p.stem):
    png = DST / (svg.stem + ".png")
    png.write_bytes(bytes(resvg_py.svg_to_bytes(svg_path=str(svg), zoom=ZOOM)))
    print(png.relative_to(ROOT))
