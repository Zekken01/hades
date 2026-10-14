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

#include "Patches/Input.hpp"  // hades: added for 0x10C9A9E0

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

// hades: moved from hades/recovered_types.h onto its real base (was hades::polymorphic_bytes)
struct VotingOutputHandler :
	public Server::Voting::VotingMessageHandler
{
	// mangled_x86(MANGLED_KNOWN_GOOD, "??1VotingOutputHandler@@UAE@XZ"); defaulted on its declaration, which skips the vfptr store
	virtual ~VotingOutputHandler() = default; // 0x10C9A7F0
	virtual void MessageReceived(Server::Voting::VotingMessage const &);
public:
	VotingOutputHandler();
};
static_assert32(sizeof(VotingOutputHandler) == 4, "Invalid VotingOutputHandler size");

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

_inline VotingOutputHandler::VotingOutputHandler() // 0x10C9A6B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0VotingOutputHandler@@QAE@XZ");
	// VotingOutputHandler *const this;
}

namespace Server
{
	namespace Voting
	{
		// mangled_x86(MANGLED_DEFAULT, "??0VotingMessageHandler@Voting@Server@@QAE@XZ"); no body to assert in
	}
}

namespace Web
{
	namespace Ui
	{
		namespace Voting
		{
			void Init() // 0x10C9A9E0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Init@Voting@Ui@Web@@YAXXZ");
				// procedure flags: nofpo

				Server::Voting::AddMessageHandler(std::make_shared<VotingOutputHandler>());
				Patches::Network::OnLifeCycleStateChanged(LifeCycleStateChanged);
				Patches::Input::RegisterMenuUIInputHandler(OnUiInputUpdate);
			}

			void Show() // 0x10C9BB40
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Show@Voting@Ui@Web@@YAXXZ");
				// procedure flags: nofpo

				ScreenLayer::Show(ScreenLayer::ScreenId::Voting, "{}");
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

void OnUiInputUpdate() // 0x10C9B850
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnUiInputUpdate@@YAXXZ");
	// `anonymous-namespace'::OnUiInputUpdate
	// procedure flags: nofpo
	// unsigned char *(*const c_gui_screen_manager__get_first)(void *, unsigned __int32, __int32);
		// Blam::Input::ActionState *action;
		// unsigned char *widget;
		// unsigned char *screenManager;
			// unsigned __int32 name;
	// function call : unsigned char *(*const)(void *, unsigned __int32, __int32)

	unsigned char *(__thiscall *const c_gui_screen_manager__get_first)(void *, unsigned __int32, __int32) = reinterpret_cast<unsigned char *(__thiscall *)(void *, unsigned __int32, __int32)>(0xAAB320);
	if (currentlyVoting)
	{
		Blam::Input::ActionState *action = Blam::Input::GetActionState(Blam::Input::eGameActionUiY);
		if (!(action->Flags & Blam::Input::eActionStateFlagsHandled) && action->Ticks == 1)
		{
			action->Ticks |= Blam::Input::eActionStateFlagsHandled;
			Web::Ui::ScreenLayer::Show(Web::Ui::ScreenLayer::Voting, "{ userInvoked: true }");
		}
		unsigned char *screenManager = (unsigned char *)0x5260F34;
		unsigned char *widget = c_gui_screen_manager__get_first(screenManager, 0, 0);
		if (widget)
		{
			unsigned __int32 name = *(unsigned __int32 *)(widget + 0x40);
			if (name == 0x100B3)
			{
				if (temporarilyHidden)
				{
					temporarilyHidden = false;
					Web::Ui::ScreenLayer::Show(Web::Ui::ScreenLayer::Voting, {});
				}
			}
			else
			{
				Web::Ui::Voting::Hide();
				temporarilyHidden = true;
			}
		}
	}
}

void OnVotingEnded() // 0x10C9BA30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnVotingEnded@@YAXXZ");
	// `anonymous-namespace'::OnVotingEnded
	// procedure flags: nofpo

	currentlyVoting = false;
	Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::Voting, "VoteEnded", "{}");
	Web::Ui::Voting::Hide();
}

