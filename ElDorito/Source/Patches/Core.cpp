/* ---------- headers */

#include "Patches/Core.hpp"
#include "hades/hades.h"

#include "Blam/ai/actor.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_engine_candy_monitor.hpp"
#include "Blam/game/game_time.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/main/main_time.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/tls.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
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
struct s_game_tick_time_samples;
struct s_main_time_globals;
struct s_player_datum;
struct s_unit_data;

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

namespace Patches { void ApplyAfterTagsLoaded(); }  // hades: added for 0X10A4AC90
namespace Patches { namespace Mopp { void InitializeForNewMap(); } }  // hades: added for 0X10A4AC90

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

void GameTickHook();
void ShutdownHook();
char const *GetMapsFolderHook();
bool LoadMapHook(void *data);
void LoadLevelHook(unsigned char *data, char n2, __int32 n3, __int32 n4);
__int32 levels_get_campaign_next_map_id_hook(__int32 campaign_id, __int32 map_id);
void GameStartHook();
bool main_load_map_hook(long campaign_id, long map_id, char const *map_path);
void FovHook();
bool z_buffer_fix_enabled();
void ActiveCamoViewModelClipHook(float *nearPlane, float *farPlane);
double AspectRatioHook();
char GetBinkVideoPathHook(__int32 p_VideoID, char *p_DestBuf);
void GetScreenshotFolderHook(wchar_t *path);
void HsPrintHook(char const *message);
void sub_757890_call_hook(__int32 a1, __int32 a2);
long long main_time_get_absolute_milliseconds();
float main_time_update_hook();
long hs_seconds_to_ticks_hook(float seconds);
unsigned __int32 system_milliseconds_hook();
void publish_waiting_gamestate();
void main_loop();
unsigned long render_thread_loop(void *lpParam);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern std::string MapsFolder; // 0x124582F4
	extern std::string MapFormatString; // 0x1245832C
	extern std::string StringIdsPath; // 0x124582D8
	extern std::string TagsPath; // 0x124582A0
	extern std::string TagListPath; // 0x124582BC
	extern std::string ResourcesPath; // 0x124583C8
	extern std::string ResourcesBPath; // 0x12458348
	extern std::string TexturesPath; // 0x124583AC
	extern std::string TexturesBPath; // 0x124583F4
	extern std::string AudioPath; // 0x12458390
	extern std::string FontsPath; // 0x12458364
	extern std::vector<std::function<void __cdecl(char const *)> > mapLoadedCallbacks; // 0x12458290
	extern std::vector<std::function<void __cdecl(void)> > gameStartCallbacks; // 0x12458380
	extern std::vector<std::function<void __cdecl(void)> > shutdownCallbacks; // 0x124583E4
	extern std::string mainLoadMapPath; // 0x12458310
	extern long long cpuFrequencyMs; // 0x12458410
	extern _LARGE_INTEGER startTime; // 0x12458418
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Core
	{
		_extern void _sub_10A45AD0();
		void ApplyAll() // 0x10A45AD0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Core@Patches@@YAXXZ");
			// procedure flags: nofpo

			QueryPerformanceCounter(&startTime);
			_LARGE_INTEGER cpuFreq;
			QueryPerformanceFrequency(&cpuFreq);
			cpuFrequencyMs = cpuFreq.QuadPart / 1000;

			Patch(0x101A5B, { 0xEB }).Apply();
			Patch::NopFill(Pointer::Base(0x102874), 2);
			Patch::NopFill(Pointer::Base(0x1030AA), 2);
			Patch(0x43731A, { 0xEB, 0x0E }).Apply();
			Patch(0x4373AD, { 0xEB, 0x03 }).Apply();
			Patch(0x3B8810, { 0xC3 }).Apply();
			Patch::NopFill(Pointer::Base(0x10C99A), 6);
			Patch::NopFill(Pointer::Base(0x1033321), 2);
			Hook(0x101FC0, GetMapsFolderHook).Apply();
			Hook(0x2EBD7, ShutdownHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x10FC2C, LoadMapHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1671BE, LoadMapHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x167B4F, LoadMapHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x14C7FF, LoadLevelHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x152C15, GameStartHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x14EB62, GameStartHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x14EB54, GameStartHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch::NopFill(Pointer::Base(0x167101), 13);
			Patch(0x1671E8, { 0x4A, 0x71, 0x56, 0x00, 0x4A, 0x71, 0x56, 0x00, 0x4A, 0x71, 0x56, 0x00 }).Apply();
			Hook(0x167300, levels_get_campaign_next_map_id_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x105ABA, GameTickHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x105AD7, GameTickHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1063E6, GameTickHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1679B5, main_load_map_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch::NopFill(Pointer::Base(0x25FA79), 10);
			Patch::NopFill(Pointer::Base(0x25FA86), 5);
			Hook(0x10CA02, FovHook).Apply();
			Hook(0x663B36, ActiveCamoViewModelClipHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x66B0CE, 0x90, 6).Apply();
			Hook(0x6648C9, AspectRatioHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x216487, AspectRatioHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch::NopFill(Pointer::Base(0x62217D), 2);
			Patch::NopFill(Pointer::Base(0x622183), 6);
			Patch::NopFill(Pointer::Base(0x10BF1B), 2);
			Patch::NopFill(Pointer::Base(0x10BF21), 6);
			Pointer::Base(0x1A315F).Write<unsigned char>(0xEB);
			Pointer::Base(0x1A31A4).Write<unsigned char>(0xEB);
			Hook(0x10590B, GetBinkVideoPathHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x20F4AD, GetScreenshotFolderHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x20F44B, GetScreenshotFolderHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x1BD006, sub_757890_call_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x105CBA, main_time_update_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Pointer(0x22AE4F2).Write<unsigned char>(0x01);
			Hook(0x32FE9A, HsPrintHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x5D882F, 0x90, 6).Apply();
			Patch(0x386AAD, { 0xEB }).Apply();
			Hook(0x279670, hs_seconds_to_ticks_hook).Apply();
			Hook(0xEC110, system_milliseconds_hook).Apply();
			Hook(0x1059E0, main_loop).Apply();
			Hook(0x1075A0, render_thread_loop).Apply();
		}

		_extern void _sub_10A44ED0();
		void ApplyAfterInit() // 0x10A44ED0
		{
			mangled_x86(MANGLED_TODO, "?ApplyAfterInit@Core@Patches@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10A4585C
			// static ...; // 0x10A45850
			// static ...; // 0x10A45848
			// std::string path;
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
				// std::vector<std::function<void __cdecl(void)> > &<range>$L0;
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

void GameTickHook() // 0x10A487F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GameTickHook@@YAXXZ");
	// `anonymous-namespace'::GameTickHook
	// procedure flags: nofpo
	// void (*sub_5547F0)();
	// function call : void (*)()

	ElDorito::Instance().Tick();

	void (*GameTick)() = (void(*)())0x5547f0;

	GameTick();
}

void ShutdownHook() // 0x10A490B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ShutdownHook@@YAXXZ");
	// `anonymous-namespace'::ShutdownHook
	// procedure flags: nofpo
	// void (*EngineShutdown)();
	// function call : void (*)()

	ElDorito::Instance().Shutdown();
	Patches::Core::ExecuteShutdownCallbacks();
	void (*ShutdownGame)() = (void (*)())0x42e410;

	ShutdownGame();
}

char const *GetMapsFolderHook() // 0x10A488D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMapsFolderHook@@YAPBDXZ");
	// `anonymous-namespace'::GetMapsFolderHook
	// procedure flags: nofpo

	return MapsFolder.c_str();
}

bool LoadMapHook(void *data) // 0x10A48DF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LoadMapHook@@YA_NPAX@Z");
	// `anonymous-namespace'::LoadMapHook
	// void *data;
	// bool (*LoadMap)(void *);
		// std::vector<std::function<void __cdecl(char const *)> > &<range>$L0;
		// std::function<void __cdecl(char const *)> *<begin>$L0;
		// std::function<void __cdecl(char const *)> *<end>$L0;
			// std::function<void __cdecl(char const *)> &callback;
	// function call : bool (*)(void *)

	typedef bool(*LoadMapPtr)(void *data);
	auto LoadMap = reinterpret_cast<LoadMapPtr>(0x566EF0);
	if (!LoadMap(data))
		return false;

	for (auto &&callback : mapLoadedCallbacks)
		callback(static_cast<const char*>(data) + 0x24); // hax

	return true;
}

void LoadLevelHook(unsigned char *data, char n2, __int32 n3, __int32 n4) // 0x10A48D40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LoadLevelHook@@YAXPAEDHH@Z");
	// `anonymous-namespace'::LoadLevelHook
	// __int32 n4;
	// __int32 (*LoadLevel)(unsigned char *, char, __int32, __int32);
	// function call : __int32 (*)(unsigned char *, char, __int32, __int32)

	void (__cdecl *LoadLevel)(unsigned char *, unsigned char, __int32, __int32) = (void(__cdecl *)(unsigned char *, unsigned char, __int32, __int32))0x54A6C0;

	*(unsigned int *)(data + 0x111C) = 0x8081002;
	*(unsigned int *)(data + 0x1120) = 0x8080808;
	*(unsigned int *)(data + 0x1124) = 0x8080808;
	LoadLevel(data, n2, n3, n4);
}

_extern __int32 _sub_10A4AAF0(__int32, __int32);
__int32 levels_get_campaign_next_map_id_hook(__int32 campaign_id, __int32 map_id) // 0x10A4AAF0
{
	// `anonymous-namespace'::levels_get_campaign_next_map_id_hook
	// __int32 map_id;
	// __int32 (*const levels_get_campaign_next_map_id)(unsigned __int32, unsigned __int32);
	// __int32 (*const game_progression_globals_get_tag)();
	// __int32 gpdt_map_block_index;
	// __int32 game_progression_type;
	{
		// __int32 gpdt_tag;
	}
	// function call : __int32 (*const)()
	// function call : __int32 (*const)(unsigned __int32, unsigned __int32)
	todo("implement");
	__int32 __result = _sub_10A4AAF0(campaign_id, map_id);
	return __result;
}

_extern void _sub_10A48740();
void GameStartHook() // 0x10A48740
{
	// `anonymous-namespace'::GameStartHook
	// procedure flags: nofpo
	// void (*GameStart)();
	{
		// std::vector<std::function<void __cdecl(void)> > &<range>$L0;
		// std::function<void __cdecl(void)> *<begin>$L0;
		// std::function<void __cdecl(void)> *<end>$L0;
		{
			// std::function<void __cdecl(void)> &callback;
		}
	}
	// function call : void (*)()
	todo("implement");
	_sub_10A48740();
}

bool main_load_map_hook(long campaign_id, long map_id, char const *map_path) // 0x10A4AC90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?main_load_map_hook@@YA_NJJPBD@Z");
	// `anonymous-namespace'::main_load_map_hook
	// char const *map_path;
	// bool loaded;
	// constexpr bool (*const `main_load_map_hook'::`2'::main_load_map)(long, long, char const *); // constant == 5154272
	// function call : bool (*const)(long, long, char const *)

	mainLoadMapPath = map_path;
	bool loaded = ((bool(__cdecl *)(long, long, char const *))0x4ea5e0)(campaign_id, map_id, map_path);
	if (loaded)
	{
		mainLoadMapPath = "";
		Patches::ApplyAfterTagsLoaded();
		Patches::Mopp::InitializeForNewMap();
	}
	return loaded;
}

