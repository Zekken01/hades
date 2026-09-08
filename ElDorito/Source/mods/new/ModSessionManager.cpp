/* ---------- headers */

#include "mods/new/ModSessionManager.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/networking/session/network_session.hpp"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/networking/session/network_session_parameter_mod.hpp"
#include "Blam/networking/session/network_session_parameters_base.hpp"
#include "Blam/networking/session/network_session_parameters_custom.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <list>
#include <mutex>
#include <ratio>
#include <stdexcept>
#include <stop_token>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class IMod;
class IModListener;
class IModManager;
class ModSessionManager;
class c_mod_package;
class c_mod_package_manager;
class c_network_session;
struct s_session_mod_options;

namespace Utils {}
using namespace ::Utils;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

extern ModSessionManager* _sub_10793CC0(ModSessionManager *const, IModManager &);
ModSessionManager::ModSessionManager(IModManager &modManager) : m_modManager(modManager) // 0x10793CC0
{
	mangled_x86(MANGLED_TODO, "??0ModSessionManager@@QAE@AAVIModManager@@@Z");
	// IModManager &modManager;
	// function call : void (IModListener *)
	todo("implement");
	_sub_10793CC0(this, modManager);
}

_extern void _sub_10793E00(ModSessionManager *const);
ModSessionManager::~ModSessionManager() // 0x10793E00
{
	mangled_x86(MANGLED_TODO, "??1ModSessionManager@@UAE@XZ");
	// ModSessionManager *const this;
	// function call : void (IModListener *)
	todo("implement");
	_sub_10793E00(this);
}

_extern void _sub_10794630(ModSessionManager *const);
void ModSessionManager::Tick() // 0x10794630
{
	mangled_x86(MANGLED_TODO, "?Tick@ModSessionManager@@QAEXXZ");
	// ModSessionManager *const this;
	todo("implement");
	_sub_10794630(this);
}

_extern void _sub_10793FC0(ModSessionManager *const);
void ModSessionManager::CheckSession() // 0x10793FC0
{
	mangled_x86(MANGLED_TODO, "?CheckSession@ModSessionManager@@AAEXXZ");
	// static ...; // 0x10794154
	// static ...; // 0x10794148
	// static ...; // 0x10794140
	// ModSessionManager *const this;
	// unsigned __int32 currentTime;
	// bool valid;
	// c_network_session *session;
	{
		// s_session_mod_options const *options;
	}
	// function call : char (*const)()
	// function call : bool (*const)(c_network_session **)
	// function call : EModResult (EModIndex, char const *, bool)
	todo("implement");
	_sub_10793FC0(this);
}

// mangled_x86(MANGLED_DEFAULT, "??0IModListener@@QAE@XZ"); no body to assert in
_inline IModListener::IModListener() = default; // 0x10793C90

_extern bool _sub_107941D0(ModSessionManager *const, s_session_mod_options const &);
bool ModSessionManager::HandleSessionModChanged(s_session_mod_options const &options) // 0x107941D0
{
	mangled_x86(MANGLED_TODO, "?HandleSessionModChanged@ModSessionManager@@AAE_NABUs_session_mod_options@@@Z");
	// static ...; // 0x1079435C
	// static ...; // 0x10794354
	// ModSessionManager *const this;
	// s_session_mod_options const &options;
	// c_mod_package_manager &packageManager;
	// c_mod_package_manager::s_entry entry;
	{
		// EModResult result;
	}
	// function call : EModResult (EModIndex, char const *, bool)
	todo("implement");
	bool __result = _sub_107941D0(this, options);
	return __result;
}

_extern void _sub_10794420(ModSessionManager *const, EModIndex, IMod *);
void ModSessionManager::OnModChanged(EModIndex index, IMod *mod) // 0x10794420
{
	mangled_x86(MANGLED_TODO, "?OnModChanged@ModSessionManager@@EAEXW4EModIndex@@PAVIMod@@@Z");
	// static ...; // 0x10794590
	// static ...; // 0x1079456C
	// static ...; // 0x10794564
	// ModSessionManager *const this;
	// EModIndex index;
	// IMod *mod;
	// c_network_session *session;
	{
		// s_session_mod_options options;
		// c_mod_package *package;
	}
	{
	}
	// function call : bool (*const)(c_network_session **)
	// function call : c_mod_package *(bool) const
	todo("implement");
	_sub_10794420(this, index, mod);
}

/* ---------- private code */
