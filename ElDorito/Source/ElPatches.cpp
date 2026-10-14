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

namespace Patches { namespace Hf2pExperimental { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Core { extern void ApplyAll(); } }  // hades: added for 0x10968240
extern void visibility_patches_apply();  // hades: added for 0x10968240
extern void effect_system_patches_apply();  // hades: added for 0x10968240
namespace Patches { namespace Audio { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Memory { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Mouse { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Network { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Scoreboard { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Shell { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Ui { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Chud { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace VirtualKeyboard { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace RawInput { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace ContentItems { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace PlayerUid { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace PlayerScale { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Input { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Forge { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace CustomPackets { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Logging { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Events { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace LoadingScreen { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Equipment { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Weapon { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Spectate { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Medals { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Simulation { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace SimulationWeapon { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Camera { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Maps { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace GameEngineSettings { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace DamageSystem { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace ModSync { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace FirstPerson { extern void ApplyAll(); } }  // hades: added for 0x10968240
extern void network_session_parameter_patches_apply();  // hades: added for 0x10968240
extern void player_model_patches_apply();  // hades: added for 0x10968240
extern void player_character_type_patches_apply();  // hades: added for 0x10968240
extern void forge_material_patches_apply();  // hades: added for 0x10968240
namespace Patches { namespace Mopp { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Animation { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Sprint { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace geometry_sampler_patches { extern void ApplyAll(); } }  // hades: added for 0x10968240
extern void render_patches_apply();  // hades: added for 0x10968240
extern void render_postprocess_patches_apply();  // hades: added for 0x10968240
extern void physics_patches_apply();  // hades: added for 0x10968240
namespace Patches { namespace campaign_patches { extern void ApplyAll(); } }  // hades: added for 0x10968240
extern void game_state_patches_apply();  // hades: added for 0x10968240
extern void saved_game_patches_apply();  // hades: added for 0x10968240
extern void life_cycle_patches_apply();  // hades: added for 0x10968240
extern void game_time_patches_apply();  // hades: added for 0x10968240
extern void font_patches_apply();  // hades: added for 0x10968240
namespace Patches { namespace PregameLobby { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Game { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Devices { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Debug { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace DeterminismDebug { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace HavokMemory { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace MouseSupport { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace MenuBlur { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Vision { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace PlayerControl { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace RenderObject { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Objects { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Player { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace ScreenEffects { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace HaloScript { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace GameEngine { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace MotorSystem { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Biped { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace MapBarriers { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Projectiles { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Unit { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Assassination { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace BreakableSurface { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Vehicle { extern void ApplyAll(); } }  // hades: added for 0x10968240
namespace Patches { namespace Bitmaps { extern void ApplyAll(); } }  // hades: added for 0x10968240
extern void widget_patches_apply();  // hades: added for 0x10968240
namespace DirectXHook { extern void ApplyAll(); }  // hades: added for 0x10968240

namespace Patches { namespace Sprint { void Tick(); } namespace Forge { void Tick(); } namespace PlayerScale { void Tick(); } namespace ModSync { void Tick(); } namespace Mopp { void Tick(); } namespace MenuBlur { void Tick(); } namespace PregameLobby { void Tick(); } namespace Debug { void Tick(); } namespace FirstPerson { void Tick(); } }  // hades: added for 0x10968600
void render_postprocess_patches_tick();  // hades: added for 0x10968600
void effect_system_patches_tick();  // hades: added for 0x10968600
void render_patches_tick();  // hades: added for 0x10968600

namespace Patches { namespace Core { extern void ApplyAfterInit(); } namespace Memory { extern void ApplyAfterInit(); } namespace Audio { extern void ApplyAfterInit(); } namespace Network { extern void ForceDedicated(); extern void ForceBotClient(); } namespace Reach { extern void ApplyAfterInit(); } }  // hades: added for 0x10968120

extern void RefreshUiPlayer();  // hades: added for 0x109681B0
namespace Patches { namespace Ui { extern void ApplyAfterTagsLoaded(); extern void ApplyUIResolution(); } namespace Weapon { extern void ApplyAfterTagsLoaded(); } namespace Tweaks { extern void ApplyAfterTagsLoaded(); } namespace Camera { extern void ApplyAfterTagsLoaded(); } namespace Forge { extern void ApplyAfterTagsLoaded(); } }  // hades: added for 0x109681B0

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
	void ApplyRequired() // 0x10968240
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyRequired@Patches@@YAXXZ");
		// procedure flags: nofpo
		// static ...; // 0x109684D8
		// static ...; // 0x109684D4
		// static ...; // 0x109684BC
		// static ...; // 0x109684B4
		// bool isdedicated;
		// wchar_t **szArgList;
		// __int32 numArgs;
			// __int32 i;
				// std::wstring arg;
		// function call : wchar_t *()
		// function call : wchar_t **(wchar_t const *, __int32 *)

