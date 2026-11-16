r"""Copy build/mtndew.dll and ElDorito/ui into a test install of the game.

usage: python tools/deploy_test.py [install dir]   (default F:\ElDewrito)

The first run moves the install's own mtndew.dll/.pdb and ui\ aside to *.cef_backup
so the CEF build can be restored; later runs just overwrite.
"""
import os
import shutil
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INSTALL = sys.argv[1] if len(sys.argv) > 1 else r"F:\ElDewrito"


def backup(name):
    path = os.path.join(INSTALL, name)
    saved = path + ".cef_backup"
    if os.path.exists(path) and not os.path.exists(saved):
        os.rename(path, saved)
        print("backed up", path, "->", saved)


def main():
    if not os.path.isfile(os.path.join(INSTALL, "eldorado.exe")):
        sys.exit("not a game install: " + INSTALL)
    for name in ("mtndew.dll", "mtndew.pdb", "ui"):
        backup(name)
    for name in ("mtndew.dll", "mtndew.pdb"):
        shutil.copy2(os.path.join(ROOT, "build", name), os.path.join(INSTALL, name))
    ui = os.path.join(INSTALL, "ui")
    if os.path.isdir(ui):
        shutil.rmtree(ui)
    shutil.copytree(os.path.join(ROOT, "ElDorito", "ui"), ui)
    print("deployed to", INSTALL)


if __name__ == "__main__":
    main()
