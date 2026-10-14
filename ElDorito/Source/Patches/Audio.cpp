/* ---------- headers */

#include "Patches/Audio.hpp"
#include "hades/hades.h"

#include "Modules/ModuleDebug.hpp"

#include "Audio/AudioDeviceManager.hpp"
#include "Blam/cache/cache_file_tag_resources.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/fmod/fmod_functions.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/interface/user_interface_definitions.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/math/sound_math.hpp"
#include "Blam/memory/allocation_interface.hpp"
#include "Blam/memory/data.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/lruv_cache.hpp"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/sounds/halo_sound_system.hpp"
#include "Blam/sounds/sound_definitions.hpp"
#include "Blam/sounds/sound_memory.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/tag_files/tag_resource_internals.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Debug/DebugDraw.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/document.h"
#include "Utils/EventSink.hpp"
#include "Utils/Singleton.hpp"
#include "Debug/DebugTrace.hpp"  // hades: added for 0x10A2F050

#include "mods/tag_resource_streaming.hpp"  // hades: added for 0x10A35650

#include <fmod_errors.h>

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
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct FMOD_EventSystem;
struct HALO_CHANNEL;
struct HALO_CHANNEL_PROPERTIES;
struct HALO_PERM_SOUND;
struct HALO_SOUND_SYSTEM;
struct SYSTEM_FMOD;
struct c_allocation_interface;
struct looping_sound_datum;
struct s_cache_file_tag_resource_table_runtime;
struct s_cache_tag_instance;
struct s_data_array;
struct s_data_iterator;
struct s_datum;
struct s_lruv_cache;
struct s_object_header;
struct s_sound_definition;
struct s_sound_permutation;
struct s_sound_permutation_chunk;
struct s_sound_source_datum;
struct s_sound_tag_data;
struct s_tag_resource;
struct s_unit_data;
struct s_user_interface_shared_globals;
struct s_xbox_sound_datum;
struct s_xbox_sound_datum_ex;
struct sound_channel_datum;
namespace Audio
{
	struct SAudioDeviceEvent;
}
namespace Patches
{
	namespace Audio
	{
		struct SAudioDeviceInfo;
	}
}
namespace hades_file_local
{
	struct c_large_integer;
	class c_sound_debug_printer;
	struct c_dumb_allocator;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Audio {}
	using namespace Patches::Audio;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

//enum debug_display_fmod_stats::__l2::e_cpu_usage
//{
//	_cpu_dsp = 0,
//	_cpu_stream,
//	_cpu_geometry,
//	_cpu_update,
//	_cpu_total,
//	k_cpu_stats_count,
//};

/* ---------- definitions */

namespace hades_file_local
{
	struct c_large_integer
	{
		unsigned __int32 hi; // 0x0
		unsigned __int32 lo; // 0x4
		unsigned long long value() const;
		c_large_integer &operator+=(c_large_integer const &);
		public: c_large_integer() = default;
		c_large_integer(unsigned long long value);
		c_large_integer(unsigned __int32 hi, unsigned __int32 lo);
	};
	static_assert(sizeof(c_large_integer) == 8, "Invalid c_large_integer size");

	class c_sound_debug_printer
	{
	public:
		c_sound_debug_printer(__int32, __int32);
		void print_line(long, char const *, ...);
		void skip_line();
	private:
		float m_yOffset; // 0x0
		float m_xOffset; // 0x4
	public:
		void __dflt_ctor_closure(); /* compiler_generated() */
	};
	static_assert(sizeof(c_sound_debug_printer) == 8, "Invalid c_sound_debug_printer size");

	struct c_dumb_allocator :
		public c_allocation_interface
	{
		virtual void *allocate(unsigned long, char const *);
		virtual void daallocate(void *);
		c_dumb_allocator(c_dumb_allocator &); /* compiler_generated() */
		c_dumb_allocator(c_dumb_allocator const &); /* compiler_generated() */
		c_dumb_allocator(); /* compiler_generated() */
		c_dumb_allocator &operator=(c_dumb_allocator &); /* compiler_generated() */
		c_dumb_allocator &operator=(c_dumb_allocator const &); /* compiler_generated() */
	};
	static_assert(sizeof(c_dumb_allocator) == 4, "Invalid c_dumb_allocator size");
}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Audio { namespace FMOD { extern FMOD_RESULT CreateOggVorbisStream(FMOD_SYSTEM *system, void *data, unsigned __int32 length, unsigned __int32 mode, FMOD_SOUND **sound); } }  // hades: added for 0x10A2E5A0  // hades: added for 0x10A2E5A0

extern c_data_array<s_sound_source_datum> **g_sound_sources;  // hades: added for 0x10A33C20
extern c_data_array<looping_sound_datum> **g_looping_sounds;  // hades: added for 0x10A33C20

namespace Audio { namespace FMOD { extern void RegisterOggVorbisCodec(FMOD_SYSTEM *system, __int32 priority); } }  // hades: added for 0x10A32060

bool SoundSystemTraceEnabled(); template<typename... TArgs> void SoundCacheDebugLog(long level, __int32 color, char const *format, TArgs &&...args) { if (!SoundSystemTraceEnabled()) return; if (static_cast<long>(Utils::Singleton<Modules::ModuleDebug>::Instance().VarSoundCache->ValueInt) <= level) CDebugTrace::Trace(color, format, std::forward<TArgs>(args)...); }  // hades: added for 0x10A35580

extern void *(*const datum_try_and_get)(s_data_array const *, unsigned long);  // hades: added for 0x10A35A90

extern s_cache_file_tag_globals *g_cache_file_tag_globals;  // hades: added for 0x10A35CD0

extern void (*const data_iterator_new)(s_data_iterator *, s_data_array const *);  // hades: added for 0x10A34E00
extern s_datum *(*const data_iterator_next)(s_data_iterator *);  // hades: added for 0x10A34E00

extern sound_channel_datum **g_sound_channels;  // hades: added for 0x10A331A0

#include "mods/memory/physical_memory_manager.hpp"  // hades: added for 0x10A35120
extern void *(*const data_new)(char const *, long, unsigned long, long, void *);  // hades: added for 0x10A35120

#include "Modules/ModuleSettings.hpp"  // hades: added for 0x10A31D40
#include "Modules/ModuleServer.hpp"  // hades: added for 0x10A34370

extern c_data_array<s_xbox_sound_datum> **g_xbox_sounds;  // hades: added for 0x10A352F0
extern void (*const datum_delete)(s_data_array *, long);  // hades: added for 0x10A352F0

extern s_sound_manager_globals **g_sound_manager_globals;  // hades: added for 0x10A34A80

namespace Patches
{
	namespace Audio
	{
		extern void ApplyAll();
		extern void ApplyAfterInit();
		extern bool SetOutputDevice(__int32 deviceIndex);
		extern bool GetDeviceInfo(__int32 deviceIndex, Patches::Audio::SAudioDeviceInfo *outInfo);
		extern __int32 GetDeviceCount();
		extern void Tick();
	}
}

_inline c_large_integer operator+(c_large_integer const &lhs, c_large_integer const &rhs);
bool SoundSystemTraceEnabled();
bool SoundQueueFilter(s_sound_tag_data const *request);
FMOD_RESULT FMOD_CheckError(FMOD_RESULT err, char const *func_name);
void debug_display_sound_system();
void debug_display_fmod_stats();
bool SYSTEM_FMOD_InitEventSystem(SYSTEM_FMOD *thisptr);
bool __fastcall SYSTEM_FMOD_Init_Hook(char *thisptr, void *unused, __int32 a2, __int32 a3);
long long MapSamples(FMOD_CHANNEL *channel, unsigned __int32 samples);
long GetQueuedSoundCount(HALO_CHANNEL const *channel);
void DelayPermutation(HALO_CHANNEL *channel, __int32 index, bool sync_time);
void HALO_CHANNEL_PlaySound(HALO_CHANNEL *channel, __int32 i);
void __fastcall HALO_CHANNEL_Update(HALO_CHANNEL *channel);
short HALO_SOUND_SYSTEM_GetChannelState(long source_index);
void __fastcall HALO_SOUND_SYSTEM_Update_Hook(HALO_SOUND_SYSTEM *sound_system);
bool sound_plays_when_paused(long definition_index);
void __fastcall HALO_SOUND_SYSTEM_Pause(HALO_SOUND_SYSTEM *thisptr, void *unused, bool paused);
void __fastcall HALO_CHANNEL_Queue(HALO_CHANNEL *channel, void *unused, s_sound_tag_data *request);
void __fastcall HALO_PERM_SOUND_InitChannelProperties(HALO_PERM_SOUND *thisptr, void *unused, HALO_CHANNEL_PROPERTIES *channel_properties);
void __fastcall HALO_PERM_SOUND_UpdateChannelProperties(HALO_PERM_SOUND *thisptr, void *unused, HALO_CHANNEL_PROPERTIES *channel_properties);
FMOD_RESULT CreateSoundHook(s_sound_tag_data *request, FMOD_SOUND **sound, void **out_data);
FMOD_RESULT FMOD_Sound_ReleaseSub_Hook(FMOD_SOUND *sound, FMOD_SYSTEM **out_system);
__int32 sound_permutation_get_unique_id(s_sound_permutation *permutation);
void loop_track_fade_hook(long definition_index, bool is_alternate, __int32 reason, float seconds, long sound_index);
void channel_signal_complete(short channel_index);
void refresh_channel(short channel_index);
void refresh_channels();
void build_channel_transmission_sources_hook(void *listener, void *voices, void *sources);
void update_hardware_channels_hook(void *a1, void *a2);
short sound_commit_looping_find_pitch_range_by_pitch_hook(s_sound_definition *sndDef, float pitchModifier, short fallbackIndex);
bool sound_attachment_is_sky_hook(long object_index);
void unit_set_mouth_aperture_hook(long unit_index, float t);
void OnAudioDeviceEvent(::Audio::SAudioDeviceEvent const &e);
void sound_cache_sound_delete_hook(s_sound_permutation_chunk *chunk);
void *sound_cache_sound_hardware_lock(s_sound_permutation_chunk *chunk, unsigned long *out_size);
void sound_cache_sound_hardware_unlock(s_sound_permutation_chunk *chunk);
void sound_cache_delete_block_proc(void *context, long block_index, bool moved);
bool sound_cache_locked_block_proc(void *context, long block_index);
void sound_cache_idle_hook();
void sound_cache_new_hook();
long find_cache_block_for_sound(long definition_index);
void sound_cache_sound_new(long definition_index, s_sound_permutation_chunk *chunk);
long sound_cache_sound_request_hook(long definition_index, s_sound_permutation_chunk *chunk, long flags);
bool sound_cache_sound_add_reference_hook(s_sound_permutation_chunk *chunk);
void sound_cache_sound_finished_hook(s_sound_permutation_chunk *chunk);
void sound_cache_flush_all_sound_guaranteed_hook();
unsigned __int32 sound_try_to_get_global_propagation_hook(char a1);

/* ---------- globals */

extern char const *tag_get_name(long tag_index);
extern void *(__cdecl *const tag_get)(unsigned long, long);

extern long const k_number_of_xbox_sound_datums; // 0x111ABBB4
bool (__thiscall *HALO_PERM_SOUND::Init)(HALO_PERM_SOUND *, s_sound_tag_data *, HALO_CHANNEL_PROPERTIES *, HALO_CHANNEL *); // 0x113541FC
HALO_PERM_SOUND *(__thiscall *HALO_PERM_SOUND::Free)(HALO_PERM_SOUND *); // 0x11354200
HALO_PERM_SOUND *(__thiscall *HALO_PERM_SOUND::Reset)(HALO_PERM_SOUND *); // 0x11354204
__int32 (__thiscall *HALO_PERM_SOUND::UpdateChannelProperties)(HALO_PERM_SOUND *, HALO_CHANNEL_PROPERTIES *); // 0x11354208
__int32 (__thiscall *HALO_PERM_SOUND::InitChannelProperties)(HALO_PERM_SOUND *, HALO_CHANNEL_PROPERTIES *); // 0x1135420C
char const *HALO_CHANNEL::STATE_NAMES[4]; // 0x11354210

/* ---------- private variables */

namespace hades_file_local
{
	extern void *g_channel_transmission_sources1[224]; // 0x124578D8
	extern void *g_channel_transmission_sources2[224]; // 0x12457C58
	extern s_lruv_cache *g_xbox_sound_cache; // 0x12457FD8
	extern void *g_sound_cache_memory; // 0x12457FDC
	extern long const g_sample_rates[4]; // 0x111ABBB8
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Audio
	{
		void ApplyAll() // 0x10A2DCC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Audio@Patches@@YAXXZ");
			// procedure flags: nofpo

					Patch(0x100DA75, { 0x02 }).Apply();
					Pointer(0x176CA18).Write<unsigned int>(reinterpret_cast<unsigned int>(SYSTEM_FMOD_Init_Hook));
					*(uint32_t *)0x404DF9 = 0x100;
					*(uint32_t *)0x4035E1 = 0x100;
					*(uint32_t *)0x404DF9 = 0x100;
					*(uint32_t *)0x517BE6 = 0x0;
					*(uint32_t *)0x517AFC = 0x3100;
					*(uint32_t *)0x517B4C = 0x3100;
					*(uint32_t *)0x667728 = 0xE0;
					*(uint32_t *)0x667736 = 0xE0;
					*(uint32_t *)0x667744 = 0xE0;
					*(uint32_t *)0x667752 = 0xE0;
					*(uint32_t *)0x667760 = 0xE0;
					*(uint16_t *)0x18BE324 = 0x61;
					*(uint16_t *)0x18BE326 = 0x61;
					*(uint16_t *)0x18BE328 = 0x12;
					*(uint16_t *)0x18BE32A = 0xC;
					Hook(0x267880, platform_sound_source_is_playing).Apply();
					Hook(0x264E39, sound_commit_looping_find_pitch_range_by_pitch_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
					Hook(0x118FC4, build_channel_transmission_sources_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
					Hook(0x119036, update_hardware_channels_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
					Hook(0x1DD990, sound_attachment_is_sky_hook).Apply();
					Hook(0x7489E0, unit_set_mouth_aperture_hook).Apply();
					::Audio::CAudioDeviceManager::Instance().deviceEvents.Subscribe(OnAudioDeviceEvent);
		}

		void ApplyAfterInit() // 0x10A2C1E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAfterInit@Audio@Patches@@YAXXZ");
			// procedure flags: nofpo

			Hook(0x251480, HALO_CHANNEL_Queue).Apply();
			Hook(0x253470, HALO_CHANNEL_Update).Apply();
			Hook(0x24FDA0, HALO_PERM_SOUND_InitChannelProperties).Apply();
			Hook(0x253640, HALO_PERM_SOUND_UpdateChannelProperties).Apply();
			Hook(0x2560C0, HALO_SOUND_SYSTEM_GetChannelState).Apply();
			Hook(0x250440, HALO_SOUND_SYSTEM_Pause).Apply();
			Pointer(0x165F6A4).Write(HALO_SOUND_SYSTEM_Update_Hook);
			Hook(0x24BD10, CreateSoundHook).Apply();
			Hook(0xF8909E, FMOD_Sound_ReleaseSub_Hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x24CF5E, sound_permutation_get_unique_id, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x266771, loop_track_fade_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x266823, loop_track_fade_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x266973, loop_track_fade_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x114DC0, refresh_channels).Apply();
			Hook(0x114080, channel_signal_complete).Apply();
			Hook(0x260090, sound_cache_new_hook).Apply();
			Hook(0x25FCB0, sound_cache_sound_request_hook).Apply();
			Hook(0x260050, sound_cache_idle_hook).Apply();
			Hook(0x260120, sound_cache_sound_delete_hook).Apply();
			Hook(0x2600E0, sound_cache_sound_add_reference_hook).Apply();
			Hook(0x25FF90, sound_cache_flush_all_sound_guaranteed_hook).Apply();
			Hook(0x260150, sound_cache_sound_finished_hook).Apply();
			Pointer(0x5132F8).Write<long const *>(g_sample_rates);
			Pointer(0x513461).Write<long const *>(g_sample_rates);
			Pointer(0x513FDC).Write<long const *>(g_sample_rates);
			Pointer(0x64BE12).Write<long const *>(g_sample_rates);
			Pointer(0x662AFB).Write<long const *>(g_sample_rates);
			Patch(0x251739, { 0xEB }).Apply();
			Hook(0x1DABD1, sound_try_to_get_global_propagation_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1DACD3, sound_try_to_get_global_propagation_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1DB06B, sound_try_to_get_global_propagation_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1DB05E, sound_try_to_get_global_propagation_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
		}

		bool SetOutputDevice(__int32 deviceIndex) // 0x10A32220
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetOutputDevice@Audio@Patches@@YA_NH@Z");
			// __int32 deviceIndex;
			// HALO_SOUND_SYSTEM *soundSystem;

			HALO_SOUND_SYSTEM *soundSystem = HALO_SOUND_SYSTEM::Get();
			if (soundSystem == nullptr)
			{
				return false;
			}
			return FMOD_System_SetDriver(soundSystem->fmod_system, deviceIndex) == FMOD_OK;
		}

		bool GetDeviceInfo(__int32 deviceIndex, Patches::Audio::SAudioDeviceInfo *outInfo) // 0x10A2F9D0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetDeviceInfo@Audio@Patches@@YA_NHPAUSAudioDeviceInfo@12@@Z");
			// Patches::Audio::SAudioDeviceInfo *outInfo;
			// HALO_SOUND_SYSTEM *soundSystem;

			HALO_SOUND_SYSTEM *soundSystem = HALO_SOUND_SYSTEM::Get();
			if (soundSystem == nullptr)
				return false;
			return FMOD_System_GetDriverInfo(soundSystem->fmod_system, deviceIndex, outInfo->name, 512, nullptr) == FMOD_OK;
		}

		__int32 GetDeviceCount() // 0x10A2F910
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetDeviceCount@Audio@Patches@@YAHXZ");
			// procedure flags: nofpo
			// static ...; // 0x10A2F994
			// static ...; // 0x10A2F988
			// static ...; // 0x10A2F980
			// HALO_SOUND_SYSTEM *soundSystem;
			// __int32 numDrivers;

			HALO_SOUND_SYSTEM *soundSystem;
			__int32 numDrivers;

			soundSystem = HALO_SOUND_SYSTEM::Get();
			if (!soundSystem)
			{
				return 0;
			}

			if (FMOD_System_GetNumDrivers(soundSystem->fmod_system, &numDrivers))
			{
				return 0;
			}

			return numDrivers;
		}

