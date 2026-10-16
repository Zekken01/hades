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

#include "Blam/Cache/StringIdCache.hpp"  // hades: added for 0x109F6080

#include "Utils/Logger.hpp"  // hades: added for 0x109F74A0

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

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const observer_get_camera = reinterpret_cast<s_observer_result *(*)(long)>(0x6127C0);
	static auto const observer_try_and_get_camera = reinterpret_cast<s_observer_result *(*)(long)>(0x613960);
}

namespace Utils::Version { std::string GetVersionString(); }  // hades: added for 0x109F6220

#include "mods/mod_system.hpp"  // hades: added for 0x109F1EA0
extern void clearCachedCharacter();  // hades: added for 0x109F1EA0

extern std::string GetCurrentPreferredCharacter();  // hades: added for 0x109F1400

extern void SetUiPlayerModelRotation(float angleDegrees, float seconds);  // hades: added for 0x109F4870
extern long find_player_character_by_name(char const *);  // hades: added for 0x109F35F0
extern long tag_find_by_name(unsigned long group_tag, char const *name);  // hades: added for 0x109EFDD0
extern real_euler_angles3d *euler_angles3d_from_vectors3d(real_euler_angles3d *angles, real_vector3d const *forward, real_vector3d const *up);  // hades: added for 0x109F35F0
namespace Player { extern real_point3d CalculateBipedPosition(real_point3d const *point, real_euler_angles3d const *euler, float distance, float right_distance); }  // hades: added for 0x109F35F0

namespace Patches { namespace PlayerUid { extern unsigned long long Get(); } }  // hades: added for 0x109F1C00

namespace Utils { namespace Cryptography { extern std::string ReformatKey(bool isPrivateKey, std::string key); extern bool PrivateEncrypt(std::string privateKey, void *data, unsigned __int32 dataSize, std::string &encrypted); } } namespace Utils { namespace Cryptography { extern bool CreateRSASignature(std::string privateKey, void *data, unsigned __int32 dataSize, std::string &signature); extern std::string GetEncryptedTimestamp(std::string publicKey, bool unused); } } namespace Server { namespace Stats { extern void GetStatsPublicKey(std::string &out); } } namespace Player { namespace Emblems { extern bool ParseURL(std::string const &url, s_player_emblem_configuration &config); extern std::string HexToStrHex(int hex); } } extern void player_format_uid(char *string, unsigned long long id);  // hades: added for 0x109F5320, 0x109F5540

namespace Web { namespace Ui { namespace WebEmote { extern void Show(); } } }  // hades: added for 0x109F1A40

void SetUiPlayerModelPosition(real_vector3d const *newPosition);  // hades: added for 0X109F4730

extern void RefreshUiPlayer();  // hades: added for 0x109F7350

