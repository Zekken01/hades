/* ---------- headers */

#include "Player/PlayerCustomizationExtension.hpp"
#include "hades/hades.h"

#include "Blam/BitStream.hpp"
#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "Modules/ModulePlayer.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Player/PlayerCharacterSystem.hpp"
#include "Utils/Singleton.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <limits>
#include <locale>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct s_player_appearance;
struct s_player_configuration;
struct s_player_emblem_configuration;
struct s_player_model_customization;
namespace Blam
{
	class BitStream;
}
namespace Modules
{
	class ModulePlayer;
}
namespace Player
{
	class PlayerCustomizationExtensions;
}

namespace Utils {}
using namespace ::Utils;
namespace Modules {}
using namespace ::Modules;
namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace Emblems {}
	using namespace Player::Emblems;
}

namespace Patches {}
using namespace ::Patches;
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

namespace Player { extern void player_appearance_encode(Blam::BitStream *stream, s_player_appearance const *appearance); }  // hades: added for 0x107DB680

namespace Player { extern bool player_appearance_decode(Blam::BitStream *stream, s_player_appearance *appearance); }  // hades: added for 0x107DB390

namespace Player
{
	extern bool ValidServiceTag(wchar_t (&tag)[5]);
	extern unsigned __int32 ParseColor(std::string const &value);
	extern void SanitizeModelCustomization(s_player_model_customization *customization);
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Player
{
	bool ValidServiceTag(wchar_t (&tag)[5]) // 0x107DB6E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ValidServiceTag@Player@@YA_NAAY04_W@Z");
		// wchar_t (&tag)[5];
			// __int32 i;

		for (long i = 0; i < 4; i++)
		{
			if (tag[i] == 0 && i < 3)
				return false;

			if (tag[i] != 0 && (tag[i] < '0' || tag[i] > 'Z'))
				return false;
		}

		return true;
	}

	_extern unsigned __int32 _sub_107DB3F0(std::string const &);
	unsigned __int32 ParseColor(std::string const &value) // 0x107DB3F0
	{
		mangled_x86(MANGLED_TODO, "?ParseColor@Player@@YAIABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
		// static ...; // 0x107DB5A7
		// static ...; // 0x107DB59C
		// static ...; // 0x107DB584
		// static ...; // 0x107DB57C
		// std::string const &value;
		// std::regex expression;
		// std::match_results<char const *,std::allocator<std::sub_match<char const *> > > what;
		todo("implement");
		unsigned __int32 __result = _sub_107DB3F0(value);
		return __result;
	}

	void PlayerCustomizationExtensions::Serialize(Blam::BitStream *stream, s_player_appearance const &data) // 0x107DB680
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Serialize@PlayerCustomizationExtensions@Player@@MAEXPAVBitStream@Blam@@ABUs_player_appearance@@@Z");
		// s_player_appearance const &data;

		Player::player_appearance_encode(stream, &data);
	}

	void PlayerCustomizationExtensions::Deserialize(Blam::BitStream *stream, s_player_appearance *out) // 0x107DB390
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Deserialize@PlayerCustomizationExtensions@Player@@MAEXPAVBitStream@Blam@@PAUs_player_appearance@@@Z");
		// s_player_appearance *out;

		Player::player_appearance_decode(stream, out);
	}

	_extern void _sub_107DB030(::Player::PlayerCustomizationExtensions *const, __int32, s_player_appearance *);
	void PlayerCustomizationExtensions::BuildData(__int32 playerIndex, s_player_appearance *out) // 0x107DB030
	{
		mangled_x86(MANGLED_TODO, "?BuildData@PlayerCustomizationExtensions@Player@@MAEXHPAUs_player_appearance@@@Z");
		// static ...; // 0x107DB2BC
		// Player::PlayerCustomizationExtensions *const this;
		// __int32 playerIndex;
		// s_player_appearance *out;
		// Modules::ModulePlayer const &modulePlayer;
		// s_player_emblem_configuration emblemConfig;
		todo("implement");
		_sub_107DB030(this, playerIndex, out);
	}

	void SanitizeModelCustomization(s_player_model_customization *customization) // 0x107DB620
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SanitizeModelCustomization@Player@@YAXPAUs_player_model_customization@@@Z");
		// s_player_model_customization *customization;
			// __int32 i;

		for (__int32 i = 0; i < 5; i++)
		{
			customization->colors[i] &= 0xFFFFFF;
		}
	}

	_extern void _sub_107DAD70(::Player::PlayerCustomizationExtensions *const, __int32, s_player_configuration *, s_player_appearance const &);
	void PlayerCustomizationExtensions::ApplyData(__int32 playerIndex, s_player_configuration *properties, s_player_appearance const &data) // 0x107DAD70
	{
		mangled_x86(MANGLED_TODO, "?ApplyData@PlayerCustomizationExtensions@Player@@MAEXHPAUs_player_configuration@@ABUs_player_appearance@@@Z");
		// s_player_appearance const &data;
		{
			// __int32 i;
		}
		todo("implement");
		_sub_107DAD70(this, playerIndex, properties, data);
	}
}

/* ---------- private code */
