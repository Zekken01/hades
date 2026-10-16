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

template auto Blam::BitStream::Read<unsigned short>(__int32);
template auto Blam::BitStream::Read<unsigned long>(__int32);

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
	void player_model_customization_encode(Blam::BitStream *stream, s_player_model_customization const *customization) // 0x107F09C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?player_model_customization_encode@Player@@YAXPAVBitStream@Blam@@PBUs_player_model_customization@@@Z");

		for (__int32 i = 0; i < 5; i++)
		{
			stream->Write<unsigned int>(customization->colors[i], 24);
		}

		for (__int32 i = 0; i < 16; i++)
		{
			stream->Write<unsigned char>(customization->armor_section_indices[i], 0, 0xFF);
		}
	}

	bool player_model_customization_decode(Blam::BitStream *stream, s_player_model_customization *customization) // 0x107F0900
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?player_model_customization_decode@Player@@YA_NPAVBitStream@Blam@@PAUs_player_model_customization@@@Z");

		for (__int32 i = 0; i < 5; i++)
		{
			customization->colors[i] = stream->ReadUnsigned<unsigned int>(24);
		}

		for (__int32 i = 0; i < 16; i++)
		{
			customization->armor_section_indices[i] = stream->ReadUnsigned<unsigned char>(0, 0xFF);
		}

		return true;
	}

	void player_emblem_configuration_encode(Blam::BitStream *stream, s_player_emblem_configuration const *emblem) // 0x107F0800
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?player_emblem_configuration_encode@Player@@YAXPAVBitStream@Blam@@PBUs_player_emblem_configuration@@@Z");

		stream->Write(emblem->foregroundIndex, 16);
		stream->Write(emblem->backgroundIndex, 16);
		stream->Write(emblem->backgroundColor, 24);
		stream->Write(emblem->secondaryColor, 24);
		stream->Write(emblem->primaryColor, 24);
		stream->WriteBool(emblem->iconEnabled);
		stream->WriteBool(emblem->backgroundHex);
		stream->WriteBool(emblem->secondaryHex);
		stream->WriteBool(emblem->primaryHex);
	}

	void player_emblem_configuration_decode(Blam::BitStream *stream, s_player_emblem_configuration *emblem) // 0x107F0710
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?player_emblem_configuration_decode@Player@@YAXPAVBitStream@Blam@@PAUs_player_emblem_configuration@@@Z");

		emblem->foregroundIndex = stream->Read<unsigned short>(16);
		emblem->backgroundIndex = stream->Read<unsigned short>(16);
		emblem->backgroundColor = stream->ReadUnsigned<unsigned int>(24);
		emblem->secondaryColor = stream->ReadUnsigned<unsigned int>(24);
		emblem->primaryColor = stream->ReadUnsigned<unsigned int>(24);
		emblem->iconEnabled = stream->ReadBool();
		emblem->backgroundHex = stream->ReadBool();
		emblem->secondaryHex = stream->ReadBool();
		emblem->primaryHex = stream->ReadBool();
	}

	void player_appearance_encode(Blam::BitStream *stream, s_player_appearance const *appearance) // 0x107F02F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?player_appearance_encode@Player@@YAXPAVBitStream@Blam@@PBUs_player_appearance@@@Z");

		stream->WriteBool(appearance->gender);
		stream->WriteStringFixed(appearance->service_tag);
		player_model_customization_encode(stream, &appearance->model_customization);

		stream->Write<unsigned long>(appearance->nameplate_color, 32);
		stream->Write<unsigned long>(appearance->preferred_character, 32);
		stream->Write<long>(appearance->characters_count, 0, 16);

		for (__int32 i = 0; i < appearance->characters_count; i++)
		{
			s_player_character_customiztion const &character = appearance->characters[i];

			stream->Write<unsigned long>(character.character_name, 32);
			player_model_customization_encode(stream, (s_player_model_customization const *)character.customization);
		}

		player_emblem_configuration_encode(stream, &appearance->emblem_config);
		stream->Write<long>(appearance->nameplate_index, 32);
	}

	bool player_appearance_decode(Blam::BitStream *stream, s_player_appearance *appearance) // 0x107F0150
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?player_appearance_decode@Player@@YA_NPAVBitStream@Blam@@PAUs_player_appearance@@@Z");

		memset(appearance, 0, sizeof(s_player_appearance));
		appearance->gender = stream->ReadBool();
		stream->ReadStringFixed(appearance->service_tag);
		if (!player_model_customization_decode(stream, &appearance->model_customization))
			return false;
		appearance->nameplate_color = stream->Read<unsigned long>(32);
		appearance->preferred_character = stream->Read<unsigned long>(32);
		appearance->characters_count = stream->Read<long>(0, 16);
		for (__int32 i = 0; i < appearance->characters_count; i++)
		{
			s_player_character_customiztion &character = appearance->characters[i];
			character.character_name = stream->Read<unsigned long>(32);
			if (!player_model_customization_decode(stream, (s_player_model_customization *)character.customization))
				return false;
		}
		player_emblem_configuration_decode(stream, &appearance->emblem_config);
		appearance->nameplate_index = stream->Read<unsigned long>(32);
		return true;
	}

	bool player_configuration_host_decode(Blam::BitStream *stream, s_player_configuration_from_host *configuration, e_player_configuration_encoding_type encoding_type) // 0x107F0480
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?player_configuration_host_decode@Player@@YA_NPAVBitStream@Blam@@PAUs_player_configuration_from_host@@W4e_player_configuration_encoding_type@@@Z");

		memset(configuration, 0, sizeof(s_player_configuration_from_host));

		stream->ReadBlock(64, (unsigned char *)configuration);
		stream->ReadStringFixed(configuration->player_name);

		configuration->team = -1;
		if (stream->ReadBool())
			configuration->team = stream->Read<long>(5);

		configuration->player_assigned_team = -1;
		if (encoding_type == _player_configuration_encoding_type_full)
		{
			if (stream->ReadBool())
				configuration->player_assigned_team = stream->Read<long>(5);

			if (!player_appearance_decode(stream, &configuration->appearance))
				return false;
		}

		if (configuration->team != -1 && !valid_team_index(configuration->team))
			return false;

		if (configuration->player_assigned_team != -1 && !valid_team_index(configuration->player_assigned_team))
			return false;

		return true;
	}

	void player_configuration_host_encode(Blam::BitStream *stream, s_player_configuration_from_host *configuration, e_player_configuration_encoding_type encoding_type) // 0x107F05E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?player_configuration_host_encode@Player@@YAXPAVBitStream@Blam@@PAUs_player_configuration_from_host@@W4e_player_configuration_encoding_type@@@Z");

		stream->WriteBlock(64, (unsigned char const *)configuration);
		stream->WriteStringFixed(configuration->player_name);

		stream->WriteBool(configuration->team != -1);
		if (configuration->team != -1)
			stream->Write<long>(configuration->team, 5);

		if (encoding_type == _player_configuration_encoding_type_full)
		{
			stream->WriteBool(configuration->player_assigned_team != -1);
			if (configuration->player_assigned_team != -1)
				stream->Write<long>(configuration->player_assigned_team, 5);

			player_appearance_encode(stream, &configuration->appearance);
		}
	}
}

