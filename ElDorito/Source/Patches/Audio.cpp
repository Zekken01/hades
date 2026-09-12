/* ---------- headers */

#include "Patches/Audio.hpp"
#include "hades/hades.h"

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
		public:
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

extern long const k_number_of_xbox_sound_datums; // 0x111ABBB4
bool (*HALO_PERM_SOUND::Init)(HALO_PERM_SOUND *, s_sound_tag_data *, HALO_CHANNEL_PROPERTIES *, HALO_CHANNEL *); // 0x113541FC
HALO_PERM_SOUND *(*HALO_PERM_SOUND::Free)(HALO_PERM_SOUND *); // 0x11354200
HALO_PERM_SOUND *(*HALO_PERM_SOUND::Reset)(HALO_PERM_SOUND *); // 0x11354204
__int32 (*HALO_PERM_SOUND::UpdateChannelProperties)(HALO_PERM_SOUND *, HALO_CHANNEL_PROPERTIES *); // 0x11354208
__int32 (*HALO_PERM_SOUND::InitChannelProperties)(HALO_PERM_SOUND *, HALO_CHANNEL_PROPERTIES *); // 0x1135420C
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
		_extern void _sub_10A2DCC0();
		void ApplyAll() // 0x10A2DCC0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Audio@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A2DCC0();
		}

		_extern void _sub_10A2C1E0();
		void ApplyAfterInit() // 0x10A2C1E0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAfterInit@Audio@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A2C1E0();
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

		_extern __int32 _sub_10A2F910();
		__int32 GetDeviceCount() // 0x10A2F910
		{
			mangled_x86(MANGLED_TODO, "?GetDeviceCount@Audio@Patches@@YAHXZ");
			// procedure flags: nofpo
			// static ...; // 0x10A2F994
			// static ...; // 0x10A2F988
			// static ...; // 0x10A2F980
			// HALO_SOUND_SYSTEM *soundSystem;
			// __int32 numDrivers;
			todo("implement");
			__int32 __result = _sub_10A2F910();
			return __result;
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

extern c_large_integer _sub_10A2C0A0(c_large_integer const &, c_large_integer const &);
_inline c_large_integer operator+(c_large_integer const &lhs, c_large_integer const &rhs) // 0x10A2C0A0
{
	// `anonymous-namespace'::operator+
	// c_large_integer const &rhs;
	// unsigned __int32 hi;
	// unsigned __int32 lo;
	// unsigned long long sum;
	// unsigned __int32 carry;
	todo("implement");
	c_large_integer __result = _sub_10A2C0A0(lhs, rhs);
	return __result;
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

_extern void _sub_10A345D0(c_sound_debug_printer *const, long, char const *, ...);
_inline void __cdecl c_sound_debug_printer::print_line(long color, char const *format, ...) // 0x10A345D0
{
	// `anonymous-namespace'::c_sound_debug_printer::print_line
	// c_sound_debug_printer *const this;
	// long color;
	// char const *format;
	// char buff[4096];
	// char *va;
	todo("implement");
	_sub_10A345D0(this, color, format);
}

_inline void c_sound_debug_printer::skip_line() // 0x10A34B00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?skip_line@c_sound_debug_printer@hades_file_local@@QAEXXZ");
	// `anonymous-namespace'::c_sound_debug_printer::skip_line
	// c_sound_debug_printer *const this;

	m_yOffset += 16.0f;
}

_extern bool _sub_10A32370();
bool SoundSystemTraceEnabled() // 0x10A32370
{
	// `anonymous-namespace'::SoundSystemTraceEnabled
	// procedure flags: nofpo
	todo("implement");
	bool __result = _sub_10A32370();
	return __result;
}

_extern bool _sub_10A322B0(s_sound_tag_data const *);
bool SoundQueueFilter(s_sound_tag_data const *request) // 0x10A322B0
{
	// `anonymous-namespace'::SoundQueueFilter
	// s_sound_tag_data const *request;
	// std::string &filterStr;
	todo("implement");
	bool __result = _sub_10A322B0(request);
	return __result;
}

extern FMOD_RESULT _sub_10A2F050(FMOD_RESULT, char const *);
FMOD_RESULT FMOD_CheckError(FMOD_RESULT err, char const *func_name) // 0x10A2F050
{
	// `anonymous-namespace'::FMOD_CheckError
	// char const *func_name;
	{
		// char const *err_string;
	}
	todo("implement");
	FMOD_RESULT __result = _sub_10A2F050(err, func_name);
	return __result;
}

_extern void _sub_10A33C20();
void debug_display_sound_system() // 0x10A33C20
{
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
	{
		// long color;
		// long current_sound_count;
		// long max_sound_count;
		{
			// s_sound_source_datum *sound_source;
			{
				// long tag_index;
				// char const *name;
			}
		}
	}
	{
		{
			// looping_sound_datum *looping_sound;
			{
			}
		}
	}
	// function call : void (*const)(s_data_iterator *, s_data_array const *)
	// function call : s_datum *(*const)(s_data_iterator *)
	// function call : void (*const)(s_data_iterator *, s_data_array const *)
	// function call : s_datum *(*const)(s_data_iterator *)
	todo("implement");
	_sub_10A33C20();
}

_extern void _sub_10A33350();
void debug_display_fmod_stats() // 0x10A33350
{
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
	{
		// __int32 i;
	}
	todo("implement");
	_sub_10A33350();
}

_extern bool _sub_10A31E20(SYSTEM_FMOD *);
bool SYSTEM_FMOD_InitEventSystem(SYSTEM_FMOD *thisptr) // 0x10A31E20
{
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
	todo("implement");
	bool __result = _sub_10A31E20(thisptr);
	return __result;
}

_extern bool _sub_10A32060(char *, void *, __int32, __int32);
bool __fastcall SYSTEM_FMOD_Init_Hook(char *thisptr, void *unused, __int32 a2, __int32 a3) // 0x10A32060
{
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
	todo("implement");
	bool __result = _sub_10A32060(thisptr, unused, a2, a3);
	return __result;
}

_extern long long _sub_10A31C20(FMOD_CHANNEL *, unsigned __int32);
long long MapSamples(FMOD_CHANNEL *channel, unsigned __int32 samples) // 0x10A31C20
{
	// `anonymous-namespace'::MapSamples
	// static ...; // 0x10A31CE8
	// static ...; // 0x10A31CE0
	// FMOD_CHANNEL *channel;
	// unsigned __int32 samples;
	// float sample_rate;
	todo("implement");
	long long __result = _sub_10A31C20(channel, samples);
	return __result;
}

_extern long _sub_10A2FA70(HALO_CHANNEL const *);
long GetQueuedSoundCount(HALO_CHANNEL const *channel) // 0x10A2FA70
{
	// `anonymous-namespace'::GetQueuedSoundCount
	// HALO_CHANNEL const *channel;
	// long count;
	{
		// long i;
	}
	todo("implement");
	long __result = _sub_10A2FA70(channel);
	return __result;
}

_extern void _sub_10A2ED10(HALO_CHANNEL *, __int32, bool);
void DelayPermutation(HALO_CHANNEL *channel, __int32 index, bool sync_time) // 0x10A2ED10
{
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
	{
		// unsigned __int32 length_pcm;
		// HALO_PERM_SOUND &previous_queued_sound;
		{
			// unsigned __int32 position;
		}
	}
	todo("implement");
	_sub_10A2ED10(channel, index, sync_time);
}

_extern void _sub_10A2FAE0(HALO_CHANNEL *, __int32);
void HALO_CHANNEL_PlaySound(HALO_CHANNEL *channel, __int32 i) // 0x10A2FAE0
{
	// `anonymous-namespace'::HALO_CHANNEL_PlaySound
	// static ...; // 0x10A2FBF8
	// static ...; // 0x10A2FBF0
	// HALO_CHANNEL *channel;
	// __int32 i;
	// __int32 num_channels;
	// HALO_SOUND_SYSTEM *sound_system;
	// function call : __int32 (*)(HALO_PERM_SOUND *, HALO_CHANNEL_PROPERTIES *)
	// function call : __int32 (*)(HALO_PERM_SOUND *, HALO_CHANNEL_PROPERTIES *)
	todo("implement");
	_sub_10A2FAE0(channel, i);
}

_extern void _sub_10A2FF60(HALO_CHANNEL *);
void __fastcall HALO_CHANNEL_Update(HALO_CHANNEL *channel) // 0x10A2FF60
{
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
	{
		// __int32 i;
		{
			// FMOD_SOUND *playing_sound;
			{
				// float channel_freq;
				// float sound_freq;
			}
		}
	}
	{
		// char *permutation_name;
		// char const *tag_name;
	}
	// function call : __int32 (*)(HALO_PERM_SOUND *, HALO_CHANNEL_PROPERTIES *)
	// function call : HALO_PERM_SOUND *(*)(HALO_PERM_SOUND *)
	// function call : HALO_PERM_SOUND *(*)(HALO_PERM_SOUND *)
	todo("implement");
	_sub_10A2FF60(channel);
}

_extern short _sub_10A31640(long);
short HALO_SOUND_SYSTEM_GetChannelState(long source_index) // 0x10A31640
{
	// `anonymous-namespace'::HALO_SOUND_SYSTEM_GetChannelState
	// long source_index;
	// HALO_SOUND_SYSTEM *sound_system;
	// HALO_CHANNEL *channels;
	{
		// __int32 i;
	}
	todo("implement");
	short __result = _sub_10A31640(source_index);
	return __result;
}

_extern void _sub_10A31BA0(HALO_SOUND_SYSTEM *);
void __fastcall HALO_SOUND_SYSTEM_Update_Hook(HALO_SOUND_SYSTEM *sound_system) // 0x10A31BA0
{
	// `anonymous-namespace'::HALO_SOUND_SYSTEM_Update_Hook
	// HALO_SOUND_SYSTEM *sound_system;
	// void (*const HALO_SOUND_SYSTEM_Update)(HALO_SOUND_SYSTEM *);
	// function call : void (*const)(HALO_SOUND_SYSTEM *)
	todo("implement");
	_sub_10A31BA0(sound_system);
}

_extern bool _sub_10A35F20(long);
bool sound_plays_when_paused(long definition_index) // 0x10A35F20
{
	// `anonymous-namespace'::sound_plays_when_paused
	// long definition_index;
	// s_sound_definition *sound;
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	bool __result = _sub_10A35F20(definition_index);
	return __result;
}

_extern void _sub_10A31720(HALO_SOUND_SYSTEM *, void *, bool);
void __fastcall HALO_SOUND_SYSTEM_Pause(HALO_SOUND_SYSTEM *thisptr, void *unused, bool paused) // 0x10A31720
{
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
	{
		// c_large_integer clock;
		{
			// __int32 i;
			{
				// HALO_CHANNEL *channel;
				{
					// __int32 j;
				}
			}
		}
	}
	{
		// c_large_integer delta_time;
		// c_large_integer pause_time;
		{
			{
				{
					{
						// c_large_integer start_time;
					}
				}
			}
		}
	}
	todo("implement");
	_sub_10A31720(thisptr, unused, paused);
}

_extern void _sub_10A2FC60(HALO_CHANNEL *, void *, s_sound_tag_data *);
void __fastcall HALO_CHANNEL_Queue(HALO_CHANNEL *channel, void *unused, s_sound_tag_data *request) // 0x10A2FC60
{
	// `anonymous-namespace'::HALO_CHANNEL_Queue
	// static ...; // 0x10A2FEA0
	// HALO_CHANNEL *channel;
	// void *unused;
	// s_sound_tag_data *request;
	// __int32 queued_count;
	{
		// char *permutation_name;
		// char const *tag_name;
	}
	{
		// unsigned __int32 length_pcm;
	}
	// function call : bool (*)(HALO_PERM_SOUND *, s_sound_tag_data *, HALO_CHANNEL_PROPERTIES *, HALO_CHANNEL *)
	todo("implement");
	_sub_10A2FC60(channel, unused, request);
}

_extern void _sub_10A30430(HALO_PERM_SOUND *, void *, HALO_CHANNEL_PROPERTIES *);
void __fastcall HALO_PERM_SOUND_InitChannelProperties(HALO_PERM_SOUND *thisptr, void *unused, HALO_CHANNEL_PROPERTIES *channel_properties) // 0x10A30430
{
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
	{
		// float max_distance;
	}
	todo("implement");
	_sub_10A30430(thisptr, unused, channel_properties);
}

_extern void _sub_10A311D0(HALO_PERM_SOUND *, void *, HALO_CHANNEL_PROPERTIES *);
void __fastcall HALO_PERM_SOUND_UpdateChannelProperties(HALO_PERM_SOUND *thisptr, void *unused, HALO_CHANNEL_PROPERTIES *channel_properties) // 0x10A311D0
{
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
	{
		// float envelope[4];
	}
	{
		// __int32 room;
		// FMOD_REVERB_CHANNELPROPERTIES reverb_properties;
	}
	// function call : float (*const)(float *, float)
	todo("implement");
	_sub_10A311D0(thisptr, unused, channel_properties);
}

extern FMOD_RESULT _sub_10A2E5A0(s_sound_tag_data *, FMOD_SOUND **, void **);
FMOD_RESULT CreateSoundHook(s_sound_tag_data *request, FMOD_SOUND **sound, void **out_data) // 0x10A2E5A0
{
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
	{
		// char *permutation_name;
		// char const *tag_name;
	}
	{
	}
	todo("implement");
	FMOD_RESULT __result = _sub_10A2E5A0(request, sound, out_data);
	return __result;
}

extern FMOD_RESULT _sub_10A2F770(FMOD_SOUND *, FMOD_SYSTEM **);
FMOD_RESULT FMOD_Sound_ReleaseSub_Hook(FMOD_SOUND *sound, FMOD_SYSTEM **out_system) // 0x10A2F770
{
	// `anonymous-namespace'::FMOD_Sound_ReleaseSub_Hook
	// static ...; // 0x10A2F800
	// static ...; // 0x10A2F7F8
	// FMOD_SOUND *sound;
	// FMOD_SYSTEM **out_system;
	// s_sound_permutation_chunk *chunk;
	// FMOD_RESULT (*const _FMOD_Sound_GetSystemObject)(FMOD_SOUND *, FMOD_SYSTEM **);
	// function call : FMOD_RESULT (*const)(FMOD_SOUND *, FMOD_SYSTEM **)
	todo("implement");
	FMOD_RESULT __result = _sub_10A2F770(sound, out_system);
	return __result;
}

__int32 sound_permutation_get_unique_id(s_sound_permutation *permutation) // 0x10A35F00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_permutation_get_unique_id@@YAHPAUs_sound_permutation@@@Z");
	// `anonymous-namespace'::sound_permutation_get_unique_id
	// s_sound_permutation *permutation;

	return (__int32)permutation;
}