		void Tick() // 0x10A324F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@Audio@Patches@@YAXXZ");
			// procedure flags: nofpo

			debug_display_sound_system();
			debug_display_fmod_stats();
		}
	}
}

/* ---------- private code */

_inline c_large_integer::c_large_integer(unsigned long long value) // 0x10A2BAF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_large_integer@hades_file_local@@QAE@_K@Z");
	// `anonymous-namespace'::c_large_integer::c_large_integer
	// unsigned long long value;

	hi = (unsigned int)(value >> 32);
	lo = (unsigned int)value;
}

_inline c_large_integer::c_large_integer(unsigned __int32 hi, unsigned __int32 lo) // 0x10A2BAB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_large_integer@hades_file_local@@QAE@II@Z");
	// `anonymous-namespace'::c_large_integer::c_large_integer
	// unsigned __int32 lo;

	this->hi = hi;
	this->lo = lo;
}

_inline unsigned long long c_large_integer::value() const // 0x10A362D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?value@c_large_integer@hades_file_local@@QBE_KXZ");
	// `anonymous-namespace'::c_large_integer::value
	// c_large_integer const *const this;

	return ((unsigned long long)hi << 32) | lo;
}

_inline c_large_integer operator+(c_large_integer const &lhs, c_large_integer const &rhs) // 0x10A2C0A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??H@YA?AUc_large_integer@hades_file_local@@ABU01@0@Z");
	// `anonymous-namespace'::operator+
	// c_large_integer const &rhs;
	// unsigned __int32 hi;
	// unsigned __int32 lo;
	// unsigned long long sum;
	// unsigned __int32 carry;

	unsigned long long sum = (unsigned long long)lhs.lo + rhs.lo;
	unsigned __int32 carry = (unsigned __int32)(sum >> 32);
	unsigned __int32 lo = (unsigned __int32)sum;

	sum = (unsigned long long)lhs.hi + rhs.hi + carry;
	unsigned __int32 hi = (unsigned __int32)sum;

	return c_large_integer(hi, lo);
}

_inline c_large_integer &c_large_integer::operator+=(c_large_integer const &rhs) // 0x10A2C160
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??Yc_large_integer@hades_file_local@@QAEAAU01@ABU01@@Z");
	// `anonymous-namespace'::c_large_integer::operator+=
	// c_large_integer const &rhs;

	return *this = *this + rhs;
}

_inline c_sound_debug_printer::c_sound_debug_printer(__int32 xoffset, __int32 yoffset) // 0x10A2BB60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0c_sound_debug_printer@hades_file_local@@QAE@HH@Z");
	// `anonymous-namespace'::c_sound_debug_printer::c_sound_debug_printer
	// __int32 yoffset;

	m_yOffset = 0.0f;
	m_xOffset = 0.0f;
	m_xOffset = (float)xoffset;
	m_yOffset = (float)yoffset;
}

_inline void __cdecl c_sound_debug_printer::print_line(long color, char const *format, ...) // 0x10A345D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?print_line@c_sound_debug_printer@hades_file_local@@QAAXJPBDZZ");
	// `anonymous-namespace'::c_sound_debug_printer::print_line
	// c_sound_debug_printer *const this;
	// long color;
	// char const *format;
	// char buff[4096];
	// char *va;

	char buff[4096];
	va_list va;

	va_start(va, format);
	vsnprintf_s(buff, _TRUNCATE, format, va);
	CDebugDrawBackend::DrawString2d(real_point2d{ m_xOffset, m_yOffset }, color, 0, 1.0f, buff);
	va_end(va);

	m_yOffset += 16.0f;
}

_inline void c_sound_debug_printer::skip_line() // 0x10A34B00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?skip_line@c_sound_debug_printer@hades_file_local@@QAEXXZ");
	// `anonymous-namespace'::c_sound_debug_printer::skip_line
	// c_sound_debug_printer *const this;

	m_yOffset += 16.0f;
}

bool SoundSystemTraceEnabled() // 0x10A32370
{
	// `anonymous-namespace'::SoundSystemTraceEnabled
	// procedure flags: nofpo

	return Modules::ModuleDebug::Instance().VarSoundSystemTrace->ValueInt != 0;
}

bool SoundQueueFilter(s_sound_tag_data const *request) // 0x10A322B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SoundQueueFilter@@YA_NPBUs_sound_tag_data@@@Z");
	// `anonymous-namespace'::SoundQueueFilter
	// s_sound_tag_data const *request;
	// std::string &filterStr;

	std::string &filterStr = Modules::ModuleDebug::Instance().VarSoundQueueFilter->ValueString;

	if (!filterStr.empty())
	{
		if (!strstr(tag_get_name(request->sound_tag_index), filterStr.c_str()))
		{
			return false;
		}
	}

	return true;
}

FMOD_RESULT FMOD_CheckError(FMOD_RESULT err, char const *func_name) // 0x10A2F050
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FMOD_CheckError@@YA?AW4FMOD_RESULT@@W41@PBD@Z");
	// `anonymous-namespace'::FMOD_CheckError
	// char const *func_name;
		// char const *err_string;

	char const *err_string;

	if (err && SoundSystemTraceEnabled())
	{
		err_string = FMOD_ErrorString(err);
		CDebugTrace::Trace(-65536, "FMOD ERROR :: %s :: %s\n", func_name, err_string);
	}

	return err;
}

void debug_display_sound_system() // 0x10A33C20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?debug_display_sound_system@@YAXXZ");
	// `anonymous-namespace'::debug_display_sound_system
	// procedure flags: nofpo
	// static ...; // 0x10A33F85
	// static ...; // 0x10A33F7C
	// static ...; // 0x10A33F64
	// static ...; // 0x10A33F5C
	// c_data_array<looping_sound_datum> *looping_sounds;
	// bool looping_sound_debug;
	// c_sound_debug_printer debug_printer;
	// s_data_iterator iterator;
	// bool sound_sources_debug;
	// c_data_array<s_sound_source_datum> *sound_sources;
		// long color;
		// long current_sound_count;
		// long max_sound_count;
			// s_sound_source_datum *sound_source;
				// long tag_index;
				// char const *name;
			// looping_sound_datum *looping_sound;
	// function call : void (*const)(s_data_iterator *, s_data_array const *)
	// function call : s_datum *(*const)(s_data_iterator *)
	// function call : void (*const)(s_data_iterator *, s_data_array const *)
	// function call : s_datum *(*const)(s_data_iterator *)

	bool sound_sources_debug = false;
	bool looping_sound_debug = false;
	if (Utils::Singleton<Modules::ModuleDebug>::Instance().VarSoundDebug && Utils::Singleton<Modules::ModuleDebug>::Instance().VarSoundDebug->ValueInt)
		sound_sources_debug = true;
	if (Utils::Singleton<Modules::ModuleDebug>::Instance().VarLoopingSoundDebug && Utils::Singleton<Modules::ModuleDebug>::Instance().VarLoopingSoundDebug->ValueInt)
		looping_sound_debug = true;
	if (!looping_sound_debug && !sound_sources_debug)
		return;
	c_sound_debug_printer debug_printer(50, 50);
	c_data_array<s_sound_source_datum> *sound_sources = *g_sound_sources;
	c_data_array<looping_sound_datum> *looping_sounds = *g_looping_sounds;
	s_data_iterator iterator;
	if (sound_sources_debug)
	{
		long current_sound_count = sound_sources->actual_count;
		long max_sound_count = sound_sources->capacity;
		long color = 0xFF00FF00;
		if (current_sound_count > max_sound_count * 0.5f)
			color = 0xFFFFFF00;
		else if (current_sound_count > max_sound_count * 0.75f)
			color = 0xFFFF0000;
		debug_printer.print_line(color, "Sound sources active: %d/%d", current_sound_count, max_sound_count);
		debug_printer.print_line(-1, "Current active sounds:");
		data_iterator_new(&iterator, sound_sources);
		while (s_sound_source_datum *sound_source = (s_sound_source_datum *)data_iterator_next(&iterator))
		{
			long tag_index = sound_source->sound_tag_index;
			if (tag_index == -1)
				continue;
			char const *name = tag_get_name(tag_index);
			debug_printer.print_line(-1, "%s", name);
		}
	}
	if (looping_sound_debug)
	{
		long current_sound_count = looping_sounds->actual_count;
		long max_sound_count = looping_sounds->capacity;
		long color = 0xFF00FF00;
		if (current_sound_count > max_sound_count * 0.5f)
			color = 0xFFFFFF00;
		else if (current_sound_count > max_sound_count * 0.75f)
			color = 0xFFFF0000;
		debug_printer.print_line(color, "Looping sounds active: %d/%d", current_sound_count, max_sound_count);
		debug_printer.print_line(-1, "Current active looping sounds:");
		data_iterator_new(&iterator, looping_sounds);
		while (looping_sound_datum *looping_sound = (looping_sound_datum *)data_iterator_next(&iterator))
		{
			long tag_index = looping_sound->looping_sound_tag_index;
			if (tag_index == -1)
				continue;
			char const *name = tag_get_name(tag_index);
			debug_printer.print_line(-1, "%s", name);
		}
	}
}

