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

extern Mod* _sub_1078B5A0(Mod *const, Mod::IClient *, EModIndex, char const *);
Mod::Mod(Mod::IClient *client, EModIndex index, char const *filename) : m_pakLoadEvent(todo_result<WaitEvent>()), m_cacheLoadEvent(todo_result<WaitEvent>()) // 0x1078B5A0
{
	mangled_x86(MANGLED_TODO, "??0Mod@@QAE@PAVIClient@0@W4EModIndex@@PBD@Z");
	// char const *filename;
	todo("implement");
	_sub_1078B5A0(this, client, index, filename);
}

// mangled_x86(MANGLED_DEFAULT, "??0ModCache@@QAE@XZ"); no body to assert in
_inline ModCache::ModCache() = default; // 0x1078B730

// mangled_x86(MANGLED_DEFAULT, "??0c_cache_file_interface@@QAE@XZ"); no body to assert in
_inline c_cache_file_interface::c_cache_file_interface() = default; // 0x1078B7B0

_extern void _sub_1078BD60(Mod *const);
Mod::~Mod() // 0x1078BD60
{
	mangled_x86(MANGLED_TODO, "??1Mod@@UAE@XZ");
	// Mod *const this;
	todo("implement");
	_sub_1078BD60(this);
}

_inline ModCache::~ModCache() // 0x1078BE40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1ModCache@@UAE@XZ");
	// ModCache *const this;

	compiler_generated();
}

_extern void _sub_1078C9E0(Mod *const);
void Mod::AddRef() // 0x1078C9E0
{
	mangled_x86(MANGLED_TODO, "?AddRef@Mod@@UAEXXZ");
	// Mod *const this;
	todo("implement");
	_sub_1078C9E0(this);
}

_extern void _sub_1078D920(Mod *const);
void Mod::Release() // 0x1078D920
{
	mangled_x86(MANGLED_TODO, "?Release@Mod@@UAEXXZ");
	// Mod *const this;
	// function call : void *(unsigned __int32)
	todo("implement");
	_sub_1078D920(this);
}

extern EModIndex _sub_1078CE10(Mod const *const);
EModIndex Mod::GetIndex() const // 0x1078CE10
{
	mangled_x86(MANGLED_TODO, "?GetIndex@Mod@@QBE?AW4EModIndex@@XZ");
	// Mod const *const this;
	todo("implement");
	EModIndex __result = _sub_1078CE10((Mod const *)this);
	return __result;
}

_extern __int32 _sub_1078CCD0(Mod const *const);
__int32 Mod::GetCacheIndex() const // 0x1078CCD0
{
	mangled_x86(MANGLED_TODO, "?GetCacheIndex@Mod@@QBEHXZ");
	// Mod const *const this;
	todo("implement");
	__int32 __result = _sub_1078CCD0((Mod const *)this);
	return __result;
}

extern char const *_sub_1078CDC0(Mod const *const);
char const *Mod::GetFilename() const // 0x1078CDC0
{
	mangled_x86(MANGLED_TODO, "?GetFilename@Mod@@UBEPBDXZ");
	// Mod const *const this;
	todo("implement");
	char const * __result = _sub_1078CDC0((Mod const *)this);
	return __result;
}

_extern bool _sub_1078CEC0(Mod const *const);
bool Mod::GetPakIsLoading() const // 0x1078CEC0
{
	mangled_x86(MANGLED_TODO, "?GetPakIsLoading@Mod@@UBE_NXZ");
	// Mod const *const this;
	todo("implement");
	bool __result = _sub_1078CEC0((Mod const *)this);
	return __result;
}

_extern bool _sub_1078CD00(Mod const *const);
bool Mod::GetCacheIsLoading() const // 0x1078CD00
{
	mangled_x86(MANGLED_TODO, "?GetCacheIsLoading@Mod@@UBE_NXZ");
	// Mod const *const this;
	todo("implement");
	bool __result = _sub_1078CD00((Mod const *)this);
	return __result;
}

extern EModResult _sub_1078CD90(Mod const *const);
EModResult Mod::GetError() const // 0x1078CD90
{
	mangled_x86(MANGLED_TODO, "?GetError@Mod@@UBE?AW4EModResult@@XZ");
	// Mod const *const this;
	todo("implement");
	EModResult __result = _sub_1078CD90((Mod const *)this);
	return __result;
}

