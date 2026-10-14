#ifndef __PATCHES_WEAPON_HPP__
#define __PATCHES_WEAPON_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/real_math_definitions.hpp"
#include "Patches/Audio.hpp"
#include "Patches/Ui.hpp"

#include <memory>
#include <string>

/* ---------- forward declarations */

struct bottomless_clip_state;
struct real_vector3d;
namespace Patches
{
	namespace Weapon
	{
		struct DefaultWeaponInfo;
		struct WeaponInfo;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Patches
{
	namespace Weapon
	{
		struct WeaponInfo
		{
			std::string weapon_type; // 0x0
			real_vector3d offset; // 0x1C
			// The special members (move assignment 0x10A265D0 included) are implicit so the struct stays an aggregate (GetEquippedWeapon uses `= {}`).
		};
		static_assert(sizeof(Patches::Weapon::WeaponInfo) == 40, "Invalid Patches::Weapon::WeaponInfo size");
	}
}

#pragma pack(push, 4)
namespace Patches
{
	namespace Weapon
	{
		struct DefaultWeaponInfo
		{
			unsigned short index; // 0x0
			std::string display_name; // 0x4
			std::string weapon_type; // 0x20
			real_vector3d offset; // 0x3C
			real_vector3d centered_offset; // 0x48
			// The special members are implicit so the struct stays an aggregate (InitializeOffsetDefaults uses `= {}`).
		};
	}
}

#pragma pack(pop)
static_assert(sizeof(Patches::Weapon::DefaultWeaponInfo) == 84, "Invalid Patches::Weapon::DefaultWeaponInfo size");

/* ---------- prototypes */

namespace Patches
{
	namespace Weapon
	{
		extern void MapLoadedCallback(char const *mapPath);
		extern void ApplyAll();
		extern void SetBottomlessClip(bool enable);
		extern void ApplyAfterTagsLoaded();
		extern std::string ResolveString(unsigned __int32 unicTagIndex, unsigned __int32 strindId);
		extern Patches::Weapon::WeaponInfo GetWeaponByType(std::string const &weaponType);
		extern real_vector3d GetOffsetByType(std::string const &weaponType);
		extern Patches::Weapon::WeaponInfo GetEquippedWeapon();
		extern void UseDefaultOffsets();
		extern bool InitializeOffsetDefaults();
		extern std::string GetTypeDisplayName(std::string const &weaponType);
		extern bool SetTypeOffset(std::string const &weaponType, real_vector3d const &weaponOffset);
	}
}

namespace Patches
{
	namespace Weapon
	{
		namespace Config
		{
			extern bool CreateList();
			extern bool LoadJSON(std::string const &Name);
			extern bool ConfigExists(std::string const &Name);
			extern bool SaveJSON(std::string const &Name);
			extern bool DeleteJSON(std::string const &Name);
		}
	}
}

extern void bottomless_clip_apply(long weapon_index, short barrel_index, bottomless_clip_state *state);
extern void bottomless_clip_restore(long weapon_index, short barrel_index, bottomless_clip_state *state);
extern void weapon_barrel_fire(long weapon_index, short barrel_index, bool simulated);
extern bool player_has_bottomless_clip(long player_index);
extern bool weapon_has_bottomless_clip(long weapon_index);

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __PATCHES_WEAPON_HPP__
