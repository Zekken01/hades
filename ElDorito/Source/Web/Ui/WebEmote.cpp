/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/input/input.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/mods/mod_globals.hpp"
#include "Blam/mods/player_action_set.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/ModGlobals.hpp"
#include "mods/new/IModManager.hpp"
#include "Modules/ModuleServer.hpp"
#include "Patch.hpp"
#include "Player/PlayerEmotes.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/encodings.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/dtoa.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/itoa.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/stack.h"
#include "ThirdParty/rapidjson/internal/strfunc.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Singleton.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/ScreenLayer.hpp"

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
#include <mutex>
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

struct s_game_globals;
struct s_mod_globals_definition;
struct s_mod_globals_player_character_customization;
struct s_mod_player_action;
struct s_mod_player_actions_set_definition;
struct s_player_datum;
namespace Modules
{
	class ModuleServer;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Ui {}
	using namespace Web::Ui;
}

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer {}
		using namespace Web::Ui::ScreenLayer;
		namespace WebEmote {}
		using namespace Web::Ui::WebEmote;
	}
}

namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge {}
		using namespace Web::Browser::Bridge;
	}
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Camera {}
	using namespace Patches::Camera;
	namespace Input {}
	using namespace Patches::Input;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const player_mapping_get_player_by_input_user = reinterpret_cast<unsigned long (*)(long)>(0x589C30);
}

#include "Blam/camera/camera.hpp"  // hades: added for 0x10CA4AB0
#include "mods/mod_system.hpp"  // hades: added for 0x10CA4DD0
namespace Patches { namespace Camera { extern e_camera_mode GetForcedCameraMode(); } }  // hades: added for 0x10CA4AB0

extern bool (*const game_is_multiplayer)();  // hades: added for 0x10CA5810

namespace Patches { namespace Input { extern void RegisterDefaultInputHandler(void (*func)()); } }  // hades: added for 0x10CA4A60

namespace Web
{
	namespace Ui
	{
		namespace WebEmote
		{
			extern void Init();
			extern void Show();
			extern void Tick();
			extern void Hide();
		}
	}
}