/* ---------- private code */

_inline bool valid_team_index(long team_index) // 0x107F0A80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?valid_team_index@@YA_NJ@Z");

	return team_index >= 0 && team_index < 16;
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template unsigned __int32 Blam::BitStream::ReadUnsigned<unsigned int>(__int32);
template unsigned char Blam::BitStream::ReadUnsigned<unsigned char>(__int32);
template unsigned char Blam::BitStream::ReadUnsigned<unsigned char>(unsigned char, unsigned char);
template unsigned long Blam::BitStream::ReadUnsigned<unsigned long>(unsigned long, unsigned long);
template void Blam::BitStream::Write<long>(long, long, long);
template void Blam::BitStream::Write<unsigned char>(unsigned char, unsigned char, unsigned char);
template void Blam::BitStream::Write<unsigned int>(unsigned __int32, __int32);
template void Blam::BitStream::Write<unsigned long>(unsigned long, __int32);
template void Blam::BitStream::WriteUnsigned<bool>(bool, __int32);
template void Blam::BitStream::WriteUnsigned<unsigned __int64>(unsigned long long, __int32);
template void Blam::BitStream::WriteUnsigned<unsigned char>(unsigned char, unsigned char, unsigned char);
template void Blam::BitStream::WriteUnsigned<unsigned int>(unsigned __int32, __int32);
template void Blam::BitStream::WriteUnsigned<unsigned long>(unsigned long, unsigned long, unsigned long);

/* ---------- explicit instantiations */
template void Blam::BitStream::ReadStringFixed<wchar_t,16>(wchar_t (&)[16]);
template void Blam::BitStream::ReadStringFixed<wchar_t,5>(wchar_t (&)[5]);
template void Blam::BitStream::WriteStringFixed<wchar_t,16>(wchar_t const (&)[16]);
template void Blam::BitStream::WriteStringFixed<wchar_t,5>(wchar_t const (&)[5]);