		UnprotectMemory();
		Hf2pExperimental::ApplyAll();
		Core::ApplyAll();
		visibility_patches_apply();
		effect_system_patches_apply();
		Audio::ApplyAll();
		Memory::ApplyAll();
		Mouse::ApplyAll();
		Network::ApplyAll();
		Scoreboard::ApplyAll();
		Shell::ApplyAll();
		Ui::ApplyAll();
		Chud::ApplyAll();
		VirtualKeyboard::ApplyAll();
		RawInput::ApplyAll();
		ContentItems::ApplyAll();
		PlayerUid::ApplyAll();
		PlayerScale::ApplyAll();
		Input::ApplyAll();
		Forge::ApplyAll();
		CustomPackets::ApplyAll();
		Logging::ApplyAll();
		Events::ApplyAll();
		LoadingScreen::ApplyAll();
		Equipment::ApplyAll();
		Weapon::ApplyAll();
		Spectate::ApplyAll();
		Medals::ApplyAll();
		Simulation::ApplyAll();
		SimulationWeapon::ApplyAll();
		Camera::ApplyAll();
		Maps::ApplyAll();
		GameEngineSettings::ApplyAll();
		DamageSystem::ApplyAll();
		ModSync::ApplyAll();
		FirstPerson::ApplyAll();
		network_session_parameter_patches_apply();
		player_model_patches_apply();
		player_character_type_patches_apply();
		forge_material_patches_apply();
		Mopp::ApplyAll();
		Animation::ApplyAll();
		Sprint::ApplyAll();
		geometry_sampler_patches::ApplyAll();
		render_patches_apply();
		render_postprocess_patches_apply();
		physics_patches_apply();
		campaign_patches::ApplyAll();
		game_state_patches_apply();
		saved_game_patches_apply();
		life_cycle_patches_apply();
		game_time_patches_apply();
		font_patches_apply();
		PregameLobby::ApplyAll();
		Game::ApplyAll();
		Devices::ApplyAll();
		Debug::ApplyAll();
		DeterminismDebug::ApplyAll();
		HavokMemory::ApplyAll();
		MouseSupport::ApplyAll();
		MenuBlur::ApplyAll();
		Vision::ApplyAll();
		PlayerControl::ApplyAll();
		RenderObject::ApplyAll();
		Objects::ApplyAll();
		Player::ApplyAll();
		ScreenEffects::ApplyAll();
		HaloScript::ApplyAll();
		GameEngine::ApplyAll();
		MotorSystem::ApplyAll();
		Biped::ApplyAll();
		MapBarriers::ApplyAll();
		Projectiles::ApplyAll();
		Unit::ApplyAll();
		Assassination::ApplyAll();
		BreakableSurface::ApplyAll();
		Vehicle::ApplyAll();
		Bitmaps::ApplyAll();
		widget_patches_apply();
		bool isdedicated = false;
		__int32 numArgs = 0;
		wchar_t **szArgList = CommandLineToArgvW(GetCommandLineW(), &numArgs);
		for (__int32 i = 1; i < numArgs; i++)
		{
			std::wstring arg = std::wstring(szArgList[i]);
			if (arg.compare(L"-headless") == 0 || arg.compare(L"-dedicated") == 0)
				isdedicated = true;
		}
		::DirectXHook::ApplyAll();
	}

	void ApplyAfterInit() // 0x10968120
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAfterInit@Patches@@YAXXZ");
		// procedure flags: nofpo

		Core::ApplyAfterInit();
		Memory::ApplyAfterInit();
		Audio::ApplyAfterInit();
		if (Utils::Singleton<ElDorito>::Instance().IsDedicated())
		{
			Network::ForceDedicated();
		}
		else if (Utils::Singleton<ElDorito>::Instance().IsBotClient())
		{
			Network::ForceBotClient();
		}

		Reach::ApplyAfterInit();
	}

	void ApplyOnFirstTick() // 0x10968220
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyOnFirstTick@Patches@@YAXXZ");
		// procedure flags: nofpo
	}

	void ApplyAfterTagsLoaded() // 0x109681B0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAfterTagsLoaded@Patches@@YAXXZ");
		// procedure flags: nofpo

		RefreshUiPlayer();
		Ui::ApplyAfterTagsLoaded();
		Ui::ApplyUIResolution();
		Weapon::ApplyAfterTagsLoaded();
		Tweaks::ApplyAfterTagsLoaded();
		Camera::ApplyAfterTagsLoaded();
		Forge::ApplyAfterTagsLoaded();
	}

	void Tick() // 0x10968600
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@Patches@@YAXXZ");
		// procedure flags: nofpo
		// static bool appliedFirstTickPatches; // 0x1240FB50

		static bool appliedFirstTickPatches = false;

		Audio::Tick();
		Sprint::Tick();
		Forge::Tick();
		PlayerScale::Tick();
		ModSync::Tick();
		Mopp::Tick();
		render_postprocess_patches_tick();
		effect_system_patches_tick();
		MenuBlur::Tick();
		PregameLobby::Tick();
		Debug::Tick();
		Network::Tick();
		render_patches_tick();
		FirstPerson::Tick();

		if (appliedFirstTickPatches)
		{
			return;
		}

		ApplyOnFirstTick();
		appliedFirstTickPatches = true;
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
