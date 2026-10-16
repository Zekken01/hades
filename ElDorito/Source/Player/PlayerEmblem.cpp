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
		void set_emblem_texture(long sampler, long player_index, bool use_generic, bool screen_emblem) // 0x107F0CB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?set_emblem_texture@PlayerEmblem@Player@@YAXJJ_N0@Z");

			if (!Player::PlayerEmblemDownload::Instance().IsAvailable())
			{
				return;
			}

			IDirect3DDevice9 *device = *reinterpret_cast<IDirect3DDevice9 **>(0x50DADDC);
			bool *g_sampler_gamma_correction_array = reinterpret_cast<bool *>(0x50DB200);
			unsigned long stage = sampler >= 16 ? sampler + 0xF1 : sampler;
			IDirect3DTexture9 *texture = Player::PlayerEmblemDownload::Instance().GetPlayerEmblem(player_index, use_generic);
			device->SetTexture(stage, texture);
			if (g_sampler_gamma_correction_array[sampler] != screen_emblem)
			{
				g_sampler_gamma_correction_array[sampler] = screen_emblem;
				device->SetSamplerState(sampler, D3DSAMP_SRGBTEXTURE, screen_emblem);
			}
		}

		void set_emblem_customization_biped(long sampler, bool use_generic, bool screen_emblem) // 0x107F0C50
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?set_emblem_customization_biped@PlayerEmblem@Player@@YAXJ_N0@Z");

			set_emblem_texture(sampler, 16, use_generic, screen_emblem);
		}
	}
}

/* ---------- private code */

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Player::PlayerEmblemDownload & Utils::Singleton<Player::PlayerEmblemDownload>::Instance();