_extern void _sub_10A34370(long, bool, __int32, float, long);
void loop_track_fade_hook(long definition_index, bool is_alternate, __int32 reason, float seconds, long sound_index) // 0x10A34370
{
	// `anonymous-namespace'::loop_track_fade_hook
	// long sound_index;
	// void (*const loop_track_fade)(long, bool, __int32, float, long);
	{
		// s_user_interface_shared_globals *wigl;
		// unsigned long lobby_countdown_seconds;
	}
	// function call : bool (*const)()
	// function call : s_user_interface_shared_globals *(*const)()
	// function call : void (*const)(long, bool, __int32, float, long)
	todo("implement");
	_sub_10A34370(definition_index, is_alternate, reason, seconds, sound_index);
}

_extern void _sub_10A331A0(short);
void channel_signal_complete(short channel_index) // 0x10A331A0
{
	// `anonymous-namespace'::channel_signal_complete
	// short channel_index;
	// sound_channel_datum *channel;
	{
		// char *permutation_name;
		// char const *tag_name;
		// HALO_CHANNEL *haloChannel;
	}
	todo("implement");
	_sub_10A331A0(channel_index);
}

_extern void _sub_10A34780(short);
void refresh_channel(short channel_index) // 0x10A34780
{
	// `anonymous-namespace'::refresh_channel
	// short channel_index;
	// sound_channel_datum *channel;
	// bool (*const sound_permutation_release)(s_sound_permutation_chunk *);
	// bool (*const sound_permutation_available_to_start)(s_sound_permutation_chunk *);
	// short state;
	{
		// s_sound_permutation_chunk *next_chunk;
		// s_sound_permutation_chunk *chunk;
	}
	{
		// s_sound_permutation_chunk *playing_chunk;
	}
	// function call : short (*const)(long)
	// function call : s_sound_permutation_chunk *(*const)(s_sound_permutation *, short)
	// function call : bool (*const)(s_sound_permutation_chunk *)
	// function call : short (*const)(s_sound_permutation *, short)
	// function call : s_sound_permutation_chunk *(*const)(s_sound_permutation *, short)
	// function call : bool (*const)(s_sound_permutation_chunk *)
	// function call : s_sound_permutation_chunk *(*const)(s_sound_permutation *, short)
	// function call : bool (*const)(s_sound_permutation_chunk *)
	todo("implement");
	_sub_10A34780(channel_index);
}

