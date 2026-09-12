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
#include "Patches/Network.hpp"
#include "Server/Voting/VotingPackets.hpp"
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
#include <limits>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

class VotingOutputHandler;
namespace Blam
{
	namespace Input
	{
		struct ActionState;
	}
}
namespace Server
{
	namespace Voting
	{
		class VotingMessageHandler;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace Voting {}
	using namespace Server::Voting;
}

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
	namespace Input {}
	using namespace Patches::Input;
}

namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

// VotingOutputHandler is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

namespace Patches
{
	namespace Input
	{
		typedef void (*MenuUIInputHandler)();
	}
}

/* ---------- prototypes */

namespace Web
{
	namespace Ui
	{
		namespace Voting
		{
			extern void Init();
			extern void Show();
			extern void Hide();
			extern void VotingEnded();
		}
	}
}

void LifeCycleStateChanged(Blam::Network::LifeCycleState newState);
void OnUiInputUpdate();
void OnVotingEnded();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern bool currentlyVoting; // 0x1247ED51
	extern bool temporarilyHidden; // 0x1247ED52
}
using namespace hades_file_local;
/* ---------- public code */

extern VotingOutputHandler* _sub_10C9A6B0(VotingOutputHandler *const);
_inline VotingOutputHandler::VotingOutputHandler() // 0x10C9A6B0
{
	mangled_x86(MANGLED_TODO, "??0VotingOutputHandler@@QAE@XZ");
	// VotingOutputHandler *const this;
	todo("implement");
	_sub_10C9A6B0(this);
}

_inline VotingOutputHandler::~VotingOutputHandler() // 0x10C9A7F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1VotingOutputHandler@@UAE@XZ");
	// VotingOutputHandler *const this;

	compiler_generated();
}

namespace Server
{
	namespace Voting
	{
		// mangled_x86(MANGLED_DEFAULT, "??0VotingMessageHandler@Voting@Server@@QAE@XZ"); no body to assert in
		_inline VotingMessageHandler::VotingMessageHandler() = default; // 0x10C9A680
	}
}

namespace Web
{
	namespace Ui
	{
		namespace Voting
		{
			_extern void _sub_10C9A9E0();
			void Init() // 0x10C9A9E0
			{
				mangled_x86(MANGLED_TODO, "?Init@Voting@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				todo("implement");
				_sub_10C9A9E0();
			}

			_extern void _sub_10C9BB40();
			void Show() // 0x10C9BB40
			{
				mangled_x86(MANGLED_TODO, "?Show@Voting@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				todo("implement");
				_sub_10C9BB40();
			}

			void Hide() // 0x10C9A990
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Hide@Voting@Ui@Web@@YAXXZ");
				// procedure flags: nofpo

				ScreenLayer::Hide(ScreenLayer::Voting);
			}

			void VotingEnded() // 0x10C9BC10
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?VotingEnded@Voting@Ui@Web@@YAXXZ");
				// procedure flags: nofpo

				currentlyVoting = false;
			}
		}
	}
}

/* ---------- private code */

void LifeCycleStateChanged(Blam::Network::LifeCycleState newState) // 0x10C9AB00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?LifeCycleStateChanged@@YAXW4LifeCycleState@Network@Blam@@@Z");
	// `anonymous-namespace'::LifeCycleStateChanged
	// Blam::Network::LifeCycleState newState;

	switch (newState)
	{
	case Blam::Network::eLifeCycleStateNone:
	case Blam::Network::eLifeCycleStateStartGame:
	case Blam::Network::eLifeCycleStateLeaving:
		OnVotingEnded();
		break;
	}
}

_extern void _sub_10C9B850();
void OnUiInputUpdate() // 0x10C9B850
{
	// `anonymous-namespace'::OnUiInputUpdate
	// procedure flags: nofpo
	// unsigned char *(*const c_gui_screen_manager__get_first)(void *, unsigned __int32, __int32);
	{
		// Blam::Input::ActionState *action;
		// unsigned char *widget;
		// unsigned char *screenManager;
		{
			// unsigned __int32 name;
		}
	}
	// function call : unsigned char *(*const)(void *, unsigned __int32, __int32)
	todo("implement");
	_sub_10C9B850();
}

void OnVotingEnded() // 0x10C9BA30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnVotingEnded@@YAXXZ");
	// `anonymous-namespace'::OnVotingEnded
	// procedure flags: nofpo

	currentlyVoting = false;
	Web::Ui::ScreenLayer::Notify("VoteEnded", "{}", true);
	Web::Ui::Voting::Hide();
}
