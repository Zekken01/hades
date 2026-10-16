/* ---------- headers */

#include "Patches/Weapon.hpp"
#include "hades/hades.h"

#include "Blam/BlamNetwork.hpp"
#include "Blam/cache/tag_iterator.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/weapon_definitions.hpp"
#include "Blam/items/weapons.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/bitstream.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/memory/static_array.inl"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/damage_definitions.hpp"
#include "Blam/objects/object_types.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "Blam/units/units.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "Console/Console.hpp"
#include "ElDorito.hpp"
#include "Patch.hpp"
#include "Patches/Audio.hpp"
#include "Patches/Ui.hpp"
#include "Pointer.hpp"
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
#include "ThirdParty/rapidjson/prettywriter.h"
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <optional>
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
#include <utility>
#include <vector>
#include "Modules/ModuleServer.hpp"  // hades: added for 0x10AF7E70

#include "Modules/ModuleWeapon.hpp"  // hades: added for 0x10AEFF90
#include "Patches/Core.hpp"  // hades: added for 0x10AEFF90

#include "Blam/items/items.hpp"  // hades: added for 0x10AF7AE0

/* ---------- forward declarations */

struct begin;
struct bottomless_clip_state;
struct end;
struct real_vector3d;
struct s_object_data;
struct s_tag_iterator;
struct s_unit_data;
struct s_weapon_barrel;
struct s_weapon_barrel_definition;
struct s_weapon_data;
struct s_weapon_definition;
struct s_weapon_magazine;
namespace Patches
{
	namespace Weapon
	{
		struct DefaultWeaponInfo;
		struct WeaponInfo;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Weapon {}
	using namespace Patches::Weapon;
	namespace Core {}
	using namespace Patches::Core;
}

namespace Console {}
using namespace ::Console;
namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

namespace hades_file_local
{
	enum ProjectilePenaltyType
	{
		eProjectilePenalty_Firing = 0,
		eProjectilePenalty_Moving,
		eProjectilePenalty_Turning,
	};
}
using namespace hades_file_local;
/* ---------- definitions */

// bottomless_clip_state is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const player_mapping_get_unit_by_output_user = reinterpret_cast<unsigned long (*)(long)>(0x589CC0);
}

#include "Blam/Cache/StringIdCache.hpp"  // hades: added for 0x10AF3190
long tag_find_by_name(unsigned long group_tag, char const *name);  // hades: added for 0x10AF3190  // hades: added for 0x10AF3190

extern float (*const game_tick_length)();  // hades: added for 0x10AF75A0

extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x10AF6680

extern bool (__cdecl *const unit_is_dual_wielding)(unsigned long);  // hades: added for 0X10AF7190

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

bool weapon_can_be_dual_wielded_hook(long weapon_index);
short unit_rotate_zoom_level_hook(long unit_index, short level);
bool weapon_should_apply_bloom(unsigned __int32 weaponObjectIndex, __int32 barrelIndex, ProjectilePenaltyType type);
void weapon_apply_firing_penalty_hook(unsigned __int32 weaponObjectIndex, __int32 barrelIndex);
void weapon_apply_movement_penalty_hook(unsigned __int32 weaponObjectIndex, __int32 barrelIndex);
void weapon_apply_turning_penalty_hook(unsigned __int32 weaponObjectIndex, __int32 barrelIndex);
bool SupportWeaponStartHook(__int32 weaponObjectIndex);
float weapon_calculate_error_angle_hook(unsigned __int32 weaponObjectIndex, __int32 barrelIndex, bool forcedScope, unsigned char scopeLevel, float error);
unsigned __int32 weapon_barrel_update_hook(unsigned __int32 weaponObjectIndex, __int32 barrelIndex);
bool weapon_bloom_decay_hook(unsigned __int32 weaponObjectIndex, __int32 barrelIndex);
bool weapon_compute_function_value_hook(long weapon_index, unsigned long function_name, long definition_index, float *out_value, bool *out_value_valid, bool *a6);
bool weapon_has_infinite_ammo_hook(long weapon_index);
bool player_has_infinite_ammo_hook(long player_index);
void weapon_barrel_fire__unit_active_camouflage_ding_hook(long unit_index, float camo, float time);

/* ---------- globals */

template<typename t_arg0> static t_arg0 *object_get(unsigned long object_index) { return (t_arg0 *)object_get(object_index); }  // hades: a file-local template in the original (undecorated `object_get<T>`), defined so it is emitted;  // hades: added for 0X10AF8260
extern s_object_data *(*const object_try_and_get_and_verify_type)(unsigned long, c_enum<enum e_object_type,long>); // 0x11248848
template<typename t_arg0> static t_arg0 *object_get(unsigned long object_index);  // hades: a file-local template in the original (undecorated `object_get<T>`), defined so it is emitted;  // hades: added for 0x10AF7FB0
extern float (*const game_seconds_to_ticks_real)(float);  // hades: added for 0x10AF7FB0
extern long (*const game_time_get)();  // hades: added for 0x10AF7FB0
template<typename t_arg0> static t_arg0 *object_get(unsigned long object_index);  // hades: a file-local template in the original (undecorated `object_get<T>`), defined so it is emitted;  // hades: added for 0x10AF8180

namespace Patches
{
	namespace Weapon
	{
		std::vector<Patches::Weapon::DefaultWeaponInfo> default_weapon_infos; // 0x12467530
		std::string JSONName; // 0x12467550
		extern bool IsMainMenu; // 0x1246752C
		std::vector<Patches::Weapon::WeaponInfo> weapon_infos; // 0x12467540
	}
}

/* ---------- private variables */

