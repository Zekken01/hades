/* ---------- headers */

#include "Patches/Core.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_engine_candy_monitor.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Console/Console.hpp"
#include "ElDorito.hpp"
#include "Job/JobDefinitions.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <codecvt>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <optional>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct begin;
struct end;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Mopp {}
	using namespace Patches::Mopp;
	namespace Core {}
	using namespace Patches::Core;
}

namespace Console {}
using namespace ::Console;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	namespace Core
	{
		extern void ApplyAll();
		extern void ApplyAfterInit();
		extern void OnShutdown(std::function<void __cdecl(void)> callback);
		extern void ExecuteShutdownCallbacks();
		extern void OnMapLoaded(std::function<void __cdecl(char const *)> callback);
		extern void OnGameStart(std::function<void __cdecl(void)> callback);
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > MapsFolder; // 0x124582F4
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > MapFormatString; // 0x1245832C
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > StringIdsPath; // 0x124582D8
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > TagsPath; // 0x124582A0
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > TagListPath; // 0x124582BC
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > ResourcesPath; // 0x124583C8
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > ResourcesBPath; // 0x12458348
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > TexturesPath; // 0x124583AC
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > TexturesBPath; // 0x124583F4
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > AudioPath; // 0x12458390
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > FontsPath; // 0x12458364
	extern std::vector<std::function<void __cdecl(char const *)>,std::allocator<std::function<void __cdecl(char const *)> > > mapLoadedCallbacks; // 0x12458290
	extern std::vector<std::function<void __cdecl(void)>,std::allocator<std::function<void __cdecl(void)> > > gameStartCallbacks; // 0x12458380
	extern std::vector<std::function<void __cdecl(void)>,std::allocator<std::function<void __cdecl(void)> > > shutdownCallbacks; // 0x124583E4
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > mainLoadMapPath; // 0x12458310
	extern long long cpuFrequencyMs; // 0x12458410
	extern _LARGE_INTEGER startTime; // 0x12458418
}
/* ---------- public code */

namespace Patches
{
	namespace Core
	{
		_extern void _sub_10A45AD0();
		void ApplyAll() // 0x10A45AD0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Core@Patches@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10A47D68
			// static ...; // 0x10A47D5C
			// static ...; // 0x10A47D54
			// _LARGE_INTEGER cpuFreq;
			// function call : __int32 (_LARGE_INTEGER *)
			// function call : __int32 (_LARGE_INTEGER *)
			todo("implement");
			_sub_10A45AD0();
		}

		_extern void _sub_10A44ED0();
		void ApplyAfterInit() // 0x10A44ED0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAfterInit@Core@Patches@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10A4585C
			// static ...; // 0x10A45850
			// static ...; // 0x10A45848
			// std::basic_string<char,std::char_traits<char>,std::allocator<char> > path;
			todo("implement");
			_sub_10A44ED0();
		}

		_extern void _sub_10A49010(std::function<void __cdecl(void)>);
		void OnShutdown(std::function<void __cdecl(void)> callback) // 0x10A49010
		{
			mangled_x86(MANGLED_TODO, "?OnShutdown@Core@Patches@@YAXV?$function@$$A6AXXZ@std@@@Z");
			// std::function<void __cdecl(void)> callback;
			todo("implement");
			_sub_10A49010(callback);
		}

		_extern void _sub_10A48680();
		void ExecuteShutdownCallbacks() // 0x10A48680
		{
			mangled_x86(MANGLED_TODO, "?ExecuteShutdownCallbacks@Core@Patches@@YAXXZ");
			// procedure flags: nofpo
			{
				// std::vector<std::function<void __cdecl(void)>,std::allocator<std::function<void __cdecl(void)> > > &<range>$L0;
				// std::function<void __cdecl(void)> *<begin>$L0;
				// std::function<void __cdecl(void)> *<end>$L0;
				{
					// std::function<void __cdecl(void)> &callback;
				}
			}
			todo("implement");
			_sub_10A48680();
		}

		_extern void _sub_10A48F70(std::function<void __cdecl(char const *)>);
		void OnMapLoaded(std::function<void __cdecl(char const *)> callback) // 0x10A48F70
		{
			mangled_x86(MANGLED_TODO, "?OnMapLoaded@Core@Patches@@YAXV?$function@$$A6AXPBD@Z@std@@@Z");
			// std::function<void __cdecl(char const *)> callback;
			todo("implement");
			_sub_10A48F70(callback);
		}

		_extern void _sub_10A48ED0(std::function<void __cdecl(void)>);
		void OnGameStart(std::function<void __cdecl(void)> callback) // 0x10A48ED0
		{
			mangled_x86(MANGLED_TODO, "?OnGameStart@Core@Patches@@YAXV?$function@$$A6AXXZ@std@@@Z");
			// std::function<void __cdecl(void)> callback;
			todo("implement");
			_sub_10A48ED0(callback);
		}
	}
}

/* ---------- private code */
