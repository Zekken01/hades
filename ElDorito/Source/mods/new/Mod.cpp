/* ---------- headers */

#include "mods/new/Mod.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/Cache/StringIdCache.hpp"
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
#include "Common/Threading/WaitEvent.hpp"
#include "Forge/Prefab.hpp"
#include "mods/cache_file_interface.hpp"
#include "mods/cache_file_tag_cache.hpp"
#include "mods/mod_package_cache.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/tag_name_dictionary.hpp"
#include "Patches/CustomPackets.hpp"
#include "Utils/Singleton.hpp"
#include "Web/WebRenderHandlerGpu.hpp"

#include "Utils/Logger.hpp"  // hades: added for 0x1078D6C0

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
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
class Mod;
class WaitEvent;
class c_file_open_scope;
class c_file_reference;
class c_mod_package;
struct ModCache;
struct c_cache_file_interface;
struct lambda_1;

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

// hades: moved from hades/recovered_types.h onto its real base (was hades::polymorphic_bytes)
struct ModCache :
	public c_cache_file_interface
{
	// mangled_x86(MANGLED_KNOWN_GOOD, "??1ModCache@@UAE@XZ"); defaulted on its declaration
	virtual ~ModCache() = default; // 0x1078be40
	virtual std::shared_ptr<Blam::Cache::StringIDCache> get_string_cache() const;
	virtual std::shared_ptr<c_cache_file_tag_cache> get_tag_cache() const;
	std::shared_ptr<Blam::Cache::StringIDCache> m_stringCache; // 0x4
	std::shared_ptr<c_cache_file_tag_cache> m_tagCache; // 0xC
public:
	ModCache() = default;  // hades: defaulted on its declaration (not user-provided), so make_shared value-initializes
};
static_assert32(sizeof(ModCache) == 20, "Invalid ModCache size");

// ModCache is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

//class Mod::Load::__l5::<lambda_1>
//{
//public:
//	void operator()() const;
//	<lambda_1>(Mod::Load::__l5::<lambda_1> &);
//	<lambda_1>(Mod::Load::__l5::<lambda_1> const &);
//	<lambda_1>(Mod *, Ref<Mod> &);
//private:
//	Mod *__this; // 0x0
//	Ref<Mod> _; // 0x4
//public:
//	Mod::Load::__l5::<lambda_1> &operator=(Mod::Load::__l5::<lambda_1> const &);
//	~<lambda_1>(); /* compiler_generated() */
//};
//static_assert(sizeof(Mod::Load::__l5::<lambda_1>) == 8, "Invalid Mod::Load::__l5::<lambda_1> size");

//class Mod::LoadCache::__l7::<lambda_1>
//{
//public:
//	void operator()() const;
//	<lambda_1>(Mod::LoadCache::__l7::<lambda_1> &);
//	<lambda_1>(Mod::LoadCache::__l7::<lambda_1> const &);
//	<lambda_1>(Mod *, __int32 const &, Ref<Mod> &);
//private:
//	Mod *__this; // 0x0
//	__int32 cacheIndex; // 0x4
//	Ref<Mod> _; // 0x8
//public:
//	Mod::LoadCache::__l7::<lambda_1> &operator=(Mod::LoadCache::__l7::<lambda_1> const &);
//	~<lambda_1>(); /* compiler_generated() */
//};
//static_assert(sizeof(Mod::LoadCache::__l7::<lambda_1>) == 12, "Invalid Mod::LoadCache::__l7::<lambda_1> size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

Mod::Mod(Mod::IClient *client, EModIndex index, char const *filename) : m_error((EModResult)1), m_pakLoadEvent(false), m_cacheLoadEvent(false), m_cache(), m_index(index), m_client(client), m_cacheIndex(-1), m_filename(filename) /* hades-mem-init: : m_pakLoadEvent(todo_result<WaitEvent>()), m_cacheLoadEvent(todo_result<WaitEvent>()) */ // 0x1078B5A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0Mod@@QAE@PAVIClient@0@W4EModIndex@@PBD@Z");
	// char const *filename;
}

