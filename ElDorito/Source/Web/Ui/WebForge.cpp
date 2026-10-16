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

namespace eldorado
{
	// Functions in eldorado.exe, named as in ManagedDonkey.
	static auto const player_mapping_get_player_by_input_user = reinterpret_cast<unsigned long (*)(long)>(0x589C30);
}

namespace Forge { extern s_map_variant *GetMapVariant(); }  // hades: added for 0x10CA9010

extern void *(*const tag_get)(unsigned long, long);  // hades: added for 0x10CA7590

s_object_data *object_get(unsigned long objectIndex);  // hades: added for 0X10CA7900
namespace Forge { namespace Selection { extern Forge::ObjectSet &GetSelection(); } }  // hades: added for 0x10CA7C80
namespace Forge { namespace Reforge { extern bool IsReforgeObject(long objectIndex); extern bool IsGarbageCollectionObject(long objectIndex); extern bool IsKillVolumeObject(long objectIndex); extern bool IsMapModifierObject(long objectIndex); extern bool IsPrematchCameraObject(long objectIndex); extern bool IsPodiumPointObject(long objectIndex); } }  // hades: added for 0x10CA7C80
namespace Forge { extern bool ObjectIsForgeScenery(long objectIndex); }  // hades: added for 0x10CA7C80
extern s_multiplayer_object_properties *(*const object_get_multiplayer)(unsigned long);  // hades: added for 0x10CA7C80

namespace Web
{
	namespace Ui
	{
		namespace WebForge
		{
			extern std::string BuildForgePaletteJSON();
			extern void OnItemSpawned(unsigned __int32 objectIndex);
			extern void ShowObjectProperties(unsigned __int32 objectIndex);
			extern void ShowObjectCreation();
			extern Web::Browser::Bridge::QueryError ProcessAction(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result);
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
std::string SerializeObjectProperties(short placementIndex);
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
	::Forge::CDeferredPropertySetter m_itemSpawnPropertySetter; // 0x1247ED94  // hades: defined, so its dynamic initializer emits the constructor
}
using namespace hades_file_local;
/* ---------- public code */


namespace Web
{
	namespace Ui
	{
		namespace WebForge
		{
			std::string BuildForgePaletteJSON() // 0x10CA6A10
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?BuildForgePaletteJSON@WebForge@Ui@Web@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
				// procedure flags: nofpo
				// static ...; // 0x10CA6F8B
				// static ...; // 0x10CA6F84
				// static ...; // 0x10CA6F6C
				// static ...; // 0x10CA6F64
				// rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator> buffer;
				// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> writer;
				// s_forge_globals_definition *forge_globals;
					// c_tag_block<s_forge_palette_item> &<range>$L0;
					// s_forge_palette_item *<begin>$L0;
					// s_forge_palette_item *<end>$L0;
						// s_forge_palette_item &item;
							// s_forge_object_property_setter *<end>$L1;
							// s_forge_object_property_setter *<begin>$L1;
							// c_tag_block<s_forge_object_property_setter> &<range>$L1;
								// s_forge_object_property_setter &setter;
					// s_forge_palette_category *<end>$L2;
					// c_tag_block<s_forge_palette_category> &<range>$L2;
					// s_forge_palette_category *<begin>$L2;
						// s_forge_palette_category &category;
					// c_tag_block<s_forge_description_text_entry> &<range>$L3;
					// s_forge_description_text_entry *<begin>$L3;
					// s_forge_description_text_entry *<end>$L3;
						// s_forge_description_text_entry &description;

