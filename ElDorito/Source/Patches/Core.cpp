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

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const game_in_progress = reinterpret_cast<bool (*)()>(0x5314B0);
}
#line 119

template<typename t_arg0> static t_arg0 *object_get(unsigned long object_index) { return (t_arg0 *)object_get(object_index); }  // hades: a file-local template in the original (undecorated `object_get<T>`), defined so it is emitted;  // hades: added for 0x10A44CB0

#include "Modules/ModuleGame.hpp"  // hades: added for 0x10A48860

#include "Modules/ModuleDebug.hpp"  // hades: added for 0x10A4C430
#include "Modules/ModuleGraphics.hpp"  // hades: added for 0x10A4C2F0
#include "Modules/ModuleScript.hpp"  // hades: added for 0x10A48C20

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
static bool z_buffer_fix_enabled();
void ActiveCamoViewModelClipHook(float *nearPlane, float *farPlane);
double AspectRatioHook();
char GetBinkVideoPathHook(__int32 p_VideoID, char *p_DestBuf);
void GetScreenshotFolderHook(wchar_t *path);
void HsPrintHook(char const *message);
void sub_757890_call_hook(__int32 a1, __int32 a2);
long long main_time_get_absolute_milliseconds();
extern long (*const game_time_get)();  // hades: added for 0x10A4B490
float main_time_update_hook();
long hs_seconds_to_ticks_hook(float seconds);
unsigned __int32 system_milliseconds_hook();
void publish_waiting_gamestate();
void main_loop();
unsigned long render_thread_loop(void *lpParam);

/* ---------- globals */

namespace Job { void Dispose(); }  // hades: added for 0X10A48680

/* ---------- private variables */

namespace hades_file_local
{
	extern "C" { std::string MapsFolder; } // 0x124582F4
	std::string MapFormatString; // 0x1245832C
	std::string StringIdsPath; // 0x124582D8
	std::string TagsPath; // 0x124582A0
	std::string TagListPath; // 0x124582BC
	std::string ResourcesPath; // 0x124583C8
	std::string ResourcesBPath; // 0x12458348
	std::string TexturesPath; // 0x124583AC
	std::string TexturesBPath; // 0x124583F4
	std::string AudioPath; // 0x12458390
	std::string FontsPath; // 0x12458364
	std::vector<std::function<void __cdecl(char const *)> > mapLoadedCallbacks; // 0x12458290
	std::vector<std::function<void __cdecl(void)> > gameStartCallbacks; // 0x12458380
	std::vector<std::function<void __cdecl(void)> > shutdownCallbacks; // 0x124583E4
	std::string mainLoadMapPath; // 0x12458310
	extern "C" long long cpuFrequencyMs; // 0x12458410
	extern _LARGE_INTEGER startTime; // 0x12458418
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Core
	{

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

		void ApplyAfterInit() // 0x10A44ED0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAfterInit@Core@Patches@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10A4585C
			// static ...; // 0x10A45850
			// static ...; // 0x10A45848
			// std::string path;

			std::string path = ElDorito::Instance().GetMapsFolder();
			MapsFolder = path;
			MapFormatString = MapsFolder + "%s.map";
			StringIdsPath = MapsFolder + "string_ids.dat";
			TagsPath = MapsFolder + "tags.dat";
			TagListPath = MapsFolder + "tag_list.csv";
			ResourcesPath = MapsFolder + "resources.dat";
			ResourcesBPath = MapsFolder + "resources_b.dat";
			TexturesPath = MapsFolder + "textures.dat";
			TexturesBPath = MapsFolder + "textures_b.dat";
			AudioPath = MapsFolder + "audio.dat";
			FontsPath = MapsFolder + "fonts\\";
			Pointer::Base(0x1AC050).Write<char const *>(MapFormatString.c_str());
			Pointer::Base(0x149CFEC).Write<char const *>(StringIdsPath.c_str());
			Pointer::Base(0x149CFF0).Write<char const *>(TagsPath.c_str());
			Pointer::Base(0x149CFF4).Write<char const *>(TagListPath.c_str());
			Pointer::Base(0x149D358).Write<char const *>(FontsPath.c_str());
			Pointer::Base(0x149D35C).Write<char const *>(FontsPath.c_str());
			Pointer::Base(0x149CFF8).Write<char const *>(ResourcesPath.c_str());
			Pointer::Base(0x149D008).Write<char const *>(ResourcesBPath.c_str());
			Pointer::Base(0x149CFFC).Write<char const *>(TexturesPath.c_str());
			Pointer::Base(0x149D000).Write<char const *>(TexturesBPath.c_str());
			Pointer::Base(0x149D004).Write<char const *>(AudioPath.c_str());
			Pointer(0x22AE4D8).Write<char const *>(ResourcesPath.c_str());
			Pointer(0x22AE4E8).Write<char const *>(ResourcesBPath.c_str());
			Pointer(0x22AE4DC).Write<char const *>(TexturesPath.c_str());
			Pointer(0x22AE4E0).Write<char const *>(TexturesBPath.c_str());
			Pointer(0x22AE4E4).Write<char const *>(AudioPath.c_str());
		}

