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

namespace Patches
{
	namespace Weapon
	{
		extern std::vector<Patches::Weapon::DefaultWeaponInfo,std::allocator<Patches::Weapon::DefaultWeaponInfo> > default_weapon_infos; // 0x12467530
		extern std::string JSONName; // 0x12467550
		extern bool IsMainMenu; // 0x1246752C
		extern std::vector<Patches::Weapon::WeaponInfo,std::allocator<Patches::Weapon::WeaponInfo> > weapon_infos; // 0x12467540
	}
}

/* ---------- private variables */

namespace hades_file_local
{
	extern bool cheat_bottomless_clip; // 0x1246752D
}
using namespace hades_file_local;
/* ---------- public code */

namespace Patches
{
	namespace Weapon
	{
		_extern void _sub_10AF3CD0(char const *);
		void MapLoadedCallback(char const *mapPath) // 0x10AF3CD0
		{
			mangled_x86(MANGLED_TODO, "?MapLoadedCallback@Weapon@Patches@@YAXPBD@Z");
			// static ...; // 0x10AF3E54
			// static ...; // 0x10AF3E4C
			// static ...; // 0x10AF3E34
			// static ...; // 0x10AF3E2C
			// char const *mapPath;
			// unsigned __int32 separatorIndex;
			// std::string currentMap;
			// std::string mapName;
			todo("implement");
			_sub_10AF3CD0(mapPath);
		}

		_extern void _sub_10AEFF90();
		void ApplyAll() // 0x10AEFF90
		{
			mangled_x86(MANGLED_TODO, "?ApplyAll@Weapon@Patches@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_10AEFF90();
		}

		_extern void _sub_10AF4E20(bool);
		void SetBottomlessClip(bool enable) // 0x10AF4E20
		{
			mangled_x86(MANGLED_TODO, "?SetBottomlessClip@Weapon@Patches@@YAX_N@Z");
			// bool enable;
			todo("implement");
			_sub_10AF4E20(enable);
		}

		void ApplyAfterTagsLoaded() // 0x10AEFF70
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ApplyAfterTagsLoaded@Weapon@Patches@@YAXXZ");
			// procedure flags: nofpo
		}
	}
}

extern std::string _sub_10AF3ED0(unsigned __int32, unsigned __int32);
namespace Patches
{
	namespace Weapon
	{
		std::string ResolveString(unsigned __int32 unicTagIndex, unsigned __int32 strindId) // 0x10AF3ED0
		{
			mangled_x86(MANGLED_TODO, "?ResolveString@Weapon@Patches@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@II@Z");
			// unsigned __int32 strindId;
			// __int32 (*const ui_get_prefered_lanquage)();
			// char *(*const ui_resolve_string)(unsigned __int32, unsigned __int32, __int32);
			// char *resolvedString;
			// function call : __int32 (*const)()
			// function call : char *(*const)(unsigned __int32, unsigned __int32, __int32)
			todo("implement");
			std::string __result = _sub_10AF3ED0(unicTagIndex, strindId);
			return __result;
		}