_extern void _sub_10A34A80();
void refresh_channels() // 0x10A34A80
{
	// `anonymous-namespace'::refresh_channels
	// procedure flags: nofpo
	{
		// __int32 i;
	}
	todo("implement");
	_sub_10A34A80();
}

_extern void _sub_10A330C0(void *, void *, void *);
void build_channel_transmission_sources_hook(void *listener, void *voices, void *sources) // 0x10A330C0
{
	// `anonymous-namespace'::build_channel_transmission_sources_hook
	// void *sources;
	// void (*const build_channel_transmission_sources)(void *, void *, void *);
	// function call : void (*const)(void *, void *, void *)
	todo("implement");
	_sub_10A330C0(listener, voices, sources);
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

_extern short _sub_10A35CD0(s_sound_definition *, float, short);
short sound_commit_looping_find_pitch_range_by_pitch_hook(s_sound_definition *sndDef, float pitchModifier, short fallbackIndex) // 0x10A35CD0
{
	// `anonymous-namespace'::sound_commit_looping_find_pitch_range_by_pitch_hook
	// static ...; // 0x10A35E70
	// s_sound_definition *sndDef;
	// float pitchModifier;
	// short fallbackIndex;
	// short ret;
	// short (*const sound_definition_find_pitch_range_by_pitch)(void *, float, short);
	{
		// long sound_tag_index;
		// char message[4096];
		{
			// __int32 i;
			{
				// s_cache_tag_instance *tag;
			}
		}
	}
	// function call : short (*const)(void *, float, short)
	// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)
	// function call : void ()
	todo("implement");
	short __result = _sub_10A35CD0(sndDef, pitchModifier, fallbackIndex);
	return __result;
}

_extern bool _sub_10A34B40(long);
bool sound_attachment_is_sky_hook(long object_index) // 0x10A34B40
{
	// `anonymous-namespace'::sound_attachment_is_sky_hook
	// long object_index;
	// s_object_header *object_header;
	// function call : long (*const)(long)
	todo("implement");
	bool __result = _sub_10A34B40(object_index);
	return __result;
}

_extern void _sub_10A36130(long, float);
void unit_set_mouth_aperture_hook(long unit_index, float t) // 0x10A36130
{
	// `anonymous-namespace'::unit_set_mouth_aperture_hook
	// float t;
	// float const k_max_step;
	// s_unit_data *unit;
	todo("implement");
	_sub_10A36130(unit_index, t);
}

_extern void _sub_10A31D40(::Audio::SAudioDeviceEvent const &);
void OnAudioDeviceEvent(::Audio::SAudioDeviceEvent const &e) // 0x10A31D40
{
	// `anonymous-namespace'::OnAudioDeviceEvent
	// static ...; // 0x10A31DEC
	// static ...; // 0x10A31DE0
	// static ...; // 0x10A31DD8
	// Audio::SAudioDeviceEvent const &e;
	// FMOD_SYSTEM *fmod_system;
	// HALO_SOUND_SYSTEM *sound_system;
	// FMOD_OUTPUTTYPE output;
	todo("implement");
	_sub_10A31D40(e);
}

_extern void _sub_10A352F0(s_sound_permutation_chunk *);
void sound_cache_sound_delete_hook(s_sound_permutation_chunk *chunk) // 0x10A352F0
{
	// `anonymous-namespace'::sound_cache_sound_delete_hook
	// s_sound_permutation_chunk *chunk;
	// function call : void (*const)(s_data_array *, long)
	// function call : void (*const)(s_lruv_cache *, long)
	todo("implement");
	_sub_10A352F0(chunk);
}

_extern void *_sub_10A35490(s_sound_permutation_chunk *, unsigned long *);
void *sound_cache_sound_hardware_lock(s_sound_permutation_chunk *chunk, unsigned long *out_size) // 0x10A35490
{
	// `anonymous-namespace'::sound_cache_sound_hardware_lock
	// unsigned long *out_size;
	// s_xbox_sound_datum_ex *cache_sound;
	todo("implement");
	void * __result = _sub_10A35490(chunk, out_size);
	return __result;
}

_extern void _sub_10A35580(s_sound_permutation_chunk *);
void sound_cache_sound_hardware_unlock(s_sound_permutation_chunk *chunk) // 0x10A35580
{
	// `anonymous-namespace'::sound_cache_sound_hardware_unlock
	// s_sound_permutation_chunk *chunk;
	// s_xbox_sound_datum_ex *cache_sound;
	todo("implement");
	_sub_10A35580(chunk);
}

_extern void _sub_10A34C30(void *, long, bool);
void sound_cache_delete_block_proc(void *context, long block_index, bool moved) // 0x10A34C30
{
	// `anonymous-namespace'::sound_cache_delete_block_proc
	// bool moved;
	// s_xbox_sound_datum_ex *cache_sound;
	// s_sound_permutation_chunk *chunk;
	{
		// s_sound_permutation_chunk *next;
	}
	// function call : void (*const)(s_data_array *, long)
	todo("implement");
	_sub_10A34C30(context, block_index, moved);
}

_extern bool _sub_10A35070(void *, long);
bool sound_cache_locked_block_proc(void *context, long block_index) // 0x10A35070
{
	// `anonymous-namespace'::sound_cache_locked_block_proc
	// long block_index;
	// s_xbox_sound_datum_ex *cache_sound;
	todo("implement");
	bool __result = _sub_10A35070(context, block_index);
	return __result;
}

void sound_cache_idle_hook() // 0x10A35010
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sound_cache_idle_hook@@YAXXZ");
	// `anonymous-namespace'::sound_cache_idle_hook
	// procedure flags: nofpo
	// function call : void (*const)(s_lruv_cache *)

	((void(__cdecl *const)(s_lruv_cache *))0x9677b0)(g_xbox_sound_cache);
}