__declspec(naked) void FovHook() // 0x10A48720
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FovHook@@YAXXZ");
	// `anonymous-namespace'::FovHook
	// procedure flags: nofpo

	__asm
	{
		mov eax, ds:[0189D42Ch]
		mov ds:[02301D98h], eax
		mov ecx, [edi + 18h]
		push 050CA08h
		ret
	}
}

_extern bool _sub_10A4C430();
bool z_buffer_fix_enabled() // 0x10A4C430
{
	// `anonymous-namespace'::z_buffer_fix_enabled
	// procedure flags: nofpo
	todo("implement");
	bool __result = _sub_10A4C430();
	return __result;
}

_extern void _sub_10A44CB0(float *, float *);
void ActiveCamoViewModelClipHook(float *nearPlane, float *farPlane) // 0x10A44CB0
{
	// `anonymous-namespace'::ActiveCamoViewModelClipHook
	// float *farPlane;
	// void (*const view_get_clip_planes)(float *, float *);
	{
		// s_player_datum const *player;
		// unsigned long const playerIndex;
		{
			// s_unit_data *unitObject;
			// float activeCamoPower;
			{
				// float const globalNear;
				// float const globalFar;
			}
		}
	}
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(float *, float *)
	todo("implement");
	_sub_10A44CB0(nearPlane, farPlane);
}