		extern WeaponInfo _sub_10AF2EF0(std::string const &);
		Patches::Weapon::WeaponInfo GetWeaponByType(std::string const &weaponType) // 0x10AF2EF0
		{
			mangled_x86(MANGLED_TODO, "?GetWeaponByType@Weapon@Patches@@YA?AUWeaponInfo@12@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// static ...; // 0x10AF30F8
			// static ...; // 0x10AF30EC
			// static ...; // 0x10AF30E4
			// std::string const &weaponType;
			{
				// std::vector<Patches::Weapon::WeaponInfo,std::allocator<Patches::Weapon::WeaponInfo> > &<range>$L0;
				// Patches::Weapon::WeaponInfo *<begin>$L0;
				// Patches::Weapon::WeaponInfo *<end>$L0;
				{
					// Patches::Weapon::WeaponInfo &weapon;
				}
			}
			{
				// Patches::Weapon::DefaultWeaponInfo *<end>$L1;
				// Patches::Weapon::DefaultWeaponInfo *<begin>$L1;
				// std::vector<Patches::Weapon::DefaultWeaponInfo,std::allocator<Patches::Weapon::DefaultWeaponInfo> > &<range>$L1;
				{
					// Patches::Weapon::DefaultWeaponInfo &default_weapon;
					{
						// Patches::Weapon::WeaponInfo newWeapon;
					}
				}
			}
			todo("implement");
			Patches::Weapon::WeaponInfo __result = _sub_10AF2EF0(weaponType);
			return __result;
		}
	}
}

extern real_vector3d _sub_10AF2C40(std::string const &);
namespace Patches
{
	namespace Weapon
	{
		real_vector3d GetOffsetByType(std::string const &weaponType) // 0x10AF2C40
		{
			mangled_x86(MANGLED_TODO, "?GetOffsetByType@Weapon@Patches@@YA?AUreal_vector3d@@ABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
			// std::string const &weaponType;
			{
				// std::vector<Patches::Weapon::WeaponInfo,std::allocator<Patches::Weapon::WeaponInfo> > &<range>$L0;
				// Patches::Weapon::WeaponInfo *<begin>$L0;
				// Patches::Weapon::WeaponInfo *<end>$L0;
				{
					// Patches::Weapon::WeaponInfo &weapon;
				}
			}
			todo("implement");
			real_vector3d __result = _sub_10AF2C40(weaponType);
			return __result;
		}

		extern WeaponInfo _sub_10AF2780();
		Patches::Weapon::WeaponInfo GetEquippedWeapon() // 0x10AF2780
		{
			mangled_x86(MANGLED_TODO, "?GetEquippedWeapon@Weapon@Patches@@YA?AUWeaponInfo@12@XZ");
			// procedure flags: nofpo
			// static ...; // 0x10AF2B44
			// static ...; // 0x10AF2B2C
			// static ...; // 0x10AF2B14
			// static ...; // 0x10AF2B0C
			// s_unit_data *unit;
			// long weaponIndex;
			// char inventoryIndex;
			// s_object_data *weaponObject;
			// std::string weapon_type_name_string;
			// s_weapon_definition *weapon_definition;
			// Patches::Weapon::WeaponInfo weapon;
			// __int32 unitIndex;
			// function call : unsigned long (*const)(long)
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
			// function call : void *(*const)(unsigned long, long)
			todo("implement");
			Patches::Weapon::WeaponInfo __result = _sub_10AF2780();
			return __result;
		}

		_extern void _sub_10AF5250();
		void UseDefaultOffsets() // 0x10AF5250
		{
			mangled_x86(MANGLED_TODO, "?UseDefaultOffsets@Weapon@Patches@@YAXXZ");
			// procedure flags: nofpo
			// static ...; // 0x10AF53FC
			// static ...; // 0x10AF53F0
			// static ...; // 0x10AF53E8
			// std::vector<std::string,std::allocator<std::string> > updatedTypeList;
			{
				// std::vector<Patches::Weapon::DefaultWeaponInfo,std::allocator<Patches::Weapon::DefaultWeaponInfo> > &<range>$L0;
				// Patches::Weapon::DefaultWeaponInfo *<begin>$L0;
				// Patches::Weapon::DefaultWeaponInfo *<end>$L0;
				{
					// Patches::Weapon::DefaultWeaponInfo &weapon;
					{
						// bool duplicate;
						{
							// std::string *<end>$L1;
							// std::string *<begin>$L1;
							// std::vector<std::string,std::allocator<std::string> > &<range>$L1;
							{
								// std::string &type;
							}
						}
					}
				}
			}
			todo("implement");
			_sub_10AF5250();
		}

		_extern bool _sub_10AF3190();
		bool InitializeOffsetDefaults() // 0x10AF3190
		{
			mangled_x86(MANGLED_TODO, "?InitializeOffsetDefaults@Weapon@Patches@@YA_NXZ");
			// procedure flags: nofpo
			// static ...; // 0x10AF35E2
			// static ...; // 0x10AF35D3
			// static ...; // 0x10AF35CC
			// static ...; // 0x10AF35BC
			// static ...; // 0x10AF35A4
			// static ...; // 0x10AF3568
			// static ...; // 0x10AF3560
			// long tag_index;
			// s_tag_iterator iterator;
			{
				// s_weapon_definition *weapon_definition;
				{
					// bool default_set;
					{
						// std::vector<Patches::Weapon::DefaultWeaponInfo,std::allocator<Patches::Weapon::DefaultWeaponInfo> > &<range>$L0;
						// Patches::Weapon::DefaultWeaponInfo *<begin>$L0;
						// Patches::Weapon::DefaultWeaponInfo *<end>$L0;
						{
							// Patches::Weapon::DefaultWeaponInfo &default_weapon;
						}
					}
					{
						// long const weapon_names_unic;
						// real_vector3d centered_offset;
						// std::string weapon_type_name_string;
						// real_vector3d offset;
						// Patches::Weapon::DefaultWeaponInfo default_weapon;
					}
				}
			}
			// function call : void (*const)(s_tag_iterator *, long)
			// function call : long (*const)(s_tag_iterator *)
			// function call : void *(*const)(unsigned long, long)
			todo("implement");
			bool __result = _sub_10AF3190();
			return __result;
		}
	}
}

extern std::string _sub_10AF2DF0(std::string const &);
namespace Patches
{
	namespace Weapon
	{
		std::string GetTypeDisplayName(std::string const &weaponType) // 0x10AF2DF0
		{
			mangled_x86(MANGLED_TODO, "?GetTypeDisplayName@Weapon@Patches@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV34@@Z");
			// std::string const &weaponType;
			{
				// std::vector<Patches::Weapon::DefaultWeaponInfo,std::allocator<Patches::Weapon::DefaultWeaponInfo> > &<range>$L0;
				// Patches::Weapon::DefaultWeaponInfo *<begin>$L0;
				// Patches::Weapon::DefaultWeaponInfo *<end>$L0;
				{
					// Patches::Weapon::DefaultWeaponInfo &weapon;
				}
			}
			todo("implement");
			std::string __result = _sub_10AF2DF0(weaponType);
			return __result;
		}

