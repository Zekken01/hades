/* ---------- headers */

#include "Modules/ModulePlayer.hpp"
#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/cache_files.hpp"
#include "Blam/camera/observer.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_globals.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/multiplayer_definitions.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/player_control.hpp"
#include "Blam/game/player_model_customization.hpp"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/mods/mod_globals.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/havok_types.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/scenario/scenario.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Common/Http/HttpRequest.hpp"
#include "ElDorito.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_definitions.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/ModGlobals.hpp"
#include "mods/new/IModManager.hpp"
#include "Modules/ModuleBase.hpp"
#include "Modules/ModuleServer.hpp"
#include "Patches/Weapon.hpp"
#include "Player/PlayerCustomizationDB.hpp"
#include "Player/PlayerCustomizationExtension.hpp"
#include "Player/PlayerEmblemDownload.hpp"
#include "Player/PlayerEmotes.hpp"
#include "Pointer.hpp"
#include "Server/ServerChat.hpp"
#include "ThirdParty/HttpRequest.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
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
#include "Utils/DewritoReader.hpp"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/StlUtil.hpp"
#include "Utils/String.hpp"
#include "Utils/WebSocket.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>
#include <d3dx9core.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
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
#include <unordered_set>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class HttpRequest;
class c_mod_package_manager;
struct real_euler_angles3d;
struct real_vector3d;
struct s_game_globals;
struct s_game_globals_player_character_type;
struct s_mod_globals_character_region_script;
struct s_mod_globals_definition;
struct s_mod_globals_player_character_customization;
struct s_model_customization_player_region;
struct s_model_customization_player_region_permutation;
struct s_model_customization_selection;
struct s_multiplayer_globals_definition;
struct s_observer_result;
struct s_player_control_input_state;
struct s_player_emblem_configuration;
struct s_scenario;
struct s_scenario_biped;
struct s_scenario_cutscene_camera_point;
namespace Blam
{
	namespace Network
	{
		struct Session;
	}
}
namespace Modules
{
	class ModuleBase;
	class ModulePlayer;
}
namespace Player
{
	class CPlayerCustomizationDB;
	struct SPersistentCharacterCustomization;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Server {}
using namespace ::Server;
namespace Server
{
	namespace Stats {}
	using namespace Server::Stats;
	namespace Chat {}
	using namespace Server::Chat;
}

namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace Emblems {}
	using namespace Player::Emblems;
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
		namespace WebEmote {}
		using namespace Web::Ui::WebEmote;
	}
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace PlayerUid {}
	using namespace Patches::PlayerUid;
}

namespace Http {}
using namespace ::Http;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
	namespace Network {}
	using namespace Blam::Network;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetPayload();
