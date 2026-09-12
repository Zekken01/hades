/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/input/input.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "ElDorito.hpp"
#include "Forge/Geoemetry.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/CustomPackets.hpp"
#include "Patches/GamePatches.hpp"
#include "Patches/LoadingScreen.hpp"
#include "Patches/Network.hpp"
#include "Patches/Ui.hpp"
#include "Pointer.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

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

namespace Blam
{
	namespace Input
	{
		class VirtualKeyboard;
	}
}

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
	namespace ScreenEffects {}
	using namespace Patches::ScreenEffects;
	namespace Devices {}
	using namespace Patches::Devices;
	namespace Hf2pExperimental {}
	using namespace Patches::Hf2pExperimental;
	namespace Chud {}
	using namespace Patches::Chud;
	namespace Sprint {}
	using namespace Patches::Sprint;
	namespace Weapon {}
	using namespace Patches::Weapon;
	namespace Simulation {}
	using namespace Patches::Simulation;
	namespace PlayerUid {}
	using namespace Patches::PlayerUid;
	namespace HavokMemory {}
	using namespace Patches::HavokMemory;
	namespace RawInput {}
	using namespace Patches::RawInput;
	namespace Player {}
	using namespace Patches::Player;
	namespace Vehicle {}
	using namespace Patches::Vehicle;
	namespace Unit {}
	using namespace Patches::Unit;
	namespace GameEngine {}
	using namespace Patches::GameEngine;
	namespace Animation {}
	using namespace Patches::Animation;
	namespace geometry_sampler_patches {}
	using namespace Patches::geometry_sampler_patches;
	namespace Vision {}
	using namespace Patches::Vision;
	namespace Objects {}
	using namespace Patches::Objects;
	namespace MouseSupport {}
	using namespace Patches::MouseSupport;
	namespace DamageSystem {}
	using namespace Patches::DamageSystem;
	namespace Mopp {}
	using namespace Patches::Mopp;
	namespace Scoreboard {}
	using namespace Patches::Scoreboard;
	namespace Assassination {}
	using namespace Patches::Assassination;
	namespace DeterminismDebug {}
	using namespace Patches::DeterminismDebug;
	namespace Forge {}
	using namespace Patches::Forge;
	namespace Biped {}
	using namespace Patches::Biped;
	namespace GameEngineSettings {}
	using namespace Patches::GameEngineSettings;
	namespace Camera {}
	using namespace Patches::Camera;
	namespace Events {}
	using namespace Patches::Events;
	namespace MenuBlur {}
	using namespace Patches::MenuBlur;
	namespace Reach {}
	using namespace Patches::Reach;
	namespace PlayerScale {}
	using namespace Patches::PlayerScale;
	namespace Ui {}
	using namespace Patches::Ui;
	namespace campaign_patches {}
	using namespace Patches::campaign_patches;
	namespace Logging {}
	using namespace Patches::Logging;
	namespace Tweaks {}
	using namespace Patches::Tweaks;
	namespace Shell {}
	using namespace Patches::Shell;
	namespace Memory {}
	using namespace Patches::Memory;
	namespace CustomPackets {}
	using namespace Patches::CustomPackets;
	namespace Core {}
	using namespace Patches::Core;
	namespace PregameLobby {}
	using namespace Patches::PregameLobby;
	namespace Medals {}
	using namespace Patches::Medals;
	namespace Input {}
	using namespace Patches::Input;
	namespace Game {}
	using namespace Patches::Game;
	namespace HaloScript {}
	using namespace Patches::HaloScript;
	namespace FirstPerson {}
	using namespace Patches::FirstPerson;
	namespace BreakableSurface {}
	using namespace Patches::BreakableSurface;
	namespace Spectate {}
	using namespace Patches::Spectate;
	namespace Debug {}
	using namespace Patches::Debug;
	namespace RenderObject {}
	using namespace Patches::RenderObject;
	namespace SimulationWeapon {}
	using namespace Patches::SimulationWeapon;
	namespace Audio {}
	using namespace Patches::Audio;
	namespace ModSync {}
	using namespace Patches::ModSync;
	namespace VirtualKeyboard {}
	using namespace Patches::VirtualKeyboard;
	namespace LoadingScreen {}
	using namespace Patches::LoadingScreen;
	namespace Bitmaps {}
	using namespace Patches::Bitmaps;
	namespace Maps {}
	using namespace Patches::Maps;
	namespace Mouse {}
	using namespace Patches::Mouse;
	namespace PlayerControl {}
	using namespace Patches::PlayerControl;
	namespace Projectiles {}
	using namespace Patches::Projectiles;
	namespace MotorSystem {}
	using namespace Patches::MotorSystem;
	namespace MapBarriers {}
	using namespace Patches::MapBarriers;
	namespace ContentItems {}
	using namespace Patches::ContentItems;
	namespace Equipment {}
	using namespace Patches::Equipment;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Patches
{
	extern void ApplyRequired();
	extern void ApplyAfterInit();
	extern void ApplyOnFirstTick();
	extern void ApplyAfterTagsLoaded();
	extern void Tick();
}