		_extern bool _sub_10AF4E80(std::string const &, real_vector3d const &);
		bool SetTypeOffset(std::string const &weaponType, real_vector3d const &weaponOffset) // 0x10AF4E80
		{
			mangled_x86(MANGLED_TODO, "?SetTypeOffset@Weapon@Patches@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABUreal_vector3d@@@Z");
			// static ...; // 0x10AF5158
			// static ...; // 0x10AF5150
			// std::string const &weaponType;
			// real_vector3d const &weaponOffset;
			// bool found;
			{
				// std::vector<Patches::Weapon::WeaponInfo,std::allocator<Patches::Weapon::WeaponInfo> > &<range>$L0;
				// Patches::Weapon::WeaponInfo *<begin>$L0;
				// Patches::Weapon::WeaponInfo *<end>$L0;
				{
					// Patches::Weapon::WeaponInfo &weapon;
				}
			}
			{
				// Patches::Weapon::WeaponInfo weapon;
			}
			{
				// Patches::Weapon::DefaultWeaponInfo *<end>$L1;
				// Patches::Weapon::DefaultWeaponInfo *<begin>$L1;
				// std::vector<Patches::Weapon::DefaultWeaponInfo,std::allocator<Patches::Weapon::DefaultWeaponInfo> > &<range>$L1;
				{
					// Patches::Weapon::DefaultWeaponInfo &weapon;
					{
						// s_weapon_definition *weaponDefinition;
					}
				}
			}
			// function call : void *(*const)(unsigned long, long)
			todo("implement");
			bool __result = _sub_10AF4E80(weaponType, weaponOffset);
			return __result;
		}
	}
}

namespace Patches
{
	namespace Weapon
	{
		namespace Config
		{
			_extern bool _sub_10AF13C0();
			bool CreateList() // 0x10AF13C0
			{
				mangled_x86(MANGLED_TODO, "?CreateList@Config@Weapon@Patches@@YA_NXZ");
				// procedure flags: nofpo
				// static ...; // 0x10AF1AD8
				// static ...; // 0x10AF1AD4
				// static ...; // 0x10AF1AC9
				// static ...; // 0x10AF1ABE
				// static ...; // 0x10AF1ABB
				// static ...; // 0x10AF1AB2
				// static ...; // 0x10AF1AA9
				// static ...; // 0x10AF1AA0
				// static ...; // 0x10AF1A40
				// static ...; // 0x10AF1A38
				// std::basic_ifstream<char,std::char_traits<char> > in;
				// std::error_code err;
				{
					// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
					// std::basic_ofstream<char,std::char_traits<char> > out;
					// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
				}
				{
					// std::string contents;
					// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> document;
					{
						// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &offsets;
						{
							// unsigned __int32 i;
							{
								// std::string offsetId;
								// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &offsetObject;
							}
						}
					}
				}
				todo("implement");
				bool __result = _sub_10AF13C0();
				return __result;
			}