double AspectRatioHook() // 0x10A48620
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?AspectRatioHook@@YANXZ");
	// `anonymous-namespace'::AspectRatioHook
	// procedure flags: nofpo
	// __int32 *gameResolution;

	int* gameResolution = reinterpret_cast<int*>(0x19106C0);
	return ((double)gameResolution[0] / (double)gameResolution[1]);
}

_extern char _sub_10A48860(__int32, char *);
char GetBinkVideoPathHook(__int32 p_VideoID, char *p_DestBuf) // 0x10A48860
{
	// `anonymous-namespace'::GetBinkVideoPathHook
	// char *p_DestBuf;
	// function call : char (*const)(__int32, char *)
	todo("implement");
	char __result = _sub_10A48860(p_VideoID, p_DestBuf);
	return __result;
}

_extern void _sub_10A48920(wchar_t *);
void GetScreenshotFolderHook(wchar_t *path) // 0x10A48920
{
	// `anonymous-namespace'::GetScreenshotFolderHook
	// static ...; // 0x10A48B69
	// static ...; // 0x10A48B58
	// static ...; // 0x10A48B54
	// static ...; // 0x10A48B30
	// static ...; // 0x10A48B28
	// wchar_t *path;
	// std::wstring_convert<std::codecvt_utf8<wchar_t,1114111,0>,wchar_t,std::allocator<wchar_t>,std::allocator<char> > wstring_to_string;
	// unsigned long return_code;
	// std::wstring unprocessed_path;
	// std::filesystem::path dir;
	{
		// static void (*`GetScreenshotFolderHook'::`5'::GetScreenshotsFolder)(wchar_t *); // 0x11354268
	}
	// function call : unsigned long (wchar_t const *, wchar_t *, unsigned long)
	// function call : void (*)(wchar_t *)
	todo("implement");
	_sub_10A48920(path);
}

