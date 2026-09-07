/* ---------- headers */

#include "Patches/LoadingScreen.hpp"
#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/CustomPackets.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <optional>
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

namespace Patches
{
	namespace LoadingScreen
	{
		class LoadingScreenUi;
		struct LoadingScreenShowInfo;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace LoadingScreen {}
	using namespace Patches::LoadingScreen;
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

namespace Patches
{
	namespace LoadingScreen
	{
		extern void ApplyAll();
		extern void SetUi(std::shared_ptr<Patches::LoadingScreen::LoadingScreenUi> ui);
	}
}

/* ---------- globals */

namespace Patches
{
	namespace LoadingScreen
	{
		extern bool firstRun; // 0x113545A0
	}
}

/* ---------- private variables */

namespace
{
	extern std::shared_ptr<Patches::LoadingScreen::LoadingScreenUi> ActiveUi; // 0x12458CF8
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const kCampaignSkullNames[16]; // 0x12458B38
}
/* ---------- public code */

namespace Patches
{
	namespace LoadingScreen
	{
		_extern void _sub_10A82A90();
		void ApplyAll() // 0x10A82A90
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@LoadingScreen@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10A82A90();
		}

		_extern void _sub_10A840A0(std::shared_ptr<Patches::LoadingScreen::LoadingScreenUi>);
		void SetUi(std::shared_ptr<Patches::LoadingScreen::LoadingScreenUi> ui) // 0x10A840A0
		{
			mangled_x86(MANGLED_TODO, "?SetUi@LoadingScreen@Patches@@YAXV?$shared_ptr@VLoadingScreenUi@LoadingScreen@Patches@@@std@@@Z");
			// std::shared_ptr<Patches::LoadingScreen::LoadingScreenUi> ui;
			todo("implement");
			_sub_10A840A0(ui);
		}

		_extern void _sub_10A827C0(Patches::LoadingScreen::LoadingScreenShowInfo *const);
		_inline LoadingScreenShowInfo::~LoadingScreenShowInfo() // 0x10A827C0
		{
			mangled_x86(MANGLED_TODO, "??1LoadingScreenShowInfo@LoadingScreen@Patches@@QAE@XZ");
			// Patches::LoadingScreen::LoadingScreenShowInfo *const this;
			compiler_generated();
			todo("implement");
			_sub_10A827C0(this);
		}
	}
}

/* ---------- private code */