_extern void _sub_10A35120();
void sound_cache_new_hook() // 0x10A35120
{
	// `anonymous-namespace'::sound_cache_new_hook
	// procedure flags: nofpo
	// unsigned long const memory_size;
	// function call : void *(*const)(char const *, long, unsigned long, long, void *)
	// function call : s_lruv_cache *(*const)(char const *, long, long, long, void *, void (*)(void *, long, bool), bool (*)(void *, long), unsigned char (*)(void *, long), c_allocation_interface *, long)
	// function call : void (*const)(s_lruv_cache *, e_hole_algorithm)
	todo("implement");
	_sub_10A35120();
}

_extern long _sub_10A34130(long);
long find_cache_block_for_sound(long definition_index) // 0x10A34130
{
	// `anonymous-namespace'::find_cache_block_for_sound
	// static ...; // 0x10A341F4
	// static ...; // 0x10A341E8
	// static ...; // 0x10A341E0
	// long definition_index;
	{
		// c_data_iterator<s_xbox_sound_datum> it;
	}
	todo("implement");
	long __result = _sub_10A34130(definition_index);
	return __result;
}

_extern void _sub_10A35650(long, s_sound_permutation_chunk *);
void sound_cache_sound_new(long definition_index, s_sound_permutation_chunk *chunk) // 0x10A35650
{
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
	todo("implement");
	_sub_10A35650(definition_index, chunk);
}