void debug_display_fmod_stats() // 0x10A33350
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?debug_display_fmod_stats@@YAXXZ");
	// `anonymous-namespace'::debug_display_fmod_stats
	// procedure flags: nofpo
	// static ...; // 0x10A33A4B
	// static ...; // 0x10A33A41
	// static ...; // 0x10A33A30
	// static ...; // 0x10A33A1E
	// static ...; // 0x10A33A16
	// static ...; // 0x10A33A08
	// static ...; // 0x10A339F2
	// static ...; // 0x10A339E0
	// static ...; // 0x10A339D8
	// static ...; // 0x10A3396C
	// static ...; // 0x10A33964
	// constexpr debug_display_fmod_stats::__l2::e_cpu_usage _cpu_dsp; // constant == 0
	// constexpr debug_display_fmod_stats::__l2::e_cpu_usage k_cpu_stats_count; // constant == 5
	// unsigned __int32 version;
	// unsigned __int32 memory_used_breakdown[48];
	// unsigned __int32 memory_used_total;
	// constexpr debug_display_fmod_stats::__l2::e_cpu_usage _cpu_stream; // constant == 1
	// float cpu_usage[5];
	// __int32 num_listeners;
	// constexpr debug_display_fmod_stats::__l2::e_cpu_usage _cpu_update; // constant == 3
	// constexpr debug_display_fmod_stats::__l2::e_cpu_usage _cpu_total; // constant == 4
	// HALO_SOUND_SYSTEM *sound_system;
	// __int32 software_channels;
	// float const k_bytes_to_mb;
	// constexpr debug_display_fmod_stats::__l2::e_cpu_usage _cpu_geometry; // constant == 2
	// c_sound_debug_printer printer;
	// __int32 result;
	// __int32 playing_channels;
	// char const *memtype_names[48];
		// __int32 i;

	enum e_cpu_usage
	{
		_cpu_dsp,
		_cpu_stream,
		_cpu_geometry,
		_cpu_update,
		_cpu_total,
		k_cpu_stats_count
	};
	char const *memtype_names[48] =
	{
		"OTHER",
		"STRING",
		"SYSTEM",
		"PLUGINS",
		"OUTPUT",
		"CHANNEL",
		"CHANNELGROUP",
		"CODEC",
		"FILE",
		"SOUND",
		"SOUND_SECONDARYRAM",
		"SOUNDGROUP",
		"STREAMBUFFER",
		"DSPCONNECTION",
		"DSP",
		"DSPCODEC",
		"PROFILE",
		"RECORDBUFFER",
		"REVERB",
		"REVERBCHANNELPROPS",
		"GEOMETRY",
		"SYNCPOINT",
		"EVENTSYSTEM",
		"MUSICSYSTEM",
		"FEV",
		"MEMORYFSB",
		"EVENTPROJECT",
		"EVENTGROUPI",
		"SOUNDBANKCLASS",
		"SOUNDBANKLIST",
		"STREAMINSTANCE",
		"SOUNDDEFCLASS",
		"SOUNDDEFDEFCLASS",
		"SOUNDDEFPOOL",
		"REVERBDEF",
		"EVENTREVERB",
		"USERPROPERTY",
		"EVENTINSTANCE",
		"EVENTINSTANCE_COMPLEX",
		"EVENTINSTANCE_SIMPLE",
		"EVENTINSTANCE_LAYER",
		"EVENTINSTANCE_SOUND",
		"EVENTENVELOPE",
		"EVENTENVELOPEDEF",
		"EVENTPARAMETER",
		"EVENTCATEGORY",
		"EVENTENVELOPEPOINT",
		"EVENTINSTANCEPOOL",
	};
	float const k_bytes_to_mb = 1.0f / (1024.0f * 1024.0f);
	if (!Modules::ModuleDebug::Instance().VarFModStats->ValueInt)
		return;
	HALO_SOUND_SYSTEM *sound_system = HALO_SOUND_SYSTEM::Get();
	float cpu_usage[k_cpu_stats_count];
	__int32 playing_channels;
	__int32 software_channels;
	unsigned __int32 version;
	__int32 num_listeners;
	unsigned __int32 memory_used_breakdown[48];
	unsigned __int32 memory_used_total;
	__int32 result = FMOD_System_GetCPUUsage(sound_system->fmod_system, &cpu_usage[_cpu_dsp], &cpu_usage[_cpu_stream], &cpu_usage[_cpu_geometry], &cpu_usage[_cpu_update], &cpu_usage[_cpu_total]);
	result |= FMOD_System_GetMemoryInfo(sound_system->fmod_system, 0xFFFFFFFF, 0xFFFFFFFF, &memory_used_total, memory_used_breakdown);
	result |= FMOD_System_GetChannelsPlaying(sound_system->fmod_system, &playing_channels);
	result |= FMOD_System_GetVersion(sound_system->fmod_system, &version);
	result |= FMOD_System_GetSoftwareChannels(sound_system->fmod_system, &software_channels);
	result |= FMOD_System_Get3DNumListeners(sound_system->fmod_system, &num_listeners);
	if (result)
		return;
	c_sound_debug_printer printer(50, 50);
	printer.print_line(0xFFFFFFFF, "version: %x", version);
	printer.print_line(0xFFFFFFFF, "dsp buffer size: %d", sound_system->dsp_buffer_size);
	printer.print_line(0xFFFFFFFF, "output rate: %d", sound_system->output_sample_rate);
	printer.print_line(0xFFFFFFFF, "channels: %d/%d", playing_channels, software_channels);
	printer.print_line(0xFFFFFFFF, "listeners: %d", num_listeners);
	printer.skip_line();
	printer.print_line(0xFF00FF00, "%-15s %.2f", "total cpu", cpu_usage[_cpu_total]);
	printer.print_line(0xFFFFFFFF, "%-15s %.2f", "dsp", cpu_usage[_cpu_dsp]);
	printer.print_line(0xFFFFFFFF, "%-15s %.2f", "stream", cpu_usage[_cpu_stream]);
	printer.print_line(0xFFFFFFFF, "%-15s %.2f", "geometry", cpu_usage[_cpu_geometry]);
	printer.print_line(0xFFFFFFFF, "%-15s %.2f", "update", cpu_usage[_cpu_update]);
	printer.skip_line();
	printer.print_line(0xFF00FF00, "%-15s %.2f MB\n", "total memory", memory_used_total * k_bytes_to_mb);
	for (__int32 i = 0; i < 48; i++)
	{
		if (memory_used_breakdown[i] < 0x2800)
			continue;
		printer.print_line(0xFFFFFFFF, "%-15s %.2f MB", memtype_names[i], memory_used_breakdown[i] * k_bytes_to_mb);
	}
}

bool SYSTEM_FMOD_InitEventSystem(SYSTEM_FMOD *thisptr) // 0x10A31E20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SYSTEM_FMOD_InitEventSystem@@YA_NPAUSYSTEM_FMOD@@@Z");
	// `anonymous-namespace'::SYSTEM_FMOD_InitEventSystem
	// static ...; // 0x10A31FE1
	// static ...; // 0x10A31FDC
	// static ...; // 0x10A31FC4
	// static ...; // 0x10A31FBC
	// SYSTEM_FMOD *thisptr;
	// FMOD_RESULT (*EventSystem_init)(FMOD_EventSystem *, __int32, __int32, void *, __int32);
	// FMOD_SYSTEM *fmod_system;
	// unsigned __int32 caps;
	// FMOD_RESULT result;
	// FMOD_ADVANCEDSETTINGS settings;
	// function call : FMOD_RESULT (*)(FMOD_EventSystem *, __int32, __int32, void *, __int32)
	// function call : FMOD_RESULT (*)(FMOD_EventSystem *, __int32, __int32, void *, __int32)

	FMOD_SYSTEM *fmod_system = *(FMOD_SYSTEM **)0x69AD05C;
	FMOD_System_SetHardwareChannels(fmod_system, 0, 0, 0, 0);
	FMOD_System_SetSoftwareChannels(fmod_system, 256);
	FMOD_ADVANCEDSETTINGS settings;
	memset(&settings, 0, sizeof(settings));
	FMOD_System_GetAdvancedSettings(fmod_system, &settings);
	settings.cbsize = sizeof(FMOD_ADVANCEDSETTINGS);
	settings.maxMPEGcodecs = 192;
	settings.maxADPCMcodecs = 0;
	settings.maxXMAcodecs = 0;
	settings.maxPCMcodecs = 0;
	FMOD_System_SetAdvancedSettings(fmod_system, &settings);
	unsigned __int32 caps;
	FMOD_System_GetDriverCaps(fmod_system, 0, &caps, nullptr, nullptr, &thisptr->speaker_mode);
	FMOD_System_SetSpeakerMode(fmod_system, thisptr->speaker_mode);
	if (caps & FMOD_CAPS_HARDWARE_EMULATED)
		FMOD_System_SetDSPBufferSize(fmod_system, 1024, 10);
	FMOD_RESULT (__stdcall *EventSystem_init)(FMOD_EventSystem *, __int32, __int32, void *, __int32) = (*(FMOD_RESULT (__stdcall ***)(FMOD_EventSystem *, __int32, __int32, void *, __int32))thisptr->event_system)[0];
	FMOD_RESULT result = EventSystem_init(thisptr->event_system, 256, 0, nullptr, 0);
	if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		FMOD_System_SetSpeakerMode(fmod_system, FMOD_SPEAKERMODE_STEREO);
		result = EventSystem_init(thisptr->event_system, 256, 0, nullptr, 0);
	}
	return result == FMOD_OK;
}

bool __fastcall SYSTEM_FMOD_Init_Hook(char *thisptr, void *unused, __int32 a2, __int32 a3) // 0x10A32060
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SYSTEM_FMOD_Init_Hook@@YI_NPADPAXHH@Z");
	// `anonymous-namespace'::SYSTEM_FMOD_Init_Hook
	// __int32 a3;
	// bool (*const snd_SYSTEM_FMOD_InitEventSystem)(void *, void *);
	// HALO_SOUND_SYSTEM **g_halo_sound_system_ptr;
	// HALO_SOUND_SYSTEM *haloSoundSystem;
	// unsigned long outputDevice;
	// bool (*const snd_SYSTEM_FMOD_PrepareInit)();
	// bool (*const HALO_SOUND_SYSTEM_Init)(void *, __int32, __int32);
	// bool (*const EventSystem_Create)(void *);
	// function call : unsigned long ()
	// function call : bool (*const)()
	// function call : bool (*const)(void *)
	// function call : __int32 (*)(unsigned __int32, void *)
	// function call : bool (*const)(void *, __int32, __int32)

	bool (*const snd_SYSTEM_FMOD_PrepareInit)() = reinterpret_cast<bool (*)()>(0x404D10);
	bool (*const snd_SYSTEM_FMOD_InitEventSystem)(void *, void *) = reinterpret_cast<bool (*)(void *, void *)>(0x404D70);
	bool (__stdcall *const EventSystem_Create)(void *) = reinterpret_cast<bool (__stdcall *)(void *)>(0x1353A80);
	bool (__thiscall *const HALO_SOUND_SYSTEM_Init)(void *, __int32, __int32) = reinterpret_cast<bool (__thiscall *)(void *, __int32, __int32)>(0x64D9A0);
	HALO_SOUND_SYSTEM **g_halo_sound_system_ptr = (HALO_SOUND_SYSTEM **)0x18BC9C8;
	*(unsigned long *)0x698D054 = GetCurrentThreadId();
	if (!snd_SYSTEM_FMOD_PrepareInit() || EventSystem_Create(thisptr + 0x30) || (*(__int32 (__stdcall **)(unsigned __int32, void *))(**(unsigned __int32 **)(thisptr + 0x30) + 0x1C))(*(unsigned __int32 *)(thisptr + 0x30), (void *)0x69AD05C) || !SYSTEM_FMOD_InitEventSystem((SYSTEM_FMOD *)thisptr))
		return false;
	HALO_SOUND_SYSTEM *haloSoundSystem = *g_halo_sound_system_ptr;
	if (!haloSoundSystem || !HALO_SOUND_SYSTEM_Init(haloSoundSystem, a2, 1))
		return false;
	::Audio::FMOD::RegisterOggVorbisCodec(haloSoundSystem->fmod_system, 0);
	*(unsigned long *)(thisptr + 4) |= 1;
	unsigned long outputDevice = Utils::Singleton<Modules::ModuleSettings>::Instance().VarAudioOutputDevice->ValueInt;
	if (outputDevice)
		Patches::Audio::SetOutputDevice(outputDevice);
	return true;
}

long long MapSamples(FMOD_CHANNEL *channel, unsigned __int32 samples) // 0x10A31C20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?MapSamples@@YA_JPAUFMOD_CHANNEL@@I@Z");
	// `anonymous-namespace'::MapSamples
	// static ...; // 0x10A31CE8
	// static ...; // 0x10A31CE0
	// FMOD_CHANNEL *channel;
	// unsigned __int32 samples;
	// float sample_rate;

	float sample_rate;

	FMOD_Channel_GetFrequency(channel, &sample_rate);
	if (sample_rate == 0.0f)
	{
		return 0;
	}

	return llround((double)samples / sample_rate * HALO_SOUND_SYSTEM::Get()->output_sample_rate);
}

long GetQueuedSoundCount(HALO_CHANNEL const *channel) // 0x10A2FA70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetQueuedSoundCount@@YAJPBUHALO_CHANNEL@@@Z");
	// `anonymous-namespace'::GetQueuedSoundCount
	// HALO_CHANNEL const *channel;
	// long count;
		// long i;

	long count = 0;
	for (unsigned long i = 0; i < 2; i++)
	{
		if (channel->queue[i].fmod_sound)
		{
			count++;
		}
	}
	return count;
}

