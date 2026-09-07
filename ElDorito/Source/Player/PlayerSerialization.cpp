/* ---------- headers */

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
#include "Player/PlayerCharacterSystem.hpp"
#include "Utils/Bits.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <tuple>
#include <type_traits>
#include <utility>

/* ---------- forward declarations */

struct s_player_appearance;
struct s_player_character_customiztion;
struct s_player_configuration_from_host;
struct s_player_emblem_configuration;
struct s_player_model_customization;
namespace Blam
{
	class BitStream;
}

namespace Utils {}
using namespace ::Utils;
namespace Player {}
using namespace ::Player;
namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Player
{
	extern void player_model_customization_encode(Blam::BitStream *stream, s_player_model_customization const *customization);
	extern bool player_model_customization_decode(Blam::BitStream *stream, s_player_model_customization *customization);
	extern void player_emblem_configuration_encode(Blam::BitStream *stream, s_player_emblem_configuration const *emblem);
	extern void player_emblem_configuration_decode(Blam::BitStream *stream, s_player_emblem_configuration *emblem);
	extern void player_appearance_encode(Blam::BitStream *stream, s_player_appearance const *appearance);
	extern bool player_appearance_decode(Blam::BitStream *stream, s_player_appearance *appearance);
	extern bool player_configuration_host_decode(Blam::BitStream *stream, s_player_configuration_from_host *configuration, e_player_configuration_encoding_type encoding_type);
	extern void player_configuration_host_encode(Blam::BitStream *stream, s_player_configuration_from_host *configuration, e_player_configuration_encoding_type encoding_type);
}

_inline bool valid_team_index(long team_index);

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Player
{
	_extern void _sub_107F09C0(Blam::BitStream *, s_player_model_customization const *);
	void player_model_customization_encode(Blam::BitStream *stream, s_player_model_customization const *customization) // 0x107F09C0
	{
		mangled_x86(MANGLED_TODO, "?player_model_customization_encode@Player@@YAXPAVBitStream@Blam@@PBUs_player_model_customization@@@Z");
		// s_player_model_customization const *customization;
		{
			// __int32 i;
		}
		{
		}
		todo("implement");
		_sub_107F09C0(stream, customization);
	}

	_extern bool _sub_107F0900(Blam::BitStream *, s_player_model_customization *);
	bool player_model_customization_decode(Blam::BitStream *stream, s_player_model_customization *customization) // 0x107F0900
	{
		mangled_x86(MANGLED_TODO, "?player_model_customization_decode@Player@@YA_NPAVBitStream@Blam@@PAUs_player_model_customization@@@Z");
		// s_player_model_customization *customization;
		{
			// __int32 i;
		}
		{
		}
		todo("implement");
		bool __result = _sub_107F0900(stream, customization);
		return __result;
	}

	_extern void _sub_107F0800(Blam::BitStream *, s_player_emblem_configuration const *);
	void player_emblem_configuration_encode(Blam::BitStream *stream, s_player_emblem_configuration const *emblem) // 0x107F0800
	{
		mangled_x86(MANGLED_TODO, "?player_emblem_configuration_encode@Player@@YAXPAVBitStream@Blam@@PBUs_player_emblem_configuration@@@Z");
		// s_player_emblem_configuration const *emblem;
		todo("implement");
		_sub_107F0800(stream, emblem);
	}

	_extern void _sub_107F0710(Blam::BitStream *, s_player_emblem_configuration *);
	void player_emblem_configuration_decode(Blam::BitStream *stream, s_player_emblem_configuration *emblem) // 0x107F0710
	{
		mangled_x86(MANGLED_TODO, "?player_emblem_configuration_decode@Player@@YAXPAVBitStream@Blam@@PAUs_player_emblem_configuration@@@Z");
		// s_player_emblem_configuration *emblem;
		todo("implement");
		_sub_107F0710(stream, emblem);
	}

	_extern void _sub_107F02F0(Blam::BitStream *, s_player_appearance const *);
	void player_appearance_encode(Blam::BitStream *stream, s_player_appearance const *appearance) // 0x107F02F0
	{
		mangled_x86(MANGLED_TODO, "?player_appearance_encode@Player@@YAXPAVBitStream@Blam@@PBUs_player_appearance@@@Z");
		// s_player_appearance const *appearance;
		{
			// __int32 i;
			{
				// s_player_character_customiztion const &character;
			}
		}
		todo("implement");
		_sub_107F02F0(stream, appearance);
	}

	_extern bool _sub_107F0150(Blam::BitStream *, s_player_appearance *);
	bool player_appearance_decode(Blam::BitStream *stream, s_player_appearance *appearance) // 0x107F0150
	{
		mangled_x86(MANGLED_TODO, "?player_appearance_decode@Player@@YA_NPAVBitStream@Blam@@PAUs_player_appearance@@@Z");
		// s_player_appearance *appearance;
		{
			// __int32 i;
			{
				// s_player_character_customiztion &character;
			}
		}
		todo("implement");
		bool __result = _sub_107F0150(stream, appearance);
		return __result;
	}

	_extern bool _sub_107F0480(Blam::BitStream *, s_player_configuration_from_host *, e_player_configuration_encoding_type);
	bool player_configuration_host_decode(Blam::BitStream *stream, s_player_configuration_from_host *configuration, e_player_configuration_encoding_type encoding_type) // 0x107F0480
	{
		mangled_x86(MANGLED_TODO, "?player_configuration_host_decode@Player@@YA_NPAVBitStream@Blam@@PAUs_player_configuration_from_host@@W4e_player_configuration_encoding_type@@@Z");
		// e_player_configuration_encoding_type encoding_type;
		todo("implement");
		bool __result = _sub_107F0480(stream, configuration, encoding_type);
		return __result;
	}

	_extern void _sub_107F05E0(Blam::BitStream *, s_player_configuration_from_host *, e_player_configuration_encoding_type);
	void player_configuration_host_encode(Blam::BitStream *stream, s_player_configuration_from_host *configuration, e_player_configuration_encoding_type encoding_type) // 0x107F05E0
	{
		mangled_x86(MANGLED_TODO, "?player_configuration_host_encode@Player@@YAXPAVBitStream@Blam@@PAUs_player_configuration_from_host@@W4e_player_configuration_encoding_type@@@Z");
		// e_player_configuration_encoding_type encoding_type;
		todo("implement");
		_sub_107F05E0(stream, configuration, encoding_type);
	}
}