_extern void _sub_10A48C20(char const *);
void HsPrintHook(char const *message) // 0x10A48C20
{
	// `anonymous-namespace'::HsPrintHook
	// char const *message;
	todo("implement");
	_sub_10A48C20(message);
}

_extern void _sub_10A4C2F0(__int32, __int32);
void sub_757890_call_hook(__int32 a1, __int32 a2) // 0x10A4C2F0
{
	// `anonymous-namespace'::sub_757890_call_hook
	// __int32 a2;
	// constexpr void (*const `sub_757890_call_hook'::`2'::sub_757890)(__int32, __int32); // constant == 7698576
	// function call : void (*const)(__int32, __int32)
	todo("implement");
	_sub_10A4C2F0(a1, a2);
}

_extern long long _sub_10A4B3A0();
long long main_time_get_absolute_milliseconds() // 0x10A4B3A0
{
	// `anonymous-namespace'::main_time_get_absolute_milliseconds
	// procedure flags: nofpo
	// long long ms;
	// long long last_milliseconds;
	// unsigned __int32 milliseconds;
	todo("implement");
	long long __result = _sub_10A4B3A0();
	return __result;
}

_extern float _sub_10A4B490();
float main_time_update_hook() // 0x10A4B490
{
	// `anonymous-namespace'::main_time_update_hook
	// procedure flags: nofpo
	// static ...; // 0x10A4B9CF
	// static ...; // 0x10A4B9C6
	// static ...; // 0x10A4B9B8
	// static ...; // 0x10A4B9A0
	// static ...; // 0x10A4B998
	// _LARGE_INTEGER cpu_tick;
	// long game_time;
	// long long (*const rasterizer_get_vblank_index)();
	// float delta_frame_time;
	// float target_frame_time;
	// bool in_game;
	// _LARGE_INTEGER cpu_frequency;
	// bool skip_time_sync;
	// bool const g_main_time_is_throttled;
	// s_main_time_globals *g_main_time_globals;
	// float (*const main_time_update)();
	// void (*const shell_idle)();
	// long long vblank_index;
	// __int32 frame_rate_limit;
	// bool const g_debug_disable_frame_rate_throttle;
	// long long milliseconds;
	{
		// __int32 sleep_ms;
		// __int32 excess_ms;
		{
			// unsigned long prev;
			// void *process_handle;
		}
	}
	// function call : long long (*const)()
	// function call : __int32 (_LARGE_INTEGER *)
	// function call : bool (*const)()
	// function call : long (*const)()
	// function call : __int32 (_LARGE_INTEGER *)
	// function call : void *()
	// function call : unsigned long (void *)
	// function call : __int32 (void *, unsigned long)
	// function call : unsigned long (unsigned long, __int32)
	// function call : __int32 (void *, unsigned long)
	// function call : __int32 (_LARGE_INTEGER *)
	// function call : bool (*const)()
	todo("implement");
	float __result = _sub_10A4B490();
	return __result;
}

