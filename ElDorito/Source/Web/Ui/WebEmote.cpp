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

			_extern void _sub_10CA4DD0();
			void Show() // 0x10CA4DD0
			{
				mangled_x86(MANGLED_TODO, "?Show@WebEmote@Ui@Web@@YAXXZ");
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
				{
					// __int32 i;
					{
						// s_mod_globals_player_character_customization *character;
					}
				}
				{
					// __int32 e;
					{
						// s_mod_player_action &emote;
						// char *animation_string;
					}
				}
				// function call : unsigned long (*const)(long)
				// function call : void *(*const)(unsigned long, long)
				// function call : __int32 (HWND__ *, tagRECT *)
				// function call : __int32 (HWND__ *, tagPOINT *)
				// function call : __int32 (__int32, __int32)
				todo("implement");
				_sub_10CA4DD0();
			}

			_extern void _sub_10CA5810();
			void Tick() // 0x10CA5810
			{
				mangled_x86(MANGLED_TODO, "?Tick@WebEmote@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				// static __int32 previousMapLoadingState; // 0x1247ED88
				// bool currentMapLoadingState;
				// function call : bool (*const)()
				// function call : bool (*const)()
				// function call : bool (*const)()
				todo("implement");
				_sub_10CA5810();
			}

			_extern void _sub_10CA4990();
			void Hide() // 0x10CA4990
			{
				mangled_x86(MANGLED_TODO, "?Hide@WebEmote@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				todo("implement");
				_sub_10CA4990();
			}
		}
	}
}

/* ---------- private code */

_extern void _sub_10CA4AB0();
void OnInput() // 0x10CA4AB0
{
	// `anonymous-namespace'::OnInput
	// procedure flags: nofpo
	// double threshold;
	// float leftx;
	// static __int32 `OnInput'::`2'::joystickMoveTicks; // 0x1247ED84
	// OnInput::__l2::ControllerAxes &controllerAxes;
	// bool isEmoting;
	// float lefty;
	{
		// long playerIndex;
		{
			// s_player_datum *player;
		}
	}
	// function call : unsigned long (*const)(long)
	// function call : unsigned long (*const)(long)
	// function call : unsigned long (*const)(long)
	todo("implement");
	_sub_10CA4AB0();
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_player_action_widget_data>::try_get_element(__int32, s_player_action_widget_data **) const;
template s_player_action_widget_data & c_tag_block<s_player_action_widget_data>::operator[](__int32);
template s_player_action_widget_data * c_tag_block<s_player_action_widget_data>::get_element(__int32) const;
template s_player_action_widget_data * c_tag_block<s_player_action_widget_data>::operator->();