			_extern bool _sub_10AF3710(std::string const &);
			bool LoadJSON(std::string const &Name) // 0x10AF3710
			{
				mangled_x86(MANGLED_TODO, "?LoadJSON@Config@Weapon@Patches@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
				// static ...; // 0x10AF3BA2
				// static ...; // 0x10AF3B99
				// static ...; // 0x10AF3B90
				// static ...; // 0x10AF3B6C
				// static ...; // 0x10AF3B64
				// std::string const &Name;
				// std::basic_ifstream<char,std::char_traits<char> > in;
				// std::string contents;
				// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> document;
				{
					// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &weaps;
					{
						// unsigned __int32 i;
						{
							// char const *weapType;
							// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &weapObject;
							// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &offsets;
						}
					}
				}
				todo("implement");
				bool __result = _sub_10AF3710(Name);
				return __result;
			}

			_extern bool _sub_10AF11B0(std::string const &);
			bool ConfigExists(std::string const &Name) // 0x10AF11B0
			{
				mangled_x86(MANGLED_TODO, "?ConfigExists@Config@Weapon@Patches@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
				// static ...; // 0x10AF1344
				// static ...; // 0x10AF1338
				// static ...; // 0x10AF1330
				// std::string const &Name;
				// bool IsCreated;
				{
					// std::vector<std::string,std::allocator<std::string> > &<range>$L0;
					// std::string *<begin>$L0;
					// std::string *<end>$L0;
					{
						// std::string offsetName;
					}
				}
				todo("implement");
				bool __result = _sub_10AF11B0(Name);
				return __result;
			}

			_extern bool _sub_10AF4070(std::string const &);
			bool SaveJSON(std::string const &Name) // 0x10AF4070
			{
				mangled_x86(MANGLED_TODO, "?SaveJSON@Config@Weapon@Patches@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
				// static ...; // 0x10AF4B58
				// static ...; // 0x10AF4B4F
				// static ...; // 0x10AF4B46
				// static ...; // 0x10AF4B42
				// static ...; // 0x10AF4B37
				// static ...; // 0x10AF4B2C
				// static ...; // 0x10AF4B23
				// static ...; // 0x10AF4B1A
				// static ...; // 0x10AF4B16
				// static ...; // 0x10AF4B0B
				// static ...; // 0x10AF4B00
				// static ...; // 0x10AF4A7C
				// static ...; // 0x10AF4A74
				// std::string const &Name;
				// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
				// std::basic_ofstream<char,std::char_traits<char> > out;
				// std::string filePath;
				// rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
				{
					// std::basic_ifstream<char,std::char_traits<char> > in;
					{
						// std::string contents;
						// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> document;
						{
							// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
							// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &offsets;
							// std::basic_ofstream<char,std::char_traits<char> > out;
							// rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
							{
								// unsigned __int32 i;
								{
									// std::string offsetId;
									// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &offsetObject;
								}
							}
						}
					}
				}
				{
					// std::vector<Patches::Weapon::WeaponInfo,std::allocator<Patches::Weapon::WeaponInfo> > &<range>$L0;
					// Patches::Weapon::WeaponInfo *<begin>$L0;
					// Patches::Weapon::WeaponInfo *<end>$L0;
					{
						// Patches::Weapon::WeaponInfo const &weapon;
					}
				}
				todo("implement");
				bool __result = _sub_10AF4070(Name);
				return __result;
			}

			_extern bool _sub_10AF1CB0(std::string const &);
			bool DeleteJSON(std::string const &Name) // 0x10AF1CB0
			{
				mangled_x86(MANGLED_TODO, "?DeleteJSON@Config@Weapon@Patches@@YA_NABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
				// static ...; // 0x10AF24F3
				// static ...; // 0x10AF24EA
				// static ...; // 0x10AF24E1
				// static ...; // 0x10AF24DD
				// static ...; // 0x10AF24D2
				// static ...; // 0x10AF24C7
				// static ...; // 0x10AF24BE
				// static ...; // 0x10AF24B5
				// static ...; // 0x10AF24AC
				// static ...; // 0x10AF2440
				// static ...; // 0x10AF2438
			// $LN32:
				// std::string const &Name;
				// std::filesystem::path fullPath;
				// std::string fileName;
				{
					// std::basic_ifstream<char,std::char_traits<char> > in;
					{
						// std::string contents;
						// rapidjson::GenericDocument<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>,rapidjson::CrtAllocator> document;
						{
							// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> jsonBuffer;
							// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &offsets;
							// std::basic_ofstream<char,std::char_traits<char> > out;
							// rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> jsonWriter;
							{
								// unsigned __int32 i;
								{
									// std::string offsetId;
									// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &offsetObject;
								}
							}
						}
					}
				}
				todo("implement");
				bool __result = _sub_10AF1CB0(Name);
				return __result;
			}
		}
	}
}

_extern void _sub_10AF6680(long, short, bottomless_clip_state *);
void bottomless_clip_apply(long weapon_index, short barrel_index, bottomless_clip_state *state) // 0x10AF6680
{
	mangled_x86(MANGLED_TODO, "?bottomless_clip_apply@@YAXJFPAUbottomless_clip_state@@@Z");
	// bottomless_clip_state *state;
	// s_weapon_barrel_definition *barrel_definition;
	// s_weapon_data *weapon_data;
	// s_weapon_definition *definition;
	{
		// s_weapon_magazine *magazine;
	}
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	_sub_10AF6680(weapon_index, barrel_index, state);
}

_extern void _sub_10AF6820(long, short, bottomless_clip_state *);
void bottomless_clip_restore(long weapon_index, short barrel_index, bottomless_clip_state *state) // 0x10AF6820
{
	mangled_x86(MANGLED_TODO, "?bottomless_clip_restore@@YAXJFPAUbottomless_clip_state@@@Z");
	// bottomless_clip_state *state;
	// s_weapon_barrel_definition *barrel_definition;
	// s_weapon_data *weapon_data;
	// s_weapon_definition *definition;
	{
		// s_weapon_magazine *magazine;
	}
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	_sub_10AF6820(weapon_index, barrel_index, state);
}

_extern void _sub_10AF73E0(long, short, bool);
void weapon_barrel_fire(long weapon_index, short barrel_index, bool simulated) // 0x10AF73E0
{
	mangled_x86(MANGLED_TODO, "?weapon_barrel_fire@@YAXJF_N@Z");
	// static ...; // 0x10AF7488
	// long weapon_index;
	// short barrel_index;
	// bool simulated;
	// void (*const weapon_barrel_fire)(long, short, bool);
	// bottomless_clip_state bottomless_clip;
	// function call : void (*const)(long, short, bool)
	todo("implement");
	_sub_10AF73E0(weapon_index, barrel_index, simulated);
}

_extern bool _sub_10AF6F60(long);
bool player_has_bottomless_clip(long player_index) // 0x10AF6F60
{
	mangled_x86(MANGLED_TODO, "?player_has_bottomless_clip@@YA_NJ@Z");
	// long player_index;
	todo("implement");
	bool __result = _sub_10AF6F60(player_index);
	return __result;
}

namespace Patches
{
	namespace Weapon
	{
		_inline DefaultWeaponInfo::DefaultWeaponInfo(Patches::Weapon::DefaultWeaponInfo &&__that) // 0x10AEF7F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0DefaultWeaponInfo@Weapon@Patches@@QAE@$$QAU012@@Z");
			// Patches::Weapon::DefaultWeaponInfo &__that;

			compiler_generated();
		}

		_inline DefaultWeaponInfo::DefaultWeaponInfo(Patches::Weapon::DefaultWeaponInfo const &__that) // 0x10AEF8E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0DefaultWeaponInfo@Weapon@Patches@@QAE@ABU012@@Z");
			// Patches::Weapon::DefaultWeaponInfo const &__that;

			compiler_generated();
		}

		_inline WeaponInfo::WeaponInfo(Patches::Weapon::WeaponInfo &&__that) // 0x10AEFA10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0WeaponInfo@Weapon@Patches@@QAE@$$QAU012@@Z");
			// Patches::Weapon::WeaponInfo &__that;

			compiler_generated();
		}