void DelayPermutation(HALO_CHANNEL *channel, __int32 index, bool sync_time) // 0x10A2ED10
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DelayPermutation@@YAXPAUHALO_CHANNEL@@H_N@Z");
	// `anonymous-namespace'::DelayPermutation
	// static ...; // 0x10A2EF80
	// static ...; // 0x10A2EF75
	// static ...; // 0x10A2EF6C
	// static ...; // 0x10A2EF30
	// static ...; // 0x10A2EF28
	// HALO_CHANNEL *channel;
	// __int32 index;
	// bool sync_time;
	// HALO_PERM_SOUND &queued_sound;
	// unsigned __int32 length_pcm;
	// HALO_SOUND_SYSTEM *sound_system;
	// c_large_integer end_time;
	// c_large_integer start_time;
		// unsigned __int32 length_pcm;
		// HALO_PERM_SOUND &previous_queued_sound;
			// unsigned __int32 position;

	HALO_SOUND_SYSTEM *sound_system = HALO_SOUND_SYSTEM::Get();
	HALO_PERM_SOUND &queued_sound = channel->queue[index];
	c_large_integer start_time;
	if (index > 0)
	{
		HALO_PERM_SOUND &previous_queued_sound = channel->queue[index - 1];
		unsigned __int32 length_pcm = channel->queue[index - 1].sample_count;
		if (!length_pcm)
			FMOD_Sound_GetLength(previous_queued_sound.fmod_sound, &length_pcm, FMOD_TIMEUNIT_PCM);
		if (sync_time)
		{
			FMOD_System_GetDSPClock(sound_system->fmod_system, &start_time.hi, &start_time.lo);
			unsigned __int32 position;
			FMOD_Channel_GetPosition(previous_queued_sound.fmod_channel, &position, FMOD_TIMEUNIT_PCM);
			length_pcm += previous_queued_sound.first_sample;
			if (position > length_pcm)
				position = length_pcm;
			start_time += MapSamples(previous_queued_sound.fmod_channel, length_pcm - position);
		}
		else
		{
			FMOD_Channel_GetDelay(previous_queued_sound.fmod_channel, FMOD_DELAYTYPE_DSPCLOCK_START, &start_time.hi, &start_time.lo);
			start_time += MapSamples(previous_queued_sound.fmod_channel, length_pcm);
		}
	}
	else
	{
		FMOD_System_GetDSPClock(sound_system->fmod_system, &start_time.hi, &start_time.lo);
	}
	unsigned __int32 length_pcm = queued_sound.sample_count;
	if (!length_pcm)
		FMOD_Sound_GetLength(queued_sound.fmod_sound, &length_pcm, FMOD_TIMEUNIT_PCM);
	c_large_integer end_time = start_time + MapSamples(queued_sound.fmod_channel, length_pcm);
	FMOD_Channel_SetDelay(queued_sound.fmod_channel, FMOD_DELAYTYPE_DSPCLOCK_START, start_time.hi, start_time.lo);
	if (!sync_time && queued_sound.sequenced_flag && queued_sound.first_sample > 0)
		FMOD_Channel_SetPosition(queued_sound.fmod_channel, queued_sound.first_sample, FMOD_TIMEUNIT_PCM);
}

void HALO_CHANNEL_PlaySound(HALO_CHANNEL *channel, __int32 i) // 0x10A2FAE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HALO_CHANNEL_PlaySound@@YAXPAUHALO_CHANNEL@@H@Z");
	// `anonymous-namespace'::HALO_CHANNEL_PlaySound
	// static ...; // 0x10A2FBF8
	// static ...; // 0x10A2FBF0
	// HALO_CHANNEL *channel;
	// __int32 i;
	// __int32 num_channels;
	// HALO_SOUND_SYSTEM *sound_system;
	// function call : __int32 (*)(HALO_PERM_SOUND *, HALO_CHANNEL_PROPERTIES *)
	// function call : __int32 (*)(HALO_PERM_SOUND *, HALO_CHANNEL_PROPERTIES *)

	HALO_SOUND_SYSTEM *sound_system = HALO_SOUND_SYSTEM::Get();
	__int32 num_channels;
	FMOD_System_GetChannelsPlaying(sound_system->fmod_system, &num_channels);
	if (num_channels >= 256)
		return;
	if (FMOD_System_PlaySound(sound_system->fmod_system, FMOD_CHANNEL_FREE, channel->queue[i].fmod_sound, 1, &channel->queue[i].fmod_channel) == FMOD_OK)
	{
		HALO_PERM_SOUND::InitChannelProperties(&channel->queue[i], &channel->properties);
		HALO_PERM_SOUND::UpdateChannelProperties(&channel->queue[i], &channel->properties);
		DelayPermutation(channel, i, false);
		FMOD_Channel_SetPaused(channel->queue[i].fmod_channel, 0);
	}
}

void __fastcall HALO_CHANNEL_Update(HALO_CHANNEL *channel) // 0x10A2FF60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HALO_CHANNEL_Update@@YIXPAUHALO_CHANNEL@@@Z");
	// `anonymous-namespace'::HALO_CHANNEL_Update
	// static ...; // 0x10A30327
	// static ...; // 0x10A3031C
	// static ...; // 0x10A3030F
	// static ...; // 0x10A30304
	// static ...; // 0x10A302D4
	// static ...; // 0x10A302CC
	// HALO_CHANNEL *channel;
	// __int32 queued_count;
	// bool is_playing;
		// __int32 i;
			// FMOD_SOUND *playing_sound;
				// float channel_freq;
				// float sound_freq;
		// char *permutation_name;
		// char const *tag_name;
	// function call : __int32 (*)(HALO_PERM_SOUND *, HALO_CHANNEL_PROPERTIES *)
	// function call : HALO_PERM_SOUND *(*)(HALO_PERM_SOUND *)
	// function call : HALO_PERM_SOUND *(*)(HALO_PERM_SOUND *)

	__int32 queued_count = GetQueuedSoundCount(channel);
	for (__int32 i = 0; i < queued_count; i++)
	{
		if (!channel->queue[i].fmod_channel && channel->queue[i].fmod_sound)
			HALO_CHANNEL_PlaySound(channel, i);
		if (!channel->queue[i].fmod_channel)
			continue;
		FMOD_SOUND *playing_sound;
		if (FMOD_Channel_GetCurrentSound(channel->queue[i].fmod_channel, &playing_sound) == FMOD_OK)
		{
			float sound_freq;
			float channel_freq;
			FMOD_Sound_GetDefaults(playing_sound, &sound_freq, nullptr, nullptr, nullptr);
			FMOD_Channel_GetFrequency(channel->queue[i].fmod_channel, &channel_freq);
			HALO_PERM_SOUND::UpdateChannelProperties(&channel->queue[i], &channel->properties);
			if (abs(channel_freq - channel->properties.playback_rate_scale * sound_freq) >= 0.000001f)
				DelayPermutation(channel, i, true);
		}
	}
	if (channel->state == HALO_CHANNEL::_STATE_STOPPING)
		channel->state = HALO_CHANNEL::_STATE_IDLE;
	if (channel->state == HALO_CHANNEL::_STATE_IDLE)
		return;
	bool is_playing;
	if (channel->queue[0].fmod_channel && FMOD_Channel_IsPlaying(channel->queue[0].fmod_channel, (FMOD_BOOL *)&is_playing) == FMOD_OK && !(is_playing & 1))
	{
		if (SoundSystemTraceEnabled())
		{
			char const *tag_name = tag_get_name(channel->queue[0].sound_definition_index);
			char *permutation_name = Blam::Cache::StringIDCache::GetCurrent()->GetString(channel->queue[0].permutation_name_string_id);
			CDebugTrace::Trace(-1, "HALO_PERM_SOUND::Finsihed() (channel: %d, state: %s) %s [%s]", channel->id, HALO_CHANNEL::STATE_NAMES[channel->state], tag_name, permutation_name);
		}
		HALO_PERM_SOUND::Free(&channel->queue[0]);
		memcpy(&channel->queue[0], &channel->queue[1], sizeof(HALO_PERM_SOUND));
		HALO_PERM_SOUND::Reset(&channel->queue[1]);
		if (GetQueuedSoundCount(channel) == 0)
			channel->state = HALO_CHANNEL::_STATE_STOPPING;
		else
			channel->state = HALO_CHANNEL::_STATE_PLAYING;
	}
}

short HALO_SOUND_SYSTEM_GetChannelState(long source_index) // 0x10A31640
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HALO_SOUND_SYSTEM_GetChannelState@@YAFJ@Z");
	// `anonymous-namespace'::HALO_SOUND_SYSTEM_GetChannelState
	// long source_index;
	// HALO_SOUND_SYSTEM *sound_system;
	// HALO_CHANNEL *channels;
		// __int32 i;

	HALO_SOUND_SYSTEM *sound_system = HALO_SOUND_SYSTEM::Get();
	HALO_CHANNEL *channels = sound_system->channels.elements;

	for (__int32 i = 0; i < sound_system->channels.count; i++)
	{
		if (channels[i].id == source_index)
		{
			switch (channels[i].state)
			{
			case HALO_CHANNEL::_STATE_STOPPING:
			case HALO_CHANNEL::_STATE_PLAYING:
				return 4;
			case HALO_CHANNEL::_STATE_FULL:
				return 5;
			}
		}
	}

	return 0;
}

void __fastcall HALO_SOUND_SYSTEM_Update_Hook(HALO_SOUND_SYSTEM *sound_system) // 0x10A31BA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HALO_SOUND_SYSTEM_Update_Hook@@YIXPAUHALO_SOUND_SYSTEM@@@Z");
	// `anonymous-namespace'::HALO_SOUND_SYSTEM_Update_Hook
	// HALO_SOUND_SYSTEM *sound_system;
	// void (*const HALO_SOUND_SYSTEM_Update)(HALO_SOUND_SYSTEM *);
	// function call : void (*const)(HALO_SOUND_SYSTEM *)

	const auto HALO_SOUND_SYSTEM_Update = (void(__thiscall *)(HALO_SOUND_SYSTEM *))0x653AA0;

	FMOD_System_LockDSP(sound_system->fmod_system);
	HALO_SOUND_SYSTEM_Update(sound_system);
	FMOD_System_UnlockDSP(sound_system->fmod_system);
}

bool sound_plays_when_paused(long definition_index) // 0x10A35F20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_plays_when_paused@@YA_NJ@Z");
	// `anonymous-namespace'::sound_plays_when_paused
	// long definition_index;
	// s_sound_definition *sound;
	// function call : void *(*const)(unsigned long, long)

	s_sound_definition *sound = (s_sound_definition *)tag_get(0x736E6421, definition_index);

	return sound->sound_class == _sound_class_ui;
}

void __fastcall HALO_SOUND_SYSTEM_Pause(HALO_SOUND_SYSTEM *thisptr, void *unused, bool paused) // 0x10A31720
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HALO_SOUND_SYSTEM_Pause@@YIXPAUHALO_SOUND_SYSTEM@@PAX_N@Z");
	// `anonymous-namespace'::HALO_SOUND_SYSTEM_Pause
	// static ...; // 0x10A31AA2
	// static ...; // 0x10A31A97
	// static ...; // 0x10A31A8C
	// static ...; // 0x10A31A50
	// static ...; // 0x10A31A48
	// HALO_SOUND_SYSTEM *thisptr;
	// void *unused;
	// bool paused;
	// void *(*const sub_650640)(bool);
		// c_large_integer clock;
			// __int32 i;
				// HALO_CHANNEL *channel;
					// __int32 j;
		// c_large_integer delta_time;
		// c_large_integer pause_time;
						// c_large_integer start_time;

	void *(__stdcall *const sub_650640)(bool) = reinterpret_cast<void *(__stdcall *)(bool)>(0x650640);
	if (((thisptr->flags & 2) != 0) == paused)
		return;
	if (paused)
		thisptr->flags |= 2;
	else
		thisptr->flags &= ~2;
	if (paused)
	{
		c_large_integer clock;
		FMOD_System_GetDSPClock(thisptr->fmod_system, &clock.hi, &clock.lo);
		thisptr->paused_time_hi = clock.hi;
		thisptr->paused_time_lo = clock.lo;
		for (__int32 i = 0; i < thisptr->channels.count; i++)
		{
			HALO_CHANNEL *channel = thisptr->channels[i];
			for (__int32 j = 0; j < 2; j++)
			{
				if (channel->queue[j].fmod_channel && !sound_plays_when_paused(channel->queue[j].sound_definition_index))
					FMOD_Channel_SetDelay(channel->queue[j].fmod_channel, FMOD_DELAYTYPE_DSPCLOCK_PAUSE, clock.hi, clock.lo);
			}
		}
	}
	else
	{
		c_large_integer clock;
		FMOD_System_GetDSPClock(thisptr->fmod_system, &clock.hi, &clock.lo);
		c_large_integer pause_time(thisptr->paused_time_hi, thisptr->paused_time_lo);
		c_large_integer delta_time(clock.value() - pause_time.value());
		for (__int32 i = 0; i < thisptr->channels.count; i++)
		{
			HALO_CHANNEL *channel = thisptr->channels[i];
			for (__int32 j = 0; j < 2; j++)
			{
				if (!channel->queue[j].fmod_channel)
					continue;
				if (sound_plays_when_paused(channel->queue[j].sound_definition_index))
					continue;
				c_large_integer start_time;
				FMOD_Channel_GetDelay(channel->queue[j].fmod_channel, FMOD_DELAYTYPE_DSPCLOCK_START, &start_time.hi, &start_time.lo);
				start_time += delta_time;
				FMOD_Channel_SetDelay(channel->queue[j].fmod_channel, FMOD_DELAYTYPE_DSPCLOCK_START, start_time.hi, start_time.lo);
				FMOD_Channel_SetDelay(channel->queue[j].fmod_channel, FMOD_DELAYTYPE_DSPCLOCK_PAUSE, 0, 0);
				FMOD_Channel_SetPaused(channel->queue[j].fmod_channel, false);
			}
		}
	}
}