namespace hades_file_local
{
	extern "C" bool cheat_bottomless_clip; // 0x1246752D
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Weapon
	{
		void MapLoadedCallback(char const *mapPath) // 0x10AF3CD0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?MapLoadedCallback@Weapon@Patches@@YAXPBD@Z");

			std::string currentMap(mapPath);
			unsigned __int32 separatorIndex = currentMap.find_first_of("\\/");
			std::string mapName = currentMap.substr(separatorIndex + 1);
			if (mapName == "mainmenu")
			{
				IsMainMenu = true;
			}
			else
			{
				IsMainMenu = false;
				default_weapon_infos.clear();
				weapon_infos.clear();
				InitializeOffsetDefaults();
				Modules::CommandMap::Instance().ExecuteCommand("Weapon.JSON.Load", false);
			}
		}

		void ApplyAll() // 0x10AEFF90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAll@Weapon@Patches@@YAXXZ");

			JSONName = Modules::ModuleWeapon::Instance().VarWeaponJSON->ValueString;
			Config::CreateList();
			Config::LoadJSON(JSONName);
			Patches::Core::OnMapLoaded(MapLoadedCallback);
			Pointer::Base(0x73F1E6).Write<unsigned char>(0x0);
			Hook(0x761550, weapon_can_be_dual_wielded_hook).Apply();
			Hook(0x1D50C0, unit_rotate_zoom_level_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x75F0F1, weapon_apply_firing_penalty_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x761197, weapon_apply_movement_penalty_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x74A8B7, weapon_apply_turning_penalty_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x13809E, SupportWeaponStartHook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7696E9, weapon_barrel_update_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x7605D0, weapon_calculate_error_angle_hook).Apply();
			Hook(0x7611A1, weapon_bloom_decay_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Patch(0x77C180, 0x90, 6).Apply();
			Pointer(0x1948574).Write(weapon_compute_function_value_hook);
			Hook(0x73DCDB, weapon_compute_function_value_hook).Apply();
			Hook(0x7BBF24, weapon_compute_function_value_hook).Apply();
			Hook(0x762146, weapon_compute_function_value_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0xCB55E, weapon_barrel_fire, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x760E9E, weapon_barrel_fire, static_cast<__int32>(HookFlags::IsCall)).Apply();
			Hook(0x763C30, weapon_has_infinite_ammo_hook).Apply();
			Hook(0x151E50, player_has_infinite_ammo_hook).Apply();
			Hook(0x76013A, weapon_barrel_fire__unit_active_camouflage_ding_hook, static_cast<__int32>(HookFlags::IsCall)).Apply();
		}

		void SetBottomlessClip(bool enable) // 0x10AF4E20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetBottomlessClip@Weapon@Patches@@YAX_N@Z");

			cheat_bottomless_clip = enable;
		}

		void ApplyAfterTagsLoaded() // 0x10AEFF70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAfterTagsLoaded@Weapon@Patches@@YAXXZ");
		}
	}
}


namespace Patches
{
	namespace Weapon
	{
		std::string ResolveString(unsigned __int32 unicTagIndex, unsigned __int32 strindId) // 0x10AF3ED0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ResolveString@Weapon@Patches@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@II@Z");

			__int32 (*const ui_get_prefered_lanquage)() = reinterpret_cast<__int32 (*)()>(0x52FC40);
			char *(*const ui_resolve_string)(unsigned __int32, unsigned __int32, __int32) = reinterpret_cast<char *(*)(unsigned __int32, unsigned __int32, __int32)>(0x51E290);
			char *resolvedString = ui_resolve_string(unicTagIndex, strindId, ui_get_prefered_lanquage());
			if (strlen(resolvedString) == 0)
				return Blam::Cache::StringIDCache::GetCurrent()->GetString(strindId);
			return resolvedString;
		}


		Patches::Weapon::WeaponInfo GetWeaponByType(std::string const &weaponType) // 0x10AF2EF0
		{
			mangled_x86(MANGLED_TODO, "?GetWeaponByType@Weapon@Patches@@YA?AUWeaponInfo@12@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			{
				// std::vector<Patches::Weapon::WeaponInfo> &<range>$L0;
				// Patches::Weapon::WeaponInfo *<begin>$L0;
				// Patches::Weapon::WeaponInfo *<end>$L0;
				{
					// Patches::Weapon::WeaponInfo &weapon;
				}
			}
			{
				// Patches::Weapon::DefaultWeaponInfo *<end>$L1;
				// Patches::Weapon::DefaultWeaponInfo *<begin>$L1;
				// std::vector<Patches::Weapon::DefaultWeaponInfo> &<range>$L1;
				{
					// Patches::Weapon::DefaultWeaponInfo &default_weapon;
					{
						// Patches::Weapon::WeaponInfo newWeapon;
					}
				}
			}

			// hades: written by hand; this function has no symbol-map entry, but its copy of a
			// weapon_infos element keeps the implicit WeaponInfo copy ctor (0x10AEFAA0) emitted.
			for (auto &weapon : weapon_infos)
			{
				if (weapon.weapon_type == weaponType)
					return weapon;
			}
			for (auto &default_weapon : default_weapon_infos)
			{
				if (default_weapon.weapon_type == weaponType)
				{
					WeaponInfo newWeapon;
					newWeapon.weapon_type = weaponType;
					weapon_infos.push_back(newWeapon);
					return newWeapon;
				}
			}
			return WeaponInfo();
		}
	}
}


namespace Patches
{
	namespace Weapon
	{
		real_vector3d GetOffsetByType(std::string const &weaponType) // 0x10AF2C40
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetOffsetByType@Weapon@Patches@@YA?AUreal_vector3d@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

			for (Patches::Weapon::WeaponInfo &weapon : weapon_infos)
			{
				if (weapon.weapon_type == weaponType)
					return weapon.offset;
			}
			return Patches::Weapon::WeaponInfo().offset;
		}

