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
#include "Modules/ModuleInput.hpp"
#include "Server/ServerChat.hpp"
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
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"
#include "Web/Ui/ScreenLayer.hpp"
#include "Web/Ui/WebMods.hpp"

#include "Patches/Input.hpp"  // hades: added for 0x10C9C760

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
#include <iomanip>
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

/* ---------- forward declarations */

namespace Blam
{
	namespace Input
	{
		struct BindingsTable;
	}
}
namespace Blam
{
	namespace Network
	{
		struct PlayerSession;
		struct Session;
	}
}
namespace Server
{
	namespace Chat
	{
		class ChatHandler;
		struct ChatMessage;
	}
}
namespace hades_file_local
{
	class GameChatHandler;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace Chat {}
	using namespace Server::Chat;
}

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
		namespace WebChat {}
		using namespace Web::Ui::WebChat;
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
namespace Blam
{
	namespace Input {}
	using namespace Blam::Input;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	class GameChatHandler :
		public Server::Chat::ChatHandler
	{
	public:
		virtual void MessageSent(__int32, Server::Chat::ChatMessage *, bool *);
		virtual void MessageReceived(Server::Chat::ChatMessage const &);
		GameChatHandler(GameChatHandler &); /* compiler_generated() */
		GameChatHandler(GameChatHandler const &); /* compiler_generated() */
		GameChatHandler() = default; /* compiler_generated() */  // hades: not user-provided, so make_shared value-initializes
		virtual ~GameChatHandler() = default; /* compiler_generated() */
		GameChatHandler &operator=(GameChatHandler &); /* compiler_generated() */
		GameChatHandler &operator=(GameChatHandler const &); /* compiler_generated() */
	};
	static_assert(sizeof(GameChatHandler) == 4, "Invalid GameChatHandler size");
}
using namespace hades_file_local;
/* ---------- prototypes */

#include "Player/PlayerCustomization.hpp"  // hades: added for 0x10C9C880
extern void player_format_uid(char *string, unsigned long long id);  // hades: added for 0x10C9C880

extern bool (*const game_engine_is_sandbox)();  // hades: added for 0x10C9CEA0

namespace Web
{
	namespace Ui
	{
		namespace WebChat
		{
			extern void Init();
			extern void Show(bool teamChat);
			extern void Hide();
			extern void SetChatBoxVisible(bool visible);
			extern bool IsChatBoxVisible();
		}
	}
}

static void OnGameInputUpdated();

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern bool isChatBoxVisible; // 0x1247ED53
}
using namespace hades_file_local;
/* ---------- public code */

namespace Web
{
	namespace Ui
	{
		namespace WebChat
		{
			void Init() // 0x10C9C760
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Init@WebChat@Ui@Web@@YAXXZ");
				// procedure flags: nofpo

				Server::Chat::AddHandler(std::make_shared<GameChatHandler>());
				Patches::Input::RegisterDefaultInputHandler(OnGameInputUpdated);
			}

			void Show(bool teamChat) // 0x10C9D080
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Show@WebChat@Ui@Web@@YAX_N@Z");
				// static ...; // 0x10C9D20B
				// static ...; // 0x10C9D200
				// static ...; // 0x10C9D1E8
				// static ...; // 0x10C9D1E0
				// bool teamChat;
				// Blam::Network::Session *session;
					// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
					// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;

				Blam::Network::Session *session = Blam::Network::GetActiveSession();
				if (session && session->IsEstablished())
				{
					rapidjson::StringBuffer jsonBuffer;
					rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
					jsonWriter.StartObject();
					jsonWriter.Key("teamChat");
					jsonWriter.Bool(teamChat);
					jsonWriter.Key("captureInput");
					jsonWriter.Bool(true);
					jsonWriter.EndObject();
					Web::Ui::ScreenLayer::Show(Web::Ui::ScreenLayer::Chat, jsonBuffer.GetString());
				}
			}

			void Hide() // 0x10C9C710
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Hide@WebChat@Ui@Web@@YAXXZ");
				// procedure flags: nofpo

				ScreenLayer::Hide(ScreenLayer::Chat);
			}

			void SetChatBoxVisible(bool visible) // 0x10C9D050
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?SetChatBoxVisible@WebChat@Ui@Web@@YAX_N@Z");
				// bool visible;

				isChatBoxVisible = visible;
			}

			bool IsChatBoxVisible() // 0x10C9C860
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?IsChatBoxVisible@WebChat@Ui@Web@@YA_NXZ");
				// procedure flags: nofpo

				return isChatBoxVisible;
			}
		}
	}
}

namespace Server
{
	namespace Chat
	{
		// mangled_x86(MANGLED_DEFAULT, "??0ChatHandler@Chat@Server@@QAE@XZ"); no body to assert in
	}
}

/* ---------- private code */