				rapidjson::StringBuffer buffer;
				rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
				writer.StartObject();
				writer.Key("palette");
				writer.StartArray();
				s_forge_globals_definition *forge_globals = forge_globals_get_definition();
				for (s_forge_palette_item &item : forge_globals->palette)
				{
					writer.StartObject();
					writer.Key("name");
					writer.String(item.name.ascii);
					writer.Key("tagIndex");
					writer.Int(item.object.index);
					writer.Key("type");
					writer.Int(item.type);
					writer.Key("categoryIndex");
					writer.Int(item.category_index);
					writer.Key("descriptionIndex");
					writer.Int(item.description_index);
					writer.Key("maxAllowed");
					writer.Int(item.max_allowed);
					writer.Key("setters");
					writer.StartArray();
					for (s_forge_object_property_setter &setter : item.setters)
					{
						writer.StartObject();
						writer.Key("target");
						writer.Int(setter.target);
						writer.Key("hidden");
						writer.Bool(setter.flags & 1);
						switch ((unsigned char)setter.type)
						{
						case _forge_object_property_setter_type_integer:
							writer.Key("type");
							writer.String("int");
							writer.Key("value");
							writer.Int(setter.integer_value);
							break;
						case _forge_object_property_setter_type_real:
							writer.Key("type");
							writer.String("float");
							writer.String("value");
							writer.Double(setter.real_value);
							break;
						}
						writer.EndObject();
					}
					writer.EndArray();
					writer.EndObject();
				}
				writer.EndArray();
				writer.Key("paletteCategories");
				writer.StartArray();
				for (s_forge_palette_category &category : forge_globals->palette_categories)
				{
					writer.StartObject();
					writer.Key("name");
					writer.String(category.name.ascii);
					writer.Key("descriptionIndex");
					writer.Int(category.description_index);
					writer.Key("parentCategoryIndex");
					writer.Int(category.parent_category_index);
					writer.EndObject();
				}
				writer.EndArray();
				writer.Key("descriptions");
				writer.StartArray();
				for (s_forge_description_text_entry &description : forge_globals->descriptions)
					writer.String(description.text.ascii);
				writer.EndArray();
				writer.EndObject();
				return buffer.GetString();
			}
		}
	}
}

namespace Forge
{
	// mangled_x86(MANGLED_DEFAULT, "??0CDeferredPropertySetter@Forge@@QAE@XZ"); no body to assert in

}

namespace Web
{
	namespace Ui
	{
		namespace WebForge
		{
			void OnItemSpawned(unsigned __int32 objectIndex) // 0x10CA7900
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?OnItemSpawned@WebForge@Ui@Web@@YAXI@Z");
				// unsigned __int32 objectIndex;
				// s_object_data *object;
				// function call : unsigned long (*const)(long)

				s_object_data *object = object_get(objectIndex);
				if (!object || object->map_variant_index == -1) { return; }
				m_itemSpawnPropertySetter.Apply(((int (__cdecl *)(int))0x589c30)(0), objectIndex);
			}

			void ShowObjectProperties(unsigned __int32 objectIndex) // 0x10CA9010
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?ShowObjectProperties@WebForge@Ui@Web@@YAXI@Z");
				// static ...; // 0x10CA914C
				// static ...; // 0x10CA9140
				// static ...; // 0x10CA9138
				// unsigned __int32 objectIndex;
				// s_object_data *currentObject;
					// s_variant_datum placement;
					// s_map_variant *mapv;

				s_object_data *currentObject = object_get(objectIndex);
				if (currentObject)
				{
					if (currentObject->map_variant_index != 0xFFFF)
					{
						s_map_variant *mapv = Forge::GetMapVariant();
						s_variant_datum placement = static_cast<s_variant_datum const &>(mapv->objects[currentObject->map_variant_index]);
						s_CurrentObjectIndex = objectIndex;
						ScreenLayer::Show(ScreenLayer::ForgeObjectProperties, SerializeObjectProperties(currentObject->map_variant_index));
					}
				}
			}

			void ShowObjectCreation() // 0x10CA8CE0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?ShowObjectCreation@WebForge@Ui@Web@@YAXXZ");
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
					// __int32 i;
						// s_variant_quota const &itemBudget;

				s_map_variant *const mapv = Forge::GetMapVariant();
				if (!mapv)
					return;
				rapidjson::StringBuffer buffer;
				rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
				char buff[256];
				writer.StartObject();
				writer.Key("budget");
				writer.StartArray();
				for (__int32 i = 0; i < mapv->placeable_object_quota_count; i++)
				{
					s_variant_quota const &itemBudget = mapv->object_quotas[i];
					sprintf_s(buff, 256, "0x%x", itemBudget.definition_index);
					writer.StartObject();
					writer.Key("tagindex");
					writer.String(buff);
					SerializeProperty(writer, "max_allowed", itemBudget.maximum_allowed);
					SerializeProperty(writer, "count_on_map", itemBudget.placed_on_map);
					SerializeProperty(writer, "runtime_min", itemBudget.minimum_count);
					SerializeProperty(writer, "runtime_max", itemBudget.maximum_count);
					writer.EndObject();
				}
				writer.EndArray();
				writer.EndObject();
				ScreenLayer::Show(ScreenLayer::ForgeObjectCreation, buffer.GetString());
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

		}
	}
}