		Patches::Weapon::WeaponInfo GetEquippedWeapon() // 0x10AF2780
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetEquippedWeapon@Weapon@Patches@@YA?AUWeaponInfo@12@XZ");

			WeaponInfo weapon = {};
			__int32 unitIndex = eldorado::player_mapping_get_unit_by_output_user(0);
			if (unitIndex == -1)
				return weapon;
			s_unit_data *unit = (s_unit_data *)object_try_and_get_and_verify_type(unitIndex, 1);
			if (!unit)
				return weapon;
			char inventoryIndex = unit->current_weapon_set.indices[0];
			if (inventoryIndex == -1)
				return weapon;
			long weaponIndex = unit->weapon_object_indices[inventoryIndex];
			s_object_data *weaponObject = object_try_and_get_and_verify_type(weaponIndex, 4);
			if (!weaponObject)
				return weapon;
			s_weapon_definition *weapon_definition = (s_weapon_definition *)tag_get('weap', weaponObject->definition_index);
			std::string weapon_type_name_string = Blam::Cache::StringIDCache::GetCurrent()->GetString(weapon_definition->weapon_type_name);
			weapon.weapon_type = weapon_type_name_string;
			weapon.offset = GetOffsetByType(weapon_type_name_string);
			return weapon;
		}

		void UseDefaultOffsets() // 0x10AF5250
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?UseDefaultOffsets@Weapon@Patches@@YAXXZ");

			weapon_infos.clear();
			std::vector<std::string> updatedTypeList;
			for (auto &weapon : default_weapon_infos)
			{
				bool duplicate = false;
				for (auto &type : updatedTypeList)
				{
					if (weapon.weapon_type == type)
					{
						duplicate = true;
						break;
					}
				}
				if (!duplicate)
				{
					updatedTypeList.push_back(weapon.weapon_type);
					SetTypeOffset(weapon.weapon_type, real_vector3d{ 0.0f, 0.0f, 0.0f });
				}
			}
		}

		bool InitializeOffsetDefaults() // 0x10AF3190
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?InitializeOffsetDefaults@Weapon@Patches@@YA_NXZ");

			if (IsMainMenu)
				return false;
			s_tag_iterator iterator;
			((void(__cdecl *)(s_tag_iterator *, long))0x5033E0)(&iterator, 'weap');
			long tag_index;
			while ((tag_index = ((long(__cdecl *)(s_tag_iterator *))0x503400)(&iterator)) != -1)
			{
				s_weapon_definition *weapon_definition = (s_weapon_definition *)tag_get('weap', tag_index);
				if (weapon_definition)
				{
					bool default_set = false;
					for (auto &default_weapon : default_weapon_infos)
					{
						if (default_weapon.index == tag_index)
						{
							default_set = true;
							break;
						}
					}
					if (!default_set)
					{
						DefaultWeaponInfo default_weapon = {};
						default_weapon.index = tag_index;
						real_vector3d offset = weapon_definition->first_person_weapon_offset;
						real_vector3d centered_offset = weapon_definition->centered_first_person_weapon_offset;
						default_weapon.offset = { offset.i, offset.j, offset.k };
						default_weapon.centered_offset = { centered_offset.i, centered_offset.j, centered_offset.k };
						std::string weapon_type_name_string = Blam::Cache::StringIDCache::GetCurrent()->GetString(weapon_definition->weapon_type_name);
						long const weapon_names_unic = tag_find_by_name('unic', "ui\\weapon_type_names");
						if (weapon_names_unic == -1)
							default_weapon.display_name = weapon_type_name_string;
						else
							default_weapon.display_name = ResolveString(weapon_names_unic, weapon_definition->weapon_type_name);
						default_weapon.weapon_type = weapon_type_name_string;
						default_weapon_infos.push_back(default_weapon);
					}
				}
			}
			return true;
		}
	}
}


namespace Patches
{
	namespace Weapon
	{
		std::string GetTypeDisplayName(std::string const &weaponType) // 0x10AF2DF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetTypeDisplayName@Weapon@Patches@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV34@@Z");

			for (Patches::Weapon::DefaultWeaponInfo &weapon : default_weapon_infos)
			{
				if (weapon.weapon_type == weaponType)
					return weapon.display_name;
			}
			return "";
		}

		bool SetTypeOffset(std::string const &weaponType, real_vector3d const &weaponOffset) // 0x10AF4E80
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetTypeOffset@Weapon@Patches@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABUreal_vector3d@@@Z");

			if (IsMainMenu)
				return false;
			bool found = false;
			for (Patches::Weapon::WeaponInfo &weapon : weapon_infos)
			{
				if (weapon.weapon_type == weaponType)
				{
					weapon.offset = weaponOffset;
					found = true;
					break;
				}
			}
			if (!found)
			{
				Patches::Weapon::WeaponInfo weapon;
				weapon.weapon_type = weaponType;
				weapon.offset = weaponOffset;
				weapon_infos.push_back(weapon);
			}
			for (Patches::Weapon::DefaultWeaponInfo &weapon : default_weapon_infos)
			{
				if (weapon.weapon_type == weaponType)
				{
					s_weapon_definition *weaponDefinition = (s_weapon_definition *)tag_get('weap', weapon.index);
					if (weaponDefinition)
					{
						weaponDefinition->first_person_weapon_offset = weapon.offset + weaponOffset;
						weaponDefinition->centered_first_person_weapon_offset = weapon.centered_offset + weaponOffset;
					}
				}
			}
			return true;
		}
	}
}

namespace Patches
{
	namespace Weapon
	{
		namespace Config
		{
			bool CreateList() // 0x10AF13C0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?CreateList@Config@Weapon@Patches@@YA_NXZ");