std::string GetPayload();
bool SendRequest(std::string payload, std::string endpoint);
bool CommandRegisterPlayer(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariablePlayerArmorUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariablePlayerEmblem(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariablePlayerNameUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
void UpdateLocalRepresentation();
bool VariablePlayerServiceTagUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool VariablePlayerGenderUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandPlayerPrintUID(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool TryParseFloat(std::string const &str, float *value);
bool CommandSetUiPlayerModelPosition(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandReturnCustomizationBiped(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandSetRegionCamera(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandSetUiPlayerModelCustomization(std::vector<std::string> const &Arguments, std::string &returnInfo);
std::string rgb2hex(unsigned long color);
std::string ResolveString(unsigned __int32 unicTagIndex, unsigned __int32 strindId);
bool CommandListCustomizationPermutations(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandSetUiPlayerModelRotation(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandSetCarryType(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool GenerateTimestamp(std::vector<std::string> const &Arguments, std::string &returnInfo);
std::string GenerateRandomServiceTag();
bool CommandReloadCustomization(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandTestCustomization(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandKillSelf(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandPlayerArmor(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandPlayerColor(std::vector<std::string> const &Arguments, std::string &returnInfo);
bool CommandPreferredCharacter(std::vector<std::string> const &Arguments, std::string &returnInfo);
static bool TryParseInt(std::string const &str, __int32 *value);
bool CommandPlayerEmote(std::vector<std::string> const &Arguments, std::string &returnInfo);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Modules
{
	ModulePlayer::ModulePlayer() : ModuleBase("Player") /* hades-mem-init: : ModuleBase(todo_result<std::string>()) */ // 0x109ECCC0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0ModulePlayer@Modules@@QAE@XZ");

		AddCommand("Armor.Update", "armor_update", "Update the player's armor.", eCommandFlagsHidden, VariablePlayerArmorUpdate);
		AddCommand("Armor.SetUiModelPosition", "armor_ui_player_model_position", "Set the position of the ui player model", CommandFlags(eCommandFlagsOmitValueInList | eCommandFlagsHidden), CommandSetUiPlayerModelPosition);
		AddCommand("Armor.SetUiModelRotation", "armor_ui_player_model_rotation", "Set the rotation of the ui player model", eCommandFlagsHidden, CommandSetUiPlayerModelRotation);
		AddCommand("Armor.SetCustomizationUI", "armor_ui_customization_set", "Set the player model to the position of the settings camera", CommandFlags(eCommandFlagsOmitValueInList | eCommandFlagsHidden), CommandSetUiPlayerModelCustomization);
		AddCommand("Armor.SetRegionCamera", "armor_ui_customization_region_camera", "run the region camera script for the character", CommandFlags(eCommandFlagsOmitValueInList | eCommandFlagsHidden), CommandSetRegionCamera);
		AddCommand("Armor.ReturnCustomizationBiped", "armor_ui_customization_return", "return the customization player model to original position", eCommandFlagsHidden, CommandReturnCustomizationBiped);
		VarPlayerEmblem = AddVariableString("Emblem", "player_emblem", "Player Emblem url", CommandFlags(eCommandFlagsNoReset | eCommandFlagsArchived), "", VariablePlayerEmblem);
		AddCommand("Armor.ListCustomizationPermutation", "armor_customization_json_return", "Prints out an array of armor permutations", eCommandFlagsHidden, CommandListCustomizationPermutations);
		AddCommand("RegisterPlayer", "register", "Contacts HS and creates a player object.", CommandFlags(eCommandFlagsInternal | eCommandFlagsRunOnMainMenu), CommandRegisterPlayer);
		AddCommand("AlertCarry", "alert_carry", "Toggle the alert carry pose", eCommandFlagsNone, CommandSetCarryType);
		AddCommand("Kill", "kill", "Kills the player that runs the command", eCommandFlagsNone, CommandKillSelf);
		AddCommand("PreferredCharacter", "preferred_character", "the preferred character for the currently loaded mod", eCommandFlagsHidden, CommandPreferredCharacter);
		VarPlayerName = AddVariableString("Name", "name", "The players ingame name", CommandFlags(eCommandFlagsNoReset | eCommandFlagsArchived), "Jasper", VariablePlayerNameUpdate);
		VarPlayerServiceTag = AddVariableString("ServiceTag", "service_tag", "The players service tag", eCommandFlagsArchived, "117", VariablePlayerServiceTagUpdate);
		VarPlayerGender = AddVariableString("Gender", "gender", "The players gender", eCommandFlagsArchived, "male", VariablePlayerGenderUpdate);
		AddVariableString("PrivKeyNote", "priv_key_note", "", CommandFlags(eCommandFlagsWriteToKeys | eCommandFlagsHidden), "The PrivKey below is used to keep your stats safe. Treat it like a password and don't share it with anyone!");
		VarPlayerPrivKey = AddVariableString("PrivKey", "player_privkey", "The players unique stats private key", CommandFlags(eCommandFlagsWriteToKeys | eCommandFlagsOmitValueInList), "");
		VarPlayerPubKey = AddVariableString("PubKey", "player_pubkey", "The players unique stats public key", CommandFlags(eCommandFlagsWriteToKeys | eCommandFlagsOmitValueInList), "");
		memset(UserName, 0, sizeof(UserName));
		AddCommand("ReloadCustomization", "reload_customization", "", eCommandFlagsNone, CommandReloadCustomization);
		AddCommand("TestCustomization", "test_customization", "", eCommandFlagsNone, CommandTestCustomization);
		AddCommand("Customization.Armor", "customization_armor", "Update or retrieve the player's armor.", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsHidden), CommandPlayerArmor);
		AddCommand("Customization.Color", "customization_color", "Update or retrieve the player's color.", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsHidden), CommandPlayerColor);
		VarNameplateColor = AddVariableString("NameplateColor", "nameplate_color", "Color for the nameplate in the lobby", CommandFlags(eCommandFlagsHostOnly | eCommandFlagsArchived), "#546e26");
		VarNameplate = AddVariableInt("Nameplate", "nameplate", "Index for the nameplate in the lobby", eCommandFlagsArchived, 0);
		AddCommand("PrintUID", "uid", "Prints the players UID", eCommandFlagsNone, CommandPlayerPrintUID);
		AddCommand("EncryptGmtTimestamp", "encryptgmttimestamp", "encrypts a timestamp using the player's private key.", eCommandFlagsHidden, GenerateTimestamp);
		AddCommand("Emote", "player_emote", "Starts an emote", eCommandFlagsNone, CommandPlayerEmote);
		VarSprintAnimationHack = AddVariableInt("SprintAnimationHack", "sprint_animation_hack", "", eCommandFlagsInternal, 1);
		Pointer::Base(0x42AA1).Write<unsigned int>((unsigned int)&UserName);
		Pointer::Base(0x124E6A).Write<unsigned int>((unsigned int)&UserName);
		char const *defaultNames[103] =
		{
			"Mustard",
			"Sleepy",
			"Dopey",
			"Grumpy",
			"Mopey",
			"Sketch",
			"Crazy",
			"Saucy",
			"Wheezy",
			"Kitty",
			"Killer",
			"Steak",
			"Butcher",
			"Darling",
			"Disco",
			"Donut",
			"Cotton",
			"Stank",
			"Ratjar",
			"Noodle",
			"Weasel",
			"Snake",
			"Shadow",
			"Caboose",
			"King",
			"Sneak",
			"The Bear",
			"Ghost",
			"Penguin",
			"Coward",
			"Moogley",
			"Doggy Dog",
			"Potato",
			"Wilshire",
			"Pirate",
			"Wallace",
			"Tooth",
			"Goat",
			"Stumpy",
			"Stomp",
			"Winky",
			"Ling-ling",
			"Hippo",
			"Turtle",
			"Moose",
			"Derby",
			"Wiggly",
			"Bongo",
			"Skip",
			"Bork",
			"Lemon",
			"Hermit",
			"Ralfie",
			"Cheese",
			"Duke",
			"Badger",
			"Beagle",
			"Wort",
			"Wiggler",
			"Soffish",
			"Yodler",
			"Geronimo",
			"Darkman",
			"Snoozy",
			"Shaggy",
			"Banana",
			"Shiz",
			"Giant",
			"Slinky",
			"Pretzel",
			"Brutus",
			"Pinky",
			"Milo",
			"Monkey",
			"Bozo",
			"Grunty",
			"Bower",
			"Floss",
			"Nappy",
			"Gerbil",
			"Goose",
			"Scruffy",
			"Soap",
			"Polo",
			"Muffin",
			"Beast",
			"Clubby",
			"Surly",
			"Balin",
			"Poodle",
			"Snaz",
			"Jungle Jim",
			"Spork",
			"Grub",
			"Snook",
			"Spleen",
			"Pumpkin",
			"Custard",
			"Cracky",
			"Pickle",
			"Slim",
			"Lucky",
			"Pudding",
		};
		char const *defaultEmblems[53] =
		{
			"?1=10&2=10&3=10&fi=1&bi=17&fl=0&m=1",
			"?1=2&2=2&3=2&fi=18&bi=45&fl=1&m=1",
			"?1=3&2=3&3=3&fi=12&bi=45&fl=0&m=1",
			"?1=1&2=0&3=1&fi=13&bi=39&fl=0&m=1",
			"?1=27&2=21&3=6&fi=49&bi=36&fl=1&m=1",
			"?1=2&2=0&3=2&fi=16&bi=40&fl=0&m=1",
			"?1=2&2=2&3=2&fi=19&bi=40&fl=1&m=1",
			"?1=12&2=0&3=12&fi=17&bi=46&fl=0&m=1",
			"?1=2&2=0&3=1&fi=65&bi=13&fl=0&m=1",
			"?1=17&2=19&3=21&fi=27&bi=32&fl=1&m=1",
			"?1=2&2=2&3=1&fi=23&bi=5&fl=1&m=1",
			"?1=13&2=12&3=28&fi=47&bi=13&fl=1&m=1",
			"?1=6&2=6&3=1&fi=43&bi=43&fl=0&m=1",
			"?1=16&2=16&3=16&fi=2&bi=39&fl=1&m=1",
			"?1=2&2=18&3=3&fi=14&bi=19&fl=1&m=1",
			"?1=9&2=6&3=9&fi=43&bi=44&fl=1&m=1",
			"?1=2&2=0&3=1&fi=63&bi=47&fl=0&m=1",
			"?1=2&2=13&3=10&fi=2&bi=0&fl=1&m=1",
			"?1=6&2=3&3=3&fi=1&bi=0&fl=1&m=1",
			"?1=2&2=29&3=29&fi=29&bi=7&fl=1&m=1",
			"?1=27&2=1&3=28&fi=27&bi=1&fl=0&m=1",
			"?1=2&2=2&3=1&fi=18&bi=40&fl=1&m=1",
			"?1=9&2=9&3=9&fi=42&bi=33&fl=0&m=1",
			"?1=6&2=15&3=12&fi=4&bi=47&fl=0&m=1",
			"?1=19&2=0&3=23&fi=14&bi=20&fl=0&m=1",
			"?1=2&2=27&3=2&fi=19&bi=37&fl=1&m=1",
			"?1=2&2=3&3=11&fi=52&bi=19&fl=1&m=1",
			"?1=3&2=3&3=3&fi=42&bi=33&fl=0&m=1",
			"?1=3&2=0&3=1&fi=59&bi=26&fl=1&m=1",
			"?1=2&2=1&3=3&fi=58&bi=35&fl=1&m=1",
			"?1=2&2=3&3=2&fi=16&bi=1&fl=1&m=1",
			"?1=3&2=6&3=9&fi=47&bi=43&fl=1&m=1",
			"?1=3&2=10&3=2&fi=30&bi=43&fl=1&m=1",
			"?1=12&2=6&3=2&fi=31&bi=17&fl=1&m=1",
			"?1=2&2=2&3=9&fi=22&bi=25&fl=1&m=1",
			"?1=19&2=2&3=1&fi=12&bi=0&fl=1&m=1",
			"?1=10&2=6&3=3&fi=30&bi=43&fl=1&m=1",
			"?1=10&2=17&3=25&fi=51&bi=38&fl=1&m=1",
			"?1=28&2=3&3=2&fi=63&bi=13&fl=1&m=1",
			"?1=3&2=0&3=9&fi=22&bi=32&fl=1&m=1",
			"?1=3&2=0&3=2&fi=56&bi=34&fl=1&m=1",
			"?1=2&2=2&3=10&fi=22&bi=0&fl=1&m=1",
			"?1=2&2=2&3=1&fi=12&bi=0&fl=1&m=1",
			"?1=1&2=14&3=14&fi=23&bi=4&fl=1&m=0",
			"?1=3&2=0&3=2&fi=38&bi=15&fl=1&m=1",
			"?1=13&2=13&3=13&fi=18&bi=12&fl=1&m=1",
			"?1=2&2=18&3=2&fi=1&bi=25&fl=1&m=1",
			"?1=2&2=12&3=2&fi=50&bi=47&fl=1&m=1",
			"?1=2&2=10&3=2&fi=27&bi=31&fl=0&m=1",
			"?1=1&2=1&3=1&fi=54&bi=16&fl=1&m=1",
			"?1=2&2=0&3=1&fi=53&bi=40&fl=1&m=1",
			"?1=2&2=3&3=2&fi=1&bi=0&fl=1&m=1",
			"?1=3&2=2&3=2&fi=69&bi=1&fl=1&m=1",
		};
		srand((unsigned int)time(nullptr));
		std::string randomName = defaultNames[rand() % (sizeof(defaultNames) / sizeof(defaultNames[0]))];
		std::string randomEmblem = defaultEmblems[rand() % (sizeof(defaultEmblems) / sizeof(defaultEmblems[0]))];
		std::string previousValue;
		Modules::CommandMap::Instance().SetVariable(VarPlayerEmblem, randomEmblem, previousValue, true);
		Modules::CommandMap::Instance().SetVariable(VarPlayerName, randomName, previousValue, true);
		Modules::CommandMap::Instance().SetVariable(VarPlayerServiceTag, GenerateRandomServiceTag(), previousValue, true);
	}

	bool ModulePlayer::ValidServiceTag(std::string const &tag) // 0x109F6BC0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ValidServiceTag@ModulePlayer@Modules@@SA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		static const std::unordered_set<std::string> filter = { "ANUS", "ARSE", "CLIT", "COCK", "COON", "CUNT", "DAGO", "DAMN", "DICK", "DIKE", "DYKE", "FUCK", "GOOK", "HEEB", "HELL", "HOMO", "JIZZ", "KIKE", "KUNT", "KYKE", "MICK", "MUFF", "PAKI", "PISS", "POON", "PUTO", "SHIT", "SHIZ", "SLUT", "SMEG", "SPIC", "TARD", "TITS", "TWAT", "WANK", "NIGA", "NIGG", "NIGR", "N1GG", "N1GR", "NIG", "N1G", "RAPE", "GAY", "GAYY" };
		return tag.length() > 2 && tag.length() < 5 && std::all_of(tag.begin(), tag.end(), [](auto c) { return c >= '0' && c <= 'Z'; }) && filter.find(tag) == filter.end();
	}

	bool ModulePlayer::ValidPlayerName(std::string const &name) // 0x109F6A50
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ValidPlayerName@ModulePlayer@Modules@@SA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

		if (name.length() == 0 || name.length() >= 16)
			return false;
		if (std::all_of(name.begin(), name.end(), isspace))
			return false;
		if (!name.empty() && name[0] == ' ')
			return false;
		return std::all_of(name.begin(), name.end(), [](auto c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ' || c == '_' || c == '-'; });
	}
}

/* ---------- private code */

std::string GetPayload() // 0x109F5540
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetPayload@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");

	rapidjson::Document dewrito = Utils::DewritoReader::Instance().GetDewritoJson();
	if (!dewrito.HasMember("playerRegister"))
		return "";
	std::string signature;
	char const *const sig = "signature";
	Utils::Cryptography::CreateRSASignature(Utils::Cryptography::ReformatKey(true, Modules::ModulePlayer::Instance().VarPlayerPrivKey->ValueString), (void *)sig, strlen(sig), signature);
	std::string pubKey;
	Server::Stats::GetStatsPublicKey(pubKey);
	std::string timestamp = Utils::Cryptography::GetEncryptedTimestamp(pubKey, false);
	rapidjson::StringBuffer s;
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	writer.StartObject();
	writer.Key("playerName");
	writer.String(Modules::ModulePlayer::Instance().VarPlayerName->ValueString.c_str());
	writer.Key("uid");
	char uid[17];
	player_format_uid(uid, Patches::PlayerUid::Get());
	writer.String(uid);
	writer.Key("pubkey");
	writer.String(Modules::ModulePlayer::Instance().VarPlayerPubKey->ValueString.c_str());
	writer.Key("serviceTag");
	writer.String(Modules::ModulePlayer::Instance().VarPlayerServiceTag->ValueString.c_str());
	writer.Key("timestamp");
	writer.String(timestamp.c_str());
	writer.Key("signature");
	writer.String(signature.c_str());
	s_player_emblem_configuration emblemConfig = {};
	if (Player::Emblems::ParseURL("emblems://emblem" + Modules::ModulePlayer::Instance().VarPlayerEmblem->ValueString, emblemConfig))
	{
		writer.Key("emblem");
		writer.StartObject();
		writer.Key("one");
		writer.String((emblemConfig.backgroundHex ? Player::Emblems::HexToStrHex(emblemConfig.backgroundColor) : std::to_string(emblemConfig.backgroundColor)).c_str());
		writer.Key("two");
		writer.String((emblemConfig.secondaryHex ? Player::Emblems::HexToStrHex(emblemConfig.secondaryColor) : std::to_string(emblemConfig.secondaryColor)).c_str());
		writer.Key("three");
		writer.String((emblemConfig.primaryHex ? Player::Emblems::HexToStrHex(emblemConfig.primaryColor) : std::to_string(emblemConfig.primaryColor)).c_str());
		writer.Key("fi");
		writer.Int(emblemConfig.foregroundIndex);
		writer.Key("bi");
		writer.Int(emblemConfig.backgroundIndex);
		writer.Key("fl");
		writer.Int(emblemConfig.iconEnabled ? 1 : 0);
		writer.EndObject();
	}
	writer.EndObject();
	return s.GetString();
}

bool SendRequest(std::string payload, std::string endpoint) // 0x109F6220
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SendRequest@@YA_NV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");

	HttpRequest req(L"ElDewrito/" + Utils::String::WidenString(Utils::Version::GetVersionString()), L"", L"");
	try
	{
		if (!req.SendRequest(Utils::String::WidenString(endpoint), L"POST", L"", L"", L"Content-Type: application/json\r\n", (void *)payload.c_str(), payload.length()))
		{
			Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Unable to connect");
		}
		std::wstring expected = L"HTTP/1.1 200 OK";
		if (req.responseHeader.length() < expected.length())
			return false;
	}
	catch (...)
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Network, Utils::LogLevel::Info, "Exception while getting player info");
	}
	return true;
}

bool CommandRegisterPlayer(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F2470
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandRegisterPlayer@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	rapidjson::Document dewrito = Utils::DewritoReader::Instance().GetDewritoJson();
	if (!dewrito.HasMember("playerRegister"))
		return false;
	std::string payload = GetPayload();
	if (!payload.empty())
	{
		std::string endpoint = dewrito["playerRegister"].GetString();
		std::thread thread(SendRequest, payload, endpoint);
		thread.detach();
		return true;
	}
	else
	{
		return false;
	}
}

bool VariablePlayerArmorUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F7350
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariablePlayerArmorUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	RefreshUiPlayer();
	return true;
}

bool VariablePlayerEmblem(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F7390
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariablePlayerEmblem@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	Player::PlayerEmblemDownload::Instance().UpdateLocalEmblem();

	return true;
}

bool VariablePlayerNameUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F74A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariablePlayerNameUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	Modules::ModulePlayer &modulePlayer = Modules::ModulePlayer::Instance();
	std::string name = modulePlayer.VarPlayerName->ValueString;
	if (!Modules::ModulePlayer::ValidPlayerName(name))
	{
		Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Warning, "Invalid player name!");
		returnInfo = "Invalid player name!";
		return false;
	}
	std::wstring nameW = Utils::String::WidenString(name);
	wcsncpy_s(modulePlayer.UserName, nameW.c_str(), _TRUNCATE);
	unsigned __int32 len = nameW.length();
	if (len < std::size(modulePlayer.UserName))
		wmemset(&modulePlayer.UserName[len], 0, std::size(modulePlayer.UserName) - len);
	return true;
}

void UpdateLocalRepresentation() // 0x109F69B0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?UpdateLocalRepresentation@@YAXXZ");

	Blam::Network::Session *activeSession = Blam::Network::GetActiveSession();

	if (activeSession && activeSession->IsEstablished())
	{
		__int32 (*Network_session_update_user_properties)(Blam::Network::Session *, __int32) = (__int32 (*)(Blam::Network::Session *, __int32))0x437b30;

		Network_session_update_user_properties(activeSession, 0);
	}
}

bool VariablePlayerServiceTagUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F7700
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariablePlayerServiceTagUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Arguments.size() == 0)
		return false;

	std::string value = Arguments[0];
	std::transform(value.begin(), value.end(), value.begin(), toupper);
	if (!Modules::ModulePlayer::ValidServiceTag(value))
	{
		returnInfo = "Invalid service tag!";
		return false;
	}

	Modules::ModulePlayer &modulePlayer = Modules::ModulePlayer::Instance();
	modulePlayer.VarPlayerServiceTag->ValueString = value;
	UpdateLocalRepresentation();
	return true;
}

