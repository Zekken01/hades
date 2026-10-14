#ifndef __STEAM_STEAMLOADER_H__
#define __STEAM_STEAMLOADER_H__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Magnets.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Steam
{
	class SteamLoader;
}

/* ---------- constants */

/* ---------- definitions */

namespace Steam
{
	class SteamLoader
	{
	private:
		HINSTANCE__ *m_hSteamClient; // 0x0
		unsigned __int32 GetSteamProcessId();
		std::string GetSteamDllPath();
		void LoadGameOverlayRenderer(std::string const &baseDllPath);
		void *GetProcAddressInternal(char const *name);
		// hades: the generator recovered no declaration for this member template,
		// so no call site could emit ??$GetProcAddress@...@SteamLoader@Steam@@.
		// It is public: the original decorates it `QAE`, not `AAE`.
	public:
		template<typename t_arg0>
		t_arg0 GetProcAddress(char const *name);
		void Initialize();
		bool IsSteamRunning(bool ignoreCreateFunc);
		void *(*GetCreateInterfaceFunc())(char const *, __int32 *);
	};
}

// static_assert(sizeof(Steam::SteamLoader) == 4, "Invalid Steam::SteamLoader size");
// Withheld: the type inventory does not describe this type, so its
// padding could not be reconstructed.

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __STEAM_STEAMLOADER_H__