		_inline WeaponInfo::WeaponInfo(Patches::Weapon::WeaponInfo const &__that) // 0x10AEFAA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0WeaponInfo@Weapon@Patches@@QAE@ABU012@@Z");
			// Patches::Weapon::WeaponInfo const &__that;

			compiler_generated();
		}

		_inline DefaultWeaponInfo::~DefaultWeaponInfo() // 0x10AEFDD0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1DefaultWeaponInfo@Weapon@Patches@@QAE@XZ");
			// Patches::Weapon::DefaultWeaponInfo *const this;

			compiler_generated();
		}
	}
}

_extern bool _sub_10AF8180(long);
bool weapon_has_bottomless_clip(long weapon_index) // 0x10AF8180
{
	mangled_x86(MANGLED_TODO, "?weapon_has_bottomless_clip@@YA_NJ@Z");
	// long weapon_index;
	// s_unit_data *unit;
	// long unit_index;
	// s_weapon_data *weapon_data;
	// function call : long (*const)(long)
	todo("implement");
	bool __result = _sub_10AF8180(weapon_index);
	return __result;
}

/* ---------- private code */

_extern bool _sub_10AF7E70(long);
bool weapon_can_be_dual_wielded_hook(long weapon_index) // 0x10AF7E70
{
	// `anonymous-namespace'::weapon_can_be_dual_wielded_hook
	// long weapon_index;
	// bool can_dual_wield;
	// s_weapon_definition *weapon_definition;
	// s_object_data *weapon;
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	bool __result = _sub_10AF7E70(weapon_index);
	return __result;
}

_extern short _sub_10AF7190(long, short);
short unit_rotate_zoom_level_hook(long unit_index, short level) // 0x10AF7190
{
	// `anonymous-namespace'::unit_rotate_zoom_level_hook
	// short level;
	// short (*const unit_rotate_zoom_level)(long, short);
	// function call : bool (*const)(unsigned long)
	// function call : short (*const)(long, short)
	todo("implement");
	short __result = _sub_10AF7190(unit_index, level);
	return __result;
}

_extern bool _sub_10AF8330(unsigned __int32, __int32, ProjectilePenaltyType);
bool weapon_should_apply_bloom(unsigned __int32 weaponObjectIndex, __int32 barrelIndex, ProjectilePenaltyType type) // 0x10AF8330
{
	// `anonymous-namespace'::weapon_should_apply_bloom
	// ProjectilePenaltyType type;
	// s_object_data *unitObject;
	// s_weapon_definition *weaponDefinition;
	// s_object_data *weaponObject;
	// __int32 functionIndex;
	// bool isCrouching;
	// function call : bool (*const)(long)
	// function call : long (*const)(long)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	bool __result = _sub_10AF8330(weaponObjectIndex, barrelIndex, type);
	return __result;
}

_extern void _sub_10AF7230(unsigned __int32, __int32);
void weapon_apply_firing_penalty_hook(unsigned __int32 weaponObjectIndex, __int32 barrelIndex) // 0x10AF7230
{
	// `anonymous-namespace'::weapon_apply_firing_penalty_hook
	// __int32 barrelIndex;
	// void (*const weapon_apply_firing_penalty)(unsigned __int32, __int32);
	// function call : void (*const)(unsigned __int32, __int32)
	todo("implement");
	_sub_10AF7230(weaponObjectIndex, barrelIndex);
}

_extern void _sub_10AF72C0(unsigned __int32, __int32);
void weapon_apply_movement_penalty_hook(unsigned __int32 weaponObjectIndex, __int32 barrelIndex) // 0x10AF72C0
{
	// `anonymous-namespace'::weapon_apply_movement_penalty_hook
	// __int32 barrelIndex;
	// void (*const weapon_apply_movement_penalty)(unsigned __int32, __int32);
	// function call : void (*const)(unsigned __int32, __int32)
	todo("implement");
	_sub_10AF72C0(weaponObjectIndex, barrelIndex);
}

_extern void _sub_10AF7350(unsigned __int32, __int32);
void weapon_apply_turning_penalty_hook(unsigned __int32 weaponObjectIndex, __int32 barrelIndex) // 0x10AF7350
{
	// `anonymous-namespace'::weapon_apply_turning_penalty_hook
	// __int32 barrelIndex;
	// void (*const weapon_apply_turning_penalty)(unsigned __int32, __int32);
	// function call : void (*const)(unsigned __int32, __int32)
	todo("implement");
	_sub_10AF7350(weaponObjectIndex, barrelIndex);
}

bool SupportWeaponStartHook(__int32 weaponObjectIndex) // 0x10AF5230
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SupportWeaponStartHook@@YA_NH@Z");
	// `anonymous-namespace'::SupportWeaponStartHook
	// __int32 weaponObjectIndex;