namespace Web
{
	namespace Ui
	{
		namespace WebForge
		{
			Web::Browser::Bridge::QueryError ProcessAction(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args, std::string *p_Result) // 0x10CA79A0
			{
				mangled_x86(MANGLED_KNOWN_GOOD, "?ProcessAction@WebForge@Ui@Web@@YA?AW4QueryError@Bridge@Browser@3@ABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@PAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z");
				// static ...; // 0x10CA7BDD
				// static ...; // 0x10CA7BD8
				// static ...; // 0x10CA7BB4
				// static ...; // 0x10CA7BAC
				// rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &p_Args;
				// std::string *p_Result;
				// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > data;
				// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > type;
					// s_object_data *currentObject;
						// Forge::CDefaultPropertyAccessor sink;
						// unsigned long playerIndex;
						// s_map_variant *mapv;
				// function call : unsigned long (*const)(long)

				auto type = p_Args.FindMember("type");
				auto data = p_Args.FindMember("data");
				if (type == p_Args.MemberEnd() || !type->value.IsNumber())
				{
					*p_Result = "Bad query : A \"type\" argument is required and must be a number";
					return Web::Browser::Bridge::QueryError_BadQuery;
				}
				if (data == p_Args.MemberEnd() || !data->value.IsObject())
				{
					*p_Result = "Bad query : \"data\" argument is required and must be a object";
					return Web::Browser::Bridge::QueryError_BadQuery;
				}
				switch (type->value.GetInt())
				{
				case 1:
				{
					s_object_data *currentObject = object_get(s_CurrentObjectIndex);
					if (currentObject && currentObject->map_variant_index != -1)
					{
						s_map_variant *mapv = Forge::GetMapVariant();
						unsigned long playerIndex = ((unsigned long (__cdecl *)(long))0x589C30)(0);
						Forge::CDefaultPropertyAccessor sink(playerIndex, s_CurrentObjectIndex);
						DeserializeObjectProperties(data->value, sink);
					}
					break;
				}
				case 2:
					m_itemSpawnPropertySetter.Reset();
					DeserializeObjectProperties(data->value, m_itemSpawnPropertySetter);
					break;
				}
				return Web::Browser::Bridge::QueryError_Ok;
			}
		}
	}
}

/* ---------- private code */

void SerializeProperty(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, char const *key, __int32 value) // 0x10CA8B80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SerializeProperty@@YAXAAV?$Writer@V?$GenericStringBuffer@U?$UTF8@D@rapidjson@@VCrtAllocator@2@@rapidjson@@U?$UTF8@D@2@U32@VCrtAllocator@2@$0A@@rapidjson@@PBDH@Z");
	// `anonymous-namespace'::SerializeProperty
	// __int32 value;

	writer.Key(key);
	writer.Int(value);
}

void SerializeProperty(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, char const *key, float value) // 0x10CA8BE0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SerializeProperty@@YAXAAV?$Writer@V?$GenericStringBuffer@U?$UTF8@D@rapidjson@@VCrtAllocator@2@@rapidjson@@U?$UTF8@D@2@U32@VCrtAllocator@2@$0A@@rapidjson@@PBDM@Z");
	// `anonymous-namespace'::SerializeProperty
	// float value;

	if (!isnan(value) && !isinf(value))
	{
		writer.Key(key);
		writer.Double(value);
	}
}

void SerializeProperty(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, char const *key, bool value) // 0x10CA8C80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SerializeProperty@@YAXAAV?$Writer@V?$GenericStringBuffer@U?$UTF8@D@rapidjson@@VCrtAllocator@2@@rapidjson@@U?$UTF8@D@2@U32@VCrtAllocator@2@$0A@@rapidjson@@PBD_N@Z");
	// `anonymous-namespace'::SerializeProperty
	// bool value;

	writer.Key(key);
	writer.Bool(value);
}

bool IsForgeLight(unsigned __int32 objectIndex) // 0x10CA7590
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?IsForgeLight@@YA_NI@Z");
	// `anonymous-namespace'::IsForgeLight
	// unsigned __int32 objectIndex;
	// s_object_data *object;
	// s_object_definition *objectDef;
		// c_tag_block<s_object_attachment_definition> &<range>$L0;
		// s_object_attachment_definition *<begin>$L0;
		// s_object_attachment_definition *<end>$L0;
			// s_object_attachment_definition const &attachment;
				// unsigned __int32 lightFlags;
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)

	s_object_data *object = object_get(objectIndex);
	if (!object)
		return false;
	s_object_definition *objectDef = (s_object_definition *)tag_get('obje', object->definition_index);
	if (!objectDef)
		return false;
	for (auto const &attachment : objectDef->attachments)
	{
		if (attachment.type.group_tag != 'ligh')
			continue;
		unsigned __int32 lightFlags = *(unsigned __int32 *)tag_get('ligh', attachment.type.index);
		if (lightFlags & 0x80000000)
			return true;
	}
	return false;
}