void __fastcall HALO_CHANNEL_Queue(HALO_CHANNEL *channel, void *unused, s_sound_tag_data *request) // 0x10A2FC60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HALO_CHANNEL_Queue@@YIXPAUHALO_CHANNEL@@PAXPAUs_sound_tag_data@@@Z");
	// `anonymous-namespace'::HALO_CHANNEL_Queue
	// static ...; // 0x10A2FEA0
	// HALO_CHANNEL *channel;
	// void *unused;
	// s_sound_tag_data *request;
	// __int32 queued_count;
		// char *permutation_name;
		// char const *tag_name;
		// unsigned __int32 length_pcm;
	// function call : bool (*)(HALO_PERM_SOUND *, s_sound_tag_data *, HALO_CHANNEL_PROPERTIES *, HALO_CHANNEL *)

	#line 1231 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\Audio.cpp"
		assert(channel->state != HALO_CHANNEL::_STATE_FULL);
		#line 1246 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\Audio.cpp"
	if (!SoundQueueFilter(request))
		return;
	if (SoundSystemTraceEnabled())
	{
		char const *tag_name = tag_get_name(request->sound_tag_index);
		char *permutation_name = Blam::Cache::StringIDCache::GetCurrent()->GetString(request->permutation->name);
		CDebugTrace::Trace(0xFF00FF00, "HALO_CHANNEL::Queue() (channel: %d, state: %s) %s [%s]", channel->id, HALO_CHANNEL::STATE_NAMES[channel->state], tag_name, permutation_name);
	}
	if (channel->state == HALO_CHANNEL::_STATE_FULL)
		return;
	__int32 queued_count = GetQueuedSoundCount(channel);
	if (HALO_PERM_SOUND::Init(&channel->queue[queued_count], request, &channel->properties, channel))
	{
		if (request->sound_definition->platform_codec.compression == _sound_compression_fsb)
		{
			unsigned __int32 length_pcm;
			FMOD_Sound_GetLength(channel->queue[queued_count].fmod_sound, &length_pcm, FMOD_TIMEUNIT_PCM);
			channel->queue[queued_count].sample_count = length_pcm;
		}
		if (++queued_count == 2)
			channel->state = HALO_CHANNEL::_STATE_FULL;
		else
			channel->state = HALO_CHANNEL::_STATE_PLAYING;
	}
}

void __fastcall HALO_PERM_SOUND_InitChannelProperties(HALO_PERM_SOUND *thisptr, void *unused, HALO_CHANNEL_PROPERTIES *channel_properties) // 0x10A30430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HALO_PERM_SOUND_InitChannelProperties@@YIXPAUHALO_PERM_SOUND@@PAXPAUHALO_CHANNEL_PROPERTIES@@@Z");
	// `anonymous-namespace'::HALO_PERM_SOUND_InitChannelProperties
	// static ...; // 0x10A30EF7
	// static ...; // 0x10A30EF0
	// static ...; // 0x10A30EC0
	// static ...; // 0x10A30EB8
	// HALO_PERM_SOUND *thisptr;
	// void *unused;
	// HALO_CHANNEL_PROPERTIES *channel_properties;
	// __int32 num_channels;
	// HALO_SOUND_SYSTEM *sound_system;
	// FMOD_SOUND *sound;
	// FMOD_CHANNELGROUP **channel_group;
	// float levels[16];
	// unsigned __int32 mode;
		// float max_distance;

	HALO_SOUND_SYSTEM *sound_system = HALO_SOUND_SYSTEM::Get();
	FMOD_CHANNELGROUP **channel_group;
	if ((thisptr->mixer_state->flags >> 4) & 1)
		channel_group = &sound_system->music_channel_group;
	else if ((thisptr->mixer_state->flags >> 2) & 1)
		channel_group = &sound_system->voice_channel_group;
	else if ((thisptr->mixer_state->flags >> 5) & 1)
		channel_group = &sound_system->sfx_channel_group;
	else
		channel_group = &sound_system->master_channel_group;
	FMOD_CheckError(FMOD_Channel_SetChannelGroup(thisptr->fmod_channel, *channel_group), "FMOD_Channel_SetChannelGroup(thisptr->fmod_channel, *channel_group)");
	unsigned __int32 mode = FMOD_2D;
	if (channel_properties->is_3d)
		mode = FMOD_3D;
	FMOD_CheckError(FMOD_Channel_SetMode(thisptr->fmod_channel, mode), "FMOD_Channel_SetMode(thisptr->fmod_channel, mode)");
	FMOD_SOUND *sound;
	__int32 num_channels = 1;
	if (FMOD_Channel_GetCurrentSound(thisptr->fmod_channel, &sound) == FMOD_OK)
		FMOD_CheckError(FMOD_Sound_GetFormat(thisptr->fmod_sound, 0, 0, &num_channels, 0), "FMOD_Sound_GetFormat(thisptr->fmod_sound, 0, 0, &num_channels, 0)");
	if (channel_properties->is_3d)
	{
		FMOD_CheckError(FMOD_Channel_Set3DDopplerLevel(thisptr->fmod_channel, 0.0), "FMOD_Channel_Set3DDopplerLevel(thisptr->fmod_channel, 0.0)");
		FMOD_CheckError(FMOD_Channel_Set3DConeSettings(thisptr->fmod_channel, (float)(channel_properties->insideconeangle * 180.0) / 3.1415927, (float)(channel_properties->outsideconeangle * 180.0) / 3.1415927, channel_properties->outsidevolume), "FMOD_Channel_Set3DConeSettings( thisptr->fmod_channel, (float)(channel_properties->insideconeangle * 180.0) / 3.1415927, (float)(channel_properties->outsideconeangle * 180.0) / 3.1415927, channel_properties->outsidevolume)");
		if (num_channels <= 2)
			FMOD_Channel_SetSpeakerMix(thisptr->fmod_channel, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0);
		float max_distance = 0.0f;
		FMOD_CheckError(FMOD_Channel_Get3DMinMaxDistance(thisptr->fmod_channel, 0, &max_distance), "FMOD_Channel_Get3DMinMaxDistance(thisptr->fmod_channel, 0, &max_distance)");
		FMOD_CheckError(FMOD_Channel_Set3DMinMaxDistance(thisptr->fmod_channel, max_distance, max_distance), "FMOD_Channel_Set3DMinMaxDistance(thisptr->fmod_channel, max_distance, max_distance)");
		FMOD_CheckError(FMOD_Channel_Set3DSpread(thisptr->fmod_channel, 45.0), "FMOD_Channel_Set3DSpread(thisptr->fmod_channel, 45.0)");
		return;
	}
	float levels[16];
	if (num_channels == 4)
	{
		levels[0] = 1.0f;
		levels[1] = 0.0f;
		levels[2] = 0.0f;
		levels[3] = 0.0f;
		levels[4] = 0.0f;
		levels[5] = 0.0f;
		FMOD_CheckError(FMOD_Channel_SetSpeakerLevels(thisptr->fmod_channel, FMOD_SPEAKER_FRONT_LEFT, levels, 4), "FMOD_Channel_SetSpeakerLevels(thisptr->fmod_channel, FMOD_SPEAKER_FRONT_LEFT, levels, 4)");
		levels[0] = 0.0f;
		levels[1] = 1.0f;
		levels[2] = 0.0f;
		levels[3] = 0.0f;
		levels[4] = 0.0f;
		levels[5] = 0.0f;
		FMOD_Channel_SetSpeakerLevels(thisptr->fmod_channel, FMOD_SPEAKER_FRONT_RIGHT, levels, 4);
		levels[0] = 0.0f;
		levels[1] = 0.0f;
		levels[2] = 1.0f;
		levels[3] = 0.0f;
		levels[4] = 0.0f;
		levels[5] = 0.0f;
		FMOD_Channel_SetSpeakerLevels(thisptr->fmod_channel, FMOD_SPEAKER_BACK_LEFT, levels, 4);
		levels[0] = 0.0f;
		levels[1] = 0.0f;
		levels[2] = 0.0f;
		levels[3] = 1.0f;
		levels[4] = 0.0f;
		levels[5] = 0.0f;
		FMOD_Channel_SetSpeakerLevels(thisptr->fmod_channel, FMOD_SPEAKER_BACK_RIGHT, levels, 4);
	}
	else if (num_channels == 6)
	{
		levels[0] = 1.0f;
		levels[1] = 0.0f;
		levels[2] = 0.0f;
		levels[3] = 0.0f;
		levels[4] = 0.0f;
		levels[5] = 0.0f;
		FMOD_CheckError(FMOD_Channel_SetSpeakerLevels(thisptr->fmod_channel, FMOD_SPEAKER_FRONT_LEFT, levels, 6), "FMOD_Channel_SetSpeakerLevels(thisptr->fmod_channel, FMOD_SPEAKER_FRONT_LEFT, levels, 6)");
		levels[0] = 0.0f;
		levels[1] = 1.0f;
		levels[2] = 0.0f;
		levels[3] = 0.0f;
		levels[4] = 0.0f;
		levels[5] = 0.0f;
		FMOD_Channel_SetSpeakerLevels(thisptr->fmod_channel, FMOD_SPEAKER_FRONT_RIGHT, levels, 6);
		levels[0] = 0.0f;
		levels[1] = 0.0f;
		levels[2] = 1.0f;
		levels[3] = 0.0f;
		levels[4] = 0.0f;
		levels[5] = 0.0f;
		FMOD_Channel_SetSpeakerLevels(thisptr->fmod_channel, FMOD_SPEAKER_FRONT_CENTER, levels, 6);
		levels[0] = 0.0f;
		levels[1] = 0.0f;
		levels[2] = 0.0f;
		levels[3] = 1.0f;
		levels[4] = 0.0f;
		levels[5] = 0.0f;
		FMOD_Channel_SetSpeakerLevels(thisptr->fmod_channel, FMOD_SPEAKER_LOW_FREQUENCY, levels, 6);
		levels[0] = 0.0f;
		levels[1] = 0.0f;
		levels[2] = 0.0f;
		levels[3] = 0.0f;
		levels[4] = 1.0f;
		levels[5] = 0.0f;
		FMOD_Channel_SetSpeakerLevels(thisptr->fmod_channel, FMOD_SPEAKER_BACK_LEFT, levels, 6);
		levels[0] = 0.0f;
		levels[1] = 0.0f;
		levels[2] = 0.0f;
		levels[3] = 0.0f;
		levels[4] = 0.0f;
		levels[5] = 1.0f;
		FMOD_Channel_SetSpeakerLevels(thisptr->fmod_channel, FMOD_SPEAKER_BACK_RIGHT, levels, 6);
	}
	else if ((thisptr->mixer_state->flags >> 4) & 1)
	{
		FMOD_CheckError(FMOD_Channel_SetSpeakerMix(thisptr->fmod_channel, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0), "FMOD_Channel_SetSpeakerMix(thisptr->fmod_channel, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0)");
	}
	else if ((thisptr->mixer_state->flags >> 2) & 1)
	{
		FMOD_CheckError(FMOD_Channel_SetSpeakerMix(thisptr->fmod_channel, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0), "FMOD_Channel_SetSpeakerMix(thisptr->fmod_channel, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0)");
	}
	else if (thisptr->mixer_state->flags & 1)
	{
		FMOD_CheckError(FMOD_Channel_SetSpeakerMix(thisptr->fmod_channel, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0), "FMOD_Channel_SetSpeakerMix(thisptr->fmod_channel, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)");
	}
}

void __fastcall HALO_PERM_SOUND_UpdateChannelProperties(HALO_PERM_SOUND *thisptr, void *unused, HALO_CHANNEL_PROPERTIES *channel_properties) // 0x10A311D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HALO_PERM_SOUND_UpdateChannelProperties@@YIXPAUHALO_PERM_SOUND@@PAXPAUHALO_CHANNEL_PROPERTIES@@@Z");
	// `anonymous-namespace'::HALO_PERM_SOUND_UpdateChannelProperties
	// static ...; // 0x10A3153A
	// static ...; // 0x10A31528
	// static ...; // 0x10A314F8
	// static ...; // 0x10A314F0
	// HALO_PERM_SOUND *thisptr;
	// void *unused;
	// HALO_CHANNEL_PROPERTIES *channel_properties;
	// float frequency;
	// HALO_SOUND_SYSTEM *sound_system;
	// float volume;
	// float playback_rate_scale;
	// FMOD_SOUND *current_sound;
	// float (*const calculate_distance_attenuation)(float *, float);
		// float envelope[4];
		// __int32 room;
		// FMOD_REVERB_CHANNELPROPERTIES reverb_properties;
	// function call : float (*const)(float *, float)

	float (*const calculate_distance_attenuation)(float *, float) = reinterpret_cast<float (*)(float *, float)>(0x662EB0);
	HALO_SOUND_SYSTEM *sound_system = HALO_SOUND_SYSTEM::Get();
	float volume = channel_properties->unknown_gain_factor * channel_properties->gain;
	if (channel_properties->is_3d)
	{
		float envelope[4];
		envelope[1] = channel_properties->d4;
		envelope[0] = channel_properties->d3;
		envelope[2] = channel_properties->d1;
		envelope[3] = channel_properties->d2;
		volume *= calculate_distance_attenuation(envelope, channel_properties->min_listener_distance);
	}
	FMOD_CheckError(FMOD_Channel_SetVolume(thisptr->fmod_channel, volume), "FMOD_Channel_SetVolume(thisptr->fmod_channel, volume)");
	float playback_rate_scale = channel_properties->playback_rate_scale;
	if (abs(playback_rate_scale) <= 0.000001f)
		playback_rate_scale = 1.0f;
	FMOD_SOUND *current_sound = nullptr;
	float frequency = 0.0f;
	FMOD_CheckError(FMOD_Channel_GetCurrentSound(thisptr->fmod_channel, &current_sound), "FMOD_Channel_GetCurrentSound(thisptr->fmod_channel, &current_sound)");
	if (FMOD_Sound_GetDefaults(current_sound, &frequency, nullptr, nullptr, nullptr) == FMOD_OK)
		FMOD_CheckError(FMOD_Channel_SetFrequency(thisptr->fmod_channel, frequency * playback_rate_scale), "FMOD_Channel_SetFrequency(thisptr->fmod_channel, frequency * playback_rate_scale)");
	if (channel_properties->is_3d)
	{
		FMOD_CheckError(FMOD_Channel_Set3DAttributes(thisptr->fmod_channel, &channel_properties->position, &channel_properties->velocity), "FMOD_Channel_Set3DAttributes(thisptr->fmod_channel, &channel_properties->position, &channel_properties->velocity)");
		FMOD_CheckError(FMOD_Channel_Set3DConeOrientation(thisptr->fmod_channel, &channel_properties->forward), "FMOD_Channel_Set3DConeOrientation(thisptr->fmod_channel, &channel_properties->forward)");
		FMOD_CheckError(FMOD_Channel_Set3DOcclusion(thisptr->fmod_channel, channel_properties->direct_occlusion * channel_properties->reverb_occlusion * 0.66999996 + 0.33000001, channel_properties->reverb_occlusion), "FMOD_Channel_Set3DOcclusion( thisptr->fmod_channel, channel_properties->direct_occlusion * channel_properties->reverb_occlusion * 0.66999996 + 0.33000001, channel_properties->reverb_occlusion)");
		FMOD_REVERB_CHANNELPROPERTIES reverb_properties;
		memset(&reverb_properties, 0, sizeof(reverb_properties));
		reverb_properties.Flags = 0x16;
		__int32 room = (__int32)floorf(channel_properties->reverb_room_factor * 100.0);
		reverb_properties.Room = room;
		reverb_properties.RoomHF = room;
		FMOD_CheckError(FMOD_Channel_SetReverbProperties(thisptr->fmod_channel, &reverb_properties), "FMOD_Channel_SetReverbProperties(thisptr->fmod_channel, &reverb_properties)");
	}
}