void OnInput();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Web
{
	namespace Ui
	{
		namespace WebEmote
		{
			void Init() // 0x10CA4A60
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Init@WebEmote@Ui@Web@@YAXXZ");
				// procedure flags: nofpo

				Patches::Input::RegisterDefaultInputHandler(OnInput);
			}

			void Show() // 0x10CA4DD0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Show@WebEmote@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				// static ...; // 0x10CA55F1
				// static ...; // 0x10CA55E9
				// static ...; // 0x10CA55DE
				// static ...; // 0x10CA55D3
				// static ...; // 0x10CA55CE
				// static ...; // 0x10CA55CC
				// static ...; // 0x10CA5584
				// static ...; // 0x10CA557C
				// s_player_datum *player;
				// std::string modHash;
				// bool enabled;
				// s_game_globals const *matg;
				// tagRECT rect;
				// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
				// unsigned long playerIndex;
				// s_mod_globals_definition const *modg;
				// tagPOINT p;
				// s_mod_player_actions_set_definition *const emoteTag;
				// short characterTypeIndex;
				// __int32 definitionIndex;
				// HWND__ *hWnd;
				// Modules::ModuleServer &serverModule;
				// __int32 player_character_customization_index;
				// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
					// __int32 i;
						// s_mod_globals_player_character_customization *character;
					// __int32 e;
						// s_mod_player_action &emote;
						// char *animation_string;
				// function call : unsigned long (*const)(long)
				// function call : void *(*const)(unsigned long, long)
				// function call : __int32 (HWND__ *, tagRECT *)
				// function call : __int32 (HWND__ *, tagPOINT *)
				// function call : __int32 (__int32, __int32)

				Modules::ModuleServer &serverModule = Modules::ModuleServer::Instance();
				bool enabled = serverModule.VarServerEmotesEnabledClient->ValueInt != 0;
				if (!enabled)
					return;
				unsigned long playerIndex = eldorado::player_mapping_get_player_by_input_user(0);
				short characterTypeIndex = -1;
				s_player_datum *player = player_get(playerIndex);
				if (player->unit_index != -1)
					characterTypeIndex = player->character_type_index;
				else
					return;
				s_game_globals const *matg = game_globals_get();
				s_mod_globals_definition const *modg = mod_globals_get_definition();
				__int32 player_character_customization_index = -1;
				for (__int32 i = 0; i < modg->player_character_customizations.count; i++)
				{
					s_mod_globals_player_character_customization *character = nullptr;
					if (!modg->player_character_customizations.try_get_element(i, &character))
						continue;
					if (!character || character->global_player_character_type_index >= matg->player_character_types.count)
						continue;
					if (!matg->player_character_types[character->global_player_character_type_index].name)
						continue;
					if (characterTypeIndex == character->global_player_character_type_index)
					{
						player_character_customization_index = i;
						break;
					}
				}
				if (player_character_customization_index == -1)
					return;
				if (modg->player_character_customizations[player_character_customization_index].action_set.index == -1)
					return;
				__int32 definitionIndex = modg->player_character_customizations[player_character_customization_index].action_set.index;
				s_mod_player_actions_set_definition *const emoteTag = (s_mod_player_actions_set_definition *)tag_get('pact', definitionIndex);
				std::string modHash = c_mod_system::get_current_mainmenu_package_hash();
				if (!emoteTag || !emoteTag->actions.count || !emoteTag->widget.count)
					return;
				rapidjson::StringBuffer jsonBuffer;
				rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
				jsonWriter.StartObject();
				jsonWriter.Key("tagIndex");
				jsonWriter.Int(definitionIndex);
				jsonWriter.Key("modHash");
				jsonWriter.String(modHash.c_str());
				jsonWriter.Key("widgetType");
				jsonWriter.Int(emoteTag->widget[0].type);
				jsonWriter.Key("style");
				jsonWriter.StartObject();
				jsonWriter.Key("backgroundColor");
				jsonWriter.Int(emoteTag->widget->background_color);
				jsonWriter.Key("borderColor");
				jsonWriter.Int(emoteTag->widget->border_color);
				jsonWriter.Key("highlightColor");
				jsonWriter.Int(emoteTag->widget->highlight_color);
				jsonWriter.Key("textColor");
				jsonWriter.Int(emoteTag->widget->text_color);
				jsonWriter.EndObject();
				jsonWriter.Key("emotes");
				jsonWriter.StartArray();
				for (__int32 e = 0; e < emoteTag->actions.count; e++)
				{
					s_mod_player_action &emote = emoteTag->actions[e];
					char *animation_string = Blam::Cache::StringIDCache::GetCurrent()->GetString(emote.animation_enter);
					jsonWriter.StartObject();
					jsonWriter.Key("title");
					jsonWriter.String(emote.title.ascii);
					jsonWriter.Key("iconName");
					jsonWriter.String(emote.icon_name.ascii);
					jsonWriter.Key("emoteIndex");
					jsonWriter.Int(e);
					jsonWriter.Key("animationName");
					jsonWriter.String(animation_string ? animation_string : "");
					jsonWriter.EndObject();
				}
				jsonWriter.EndArray();
				jsonWriter.EndObject();
				HWND hWnd = Pointer::Base(0x159C014).Read<HWND>();
				if (!hWnd)
					return;
				RECT rect;
				GetClientRect(hWnd, &rect);
				POINT p;
				p.x = (rect.right - rect.left) / 2;
				p.y = (rect.bottom - rect.top) / 2;
				ClientToScreen(hWnd, &p);
				SetCursorPos(p.x, p.y);
				Web::Ui::ScreenLayer::Show("emote", jsonBuffer.GetString());
			}

			void Tick() // 0x10CA5810
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Tick@WebEmote@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				// static __int32 previousMapLoadingState; // 0x1247ED88
				// bool currentMapLoadingState;
				// function call : bool (*const)()
				// function call : bool (*const)()
				// function call : bool (*const)()

				static __int32 previousMapLoadingState = 0;

				if (!game_is_multiplayer() && !((bool(__cdecl *)())0x531E90)())
				{
					return;
				}

				bool currentMapLoadingState = *(bool *)0x23917F0;
				if (previousMapLoadingState && !currentMapLoadingState && ((bool(__cdecl *)())0x531E90)())
				{
					Hide();
				}

				previousMapLoadingState = currentMapLoadingState;
			}

			void Hide() // 0x10CA4990
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Hide@WebEmote@Ui@Web@@YAXXZ");
				// procedure flags: nofpo

				ScreenLayer::Hide("emote");
			}
		}
	}
}