bool VariablePlayerGenderUpdate(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F73E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?VariablePlayerGenderUpdate@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	if (Arguments.size() == 0 || (Arguments[0].compare("male") != 0 && Arguments[0].compare("female") != 0))
		return false;

	UpdateLocalRepresentation();

	return true;
}

bool CommandPlayerPrintUID(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F1C00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandPlayerPrintUID@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	unsigned long long uid = Patches::PlayerUid::Get();
	std::stringstream ss;
	ss << std::setw(16) << std::setfill('0') << std::hex << uid << std::dec << std::setw(0);
	returnInfo = "Player UID: 0x" + ss.str();
	return true;
}

bool TryParseFloat(std::string const &str, float *value) // 0x109F6800
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?TryParseFloat@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAM@Z");

	char* endp;
	*value = std::strtof(str.c_str(), &endp);

	return str.c_str() != endp;
}

bool CommandSetUiPlayerModelPosition(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F4730
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandSetUiPlayerModelPosition@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	real_vector3d position;
	if (Arguments.size() < 3 || !TryParseFloat(Arguments[0], &position.i) || !TryParseFloat(Arguments[1], &position.j) || !TryParseFloat(Arguments[2], &position.k))
	{
		returnInfo = "Invalid arguments";
		return false;
	}

	SetUiPlayerModelPosition(&position);
	return true;
}