_extern long _sub_10A35A90(long, s_sound_permutation_chunk *, long);
long sound_cache_sound_request_hook(long definition_index, s_sound_permutation_chunk *chunk, long flags) // 0x10A35A90
{
	// `anonymous-namespace'::sound_cache_sound_request_hook
	// long flags;
	// char const *tag_name;
	// long result_flags;
	// long sound_cache_index;
	{
		// long cache_block_index;
		{
			// s_xbox_sound_datum_ex *datum;
		}
	}
	{
		// s_xbox_sound_datum_ex *datum;
	}
	{
		// s_xbox_sound_datum *datum;
	}
	// function call : void *(*const)(s_data_array const *, unsigned long)
	// function call : void *(*const)(s_data_array const *, unsigned long)
	// function call : void (*const)(s_lruv_cache *, long)
	todo("implement");
	long __result = _sub_10A35A90(definition_index, chunk, flags);
	return __result;
}

_extern bool _sub_10A35290(s_sound_permutation_chunk *);
bool sound_cache_sound_add_reference_hook(s_sound_permutation_chunk *chunk) // 0x10A35290
{
	// `anonymous-namespace'::sound_cache_sound_add_reference_hook
	// s_sound_permutation_chunk *chunk;
	// function call : unsigned long (*const)(long, s_sound_permutation_chunk *, unsigned long)
	todo("implement");
	bool __result = _sub_10A35290(chunk);
	return __result;
}

