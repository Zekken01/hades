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

#include "mods/mod_system.hpp"  // hades: added for 0x10792110

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

template<typename Method, typename ...Args> void Notify(Method &&method, Args &&...args);

/* ---------- private variables */

/* ---------- public code */

ModManager::ModManager() : m_sessionManager(*this) /* hades-mem-init: : m_sessionManager(todo_result<ModSessionManager>()) */ // 0x10791060
{
}

_inline ModListenerSet::~ModListenerSet() = default; // 0x10791420

ModManager::~ModManager() // 0x10791490
{
}

#line 114
EModResult ModManager::SetMod(EModIndex index, char const *filename, bool async) // 0x10792110
{
#line 132

	#line 116 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\new\\ModManager.cpp"
		assert(IsMainThread());
		#line 136 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\new\\ModManager.cpp"
	EModResult result = kUnknownError;
	Mod const *oldMod = m_mods[index];
	if (!filename)
	{
		if (!oldMod)
			return kSuccess;
		m_mods[index] = nullptr;
		result = kSuccess;
	}
	else
	{
		if (oldMod && !strcmp(oldMod->GetFilename(), filename) && oldMod->GetError() == kSuccess)
			return kSuccess;
		Ref<Mod> const mod = new Mod(this, index, filename);
		m_mods[index] = mod;
		result = mod->Load(async && true);
		c_mod_package_manager &package_manager = c_mod_system::get_package_manager();
		std::string path = filename;
		unsigned __int32 lastSeparatorIndex = path.find_last_of("\\");
		std::string file_name = path.substr(lastSeparatorIndex + 1);
		package_manager.touch_package(file_name.c_str());
	}
	m_listeners.Notify(&IModListener::OnModChanged, index, m_mods[index]);
	return result;
}

EModResult ModManager::SetModCache(EModIndex index, __int32 cacheIndex, bool async) // 0x10792520
{
#line 178

	#line 170 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\new\\ModManager.cpp"
		assert(IsMainThread());
		#line 182 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\new\\ModManager.cpp"
	EModResult result = kUnknownError;
	if (Mod *mod = m_mods[index])
	{
		if (mod->GetCacheIndex() == cacheIndex)
		{
			return mod->GetError();
		}

		result = mod->LoadCache(cacheIndex, async && true);
		m_listeners.Notify(&IModListener::OnModCacheChanged, index, mod);
	}
	else
	{
		result = kNoModSet;
	}

	return result;
}

Ref<IMod> ModManager::GetModShared(EModIndex index) const // 0x10791D90
{
	return m_mods[index];
}

#line 209
IMod *ModManager::GetMod(EModIndex index) const // 0x10791CF0
{
#line 213

	#line 212 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\new\\ModManager.cpp"
		assert(IsMainThread() && "Use GetModShared() for threads other than the main thread");
		#line 217 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\new\\ModManager.cpp"
	return m_mods[index].Get();
}

void ModManager::AddListener(IModListener *listener) // 0x10791C50
{
	m_listeners.Add(listener);
}

void ModManager::RemoveListener(IModListener *listener) // 0x10792040
{
	m_listeners.Remove(listener);
}

void ModManager::SetMainThread() // 0x107920B0
{
	m_mainThreadId = std::this_thread::get_id();
}

bool ModManager::IsMainThread() const // 0x10791E10
{
	return std::this_thread::get_id() == m_mainThreadId;
}

void ModManager::Tick() // 0x107926C0
{
	m_sessionManager.Tick();
}

void ModManager::OnModLoadStateChanged(Mod *mod) // 0x10791EA0
{
	m_listeners.Notify(&IModListener::OnModLoadStateChangedAsync, mod->GetIndex(), mod);
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
