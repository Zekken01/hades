/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Player/PlayerCustomizationExtension.hpp"
#include "Pointer.hpp"
#include "Utils/Singleton.hpp"

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
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

namespace Patches
{
	namespace Network
	{
		class PlayerPropertiesExtender;
		class PlayerPropertiesExtensionBase;
	}
}
namespace Player
{
	class PlayerCustomizationExtensions;
}

namespace Utils {}
using namespace ::Utils;
namespace Player {}
using namespace ::Player;
namespace Player
{
	namespace PlayerPodium {}
	using namespace Player::PlayerPodium;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Sprint {}
	using namespace Patches::Sprint;
	namespace PlayerScale {}
	using namespace Patches::PlayerScale;
	namespace Network {}
	using namespace Patches::Network;
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
	namespace Player
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

namespace Utils
{
	Patches::Network::PlayerPropertiesExtender *Utils::Singleton<Patches::Network::PlayerPropertiesExtender>::m_instance; // 0x124083A4
}

/* ---------- private variables */

/* ---------- public code */

namespace Patches
{
	namespace Player
	{
		_extern void _sub_108D9400();
		void ApplyAll() // 0x108D9400
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Player@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_108D9400();
		}
	}
}

namespace Player
{
	extern PlayerCustomizationExtensions* _sub_108D8C10(::Player::PlayerCustomizationExtensions *const);
	_inline PlayerCustomizationExtensions::PlayerCustomizationExtensions() // 0x108D8C10
	{
		mangled_x86(MANGLED_TODO, "??0PlayerCustomizationExtensions@Player@@QAE@XZ");
		// Player::PlayerCustomizationExtensions *const this;
		compiler_generated();
		todo("implement");
		_sub_108D8C10(this);
	}
}

namespace Patches
{
	namespace Network
	{
		extern PlayerPropertiesExtender* _sub_108D8C70(Patches::Network::PlayerPropertiesExtender *const);
		_inline PlayerPropertiesExtender::PlayerPropertiesExtender() // 0x108D8C70
		{
			mangled_x86(MANGLED_TODO, "??0PlayerPropertiesExtender@Network@Patches@@QAE@XZ");
			// Patches::Network::PlayerPropertiesExtender *const this;
			compiler_generated();
			todo("implement");
			_sub_108D8C70(this);
		}

		extern PlayerPropertiesExtensionBase* _sub_108D8CC0(Patches::Network::PlayerPropertiesExtensionBase *const);
		_inline PlayerPropertiesExtensionBase::PlayerPropertiesExtensionBase() // 0x108D8CC0
		{
			mangled_x86(MANGLED_TODO, "??0PlayerPropertiesExtensionBase@Network@Patches@@QAE@XZ");
			// Patches::Network::PlayerPropertiesExtensionBase *const this;
			compiler_generated();
			todo("implement");
			_sub_108D8CC0(this);
		}
	}
}

namespace Player
{
	_extern void _sub_108D8ED0(::Player::PlayerCustomizationExtensions *const);
	_inline PlayerCustomizationExtensions::~PlayerCustomizationExtensions() // 0x108D8ED0
	{
		mangled_x86(MANGLED_TODO, "??1PlayerCustomizationExtensions@Player@@UAE@XZ");
		// Player::PlayerCustomizationExtensions *const this;
		compiler_generated();
		todo("implement");
		_sub_108D8ED0(this);
	}
}

/* ---------- private code */