FMOD_RESULT CreateSoundHook(s_sound_tag_data *request, FMOD_SOUND **sound, void **out_data) // 0x10A2E5A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CreateSoundHook@@YA?AW4FMOD_RESULT@@PAUs_sound_tag_data@@PAPAUFMOD_SOUND@@PAPAX@Z");
	// `anonymous-namespace'::CreateSoundHook
	// static ...; // 0x10A2EB53
	// static ...; // 0x10A2EB4C
	// static ...; // 0x10A2EB34
	// static ...; // 0x10A2EB2C
// $LN10:
// $LN9:
// $LN8:
// $LN7:
// $LN6:
	// s_sound_tag_data *request;
	// FMOD_SOUND **sound;
	// void **out_data;
	// s_sound_definition *sound_definition;
	// void *raw_address;
	// unsigned long sample_size;
	// unsigned char compression_type;
	// char const *compression_name;
	// s_sound_permutation_chunk *chunk;
	// unsigned long length;
	// HALO_SOUND_SYSTEM *sound_system;
	// unsigned long raw_size;
	// FMOD_CREATESOUNDEXINFO exinfo;
	// __int32 *g_sound_encoding_numchannels;
	// void *sample_address;
	// bool should_stream;
	// FMOD_RESULT result;
	// unsigned __int32 mode;
		// char *permutation_name;
		// char const *tag_name;

	HALO_SOUND_SYSTEM *sound_system = HALO_SOUND_SYSTEM::Get();
	__int32 *g_sound_encoding_numchannels = (__int32 *)0x166B1FC;
	s_sound_definition *sound_definition = request->sound_definition;
	s_sound_permutation_chunk *chunk = &request->permutation->permutation_chunks[0];
	unsigned long raw_size;
	void *raw_address = sound_cache_sound_hardware_lock(chunk, &raw_size);
	if (!raw_address || chunk->offset < 0 || chunk->offset > raw_size)
	{
		sound_cache_sound_hardware_unlock(chunk);
		return FMOD_ERR_FORMAT;
	}
	void *sample_address = offset_pointer(raw_address, chunk->offset);
	unsigned long sample_size = chunk->encoded_size & 0x3FFFFFF;
	bool should_stream = sound_definition->platform_codec.load_mode == _sound_load_mode_stream;
	FMOD_CREATESOUNDEXINFO exinfo;
	memset(&exinfo, 0, sizeof(exinfo));
	exinfo.cbsize = sizeof(exinfo);
	exinfo.userdata = chunk;
	unsigned __int32 mode = 0xA004048;
	unsigned long length = 0;
	unsigned char compression_type = sound_definition->platform_codec.compression;
	char const *compression_name = nullptr;
	switch (compression_type)
	{
	case 3:
		compression_name = "pcm";
		break;
	case 8:
		compression_name = "mpeg";
		break;
	case 9:
		compression_name = "fsb";
		break;
	case 32:
		compression_name = "ogg-vorbis";
		break;
	default:
		compression_name = "<unknown>";
		break;
	}
	length = sample_size;
	if (compression_type == 3)
	{
		mode |= 0x10000000;
		mode |= 0x1000;
		exinfo.format = FMOD_SOUND_FORMAT_PCM16;
		exinfo.numchannels = g_sound_encoding_numchannels[(unsigned char)sound_definition->platform_codec.encoding];
		exinfo.defaultfrequency = g_sample_rates[(unsigned char)sound_definition->sample_rate];
		sample_address = offset_pointer(sample_address, 16);
		length = sample_size - 32;
	}
	else if (compression_type == 8)
	{
		mode |= 0x10000000;
		if (!should_stream)
			mode |= 0x200;
		exinfo.suggestedsoundtype = FMOD_SOUND_TYPE_MPEG;
	}
	else if (compression_type == 9)
	{
		mode |= 0x10000000;
		if (!should_stream)
			mode |= 0x200;
		exinfo.suggestedsoundtype = FMOD_SOUND_TYPE_FSB;
	}
	else if (compression_type == 32)
	{
	}
	else
	{
		mode |= 0x10000000;
	}
	exinfo.length = length;
	FMOD_RESULT result = FMOD_ERR_INTERNAL;
	if (compression_type == 32)
		result = ::Audio::FMOD::CreateOggVorbisStream(sound_system->fmod_system, sample_address, length, mode, sound);
	else if (should_stream)
		result = FMOD_System_CreateStream(sound_system->fmod_system, (char const *)sample_address, mode, &exinfo, sound);
	else
		result = FMOD_System_CreateSound(sound_system->fmod_system, (char const *)sample_address, mode, &exinfo, sound);
	if (result != FMOD_OK)
	{
		sound_cache_sound_hardware_unlock(chunk);
		if (SoundSystemTraceEnabled())
		{
			char const *tag_name = tag_get_name(request->sound_tag_index);
			char *permutation_name = Blam::Cache::StringIDCache::GetCurrent()->GetString(request->permutation->name);
			CDebugTrace::Trace(0xFFFF0000, "CreateSound() failed. (Error: %s) %s [%s]", FMOD_ErrorString(result), tag_name, permutation_name);
		}
	}
	else if (SoundSystemTraceEnabled())
	{
		char const *tag_name = tag_get_name(request->sound_tag_index);
		char *permutation_name = Blam::Cache::StringIDCache::GetCurrent()->GetString(request->permutation->name);
		CDebugTrace::Trace(0xFF00FFFF, "CreateSound() codec: %s, %s [%s]", compression_name, tag_name, permutation_name);
	}
	return result;
}

FMOD_RESULT FMOD_Sound_ReleaseSub_Hook(FMOD_SOUND *sound, FMOD_SYSTEM **out_system) // 0x10A2F770
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FMOD_Sound_ReleaseSub_Hook@@YA?AW4FMOD_RESULT@@PAUFMOD_SOUND@@PAPAUFMOD_SYSTEM@@@Z");
	// `anonymous-namespace'::FMOD_Sound_ReleaseSub_Hook
	// static ...; // 0x10A2F800
	// static ...; // 0x10A2F7F8
	// FMOD_SOUND *sound;
	// FMOD_SYSTEM **out_system;
	// s_sound_permutation_chunk *chunk;
	// FMOD_RESULT (*const _FMOD_Sound_GetSystemObject)(FMOD_SOUND *, FMOD_SYSTEM **);
	// function call : FMOD_RESULT (*const)(FMOD_SOUND *, FMOD_SYSTEM **)

	FMOD_RESULT (*const _FMOD_Sound_GetSystemObject)(FMOD_SOUND *, FMOD_SYSTEM **) = (FMOD_RESULT (*const)(FMOD_SOUND *, FMOD_SYSTEM **))0x139eb22;
	s_sound_permutation_chunk *chunk;

	if (FMOD_Sound_GetUserData(sound, (void **)&chunk) == FMOD_OK && chunk)
	{
		sound_cache_sound_hardware_unlock(chunk);
	}

	return _FMOD_Sound_GetSystemObject(sound, out_system);
}

__int32 sound_permutation_get_unique_id(s_sound_permutation *permutation) // 0x10A35F00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_permutation_get_unique_id@@YAHPAUs_sound_permutation@@@Z");
	// `anonymous-namespace'::sound_permutation_get_unique_id
	// s_sound_permutation *permutation;

	return (__int32)permutation;
}

void loop_track_fade_hook(long definition_index, bool is_alternate, __int32 reason, float seconds, long sound_index) // 0x10A34370
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?loop_track_fade_hook@@YAXJ_NHMJ@Z");
	// `anonymous-namespace'::loop_track_fade_hook
	// long sound_index;
	// void (*const loop_track_fade)(long, bool, __int32, float, long);
		// s_user_interface_shared_globals *wigl;
		// unsigned long lobby_countdown_seconds;
	// function call : bool (*const)()
	// function call : s_user_interface_shared_globals *(*const)()
	// function call : void (*const)(long, bool, __int32, float, long)

	const auto loop_track_fade = (void(*)(long, bool, __int32, float, long))0x664490;

	if (((bool(*)())0x531E90)())
	{
		s_user_interface_shared_globals *wigl;
		unsigned long lobby_countdown_seconds;

		wigl = ((s_user_interface_shared_globals *(*)())0xA84D20)();
		lobby_countdown_seconds = Modules::ModuleServer::Instance().VarServerCountdownLobby->ValueInt;
		if (definition_index == wigl->main_menu_music.index)
		{
			if (lobby_countdown_seconds > 0)
			{
				seconds = (float)Modules::ModuleServer::Instance().VarServerCountdownLobby->ValueInt - 0.5f;
			}
		}
	}

	loop_track_fade(definition_index, is_alternate, reason, seconds, sound_index);
}

void channel_signal_complete(short channel_index) // 0x10A331A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?channel_signal_complete@@YAXF@Z");
	// `anonymous-namespace'::channel_signal_complete
	// short channel_index;
	// sound_channel_datum *channel;
		// char *permutation_name;
		// char const *tag_name;
		// HALO_CHANNEL *haloChannel;

	sound_channel_datum *channel = &(*g_sound_channels)[channel_index];
	if (SoundSystemTraceEnabled())
	{
		char const *tag_name = tag_get_name(channel->playing_sound_definition_index);
		char *permutation_name = Blam::Cache::StringIDCache::GetCurrent()->GetString(channel->playing_permutation->name);
		HALO_CHANNEL *haloChannel = HALO_SOUND_SYSTEM::Get()->FindChannel(channel->hardware_source_index);
		CDebugTrace::Trace(0xFFFFFF00, "channel_signal_complete() (channel: %d, state: %s) %s [%s]", haloChannel->id, HALO_CHANNEL::STATE_NAMES[haloChannel->state], tag_name, permutation_name);
	}
}

void refresh_channel(short channel_index) // 0x10A34780
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?refresh_channel@@YAXF@Z");
	// `anonymous-namespace'::refresh_channel
	// short channel_index;
	// sound_channel_datum *channel;
	// bool (*const sound_permutation_release)(s_sound_permutation_chunk *);
	// bool (*const sound_permutation_available_to_start)(s_sound_permutation_chunk *);
	// short state;
		// s_sound_permutation_chunk *next_chunk;
		// s_sound_permutation_chunk *chunk;
		// s_sound_permutation_chunk *playing_chunk;
	// function call : short (*const)(long)
	// function call : s_sound_permutation_chunk *(*const)(s_sound_permutation *, short)
	// function call : bool (*const)(s_sound_permutation_chunk *)
	// function call : short (*const)(s_sound_permutation *, short)
	// function call : s_sound_permutation_chunk *(*const)(s_sound_permutation *, short)
	// function call : bool (*const)(s_sound_permutation_chunk *)
	// function call : s_sound_permutation_chunk *(*const)(s_sound_permutation *, short)
	// function call : bool (*const)(s_sound_permutation_chunk *)

	bool (*const sound_permutation_available_to_start)(s_sound_permutation_chunk *) = reinterpret_cast<bool (*)(s_sound_permutation_chunk *)>(0x660270);
	bool (*const sound_permutation_release)(s_sound_permutation_chunk *) = reinterpret_cast<bool (*)(s_sound_permutation_chunk *)>(0x660150);
	sound_channel_datum *channel = &(*g_sound_channels)[channel_index];
	if (channel->hardware_source_index == -1)
		return;
	if (channel->flags & 1)
		return;
	if (!channel->playing_permutation)
		return;
	short state = ((short (*)(long))0x667850)(channel->hardware_source_index);
	if (channel->queued_permutation && state < 5)
	{
		s_sound_permutation_chunk *chunk = ((s_sound_permutation_chunk *(*)(s_sound_permutation *, unsigned short))0x662890)(channel->playing_permutation, channel->playing_chunk_index);
		sound_permutation_release(chunk);
		if (((short (*)(s_sound_permutation *, unsigned short))0x6628F0)(channel->playing_permutation, channel->playing_chunk_index) == -1)
			channel->playing_time_seconds = 0.0f;
		channel->refresh_counter++;
		channel->playing_sound_definition_index = channel->queued_sound_definition_index;
		channel->playing_permutation = channel->queued_permutation;
		channel->playing_chunk_index = channel->queued_chunk_index;
		channel->queued_sound_definition_index = -1;
		channel->queued_permutation = nullptr;
		channel->queued_chunk_index = -1;
		s_sound_permutation_chunk *next_chunk = ((s_sound_permutation_chunk *(*)(s_sound_permutation *, unsigned short))0x662890)(channel->playing_permutation, channel->playing_chunk_index);
		if (!sound_permutation_available_to_start(next_chunk))
			state = 0;
	}
	if (channel->playing_permutation && state < 4)
	{
		s_sound_permutation_chunk *playing_chunk = ((s_sound_permutation_chunk *(*)(s_sound_permutation *, unsigned short))0x662890)(channel->playing_permutation, channel->playing_chunk_index);
		sound_permutation_release(playing_chunk);
		channel->playing_sound_definition_index = -1;
		channel->playing_permutation = nullptr;
		channel->playing_chunk_index = -1;
	}
	if (platform_sound_source_is_playing(channel->hardware_source_index))
		channel->playing_time_seconds += (*g_sound_manager_globals)->frame_delta_time_seconds;
}