bool SendRequest(std::basic_string<char,std::char_traits<char>,std::allocator<char> > payload, std::basic_string<char,std::char_traits<char>,std::allocator<char> > endpoint);
bool CommandRegisterPlayer(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool VariablePlayerArmorUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool VariablePlayerEmblem(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool VariablePlayerNameUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
void UpdateLocalRepresentation();
bool VariablePlayerServiceTagUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool VariablePlayerGenderUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandPlayerPrintUID(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool TryParseFloat(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str, float *value);
bool CommandSetUiPlayerModelPosition(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandReturnCustomizationBiped(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandSetRegionCamera(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandSetUiPlayerModelCustomization(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
std::basic_string<char,std::char_traits<char>,std::allocator<char> > rgb2hex(unsigned long color);
std::basic_string<char,std::char_traits<char>,std::allocator<char> > ResolveString(unsigned __int32 unicTagIndex, unsigned __int32 strindId);
bool CommandListCustomizationPermutations(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandSetUiPlayerModelRotation(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandSetCarryType(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool GenerateTimestamp(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
std::basic_string<char,std::char_traits<char>,std::allocator<char> > GenerateRandomServiceTag();
bool CommandReloadCustomization(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandTestCustomization(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandKillSelf(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandPlayerArmor(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandPlayerColor(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool CommandPreferredCharacter(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);
bool TryParseInt(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str, __int32 *value);
bool CommandPlayerEmote(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	extern ModulePlayer* _sub_109ECCC0(Modules::ModulePlayer *const);
	ModulePlayer::ModulePlayer() : ModuleBase(todo_result<std::basic_string<char,std::char_traits<char>,std::allocator<char> >>()) // 0x109ECCC0
	{
		mangled_x86(MANGLED_TODO, "??0ModulePlayer@Modules@@QAE@XZ");
		// static ...; // 0x109EE7D9
		// static ...; // 0x109EE7CA
		// static ...; // 0x109EE7BF
		// static ...; // 0x109EE7B2
		// static ...; // 0x109EE7A4
		// static ...; // 0x109EE768
		// static ...; // 0x109EE760
		// Modules::ModulePlayer *const this;
		// char const *defaultNames[103];
		// char const *defaultEmblems[53];
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > randomEmblem;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > randomName;
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > previousValue;
		todo("implement");
		_sub_109ECCC0(this);
	}

	_extern bool _sub_109F6BC0(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
	bool ModulePlayer::ValidServiceTag(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &tag) // 0x109F6BC0
	{
		mangled_x86(MANGLED_TODO, "?ValidServiceTag@ModulePlayer@Modules@@SA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &tag;
		// static std::unordered_set<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::hash<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::equal_to<std::basic_string<char,std::char_traits<char>,std::allocator<char> > >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > filter; // 0x12455E48
		// static __int32 $TSS0; // 0x12455E70
		todo("implement");
		bool __result = _sub_109F6BC0(tag);
		return __result;
	}

	_extern bool _sub_109F6A50(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &);
	bool ModulePlayer::ValidPlayerName(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name) // 0x109F6A50
	{
		mangled_x86(MANGLED_TODO, "?ValidPlayerName@ModulePlayer@Modules@@SA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &name;
		todo("implement");
		bool __result = _sub_109F6A50(name);
		return __result;
	}
}

/* ---------- private code */

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_109F5540();
std::basic_string<char,std::char_traits<char>,std::allocator<char> > GetPayload() // 0x109F5540
{
	// `anonymous-namespace'::GetPayload
	// procedure flags: nofpo
	// static ...; // 0x109F5E31
	// static ...; // 0x109F5E27
	// static ...; // 0x109F5E20
	// static ...; // 0x109F5E16
	// static ...; // 0x109F5E14
	// static ...; // 0x109F5E0D
	// static ...; // 0x109F5E09
	// static ...; // 0x109F5DFC
	// static ...; // 0x109F5D9C
	// static ...; // 0x109F5D94
	// char const *const sig;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > signature;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > pubKey;
	// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> dewrito;
	// s_player_emblem_configuration emblemConfig;
	// char uid[17];
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> s;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > timestamp;
	todo("implement");
	std::string __result = _sub_109F5540();
	return __result;
}

_extern bool _sub_109F6220(std::string, std::string);
bool SendRequest(std::basic_string<char,std::char_traits<char>,std::allocator<char> > payload, std::basic_string<char,std::char_traits<char>,std::allocator<char> > endpoint) // 0x109F6220
{
	// `anonymous-namespace'::SendRequest
	// static ...; // 0x109F66BC
	// static ...; // 0x109F66A4
	// static ...; // 0x109F669C
// $LN27:
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > payload;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > endpoint;
	// HttpRequest req;
	{
		// std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > expected;
	}
	todo("implement");
	bool __result = _sub_109F6220(payload, endpoint);
	return __result;
}

_extern bool _sub_109F2470(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandRegisterPlayer(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F2470
{
	// `anonymous-namespace'::CommandRegisterPlayer
	// static ...; // 0x109F2688
	// static ...; // 0x109F267F
	// static ...; // 0x109F2678
	// static ...; // 0x109F2648
	// static ...; // 0x109F2640
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > payload;
	// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> dewrito;
	{
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > endpoint;
		// std::thread thread;
	}
	todo("implement");
	bool __result = _sub_109F2470(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109F7350(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool VariablePlayerArmorUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F7350
{
	// `anonymous-namespace'::VariablePlayerArmorUpdate
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_109F7350(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109F7390(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool VariablePlayerEmblem(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F7390
{
	// `anonymous-namespace'::VariablePlayerEmblem
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_109F7390(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109F74A0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool VariablePlayerNameUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F74A0
{
	// `anonymous-namespace'::VariablePlayerNameUpdate
	// static ...; // 0x109F767C
	// static ...; // 0x109F7664
	// static ...; // 0x109F765C
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// Modules::ModulePlayer &modulePlayer;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > name;
	// std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > nameW;
	// unsigned __int32 len;
	todo("implement");
	bool __result = _sub_109F74A0(Arguments, returnInfo);
	return __result;
}

_extern void _sub_109F69B0();
void UpdateLocalRepresentation() // 0x109F69B0
{
	// `anonymous-namespace'::UpdateLocalRepresentation
	// procedure flags: nofpo
	// Blam::Network::Session *activeSession;
	{
		// __int32 (*Network_session_update_user_properties)(Blam::Network::Session *, __int32);
	}
	// function call : __int32 (*)(Blam::Network::Session *, __int32)
	todo("implement");
	_sub_109F69B0();
}

_extern bool _sub_109F7700(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool VariablePlayerServiceTagUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F7700
{
	// `anonymous-namespace'::VariablePlayerServiceTagUpdate
	// static ...; // 0x109F788C
	// static ...; // 0x109F7884
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// Modules::ModulePlayer &modulePlayer;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > value;
	todo("implement");
	bool __result = _sub_109F7700(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109F73E0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool VariablePlayerGenderUpdate(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F73E0
{
	// `anonymous-namespace'::VariablePlayerGenderUpdate
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_109F73E0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109F1C00(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandPlayerPrintUID(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F1C00
{
	// `anonymous-namespace'::CommandPlayerPrintUID
	// static ...; // 0x109F1E04
	// static ...; // 0x109F1DFC
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// unsigned long long uid;
	// std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > ss;
	todo("implement");
	bool __result = _sub_109F1C00(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109F6800(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, float *);
bool TryParseFloat(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str, float *value) // 0x109F6800
{
	// `anonymous-namespace'::TryParseFloat
	// static ...; // 0x109F688C
	// static ...; // 0x109F6884
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str;
	// float *value;
	// char *endp;
	todo("implement");
	bool __result = _sub_109F6800(str, value);
	return __result;
}

_extern bool _sub_109F4730(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandSetUiPlayerModelPosition(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F4730
{
	// `anonymous-namespace'::CommandSetUiPlayerModelPosition
	// static ...; // 0x109F4814
	// static ...; // 0x109F480C
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// real_vector3d position;
	todo("implement");
	bool __result = _sub_109F4730(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109F2770(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandReturnCustomizationBiped(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F2770
{
	// `anonymous-namespace'::CommandReturnCustomizationBiped
	// static ...; // 0x109F2AD9
	// static ...; // 0x109F2AD0
	// static ...; // 0x109F2AAC
	// static ...; // 0x109F2AA4
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > preferredCharacterName;
	// s_game_globals const *game_globals;
	// s_mod_globals_definition const *mod_globals;
	// short bipedIndex;
	// s_scenario *const scnr;
	// s_scenario_biped const &character;
	{
		// __int32 i;
		{
			// s_mod_globals_player_character_customization *character;
		}
	}
	{
		// real_vector3d position;
		// float rotation;
	}
	todo("implement");
	bool __result = _sub_109F2770(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109F2C70(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandSetRegionCamera(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F2C70
{
	// `anonymous-namespace'::CommandSetRegionCamera
	// static ...; // 0x109F33E6
	// static ...; // 0x109F33DB
	// static ...; // 0x109F33D1
	// static ...; // 0x109F33C3
	// static ...; // 0x109F33BC
	// static ...; // 0x109F33AB
	// static ...; // 0x109F339C
	// static ...; // 0x109F333C
	// static ...; // 0x109F3334
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > preferredCharacterName;
	// long (*const interface_get_closest_authored_ui_aspect_ratio)();
	// s_game_globals const *game_globals;
	// float ui_aspect_ratio;
	// s_mod_globals_definition const *mod_globals;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
	// long *ui_resolution;
	// long display_mode;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
	{
		// long character_type_index;
		{
			// __int32 i;
			{
				// s_mod_globals_player_character_customization *character;
				{
					// __int32 x;
					{
						// s_mod_globals_character_region_script *region_script;
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > region;
						{
							// float rotationAngle;
							// std::basic_string<char,std::char_traits<char>,std::allocator<char> > scriptWidescreen;
							// std::basic_string<char,std::char_traits<char>,std::allocator<char> > scriptStandard;
							// float rotationSpeed;
						}
					}
				}
			}
		}
	}
	// function call : long (*const)()
	todo("implement");
	bool __result = _sub_109F2C70(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109F35F0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandSetUiPlayerModelCustomization(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F35F0
{
	// `anonymous-namespace'::CommandSetUiPlayerModelCustomization
	// static ...; // 0x109F4390
	// static ...; // 0x109F4386
	// static ...; // 0x109F437A
	// static ...; // 0x109F436C
	// static ...; // 0x109F4366
	// static ...; // 0x109F4360
	// static ...; // 0x109F4357
	// static ...; // 0x109F4349
	// static ...; // 0x109F4342
	// static ...; // 0x109F4337
	// static ...; // 0x109F432C
	// static ...; // 0x109F429C
	// static ...; // 0x109F4294
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > preferredCharacterName;
	// float const two_PI;
	// long (*const interface_get_closest_authored_ui_aspect_ratio)();
	// s_game_globals const *game_globals;
	// float ui_aspect_ratio;
	// s_mod_globals_definition const *mod_globals;
	// s_observer_result *observer_camera_data;
	// long *ui_resolution;
	// s_scenario *const scnr;
	// c_tag_block<s_scenario_cutscene_camera_point> cutscenes;
	// long display_mode;
	{
		// long character_type_index;
		{
			// s_game_globals_player_character_type const *character_type;
			// long representation_index;
			{
				// __int32 i;
				{
					// s_mod_globals_player_character_customization *character;
					{
						// float rotationAngle;
						// float rotationOffset;
						// float amt;
						// __int32 settings_camera_index;
						// real_vector3d position;
						// bool canRotate;
						// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
						// s_observer_result *camera;
						// real_point3d point;
						// real_point3d newBipedPoint;
						// real_vector3d bipedOffset;
						// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
						{
							// float yaw;
							// real_euler_angles3d euler;
						}
						{
							// __int32 x;
							{
								// s_mod_globals_character_region_script *region_script;
								// std::basic_string<char,std::char_traits<char>,std::allocator<char> > region;
							}
						}
					}
				}
			}
		}
	}
	// function call : s_observer_result *(*const)(long)
	// function call : long (*const)()
	// function call : s_observer_result *(*const)(long)
	todo("implement");
	bool __result = _sub_109F35F0(Arguments, returnInfo);
	return __result;
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_109F9C00(unsigned long);
std::basic_string<char,std::char_traits<char>,std::allocator<char> > rgb2hex(unsigned long color) // 0x109F9C00
{
	// `anonymous-namespace'::rgb2hex
	// static ...; // 0x109F9D0D
	// static ...; // 0x109F9D08
	// static ...; // 0x109F9CF0
	// static ...; // 0x109F9CE8
	// unsigned long color;
	// char buff[255];
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > result;
	todo("implement");
	std::string __result = _sub_109F9C00(color);
	return __result;
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_109F6080(unsigned __int32, unsigned __int32);
std::basic_string<char,std::char_traits<char>,std::allocator<char> > ResolveString(unsigned __int32 unicTagIndex, unsigned __int32 strindId) // 0x109F6080
{
	// `anonymous-namespace'::ResolveString
	// unsigned __int32 strindId;
	// __int32 (*const ui_get_prefered_lanquage)();
	// char *(*const ui_resolve_string)(unsigned __int32, unsigned __int32, __int32);
	// char *resolvedString;
	// function call : __int32 (*const)()
	// function call : char *(*const)(unsigned __int32, unsigned __int32, __int32)
	todo("implement");
	std::string __result = _sub_109F6080(unicTagIndex, strindId);
	return __result;
}

_extern bool _sub_109EFDD0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandListCustomizationPermutations(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109EFDD0
{
	// `anonymous-namespace'::CommandListCustomizationPermutations
	// static ...; // 0x109F0F6E
	// static ...; // 0x109F0F63
	// static ...; // 0x109F0F58
	// static ...; // 0x109F0F3D
	// static ...; // 0x109F0F2E
	// static ...; // 0x109F0F18
	// static ...; // 0x109F0F07
	// static ...; // 0x109F0EF9
	// static ...; // 0x109F0EF2
	// static ...; // 0x109F0EE6
	// static ...; // 0x109F0EDA
	// static ...; // 0x109F0ED0
	// static ...; // 0x109F0EC6
	// static ...; // 0x109F0EBC
	// static ...; // 0x109F0E08
	// static ...; // 0x109F0E00
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > preferredCharacterName;
	// long const armorStrings;
	// long const colorStrings;
	// s_game_globals const *matg;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
	// s_mod_globals_definition const *modg;
	// s_multiplayer_globals_definition *const mulg;
	// s_mod_globals_player_character_customization *currently_chosen_character;
	// long const armorStringshf2p;
	// long const globalStrings;
	// __int32 player_character_customization_index;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
	{
		// __int32 i;
		{
			// s_mod_globals_player_character_customization *character;
		}
	}
	{
		// s_model_customization_selection *customization;
		// char const *colorNamesKeys[5];
		// char const *colorDescriptionsKeys[5];
		// char const *colorDefaultKeys[5];
		{
			// long i;
		}
		{
			// __int32 i;
			{
				// bool hasVisiblePermutations;
				// s_model_customization_player_region *region;
				{
					// __int32 perm_index;
					{
						// s_model_customization_player_region_permutation *permutation;
					}
				}
				{
					{
						// char *desc_stringid;
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > desc_name;
						// char *perm_stringid;
						// std::basic_string<char,std::char_traits<char>,std::allocator<char> > perm_name;
					}
				}
			}
		}
	}
	{
		{
		}
	}
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	bool __result = _sub_109EFDD0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109F4870(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandSetUiPlayerModelRotation(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F4870
{
	// `anonymous-namespace'::CommandSetUiPlayerModelRotation
	// static ...; // 0x109F49D0
	// static ...; // 0x109F49B8
	// static ...; // 0x109F49B0
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// float rotationAngle;
	// float rotationTime;
	todo("implement");
	bool __result = _sub_109F4870(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109F2BE0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandSetCarryType(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F2BE0
{
	// `anonymous-namespace'::CommandSetCarryType
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// s_player_control_input_state *player_control;
	todo("implement");
	bool __result = _sub_109F2BE0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109F5320(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool GenerateTimestamp(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F5320
{
	// `anonymous-namespace'::GenerateTimestamp
	// static ...; // 0x109F54B8
	// static ...; // 0x109F54B4
	// static ...; // 0x109F5490
	// static ...; // 0x109F5488
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// Modules::ModulePlayer &modulePlayer;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > encryptedString;
	// char buf[42];
	// tm *now_tm;
	// long long now;
	todo("implement");
	bool __result = _sub_109F5320(Arguments, returnInfo);
	return __result;
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_109F5180();
std::basic_string<char,std::char_traits<char>,std::allocator<char> > GenerateRandomServiceTag() // 0x109F5180
{
	// `anonymous-namespace'::GenerateRandomServiceTag
	// procedure flags: nofpo
	// static ...; // 0x109F52C4
	// static ...; // 0x109F52B8
	// static ...; // 0x109F52B0
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > tag;
	todo("implement");
	std::string __result = _sub_109F5180();
	return __result;
}

_extern bool _sub_109F2730(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandReloadCustomization(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F2730
{
	// `anonymous-namespace'::CommandReloadCustomization
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_109F2730(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109F4A50(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandTestCustomization(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F4A50
{
	// `anonymous-namespace'::CommandTestCustomization
	// static ...; // 0x109F4FF0
	// static ...; // 0x109F4FD8
	// static ...; // 0x109F4FD0
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// Player::SPersistentCharacterCustomization customization1;
	// Player::CPlayerCustomizationDB &db;
	// Player::SPersistentCharacterCustomization customization2;
	todo("implement");
	bool __result = _sub_109F4A50(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109EFD00(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandKillSelf(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109EFD00
{
	// `anonymous-namespace'::CommandKillSelf
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	todo("implement");
	bool __result = _sub_109EFD00(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109F1400(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandPlayerArmor(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F1400
{
	// `anonymous-namespace'::CommandPlayerArmor
	// static ...; // 0x109F1658
	// static ...; // 0x109F1640
	// static ...; // 0x109F1638
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > preferredCharacterName;
	// Player::CPlayerCustomizationDB &db;
	{
		// Player::SPersistentCharacterCustomization customization;
	}
	todo("implement");
	bool __result = _sub_109F1400(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109F1720(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandPlayerColor(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F1720
{
	// `anonymous-namespace'::CommandPlayerColor
	// static ...; // 0x109F1978
	// static ...; // 0x109F1960
	// static ...; // 0x109F1958
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > preferredCharacterName;
	// Player::CPlayerCustomizationDB &db;
	{
		// Player::SPersistentCharacterCustomization customization;
	}
	todo("implement");
	bool __result = _sub_109F1720(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109F1EA0(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandPreferredCharacter(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F1EA0
{
	// `anonymous-namespace'::CommandPreferredCharacter
	// static ...; // 0x109F232D
	// static ...; // 0x109F2328
	// static ...; // 0x109F2322
	// static ...; // 0x109F2318
	// static ...; // 0x109F22DC
	// static ...; // 0x109F22D4
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// bool (*const game_is_mainmenu)();
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > modHash;
	// bool modIsCharacterType;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > modName;
	// Player::CPlayerCustomizationDB &db;
	// c_mod_package_manager::s_entry entry;
	// unsigned char hash[20];
	{
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &preferredCharacterName;
	}
	{
		// std::basic_string<char,std::char_traits<char>,std::allocator<char> > character;
	}
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_109F1EA0(Arguments, returnInfo);
	return __result;
}

_extern bool _sub_109F68D0(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &, __int32 *);
bool TryParseInt(std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str, __int32 *value) // 0x109F68D0
{
	// `anonymous-namespace'::TryParseInt
	// static ...; // 0x109F6970
	// static ...; // 0x109F6968
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > const &str;
	// __int32 *value;
	// char const *c_str;
	// char *endp;
	todo("implement");
	bool __result = _sub_109F68D0(str, value);
	return __result;
}

_extern bool _sub_109F1A40(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &);
bool CommandPlayerEmote(std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments, std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo) // 0x109F1A40
{
	// `anonymous-namespace'::CommandPlayerEmote
	// static ...; // 0x109F1B8C
	// static ...; // 0x109F1B84
	// std::vector<std::basic_string<char,std::char_traits<char>,std::allocator<char> >,std::allocator<std::basic_string<char,std::char_traits<char>,std::allocator<char> > > > const &Arguments;
	// std::basic_string<char,std::char_traits<char>,std::allocator<char> > &returnInfo;
	// bool (*const game_is_mainmenu)();
	// __int32 emoteIndex;
	// unsigned long playerIndex;
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)()
	// function call : bool (*const)()
	todo("implement");
	bool __result = _sub_109F1A40(Arguments, returnInfo);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_mod_globals_character_region_script>::try_get_element(__int32, s_mod_globals_character_region_script **) const;
template bool c_tag_block<s_scenario_biped>::try_get_element(__int32, s_scenario_biped **) const;
template bool c_tag_block<s_scenario_object_name>::try_get_element(__int32, s_scenario_object_name **) const;
template s_model_customization_region_permutation * c_tag_block<s_model_customization_region_permutation>::operator->();
template s_scenario_biped & c_tag_block<s_scenario_biped>::operator[](__int32);
template s_scenario_biped * c_tag_block<s_scenario_biped>::get_element(__int32) const;
template s_scenario_object_name & c_tag_block<s_scenario_object_name>::operator[](__int32);
template s_scenario_object_name * c_tag_block<s_scenario_object_name>::get_element(__int32) const;
