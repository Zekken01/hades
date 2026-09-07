/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/interface/user_interface_multiplayer_game_settings.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/static_array.inl"
#include "Blam/networking/session/network_session_membership.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "mods/FileSystem/ModPackageFileSystemView.hpp"
#include "mods/mod_identifier.hpp"
#include "mods/mod_package_manager.hpp"
#include "mods/new/IModManager.hpp"
#include "mods/user_interface_mods.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Pointer.hpp"

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
#include <istream>
#include <iterator>
#include <limits>
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

class IMod;
class IModListener;
class c_user_interface_mods_player_character_data;
struct c_game_engine_assault_variant;
struct c_game_engine_base_variant;
struct c_game_engine_ctf_variant;
struct c_game_engine_infection_variant;
struct c_game_engine_juggernaut_variant;
struct c_game_engine_king_variant;
struct c_game_engine_oddball_variant;
struct c_game_engine_sandbox_variant;
struct c_game_engine_slayer_variant;
struct c_game_engine_territories_variant;
struct c_game_engine_vip_variant;
struct c_gui_screen_game_options;
namespace
{
	union u_game_engine_variant;
	class c_user_interface_player_model_text_value_pair_proxy;
	class c_user_interface_player_model_set_text_value_pair_proxy;
	class ModListener;
}

namespace Utils {}
using namespace ::Utils;
namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace GameEngineSettings {}
	using namespace Patches::GameEngineSettings;
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

namespace
{
	union u_game_engine_variant
	{
		c_game_engine_base_variant base; // 0x0
		c_game_engine_ctf_variant ctf; // 0x0
		c_game_engine_slayer_variant slayer; // 0x0
		c_game_engine_oddball_variant oddball; // 0x0
		c_game_engine_king_variant koth; // 0x0
		c_game_engine_sandbox_variant sandbox; // 0x0
		c_game_engine_vip_variant vip; // 0x0
		c_game_engine_juggernaut_variant juggernaut; // 0x0
		c_game_engine_territories_variant territories; // 0x0
		c_game_engine_assault_variant assault; // 0x0
		c_game_engine_infection_variant infection; // 0x0
	};
	static_assert(sizeof(u_game_engine_variant) == 592, "Invalid u_game_engine_variant size");

	class c_user_interface_player_model_text_value_pair_proxy :
		public s_user_interface_text_value_pair_proxy<16>
	{
	public:
		c_user_interface_player_model_text_value_pair_proxy(c_user_interface_mods_player_character_data *);
		void update(c_gui_screen_game_options *);
		bool try_get_string(unsigned long, wchar_t *);
	private:
		c_user_interface_mods_player_character_data *m_data; // 0x15C
	};
	static_assert(sizeof(c_user_interface_player_model_text_value_pair_proxy) == 352, "Invalid c_user_interface_player_model_text_value_pair_proxy size");

	//@@anonymous-namespace@@
	class c_user_interface_player_model_set_text_value_pair_proxy :
		public s_user_interface_text_value_pair_proxy<8>
	{
	public:
		c_user_interface_player_model_set_text_value_pair_proxy(c_user_interface_mods_player_character_data *);
		void update(c_gui_screen_game_options *);
		bool try_get_string(unsigned long, wchar_t *);
	private:
		c_user_interface_mods_player_character_data *m_data; // 0x15C
	};
	static_assert(sizeof(c_user_interface_player_model_set_text_value_pair_proxy) == 352, "Invalid c_user_interface_player_model_set_text_value_pair_proxy size");

	//@@anonymous-namespace@@
	class ModListener :
		public IModListener
	{
	private:
		virtual void OnModChanged(EModIndex, IMod *);
	public:
		ModListener(ModListener &); /* compiler_generated() */
		ModListener(ModListener const &); /* compiler_generated() */
		ModListener(); /* compiler_generated() */
		virtual ~ModListener(); /* compiler_generated() */
		ModListener &operator=(ModListener &); /* compiler_generated() */
		ModListener &operator=(ModListener const &); /* compiler_generated() */
	};
	static_assert(sizeof(ModListener) == 4, "Invalid ModListener size");
}
/* ---------- prototypes */

namespace Patches
{
	namespace GameEngineSettings
	{
		extern void ApplyAll();
	}
}

/* ---------- globals */

/* ---------- private variables */

namespace
{
	extern c_user_interface_mods_player_character_data g_player_characte_data; // 0x12464BA8
	extern bool g_player_model_proxy_dirty; // 0x113547A0
}
/* ---------- public code */

namespace Patches
{
	namespace GameEngineSettings
	{
		_extern void _sub_10A9EA80();
		void ApplyAll() // 0x10A9EA80
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@GameEngineSettings@Patches@@YAXXZ");
			// procedure flags: nofpo
			// function call : void (IModListener *)
			todo("implement");
			_sub_10A9EA80();
		}
	}
}

/* ---------- private code */
