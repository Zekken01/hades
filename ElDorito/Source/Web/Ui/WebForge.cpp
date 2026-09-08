/* ---------- headers */

#include "hades/hades.h"

#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/cseries_memory.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/forge/forge_globals.hpp"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/color_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/multiplayer_game_objects.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/saved_games/scenario_map_variant.hpp"
#include "Blam/scenario/scenario_definitions.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_block_index.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "ElDorito.hpp"
#include "Forge/ForgeDevice.hpp"
#include "Forge/ForgeObjectProperties.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/ObjectProperties/ForgeObjectPropertyAccessor.hpp"
#include "Forge/ObjectProperties/ForgeObjectPropertyDefinitions.hpp"
#include "Forge/ObjectProperties/ForgeObjectPropertyManager.hpp"
#include "Forge/ObjectProperties/ForgePropertyValue.hpp"
#include "Forge/ObjectSet.hpp"
#include "Interface/CustomBitmapManager.hpp"
#include "mods/map_variant_loader.hpp"
#include "Patches/GamePatches.hpp"
#include "Patches/PlayerPropertiesExtension.hpp"
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
#include "ThirdParty/rapidjson/reader.h"
#include "ThirdParty/rapidjson/stream.h"
#include "ThirdParty/rapidjson/stringbuffer.h"
#include "ThirdParty/rapidjson/writer.h"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"
#include "Web/Ui/Screen.hpp"

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <array>
#include <atomic>
#include <bitset>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct CForgeDeviceObjectProperties;
struct begin;
struct end;
struct real_rgb_color;
struct s_forge_description_text_entry;
struct s_forge_globals_definition;
struct s_forge_material_type;
struct s_forge_object_property_setter;
struct s_forge_palette_category;
struct s_forge_palette_item;
struct s_forge_sky_definition;
struct s_forge_weather_definition;
struct s_map_variant;
struct s_multiplayer_object_properties;
struct s_object_attachment_definition;
struct s_object_data;
struct s_object_definition;
struct s_variant_datum;
struct s_variant_quota;
namespace Forge
{
	class CDefaultPropertyAccessor;
	class CDeferredPropertySetter;
	class CObjectPropertyAccessor;
	class CObjectPropertyManager;
	struct ForgeGarbageVolumeProperties;
	struct ForgeKillVolumeProperties;
	struct ForgeLightProperties;
	struct ForgeMapModifierProperties;
	struct ForgeScreenFxProperties;
	struct ReforgeObjectProperties;
	struct SPropertyDefinition;
	struct SPropertyValue;
}

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Selection {}
	using namespace Forge::Selection;
	namespace Reforge {}
	using namespace Forge::Reforge;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Ui {}
	using namespace Web::Ui;
}

namespace Web
{
	namespace Ui
	{
		namespace ScreenLayer {}
		using namespace Web::Ui::ScreenLayer;
		namespace WebForge {}
		using namespace Web::Ui::WebForge;
	}
}

namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge {}
		using namespace Web::Browser::Bridge;
	}
}

namespace Patches {}
using namespace ::Patches;
namespace Patches
{
	namespace Game {}
	using namespace Patches::Game;
}

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

namespace Web
{
	namespace Ui
	{
		namespace WebForge
		{
			extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > BuildForgePaletteJSON();
			extern void OnItemSpawned(unsigned __int32 objectIndex);
			extern void ShowObjectProperties(unsigned __int32 objectIndex);
			extern void ShowObjectCreation();
			extern Web::Browser::Bridge::QueryError ProcessAction(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > *p_Result);
		}
	}
}

void SerializeProperty(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, char const *key, __int32 value);
void SerializeProperty(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, char const *key, float value);
void SerializeProperty(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, char const *key, bool value);
bool IsForgeLight(unsigned __int32 objectIndex);
bool IsForgeScreenEffectObject(unsigned __int32 objectIndex);
long ObjectGetChangeColors(long objectIndex, real_rgb_color *outColors);
void SerializeObjectProperties(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, ::Forge::CObjectPropertyAccessor &accessor);
std::basic_string<char,std::char_traits<char>,std::allocator<char> > SerializeObjectProperties(short placementIndex);
void DeserializeObjectProperties(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &json, ::Forge::CObjectPropertyAccessor &sink);