extern c_mod_package *_sub_1078CE40(Mod const *const, bool);
c_mod_package *Mod::GetPak(bool wait) const // 0x1078CE40
{
	mangled_x86(MANGLED_TODO, "?GetPak@Mod@@UBEPAVc_mod_package@@_N@Z");
	// bool wait;
	todo("implement");
	c_mod_package * __result = _sub_1078CE40((Mod const *)this, wait);
	return __result;
}

extern std::shared_ptr<c_cache_file_interface> _sub_1078CC20(Mod const *const, bool);
std::shared_ptr<c_cache_file_interface> Mod::GetCache(bool wait) const // 0x1078CC20
{
	mangled_x86(MANGLED_TODO, "?GetCache@Mod@@UBE?AV?$shared_ptr@Uc_cache_file_interface@@@std@@_N@Z");
	// bool wait;
	todo("implement");
	std::shared_ptr<c_cache_file_interface> __result = _sub_1078CC20((Mod const *)this, wait);
	return __result;
}

extern EModResult _sub_1078CF50(Mod *const, bool);
EModResult Mod::Load(bool async) // 0x1078CF50
{
	mangled_x86(MANGLED_TODO, "?Load@Mod@@QAE?AW4EModResult@@_N@Z");
	// bool async;
	{
	}
	todo("implement");
	EModResult __result = _sub_1078CF50(this, async);
	return __result;
}

extern EModResult _sub_1078D130(Mod *const, __int32, bool);
EModResult Mod::LoadCache(__int32 cacheIndex, bool async) // 0x1078D130
{
	mangled_x86(MANGLED_TODO, "?LoadCache@Mod@@QAE?AW4EModResult@@H_N@Z");
	// bool async;
	{
	}
	todo("implement");
	EModResult __result = _sub_1078D130(this, cacheIndex, async);
	return __result;
}

extern EModResult _sub_1078D6C0(Mod *const);
EModResult Mod::LoadPakBlocking() // 0x1078D6C0
{
	mangled_x86(MANGLED_TODO, "?LoadPakBlocking@Mod@@AAE?AW4EModResult@@XZ");
	// static ...; // 0x1078D8A0
	// static ...; // 0x1078D89C
	// static ...; // 0x1078D884
	// static ...; // 0x1078D87C
	// Mod *const this;
	// c_mod_package::e_error err;
	// std::unique_ptr<c_mod_package> pak;
	todo("implement");
	EModResult __result = _sub_1078D6C0(this);
	return __result;
}

extern EModResult _sub_1078CB60(Mod *const, EModResult);
EModResult Mod::FinishLoadPak(EModResult error) // 0x1078CB60
{
	mangled_x86(MANGLED_TODO, "?FinishLoadPak@Mod@@AAE?AW4EModResult@@W42@@Z");
	// EModResult error;
	// function call : void (Mod *)
	todo("implement");
	EModResult __result = _sub_1078CB60(this, error);
	return __result;
}

extern EModResult _sub_1078CAB0(Mod *const, EModResult);
EModResult Mod::FinishLoadCache(EModResult error) // 0x1078CAB0
{
	mangled_x86(MANGLED_TODO, "?FinishLoadCache@Mod@@AAE?AW4EModResult@@W42@@Z");
	// EModResult error;
	// function call : void (Mod *)
	todo("implement");
	EModResult __result = _sub_1078CAB0(this, error);
	return __result;
}

// mangled_x86(MANGLED_DEFAULT, "??0IMod@@QAE@XZ"); no body to assert in
_inline IMod::IMod() = default; // 0x1078B570

extern EModResult _sub_1078D2F0(Mod *const, __int32);
EModResult Mod::LoadCacheBlocking(__int32 cacheIndex) // 0x1078D2F0
{
	mangled_x86(MANGLED_TODO, "?LoadCacheBlocking@Mod@@AAE?AW4EModResult@@H@Z");
	// static ...; // 0x1078D5EE
	// static ...; // 0x1078D5E8
	// static ...; // 0x1078D5C4
	// static ...; // 0x1078D5BC
	// Mod *const this;
	// __int32 cacheIndex;
	// c_file_reference file;
	// std::shared_ptr<ModCache> cache;
	// c_file_open_scope scope;
	todo("implement");
	EModResult __result = _sub_1078D2F0(this, cacheIndex);
	return __result;
}

_extern void _sub_1078CA40(Mod *const);
void Mod::Finish() // 0x1078CA40
{
	mangled_x86(MANGLED_TODO, "?Finish@Mod@@QAEXXZ");
	// Mod *const this;
	todo("implement");
	_sub_1078CA40(this);
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