bool IsForgeScreenEffectObject(unsigned __int32 objectIndex) // 0x10CA76E0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?IsForgeScreenEffectObject@@YA_NI@Z");
	// `anonymous-namespace'::IsForgeScreenEffectObject
	// unsigned __int32 objectIndex;
	// s_object_data *object;
	// s_object_definition *objectDef;
		// c_tag_block<s_object_attachment_definition> &<range>$L0;
		// s_object_attachment_definition *<begin>$L0;
		// s_object_attachment_definition *<end>$L0;
			// s_object_attachment_definition const &attachment;
	// function call : void *(*const)(unsigned long, long)

	s_object_data *object = object_get(objectIndex);
	if (!object)
		return false;
	s_object_definition *objectDef = (s_object_definition *)tag_get('obje', object->definition_index);
	if (!objectDef)
		return false;
	for (auto const &attachment : objectDef->attachments)
	{
		if (attachment.type.group_tag != 'effe')
			continue;
		if (attachment.marker == 0x13BB)
			return true;
	}
	return false;
}

long ObjectGetChangeColors(long objectIndex, real_rgb_color *outColors) // 0x10CA7800
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?ObjectGetChangeColors@@YAJJPAUreal_rgb_color@@@Z");
	// `anonymous-namespace'::ObjectGetChangeColors
	// real_rgb_color *outColors;
	// real_rgb_color *colors;
	// s_object_data *object;
	// unsigned __int32 count;
		// __int32 i;

	s_object_data *object = object_get(objectIndex);
	if (!object)
		return 0;
	if (object->change_colors.size <= 0)
		return 0;
	unsigned __int32 count = object->change_colors.size / sizeof(real_rgb_color) / 2;
	real_rgb_color *colors = (real_rgb_color *)offset_pointer(object, object->change_colors.offset);
	for (__int32 i = 0; i < count; i++)
		outColors[i] = colors[i];
	return count;
}

void SerializeObjectProperties(rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer, ::Forge::CObjectPropertyAccessor &accessor) // 0x10CA8900
{
	// `anonymous-namespace'::SerializeObjectProperties
	// static ...; // 0x10CA8AEC
	// static ...; // 0x10CA8AE4
	// rapidjson::Writer<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>,rapidjson::CrtAllocator>,rapidjson::UTF8<char>,rapidjson::UTF8<char>,rapidjson::CrtAllocator,0> &writer;
	// Forge::CObjectPropertyAccessor &accessor;
	// Forge::CObjectPropertyManager &propertyManager;
		// std::array<Forge::SPropertyDefinition,90> const &<range>$L0;
		// Forge::SPropertyDefinition const *<begin>$L0;
		// Forge::SPropertyDefinition const *<end>$L0;
			// Forge::SPropertyDefinition const &propertyDef;
				// float value;
	// function call : Forge::SPropertyValue (Forge::EObjectProperty)
	// function call : Forge::SPropertyValue (Forge::EObjectProperty)

	::Forge::CObjectPropertyManager &propertyManager = Utils::Singleton<::Forge::CObjectPropertyManager>::Instance();
	for (::Forge::SPropertyDefinition const &propertyDef : propertyManager.GetProperties())
	{
		switch (propertyDef.valueType)
		{
		case ::Forge::Integer:
			writer.Key(propertyDef.name);
			writer.Int(accessor.GetPropertyValue(propertyDef.property).intValue);
			break;
		case ::Forge::Real:
		{
			float value = accessor.GetPropertyValue(propertyDef.property).realValue;
			if (!isnan(value) && !isinf(value))
			{
				writer.Key(propertyDef.name);
				writer.Double(value);
			}
			break;
		}
		}
	}
}