		void OnShutdown(std::function<void __cdecl(void)> callback) // 0x10A49010
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnShutdown@Core@Patches@@YAXV?$function@$$A6AXXZ@std@@@Z");
			// std::function<void __cdecl(void)> callback;

			shutdownCallbacks.push_back(callback);
		}

		void ExecuteShutdownCallbacks() // 0x10A48680
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ExecuteShutdownCallbacks@Core@Patches@@YAXXZ");
			// procedure flags: nofpo
				// std::vector<std::function<void __cdecl(void)> > &<range>$L0;
				// std::function<void __cdecl(void)> *<begin>$L0;
				// std::function<void __cdecl(void)> *<end>$L0;
					// std::function<void __cdecl(void)> &callback;

			for (auto &&callback : shutdownCallbacks)
				callback();

			Job::Dispose();
		}

		void OnMapLoaded(std::function<void __cdecl(char const *)> callback) // 0x10A48F70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnMapLoaded@Core@Patches@@YAXV?$function@$$A6AXPBD@Z@std@@@Z");
			// std::function<void __cdecl(char const *)> callback;

			mapLoadedCallbacks.push_back(callback);
		}

		void OnGameStart(std::function<void __cdecl(void)> callback) // 0x10A48ED0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OnGameStart@Core@Patches@@YAXV?$function@$$A6AXXZ@std@@@Z");
			// std::function<void __cdecl(void)> callback;

			gameStartCallbacks.push_back(callback);
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

__int32 levels_get_campaign_next_map_id_hook(__int32 campaign_id, __int32 map_id) // 0x10A4AAF0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?levels_get_campaign_next_map_id_hook@@YAHHH@Z");
	// `anonymous-namespace'::levels_get_campaign_next_map_id_hook
	// __int32 map_id;
	// __int32 (*const levels_get_campaign_next_map_id)(unsigned __int32, unsigned __int32);
	// __int32 (*const game_progression_globals_get_tag)();
	// __int32 gpdt_map_block_index;
	// __int32 game_progression_type;
		// __int32 gpdt_tag;
	// function call : __int32 (*const)()
	// function call : __int32 (*const)(unsigned __int32, unsigned __int32)

	__int32 (*const levels_get_campaign_next_map_id)(unsigned __int32, unsigned __int32) = reinterpret_cast<__int32 (*)(unsigned __int32, unsigned __int32)>(0x54BB80);
	__int32 (*const game_progression_globals_get_tag)() = reinterpret_cast<__int32 (*)()>(0x671D00);
	__int32 game_progression_type = Pointer(0x23917E8).Read<__int32>();
	__int32 gpdt_map_block_index = Pointer(0x23917EC).Read<__int32>();
	if (game_progression_type > 0)
	{
		__int32 gpdt_tag = game_progression_globals_get_tag();
		map_id = *(__int32 *)(gpdt_map_block_index * 0x124 + *(__int32 *)(gpdt_tag + 0x34) + 0x1C);
	}
	else
		map_id = levels_get_campaign_next_map_id(campaign_id, map_id);
	return map_id;
}