/* ---------- globals */

namespace Utils
{
	::Forge::CObjectPropertyManager *Utils::Singleton< ::Forge::CObjectPropertyManager>::m_instance; // 0x1247ED90
}

/* ---------- private variables */

namespace hades_file_local
{
	extern unsigned __int32 s_CurrentObjectIndex; // 0x113553F0
	extern ::Forge::CDeferredPropertySetter m_itemSpawnPropertySetter; // 0x1247ED94
}
using namespace hades_file_local;
/* ---------- public code */

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10CA6A10();
namespace Web
{
	namespace Ui
	{
		namespace WebForge
		{
			std::basic_string<char,std::char_traits<char>,std::allocator<char> > BuildForgePaletteJSON() // 0x10CA6A10
			{
				mangled_x86(MANGLED_TODO, "?BuildForgePaletteJSON@WebForge@Ui@Web@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
				// procedure flags: nofpo
				// static ...; // 0x10CA6F8B
				// static ...; // 0x10CA6F84
				// static ...; // 0x10CA6F6C
				// static ...; // 0x10CA6F64
				// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
				// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
				// s_forge_globals_definition *forge_globals;
				{
					// c_tag_block<s_forge_palette_item> &<range>$L0;
					// s_forge_palette_item *<begin>$L0;
					// s_forge_palette_item *<end>$L0;
					{
						// s_forge_palette_item &item;
						{
							// s_forge_object_property_setter *<end>$L1;
							// s_forge_object_property_setter *<begin>$L1;
							// c_tag_block<s_forge_object_property_setter> &<range>$L1;
							{
								// s_forge_object_property_setter &setter;
							}
						}
					}
				}
				{
					// s_forge_palette_category *<end>$L2;
					// c_tag_block<s_forge_palette_category> &<range>$L2;
					// s_forge_palette_category *<begin>$L2;
					{
						// s_forge_palette_category &category;
					}
				}
				{
					// c_tag_block<s_forge_description_text_entry> &<range>$L3;
					// s_forge_description_text_entry *<begin>$L3;
					// s_forge_description_text_entry *<end>$L3;
					{
						// s_forge_description_text_entry &description;
					}
				}
				todo("implement");
				std::string __result = _sub_10CA6A10();
				return __result;
			}
		}
	}
}

namespace Forge
{
	_inline CDeferredPropertySetter::CDeferredPropertySetter() // 0x10CA64C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??0CDeferredPropertySetter@Forge@@QAE@XZ");
		// Forge::CDeferredPropertySetter *const this;

		compiler_generated();
	}

	_inline CDeferredPropertySetter::~CDeferredPropertySetter() // 0x10CA67C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "??1CDeferredPropertySetter@Forge@@UAE@XZ");
		// Forge::CDeferredPropertySetter *const this;

		compiler_generated();
	}
}

namespace Web
{
	namespace Ui
	{
		namespace WebForge
		{
			_extern void _sub_10CA7900(unsigned __int32);
			void OnItemSpawned(unsigned __int32 objectIndex) // 0x10CA7900
			{
				mangled_x86(MANGLED_TODO, "?OnItemSpawned@WebForge@Ui@Web@@YAXI@Z");
				// unsigned __int32 objectIndex;
				// s_object_data *object;
				// function call : unsigned long (*const)(long)
				todo("implement");
				_sub_10CA7900(objectIndex);
			}

			_extern void _sub_10CA9010(unsigned __int32);
			void ShowObjectProperties(unsigned __int32 objectIndex) // 0x10CA9010
			{
				mangled_x86(MANGLED_TODO, "?ShowObjectProperties@WebForge@Ui@Web@@YAXI@Z");
				// static ...; // 0x10CA914C
				// static ...; // 0x10CA9140
				// static ...; // 0x10CA9138
				// unsigned __int32 objectIndex;
				// s_object_data *currentObject;
				{
					// s_variant_datum placement;
					// s_map_variant *mapv;
				}
				todo("implement");
				_sub_10CA9010(objectIndex);
			}