void refresh_channels() // 0x10A34A80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?refresh_channels@@YAXXZ");
	// `anonymous-namespace'::refresh_channels
	// procedure flags: nofpo
		// __int32 i;

	for (long i = 0; i < (*g_sound_manager_globals)->channel_count; i++)
	{
		refresh_channel((short)i);
	}
}

void build_channel_transmission_sources_hook(void *listener, void *voices, void *sources) // 0x10A330C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?build_channel_transmission_sources_hook@@YAXPAX00@Z");
	// `anonymous-namespace'::build_channel_transmission_sources_hook
	// void *sources;
	// void (*const build_channel_transmission_sources)(void *, void *, void *);
	// function call : void (*const)(void *, void *, void *)

	const auto build_channel_transmission_sources = (void(*)(void *, void *, void *))0x51B070;

	memset(&g_channel_transmission_sources1, 0, sizeof(g_channel_transmission_sources1));
	memset(&g_channel_transmission_sources2, 0, sizeof(g_channel_transmission_sources2));
	build_channel_transmission_sources(listener, g_channel_transmission_sources1, g_channel_transmission_sources2);
}

void update_hardware_channels_hook(void *a1, void *a2) // 0x10A36230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?update_hardware_channels_hook@@YAXPAX0@Z");
	// `anonymous-namespace'::update_hardware_channels_hook
	// void *a2;
	// void (*const update_hardware_channels)(void *, void *);
	// function call : void (*const)(void *, void *)

	void (__cdecl *const update_hardware_channels)(void *, void *) = (void(__cdecl *const)(void *, void *))0x51b7d0;

	memset(&g_channel_transmission_sources1, 0, 896);
	memset(&g_channel_transmission_sources2, 0, 896);
	update_hardware_channels(&g_channel_transmission_sources1, &g_channel_transmission_sources2);
}

short sound_commit_looping_find_pitch_range_by_pitch_hook(s_sound_definition *sndDef, float pitchModifier, short fallbackIndex) // 0x10A35CD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_commit_looping_find_pitch_range_by_pitch_hook@@YAFPAUs_sound_definition@@MF@Z");
	// `anonymous-namespace'::sound_commit_looping_find_pitch_range_by_pitch_hook
	// static ...; // 0x10A35E70
	// s_sound_definition *sndDef;
	// float pitchModifier;
	// short fallbackIndex;
	// short ret;
	// short (*const sound_definition_find_pitch_range_by_pitch)(void *, float, short);
		// long sound_tag_index;
		// char message[4096];
			// __int32 i;
				// s_cache_tag_instance *tag;
	// function call : short (*const)(void *, float, short)
	// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)
	// function call : void ()

	short (*const sound_definition_find_pitch_range_by_pitch)(void *, float, short) = reinterpret_cast<short (*)(void *, float, short)>(0x661C20);
	short ret = sound_definition_find_pitch_range_by_pitch(sndDef, pitchModifier, fallbackIndex);
	if (ret < 0 || ret >= sndDef->pitch_ranges.count)
	{
		long sound_tag_index = -1;
		for (__int32 i = 0; i < g_cache_file_tag_globals->loaded_instance_count; i++)
		{
			s_cache_tag_instance *tag = g_cache_file_tag_globals->instances[i];
			if (sndDef == offset_pointer(tag, tag->definition_offset))
				sound_tag_index = g_cache_file_tag_globals->absolute_index_index_map[i];
		}
		#line 1809 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\Audio.cpp"
			assert(sound_tag_index);
			#line 1824 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\Audio.cpp"
		char message[4096];
		sprintf_s(message, "Pitch range not found! (Report this please)\n\ntag: %s\nret: %d\npitch: %f", tag_get_name(sound_tag_index), ret, pitchModifier);
		MessageBoxA(nullptr, message, "Pitch range not found!", 0);
		DebugBreak();
	}
	if (ret == -1)
		ret = 0;
	return ret;
}

bool sound_attachment_is_sky_hook(long object_index) // 0x10A34B40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_attachment_is_sky_hook@@YA_NJ@Z");
	// `anonymous-namespace'::sound_attachment_is_sky_hook
	// long object_index;
	// s_object_header *object_header;
	// function call : long (*const)(long)

	object_index = ((long(__cdecl *)(long))0xB2EAB0)(object_index);
	s_object_header *object_header = object_header_get(object_index);
	if (!object_header || object_header->type != _object_type_scenery)
	{
		return false;
	}
	return *(unsigned long *)((unsigned char *)object_header->data + 0x178) & 4;
}

void unit_set_mouth_aperture_hook(long unit_index, float t) // 0x10A36130
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_set_mouth_aperture_hook@@YAXJM@Z");
	// `anonymous-namespace'::unit_set_mouth_aperture_hook
	// float t;
	// float const k_max_step;
	// s_unit_data *unit;

	const float k_max_step = 0.3f;

	s_unit_data *unit = (s_unit_data *)object_get(unit_index);

	unit->mouth_aperture += fminf(fmaxf(t - unit->mouth_aperture, -k_max_step), k_max_step);
}

void OnAudioDeviceEvent(::Audio::SAudioDeviceEvent const &e) // 0x10A31D40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnAudioDeviceEvent@@YAXABUSAudioDeviceEvent@Audio@@@Z");
	// `anonymous-namespace'::OnAudioDeviceEvent
	// static ...; // 0x10A31DEC
	// static ...; // 0x10A31DE0
	// static ...; // 0x10A31DD8
	// Audio::SAudioDeviceEvent const &e;
	// FMOD_SYSTEM *fmod_system;
	// HALO_SOUND_SYSTEM *sound_system;
	// FMOD_OUTPUTTYPE output;

	HALO_SOUND_SYSTEM *sound_system = HALO_SOUND_SYSTEM::Get();
	FMOD_SYSTEM *fmod_system = sound_system->fmod_system;

	if (!sound_system || !fmod_system)
		return;

	if (Modules::ModuleSettings::Instance().VarAudioOutputDevice->ValueInt)
		return;

	FMOD_OUTPUTTYPE output;
	FMOD_System_GetOutput(fmod_system, &output);
	FMOD_System_SetOutput(fmod_system, output);
	FMOD_System_SetDriver(fmod_system, 0);
}

void sound_cache_sound_delete_hook(s_sound_permutation_chunk *chunk) // 0x10A352F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_cache_sound_delete_hook@@YAXPAUs_sound_permutation_chunk@@@Z");
	// `anonymous-namespace'::sound_cache_sound_delete_hook
	// s_sound_permutation_chunk *chunk;
	// function call : void (*const)(s_data_array *, long)
	// function call : void (*const)(s_lruv_cache *, long)

	if (chunk->runtime_index != -1)
	{
		datum_delete(*g_xbox_sounds, chunk->runtime_index);
		((void(*)(s_lruv_cache *, long))0x9668F0)(g_xbox_sound_cache, chunk->runtime_index);
	}
}

void *sound_cache_sound_hardware_lock(s_sound_permutation_chunk *chunk, unsigned long *out_size) // 0x10A35490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_cache_sound_hardware_lock@@YAPAXPAUs_sound_permutation_chunk@@PAK@Z");
	// `anonymous-namespace'::sound_cache_sound_hardware_lock
	// unsigned long *out_size;
	// s_xbox_sound_datum_ex *cache_sound;

	s_xbox_sound_datum_ex *cache_sound = (s_xbox_sound_datum_ex *)(*g_xbox_sounds)->try_and_get(chunk->runtime_index);
	SoundCacheDebugLog(1, 0xFFFF00FF, "sound_cache_sound_hardware_lock() %s, chunk %x", tag_get_name(cache_sound->sound_tag_index), chunk);
	if (cache_sound->hardware_reference_count < 0xFF)
		cache_sound->hardware_reference_count++;
	*out_size = cache_sound->size;
	return cache_sound->buffer;
}

void sound_cache_sound_hardware_unlock(s_sound_permutation_chunk *chunk) // 0x10A35580
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_cache_sound_hardware_unlock@@YAXPAUs_sound_permutation_chunk@@@Z");
	// `anonymous-namespace'::sound_cache_sound_hardware_unlock
	// s_sound_permutation_chunk *chunk;
	// s_xbox_sound_datum_ex *cache_sound;

	s_xbox_sound_datum_ex *cache_sound = (s_xbox_sound_datum_ex *)(*g_xbox_sounds)->try_and_get(chunk->runtime_index);
	if (!cache_sound)
		return;
	SoundCacheDebugLog(1, 0xFFFF00FF, "sound_cache_sound_hardware_unlock() %s, chunk %x", tag_get_name(cache_sound->sound_tag_index), chunk);
	if (cache_sound->hardware_reference_count > 0)
		cache_sound->hardware_reference_count--;
}

void sound_cache_delete_block_proc(void *context, long block_index, bool moved) // 0x10A34C30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_cache_delete_block_proc@@YAXPAXJ_N@Z");
	// `anonymous-namespace'::sound_cache_delete_block_proc
	// bool moved;
	// s_xbox_sound_datum_ex *cache_sound;
	// s_sound_permutation_chunk *chunk;
		// s_sound_permutation_chunk *next;
	// function call : void (*const)(s_data_array *, long)

	s_xbox_sound_datum_ex *cache_sound = (s_xbox_sound_datum_ex *)(*g_xbox_sounds)->try_and_get(block_index);
	if (!cache_sound)
	{
		SoundCacheDebugLog(4, 0xFFFF0000, "sound_cache_delete_block_proc() data out of sync (block: %x)", block_index);
		return;
	}
	SoundCacheDebugLog(2, 0xFFFFFF00, "sound_cache_delete_block_proc() purged %s, chunk: %x", tag_get_name(cache_sound->sound_tag_index), cache_sound->chunk);
	if (cache_sound->hardware_reference_count || cache_sound->software_reference_count || cache_sound->io_pending())
		SoundCacheDebugLog(4, 0xFFFF0000, "sound_cache_delete_block_proc() %s tried to purge sound that was in use (sw_refs: %d, hw_refs: %d, io: %d)", tag_get_name(cache_sound->sound_tag_index), cache_sound->software_reference_count, cache_sound->hardware_reference_count, cache_sound->is_loading);
	s_sound_permutation_chunk *chunk = cache_sound->chunk;
	do
	{
		s_sound_permutation_chunk *next = chunk->next;
		chunk->runtime_index = -1;
		chunk->next = nullptr;
		chunk = next;
	}
	while (chunk);
	datum_delete(*g_xbox_sounds, block_index);
}

bool sound_cache_locked_block_proc(void *context, long block_index) // 0x10A35070
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_cache_locked_block_proc@@YA_NPAXJ@Z");
	// `anonymous-namespace'::sound_cache_locked_block_proc
	// long block_index;
	// s_xbox_sound_datum_ex *cache_sound;

	s_xbox_sound_datum_ex *cache_sound;

	cache_sound = (s_xbox_sound_datum_ex *)(*g_xbox_sounds)->try_and_get(block_index);
	if (!cache_sound)
	{
		return false;
	}

	if (cache_sound->software_reference_count || cache_sound->hardware_reference_count)
	{
		return true;
	}

	if (cache_sound->io_pending())
	{
		return true;
	}

	return false;
}

void sound_cache_idle_hook() // 0x10A35010
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_cache_idle_hook@@YAXXZ");
	// `anonymous-namespace'::sound_cache_idle_hook
	// procedure flags: nofpo
	// function call : void (*const)(s_lruv_cache *)

	((void(__cdecl *const)(s_lruv_cache *))0x9677b0)(g_xbox_sound_cache);
}

void sound_cache_new_hook() // 0x10A35120
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_cache_new_hook@@YAXXZ");
	// `anonymous-namespace'::sound_cache_new_hook
	// procedure flags: nofpo
	// unsigned long const memory_size;
	// function call : void *(*const)(char const *, long, unsigned long, long, void *)
	// function call : s_lruv_cache *(*const)(char const *, long, long, long, void *, void (*)(void *, long, bool), bool (*)(void *, long), unsigned char (*)(void *, long), c_allocation_interface *, long)
	// function call : void (*const)(s_lruv_cache *, e_hole_algorithm)

	*g_xbox_sounds = (c_data_array<s_xbox_sound_datum> *)data_new("xbox sound", 512, 32, 0, *(void **)0x189D394);
	g_xbox_sound_cache = ((s_lruv_cache *(*)(char const *, long, long, long, long, void (*)(void *, long, bool), bool (*)(void *, long), long, void *, long))0x9678D0)("xbox sound cache", 0x2000, 14, 512, 0, sound_cache_delete_block_proc, sound_cache_locked_block_proc, 0, *(void **)0x189D394, -1);
	((void (*)(s_lruv_cache *, long))0x967AC0)(g_xbox_sound_cache, 2);
	unsigned long const memory_size = (1 << g_xbox_sound_cache->page_size_bits) * g_xbox_sound_cache->maximum_page_count;
	g_sound_cache_memory = c_physical_memory_manager::allocate((e_physical_memory_stage)0, "sound cache", memory_size, 2, nullptr);
	#line 2033 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\Audio.cpp"
		assert(g_sound_cache_memory);
		#line 2025 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\Audio.cpp"
}