void GameStartHook() // 0x10A48740
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GameStartHook@@YAXXZ");
	// `anonymous-namespace'::GameStartHook
	// procedure flags: nofpo
	// void (*GameStart)();
		// std::vector<std::function<void __cdecl(void)> > &<range>$L0;
		// std::function<void __cdecl(void)> *<begin>$L0;
		// std::function<void __cdecl(void)> *<end>$L0;
			// std::function<void __cdecl(void)> &callback;
	// function call : void (*)()

	typedef void(*GameStartPtr)();
	auto GameStart = reinterpret_cast<GameStartPtr>(0x551590);
	GameStart();

	for (auto &&callback : gameStartCallbacks)
		callback();
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

static bool z_buffer_fix_enabled() // 0x10A4C430
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?z_buffer_fix_enabled@@YA_NXZ");
	// `anonymous-namespace'::z_buffer_fix_enabled
	// procedure flags: nofpo

	return Utils::Singleton<Modules::ModuleDebug>::Instance().VarZBuffTest->ValueInt != 0;
}

void ActiveCamoViewModelClipHook(float *nearPlane, float *farPlane) // 0x10A44CB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ActiveCamoViewModelClipHook@@YAXPAM0@Z");
	// `anonymous-namespace'::ActiveCamoViewModelClipHook
	// float *farPlane;
	// void (*const view_get_clip_planes)(float *, float *);
		// s_player_datum const *player;
		// unsigned long const playerIndex;
			// s_unit_data *unitObject;
			// float activeCamoPower;
				// float const globalNear;
				// float const globalFar;
	// function call : unsigned long (*const)(long)
	// function call : void (*const)(float *, float *)

	void (*const view_get_clip_planes)(float *, float *) = reinterpret_cast<void (*)(float *, float *)>(0xA25AA0);
	if (!z_buffer_fix_enabled())
	{
		unsigned long const playerIndex = ((unsigned long (*)(long))0x589C30)(0);
		if (playerIndex != -1)
		{
			s_player_datum const *player = players_get()->try_and_get(playerIndex);
			if (player)
			{
				s_unit_data *unitObject = object_get<s_unit_data>(player->unit_index);
				float activeCamoPower = 0.0f;
				if (unitObject)
				{
					float const globalNear = *(float *)0x191068C;
					float const globalFar = *(float *)0x1910690;
					activeCamoPower = unitObject->active_camouflage;
					if (activeCamoPower > 0.0f)
					{
						*nearPlane = globalNear * 3.25f;
						*farPlane = globalFar;
						return;
					}
					if (unitObject->scale < 0.4)
					{
						*nearPlane = globalNear * std::max(2.0f, unitObject->scale / 0.4f * 10.0f);
						*farPlane = globalFar;
						return;
					}
				}
			}
		}
	}
	view_get_clip_planes(nearPlane, farPlane);
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

char GetBinkVideoPathHook(__int32 p_VideoID, char *p_DestBuf) // 0x10A48860
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetBinkVideoPathHook@@YADHPAD@Z");
	// `anonymous-namespace'::GetBinkVideoPathHook
	// char *p_DestBuf;
	// function call : char (*const)(__int32, char *)

	if (Utils::Singleton<Modules::ModuleGame>::Instance().VarSkipIntroVideos->ValueInt == 1)
	{
		return 0;
	}

	return ((char(__cdecl *)(__int32, char *))0xA99120)(p_VideoID, p_DestBuf);
}