// mangled_x86(MANGLED_DEFAULT, "??0ModCache@@QAE@XZ"); no body to assert in
// _inline ModCache::ModCache() = default; // 0x1078B730  // hades: defaulted on its declaration

// mangled_x86(MANGLED_DEFAULT, "??0c_cache_file_interface@@QAE@XZ"); no body to assert in

Mod::~Mod() // 0x1078BD60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1Mod@@UAE@XZ");
	// Mod *const this;

	Finish();
}

void Mod::AddRef() // 0x1078C9E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?AddRef@Mod@@UAEXXZ");
	// Mod *const this;

	m_refCount++;
}

void Mod::Release() // 0x1078D920
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Release@Mod@@UAEXXZ");
	// Mod *const this;
	// function call : void *(unsigned __int32)

	if (m_refCount-- == 1)
		delete this;
}

EModIndex Mod::GetIndex() const // 0x1078CE10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetIndex@Mod@@QBE?AW4EModIndex@@XZ");
	// Mod const *const this;

	return m_index;
}

__int32 Mod::GetCacheIndex() const // 0x1078CCD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetCacheIndex@Mod@@QBEHXZ");
	// Mod const *const this;

	return m_cacheIndex;
}

char const *Mod::GetFilename() const // 0x1078CDC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetFilename@Mod@@UBEPBDXZ");
	// Mod const *const this;

	return m_filename.c_str();
}

bool Mod::GetPakIsLoading() const // 0x1078CEC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetPakIsLoading@Mod@@UBE_NXZ");
	// Mod const *const this;

	return !m_pakLoadEvent.Wait(0);
}

bool Mod::GetCacheIsLoading() const // 0x1078CD00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetCacheIsLoading@Mod@@UBE_NXZ");
	// Mod const *const this;

	return !m_cacheLoadEvent.Wait(0);
}

EModResult Mod::GetError() const // 0x1078CD90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetError@Mod@@UBE?AW4EModResult@@XZ");
	// Mod const *const this;

	return m_error;
}

c_mod_package *Mod::GetPak(bool wait) const // 0x1078CE40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetPak@Mod@@UBEPAVc_mod_package@@_N@Z");
	// bool wait;

	if (wait)
	{
		m_pakLoadEvent.Wait(-1);
	}

	return m_pak.get();
}

std::shared_ptr<c_cache_file_interface> Mod::GetCache(bool wait) const // 0x1078CC20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetCache@Mod@@UBE?AV?$shared_ptr@Uc_cache_file_interface@@@std@@_N@Z");
	// bool wait;

	if (wait)
		m_cacheLoadEvent.Wait(-1);
	return m_cache;
}

EModResult Mod::Load(bool async) // 0x1078CF50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Load@Mod@@QAE?AW4EModResult@@_N@Z");
	// bool async;

	#line 272 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\mods\\new\\Mod.cpp"
		assert(m_error == EModResult::kNotLoaded);
		#line 278 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\mods\\new\\Mod.cpp"
	m_pakLoadEvent.Reset();
	m_pak = nullptr;
	m_cache = nullptr;
	if (async)
	{
		return BeginLoadAsync([this, _ = Ref<Mod>(this)]() { LoadPakBlocking(); });
		return kPending;
	}
	else
	{
		return LoadPakBlocking();
	}
}

EModResult Mod::LoadCache(__int32 cacheIndex, bool async) // 0x1078D130
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LoadCache@Mod@@QAE?AW4EModResult@@H_N@Z");
	// bool async;

	if (m_cacheIndex == cacheIndex)
		return m_error;
	m_cacheLoadEvent.Reset();
	m_cache = nullptr;
	m_cacheIndex = cacheIndex;
	if (async)
	{
		return BeginLoadAsync([this, cacheIndex, _ = Ref<Mod>(this)]() { LoadCacheBlocking(cacheIndex); });
	}
	else
	{
		return LoadCacheBlocking(cacheIndex);
	}
}