/* ---------- private code */

void OnInput() // 0x10CA4AB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnInput@@YAXXZ");
	// `anonymous-namespace'::OnInput
	// procedure flags: nofpo
	// double threshold;
	// float leftx;
	// static __int32 `OnInput'::`2'::joystickMoveTicks; // 0x1247ED84
	// OnInput::__l2::ControllerAxes &controllerAxes;
	// bool isEmoting;
	// float lefty;
		// long playerIndex;
			// s_player_datum *player;
	// function call : unsigned long (*const)(long)
	// function call : unsigned long (*const)(long)
	// function call : unsigned long (*const)(long)

	struct ControllerAxes
	{
		short LeftX;
		short LeftY;
	};
	ControllerAxes &controllerAxes = *reinterpret_cast<ControllerAxes *>(0x244D4E4);
	float leftx = abs(controllerAxes.LeftX / 32768.0f);
	float lefty = abs(controllerAxes.LeftY / 32768.0f);
	double threshold = 0.5;
	static __int32 joystickMoveTicks = 0;
	bool isEmoting = Player::CPlayerEmotes::PlayerIsEmoting(reinterpret_cast<long (*)(long)>(0x589C30)(0));
	if (isEmoting)
	{
		if (!(leftx >= threshold) && !(lefty >= threshold))
			joystickMoveTicks++;
	}
	else
		joystickMoveTicks = 0;
	if (isEmoting && (Blam::Input::GetActionState(Blam::Input::eGameActionJump)->Ticks == 1 || Blam::Input::GetActionState(Blam::Input::eGameActionMoveForward)->Ticks == 1 || Blam::Input::GetActionState(Blam::Input::eGameActionMoveBack)->Ticks == 1 || Blam::Input::GetActionState(Blam::Input::eGameActionMoveLeft)->Ticks == 1 || Blam::Input::GetActionState(Blam::Input::eGameActionMoveRight)->Ticks == 1 || Blam::Input::GetActionState(Blam::Input::eGameActionMelee)->Ticks == 1 || Blam::Input::GetActionState(Blam::Input::eGameActionFireLeft)->Ticks == 1 || Blam::Input::GetActionState(Blam::Input::eGameActionFireRight)->Ticks == 1 || leftx >= threshold && joystickMoveTicks >= 1 || lefty >= threshold && joystickMoveTicks >= 1))
	{
		long playerIndex = reinterpret_cast<long (*)(long)>(0x589C30)(0);
		if (playerIndex != -1)
		{
			s_player_datum *player = player_get(playerIndex);
			if (Player::CPlayerEmotes::UnitMovementInhibited(player->unit_index) && Patches::Camera::GetForcedCameraMode() != _camera_mode_flying)
				Player::CPlayerEmotes::RequestStopEmote();
		}
	}
	if (Blam::Input::GetActionState(Blam::Input::eGameActionEmote)->Ticks == 1)
	{
		Blam::Input::GetActionState(Blam::Input::eGameActionEmote)->Flags |= Blam::Input::eActionStateFlagsHandled;
		if (Player::CPlayerEmotes::PlayerIsEmoting(reinterpret_cast<long (*)(long)>(0x589C30)(0)))
			Player::CPlayerEmotes::RequestStopEmote();
		else
			Web::Ui::WebEmote::Show();
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_player_action_widget_data>::try_get_element(__int32, s_player_action_widget_data **) const;
template s_player_action_widget_data & c_tag_block<s_player_action_widget_data>::operator[](__int32);
template s_player_action_widget_data * c_tag_block<s_player_action_widget_data>::get_element(__int32) const;
template s_player_action_widget_data * c_tag_block<s_player_action_widget_data>::operator->();