void GetScreenshotFolderHook(wchar_t *path) // 0x10A48920
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetScreenshotFolderHook@@YAXPA_W@Z");
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
		// static void (*`GetScreenshotFolderHook'::`5'::GetScreenshotsFolder)(wchar_t *); // 0x11354268
	// function call : unsigned long (wchar_t const *, wchar_t *, unsigned long)
	// function call : void (*)(wchar_t *)

	std::wstring_convert<std::codecvt_utf8<wchar_t>> wstring_to_string;
	std::wstring unprocessed_path = wstring_to_string.from_bytes(Utils::Singleton<Modules::ModuleGame>::Instance().VarScreenshotsFolder->ValueString);
	unsigned long return_code = ExpandEnvironmentStringsW(unprocessed_path.c_str(), path, 0x104);
	if (return_code == 0 || return_code > 0x104)
	{
		static void (*GetScreenshotsFolder)(wchar_t *) = reinterpret_cast<void (*)(wchar_t *)>(0x60F310);
		GetScreenshotsFolder(path);
		return;
	}
	std::filesystem::path dir(path);
	dir = std::filesystem::weakly_canonical(dir);
	std::filesystem::create_directories(dir);
	wcsncpy(path, dir.c_str(), 0x103);
}

void HsPrintHook(char const *message) // 0x10A48C20
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?HsPrintHook@@YAXPBD@Z");
	// `anonymous-namespace'::HsPrintHook
	// char const *message;

	if (!Utils::Singleton<Modules::ModuleScript>::Instance().VarPrintToConsole->ValueInt)
		return;

	if (!message)
		return;

	Console::WriteLine(message);
}

void sub_757890_call_hook(__int32 a1, __int32 a2) // 0x10A4C2F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?sub_757890_call_hook@@YAXHH@Z");
	// `anonymous-namespace'::sub_757890_call_hook
	// __int32 a2;
	// constexpr void (*const `sub_757890_call_hook'::`2'::sub_757890)(__int32, __int32); // constant == 7698576
	// function call : void (*const)(__int32, __int32)

	if (!Utils::Singleton<Modules::ModuleGraphics>::Instance().VarDisableContrails->ValueInt)
	{
		((void(__cdecl *)(__int32, __int32))0x757890)(a1, a2);
	}
}

long long main_time_get_absolute_milliseconds() // 0x10A4B3A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?main_time_get_absolute_milliseconds@@YA_JXZ");
	// `anonymous-namespace'::main_time_get_absolute_milliseconds
	// procedure flags: nofpo
	// long long ms;
	// long long last_milliseconds;
	// unsigned __int32 milliseconds;

	unsigned __int32 milliseconds = system_milliseconds();
	long long last_milliseconds = tls_getd().main_time_globals->last_milliseconds;
	long long ms = milliseconds | (last_milliseconds & 0xFFFFFFFF00000000);
	if (ms < last_milliseconds)
	{
		ms += 0x100000000;
	}

	#line 665 "C:\\Users\\Administrator\\Desktop\\eldewrito-ci\\ElDewritoCI.Blazor\\bin\\Debug\\net8.0\\staging\\ElDorito\\ElDorito\\Source\\Patches\\Core.cpp"
		assert(ms >= last_milliseconds);
		#line 675 "F:\\Project Hades\\Hades\\Source\\ElDorito\\Source\\Patches\\Core.cpp"
	return ms;
}