void UnprotectMemory();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	_extern void _sub_10968240();
	void ApplyRequired() // 0x10968240
	{
		mangled_x86(MANGLED_TODO, "?ApplyRequired@Patches@@YAXXZ");
		// procedure flags: nofpo
		// static ...; // 0x109684D8
		// static ...; // 0x109684D4
		// static ...; // 0x109684BC
		// static ...; // 0x109684B4
		// bool isdedicated;
		// wchar_t **szArgList;
		// __int32 numArgs;
		{
			// __int32 i;
			{
				// std::wstring arg;
			}
		}
		// function call : wchar_t *()
		// function call : wchar_t **(wchar_t const *, __int32 *)
		todo("implement");
		_sub_10968240();
	}

	_extern void _sub_10968120();
	void ApplyAfterInit() // 0x10968120
	{
		mangled_x86(MANGLED_TODO, "?ApplyAfterInit@Patches@@YAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_10968120();
	}

	void ApplyOnFirstTick() // 0x10968220
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyOnFirstTick@Patches@@YAXXZ");
		// procedure flags: nofpo
	}

	_extern void _sub_109681B0();
	void ApplyAfterTagsLoaded() // 0x109681B0
	{
		mangled_x86(MANGLED_TODO, "?ApplyAfterTagsLoaded@Patches@@YAXXZ");
		// procedure flags: nofpo
		todo("implement");
		_sub_109681B0();
	}

	_extern void _sub_10968600();
	void Tick() // 0x10968600
	{
		mangled_x86(MANGLED_TODO, "?Tick@Patches@@YAXXZ");
		// procedure flags: nofpo
		// static bool appliedFirstTickPatches; // 0x1240FB50
		todo("implement");
		_sub_10968600();
	}
}

/* ---------- private code */

void UnprotectMemory() // 0x109686B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UnprotectMemory@@YAXXZ");
	// `anonymous-namespace'::UnprotectMemory
	// procedure flags: nofpo
	// static ...; // 0x1096876C
	// static ...; // 0x10968760
	// static ...; // 0x10968758
	// unsigned __int32 Total;
	// _MEMORY_BASIC_INFORMATION MemInfo;
	// unsigned __int32 Offset;
	// function call : unsigned long (void const *, _MEMORY_BASIC_INFORMATION *, unsigned long)
	// function call : __int32 (void *, unsigned long, unsigned long, unsigned long *)

	// Enable write to all executable memory
	size_t Offset, Total;
	Offset = Total = 0;
	MEMORY_BASIC_INFORMATION MemInfo;

	//printf("\nUnprotecting memory...");
	while (VirtualQuery((uint8_t*)GetBasePointer() + Offset, &MemInfo, sizeof(MEMORY_BASIC_INFORMATION)))
	{
		Offset += MemInfo.RegionSize;
		if (MemInfo.Protect == PAGE_EXECUTE_READ)
		{
			//printf("%0X\n", (size_t)((uint8_t*)GetBasePointer() + Offset));
			Total += MemInfo.RegionSize;
			VirtualProtect(MemInfo.BaseAddress, MemInfo.RegionSize, PAGE_EXECUTE_READWRITE, &MemInfo.Protect);
		}
	}
	//printf("\nDone! Unprotected %u bytes of memory\n", Total);
}
