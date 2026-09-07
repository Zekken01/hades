/* ---------- headers */

#include "hades/hades.h"

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
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
#include "Player/PlayerEmblemDownload.hpp"
#include "Player/PlayerEmblemGenerator.hpp"
#include "Utils/Singleton.hpp"

#include <d3dx9core.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>

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
#include <limits>
#include <map>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

namespace Player
{
	class PlayerEmblemDownload;
}

namespace Utils {}
using namespace ::Utils;
namespace Player {}
using namespace ::Player;
namespace Http {}
using namespace ::Http;
namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

namespace Utils
{
	Player::PlayerEmblemDownload *Utils::Singleton<Player::PlayerEmblemDownload>::m_instance; // 0x1138F3DC
}

/* ---------- private variables */

/* ---------- public code */

namespace Player
{
	namespace PlayerEmblem
	{
		_extern void _sub_107F0CB0(long, long, bool, bool);
		void set_emblem_texture(long sampler, long player_index, bool use_generic, bool screen_emblem) // 0x107F0CB0
		{
			mangled_x86(MANGLED_TODO, "?set_emblem_texture@PlayerEmblem@Player@@YAXJJ_N0@Z");
			// bool screen_emblem;
			// IDirect3DDevice9 *device;
			// unsigned long stage;
			// bool *g_sampler_gamma_correction_array;
			// IDirect3DTexture9 *texture;
			// function call : HRESULT (unsigned long, IDirect3DBaseTexture9 *)
			// function call : HRESULT (unsigned long, _D3DSAMPLERSTATETYPE, unsigned long)
			todo("implement");
			_sub_107F0CB0(sampler, player_index, use_generic, screen_emblem);
		}

		_extern void _sub_107F0C50(long, bool, bool);
		void set_emblem_customization_biped(long sampler, bool use_generic, bool screen_emblem) // 0x107F0C50
		{
			mangled_x86(MANGLED_TODO, "?set_emblem_customization_biped@PlayerEmblem@Player@@YAXJ_N0@Z");
			// bool screen_emblem;
			todo("implement");
			_sub_107F0C50(sampler, use_generic, screen_emblem);
		}
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Player::PlayerEmblemDownload & Utils::Singleton<Player::PlayerEmblemDownload>::Instance();