bool CommandReturnCustomizationBiped(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F2770
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandReturnCustomizationBiped@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	s_scenario *const scnr = *g_scenario_definition;
	std::string preferredCharacterName = GetCurrentPreferredCharacter();
	s_game_globals const *game_globals = game_globals_get();
	s_mod_globals_definition const *mod_globals = mod_globals_get_definition();
	short bipedIndex = -1;
	for (__int32 i = 0; i < mod_globals->player_character_customizations.count; i++)
	{
		s_mod_globals_player_character_customization *character = nullptr;
		if (!mod_globals->player_character_customizations.try_get_element(i, &character))
			continue;
		if (strcmp(preferredCharacterName.c_str(), Blam::Cache::StringIDCache::GetCurrent()->GetString(game_globals->player_character_types[character->global_player_character_type_index].name)) == 0)
		{
			if (character->character_position_data.biped_name_index < scnr->object_names.count)
				bipedIndex = scnr->object_names[character->character_position_data.biped_name_index].scenario_datum_index;
			break;
		}
	}
	if (bipedIndex == -1)
	{
		returnInfo = "Missing Biped Position in Scnr. Cant return Biped";
		return true;
	}
	s_scenario_biped const &character = scnr->bipeds[bipedIndex];
	if (&character)
	{
		real_vector3d position = {};
		position.i = character.position.x;
		position.j = character.position.y;
		position.k = character.position.z;
		float rotation = character.rotation.yaw * 57.29578f;
		SetUiPlayerModelPosition(&position);
		SetUiPlayerModelRotation(rotation, 0.0f);
	}
	return true;
}

