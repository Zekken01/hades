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
#include "Blam/main/levels.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/font_package.hpp"
#include "mods/map_variant_loader.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "Modules/ModuleServer.hpp"
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

class c_mod_package_manager;
struct c_game_engine_base_variant;
struct s_game_options;
struct s_level_datum;
struct s_level_insertion_datum;
struct s_map_variant;
namespace Modules
{
	class ModuleServer;
}
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

bool ShowLoadingScreenHook(s_game_options &options);
void BeginLoadingHook(unsigned __int32 totalBytes);
void UpdateLoadingProgressHook(unsigned __int32 bytes);
void HideLoadingScreenHook();
std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > GetActiveSkullsForDisplay(unsigned long primarySkulls, unsigned long secondarySkulls);
std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > GetActiveSkullsForDisplay();
std::basic_string<char,std::char_traits<char>,std::allocator<char> > camapgin_difficulty_level_to_string(long level);
bool BuildLoadingScreenShowInfo(s_game_options &gameOptions, Patches::LoadingScreen::LoadingScreenShowInfo &outInfo);

/* ---------- globals */

namespace Patches
{
	namespace LoadingScreen
	{
		extern bool firstRun; // 0x113545A0
	}
}

/* ---------- private variables */

namespace hades_file_local
{
	extern std::shared_ptr<Patches::LoadingScreen::LoadingScreenUi> ActiveUi; // 0x12458CF8
	extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > const kCampaignSkullNames[16]; // 0x12458B38
}
using namespace hades_file_local;
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

_extern bool _sub_10A84100(s_game_options &);
bool ShowLoadingScreenHook(s_game_options &options) // 0x10A84100
{
	// `anonymous-namespace'::ShowLoadingScreenHook
	// static ...; // 0x10A84498
	// static ...; // 0x10A8448C
	// static ...; // 0x10A84484
	// s_game_options &options;
	{
		// bool HasIntroBinks;
	}
	{
		// Patches::LoadingScreen::LoadingScreenShowInfo info;
	}
	// function call : bool (*)(s_game_options &)
	// function call : void (Patches::LoadingScreen::LoadingScreenShowInfo const &)
	// function call : bool (*)(s_game_options &)
	todo("implement");
	bool __result = _sub_10A84100(options);
	return __result;
}

_extern void _sub_10A82EA0(unsigned __int32);
void BeginLoadingHook(unsigned __int32 totalBytes) // 0x10A82EA0
{
	// `anonymous-namespace'::BeginLoadingHook
	// unsigned __int32 totalBytes;
	// function call : void (unsigned __int32)
	todo("implement");
	_sub_10A82EA0(totalBytes);
}

_extern void _sub_10A84590(unsigned __int32);
void UpdateLoadingProgressHook(unsigned __int32 bytes) // 0x10A84590
{
	// `anonymous-namespace'::UpdateLoadingProgressHook
	// unsigned __int32 bytes;
	// function call : void (unsigned __int32)
	todo("implement");
	_sub_10A84590(bytes);
}

_extern void _sub_10A84000();
void HideLoadingScreenHook() // 0x10A84000
{
	// `anonymous-namespace'::HideLoadingScreenHook
	// procedure flags: nofpo
	// void (*HideLoadingScreen)();
	// function call : void (*)()
	// function call : void ()
	todo("implement");
	_sub_10A84000();
}

extern std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > _sub_10A83D50(unsigned long, unsigned long);
std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > GetActiveSkullsForDisplay(unsigned long primarySkulls, unsigned long secondarySkulls) // 0x10A83D50
{
	// `anonymous-namespace'::GetActiveSkullsForDisplay
	// static ...; // 0x10A83E6C
	// static ...; // 0x10A83E64
	// unsigned long primarySkulls;
	// unsigned long secondarySkulls;
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > skulls;
	{
		// __int32 i;
	}
	todo("implement");
	std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > __result = _sub_10A83D50(primarySkulls, secondarySkulls);
	return __result;
}

extern std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > _sub_10A83ED0();
std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > GetActiveSkullsForDisplay() // 0x10A83ED0
{
	// `anonymous-namespace'::GetActiveSkullsForDisplay
	// procedure flags: nofpo
	// static ...; // 0x10A83FAC
	// static ...; // 0x10A83F9C
	// static ...; // 0x10A83F84
	// static ...; // 0x10A83F7C
	// unsigned long secondarySkulls;
	// unsigned long primarySkulls;
	// function call : unsigned long *(*const)(unsigned long *)
	// function call : unsigned long *(*const)(unsigned long *)
	todo("implement");
	std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > __result = _sub_10A83ED0();
	return __result;
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10A84770(long);
std::basic_string<char,std::char_traits<char>,std::allocator<char> > camapgin_difficulty_level_to_string(long level) // 0x10A84770
{
	// `anonymous-namespace'::camapgin_difficulty_level_to_string
	// static ...; // 0x10A84874
// $LN7:
// $LN6:
// $LN5:
// $LN4:
	// long level;
	todo("implement");
	std::string __result = _sub_10A84770(level);
	return __result;
}

_extern bool _sub_10A82F40(s_game_options &, Patches::LoadingScreen::LoadingScreenShowInfo &);
bool BuildLoadingScreenShowInfo(s_game_options &gameOptions, Patches::LoadingScreen::LoadingScreenShowInfo &outInfo) // 0x10A82F40
{
	// `anonymous-namespace'::BuildLoadingScreenShowInfo
	// static ...; // 0x10A83A52
	// static ...; // 0x10A83A46
	// static ...; // 0x10A83A40
	// static ...; // 0x10A83A3A
	// static ...; // 0x10A83A30
	// static ...; // 0x10A839F4
	// static ...; // 0x10A839EC
// $LN13:
// $LN12:
// $LN11:
// $LN10:
// $LN9:
// $LN8:
// $LN7:
	// s_game_options &gameOptions;
	// Patches::LoadingScreen::LoadingScreenShowInfo &outInfo;
	// bool hasModSet;
	// Modules::ModuleServer const &moduleServer;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > modhash;
	// c_mod_package_manager::s_entry mod_package;
	{
		// char *rawGameVariant;
		// s_map_variant const &mapVariant;
		// s_level_datum level;
		// c_game_engine_base_variant *gameVariant;
	}
	{
		// s_level_insertion_datum insertion;
	}
	// function call : bool (*const)(long, s_level_datum *)
	// function call : bool (*const)(long, s_level_datum *)
	// function call : bool (*const)(long, s_level_insertion_datum *)
	// function call : long (*const)()
	todo("implement");
	bool __result = _sub_10A82F40(gameOptions, outInfo);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template c_enum<enum e_game_engine_type,long>::operator long() const;
template c_enum<enum e_game_mode,long>::operator long() const;