/* ---------- private code */

_extern bool _sub_107F0A80(long);
_inline bool valid_team_index(long team_index) // 0x107F0A80
{
	// `anonymous-namespace'::valid_team_index
	// long team_index;
	todo("implement");
	bool __result = _sub_107F0A80(team_index);
	return __result;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template unsigned __int32 Blam::BitStream::ReadUnsigned<unsigned int>(__int32);
template unsigned char Blam::BitStream::ReadUnsigned<unsigned char>(__int32);
template unsigned char Blam::BitStream::ReadUnsigned<unsigned char>(unsigned char, unsigned char);
template unsigned long Blam::BitStream::Read<unsigned long>(__int32);
template unsigned long Blam::BitStream::ReadUnsigned<unsigned long>(unsigned long, unsigned long);
template unsigned short Blam::BitStream::Read<unsigned short>(__int32);
template void Blam::BitStream::Write<long>(long, long, long);
template void Blam::BitStream::Write<unsigned char>(unsigned char, unsigned char, unsigned char);
template void Blam::BitStream::Write<unsigned int>(unsigned __int32, __int32);
template void Blam::BitStream::Write<unsigned long>(unsigned long, __int32);
template void Blam::BitStream::WriteUnsigned<bool>(bool, __int32);
template void Blam::BitStream::WriteUnsigned<unsigned __int64>(unsigned long long, __int32);
template void Blam::BitStream::WriteUnsigned<unsigned char>(unsigned char, unsigned char, unsigned char);
template void Blam::BitStream::WriteUnsigned<unsigned int>(unsigned __int32, __int32);
template void Blam::BitStream::WriteUnsigned<unsigned long>(unsigned long, unsigned long, unsigned long);