bool CommandSetRegionCamera(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F2C70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandSetRegionCamera@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	extern long find_player_character_by_name(char const *);
	s_game_globals const *game_globals = game_globals_get();
	s_mod_globals_definition const *mod_globals = mod_globals_get_definition();
	std::string preferredCharacterName = GetCurrentPreferredCharacter();
	long *ui_resolution = (long *)0x19106C8;
	float ui_aspect_ratio = (float)ui_resolution[0] / (float)ui_resolution[1];
	long (*const interface_get_closest_authored_ui_aspect_ratio)() = reinterpret_cast<long (*)()>(0xA9F980);
	long display_mode = interface_get_closest_authored_ui_aspect_ratio();
	rapidjson::StringBuffer jsonBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
	jsonWriter.StartObject();
	long character_type_index = find_player_character_by_name(preferredCharacterName.c_str());
	if (character_type_index != -1)
	{
		for (__int32 i = 0; i < mod_globals->player_character_customizations.count; i++)
		{
			s_mod_globals_player_character_customization *character = nullptr;
			if (!mod_globals->player_character_customizations.try_get_element(i, &character))
				continue;
			if (strcmp(preferredCharacterName.c_str(), Blam::Cache::StringIDCache::GetCurrent()->GetString(game_globals->player_character_types[character->global_player_character_type_index].name)) == 0)
			{
				for (__int32 x = 0; x < character->region_camera_scripts.count; x++)
				{
					s_mod_globals_character_region_script *region_script = nullptr;
					if (!character->region_camera_scripts.try_get_element(x, &region_script))
						continue;
					std::string region = (char const *)region_script->region_name;
					if (strcmp(Arguments[0].c_str(), region.c_str()) == 0)
					{
						std::string scriptWidescreen = (char const *)region_script->script_name_widescreen;
						std::string scriptStandard = (char const *)region_script->script_name_standard;
						if (scriptWidescreen.size() > 0 && display_mode == 0)
							Modules::CommandMap::Instance().ExecuteCommand("Game.ScenarioScript " + scriptWidescreen, false);
						else if (scriptStandard.size() > 0 && display_mode == 1)
							Modules::CommandMap::Instance().ExecuteCommand("Game.ScenarioScript " + scriptStandard, false);
						else if (scriptStandard.size() == 0 && display_mode == 1 && scriptWidescreen.size() > 0)
							Modules::CommandMap::Instance().ExecuteCommand("Game.ScenarioScript " + scriptWidescreen, false);
						float rotationAngle = region_script->biped_rotation;
						float rotationSpeed = region_script->rotation_duration;
						SetUiPlayerModelRotation(rotationAngle, rotationSpeed);
						jsonWriter.Key("success");
						jsonWriter.String("true");
						jsonWriter.Key("rotation");
						jsonWriter.String(std::to_string(rotationAngle).c_str());
						jsonWriter.EndObject();
						returnInfo = jsonBuffer.GetString();
						return true;
					}
				}
			}
		}
	}
	jsonWriter.Key("success");
	jsonWriter.String("false");
	jsonWriter.EndObject();
	returnInfo = jsonBuffer.GetString();
	return true;
}

bool CommandSetUiPlayerModelCustomization(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F35F0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandSetUiPlayerModelCustomization@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	s_game_globals const *game_globals = game_globals_get();
	s_mod_globals_definition const *mod_globals = mod_globals_get_definition();
	std::string preferredCharacterName = GetCurrentPreferredCharacter();
	s_scenario *const scnr = *g_scenario_definition;
	float const two_PI = *(float *)0x18A0F08;
	if (preferredCharacterName == "")
	{
		returnInfo = "ERROR: Game is not loaded yet";
		return true;
	}
	if (!scnr)
	{
		returnInfo = "ERROR: No scenario loaded";
		return true;
	}
	s_observer_result *observer_camera_data = eldorado::observer_try_and_get_camera(0);
	c_tag_block<s_scenario_cutscene_camera_point> cutscenes = scnr->cutscene_camera_points;
	long *ui_resolution = (long *)0x19106C8;
	float ui_aspect_ratio = (float)ui_resolution[0] / ui_resolution[1];
	long (*const interface_get_closest_authored_ui_aspect_ratio)() = reinterpret_cast<long (*)()>(0xA9F980);
	long display_mode = interface_get_closest_authored_ui_aspect_ratio();
	{
		long character_type_index = find_player_character_by_name(preferredCharacterName.c_str());
		if (character_type_index != -1)
		{
			s_game_globals_player_character_type const *character_type = game_globals->player_character_types.get_element(character_type_index);
			long representation_index = character_type->multiplayer_player_representation_block_index;
			if (representation_index < 0 || representation_index >= game_globals->PlayerRepresentation.count)
			{
				returnInfo = "ERROR: Matg PlayerCharacterTypes->MultiplayerRepresentation Index is not within a valid range";
				return true;
			}
			if (mod_globals->player_character_customizations.count <= 0)
			{
				returnInfo = "ERROR: modg is missing entries for PlayerCharacterCustomizations";
				return true;
			}
			for (__int32 i = 0; i < mod_globals->player_character_customizations.count; i++)
			{
				s_mod_globals_player_character_customization *character = nullptr;
				if (!mod_globals->player_character_customizations.try_get_element(i, &character))
					continue;
				if (strcmp(preferredCharacterName.c_str(), Blam::Cache::StringIDCache::GetCurrent()->GetString(game_globals->player_character_types[character->global_player_character_type_index].name)) == 0)
				{
					__int32 settings_camera_index = character->character_position_data.settings_camera_index;
					real_vector3d bipedOffset = *(real_vector3d *)character->character_position_data.relative_biped_position;
					float rotationOffset = character->character_position_data.relative_biped_rotation;
					real_point3d newBipedPoint = {};
					float rotationAngle = 0.0f;
					s_observer_result *camera = eldorado::observer_get_camera(0);
					real_point3d point = camera->position;
					if (display_mode == 1)
					{
						bipedOffset.j += -0.08f;
						bipedOffset.i += 0.09f;
					}
					if (Arguments.size() == 1 && Arguments[0] == "debug")
					{
						real_euler_angles3d euler;
						euler_angles3d_from_vectors3d(&euler, &observer_camera_data->forward, &observer_camera_data->up);
						float yaw = euler.yaw;
						if (yaw < 0.0f)
							yaw += two_PI;
						rotationAngle = yaw * 57.29578f + 204.072479 + rotationOffset;
						newBipedPoint = Player::CalculateBipedPosition(&point, &euler, 0.745f + bipedOffset.i, 0.324f + bipedOffset.j);
						bipedOffset.k = -0.0065f;
					}
					else if (settings_camera_index != -1)
					{
						rotationAngle = cutscenes[settings_camera_index].orientation.yaw * 57.29578f + 204.072479f + rotationOffset;
						newBipedPoint = Player::CalculateBipedPosition(&cutscenes[settings_camera_index].position, &cutscenes[settings_camera_index].orientation, 0.745f + bipedOffset.i, 0.324f + bipedOffset.j);
						bipedOffset.k += -0.0065f;
					}
					real_vector3d position = {};
					if (!(character->character_position_data.flags & 1))
					{
						if (display_mode == 0)
						{
							position.i = character->character_position_data.biped_position_widescreen.x;
							position.j = character->character_position_data.biped_position_widescreen.y;
							position.k = character->character_position_data.biped_position_widescreen.z;
						}
						else
						{
							position.i = character->character_position_data.biped_position_standard.x;
							position.j = character->character_position_data.biped_position_standard.y;
							position.k = character->character_position_data.biped_position_standard.z;
						}
						rotationAngle = character->character_position_data.biped_rotation;
					}
					else
					{
						position.i = newBipedPoint.x;
						position.j = newBipedPoint.y;
						position.k = newBipedPoint.z - 0.442742 + bipedOffset.k;
					}
					SetUiPlayerModelPosition(&position);
					float amt = 0.0f;
					if (Arguments.size() >= 1 && Arguments[0] == "exit_subcamera")
					{
						for (__int32 x = 0; x < character->region_camera_scripts.count; x++)
						{
							s_mod_globals_character_region_script *region_script = nullptr;
							if (!character->region_camera_scripts.try_get_element(x, &region_script))
								continue;
							std::string region = (char const *)region_script->region_name;
							if (strcmp("exit", region.c_str()) == 0)
							{
								rotationAngle += region_script->biped_rotation;
								amt = region_script->rotation_duration;
								break;
							}
						}
					}
					SetUiPlayerModelRotation(rotationAngle, amt);
					rapidjson::StringBuffer jsonBuffer;
					rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
					jsonWriter.StartObject();
					jsonWriter.Key("x");
					jsonWriter.String(std::to_string(position.i).c_str());
					jsonWriter.Key("y");
					jsonWriter.String(std::to_string(position.j).c_str());
					jsonWriter.Key("z");
					jsonWriter.String(std::to_string(position.k).c_str());
					jsonWriter.Key("rotation");
					jsonWriter.String(std::to_string(rotationAngle).c_str());
					bool canRotate = (character->character_position_data.flags & 8) != 0;
					jsonWriter.Key("rotatable");
					jsonWriter.Bool(canRotate);
					jsonWriter.EndObject();
					returnInfo = jsonBuffer.GetString();
					return true;
				}
			}
		}
	}
	returnInfo = "ERROR: PreferredCharacter Name " + preferredCharacterName + " does not match Modg->PlayerCharacterCustomizations->GlobalPlayerCharacterTypeIndex with Matg->PlayerCharacterTypes ";
	return true;
}