	return false;
}

_extern float _sub_10AF7AE0(unsigned __int32, __int32, bool, unsigned char, float);
float weapon_calculate_error_angle_hook(unsigned __int32 weaponObjectIndex, __int32 barrelIndex, bool forcedScope, unsigned char scopeLevel, float error) // 0x10AF7AE0
{
	// `anonymous-namespace'::weapon_calculate_error_angle_hook
	// float error;
	// float fireTimePenalty;
	// float errorAngleMin;
	// float magnificationFactor;
	// s_weapon_definition *weaponDefinition;
	// float min;
	// float (*weapon_caclulate_magnification)(unsigned __int32, unsigned short);
	// s_object_data *weaponObject;
	// s_weapon_barrel_definition &barrelDefinition;
	// unsigned __int32 unitObjectIndex;
	// float max;
	// float errorAngleMax;
	// float errorAngle;
	{
		// s_object_data *unitObject;
		// unsigned char magnificationLevel;
		// float magnification;
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : float (*)(unsigned __int32, unsigned short)
	// function call : float (*const)(unsigned __int32, unsigned __int32)
	// function call : bool (*const)(unsigned __int32)
	todo("implement");
	float __result = _sub_10AF7AE0(weaponObjectIndex, barrelIndex, forcedScope, scopeLevel, error);
	return __result;
}

_extern unsigned __int32 _sub_10AF75A0(unsigned __int32, __int32);
unsigned __int32 weapon_barrel_update_hook(unsigned __int32 weaponObjectIndex, __int32 barrelIndex) // 0x10AF75A0
{
	// `anonymous-namespace'::weapon_barrel_update_hook
	// __int32 barrelIndex;
	// s_weapon_definition *weaponDefinition;
	// s_object_data *weaponObject;
	// bool (*const weapon_update_barrel)(unsigned __int32, __int32);
	// bool result;
	{
		// s_weapon_barrel *barrels;
		// s_weapon_barrel &barrel;
		// float secondsPerTick;
		// s_weapon_barrel_definition &barrelDefinition;
		{
			// s_object_data *unitObject;
			// float t;
			// unsigned char weaponObjectFlags;
			// bool hasBloomFunction;
			// unsigned __int32 unitObjectIndex;
			// bool isCrouching;
			{
				// float fireTimePenalty;
				// float errorAccelerationTime;
			}
		}
	}
	// function call : bool (*const)(unsigned __int32, __int32)
	// function call : void *(*const)(unsigned long, long)
	// function call : float (*const)()
	// function call : float (*const)()
	// function call : float (*const)(unsigned __int32, unsigned __int32)
	// function call : bool (*const)(unsigned __int32)
	todo("implement");
	unsigned __int32 __result = _sub_10AF75A0(weaponObjectIndex, barrelIndex);
	return __result;
}

bool weapon_bloom_decay_hook(unsigned __int32 weaponObjectIndex, __int32 barrelIndex) // 0x10AF7AC0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?weapon_bloom_decay_hook@@YA_NIH@Z");
	// `anonymous-namespace'::weapon_bloom_decay_hook
	// __int32 barrelIndex;

	return false;
}