float main_time_update_hook() // 0x10A4B490
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?main_time_update_hook@@YAMXZ");
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
		// __int32 sleep_ms;
		// __int32 excess_ms;
			// unsigned long prev;
			// void *process_handle;
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

	float (*const main_time_update)() = (float (*)())0x508170;
	void (*const shell_idle)() = (void (*)())0x42E940;
	long long (*const rasterizer_get_vblank_index)() = (long long (*)())0xA25A80;
	bool const g_debug_disable_frame_rate_throttle = false;
	bool const g_main_time_is_throttled = true;
	LARGE_INTEGER cpu_tick;
	LARGE_INTEGER cpu_frequency;
	long long milliseconds;
	long long vblank_index;
	float delta_frame_time;
	float target_frame_time;
	long game_time = 0;
	bool in_game;
	__int32 frame_rate_limit = Utils::Singleton<Modules::ModuleGraphics>::Instance().VarFrameRateLimit->ValueInt;
	s_main_time_globals *g_main_time_globals = tls_getd().main_time_globals;
	milliseconds = main_time_get_absolute_milliseconds();
	vblank_index = rasterizer_get_vblank_index();
	QueryPerformanceFrequency(&cpu_frequency);
	bool skip_time_sync = true;
	if (frame_rate_limit)
	{
		if ((in_game = eldorado::game_in_progress()))
		{
			game_time = game_time_get();
			target_frame_time = 1.0f / frame_rate_limit;
		}
		else
		{
			game_time = 0;
			target_frame_time = 0.005f;
		}
		if (in_game && !g_debug_disable_frame_rate_throttle && g_main_time_is_throttled)
		{
			QueryPerformanceCounter(&cpu_tick);
			delta_frame_time = (float)((double)(cpu_tick.QuadPart - g_main_time_globals->last_cpu_ticks) / (double)cpu_frequency.QuadPart);
			__int32 excess_ms = (__int32)((target_frame_time - delta_frame_time) * 1000.0f);
			skip_time_sync = excess_ms <= 0;
			__int32 sleep_ms = (__int32)(target_frame_time * 1000.0f - 1.0f);
			if (excess_ms - 1 < sleep_ms)
				sleep_ms = excess_ms - 1;
			if (sleep_ms > 1)
			{
				void *process_handle = GetCurrentProcess();
				unsigned long prev = GetPriorityClass(process_handle);
				SetPriorityClass(process_handle, HIGH_PRIORITY_CLASS);
				SleepEx(sleep_ms, FALSE);
				SetPriorityClass(process_handle, Utils::Singleton<ElDorito>::Instance().IsHighPriority() ? HIGH_PRIORITY_CLASS : NORMAL_PRIORITY_CLASS);
			}
		}
	}
	do
	{
		QueryPerformanceCounter(&cpu_tick);
		milliseconds = main_time_get_absolute_milliseconds();
		delta_frame_time = (float)((double)(cpu_tick.QuadPart - g_main_time_globals->last_cpu_ticks) / (double)cpu_frequency.QuadPart);
		if (g_debug_disable_frame_rate_throttle)
			break;
	} while ((frame_rate_limit && target_frame_time > delta_frame_time) || (eldorado::game_in_progress() && delta_frame_time < 0.001f));
	if (!skip_time_sync)
		cpu_tick.QuadPart = g_main_time_globals->last_cpu_ticks + (long long)(target_frame_time * (double)cpu_frequency.QuadPart);
	delta_frame_time = fminf(fmaxf(delta_frame_time, 0.0f), 10.0f);
	g_main_time_globals->last_game_time = game_time;
	g_main_time_globals->last_milliseconds = milliseconds;
	g_main_time_globals->last_cpu_ticks = cpu_tick.QuadPart;
	g_main_time_globals->target_display_blank_index = vblank_index;
	g_main_time_globals->unknown_blank_index = vblank_index;
	return delta_frame_time;
}

long hs_seconds_to_ticks_hook(float seconds) // 0x10A4A9E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?hs_seconds_to_ticks_hook@@YAJM@Z");
	// `anonymous-namespace'::hs_seconds_to_ticks_hook
	// float seconds;
	// float ticks;

	float ticks = seconds * 30.0;
	if (ticks < 0.0)
	{
		return (long)(-0.5f + ticks);
	}
	else
	{
		return (long)(0.5f + ticks);
	}
}

unsigned __int32 system_milliseconds_hook() // 0x10A4C360
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?system_milliseconds_hook@@YAIXZ");
	// `anonymous-namespace'::system_milliseconds_hook
	// procedure flags: nofpo
	// static ...; // 0x10A4C3F0
	// static ...; // 0x10A4C3E4
	// static ...; // 0x10A4C3DC
	// _LARGE_INTEGER currentTime;
	// function call : __int32 (_LARGE_INTEGER *)

	LARGE_INTEGER currentTime;

	QueryPerformanceCounter(&currentTime);
	return (unsigned __int32)((currentTime.QuadPart - startTime.QuadPart) / cpuFrequencyMs);
}