void VotingOutputHandler::MessageReceived(Server::Voting::VotingMessage const &message) // 0x10C9AB70
{

	if (message.Type == Server::Voting::VotingOptions)
	{
		rapidjson::StringBuffer jsonBuffer;
		rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
		jsonWriter.StartObject();
		jsonWriter.Key("timeRemaining");
		jsonWriter.Int(message.voteTime);
		jsonWriter.Key("votingOptions");
		jsonWriter.StartArray();
		for (int i = 0; i < 6; i++)
		{
			jsonWriter.StartObject();
			jsonWriter.Key("index");
			jsonWriter.Int(i + 1);
			jsonWriter.Key("scnrname");
			jsonWriter.String(message.votingOptions[i].scnrName);
			jsonWriter.Key("mapname");
			jsonWriter.String(message.votingOptions[i].mapName);
			jsonWriter.Key("typename");
			jsonWriter.String(message.votingOptions[i].typeName);
			jsonWriter.Key("modname");
			jsonWriter.String(message.votingOptions[i].modName);
			jsonWriter.Key("modhash");
			jsonWriter.String(message.votingOptions[i].modHash);
			jsonWriter.Key("image");
			jsonWriter.String(message.votingOptions[i].imageUri);
			jsonWriter.EndObject();
		}
		jsonWriter.EndArray();
		jsonWriter.EndObject();
		Web::Ui::Voting::Show();
		Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::Voting, "VotingOptionsUpdated", jsonBuffer.GetString());
		currentlyVoting = true;
	}
	else if (message.Type == Server::Voting::VetoOption)
	{
		rapidjson::StringBuffer jsonBuffer;
		rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
		jsonWriter.StartObject();
		jsonWriter.Key("timeRemaining");
		jsonWriter.Int(message.voteTime);
		jsonWriter.Key("votesNeededToPass");
		jsonWriter.Int(message.votesNeededToPass);
		jsonWriter.Key("vetoOption");
		jsonWriter.StartObject();
		jsonWriter.Key("scnrname");
		jsonWriter.String(message.votingOptions[0].scnrName);
		jsonWriter.Key("mapname");
		jsonWriter.String(message.votingOptions[0].mapName);
		jsonWriter.Key("typename");
		jsonWriter.String(message.votingOptions[0].typeName);
		jsonWriter.Key("modname");
		jsonWriter.String(message.votingOptions[0].modName);
		jsonWriter.Key("modhash");
		jsonWriter.String(message.votingOptions[0].modHash);
		jsonWriter.Key("canveto");
		jsonWriter.Bool(message.votingOptions[0].canVeto);
		jsonWriter.Key("image");
		jsonWriter.String(message.votingOptions[0].imageUri);
		jsonWriter.EndObject();
		jsonWriter.EndObject();
		Web::Ui::Voting::Show();
		Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::Voting, "VetoOptionsUpdated", jsonBuffer.GetString());
		currentlyVoting = true;
	}
	else if (message.Type == Server::Voting::Winner)
	{
		rapidjson::StringBuffer jsonBuffer;
		rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
		jsonWriter.StartObject();
		jsonWriter.Key("Winner");
		jsonWriter.Int(message.winner);
		jsonWriter.EndObject();
		Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::Voting, "Winner", jsonBuffer.GetString());
	}
	else if (message.Type == Server::Voting::VoteTimerUpdated)
	{
		rapidjson::StringBuffer jsonBuffer;
		rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
		jsonWriter.StartObject();
		jsonWriter.Key("timeUntilGameStart");
		jsonWriter.Int(message.voteTime);
		jsonWriter.Key("shouldUpdateTimer");
		jsonWriter.Bool(message.shouldUpdateTimer);
		jsonWriter.EndObject();
		Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::Voting, "VoteTimerUpdated", jsonBuffer.GetString());
	}
	else if (message.Type == Server::Voting::VoteTally)
	{
		rapidjson::StringBuffer jsonBuffer;
		rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
		jsonWriter.StartObject();
		jsonWriter.Key("votesNeededToPass");
		jsonWriter.Int(message.votesNeededToPass);
		jsonWriter.Key("voteCounts");
		jsonWriter.StartArray();
		for (int i = 0; i < 6; i++)
		{
			jsonWriter.StartObject();
			jsonWriter.Key("OptionIndex");
			jsonWriter.Int(i + 1);
			jsonWriter.Key("Count");
			jsonWriter.Int(message.votes[i]);
			jsonWriter.EndObject();
		}
		jsonWriter.EndArray();
		jsonWriter.EndObject();
		Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::Voting, "VoteCountsUpdated", jsonBuffer.GetString());
	}
	else if (message.Type == Server::Voting::VoteEnded)
	{
		OnVotingEnded();
	}
}

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { bool currentlyVoting; }
namespace hades_file_local { bool temporarilyHidden; }