				Modules::ModuleWeapon::Instance().WeaponsJSONList.clear();
				std::error_code err;
				if (!std::filesystem::exists("data/weapon_offsets", err))
				{
					if (!std::filesystem::create_directory("data/weapon_offsets", err))
						return false;
				}
				if (!std::filesystem::exists("data/weapon_offsets/offsets.json", err))
				{
					std::ofstream out("data/weapon_offsets/offsets.json", std::ios::trunc);
					if (!out.is_open())
						return false;
					rapidjson::StringBuffer jsonBuffer;
					rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
					jsonWriter.StartObject();
					jsonWriter.Key("offsets");
					jsonWriter.StartArray();
					jsonWriter.StartObject();
					jsonWriter.Key("id");
					jsonWriter.String(JSONName.c_str());
					jsonWriter.EndObject();
					jsonWriter.EndArray();
					jsonWriter.EndObject();
					out << jsonBuffer.GetString();
					if (out.fail())
						return false;
					out.flush();
					out.close();
				}
				std::ifstream in("data/weapon_offsets/offsets.json", std::ios::in | std::ios::binary);
				if (in && in.is_open())
				{
					std::string contents;
					in.seekg(0, std::ios::end);
					contents.resize(in.tellg());
					in.seekg(0, std::ios::beg);
					in.read(&contents[0], contents.size());
					in.close();
					rapidjson::Document document;
					if (!document.Parse<0>(contents.c_str()).HasParseError() && document.IsObject())
					{
						if (!document.HasMember("offsets"))
							return false;
						rapidjson::Value const &offsets = document["offsets"];
						for (unsigned __int32 i = 0; i < offsets.Size(); i++)
						{
							rapidjson::Value const &offsetObject = offsets[i];
							if (!offsetObject.HasMember("id"))
								continue;
							std::string offsetId = offsetObject["id"].GetString();
							Modules::ModuleWeapon::Instance().WeaponsJSONList.push_back(offsetId.c_str());
						}
					}
				}
				return true;
			}

			bool LoadJSON(std::string const &Name) // 0x10AF3710
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?LoadJSON@Config@Weapon@Patches@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

				std::ifstream in("data/weapon_offsets/offsets/" + Name + ".json", std::ios::in | std::ios::binary);
				if (!in || !in.is_open())
					return false;
				std::string contents;
				in.seekg(0, std::ios::end);
				contents.resize(in.tellg());
				in.seekg(0, std::ios::beg);
				in.read(&contents[0], contents.size());
				in.close();
				rapidjson::Document document;
				if (!document.Parse<0>(contents.c_str()).HasParseError() && document.IsObject())
				{
					if (!document.HasMember("weapons"))
						return false;
					rapidjson::Value const &weaps = document["weapons"];
					for (unsigned __int32 i = 0; i < weaps.Size(); i++)
					{
						rapidjson::Value const &weapObject = weaps[i];
						if (!weapObject.HasMember("type") || !weapObject.HasMember("offset"))
							continue;
						char const *weapType = weapObject["type"].GetString();
						rapidjson::Value const &offsets = weapObject["offset"];
						SetTypeOffset(weapType, { offsets[0].GetFloat(), offsets[1].GetFloat(), offsets[2].GetFloat() });
					}
				}
				return true;
			}

			bool ConfigExists(std::string const &Name) // 0x10AF11B0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?ConfigExists@Config@Weapon@Patches@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