std::string rgb2hex(unsigned long color) // 0x109F9C00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?rgb2hex@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@K@Z");

	std::string result;
	char buff[255];

	sprintf_s(buff, "#%06X", color);
	result.append(buff);

	return result;
}

std::string ResolveString(unsigned __int32 unicTagIndex, unsigned __int32 strindId) // 0x109F6080
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ResolveString@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@II@Z");

	__int32 (*const ui_get_prefered_lanquage)() = reinterpret_cast<__int32 (*)()>(0x52FC40);
	char *(*const ui_resolve_string)(unsigned __int32, unsigned __int32, __int32) = reinterpret_cast<char *(*)(unsigned __int32, unsigned __int32, __int32)>(0x51E290);
	char *resolvedString = ui_resolve_string(unicTagIndex, strindId, ui_get_prefered_lanquage());
	if (strlen(resolvedString) == 0)
		return Blam::Cache::StringIDCache::GetCurrent()->GetString(strindId);
	return resolvedString;
}

bool CommandListCustomizationPermutations(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109EFDD0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandListCustomizationPermutations@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	long const armorStringshf2p = tag_find_by_name('unic', "hf2p\\armor_strings");
	long const armorStrings = tag_find_by_name('unic', "ui\\halox\\start_menu\\panes\\settings_appearance_model\\strings");
	long const colorStrings = tag_find_by_name('unic', "ui\\halox\\start_menu\\panes\\settings_appearance_colors\\strings");
	long const globalStrings = tag_find_by_name('unic', "ui\\global_strings\\global_strings");
	s_game_globals const *matg = game_globals_get();
	s_mod_globals_definition const *modg = mod_globals_get_definition();
	s_multiplayer_globals_definition *const mulg = (s_multiplayer_globals_definition *)tag_get('mulg', matg->MultiplayerGlobals.index);
	std::string preferredCharacterName = GetCurrentPreferredCharacter();
	__int32 player_character_customization_index = -1;
	for (__int32 i = 0; i < modg->player_character_customizations.count; i++)
	{
		s_mod_globals_player_character_customization *character = nullptr;
		if (!modg->player_character_customizations.try_get_element(i, &character))
			continue;
		if (!character || !matg->player_character_types[character->global_player_character_type_index].name)
			continue;
		if (strcmp(preferredCharacterName.c_str(), Blam::Cache::StringIDCache::GetCurrent()->GetString(matg->player_character_types[character->global_player_character_type_index].name)) == 0)
		{
			player_character_customization_index = i;
			break;
		}
	}
	rapidjson::StringBuffer jsonBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
	jsonWriter.StartObject();
	s_mod_globals_player_character_customization *currently_chosen_character = nullptr;
	if (player_character_customization_index != -1 && modg->player_character_customizations.try_get_element(player_character_customization_index, &currently_chosen_character) && currently_chosen_character && currently_chosen_character->character_name)
	{
		jsonWriter.Key("name");
		jsonWriter.String(Blam::Cache::StringIDCache::GetCurrent()->GetString(matg->player_character_types[currently_chosen_character->global_player_character_type_index].name));
		jsonWriter.Key("colors");
		jsonWriter.StartObject();
		char const *colorNamesKeys[5] = { "primary", "secondary", "tertiary", "quaternary", "quinary" };
		char const *colorDescriptionsKeys[5] = { "primaryDesc", "secondaryDesc", "tertiaryDesc", "quaternaryDesc", "quinaryDesc" };
		char const *colorDefaultKeys[5] = { "primaryDefault", "secondaryDefault", "tertiaryDefault", "quaternaryDefault", "quinaryDefault" };
		for (long i = 0; i < 5; i++)
		{
			if (currently_chosen_character->character_colors.valid_color_flags & (1 << i))
			{
				jsonWriter.Key(colorNamesKeys[i]);
				jsonWriter.String(ResolveString(colorStrings, ((s_mod_globals_player_character_colors::s_change_color_block *)currently_chosen_character->character_colors.colors)[i].name).c_str());
				jsonWriter.Key(colorDescriptionsKeys[i]);
				jsonWriter.String(ResolveString(colorStrings, ((s_mod_globals_player_character_colors::s_change_color_block *)currently_chosen_character->character_colors.colors)[i].description).c_str());
				jsonWriter.Key(colorDefaultKeys[i]);
				jsonWriter.String(rgb2hex(((s_mod_globals_player_character_colors::s_change_color_block *)currently_chosen_character->character_colors.colors)[i].default_color).c_str());
			}
		}
		jsonWriter.EndObject();
		jsonWriter.Key("regions");
		jsonWriter.StartArray();
		s_model_customization_selection *customization = nullptr;
		if (!mulg->universal->player_model.try_get_element(matg->player_character_types[modg->player_character_customizations[player_character_customization_index].global_player_character_type_index].multiplayer_armor_customization_block_index, &customization) || !customization)
			return false;
		for (__int32 i = 0; i < customization->regions.count; i++)
		{
			s_model_customization_player_region *region = nullptr;
			if (!customization->regions.try_get_element(i, &region) || !region)
				continue;
			bool hasVisiblePermutations = false;
			for (__int32 perm_index = 0; perm_index < region->permutations.count; perm_index++)
			{
				s_model_customization_player_region_permutation *permutation = nullptr;
				if (!region->permutations.try_get_element(perm_index, &permutation) || !permutation)
					continue;
				if (permutation->flags & 0x8000)
					continue;
				else
					hasVisiblePermutations = true;
			}
			if (!hasVisiblePermutations)
				continue;
			jsonWriter.StartObject();
			jsonWriter.Key("name");
			jsonWriter.String(ResolveString(armorStrings, region->name).c_str());
			jsonWriter.Key("type");
			jsonWriter.String(Blam::Cache::StringIDCache::GetCurrent()->GetString(region->name));
			jsonWriter.Key("permutations");
			jsonWriter.StartArray();
			for (__int32 perm_index = 0; perm_index < region->permutations.count; perm_index++)
			{
				s_model_customization_player_region_permutation *permutation = nullptr;
				if (!region->permutations.try_get_element(perm_index, &permutation) || !permutation)
					continue;
				if (permutation->flags & 0x8000)
					continue;
				jsonWriter.StartObject();
				jsonWriter.Key("permutation");
				if (!permutation->variants.count)
					jsonWriter.String("base");
				else
					jsonWriter.String(Blam::Cache::StringIDCache::GetCurrent()->GetString(permutation->variants->permutation_name));
				std::string perm_name = ResolveString(armorStrings, permutation->name);
				char *perm_stringid = Blam::Cache::StringIDCache::GetCurrent()->GetString(permutation->name);
				if (perm_name == perm_stringid)
					perm_name = ResolveString(armorStringshf2p, permutation->name);
				std::string desc_name = ResolveString(armorStrings, permutation->description);
				char *desc_stringid = Blam::Cache::StringIDCache::GetCurrent()->GetString(permutation->description);
				if (desc_name == desc_stringid)
					desc_name = ResolveString(armorStringshf2p, permutation->description);
				jsonWriter.Key("name");
				jsonWriter.String(perm_name.c_str());
				jsonWriter.Key("desc");
				jsonWriter.String(desc_name.c_str());
				jsonWriter.EndObject();
			}
			jsonWriter.EndArray();
			jsonWriter.EndObject();
		}
		jsonWriter.EndArray();
	}
	jsonWriter.Key("characters");
	jsonWriter.StartArray();
	for (__int32 i = 0; i < modg->player_character_customizations.count; i++)
	{
		s_mod_globals_player_character_customization *character = nullptr;
		if (!modg->player_character_customizations.try_get_element(i, &character))
			continue;
		if (!character || !matg->player_character_types[character->global_player_character_type_index].name)
			continue;
		if (static_cast<char>(matg->player_character_types[character->global_player_character_type_index].multiplayer_armor_customization_block_index) == -1)
			continue;
		jsonWriter.StartObject();
		jsonWriter.Key("name");
		jsonWriter.String(ResolveString(armorStrings, character->character_name).c_str());
		jsonWriter.Key("description");
		jsonWriter.String(ResolveString(armorStrings, character->character_description).c_str());
		jsonWriter.Key("type");
		jsonWriter.String(Blam::Cache::StringIDCache::GetCurrent()->GetString(matg->player_character_types[character->global_player_character_type_index].name));
		jsonWriter.EndObject();
	}
	jsonWriter.EndArray();
	jsonWriter.EndObject();
	returnInfo = jsonBuffer.GetString();
	return true;
}