long find_cache_block_for_sound(long definition_index) // 0x10A34130
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?find_cache_block_for_sound@@YAJJ@Z");
	// `anonymous-namespace'::find_cache_block_for_sound
	// static ...; // 0x10A341F4
	// static ...; // 0x10A341E8
	// static ...; // 0x10A341E0
	// long definition_index;
		// c_data_iterator<s_xbox_sound_datum> it;

	for (c_data_iterator<s_xbox_sound_datum> it = (*g_xbox_sounds)->begin(); it != (*g_xbox_sounds)->end(); ++it)
	{
		if (it->sound_tag_index == definition_index)
		{
			return it.current_datum_index;
		}
	}

	return -1;
}

void sound_cache_sound_new(long definition_index, s_sound_permutation_chunk *chunk) // 0x10A35650
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_cache_sound_new@@YAXJPAUs_sound_permutation_chunk@@@Z");
	// `anonymous-namespace'::sound_cache_sound_new
	// s_sound_permutation_chunk *chunk;
	// s_cache_file_tag_resource_table_runtime *resource_table;
	// s_xbox_sound_datum_ex *datum;
	// char *buffer;
	// s_tag_resource *resource;
	// unsigned long buffer_size;
	// long datum_index;
	// unsigned long const memory_size;
	// void *page_atlas;
	// long task_id;
	// s_cache_tag_instance **tag_instance;
	// s_sound_definition *sound_def;
	// void *resource_runtime_manager;
	// short resource_index;
	// long block_index;
	// unsigned long address;
	// function call : void *(*const)(unsigned long, long)
	// function call : long (*const)(s_lruv_cache *, long, long)
	// function call : unsigned long (*const)(s_lruv_cache *, long)
	// function call : long (*const)(s_data_array *, long)
	// function call : void (*const)(s_lruv_cache *, long)
	// function call : void *(*const)(s_data_array const *, unsigned long)
	// function call : void (*const)(s_lruv_cache *, long)

	s_sound_definition *sound_def = (s_sound_definition *)tag_get('snd!', definition_index);
	s_cache_tag_instance **tag_instance = &g_cache_file_tag_globals->instances[g_cache_file_tag_globals->index_to_absolute_index_map[definition_index]];
	void *resource_runtime_manager = *(void **)0x23916C8;
	void *page_atlas = offset_pointer(resource_runtime_manager, 0x14);
	s_cache_file_tag_resource_table_runtime *resource_table = *(s_cache_file_tag_resource_table_runtime **)offset_pointer(resource_runtime_manager, 0x24);
	short resource_index = sound_def->resource;
	if (resource_index < 0 || resource_index >= resource_table->count)
		return;
	s_tag_resource *resource = resource_table->resources[resource_index];
	unsigned long buffer_size = (resource->uncompressed_block_size + 0xFFF) & 0xFFFFF000;
	long block_index = ((long(__cdecl *)(s_lruv_cache *, unsigned long, long))0x966B60)(g_xbox_sound_cache, buffer_size, 0);
	if (block_index == -1)
		return;
	unsigned long address = ((unsigned long(__cdecl *)(s_lruv_cache *, long))0x966A00)(g_xbox_sound_cache, block_index);
	char *buffer = (char *)offset_pointer(g_sound_cache_memory, address);
	unsigned long const memory_size = (1 << g_xbox_sound_cache->page_size_bits) * g_xbox_sound_cache->maximum_page_count;
	#line 2070 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\Audio.cpp"
		assert(buffer + buffer_size <= (char*)g_sound_cache_memory + memory_size);
		#line 2095 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\Audio.cpp"
	long datum_index = ((long(__cdecl *)(c_data_array<s_xbox_sound_datum> *, long))0x55B550)(*g_xbox_sounds, block_index);
	if (datum_index == -1)
	{
		((void(__cdecl *)(s_lruv_cache *, long))0x9668F0)(g_xbox_sound_cache, block_index);
		return;
	}
	#line 2079 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\Audio.cpp"
		assert(block_index == datum_index);
		#line 2104 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\Audio.cpp"
	s_xbox_sound_datum_ex *datum = (s_xbox_sound_datum_ex *)datum_try_and_get(*g_xbox_sounds, block_index);
	#line 2082 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\Audio.cpp"
		assert(datum);
		#line 2108 "C:\\Users\\zekken\\Desktop\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\Audio.cpp"
	datum->sound_tag_index = definition_index;
	datum->buffer = buffer;
	datum->size = buffer_size;
	datum->chunk = chunk;
	datum->software_reference_count = 0;
	datum->hardware_reference_count = 0;
	datum->is_loading = true;
	long task_id = tag_resource_stream_async(sound_def->resource, datum->buffer, datum->size, &datum->io_completion);
	if (task_id == -1)
	{
		((void(__cdecl *)(s_lruv_cache *, long))0x9668F0)(g_xbox_sound_cache, block_index);
		block_index = -1;
	}
	chunk->runtime_index = block_index;
	chunk->next = nullptr;
	SoundCacheDebugLog(2, 0xFF00FF00, "sound_cache_sound_new() %s, chunk: %x", tag_get_name(definition_index), chunk);
}

long sound_cache_sound_request_hook(long definition_index, s_sound_permutation_chunk *chunk, long flags) // 0x10A35A90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_cache_sound_request_hook@@YAJJPAUs_sound_permutation_chunk@@J@Z");
	// `anonymous-namespace'::sound_cache_sound_request_hook
	// long flags;
	// char const *tag_name;
	// long result_flags;
	// long sound_cache_index;
		// long cache_block_index;
			// s_xbox_sound_datum_ex *datum;
		// s_xbox_sound_datum_ex *datum;
		// s_xbox_sound_datum *datum;
	// function call : void *(*const)(s_data_array const *, unsigned long)
	// function call : void *(*const)(s_data_array const *, unsigned long)
	// function call : void (*const)(s_lruv_cache *, long)

	char const *tag_name = tag_get_name(definition_index);
	if (chunk->runtime_index == -1 && definition_index != -1 && (flags & 1))
	{
		long cache_block_index = find_cache_block_for_sound(definition_index);
		if (cache_block_index == -1)
		{
			sound_cache_sound_new(definition_index, chunk);
		}
		else
		{
			chunk->runtime_index = cache_block_index;
			s_xbox_sound_datum_ex *datum = (s_xbox_sound_datum_ex *)datum_try_and_get(*g_xbox_sounds, chunk->runtime_index);
			chunk->next = datum->chunk;
			datum->chunk = chunk;
		}
	}
	long result_flags = 0;
	if (chunk->runtime_index != -1)
	{
		s_xbox_sound_datum_ex *datum = (s_xbox_sound_datum_ex *)datum_try_and_get(*g_xbox_sounds, chunk->runtime_index);
		((void (*)(s_lruv_cache *, long))0x966EE0)(g_xbox_sound_cache, chunk->runtime_index);
		if (datum->io_completion.is_done() && !datum->io_completion.get_internal_data())
			result_flags |= 2;
	}
	long sound_cache_index = chunk->runtime_index;
	if (sound_cache_index != -1 && (flags & 2))
	{
		s_xbox_sound_datum *datum = (*g_xbox_sounds)->try_and_get(sound_cache_index);
		datum->software_reference_count++;
		result_flags |= 4;
	}
	if (!(result_flags & 0xA) && chunk->runtime_index != -1)
		result_flags |= 1;
	return result_flags;
}

bool sound_cache_sound_add_reference_hook(s_sound_permutation_chunk *chunk) // 0x10A35290
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_cache_sound_add_reference_hook@@YA_NPAUs_sound_permutation_chunk@@@Z");
	// `anonymous-namespace'::sound_cache_sound_add_reference_hook
	// s_sound_permutation_chunk *chunk;
	// function call : unsigned long (*const)(long, s_sound_permutation_chunk *, unsigned long)

	return (((unsigned __int32)((unsigned __int32(__cdecl *)(long, s_sound_permutation_chunk *, long))0x65fcb0)(-1, chunk, 2)) >> 2) & 1;
}

void sound_cache_sound_finished_hook(s_sound_permutation_chunk *chunk) // 0x10A353A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_cache_sound_finished_hook@@YAXPAUs_sound_permutation_chunk@@@Z");
	// `anonymous-namespace'::sound_cache_sound_finished_hook
	// s_sound_permutation_chunk *chunk;
	// s_xbox_sound_datum_ex *cache_sound;
	// function call : void (*const)(s_lruv_cache *, long)

	s_xbox_sound_datum_ex *cache_sound = (s_xbox_sound_datum_ex *)(*g_xbox_sounds)->try_and_get(chunk->runtime_index);

	if (cache_sound->software_reference_count)
	{
		cache_sound->software_reference_count--;
	}

	if (!cache_sound->software_reference_count && !cache_sound->hardware_reference_count && !cache_sound->io_completion.is_done() && !cache_sound->is_loading)
	{
		((void(*)(s_lruv_cache *, long))0x9668F0)(g_xbox_sound_cache, chunk->runtime_index);
	}
}

void sound_cache_flush_all_sound_guaranteed_hook() // 0x10A34E00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_cache_flush_all_sound_guaranteed_hook@@YAXXZ");
	// `anonymous-namespace'::sound_cache_flush_all_sound_guaranteed_hook
	// procedure flags: nofpo
	// static ...; // 0x10A34F98
	// static ...; // 0x10A34F8C
	// static ...; // 0x10A34F84
	// unsigned long start_time;
	// s_data_iterator iterator;
	// void (*const async_idle)();
	// void (*const tag_resources_pump_io)();
		// s_xbox_sound_datum_ex *datum;
	// function call : void (*const)(s_data_iterator *, s_data_array const *)
	// function call : s_datum *(*const)(s_data_iterator *)
	// function call : s_datum *(*const)(s_data_iterator *)
	// function call : void (*const)()
	// function call : void (*const)(s_lruv_cache *)
	// function call : void (*const)()
	// function call : void (*const)(s_lruv_cache *, long)

	void (*const async_idle)() = reinterpret_cast<void (*)()>(0x5084E0);
	void (*const tag_resources_pump_io)() = reinterpret_cast<void (*)()>(0x564010);
	unsigned long start_time = system_milliseconds();
	s_data_iterator iterator;
	data_iterator_new(&iterator, *g_xbox_sounds);
	for (s_xbox_sound_datum_ex *datum = (s_xbox_sound_datum_ex *)data_iterator_next(&iterator); datum; datum = (s_xbox_sound_datum_ex *)data_iterator_next(&iterator))
	{
		do
		{
			if (!datum->software_reference_count && !datum->hardware_reference_count && !datum->io_pending())
				break;
			async_idle();
			((void (*)(s_lruv_cache *))0x9677B0)(g_xbox_sound_cache);
			tag_resources_pump_io();
		}
		while (system_milliseconds() - start_time < 5000);
		if (datum->chunk->runtime_index != -1 && datum->chunk->runtime_index != 0)
			((void (*)(s_lruv_cache *, long))0x9668F0)(g_xbox_sound_cache, datum->chunk->runtime_index);
	}
}

unsigned __int32 sound_try_to_get_global_propagation_hook(char a1) // 0x10A35FC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_try_to_get_global_propagation_hook@@YAID@Z");
	// `anonymous-namespace'::sound_try_to_get_global_propagation_hook
	// char a1;
	// unsigned __int32 (*const sound_try_to_get_global_propagation)(char);
	// function call : bool (*const)()
	// function call : unsigned __int32 (*const)(char)

	const auto sound_try_to_get_global_propagation = (unsigned __int32(*)(char))0x51A270;

	if (((bool(*)())0x531E90)())
	{
		return 0;
	}

	return sound_try_to_get_global_propagation(a1);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template HALO_CHANNEL * HALO_LIST<HALO_CHANNEL>::operator[](__int32);
template bool c_data_iterator<s_xbox_sound_datum>::operator!=(c_data_iterator<s_xbox_sound_datum> const &) const;
template bool c_data_iterator<s_xbox_sound_datum>::operator==(c_data_iterator<s_xbox_sound_datum> const &) const;
template bool c_enum<enum e_sound_class,unsigned char>::operator==(e_sound_class const &) const;
template bool c_enum<enum e_sound_compression,unsigned char>::operator==(e_sound_compression const &) const;
template bool c_enum<enum e_sound_load_mode,unsigned char>::operator==(e_sound_load_mode const &) const;
template bool c_tag_block<s_sound_permutation_chunk>::try_get_element(__int32, s_sound_permutation_chunk **) const;
template c_data_iterator<s_xbox_sound_datum> & c_data_iterator<s_xbox_sound_datum>::operator++();
template c_data_iterator<s_xbox_sound_datum> c_data_array<s_xbox_sound_datum>::begin();
template c_data_iterator<s_xbox_sound_datum> c_data_array<s_xbox_sound_datum>::end();
template c_data_iterator<s_xbox_sound_datum>::c_data_iterator(s_data_array *);
template c_enum<enum e_sound_compression,unsigned char>::operator unsigned char() const;
template c_enum<enum e_sound_encoding,unsigned char>::operator unsigned char() const;
template c_enum<enum e_sound_sample_rate,unsigned char>::operator unsigned char() const;
template s_sound_permutation_chunk & c_tag_block<s_sound_permutation_chunk>::operator[](__int32);
template s_sound_permutation_chunk * c_tag_block<s_sound_permutation_chunk>::get_element(__int32) const;
template s_xbox_sound_datum & c_data_iterator<s_xbox_sound_datum>::next();
template s_xbox_sound_datum * c_data_array<s_xbox_sound_datum>::try_and_get(unsigned long);
template s_xbox_sound_datum * c_data_iterator<s_xbox_sound_datum>::operator->();
template void Pointer::Write<long const *>(long const *const) const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { void *g_channel_transmission_sources1[224]; }
namespace hades_file_local { void *g_channel_transmission_sources2[224]; }
namespace hades_file_local { s_lruv_cache *g_xbox_sound_cache; }
namespace hades_file_local { void *g_sound_cache_memory; }
namespace hades_file_local { long const g_sample_rates[4] = { 22050, 44100, 32000, 48000 }; }
long const k_number_of_xbox_sound_datums = 512;