				bool IsCreated = false;
				for (std::string offsetName : Utils::Singleton<Modules::ModuleWeapon>::Instance().WeaponsJSONList)
				{
					if (Utils::String::ToLower(Name) == Utils::String::ToLower(offsetName))
						IsCreated = true;
				}
				return IsCreated;
			}

			bool SaveJSON(std::string const &Name) // 0x10AF4070
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?SaveJSON@Config@Weapon@Patches@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

				CreateList();
				Utils::Singleton<Modules::ModuleWeapon>::Instance().VarWeaponJSON->ValueString = Name;
				if (!ConfigExists(Name))
				{
					std::ifstream in("data/weapon_offsets/offsets.json", std::ios::in | std::ios::binary);
					if (in && in.is_open())
					{
						std::string contents;
						in.seekg(0, std::ios::end);
						contents.resize(in.tellg());
						in.seekg(0, std::ios::beg);
						in.read(&contents[0], contents.size());
						in.close();
						rapidjson::Document document;
						if (!document.Parse<0>(contents.c_str()).HasParseError() && document.IsObject())
						{
							if (!document.HasMember("offsets"))
								return false;
							std::ofstream out("data/weapon_offsets/offsets.json", std::ios::trunc);
							if (!out.is_open())
								return false;
							rapidjson::StringBuffer jsonBuffer;
							rapidjson::PrettyWriter<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
							jsonWriter.StartObject();
							jsonWriter.Key("offsets");
							jsonWriter.StartArray();
							rapidjson::Value const &offsets = document["offsets"];
							for (unsigned __int32 i = 0; i < offsets.Size(); i++)
							{
								rapidjson::Value const &offsetObject = offsets[i];
								if (!offsetObject.HasMember("id"))
									continue;
								std::string offsetId = offsetObject["id"].GetString();
								jsonWriter.StartObject();
								jsonWriter.Key("id");
								jsonWriter.String(offsetId.c_str());
								jsonWriter.EndObject();
							}
							jsonWriter.StartObject();
							jsonWriter.Key("id");
							jsonWriter.String(Name.c_str());
							jsonWriter.EndObject();
							jsonWriter.EndArray();
							jsonWriter.EndObject();
							out << jsonBuffer.GetString();
							if (out.fail())
								return false;
							out.flush();
							out.close();
						}
					}
				}
				std::string filePath = "data/weapon_offsets/offsets/";
				std::filesystem::create_directories(std::filesystem::path(filePath));
				std::ofstream out(filePath + Name + ".json", std::ios::trunc);
				if (!out.is_open() || Utils::String::ToLower(Name) == "default")
					return false;
				rapidjson::StringBuffer jsonBuffer;
				rapidjson::PrettyWriter<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
				jsonWriter.StartObject();
				jsonWriter.Key("weapons");
				jsonWriter.StartArray();
				for (Patches::Weapon::WeaponInfo const &weapon : weapon_infos)
				{
					jsonWriter.StartObject();
					jsonWriter.Key("type");
					jsonWriter.String(weapon.weapon_type.c_str());
					jsonWriter.Key("offset");
					jsonWriter.StartArray();
					jsonWriter.SetMaxDecimalPlaces(6);
					jsonWriter.Double(weapon.offset.i);
					jsonWriter.Double(weapon.offset.j);
					jsonWriter.Double(weapon.offset.k);
					jsonWriter.EndArray();
					jsonWriter.EndObject();
				}
				jsonWriter.EndArray();
				jsonWriter.EndObject();
				out << jsonBuffer.GetString();
				if (out.fail())
					return false;
				out.flush();
				out.close();
				return true;
			}

			bool DeleteJSON(std::string const &Name) // 0x10AF1CB0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?DeleteJSON@Config@Weapon@Patches@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");

				if (Name == "default")
					return false;
				CreateList();
				Utils::Singleton<Modules::ModuleWeapon>::Instance().VarWeaponJSON->ValueString = "default";
				if (ConfigExists(Name))
				{
					std::ifstream in("data/weapon_offsets/offsets.json", std::ios::in | std::ios::binary);
					if (in && in.is_open())
					{
						std::string contents;
						in.seekg(0, std::ios::end);
						contents.resize(in.tellg());
						in.seekg(0, std::ios::beg);
						in.read(&contents[0], contents.size());
						in.close();
						rapidjson::Document document;
						if (!document.Parse<0>(contents.c_str()).HasParseError() && document.IsObject())
						{
							if (!document.HasMember("offsets"))
								return false;
							std::ofstream out("data/weapon_offsets/offsets.json", std::ios::trunc);
							if (!out.is_open())
								return false;
							rapidjson::StringBuffer jsonBuffer;
							rapidjson::PrettyWriter<rapidjson::StringBuffer> jsonWriter(jsonBuffer);
							jsonWriter.StartObject();
							jsonWriter.Key("offsets");
							jsonWriter.StartArray();
							rapidjson::Value const &offsets = document["offsets"];
							for (unsigned __int32 i = 0; i < offsets.Size(); i++)
							{
								rapidjson::Value const &offsetObject = offsets[i];
								if (!offsetObject.HasMember("id"))
									continue;
								std::string offsetId = offsetObject["id"].GetString();
								if (offsetId == Name)
									continue;
								jsonWriter.StartObject();
								jsonWriter.Key("id");
								jsonWriter.String(offsetId.c_str());
								jsonWriter.EndObject();
							}
							jsonWriter.EndArray();
							jsonWriter.EndObject();
							out << jsonBuffer.GetString();
							if (out.fail())
								return false;
							out.flush();
							out.close();
						}
					}
				}
				std::string fileName = Name + ".json";
				std::filesystem::path fullPath = std::filesystem::path("data/weapon_offsets/offsets/") / std::filesystem::path(fileName.c_str());
				if (std::filesystem::exists(fullPath))
				{
					try
					{
						std::filesystem::remove(fullPath);
						return true;
					}
					catch (...)
					{
						return false;
					}
				}
				else
					return false;
				return false;
			}
		}
	}
}

void bottomless_clip_apply(long weapon_index, short barrel_index, bottomless_clip_state *state) // 0x10AF6680
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?bottomless_clip_apply@@YAXJFPAUbottomless_clip_state@@@Z");

	state->applied = false;
	s_weapon_data *weapon_data = (s_weapon_data *)object_get(weapon_index);
	s_weapon_definition *definition = (s_weapon_definition *)tag_get('weap', weapon_data->definition_index);
	s_weapon_barrel_definition *barrel_definition = &definition->barrels[barrel_index];
	if (!weapon_has_bottomless_clip(weapon_index))
		return;
	state->applied = true;
	state->heat = weapon_data->heat;
	weapon_data->heat = 0.0f;
	state->age = weapon_data->age;
	weapon_data->age = 0.0f;
	if (barrel_definition->magazine_index != -1)
	{
		s_weapon_magazine *magazine = &weapon_data->magazines[barrel_definition->magazine_index];
		state->rounds_loaded = magazine->rounds_loaded;
		magazine->rounds_loaded = definition->magazines[barrel_definition->magazine_index].rounds_total_loaded_maximum;
	}
}

void bottomless_clip_restore(long weapon_index, short barrel_index, bottomless_clip_state *state) // 0x10AF6820
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?bottomless_clip_restore@@YAXJFPAUbottomless_clip_state@@@Z");

	if (!state->applied)
		return;

	s_weapon_data *weapon_data = (s_weapon_data *)object_get(weapon_index);
	s_weapon_definition *definition = (s_weapon_definition *)tag_get(0x77656170, weapon_data->definition_index);
	s_weapon_barrel_definition *barrel_definition = &definition->barrels[barrel_index];

	weapon_data->age = state->age;
	weapon_data->heat = state->heat;

	if (barrel_definition->magazine_index != -1)
	{
		s_weapon_magazine *magazine = &weapon_data->magazines[barrel_definition->magazine_index];
		magazine->rounds_loaded = state->rounds_loaded;
	}
}