bool CommandSetUiPlayerModelRotation(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F4870
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandSetUiPlayerModelRotation@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	float rotationAngle = 0.0f;
	float rotationTime = 0.0f;
	if (Arguments.size() < 1)
	{
		returnInfo = std::to_string(*(float *)0x194A66C);
		return true;
	}
	if (!TryParseFloat(Arguments[0], &rotationAngle))
	{
		returnInfo = "Invalid arguments";
		return false;
	}
	if (Arguments.size() > 1 && !TryParseFloat(Arguments[1], &rotationTime))
	{
		returnInfo = "Invalid arguments";
		return false;
	}
	SetUiPlayerModelRotation(rotationAngle, rotationTime);
	return true;
}

bool CommandSetCarryType(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F2BE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandSetCarryType@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	s_player_control_input_state *state = player_control_input_get(0);

	state->weapon_lowered = !state->weapon_lowered;
	return true;
}

bool GenerateTimestamp(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F5320
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GenerateTimestamp@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	Modules::ModulePlayer &modulePlayer = Modules::ModulePlayer::Instance();
	std::string encryptedString;
	long long now = time(nullptr);
	tm *now_tm = gmtime(&now);
	char buf[42];
	strftime(buf, sizeof(buf), "%Y%m%d %X", now_tm);
	Utils::Cryptography::PrivateEncrypt(Utils::Cryptography::ReformatKey(true, modulePlayer.VarPlayerPrivKey->ValueString), buf, strlen(buf), encryptedString);
	returnInfo = encryptedString;
	return true;
}

std::string GenerateRandomServiceTag() // 0x109F5180
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GenerateRandomServiceTag@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");

	std::string tag(4, 0);
	tag[0] = rand() % 26 + 'A';
	tag[1] = rand() % 10 + '0';
	tag[2] = rand() % 10 + '0';
	tag[3] = rand() % 10 + '0';
	return tag;
}

bool CommandReloadCustomization(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F2730
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandReloadCustomization@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	Player::CPlayerCharacterSystem::ReloadCustomizations();

	return true;
}

