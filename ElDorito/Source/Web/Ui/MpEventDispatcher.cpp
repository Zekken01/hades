/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/game/engine/game_engine_events.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Patches/Events.hpp"
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
#include "Utils/NameValueTable.hpp"
#include "Utils/StlUtil.hpp"
#include "Web/Bridge/WebRendererQueryHandler.hpp"
#include "Web/Ui/Screen.hpp"

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
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <list>
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
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct s_game_engine_event_data;
struct s_multiplayer_event_response_definition;

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
		namespace MpEventDispatcher {}
		using namespace Web::Ui::MpEventDispatcher;
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
	namespace Events {}
	using namespace Patches::Events;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Web
{
	namespace Ui
	{
		namespace MpEventDispatcher
		{
			extern void Init();
		}
	}
}

void OnEvent(unsigned long player, s_game_engine_event_data const *event, s_multiplayer_event_response_definition const *definition);
std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetEventName(unsigned __int32 stringId);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern std::unordered_map<unsigned int,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::hash<unsigned int>,std::equal_to<unsigned int>,std::allocator<std::pair<unsigned int const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > EventNames; // 0x1247ECA0
}
using namespace hades_file_local;
/* ---------- public code */

namespace Web
{
	namespace Ui
	{
		namespace MpEventDispatcher
		{
			_extern void _sub_10C8A6A0();
			void Init() // 0x10C8A6A0
			{
				mangled_x86(MANGLED_TODO, "?Init@MpEventDispatcher@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				todo("implement");
				_sub_10C8A6A0();
			}
		}
	}
}

/* ---------- private code */

_extern void _sub_10C8A700(unsigned long, s_game_engine_event_data const *, s_multiplayer_event_response_definition const *);
void OnEvent(unsigned long player, s_game_engine_event_data const *event, s_multiplayer_event_response_definition const *definition) // 0x10C8A700
{
	// `anonymous-namespace'::OnEvent
	// static ...; // 0x10C8A91C
	// static ...; // 0x10C8A8F8
	// static ...; // 0x10C8A8F0
	// unsigned long player;
	// s_game_engine_event_data const *event;
	// s_multiplayer_event_response_definition const *definition;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > eventName;
	// unsigned __int32 (*GetLocalPlayer)(__int32);
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
	// function call : unsigned __int32 (*)(__int32)
	todo("implement");
	_sub_10C8A700(player, event, definition);
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10C8A3E0(unsigned __int32);
std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetEventName(unsigned __int32 stringId) // 0x10C8A3E0
{
	// `anonymous-namespace'::GetEventName
	// static ...; // 0x10C8A60E
	// static ...; // 0x10C8A60B
	// static ...; // 0x10C8A608
	// static ...; // 0x10C8A5E4
	// static ...; // 0x10C8A5DC
	// unsigned __int32 stringId;
	// std::_List_iterator<std::_List_val<std::_List_simple_types<std::pair<unsigned int const ,std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > > > it;
	// std::basic_ostringstream<char,std::char_traits<char>,std::allocator<char> > ss;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > name;
	todo("implement");
	std::string __result = _sub_10C8A3E0(stringId);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_enum<enum e_game_engine_event_audience,short>::operator short() const;
template c_enum<enum e_game_engine_event_type,char>::operator char() const;