EModResult Mod::LoadPakBlocking() // 0x1078D6C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LoadPakBlocking@Mod@@AAE?AW4EModResult@@XZ");
	// static ...; // 0x1078D8A0
	// static ...; // 0x1078D89C
	// static ...; // 0x1078D884
	// static ...; // 0x1078D87C
	// Mod *const this;
	// c_mod_package::e_error err;
	// std::unique_ptr<c_mod_package> pak;

	auto pak = std::make_unique<c_mod_package>(m_filename.c_str());
	c_mod_package::e_error err;
	if (!pak->initialize(&err))
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, "Mod::LoadPakBlocking Failed to open mod package '%s'. Error: %s", m_filename.c_str(), c_mod_package::get_error_string(err));
		return FinishLoadPak(kPakLoadFailed);
	}
	m_pak = std::move(pak);
	FinishLoadPak(kSuccess);
	return LoadCache(m_cacheIndex != -1 ? m_cacheIndex : 0, false);
}

EModResult Mod::FinishLoadPak(EModResult error) // 0x1078CB60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FinishLoadPak@Mod@@AAE?AW4EModResult@@W42@@Z");
	// EModResult error;
	// function call : void (Mod *)

	m_error = error;
	m_pakLoadEvent.Set();
	if (error)
	{
		m_cacheLoadEvent.Set();
	}

	m_client->OnModLoadStateChanged(this);
	return error;
}

EModResult Mod::FinishLoadCache(EModResult error) // 0x1078CAB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FinishLoadCache@Mod@@AAE?AW4EModResult@@W42@@Z");
	// EModResult error;
	// function call : void (Mod *)

	m_error = error;
	m_cacheLoadEvent.Set();
	m_client->OnModLoadStateChanged(this);
	return error;
}

// mangled_x86(MANGLED_DEFAULT, "??0IMod@@QAE@XZ"); no body to assert in

EModResult Mod::LoadCacheBlocking(__int32 cacheIndex) // 0x1078D2F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LoadCacheBlocking@Mod@@AAE?AW4EModResult@@H@Z");
	// static ...; // 0x1078D5EE
	// static ...; // 0x1078D5E8
	// static ...; // 0x1078D5C4
	// static ...; // 0x1078D5BC
	// Mod *const this;
	// __int32 cacheIndex;
	// c_file_reference file;
	// std::shared_ptr<ModCache> cache;
	// c_file_open_scope scope;

	m_pakLoadEvent.Wait(4294967295);
	auto cache = std::make_shared<ModCache>();
	auto file = m_pak->get_file();
	c_file_open_scope scope(file, 1);
	cache->m_tagCache = m_pak->open_tag_cache(file, cacheIndex);
	if (!cache->m_tagCache)
		return FinishLoadCache(kCacheLoadFailed);
	cache->m_stringCache = m_pak->open_string_id_cache(file);
	if (!cache->m_stringCache)
		return FinishLoadCache(kCacheLoadFailed);
	m_cache = std::move(cache);
	return FinishLoadCache(kSuccess);
}

void Mod::Finish() // 0x1078CA40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Finish@Mod@@QAEXXZ");
	// Mod *const this;

	m_cacheLoadEvent.Wait(4294967295);
	m_loadThread.detach();
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Ref<Mod>::Ref(Mod *);
template Ref<Mod>::Ref(Ref<Mod> &);
template Ref<Mod>::Ref(Ref<Mod> const &);
template Ref<Mod>::~Ref();

// hades: ModCache's accessors were dropped from the tree (orphaned members); they sit
// at the end of the file so the functions above keep their line numbers.
std::shared_ptr<Blam::Cache::StringIDCache> ModCache::get_string_cache() const // 0x1078E000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_string_cache@ModCache@@UBE?AV?$shared_ptr@UStringIDCache@Cache@Blam@@@std@@XZ");

	return m_stringCache;
}

std::shared_ptr<c_cache_file_tag_cache> ModCache::get_tag_cache() const // 0x1078E080
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?get_tag_cache@ModCache@@UBE?AV?$shared_ptr@Vc_cache_file_tag_cache@@@std@@XZ");

	return m_tagCache;
}