std::string SerializeObjectProperties(short placementIndex) // 0x10CA7C80
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?SerializeObjectProperties@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@F@Z");
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
		// c_tag_block<s_forge_sky_definition> &<range>$L0;
		// s_forge_sky_definition *<begin>$L0;
		// s_forge_sky_definition *<end>$L0;
			// s_forge_sky_definition &sky;
		// s_forge_weather_definition *<end>$L1;
		// s_forge_weather_definition *<begin>$L1;
		// c_tag_block<s_forge_weather_definition> &<range>$L1;
			// s_forge_weather_definition &weatherEffect;
		// s_forge_material_type *<end>$L2;
		// c_tag_block<s_forge_material_type> &<range>$L2;
		// s_forge_material_type *<begin>$L2;
			// s_forge_material_type &mateiral_type;
		// std::exception ex;
		// char buff[4096];
	// function call : s_multiplayer_object_properties *(*const)(unsigned long)
	// function call : bool (*)(unsigned __int32)
	// function call : unsigned long (*const)(long)
	// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)

	static bool (*Weapon_HasSpareClips)(unsigned __int32) = (bool (*)(unsigned __int32))0xB624E0;
	s_map_variant *mapv = Forge::GetMapVariant();
	s_variant_datum placement = static_cast<s_variant_datum const &>(mapv->objects[placementIndex]);
	if (placement.quota_index == -1)
		return "{}";
	s_variant_quota const &budget = mapv->object_quotas[placement.quota_index];
	s_object_data *object = object_get(placement.object_index);
	if (!object)
		return "{}";
	s_multiplayer_object_properties *mpProperties = object_get_multiplayer(placement.object_index);
	if (!mpProperties)
		return "{}";
	s_multiplayer_object_properties &properties = *mpProperties;
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	Forge::ForgeLightProperties const *lightProperties = (Forge::ForgeLightProperties const *)&properties.boundry_width;
	Forge::ForgeScreenFxProperties const *screenFxProperties = (Forge::ForgeScreenFxProperties const *)&properties.boundry_width;
	Forge::ReforgeObjectProperties const *reforgeProperties = (Forge::ReforgeObjectProperties const *)&properties.boundry_width;
	Forge::ForgeMapModifierProperties const *mapModifierProperties = (Forge::ForgeMapModifierProperties const *)&properties.boundry_width;
	Forge::ForgeGarbageVolumeProperties const *garbageVolumeProperties = (Forge::ForgeGarbageVolumeProperties const *)&properties.teleporter_channel;
	Forge::ForgeKillVolumeProperties const *killVolumeProperties = (Forge::ForgeKillVolumeProperties const *)&properties.teleporter_channel;
	CForgeDeviceObjectProperties const *deviceProperties = (CForgeDeviceObjectProperties const *)&properties.boundry_width;
	EForgeDeviceType forgeDeviceType = Utils::Singleton<CForgeDeviceManager>::Instance().GetDeviceType(s_CurrentObjectIndex);
	real_rgb_color changeColors[5];
	__int32 changeColorCount = ObjectGetChangeColors(placement.object_index, changeColors);
	writer.StartObject();
	SerializeProperty(writer, "tag_index", int(budget.definition_index));
	SerializeProperty(writer, "object_index", int(s_CurrentObjectIndex));
	SerializeProperty(writer, "object_type", object_get_type(placement.object_index));
	SerializeProperty(writer, "object_type_mp", static_cast<e_multiplayer_object_type>(properties.multiplayer_object_type));
	SerializeProperty(writer, "has_material", Forge::Reforge::IsReforgeObject(s_CurrentObjectIndex));
	SerializeProperty(writer, "has_spare_clips", properties.multiplayer_object_type == _object_multiplayer_type_weapon && !Weapon_HasSpareClips(budget.definition_index));
	SerializeProperty(writer, "is_selected", Forge::Selection::GetSelection().Contains(placement.object_index));
	SerializeProperty(writer, "is_light", IsForgeLight(placement.object_index));
	SerializeProperty(writer, "is_garbage_volume", Forge::Reforge::IsGarbageCollectionObject(placement.object_index));
	SerializeProperty(writer, "is_kill_volume", Forge::Reforge::IsKillVolumeObject(placement.object_index));
	SerializeProperty(writer, "is_map_modifier", Forge::Reforge::IsMapModifierObject(placement.object_index));
	SerializeProperty(writer, "is_screenfx", IsForgeScreenEffectObject(placement.object_index));
	SerializeProperty(writer, "is_forge_scenery", Forge::ObjectIsForgeScenery(placement.object_index));
	SerializeProperty(writer, "is_prematch_camera", Forge::Reforge::IsPrematchCameraObject(placement.object_index));
	SerializeProperty(writer, "is_podium_point", Forge::Reforge::IsPodiumPointObject(placement.object_index));
	SerializeProperty(writer, "change_color_count", changeColorCount);
	s_forge_globals_definition *forge_globals = forge_globals_get_definition();
	writer.Key("options");
	writer.StartObject();
	writer.Key("skies");
	writer.StartArray();
	if (forge_globals)
	{
		for (s_forge_sky_definition &sky : forge_globals->skies)
			writer.String(sky.name.ascii);
	}
	writer.EndArray();
	writer.Key("weather_effects");
	writer.StartArray();
	if (forge_globals)
	{
		for (s_forge_weather_definition &weatherEffect : forge_globals->weather_effects)
			writer.String(weatherEffect.name.ascii);
	}
	writer.EndArray();
	writer.Key("material_types");
	writer.StartArray();
	if (forge_globals)
	{
		for (s_forge_material_type &mateiral_type : forge_globals->material_types)
			writer.String(mateiral_type.name.ascii);
	}
	writer.EndArray();
	writer.EndObject();
	writer.Key("properties");
	writer.StartObject();
	long playerIndex = eldorado::player_mapping_get_player_by_input_user(0);
	Forge::CDefaultPropertyAccessor accessor(playerIndex, placement.object_index);
	try
	{
		SerializeObjectProperties(writer, accessor);
	}
	catch (std::exception ex)
	{
		char buff[4096];
		sprintf_s(buff, "Error serializing forge object properties: %s\n", ex.what());
		MessageBoxA(NULL, ex.what(), "Error", MB_ICONERROR);
	}
	writer.EndObject();
	SerializeProperty(writer, "device_type", forgeDeviceType);
	writer.Key("budget");
	writer.StartObject();
	SerializeProperty(writer, "summary_placed_on_map", budget.placed_on_map);
	SerializeProperty(writer, "summary_total_cost", budget.placed_on_map * budget.cost);
	SerializeProperty(writer, "summary_maximum_allowed", budget.maximum_allowed);
	SerializeProperty(writer, "summary_runtime_minimum", budget.minimum_count);
	SerializeProperty(writer, "summary_runtime_maximum", budget.maximum_count);
	writer.EndObject();
	writer.EndObject();
	return buffer.GetString();
}