			_extern void _sub_10CA8CE0();
			void ShowObjectCreation() // 0x10CA8CE0
			{
				mangled_x86(MANGLED_TODO, "?ShowObjectCreation@WebForge@Ui@Web@@YAXXZ");
				// procedure flags: nofpo
				// static ...; // 0x10CA8F60
				// static ...; // 0x10CA8F59
				// static ...; // 0x10CA8F54
				// static ...; // 0x10CA8F30
				// static ...; // 0x10CA8F28
				// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
				// char buff[256];
				// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
				// s_map_variant *const mapv;
				{
					// __int32 i;
					{
						// s_variant_quota const &itemBudget;
					}
				}
				todo("implement");
				_sub_10CA8CE0();
			}
		}
	}
}

namespace Web
{
	namespace Browser
	{
		namespace Bridge
		{
			extern QueryError _sub_10CA79A0(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, std::basic_string<char,std::char_traits<char>,std::allocator<char> > *);
		}
	}
}

namespace Web
{
	namespace Ui
	{
		namespace WebForge
		{
			Web::Browser::Bridge::QueryError ProcessAction(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::basic_string<char,std::char_traits<char>,std::allocator<char> > *p_Result) // 0x10CA79A0
			{
				mangled_x86(MANGLED_TODO, "?ProcessAction@WebForge@Ui@Web@@YA?AW4QueryError@Bridge@Browser@3@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
				// static ...; // 0x10CA7BDD
				// static ...; // 0x10CA7BD8
				// static ...; // 0x10CA7BB4
				// static ...; // 0x10CA7BAC
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
				// std::basic_string<char,std::char_traits<char>,std::allocator<char> > *p_Result;
				// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > data;
				// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > type;
				{
					// s_object_data *currentObject;
					{
						// Forge::CDefaultPropertyAccessor sink;
						// unsigned long playerIndex;
						// s_map_variant *mapv;
					}
				}
				// function call : unsigned long (*const)(long)
				todo("implement");
				Web::Browser::Bridge::QueryError __result = _sub_10CA79A0(p_Args, p_Result);
				return __result;
			}
		}
	}
}

/* ---------- private code */

_extern void _sub_10CA8B80(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &, char const *, __int32);
void SerializeProperty(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, char const *key, __int32 value) // 0x10CA8B80
{
	// `anonymous-namespace'::SerializeProperty
	// __int32 value;
	todo("implement");
	_sub_10CA8B80(writer, key, value);
}

_extern void _sub_10CA8BE0(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &, char const *, float);
void SerializeProperty(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, char const *key, float value) // 0x10CA8BE0
{
	// `anonymous-namespace'::SerializeProperty
	// float value;
	todo("implement");
	_sub_10CA8BE0(writer, key, value);
}

_extern void _sub_10CA8C80(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &, char const *, bool);
void SerializeProperty(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, char const *key, bool value) // 0x10CA8C80
{
	// `anonymous-namespace'::SerializeProperty
	// bool value;
	todo("implement");
	_sub_10CA8C80(writer, key, value);
}

_extern bool _sub_10CA7590(unsigned __int32);
bool IsForgeLight(unsigned __int32 objectIndex) // 0x10CA7590
{
	// `anonymous-namespace'::IsForgeLight
	// unsigned __int32 objectIndex;
	// s_object_data *object;
	// s_object_definition *objectDef;
	{
		// c_tag_block<s_object_attachment_definition> &<range>$L0;
		// s_object_attachment_definition *<begin>$L0;
		// s_object_attachment_definition *<end>$L0;
		{
			// s_object_attachment_definition const &attachment;
			{
				// unsigned __int32 lightFlags;
			}
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	bool __result = _sub_10CA7590(objectIndex);
	return __result;
}

_extern bool _sub_10CA76E0(unsigned __int32);
bool IsForgeScreenEffectObject(unsigned __int32 objectIndex) // 0x10CA76E0
{
	// `anonymous-namespace'::IsForgeScreenEffectObject
	// unsigned __int32 objectIndex;
	// s_object_data *object;
	// s_object_definition *objectDef;
	{
		// c_tag_block<s_object_attachment_definition> &<range>$L0;
		// s_object_attachment_definition *<begin>$L0;
		// s_object_attachment_definition *<end>$L0;
		{
			// s_object_attachment_definition const &attachment;
		}
	}
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	bool __result = _sub_10CA76E0(objectIndex);
	return __result;
}

_extern long _sub_10CA7800(long, real_rgb_color *);
long ObjectGetChangeColors(long objectIndex, real_rgb_color *outColors) // 0x10CA7800
{
	// `anonymous-namespace'::ObjectGetChangeColors
	// real_rgb_color *outColors;
	// real_rgb_color *colors;
	// s_object_data *object;
	// unsigned __int32 count;
	{
		// __int32 i;
	}
	todo("implement");
	long __result = _sub_10CA7800(objectIndex, outColors);
	return __result;
}

_extern void _sub_10CA8900(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &, ::Forge::CObjectPropertyAccessor &);
void SerializeObjectProperties(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, ::Forge::CObjectPropertyAccessor &accessor) // 0x10CA8900
{
	// `anonymous-namespace'::SerializeObjectProperties
	// static ...; // 0x10CA8AEC
	// static ...; // 0x10CA8AE4
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer;
	// Forge::CObjectPropertyAccessor &accessor;
	// Forge::CObjectPropertyManager &propertyManager;
	{
		// std::array<Forge::SPropertyDefinition,90> const &<range>$L0;
		// Forge::SPropertyDefinition const *<begin>$L0;
		// Forge::SPropertyDefinition const *<end>$L0;
		{
			// Forge::SPropertyDefinition const &propertyDef;
			{
				// float value;
			}
		}
	}
	// function call : Forge::SPropertyValue (Forge::EObjectProperty)
	// function call : Forge::SPropertyValue (Forge::EObjectProperty)
	todo("implement");
	_sub_10CA8900(writer, accessor);
}

extern std::basic_string<char,std::char_traits<char>,std::allocator<char> > _sub_10CA7C80(short);
std::basic_string<char,std::char_traits<char>,std::allocator<char> > SerializeObjectProperties(short placementIndex) // 0x10CA7C80
{
	// `anonymous-namespace'::SerializeObjectProperties
	// static ...; // 0x10CA8674
	// static ...; // 0x10CA866D
	// static ...; // 0x10CA8666
	// static ...; // 0x10CA8659
	// static ...; // 0x10CA8650
	// static ...; // 0x10CA864D
	// static ...; // 0x10CA8648
	// static ...; // 0x10CA85F4
	// static ...; // 0x10CA85EC
// $LN30:
	// short placementIndex;
	// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
	// s_variant_datum placement;
	// Forge::ForgeScreenFxProperties const *screenFxProperties;
	// s_variant_quota const &budget;
	// s_object_data *object;
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
	// Forge::ForgeKillVolumeProperties const *killVolumeProperties;
	// static bool (*`SerializeObjectProperties'::`2'::Weapon_HasSpareClips)(unsigned __int32); // 0x113553F4
	// EForgeDeviceType forgeDeviceType;
	// long playerIndex;
	// Forge::ReforgeObjectProperties const *reforgeProperties;
	// s_multiplayer_object_properties &properties;
	// Forge::ForgeLightProperties const *lightProperties;
	// CForgeDeviceObjectProperties const *deviceProperties;
	// real_rgb_color changeColors[5];
	// s_forge_globals_definition *forge_globals;
	// Forge::CDefaultPropertyAccessor accessor;
	// s_map_variant *mapv;
	// __int32 changeColorCount;
	// s_multiplayer_object_properties *mpProperties;
	// Forge::ForgeMapModifierProperties const *mapModifierProperties;
	// Forge::ForgeGarbageVolumeProperties const *garbageVolumeProperties;
	{
		// c_tag_block<s_forge_sky_definition> &<range>$L0;
		// s_forge_sky_definition *<begin>$L0;
		// s_forge_sky_definition *<end>$L0;
		{
			// s_forge_sky_definition &sky;
		}
	}
	{
		// s_forge_weather_definition *<end>$L1;
		// s_forge_weather_definition *<begin>$L1;
		// c_tag_block<s_forge_weather_definition> &<range>$L1;
		{
			// s_forge_weather_definition &weatherEffect;
		}
	}
	{
		// s_forge_material_type *<end>$L2;
		// c_tag_block<s_forge_material_type> &<range>$L2;
		// s_forge_material_type *<begin>$L2;
		{
			// s_forge_material_type &mateiral_type;
		}
	}
	{
		// std::exception ex;
		// char buff[4096];
	}
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : bool (*)(unsigned __int32)
	// function call : unsigned long (*const)(long)
	// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)
	todo("implement");
	std::string __result = _sub_10CA7C80(placementIndex);
	return __result;
}

_extern void _sub_10CA7100(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &, ::Forge::CObjectPropertyAccessor &);
void DeserializeObjectProperties(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &json, ::Forge::CObjectPropertyAccessor &sink) // 0x10CA7100
{
	// `anonymous-namespace'::DeserializeObjectProperties
	// static ...; // 0x10CA73AA
	// static ...; // 0x10CA73A4
	// static ...; // 0x10CA73A1
	// static ...; // 0x10CA739C
	// static ...; // 0x10CA7360
	// static ...; // 0x10CA7358
// $LN17:
	// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &json;
	// Forge::CObjectPropertyAccessor &sink;
	// Forge::CObjectPropertyManager &propertyManager;
	{
		// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > it;
		{
			// Forge::EObjectProperty property;
			// Forge::SPropertyDefinition const *propertyDef;
			// char const *const &name;
			// Forge::SPropertyValue value;
			{
				// std::exception ex;
				// char buff[4096];
			}
		}
	}
	// function call : void (Forge::EObjectProperty, Forge::SPropertyValue)
	// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)
	todo("implement");
	_sub_10CA7100(json, sink);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template Forge::CObjectPropertyManager & Utils::Singleton<Forge::CObjectPropertyManager>::Instance();
template c_enum<enum e_forge_object_property_setter_type,unsigned char>::operator unsigned char() const;
template c_enum<enum e_multiplayer_object_type,char>::operator enum e_multiplayer_object_type() const;
template c_flags<enum e_forge_object_property_setter_flags,unsigned char> c_flags<enum e_forge_object_property_setter_flags,unsigned char>::operator&(__int32 const) const;
template c_flags<enum e_forge_object_property_setter_flags,unsigned char>::c_flags(unsigned char const &);
template c_flags<enum e_forge_object_property_setter_flags,unsigned char>::operator bool() const;
template c_tag_block_index<s_forge_description_text_entry,short>::operator short() const;
template c_tag_block_index<s_forge_palette_category,short>::operator short() const;
template s_forge_description_text_entry * c_tag_block<s_forge_description_text_entry>::begin();
template s_forge_description_text_entry * c_tag_block<s_forge_description_text_entry>::end();
template s_forge_material_type * c_tag_block<s_forge_material_type>::begin();
template s_forge_material_type * c_tag_block<s_forge_material_type>::end();
template s_forge_object_property_setter * c_tag_block<s_forge_object_property_setter>::begin();
template s_forge_object_property_setter * c_tag_block<s_forge_object_property_setter>::end();
template s_forge_palette_category * c_tag_block<s_forge_palette_category>::begin();
template s_forge_palette_category * c_tag_block<s_forge_palette_category>::end();
template s_forge_palette_item * c_tag_block<s_forge_palette_item>::begin();
template s_forge_palette_item * c_tag_block<s_forge_palette_item>::end();
template s_forge_sky_definition * c_tag_block<s_forge_sky_definition>::begin();
template s_forge_sky_definition * c_tag_block<s_forge_sky_definition>::end();
template s_forge_weather_definition * c_tag_block<s_forge_weather_definition>::begin();
template s_forge_weather_definition * c_tag_block<s_forge_weather_definition>::end();
template s_object_attachment_definition * c_tag_block<s_object_attachment_definition>::begin();
template s_object_attachment_definition * c_tag_block<s_object_attachment_definition>::end();
