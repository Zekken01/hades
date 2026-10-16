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

#include "mods/mod_system.hpp"  // hades: added for 0x107941D0

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

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const main_game_change_in_progress = reinterpret_cast<char (*)()>(0x5670E0);
}

s_session_mod_options const *network_squad_session_get_mod();  // hades: added for 0x10793FC0
unsigned long system_milliseconds();  // hades: added for 0x10793FC0

extern bool (*const network_session_interface_get_squad_session)(c_network_session **);  // hades: added for 0x10794420
bool network_squad_session_set_mod(s_session_mod_options const *);  // hades: added for 0x10794420

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

ModSessionManager::ModSessionManager(IModManager &modManager) : m_modManager(modManager) // 0x10793CC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0ModSessionManager@@QAE@AAVIModManager@@@Z");

	memset(m_currentPakHash, 0, 20);
	m_modManager.AddListener(this);
	m_lastCheckTime = 0;
	m_valid = false;
}

ModSessionManager::~ModSessionManager() // 0x10793E00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1ModSessionManager@@UAE@XZ");

	m_modManager.RemoveListener(this);
}

void ModSessionManager::Tick() // 0x10794630
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@ModSessionManager@@QAEXXZ");

	CheckSession();
}

void ModSessionManager::CheckSession() // 0x10793FC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CheckSession@ModSessionManager@@AAEXXZ");

	if (eldorado::main_game_change_in_progress())
		return;
	unsigned __int32 currentTime = system_milliseconds();
	if (currentTime - m_lastCheckTime < 10)
		return;
	m_lastCheckTime = currentTime;
	bool valid = false;
	c_network_session *session;
	if (network_session_interface_get_squad_session(&session) && session->established())
	{
		s_session_mod_options const *options = network_squad_session_get_mod();
		if (options && options->valid)
		{
			valid = true;
			if (memcmp(m_currentPakHash, options->hash, sizeof(m_currentPakHash)))
				valid &= HandleSessionModChanged(*options);
		}
	}
	if (m_valid != valid)
	{
		m_valid = valid;
		if (!m_valid)
		{
			memset(m_currentPakHash, 0, sizeof(m_currentPakHash));
			m_modManager.SetMod((EModIndex)0, nullptr, true);
		}
	}
}

// mangled_x86(MANGLED_DEFAULT, "??0IModListener@@QAE@XZ"); no body to assert in

bool ModSessionManager::HandleSessionModChanged(s_session_mod_options const &options) // 0x107941D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HandleSessionModChanged@ModSessionManager@@AAE_NABUs_session_mod_options@@@Z");

	c_mod_package_manager &packageManager = c_mod_system::get_package_manager();
	c_mod_package_manager::s_entry entry;
	if (packageManager.find_package_by_hash(options.hash, &entry))
	{
		memcpy(m_currentPakHash, options.hash, sizeof(m_currentPakHash));
		EModResult result = m_modManager.SetMod((EModIndex)0, entry.file.filename, true);
		return result == kSuccess || result == kPending;
	}
	return false;
}

void ModSessionManager::OnModChanged(EModIndex index, IMod *mod) // 0x10794420
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnModChanged@ModSessionManager@@EAEXW4EModIndex@@PAVIMod@@@Z");

	if (index != 0)
		return;
	c_network_session *session;
	if (!network_session_interface_get_squad_session(&session) || !session->established() || !session->is_host())
		return;
	if (mod)
	{
		c_mod_package *package = mod->GetPak(true);
		if (!package)
			return;
		s_session_mod_options options = {};
		memcpy(options.hash, package->get_header()->sha1, sizeof(options.hash));
		options.valid = true;
		network_squad_session_set_mod(&options);
	}
	else
	{
		s_session_mod_options options = {};
		network_squad_session_set_mod(&options);
	}
}

/* ---------- private code */
