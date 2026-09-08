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
		GameChatHandler(); /* compiler_generated() */
		virtual ~GameChatHandler(); /* compiler_generated() */
		GameChatHandler &operator=(GameChatHandler &); /* compiler_generated() */
		GameChatHandler &operator=(GameChatHandler const &); /* compiler_generated() */
	};
	static_assert(sizeof(GameChatHandler) == 4, "Invalid GameChatHandler size");
}
using namespace hades_file_local;
/* ---------- prototypes */

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

void OnGameInputUpdated();

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
			_extern void _sub_10C9C760();
			void Init() // 0x10C9C760
			{
				mangled_x86(MANGLED_TODO, "?Init@WebChat@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				todo("implement");
				_sub_10C9C760();
			}

			_extern void _sub_10C9D080(bool);
			void Show(bool teamChat) // 0x10C9D080
			{
				mangled_x86(MANGLED_TODO, "?Show@WebChat@Ui@Web@@YAX_N@Z");
				// static ...; // 0x10C9D20B
				// static ...; // 0x10C9D200
				// static ...; // 0x10C9D1E8
				// static ...; // 0x10C9D1E0
				// bool teamChat;
				// Blam::Network::Session *session;
				{
					// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
					// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
				}
				todo("implement");
				_sub_10C9D080(teamChat);
			}

			_extern void _sub_10C9C710();
			void Hide() // 0x10C9C710
			{
				mangled_x86(MANGLED_TODO, "?Hide@WebChat@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				todo("implement");
				_sub_10C9C710();
			}

			_extern void _sub_10C9D050(bool);
			void SetChatBoxVisible(bool visible) // 0x10C9D050
			{
				mangled_x86(MANGLED_TODO, "?SetChatBoxVisible@WebChat@Ui@Web@@YAX_N@Z");
				// bool visible;
				todo("implement");
				_sub_10C9D050(visible);
			}

			_extern bool _sub_10C9C860();
			bool IsChatBoxVisible() // 0x10C9C860
			{
				mangled_x86(MANGLED_TODO, "?IsChatBoxVisible@WebChat@Ui@Web@@YA_NXZ");
				// procedure flags: nofpo
				todo("implement");
				bool __result = _sub_10C9C860();
				return __result;
			}
		}
	}
}

namespace Server
{
	namespace Chat
	{
		// mangled_x86(MANGLED_DEFAULT, "??0ChatHandler@Chat@Server@@QAE@XZ"); no body to assert in
		_inline ChatHandler::ChatHandler() = default; // 0x10C9C400
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

_extern void _sub_10C9C880(GameChatHandler *const, Server::Chat::ChatMessage const &);
void GameChatHandler::MessageReceived(Server::Chat::ChatMessage const &message) // 0x10C9C880
{
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
	{
		// Blam::Network::PlayerSession player;
		// std::stringstream color;
		// char uid[17];
	}
	todo("implement");
	_sub_10C9C880(this, message);
}

// mangled_x86(MANGLED_DEFAULT, "??0GameChatHandler@hades_file_local@@QAE@XZ"); no body to assert in
_inline GameChatHandler::GameChatHandler() = default; // 0x10C9C430

_inline GameChatHandler::~GameChatHandler() // 0x10C9C570
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??1GameChatHandler@hades_file_local@@UAE@XZ");
	// `anonymous-namespace'::GameChatHandler::~GameChatHandler
	// GameChatHandler *const this;

	compiler_generated();
}

_extern void _sub_10C9CEA0();
void OnGameInputUpdated() // 0x10C9CEA0
{
	// `anonymous-namespace'::OnGameInputUpdated
	// procedure flags: nofpo
	// static ...; // 0x10C9CFEC
	// static ...; // 0x10C9CFE0
	// static ...; // 0x10C9CFD8
	// Blam::Input::BindingsTable bindings;
	// function call : bool (*const)()
	todo("implement");
	_sub_10C9CEA0();
}