void weapon_barrel_fire(long weapon_index, short barrel_index, bool simulated) // 0x10AF73E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?weapon_barrel_fire@@YAXJF_N@Z");

	void (__cdecl *const weapon_barrel_fire)(long, short, bool) = (void(__cdecl *const)(long, short, bool))0xB5F860;
	bottomless_clip_state bottomless_clip;

	bottomless_clip_apply(weapon_index, barrel_index, &bottomless_clip);
	weapon_barrel_fire(weapon_index, barrel_index, simulated);
	bottomless_clip_restore(weapon_index, barrel_index, &bottomless_clip);
}

bool player_has_bottomless_clip(long player_index) // 0x10AF6F60
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_has_bottomless_clip@@YA_NJ@Z");


	if (cheat_bottomless_clip)
	{
		return true;
	}
	if (player_index == -1)
	{
		return false;
	}
	return player_get(player_index)->traits.weapons.infinite_ammo == 3;
}

namespace Patches
{
	namespace Weapon
	{
		// mangled_x86(MANGLED_DEFAULT, "??0DefaultWeaponInfo@Weapon@Patches@@QAE@$$QAU012@@Z"); no body to assert in
		// implicit: DefaultWeaponInfo::DefaultWeaponInfo(Patches::Weapon::DefaultWeaponInfo &&__that) = default; // 0x10AEF7F0

		// mangled_x86(MANGLED_DEFAULT, "??0DefaultWeaponInfo@Weapon@Patches@@QAE@ABU012@@Z"); no body to assert in
		// implicit: DefaultWeaponInfo::DefaultWeaponInfo(Patches::Weapon::DefaultWeaponInfo const &__that) = default; // 0x10AEF8E0

		// mangled_x86(MANGLED_DEFAULT, "??0WeaponInfo@Weapon@Patches@@QAE@$$QAU012@@Z"); no body to assert in
		// implicit: WeaponInfo::WeaponInfo(Patches::Weapon::WeaponInfo &&__that) = default; // 0x10AEFA10

		// mangled_x86(MANGLED_DEFAULT, "??0WeaponInfo@Weapon@Patches@@QAE@ABU012@@Z"); no body to assert in
		// implicit: WeaponInfo::WeaponInfo(Patches::Weapon::WeaponInfo const &__that) = default; // 0x10AEFAA0

		// mangled_x86(MANGLED_DEFAULT, "??1DefaultWeaponInfo@Weapon@Patches@@QAE@XZ"); no body to assert in
		// implicit: DefaultWeaponInfo::~DefaultWeaponInfo() = default; // 0x10AEFDD0
	}
}

bool weapon_has_bottomless_clip(long weapon_index) // 0x10AF8180
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?weapon_has_bottomless_clip@@YA_NJ@Z");

	s_weapon_data *weapon_data = (s_weapon_data *)object_get(weapon_index);
	long unit_index = ((long(__cdecl *)(long))0xB62DF0)(weapon_index);
	if (unit_index == -1)
		return false;

	s_unit_data *unit = object_get<s_unit_data>(unit_index);
	return unit->player_index != -1 && player_has_bottomless_clip(unit->player_index);
}

/* ---------- private code */

bool weapon_can_be_dual_wielded_hook(long weapon_index) // 0x10AF7E70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?weapon_can_be_dual_wielded_hook@@YA_NJ@Z");

	if (!Modules::ModuleServer::Instance().VarServerDualWieldEnabledClient->ValueInt)
		return false;

	s_object_data *weapon = object_get(weapon_index);
	if (!weapon)
		return false;

	s_weapon_definition *weapon_definition = (s_weapon_definition *)tag_get(0x77656170, weapon->definition_index);
	if (!weapon_definition)
		return false;

	bool can_dual_wield = weapon_definition->weapon_flags.test(_weapon_can_be_dual_wielded_bit) || weapon_definition->weapon_flags.test(_weapon_can_only_be_dual_wielded_bit);
	return can_dual_wield;
}

short unit_rotate_zoom_level_hook(long unit_index, short level) // 0x10AF7190
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?unit_rotate_zoom_level_hook@@YAFJF@Z");

	short (__cdecl *const unit_rotate_zoom_level)(long, unsigned short) = (short(__cdecl *const)(long, unsigned short))0xb47630;

	if (unit_is_dual_wielding(unit_index))
		return -1;

	return unit_rotate_zoom_level(unit_index, level);
}

bool weapon_should_apply_bloom(unsigned __int32 weaponObjectIndex, __int32 barrelIndex, ProjectilePenaltyType type) // 0x10AF8330
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?weapon_should_apply_bloom@@YA_NIHW4ProjectilePenaltyType@hades_file_local@@@Z");

	if (!((bool (__cdecl *)(long))0xB63EA0)(weaponObjectIndex))
		return false;
	s_object_data *weaponObject = object_get(weaponObjectIndex);
	if (!weaponObject)
		return false;
	s_object_data *unitObject = object_get(((long (__cdecl *)(long))0xB63030)(weaponObjectIndex));
	if (!unitObject)
		return false;

	bool isCrouching = ((s_unit_data *)unitObject)->crouch_fraction > 0.0f;
	s_weapon_definition *weaponDefinition = (s_weapon_definition *)tag_get(0x77656170, weaponObject->definition_index);
	__int32 functionIndex = 0;
	switch (type)
	{
	case eProjectilePenalty_Firing:
		functionIndex = isCrouching ? 0 : 1;
		break;
	case eProjectilePenalty_Moving:
		functionIndex = 2;
		break;
	case eProjectilePenalty_Turning:
		functionIndex = 3;
		break;
	}

	if (barrelIndex < 0 || barrelIndex >= weaponDefinition->barrels.count)
		return false;
	return (&weaponDefinition->barrels[barrelIndex].firing_penalty_function)[functionIndex].count > 0;
}