_extern void _sub_10A353A0(s_sound_permutation_chunk *);
void sound_cache_sound_finished_hook(s_sound_permutation_chunk *chunk) // 0x10A353A0
{
	// `anonymous-namespace'::sound_cache_sound_finished_hook
	// s_sound_permutation_chunk *chunk;
	// s_xbox_sound_datum_ex *cache_sound;
	// function call : void (*const)(s_lruv_cache *, long)
	todo("implement");
	_sub_10A353A0(chunk);
}

_extern void _sub_10A34E00();
void sound_cache_flush_all_sound_guaranteed_hook() // 0x10A34E00
{
	// `anonymous-namespace'::sound_cache_flush_all_sound_guaranteed_hook
	// procedure flags: nofpo
	// static ...; // 0x10A34F98
	// static ...; // 0x10A34F8C
	// static ...; // 0x10A34F84
	// unsigned long start_time;
	// s_data_iterator iterator;
	// void (*const async_idle)();
	// void (*const tag_resources_pump_io)();
	{
		// s_xbox_sound_datum_ex *datum;
	}
	// function call : void (*const)(s_data_iterator *, s_data_array const *)
	// function call : s_datum *(*const)(s_data_iterator *)
	// function call : s_datum *(*const)(s_data_iterator *)
	// function call : void (*const)()
	// function call : void (*const)(s_lruv_cache *)
	// function call : void (*const)()
	// function call : void (*const)(s_lruv_cache *, long)
	todo("implement");
	_sub_10A34E00();
}

_extern unsigned __int32 _sub_10A35FC0(char);
unsigned __int32 sound_try_to_get_global_propagation_hook(char a1) // 0x10A35FC0
{
	// `anonymous-namespace'::sound_try_to_get_global_propagation_hook
	// char a1;
	// unsigned __int32 (*const sound_try_to_get_global_propagation)(char);
	// function call : bool (*const)()
	// function call : unsigned __int32 (*const)(char)
	todo("implement");
	unsigned __int32 __result = _sub_10A35FC0(a1);
	return __result;
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