void publish_waiting_gamestate() // 0x10A4BC80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?publish_waiting_gamestate@@YAXXZ");
	// `anonymous-namespace'::publish_waiting_gamestate
	// procedure flags: nofpo
	// void (*const main_render_purge_pending_messages)();
	// bool (*const multithreaded)();
	// void (*const main_time_mark_publishing_start_time)();
	// unsigned long (*const main_time_mark_publishing_end_time)();
	// bool (*const restricted_region_publish_to_mirror_blocking)(long);
	// long volatile &g_render_thread_enabled;
		// s_game_tick_time_samples *gamestate_timing;
	// function call : bool (*const)()
	// function call : void (*const)()
	// function call : bool (*const)(long)
	// function call : void (*const)()
	// function call : unsigned long (*const)()

	void (*const main_time_mark_publishing_start_time)() = reinterpret_cast<void (*)()>(0x5080B0);
	void (*const main_render_purge_pending_messages)() = reinterpret_cast<void (*)()>(0x604AA0);
	bool (*const multithreaded)() = reinterpret_cast<bool (*)()>(0x42E2C0);
	unsigned long (*const main_time_mark_publishing_end_time)() = reinterpret_cast<unsigned long (*)()>(0x508070);
	bool (*const restricted_region_publish_to_mirror_blocking)(long) = reinterpret_cast<bool (*)(long)>(0x5A0470);
	long volatile &g_render_thread_enabled = *reinterpret_cast<long volatile *>(0x22B46C8);
	if (multithreaded() && g_render_thread_enabled == 1)
	{
		main_time_mark_publishing_start_time();
		if (restricted_region_publish_to_mirror_blocking(3))
		{
			s_game_tick_time_samples *gamestate_timing = tls_getd().main_gamestate_timing;
			gamestate_timing->publishing_flags = 0;
			gamestate_timing->delta = 0.0f;
			gamestate_timing->game_delta = 0.0f;
			gamestate_timing->frame_delta = 0.0f;
			gamestate_timing->update_steps = 0;
			main_render_purge_pending_messages();
			main_time_mark_publishing_end_time();
		}
	}
}

