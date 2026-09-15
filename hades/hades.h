#pragma once
#ifndef __HADES_H__
#define __HADES_H__

/* ---------- headers */

// Every generated translation unit includes this as its first header; it is the hook
// for anything the whole reconstruction needs. Keep it small -- it is on the critical
// path of all ~900 first-party translation units.
//
// One umbrella for every binary Hades reconstructs -- mtndew.dll and custom_menu.exe
// both include this, and both recovered headers below are built from all of their
// dumps and type inventories at once (build_recovered_types.py, build_recovered_templates.py,
// --target all). A type recovered for either binary is therefore declared once, in one
// place, and neither tree has to know which binary it belongs to.
//
// The external headers a recovered type is written against -- Windows, DirectX, FMOD,
// OpenSSL, CEF -- come from recovered_types.h, which emits them in the order they have
// to be included in (WinSock2 before Windows, above all). Nothing external belongs here.

#include "hades/reverse_engineering.h"
#include "hades/recovered_early_templates.h"
#include "hades/recovered_types.h"
#include "hades/recovered_templates.h"

#endif // __HADES_H__
