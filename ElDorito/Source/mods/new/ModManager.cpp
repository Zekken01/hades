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

_extern void _sub_10791420(ModListenerSet *const);
_inline ModListenerSet::~ModListenerSet() // 0x10791420
{
	mangled_x86(MANGLED_TODO, "??1ModListenerSet@@QAE@XZ");
	// ModListenerSet *const this;
	compiler_generated();
	todo("implement");
	_sub_10791420(this);
}

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
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > path;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > file_name;
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

extern Mod::IClient* _sub_10790F80(Mod::IClient *const);
_inline Mod::IClient::IClient() // 0x10790F80
{
	mangled_x86(MANGLED_TODO, "??0IClient@Mod@@QAE@XZ");
	// Mod::IClient *const this;
	compiler_generated();
	todo("implement");
	_sub_10790F80(this);
}

extern IModManager* _sub_10790FB0(IModManager *const);
_inline IModManager::IModManager() // 0x10790FB0
{
	mangled_x86(MANGLED_TODO, "??0IModManager@@QAE@XZ");
	// IModManager *const this;
	compiler_generated();
	todo("implement");
	_sub_10790FB0(this);
}

extern ModListenerSet* _sub_10790FE0(ModListenerSet *const);
_inline ModListenerSet::ModListenerSet() // 0x10790FE0
{
	mangled_x86(MANGLED_TODO, "??0ModListenerSet@@QAE@XZ");
	// ModListenerSet *const this;
	compiler_generated();
	todo("implement");
	_sub_10790FE0(this);
}

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

_extern void _sub_10791C50(ModManager *const, IModListener *);
void ModManager::AddListener(IModListener *listener) // 0x10791C50
{
	mangled_x86(MANGLED_TODO, "?AddListener@ModManager@@UAEXPAVIModListener@@@Z");
	// IModListener *listener;
	todo("implement");
	_sub_10791C50(this, listener);
}

_extern void _sub_10792040(ModManager *const, IModListener *);
void ModManager::RemoveListener(IModListener *listener) // 0x10792040
{
	mangled_x86(MANGLED_TODO, "?RemoveListener@ModManager@@UAEXPAVIModListener@@@Z");
	// IModListener *listener;
	todo("implement");
	_sub_10792040(this, listener);
}

_extern void _sub_107920B0(ModManager *const);
void ModManager::SetMainThread() // 0x107920B0
{
	mangled_x86(MANGLED_TODO, "?SetMainThread@ModManager@@QAEXXZ");
	// ModManager *const this;
	todo("implement");
	_sub_107920B0(this);
}

_extern bool _sub_10791E10(ModManager const *const);
bool ModManager::IsMainThread() const // 0x10791E10
{
	mangled_x86(MANGLED_TODO, "?IsMainThread@ModManager@@QBE_NXZ");
	// ModManager const *const this;
	todo("implement");
	bool __result = _sub_10791E10((ModManager const *)this);
	return __result;
}

_extern void _sub_107926C0(ModManager *const);
void ModManager::Tick() // 0x107926C0
{
	mangled_x86(MANGLED_TODO, "?Tick@ModManager@@UAEXXZ");
	// ModManager *const this;
	todo("implement");
	_sub_107926C0(this);
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
