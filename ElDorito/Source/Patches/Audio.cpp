/* ---------- headers */

#include "Patches/Audio.hpp"
#include "hades/hades.h"

#include "Audio/AudioDeviceManager.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/fmod/fmod_functions.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/math/sound_math.hpp"
#include "Blam/memory/allocation_interface.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/data_iterator.inl"
#include "Blam/memory/lruv_cache.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/sounds/halo_sound_system.hpp"
#include "Blam/sounds/sound_memory.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Debug/DebugDraw.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"
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
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct HALO_CHANNEL;
struct HALO_CHANNEL_PROPERTIES;
struct HALO_PERM_SOUND;
struct HALO_SOUND_SYSTEM;
struct c_allocation_interface;
struct s_lruv_cache;
struct s_sound_tag_data;
namespace Patches
{
	namespace Audio
	{
		struct SAudioDeviceInfo;
	}
}
namespace
{
	struct c_large_integer;
	class c_sound_debug_printer;
	struct c_dumb_allocator;
}

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

namespace
{
	struct c_large_integer
	{
		unsigned __int32 hi; // 0x0
		unsigned __int32 lo; // 0x4
		unsigned long long value() const;
		c_large_integer &operator+=(c_large_integer const &);
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

/* ---------- globals */

extern long const k_number_of_xbox_sound_datums; // 0x111ABBB4
bool (*HALO_PERM_SOUND::Init)(HALO_PERM_SOUND *, s_sound_tag_data *, HALO_CHANNEL_PROPERTIES *, HALO_CHANNEL *); // 0x113541FC
HALO_PERM_SOUND *(*HALO_PERM_SOUND::Free)(HALO_PERM_SOUND *); // 0x11354200
HALO_PERM_SOUND *(*HALO_PERM_SOUND::Reset)(HALO_PERM_SOUND *); // 0x11354204
__int32 (*HALO_PERM_SOUND::UpdateChannelProperties)(HALO_PERM_SOUND *, HALO_CHANNEL_PROPERTIES *); // 0x11354208
__int32 (*HALO_PERM_SOUND::InitChannelProperties)(HALO_PERM_SOUND *, HALO_CHANNEL_PROPERTIES *); // 0x1135420C
char const *HALO_CHANNEL::STATE_NAMES[4]; // 0x11354210

/* ---------- private variables */

namespace
{
	extern void *g_channel_transmission_sources1[224]; // 0x124578D8
	extern void *g_channel_transmission_sources2[224]; // 0x12457C58
	extern s_lruv_cache *g_xbox_sound_cache; // 0x12457FD8
	extern void *g_sound_cache_memory; // 0x12457FDC
	extern long const g_sample_rates[4]; // 0x111ABBB8
}
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

		_extern bool _sub_10A32220(__int32);
		bool SetOutputDevice(__int32 deviceIndex) // 0x10A32220
		{
			mangled_x86(MANGLED_TODO, "?SetOutputDevice@Audio@Patches@@YA_NH@Z");
			// __int32 deviceIndex;
			// HALO_SOUND_SYSTEM *soundSystem;
			todo("implement");
			bool __result = _sub_10A32220(deviceIndex);
			return __result;
		}

		_extern bool _sub_10A2F9D0(__int32, Patches::Audio::SAudioDeviceInfo *);
		bool GetDeviceInfo(__int32 deviceIndex, Patches::Audio::SAudioDeviceInfo *outInfo) // 0x10A2F9D0
		{
			mangled_x86(MANGLED_TODO, "?GetDeviceInfo@Audio@Patches@@YA_NHPAUSAudioDeviceInfo@12@@Z");
			// Patches::Audio::SAudioDeviceInfo *outInfo;
			// HALO_SOUND_SYSTEM *soundSystem;
			todo("implement");
			bool __result = _sub_10A2F9D0(deviceIndex, outInfo);
			return __result;
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

		_extern void _sub_10A324F0();
		void Tick() // 0x10A324F0
		{
			mangled_x86(MANGLED_TODO, "?Tick@Audio@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A324F0();
		}
	}
}

/* ---------- private code */
