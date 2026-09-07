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
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/objects/damage.hpp"
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
#include "Forge/Geoemetry.hpp"
#include "Forge/ObjectProperties/ForgeObjectPropertyAccessor.hpp"
#include "Forge/ObjectProperties/ForgeObjectPropertyManager.hpp"
#include "Forge/ObjectProperties/ForgePropertyValue.hpp"
#include "Forge/ObjectSet.hpp"
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

struct begin;
struct end;
struct s_forge_description_text_entry;
struct s_forge_globals_definition;
struct s_forge_object_property_setter;
struct s_forge_palette_category;
struct s_forge_palette_item;
struct s_map_variant;
struct s_object_data;
struct s_variant_datum;
struct s_variant_quota;
namespace Forge
{
	class CDefaultPropertyAccessor;
	class CDeferredPropertySetter;
	class CObjectPropertyManager;
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

/* ---------- globals */

namespace Utils
{
	::Forge::CObjectPropertyManager *Utils::Singleton< ::Forge::CObjectPropertyManager>::m_instance; // 0x1247ED90
}

/* ---------- private variables */

namespace
{
	extern unsigned __int32 s_CurrentObjectIndex; // 0x113553F0
	extern ::Forge::CDeferredPropertySetter m_itemSpawnPropertySetter; // 0x1247ED94
}
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
	extern CDeferredPropertySetter* _sub_10CA64C0(::Forge::CDeferredPropertySetter *const);
	_inline CDeferredPropertySetter::CDeferredPropertySetter() // 0x10CA64C0
	{
		mangled_x86(MANGLED_TODO, "??0CDeferredPropertySetter@Forge@@QAE@XZ");
		// Forge::CDeferredPropertySetter *const this;
		compiler_generated();
		todo("implement");
		_sub_10CA64C0(this);
	}

	_extern void _sub_10CA67C0(::Forge::CDeferredPropertySetter *const);
	_inline CDeferredPropertySetter::~CDeferredPropertySetter() // 0x10CA67C0
	{
		mangled_x86(MANGLED_TODO, "??1CDeferredPropertySetter@Forge@@UAE@XZ");
		// Forge::CDeferredPropertySetter *const this;
		compiler_generated();
		todo("implement");
		_sub_10CA67C0(this);
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