void DeserializeObjectProperties(rapidjson::GenericValue<rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > const &json, ::Forge::CObjectPropertyAccessor &sink) // 0x10CA7100
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?DeserializeObjectProperties@@YAXABV?$GenericValue@U?$UTF8@D@rapidjson@@V?$MemoryPoolAllocator@VCrtAllocator@rapidjson@@@2@@rapidjson@@AAVCObjectPropertyAccessor@Forge@@@Z");
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
		// rapidjson::GenericMemberIterator<1,rapidjson::UTF8<char>,rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> > it;
			// Forge::EObjectProperty property;
			// Forge::SPropertyDefinition const *propertyDef;
			// char const *const &name;
			// Forge::SPropertyValue value;
				// std::exception ex;
				// char buff[4096];
	// function call : void (Forge::EObjectProperty, Forge::SPropertyValue)
	// function call : __int32 (HWND__ *, char const *, char const *, unsigned __int32)

	Forge::CObjectPropertyManager &propertyManager = Utils::Singleton<Forge::CObjectPropertyManager>::Instance();
	for (auto it = json.MemberBegin(); it != json.MemberEnd(); ++it)
	{
		const char *const &name = it->name.GetString();
		Forge::EObjectProperty property = propertyManager.FindPropertyByName(name);
		const Forge::SPropertyDefinition *propertyDef = propertyManager.GetProperty(property);
		Forge::SPropertyValue value;
		switch (propertyDef->valueType)
		{
		case Forge::EPropertyValueType::Integer:
			if (it->value.IsNumber())
				value = Forge::SPropertyValue::Integer(it->value.GetInt());
			break;
		case Forge::EPropertyValueType::Real:
			if (it->value.IsNumber())
				value = Forge::SPropertyValue::Real(it->value.GetFloat());
			break;
		}
		try
		{
			sink.SetPropertyValue(property, value);
		}
		catch (std::exception ex)
		{
			char buff[4096];
			sprintf_s(buff, "Error setting forge object property: %s\n", ex.what());
			MessageBoxA(NULL, ex.what(), "Error", MB_ICONERROR);
		}
	}
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

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { unsigned __int32 s_CurrentObjectIndex = 0xffffffff; }