_extern long _sub_10A4A9E0(float);
long hs_seconds_to_ticks_hook(float seconds) // 0x10A4A9E0
{
	// `anonymous-namespace'::hs_seconds_to_ticks_hook
	// float seconds;
	// float ticks;
	todo("implement");
	long __result = _sub_10A4A9E0(seconds);
	return __result;
}

_extern unsigned __int32 _sub_10A4C360();
unsigned __int32 system_milliseconds_hook() // 0x10A4C360
{
	// `anonymous-namespace'::system_milliseconds_hook
	// procedure flags: nofpo
	// static ...; // 0x10A4C3F0
	// static ...; // 0x10A4C3E4
	// static ...; // 0x10A4C3DC
	// _LARGE_INTEGER currentTime;
	// function call : __int32 (_LARGE_INTEGER *)
	todo("implement");
	unsigned __int32 __result = _sub_10A4C360();
	return __result;
}

_extern void _sub_10A4BC80();
void publish_waiting_gamestate() // 0x10A4BC80
{
	// `anonymous-namespace'::publish_waiting_gamestate
	// procedure flags: nofpo
	// void (*const main_render_purge_pending_messages)();
	// bool (*const multithreaded)();
	// void (*const main_time_mark_publishing_start_time)();
	// unsigned long (*const main_time_mark_publishing_end_time)();
	// bool (*const restricted_region_publish_to_mirror_blocking)(long);
	// long volatile &g_render_thread_enabled;
	{
		// s_game_tick_time_samples *gamestate_timing;
	}
	// function call : bool (*const)()
	// function call : void (*const)()
	// function call : bool (*const)(long)
	// function call : void (*const)()
	// function call : unsigned long (*const)()
	todo("implement");
	_sub_10A4BC80();
}