_extern bool _sub_10AF7FB0(long, unsigned long, long, float *, bool *, bool *);
bool weapon_compute_function_value_hook(long weapon_index, unsigned long function_name, long definition_index, float *out_value, bool *out_value_valid, bool *a6) // 0x10AF7FB0
{
	// `anonymous-namespace'::weapon_compute_function_value_hook
	// bool *a6;
	// bool (*const weapon_compute_function_value)(long, unsigned long, long, float *, bool *, bool *);
	{
		// s_weapon_data *weapon;
		// long barrel_index;
	}
	// function call : float (*const)(float)
	// function call : long (*const)()
	// function call : bool (*const)(long, unsigned long, long, float *, bool *, bool *)
	todo("implement");
	bool __result = _sub_10AF7FB0(weapon_index, function_name, definition_index, out_value, out_value_valid, a6);
	return __result;
}

_extern bool _sub_10AF8260(long);
bool weapon_has_infinite_ammo_hook(long weapon_index) // 0x10AF8260
{
	// `anonymous-namespace'::weapon_has_infinite_ammo_hook
	// long weapon_index;
	// bool (*const player_has_infinite_ammo)(long);
	// s_weapon_data *weapon;
	// long owner_unit_index;
	{
		// s_unit_data *unit;
	}
	// function call : long (*const)(long)
	// function call : bool (*const)(long)
	todo("implement");
	bool __result = _sub_10AF8260(weapon_index);
	return __result;
}

_extern bool _sub_10AF7000(long);
bool player_has_infinite_ammo_hook(long player_index) // 0x10AF7000
{
	// `anonymous-namespace'::player_has_infinite_ammo_hook
	// long player_index;
	todo("implement");
	bool __result = _sub_10AF7000(player_index);
	return __result;
}

_extern void _sub_10AF74E0(long, float, float);
void weapon_barrel_fire__unit_active_camouflage_ding_hook(long unit_index, float camo, float time) // 0x10AF74E0
{
	// `anonymous-namespace'::weapon_barrel_fire__unit_active_camouflage_ding_hook
	// float time;
	// void (*const unit_active_camouflage_ding)(long, float, float);
	// function call : s_object_data *(*const)(unsigned long, c_enum<enum e_object_type,long>)
	// function call : void (*const)(long, float, float)
	todo("implement");
	_sub_10AF74E0(unit_index, camo, time);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_flags<enum e_weapon_definition_flags,unsigned long>::test(e_weapon_definition_flags) const;
template c_flags<enum e_barrel_flags,long>::operator long() const;
template c_flags<enum e_weapon_definition_flags,unsigned long>::operator unsigned long() const;