void weapon_apply_firing_penalty_hook(unsigned __int32 weaponObjectIndex, __int32 barrelIndex) // 0x10AF7230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?weapon_apply_firing_penalty_hook@@YAXIH@Z");

	void (__cdecl *const weapon_apply_firing_penalty)(unsigned __int32, __int32) = (void(__cdecl *const)(unsigned __int32, __int32))0xb5c2e0;

	if (weapon_should_apply_bloom(weaponObjectIndex, barrelIndex, eProjectilePenalty_Firing))
	{
		weapon_apply_firing_penalty(weaponObjectIndex, barrelIndex);
	}
}

void weapon_apply_movement_penalty_hook(unsigned __int32 weaponObjectIndex, __int32 barrelIndex) // 0x10AF72C0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?weapon_apply_movement_penalty_hook@@YAXIH@Z");

	void (__cdecl *const weapon_apply_movement_penalty)(unsigned __int32, __int32) = (void(__cdecl *const)(unsigned __int32, __int32))0xb5c450;

	if (weapon_should_apply_bloom(weaponObjectIndex, barrelIndex, eProjectilePenalty_Moving))
	{
		weapon_apply_movement_penalty(weaponObjectIndex, barrelIndex);
	}
}

void weapon_apply_turning_penalty_hook(unsigned __int32 weaponObjectIndex, __int32 barrelIndex) // 0x10AF7350
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?weapon_apply_turning_penalty_hook@@YAXIH@Z");

	void (__cdecl *const weapon_apply_turning_penalty)(unsigned __int32, __int32) = (void(__cdecl *const)(unsigned __int32, __int32))0xb5c630;

	if (weapon_should_apply_bloom(weaponObjectIndex, barrelIndex, eProjectilePenalty_Turning))
	{
		weapon_apply_turning_penalty(weaponObjectIndex, barrelIndex);
	}
}

bool SupportWeaponStartHook(__int32 weaponObjectIndex) // 0x10AF5230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SupportWeaponStartHook@@YA_NH@Z");

	return false;
}

float weapon_calculate_error_angle_hook(unsigned __int32 weaponObjectIndex, __int32 barrelIndex, bool forcedScope, unsigned char scopeLevel, float error) // 0x10AF7AE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?weapon_calculate_error_angle_hook@@YAMIH_NEM@Z");

	float (*weapon_caclulate_magnification)(unsigned __int32, unsigned short) = reinterpret_cast<float (*)(unsigned __int32, unsigned short)>(0xB636E0);
	s_object_data *weaponObject = object_get(weaponObjectIndex);
	if (!weaponObject)
		return 0.0f;
	s_weapon_definition *weaponDefinition = (s_weapon_definition *)tag_get('weap', weaponObject->definition_index);
	if (barrelIndex >= weaponDefinition->barrels.count)
		return 0.0f;
	s_weapon_barrel_definition &barrelDefinition = weaponDefinition->barrels[barrelIndex];
	float magnificationFactor = 1.0f;
	unsigned __int32 unitObjectIndex = ((s_item_data *)weaponObject)->owner_unit_index;
	if ((unsigned char)((s_item_data *)weaponObject)->inventory_state && unitObjectIndex != -1 && !((unsigned short)(long)barrelDefinition.barrel_flags & 1))
	{
		s_object_data *unitObject = object_get(unitObjectIndex);
		unsigned char magnificationLevel = ((s_unit_data *)unitObject)->current_zoom_level;
		if (forcedScope)
			magnificationLevel = scopeLevel;
		float magnification = weapon_caclulate_magnification(weaponObjectIndex, magnificationLevel);
		if (magnification > 0.0001f)
			magnificationFactor = 1.0f / magnification;
	}
	float fireTimePenalty = ((float (*)(unsigned __int32, unsigned __int32))0xB44680)(unitObjectIndex, weaponObjectIndex);
	if (((unsigned long)weaponDefinition->weapon_flags >> 27) & 1)
	{
		if (((bool (*)(unsigned __int32))0xB64050)(weaponObjectIndex))
			fireTimePenalty = 1.0f;
		else
			fireTimePenalty = 0.0f;
	}
	float errorAngleMin = barrelDefinition.dual_wield_error_angle.lower;
	if (errorAngleMin == 0.0f)
		errorAngleMin = barrelDefinition.projectile_error_angle.lower;
	float errorAngleMax = barrelDefinition.dual_wield_error_angle.upper;
	if (errorAngleMax == 0.0f)
		errorAngleMax = barrelDefinition.projectile_error_angle.upper;
	float min = (1.0f - fireTimePenalty) * barrelDefinition.projectile_error_angle.lower + errorAngleMin * fireTimePenalty;
	float max = (1.0f - fireTimePenalty) * barrelDefinition.projectile_error_angle.upper + errorAngleMax * fireTimePenalty;
	float errorAngle = (max - min) * magnificationFactor * error + min * magnificationFactor;
	return errorAngle;
}