void main_loop() // 0x10A4AD40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?main_loop@@YAXXZ");
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

	void (*const sub_5A05B0)(long) = (void (*)(long))0x5A05B0;
	void (*const main_game_unload_and_prepare_for_next_game)(void *) = (void (*)(void *))0x567F40;
	void (*const game_dispose)() = (void (*)())0x51D960;
	void (*const main_render_signal_shutdown)() = (void (*)())0x604AA0;
	void (*const c_rasterizer__rasterizer_device_release_thread)() = (void (*)())0xA222F0;
	void (*const main_loop_enter)() = (void (*)())0x506200;
	void (*const sub_5A03A0)(long) = (void (*)(long))0x5A03A0;
	__int32 (*const _internal_halt_render_thread_and_lock_resources)(char const *, __int32) = (__int32 (*)(char const *, __int32))0x504D20;
	char (*const screenshot_unknown)() = (char (*)())0x5547F0;
	void (__thiscall *const c_interlocked_long__set_bit)(long volatile *, char, char) = (void (__thiscall *)(long volatile *, char, char))0x52BD10;
	long (__thiscall *const c_interlocked_int32__set)(long volatile *, long) = (long (__thiscall *)(long volatile *, long))0x52BCB0;
	char (*const sub_6103F0)() = (char (*)())0x6103F0;
	void (*const main_loading_dispose)() = (void (*)())0x52F4E0;
	long (__thiscall *const c_synchronized_int32__set_if_equal)(long volatile *, long, long) = (long (__thiscall *)(long volatile *, long, long))0x52BDA0;
	void (*const physical_memory_resize_region_dispose)() = (void (*)())0x530CD0;
	void (*const game_sound_process_update_messages)() = (void (*)())0x5D9630;
	void (*const restricted_region_lock_primary)(long, long) = (void (*)(long, long))0x51CB70;
	void (*const main_render_purge_pending_messages)() = (void (*)())0x604AD0;
	void (*const main_loop_body_single_threaded)() = (void (*)())0x506080;
	void (*const process_game_engine_globals_messages)() = (void (*)())0x505C10;
	bool (*const multithreaded)() = (bool (*)())0x42E2C0;
	char (*const sub_610530)() = (char (*)())0x610530;
	long volatile &g_single_thread_request_flags = *(long volatile *)0x22B46C8;
	long volatile &dword_22B471C = *(long volatile *)0x22B471C;
	char &unk_22AE4F0 = *(char *)0x22AE4F0;
	bool &g_main_exit = *(bool *)0x22B473C;
	bool &unk_22AE4F2 = *(bool *)0x22AE4F2;
	unsigned long &dword_22B47B8 = *(unsigned long *)0x22B47B8;
	char v2;
	__int32 lock_result = 0;
	if (multithreaded())
	{
		unk_22AE4F0 = 1;
		_InterlockedExchange(&g_single_thread_request_flags, 1);
	}
	main_loop_enter();
	if (multithreaded())
	{
		sub_5A05B0(4);
		sub_5A05B0(2);
	}
	while (!g_main_exit)
	{
		v2 = 0;
		dword_22B47B8 = system_milliseconds();
		c_interlocked_long__set_bit(&dword_22B471C, 0, unk_22AE4F0 == 0);
		if (multithreaded() && (g_single_thread_request_flags == 1 || g_single_thread_request_flags == 2))
		{
			GameTickHook();
			game_sound_process_update_messages();
			process_game_engine_globals_messages();
			publish_waiting_gamestate();
		}
		else
		{
			v2 = 1;
			GameTickHook();
			game_sound_process_update_messages();
			main_loop_body_single_threaded();
		}
		bool a3 = false;
		if (sub_6103F0() || sub_610530())
			a3 = true;
		c_interlocked_long__set_bit(&dword_22B471C, 3, a3);
		if (multithreaded() && (dword_22B471C != 0) != v2)
		{
			if (v2)
			{
				if (multithreaded())
				{
					if (lock_result & 1)
					{
						c_rasterizer__rasterizer_device_release_thread();
						sub_5A05B0(4);
						sub_5A05B0(2);
					}
					if ((lock_result & 2) && multithreaded())
						c_synchronized_int32__set_if_equal(&g_single_thread_request_flags, 1, 0);
				}
			}
			else
			{
				lock_result = _internal_halt_render_thread_and_lock_resources("D:\\Projects\\eldorado_cert_ms23_code\\Halo3\\source\\main\\main.cpp", 1490);
			}
		}
	}
	if (multithreaded())
		_InterlockedCompareExchange(&g_single_thread_request_flags, 0, 1);
	if (multithreaded())
	{
		sub_5A03A0(2);
		sub_5A03A0(4);
	}
	if (multithreaded())
	{
		main_render_signal_shutdown();
		restricted_region_lock_primary(2, -1);
	}
	main_render_purge_pending_messages();
	main_game_unload_and_prepare_for_next_game(nullptr);
	game_dispose();
	physical_memory_resize_region_dispose();
	main_loading_dispose();
}