void GameChatHandler::MessageSent(__int32 senderPeer, Server::Chat::ChatMessage *message, bool *ignore) // 0x10C9CE80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?MessageSent@GameChatHandler@hades_file_local@@UAEXHPAUChatMessage@Chat@Server@@PA_N@Z");
	// the original is empty
	// `anonymous-namespace'::GameChatHandler::MessageSent
	// bool *ignore;
}

void GameChatHandler::MessageReceived(Server::Chat::ChatMessage const &message) // 0x10C9C880
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?MessageReceived@GameChatHandler@hades_file_local@@UAEXABUChatMessage@Chat@Server@@@Z");
	// `anonymous-namespace'::GameChatHandler::MessageReceived
	// static ...; // 0x10C9CD30
	// static ...; // 0x10C9CD25
	// static ...; // 0x10C9CD1E
	// static ...; // 0x10C9CD1A
	// static ...; // 0x10C9CD14
	// static ...; // 0x10C9CCD8
	// static ...; // 0x10C9CCD0
// $LN8:
// $LN7:
// $LN6:
// $LN5:
	// GameChatHandler *const this;
	// Server::Chat::ChatMessage const &message;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
	// char const *chatType;
	// Blam::Network::Session *session;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
		// Blam::Network::PlayerSession player;
		// std::stringstream color;
		// char uid[17];

	Blam::Network::Session *session = Blam::Network::GetActiveSession();
	if (!session)
		return;
	rapidjson::StringBuffer jsonBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
	jsonWriter.StartObject();
	jsonWriter.Key("message");
	jsonWriter.String(std::string(message.Body).c_str());
	jsonWriter.Key("sender");
	jsonWriter.String(Server::Chat::GetSenderName(message).c_str());
	char const *chatType;
	switch (message.Type)
	{
	case Server::Chat::ChatMessageType::Global:
		chatType = "GLOBAL";
		break;
	case Server::Chat::ChatMessageType::Team:
		chatType = "TEAM";
		break;
	case Server::Chat::ChatMessageType::Whisper:
		chatType = "WHISPER";
		break;
	case Server::Chat::ChatMessageType::Server:
		chatType = "SERVER";
		break;
	default:
		chatType = "UNKNOWN";
		break;
	}
	jsonWriter.Key("chatType");
	jsonWriter.String(chatType);
	if (message.Type != Server::Chat::ChatMessageType::Server)
	{
		Blam::Network::PlayerSession player = session->MembershipInfo.PlayerSessions[message.SenderPlayer];
		jsonWriter.Key("teamIndex");
		jsonWriter.Int(player.Properties.host.team);
		char uid[17];
		player_format_uid(uid, player.Properties.host.player_uid);
		jsonWriter.Key("UID");
		jsonWriter.String(uid);
		std::stringstream color;
		color << "#" << std::setw(6) << std::setfill('0') << std::hex << Player::CPlayerCustomization::GetPlayerPrimaryColor(message.SenderPlayer);
		jsonWriter.Key("color");
		jsonWriter.String(color.str().c_str());
		jsonWriter.Key("hasTeams");
		jsonWriter.Bool(session->HasTeams());
	}
	jsonWriter.EndObject();
	Web::Ui::ScreenLayer::NotifyScreen(Web::Ui::ScreenLayer::Chat, "chat", jsonBuffer.GetString());
}

// mangled_x86(MANGLED_DEFAULT, "??0GameChatHandler@hades_file_local@@QAE@XZ"); no body to assert in
// _inline GameChatHandler::GameChatHandler() = default; // 0x10C9C430  // hades: defaulted on its declaration


static void OnGameInputUpdated() // 0x10C9CEA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?OnGameInputUpdated@@YAXXZ");
	// `anonymous-namespace'::OnGameInputUpdated
	// procedure flags: nofpo
	// static ...; // 0x10C9CFEC
	// static ...; // 0x10C9CFE0
	// static ...; // 0x10C9CFD8
	// Blam::Input::BindingsTable bindings;
	// function call : bool (*const)()

	Blam::Input::BindingsTable bindings;
	Blam::Input::GetBindings(0, &bindings);
	if (game_engine_is_sandbox() && Blam::Input::GetKeyTicks(Blam::Input::eKeyCodeCtrl, Blam::Input::eInputTypeGame) > 0)
		return;

	if (Blam::Input::GetKeyTicks(bindings.PrimaryKeys[Blam::Input::eGameActionTeamChat], Blam::Input::eInputTypeUi) == 1 || Blam::Input::GetKeyTicks(bindings.SecondaryKeys[Blam::Input::eGameActionTeamChat], Blam::Input::eInputTypeUi) == 1)
		Web::Ui::WebChat::Show(true);
	if (Blam::Input::GetKeyTicks(bindings.PrimaryKeys[Blam::Input::eGameActionGeneralChat], Blam::Input::eInputTypeUi) == 1 || Blam::Input::GetKeyTicks(bindings.SecondaryKeys[Blam::Input::eGameActionGeneralChat], Blam::Input::eInputTypeUi) == 1)
		Web::Ui::WebChat::Show(false);
}