unsigned __int32 weapon_barrel_update_hook(unsigned __int32 weaponObjectIndex, __int32 barrelIndex) // 0x10AF75A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?weapon_barrel_update_hook@@YAIIH@Z");

	bool (*const weapon_update_barrel)(unsigned __int32, __int32) = reinterpret_cast<bool (*)(unsigned __int32, __int32)>(0xB60BD0);
	bool result = weapon_update_barrel(weaponObjectIndex, barrelIndex);
	s_object_data *weaponObject = object_get(weaponObjectIndex);
	s_weapon_definition *weaponDefinition = (s_weapon_definition *)tag_get('weap', weaponObject->definition_index);
	if (weaponObject && barrelIndex < weaponDefinition->barrels.count)
	{
		s_weapon_barrel *barrels = (s_weapon_barrel *)((unsigned char *)weaponObject + 0x204);
		s_weapon_barrel &barrel = barrels[barrelIndex];
		s_weapon_barrel_definition &barrelDefinition = weaponDefinition->barrels[barrelIndex];
		float secondsPerTick = game_tick_length();
		if (barrel.state == 1)
		{
			unsigned char weaponObjectFlags = *((unsigned char *)weaponObject + 0x179);
			unsigned __int32 unitObjectIndex = -1;
			if (weaponObjectFlags & 1)
				unitObjectIndex = *(unsigned __int32 *)((unsigned char *)weaponObject + 0x184);
			s_object_data *unitObject = object_get(unitObjectIndex);
			bool isCrouching = unitObject && *(float *)((unsigned char *)unitObject + 0x418) > 0.0f;
			bool hasBloomFunction = (&barrelDefinition.firing_penalty_function)[unitObject && isCrouching ? 0 : 1].count > 0;
			float t = game_tick_length();
			if (!hasBloomFunction)
			{
				float errorAccelerationTime = ((float (*)(unsigned __int32, unsigned __int32))0xB44680)(unitObjectIndex, weaponObjectIndex);
				if (((unsigned long)weaponDefinition->weapon_flags >> 27) & 1)
				{
					if (((bool (*)(unsigned __int32))0xB64050)(weaponObjectIndex))
						errorAccelerationTime = 1.0f;
					else
						errorAccelerationTime = 0.0f;
				}
				float fireTimePenalty = errorAccelerationTime * barrelDefinition.unknown + (1.0f - errorAccelerationTime) * barrelDefinition.unknown9;
				barrel.error += t * fireTimePenalty;
			}
			barrel.recoil += t * barrelDefinition.unknown6;
		}
		else
		{
			barrel.error -= barrelDefinition.bloom_rate_of_decay * secondsPerTick;
			barrel.recoil -= barrelDefinition.unknown7 * secondsPerTick;
		}
		if (barrel.error > 1.0f)
			barrel.error = 1.0f;
		if (barrel.error < 0.0f)
			barrel.error = 0.0f;
		if (barrel.recoil > 1.0f)
			barrel.recoil = 1.0f;
		if (barrel.recoil < 0.0f)
			barrel.recoil = 0.0f;
		return result | (barrel.error != 0.0f);
	}
	return result;
}

bool weapon_bloom_decay_hook(unsigned __int32 weaponObjectIndex, __int32 barrelIndex) // 0x10AF7AC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?weapon_bloom_decay_hook@@YA_NIH@Z");

	return false;
}

bool weapon_compute_function_value_hook(long weapon_index, unsigned long function_name, long definition_index, float *out_value, bool *out_value_valid, bool *a6) // 0x10AF7FB0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?weapon_compute_function_value_hook@@YA_NJKJPAMPA_N1@Z");

	bool (__cdecl *const weapon_compute_function_value)(long, unsigned long, long, float *, bool *, bool *) = (bool(__cdecl *const)(long, unsigned long, long, float *, bool *, bool *))0xB61920;

	if (function_name == 538 || function_name == 539)
	{
		s_weapon_data *weapon = object_get<s_weapon_data>(weapon_index);
		long barrel_index = function_name == 538 ? 0 : 1;

		if (game_seconds_to_ticks_real(1.0f / 30.0f) >= game_time_get() - weapon->game_time_last_fired)
			*out_value = weapon->barrels[barrel_index].firing_rate;
		else
			*out_value = 0.0f;

		*out_value_valid = *out_value != 0.0f;
		return *out_value_valid;
	}

	return weapon_compute_function_value(weapon_index, function_name, definition_index, out_value, out_value_valid, a6);
}

bool weapon_has_infinite_ammo_hook(long weapon_index) // 0x10AF8260
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?weapon_has_infinite_ammo_hook@@YA_NJ@Z");


	bool (__cdecl *const player_has_infinite_ammo)(long) = (bool(__cdecl *const)(long))0x551E50;
	s_weapon_data *weapon = object_get<s_weapon_data>(weapon_index);
	long owner_unit_index = ((long(__cdecl *)(long))0xB62DF0)(weapon_index);

	if (owner_unit_index != -1)
	{
		s_unit_data *unit = object_get<s_unit_data>(owner_unit_index);
		if (unit->player_index != -1)
		{
			return player_has_infinite_ammo(unit->player_index);
		}
	}
	return false;
}

bool player_has_infinite_ammo_hook(long player_index) // 0x10AF7000
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?player_has_infinite_ammo_hook@@YA_NJ@Z");

	if (player_index == -1)
	{
		return false;
	}
	if (cheat_bottomless_clip)
	{
		return true;
	}
	return player_get(player_index)->traits.weapons.infinite_ammo >= 2;
}

void weapon_barrel_fire__unit_active_camouflage_ding_hook(long unit_index, float camo, float time) // 0x10AF74E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?weapon_barrel_fire__unit_active_camouflage_ding_hook@@YAXJMM@Z");


	if (!object_try_and_get_and_verify_type(unit_index, 0x2003))
	{
		return;
	}

	void (__cdecl *const unit_active_camouflage_ding)(long, float, float) = (void(__cdecl *const)(long, float, float))0xB38760;

	unit_active_camouflage_ding(unit_index, camo, time);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_flags<enum e_weapon_definition_flags,unsigned long>::test(e_weapon_definition_flags) const;
template c_flags<enum e_barrel_flags,long>::operator long() const;
template c_flags<enum e_weapon_definition_flags,unsigned long>::operator unsigned long() const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace Patches { namespace Weapon { bool IsMainMenu; } }

namespace hades_file_local { extern "C" { bool cheat_bottomless_clip; } }
