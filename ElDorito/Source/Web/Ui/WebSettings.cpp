/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamInput.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/input/input.hpp"
#include "Blam/interface/user_interface_sound.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Patch.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "Utils/Singleton.hpp"
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

namespace Web
{
	namespace Ui
	{
		class WebScreen;
	}
}
namespace hades_file_local
{
	class WebSettingsScreen;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
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
		namespace WebSettings {}
		using namespace Web::Ui::WebSettings;
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

namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	class WebSettingsScreen :
		public Web::Ui::WebScreen
	{
	public:
		WebSettingsScreen(WebSettingsScreen &); /* compiler_generated() */
		WebSettingsScreen(WebSettingsScreen const &); /* compiler_generated() */
		WebSettingsScreen(); /* compiler_generated() */
		WebSettingsScreen &operator=(WebSettingsScreen &); /* compiler_generated() */
		WebSettingsScreen &operator=(WebSettingsScreen const &); /* compiler_generated() */
	};
	static_assert(sizeof(WebSettingsScreen) == 4, "Invalid WebSettingsScreen size");
}
using namespace hades_file_local;
typedef bool (*CommandUpdateFunc)(std::vector<std::string> const &, std::string &);
namespace Patches
{
	namespace Input
	{
		typedef void (*DefaultInputHandler)();
	}
}

/* ---------- prototypes */

namespace Web
{
	namespace Ui
	{
		namespace WebSettings
		{
			extern void Init();
			extern void Show();
		}
	}
}

void OnGameInputUpdated();

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Web
{
	namespace Ui
	{
		namespace WebSettings
		{
			_extern void _sub_10CB52B0();
			void Init() // 0x10CB52B0
			{
				mangled_x86(MANGLED_TODO, "?Init@WebSettings@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				todo("implement");
				_sub_10CB52B0();
			}

			void Show() // 0x10CB57D0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?Show@WebSettings@Ui@Web@@YAXXZ");
				// procedure flags: nofpo

				ScreenLayer::Show(ScreenLayer::ScreenId::Settings, "{}");
			}
		}
	}
}

/* ---------- private code */

_extern void _sub_10CB53C0();
void OnGameInputUpdated() // 0x10CB53C0
{
	// `anonymous-namespace'::OnGameInputUpdated
	// procedure flags: nofpo
	// function call : long (*const)(e_user_interface_sound, long)
	// function call : bool (*const)()
	// function call : long (*const)(e_user_interface_sound, long)
	todo("implement");
	_sub_10CB53C0();
}

// mangled_x86(MANGLED_DEFAULT, "??0WebSettingsScreen@hades_file_local@@QAE@XZ"); no body to assert in
_inline WebSettingsScreen::WebSettingsScreen() = default; // 0x10CB5130