unsigned long render_thread_loop(void *lpParam) // 0x10A4BE90
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?render_thread_loop@@YAKPAX@Z");
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
		// unsigned long tag_resource_access_cookie;
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

	bool (*const restricted_region_mirror_locked_for_current_thread)(long) = reinterpret_cast<bool (*)(long)>(0x5A0410);
	void (*const font_idle)() = reinterpret_cast<void (*)()>(0x509390);
	__int32 (*const current_thread_update_test_functions)() = reinterpret_cast<__int32 (*)()>(0x51C390);
	void (*const c_rasterizer__cleanup_d3d_states)(char) = reinterpret_cast<void (*)(char)>(0xA1F890);
	void (*const tag_resources_unlock_render_gpu_usage)(unsigned long) = reinterpret_cast<void (*)(unsigned long)>(0x564100);
	unsigned long (*const tag_resources_lock_render)() = reinterpret_cast<unsigned long (*)()>(0x563FC0);
	long (__thiscall *const c_interlocked_int32__set)(long volatile *, long) = reinterpret_cast<long (__thiscall *)(long volatile *, long)>(0x52BCB0);
	bool (*const restricted_region_try_and_lock_primary)(long) = reinterpret_cast<bool (*)(long)>(0x5A0530);
	__int32 (*const restricted_region_unlock_mirror)(__int32) = reinterpret_cast<__int32 (*)(__int32)>(0x5A0570);
	bool (*const restricted_region_lock_mirror)(long) = reinterpret_cast<bool (*)(long)>(0x5A0360);
	bool (*const restricted_region_wait_for_available_mirror)(long, __int32) = reinterpret_cast<bool (*)(long, __int32)>(0x5A0660);
	void (*const restricted_region_unlock_primary)(long) = reinterpret_cast<void (*)(long)>(0x5A05B0);
	bool (*const current_thread_should_exit)() = reinterpret_cast<bool (*)()>(0x51C360);
	void (*const process_published_game_state)(char) = reinterpret_cast<void (*)(char)>(0x507450);
	bool (*const multithreaded)() = reinterpret_cast<bool (*)()>(0x42E2C0);
	long (*const c_rasterizer__rasterizer_device_acquire_thread)() = reinterpret_cast<long (*)()>(0xA222D0);
	void (*const c_rasterizer__rasterizer_device_release_thread)() = reinterpret_cast<void (*)()>(0xA222F0);
	unsigned long (*const tag_resources_unlock_render_access)() = reinterpret_cast<unsigned long (*)()>(0x5640E0);
	long volatile &g_single_thread_request_flags = *reinterpret_cast<long volatile *>(0x22B46C8);
	long volatile &g_render_thread_enabled = *reinterpret_cast<long volatile *>(0x22B471C);
	long volatile &g_render_thread_waiting = *reinterpret_cast<long volatile *>(0x22B456C);
	if (Utils::Singleton<ElDorito>::Instance().IsHeadless())
		return 1;
	if (multithreaded() && !current_thread_should_exit())
	{
		do
		{
			current_thread_update_test_functions();
			if (g_single_thread_request_flags == 1)
			{
				font_idle();
				c_interlocked_int32__set(&g_render_thread_waiting, 1);
				if (restricted_region_wait_for_available_mirror(3, 0x42) && restricted_region_try_and_lock_primary(2))
				{
					if (restricted_region_try_and_lock_primary(4))
					{
						if (g_single_thread_request_flags && !current_thread_should_exit() && restricted_region_lock_mirror(3))
						{
							c_interlocked_int32__set(&g_render_thread_waiting, 0);
							tag_resources_lock_render();
							c_rasterizer__rasterizer_device_acquire_thread();
							process_published_game_state(1);
							c_rasterizer__cleanup_d3d_states(0);
							unsigned long tag_resource_access_cookie = tag_resources_unlock_render_access();
							c_rasterizer__rasterizer_device_release_thread();
							tag_resources_unlock_render_gpu_usage(tag_resource_access_cookie);
							if (restricted_region_mirror_locked_for_current_thread(3))
								restricted_region_unlock_mirror(3);
						}
						restricted_region_unlock_primary(4);
					}
					restricted_region_unlock_primary(2);
				}
				c_interlocked_int32__set(&g_render_thread_waiting, 0);
			}
			else if (g_single_thread_request_flags == 2)
			{
				font_idle();
			}
		} while (!current_thread_should_exit());
	}
	return 1;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template void Pointer::Write<char const *>(char const *const) const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { _LARGE_INTEGER startTime; }

namespace hades_file_local { extern "C" { long long cpuFrequencyMs; } }
