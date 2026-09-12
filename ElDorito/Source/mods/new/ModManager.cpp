/* ---------- headers */

#include "mods/new/ModManager.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/RefCounting.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/new/Mod.hpp"
#include "mods/new/ModListenerSet.hpp"
#include "mods/new/ModSessionManager.hpp"
#include "mods/tag_name_dictionary.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <ratio>
#include <shared_mutex>
#include <stdexcept>
#include <stop_token>
#include <string>
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
class Mod;
class ModListenerSet;
class ModManager;
class ModSessionManager;
class c_mod_package_manager;

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

extern ModManager* _sub_10791060(ModManager *const);
ModManager::ModManager() : m_sessionManager(todo_result<ModSessionManager>()) // 0x10791060
{
	mangled_x86(MANGLED_TODO, "??0ModManager@@QAE@XZ");
	// ModManager *const this;
	todo("implement");
	_sub_10791060(this);
}

// mangled_x86(MANGLED_DEFAULT, "??1ModListenerSet@@QAE@XZ"); no body to assert in
_inline ModListenerSet::~ModListenerSet() = default; // 0x10791420

_extern void _sub_10791490(ModManager *const);
ModManager::~ModManager() // 0x10791490
{
	mangled_x86(MANGLED_TODO, "??1ModManager@@UAE@XZ");
	// ModManager *const this;
	todo("implement");
	_sub_10791490(this);
}

extern EModResult _sub_10792110(ModManager *const, EModIndex, char const *, bool);
EModResult ModManager::SetMod(EModIndex index, char const *filename, bool async) // 0x10792110
{
	mangled_x86(MANGLED_TODO, "?SetMod@ModManager@@UAE?AW4EModResult@@W4EModIndex@@PBD_N@Z");
	// static ...; // 0x10792410
	// static ...; // 0x10792408
	// ModManager *const this;
	// EModIndex index;
	// char const *filename;
	// bool async;
	// Mod const *oldMod;
	// EModResult result;
	{
		// std::string path;
		// std::string file_name;
		// Ref<Mod> mod;
		// c_mod_package_manager &package_manager;
		// unsigned __int32 lastSeparatorIndex;
	}
	// function call : char const *() const
	// function call : EModResult () const
	todo("implement");
	EModResult __result = _sub_10792110(this, index, filename, async);
	return __result;
}

// mangled_x86(MANGLED_DEFAULT, "??0IClient@Mod@@QAE@XZ"); no body to assert in
_inline Mod::IClient::IClient() = default; // 0x10790F80

// mangled_x86(MANGLED_DEFAULT, "??0IModManager@@QAE@XZ"); no body to assert in
_inline IModManager::IModManager() = default; // 0x10790FB0

// mangled_x86(MANGLED_DEFAULT, "??0ModListenerSet@@QAE@XZ"); no body to assert in
_inline ModListenerSet::ModListenerSet() = default; // 0x10790FE0

extern EModResult _sub_10792520(ModManager *const, EModIndex, __int32, bool);
EModResult ModManager::SetModCache(EModIndex index, __int32 cacheIndex, bool async) // 0x10792520
{
	mangled_x86(MANGLED_TODO, "?SetModCache@ModManager@@UAE?AW4EModResult@@W4EModIndex@@H_N@Z");
	// ModManager *const this;
	// EModIndex index;
	// __int32 cacheIndex;
	// bool async;
	// EModResult result;
	{
		// Mod *mod;
	}
	// function call : EModResult () const
	todo("implement");
	EModResult __result = _sub_10792520(this, index, cacheIndex, async);
	return __result;
}

extern Ref<IMod> _sub_10791D90(ModManager const *const, EModIndex);
Ref<IMod> ModManager::GetModShared(EModIndex index) const // 0x10791D90
{
	mangled_x86(MANGLED_TODO, "?GetModShared@ModManager@@UBE?AV?$Ref@VIMod@@@@W4EModIndex@@@Z");
	// EModIndex index;
	todo("implement");
	Ref<IMod> __result = _sub_10791D90((ModManager const *)this, index);
	return __result;
}

extern IMod *_sub_10791CF0(ModManager const *const, EModIndex);
IMod *ModManager::GetMod(EModIndex index) const // 0x10791CF0
{
	mangled_x86(MANGLED_TODO, "?GetMod@ModManager@@UBEPAVIMod@@W4EModIndex@@@Z");
	// EModIndex index;
	todo("implement");
	IMod * __result = _sub_10791CF0((ModManager const *)this, index);
	return __result;
}

void ModManager::AddListener(IModListener *listener) // 0x10791C50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?AddListener@ModManager@@UAEXPAVIModListener@@@Z");
	// IModListener *listener;

	m_listeners.Add(listener);
}

void ModManager::RemoveListener(IModListener *listener) // 0x10792040
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RemoveListener@ModManager@@UAEXPAVIModListener@@@Z");
	// IModListener *listener;

	m_listeners.Remove(listener);
}

void ModManager::SetMainThread() // 0x107920B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SetMainThread@ModManager@@QAEXXZ");
	// ModManager *const this;

	m_mainThreadId = std::this_thread::get_id();
}

bool ModManager::IsMainThread() const // 0x10791E10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?IsMainThread@ModManager@@QBE_NXZ");
	// ModManager const *const this;

	return std::this_thread::get_id() == m_mainThreadId;
}

void ModManager::Tick() // 0x107926C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@ModManager@@UAEXXZ");
	// ModManager *const this;

	m_sessionManager.Tick();
}

_extern void _sub_10791EA0(Mod::IClient * const, Mod *);
void ModManager::OnModLoadStateChanged(Mod *mod) // 0x10791EA0
{
	mangled_x86(MANGLED_TODO, "?OnModLoadStateChanged@ModManager@@EAEXPAVMod@@@Z");
	// __shifted(ModManager, 4);
	// Mod *mod;
	todo("implement");
	_sub_10791EA0((Mod::IClient *)this, mod);
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Mod * Ref<Mod>::Get() const;
template Mod * Ref<Mod>::operator->() const;
template Ref<Mod> & Ref<Mod>::operator=(Mod *);
template Ref<Mod> & Ref<Mod>::operator=(Ref<Mod> const &);
template Ref<Mod>::Ref();
template Ref<Mod>::operator Mod *() const;