_extern void _sub_10A4AD40();
void main_loop() // 0x10A4AD40
{
	// `anonymous-namespace'::main_loop
	// procedure flags: nofpo
	// void (*const main_game_unload_and_prepare_for_next_game)(void *);
	// void (*const c_rasterizer__rasterizer_device_release_thread)();
	// void (*const main_render_purge_pending_messages)();
	// void (*const c_interlocked_long__set_bit)(long volatile *, char, char);
	// void *(*const restricted_region_lock_primary)(long);
	// void (*const main_render_signal_shutdown)();
	// void (*const physical_memory_resize_region_dispose)();
	// void (*const game_sound_process_update_messages)();
	// long volatile &g_single_thread_request_flags;
	// __int32 (*const _internal_halt_render_thread_and_lock_resources)(char const *, __int32);
	// bool (*const multithreaded)();
	// bool &unk_22AE4F2;
	// long (*const c_interlocked_int32__set)(long volatile *, long);
	// void (*const main_loading_dispose)();
	// void (*const main_loop_body_single_threaded)();
	// char &unk_22AE4F0;
	// bool &g_main_exit;
	// unsigned long &dword_22B47B8;
	// char (*const screenshot_unknown)();
	// long (*const c_synchronized_int32__set_if_equal)(long volatile *, long, long);
	// void (*const game_dispose)();
	// void (*const main_loop_enter)();
	// char (*const sub_610530)();
	// char v2;
	// void (*const process_game_engine_globals_messages)();
	// void (*const wait_for_thread_to_exit)(__int32, unsigned long);
	// long volatile &g_render_thread_enabled;
	// unsigned long v3;
	// void (*const main_loop_body)();
	// char a3;
	// void (*const restricted_region_unlock_primary)(long);
	// function call : bool (*const)()
	// function call : void (*const)()
	// function call : bool (*const)()
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	// function call : void (*const)(long volatile *, char, char)
	// function call : bool (*const)()
	// function call : void (*const)()
	// function call : void (*const)()
	// function call : void (*const)()
	// function call : void (*const)()
	// function call : char (*const)()
	// function call : char (*const)()
	// function call : void (*const)(long volatile *, char, char)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : void (*const)()
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	// function call : bool (*const)()
	// function call : long (*const)(long volatile *, long, long)
	// function call : __int32 (*const)(char const *, __int32)
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : void *(*const)(long)
	// function call : void *(*const)(long)
	// function call : bool (*const)()
	// function call : void (*const)()
	// function call : void (*const)(__int32, unsigned long)
	// function call : void (*const)()
	// function call : void (*const)(void *)
	// function call : void (*const)()
	// function call : void (*const)()
	// function call : void (*const)()
	todo("implement");
	_sub_10A4AD40();
}

_extern unsigned long _sub_10A4BE90(void *);
unsigned long render_thread_loop(void *lpParam) // 0x10A4BE90
{
	// `anonymous-namespace'::render_thread_loop
	// void *lpParam;
	// bool (*const restricted_region_try_and_lock_primary)(long);
	// bool (*const restricted_region_lock_mirror)(long);
	// long (*const c_rasterizer__rasterizer_device_acquire_thread)();
	// void (*const c_rasterizer__rasterizer_device_release_thread)();
	// void (*const font_idle)();
	// long volatile &g_render_thread_waiting;
	// bool (*const current_thread_should_exit)();
	// void (*const process_published_game_state)(char);
	// unsigned long (*const tag_resources_lock_render)();
	// long volatile &g_single_thread_request_flags;
	// bool (*const multithreaded)();
	// long (*const c_interlocked_int32__set)(long volatile *, long);
	// bool (*const restricted_region_wait_for_available_mirror)(long, __int32);
	// void (*const c_rasterizer__cleanup_d3d_states)(char);
	// bool (*const restricted_region_mirror_locked_for_current_thread)(long);
	// long volatile &g_render_thread_enabled;
	// void (*const tag_resources_unlock_render_gpu_usage)(unsigned long);
	// __int32 (*const restricted_region_unlock_mirror)(__int32);
	// unsigned long (*const tag_resources_unlock_render_access)();
	// __int32 (*const current_thread_update_test_functions)();
	// void (*const restricted_region_unlock_primary)(long);
	{
		// unsigned long tag_resource_access_cookie;
	}
	// function call : bool (*const)()
	// function call : bool (*const)()
	// function call : __int32 (*const)()
	// function call : void (*const)()
	// function call : long (*const)(long volatile *, long)
	// function call : bool (*const)(long, __int32)
	// function call : bool (*const)(long)
	// function call : bool (*const)(long)
	// function call : bool (*const)()
	// function call : bool (*const)(long)
	// function call : long (*const)(long volatile *, long)
	// function call : unsigned long (*const)()
	// function call : long (*const)()
	// function call : void (*const)(char)
	// function call : void (*const)(char)
	// function call : unsigned long (*const)()
	// function call : void (*const)()
	// function call : void (*const)(unsigned long)
	// function call : bool (*const)(long)
	// function call : __int32 (*const)(__int32)
	// function call : void (*const)(long)
	// function call : void (*const)(long)
	// function call : long (*const)(long volatile *, long)
	// function call : void (*const)()
	// function call : bool (*const)()
	todo("implement");
	unsigned long __result = _sub_10A4BE90(lpParam);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template void Pointer::Write<char const *>(char const *const) const;