bool CommandTestCustomization(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F4A50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandTestCustomization@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	Player::CPlayerCustomizationDB &db = Player::CPlayerCustomizationDB::Instance();
	Player::SPersistentCharacterCustomization customization1;
	customization1.colors["primary"] = "#ff0000";
	customization1.permutations["helmet"] = "mp_ninja";
	if (!db.SetCharacterCustomization("masterchief", customization1))
	{
		returnInfo = "There was a problem setting the customization";
		return false;
	}
	Player::SPersistentCharacterCustomization customization2;
	customization2.colors = { { "primary", "#ff0000" }, { "secondary", "#00ff00" } };
	customization2.permutations = { { "hlmet", "mp_ninja" }, { "body", "mp_bungie" } };
	if (!db.SetCharacterCustomization("masterchief", customization2))
	{
		returnInfo = "There was a problem setting the customization";
		return false;
	}
	if (!db.SetCharacterColor("masterchief", "primary", "#ff0000"))
	{
		returnInfo = "There was a problem setting the value";
		return false;
	}
	if (!db.SetCharacterPermutation("masterchief", "helmet", "mp_ninja"))
	{
		returnInfo = "There was a problem setting the value";
		return false;
	}
	db.Save("test.json");
	Player::CPlayerCharacterSystem::ReloadCustomizations();
	return true;
}

bool CommandKillSelf(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109EFD00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandKillSelf@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	Server::Chat::SendGlobalMessage("!kill");

	return true;
}

bool CommandPlayerArmor(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F1400
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandPlayerArmor@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	std::string preferredCharacterName = GetCurrentPreferredCharacter();
	Player::CPlayerCustomizationDB &db = Player::CPlayerCustomizationDB::Instance();
	if (Arguments.size() == 1)
	{
		Player::SPersistentCharacterCustomization customization;
		if (!db.GetCharacterCustomization(preferredCharacterName, customization))
		{
			returnInfo = "Failed to get character";
			return true;
		}
		returnInfo = customization.permutations[Arguments[0]].c_str();
		return true;
	}
	else if (Arguments.size() == 0 || Arguments.size() > 2)
	{
		returnInfo = "Invalid arguments";
		return true;
	}
	if (!db.SetCharacterPermutation(preferredCharacterName, Arguments[0], Arguments[1]))
	{
		returnInfo = "There was a problem setting the value";
		return false;
	}
	db.Save();
	RefreshUiPlayer();
	Player::CPlayerCharacterSystem::ReloadCustomizations();
	return true;
}

bool CommandPlayerColor(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F1720
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandPlayerColor@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	std::string preferredCharacterName = GetCurrentPreferredCharacter();
	Player::CPlayerCustomizationDB &db = Player::CPlayerCustomizationDB::Instance();
	if (Arguments.size() == 1)
	{
		Player::SPersistentCharacterCustomization customization;
		if (!db.GetCharacterCustomization(preferredCharacterName, customization))
		{
			returnInfo = "Failed to get character";
			return true;
		}
		returnInfo = customization.colors[Arguments[0]].c_str();
		return true;
	}
	else if (Arguments.size() == 0 || Arguments.size() > 2)
	{
		returnInfo = "Invalid arguments";
		return true;
	}
	if (!db.SetCharacterColor(preferredCharacterName, Arguments[0], Arguments[1]))
	{
		returnInfo = "There was a problem setting the value";
		return false;
	}
	db.Save();
	RefreshUiPlayer();
	Player::CPlayerCharacterSystem::ReloadCustomizations();
	return true;
}

bool CommandPreferredCharacter(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F1EA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandPreferredCharacter@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	bool (*const game_is_mainmenu)() = reinterpret_cast<bool (*)()>(0x531E90);
	Player::CPlayerCustomizationDB &db = Utils::Singleton<Player::CPlayerCustomizationDB>::Instance();
	std::string modName = c_mod_system::get_current_package_filename(kMainMenu);
	std::string modHash = c_mod_system::get_current_mainmenu_package_hash();
	bool modIsCharacterType = false;
	unsigned char hash[20];
	Utils::String::HexStringToBytes(modHash, hash, 20);
	c_mod_package_manager::s_entry entry;
	if (c_mod_system::get_package_manager().find_package_by_hash(hash, &entry))
		modIsCharacterType = entry.modtype.character;
	if (!game_is_mainmenu())
	{
		returnInfo = "Must be at mainmenu";
		return false;
	}
	if (Arguments.size() == 1)
	{
		std::string const &preferredCharacterName = Arguments[0];
		if (modName.empty() || !modName.empty() && !modIsCharacterType)
			modName = "default";
		db.SetPreferredCharacter(modName, preferredCharacterName);
		db.Save();
	}
	else
	{
		std::string character = GetCurrentPreferredCharacter();
		if (!modName.empty() && db.GetPreferredCharacter(character).empty())
		{
			if (!modIsCharacterType)
				modName = "default";
			db.SetPreferredCharacter(modName, character);
		}
		else if (modName.empty() && db.GetPreferredCharacter(character).empty())
		{
			db.SetPreferredCharacter("default", character);
		}
		db.Save();
		returnInfo = character;
		return true;
	}
	UpdateLocalRepresentation();
	RefreshUiPlayer();
	clearCachedCharacter();
	return true;
}

static bool TryParseInt(std::string const &str, __int32 *value) // 0x109F68D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?TryParseInt@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAH@Z");

	if (str.length() == 0)
		return false;

	auto c_str = str.c_str();
	char* endp;

	*value = std::strtol(c_str, &endp, 10);

	return endp != c_str;
}

bool CommandPlayerEmote(std::vector<std::string> const &Arguments, std::string &returnInfo) // 0x109F1A40
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?CommandPlayerEmote@@YA_NABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@AAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@2@@Z");

	bool (*const game_is_mainmenu)() = reinterpret_cast<bool (*)()>(0x531E90);
	unsigned long playerIndex = ((unsigned long (__cdecl *)(long))0x589C30)(0);
	if (!((bool (__cdecl *)())0x5314B0)() || playerIndex == -1 || game_is_mainmenu())
	{
		returnInfo = "Command unavailable";
		return false;
	}

	if (!Modules::ModuleServer::Instance().VarServerEmotesEnabledClient->ValueInt)
	{
		returnInfo = "Emotes are disabled on this server";
		return false;
	}

	if (Arguments.size() == 0)
	{
		Web::Ui::WebEmote::Show();
		return true;
	}
	else if (Arguments.size() != 1)
	{
		returnInfo = "Bad Arguments";
		return false;
	}

	__int32 emoteIndex = -1;
	if (!TryParseInt(Arguments[0], &emoteIndex))
	{
		returnInfo = "Bad Arguments";
		return false;
	}

	return Player::CPlayerEmotes::RequestStartEmote(emoteIndex);
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
