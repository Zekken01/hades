/* ---------- headers */

#include "Forge/Magnets.hpp"
#include "hades/hades.h"

#include "Blam/cache/cache_files.hpp"
#include "Blam/cseries/cseries.hpp"
#include "Blam/cseries/enums.inl"
#include "Blam/cseries/flags.inl"
#include "Blam/game/engine/game_engine_option.hpp"
#include "Blam/game/game_variant.hpp"
#include "Blam/game/player_appearance.hpp"
#include "Blam/game/player_configuration.inl"
#include "Blam/game/players.hpp"
#include "Blam/hs/hs.hpp"
#include "Blam/items/equipment_definitions.hpp"
#include "Blam/math/real_math.inl"
#include "Blam/math/real_math_definitions.hpp"
#include "Blam/memory/data_array.inl"
#include "Blam/models/model_definitions.hpp"
#include "Blam/objects/damage.hpp"
#include "Blam/objects/object_definitions.hpp"
#include "Blam/objects/objects.hpp"
#include "Blam/physics/collision_bsp.hpp"
#include "Blam/physics/collision_model.hpp"
#include "Blam/rasterizer/rasterizer_geometry.hpp"
#include "Blam/render/render_model.hpp"
#include "Blam/structures/cluster_reference.hpp"
#include "Blam/tag_files/file_reference.inl"
#include "Blam/tag_files/files.hpp"
#include "Blam/tag_files/tag_block.inl"
#include "Blam/tag_files/tag_groups.hpp"
#include "ChatCommands/ChatCommandMap.hpp"
#include "Common/Http/HttpHeaders.hpp"
#include "ElDorito.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/ObjectSet.hpp"
#include "Pointer.hpp"
#include "ThirdParty/rapidjson/allocators.h"
#include "ThirdParty/rapidjson/document.h"
#include "ThirdParty/rapidjson/encodedstream.h"
#include "ThirdParty/rapidjson/error/en.h"
#include "ThirdParty/rapidjson/error/error.h"
#include "ThirdParty/rapidjson/internal/biginteger.h"
#include "ThirdParty/rapidjson/internal/diyfp.h"
#include "ThirdParty/rapidjson/internal/ieee754.h"
#include "ThirdParty/rapidjson/internal/pow10.h"
#include "ThirdParty/rapidjson/internal/strtod.h"
#include "ThirdParty/rapidjson/memorystream.h"
#include "ThirdParty/rapidjson/reader.h"
#include "Utils/Macros.hpp"
#include "Utils/Singleton.hpp"
#include "Utils/String.hpp"

#include <boost/asio.hpp>
#include <boost/assert.hpp>
#include <boost/exception/all.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/parameter/aux_/use_default_tag.hpp>
#include <boost/throw_exception.hpp>

#include <Windows.h>
#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/is_alignment.hpp>
#include <boost/current_function.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/parameter/aux_/void.hpp>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <algorithm>
#include <atomic>
#include <bitset>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <functional>
#include <ios>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <limits>
#include <memory>
#include <mutex>
#include <ostream>
#include <ratio>
#include <sstream>
#include <stdexcept>
#include <stop_token>
#include <streambuf>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

/* ---------- forward declarations */

struct collision_model_definition;
struct collision_model_instance;
struct collision_vertex;
struct model_definition;
struct real_matrix4x3;
struct real_point3d;
struct real_vector3d;
struct s_cluster_reference;
struct s_collision_model_bsp_iterator;
struct s_model_definition;
struct s_object_data;
struct s_object_definition;
struct s_player_datum;
struct s_render_model;
struct s_render_model_marker_group;
namespace Forge
{
	class ObjectSet;
}
namespace Forge
{
	namespace Magnets
	{
		struct Magnet;
		struct MagnetPair;
	}
}
namespace hades_file_local
{
	class MagnetManager;
}
using namespace hades_file_local;

namespace Utils {}
using namespace ::Utils;
namespace Utils
{
	namespace AntiCheat {}
	using namespace Utils::AntiCheat;
}

namespace Modules {}
using namespace ::Modules;
namespace Forge {}
using namespace ::Forge;
namespace Forge
{
	namespace Magnets {}
	using namespace Forge::Magnets;
	namespace Selection {}
	using namespace Forge::Selection;
	namespace Geoemetry {}
	using namespace Forge::Geoemetry;
}

namespace base
{
	namespace internal {}
	using namespace base::internal;
}

namespace Blam {}
using namespace ::Blam;
namespace Blam
{
	namespace Cache {}
	using namespace Blam::Cache;
}

/* ---------- constants */

/* ---------- definitions */

namespace hades_file_local
{
	class MagnetManager
	{
	public:
		MagnetManager();
		void Update();
		void Render();
		void RenderMagnet(Forge::Magnets::Magnet const &);
		Forge::Magnets::MagnetPair const &GetMagnetPair() const;
	private:
		unsigned __int32 m_LastCheck; // 0x0
		__int32 m_NumSourceMagnets; // 0x4
		__int32 m_NumDestMagnets; // 0x8
		Forge::Magnets::MagnetPair m_MagnetPairing; // 0xC
		Forge::Magnets::Magnet m_SourceMagnets[512]; // 0x18
		Forge::Magnets::Magnet m_DestMagnets[2048]; // 0x1818
		void GetObjectMarkers(unsigned __int32, std::vector<real_point3d,std::allocator<real_point3d> > &);
		void AddSourceObject(unsigned __int32);
		void AddDestObject(unsigned __int32);
		void PerformPairing();
	};
	static_assert(sizeof(MagnetManager) == 30744, "Invalid MagnetManager size");

}
using namespace hades_file_local;
/* ---------- prototypes */

namespace Forge
{
	namespace Magnets
	{
		extern bool Initialize();
		extern void Shutdown();
		extern void Update();
		extern void Render();
		extern Forge::Magnets::MagnetPair const &GetMagnetPair();
	}
}

bool MagnetsEnabled();
bool MagnetsVisible();
unsigned short GetPlasmaShaderTagIndex();
__int32 FindMagnetMarkerGroup(s_render_model const *renderModel);
void GetMagnetsFromCollisionModel(unsigned __int32 objectIndex, std::vector<real_point3d,std::allocator<real_point3d> > &markers);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern char const *MARKER_GROUP_NAME; // 0x11353D3C
	extern unsigned long markerGroupName; // 0x1240FB58
}
using namespace hades_file_local;
/* ---------- public code */

namespace Forge
{
	namespace Magnets
	{
		_extern bool _sub_1096D1B0();
		bool Initialize() // 0x1096D1B0
		{
			mangled_x86(MANGLED_TODO, "?Initialize@Magnets@Forge@@YA_NXZ");
			// procedure flags: nofpo
			todo("implement");
			bool __result = _sub_1096D1B0();
			return __result;
		}

		_extern void _sub_1096DE20();
		void Shutdown() // 0x1096DE20
		{
			mangled_x86(MANGLED_TODO, "?Shutdown@Magnets@Forge@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_1096DE20();
		}

		_extern void _sub_1096E210();
		void Update() // 0x1096E210
		{
			mangled_x86(MANGLED_TODO, "?Update@Magnets@Forge@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_1096E210();
		}

		_extern void _sub_1096D8C0();
		void Render() // 0x1096D8C0
		{
			mangled_x86(MANGLED_TODO, "?Render@Magnets@Forge@@YAXXZ");
			// procedure flags: nofpo
			todo("implement");
			_sub_1096D8C0();
		}

		extern MagnetPair const &_sub_1096CB80();
		Forge::Magnets::MagnetPair const &GetMagnetPair() // 0x1096CB80
		{
			mangled_x86(MANGLED_TODO, "?GetMagnetPair@Magnets@Forge@@YAABUMagnetPair@12@XZ");
			// procedure flags: nofpo
			// static Forge::Magnets::MagnetPair nullMagnetPair; // 0x1240FB5C
			todo("implement");
			Forge::Magnets::MagnetPair const & __result = _sub_1096CB80();
			return __result;
		}
	}
}

/* ---------- private code */

extern MagnetManager* _sub_1096C1A0(MagnetManager *const);
_inline MagnetManager::MagnetManager() // 0x1096C1A0
{
	// `anonymous-namespace'::MagnetManager::MagnetManager
	// MagnetManager *const this;
	todo("implement");
	_sub_1096C1A0(this);
}

namespace Forge
{
	namespace Magnets
	{
		extern MagnetPair const &_sub_1096CB50(MagnetManager const *const);
	}
}

_inline Forge::Magnets::MagnetPair const &MagnetManager::GetMagnetPair() const // 0x1096CB50
{
	// `anonymous-namespace'::MagnetManager::GetMagnetPair
	// MagnetManager const *const this;
	todo("implement");
	Forge::Magnets::MagnetPair const & __result = _sub_1096CB50((MagnetManager const *)this);
	return __result;
}

_extern bool _sub_1096D360();
bool MagnetsEnabled() // 0x1096D360
{
	// `anonymous-namespace'::MagnetsEnabled
	// procedure flags: nofpo
	todo("implement");
	bool __result = _sub_1096D360();
	return __result;
}

_extern bool _sub_1096D3D0();
bool MagnetsVisible() // 0x1096D3D0
{
	// `anonymous-namespace'::MagnetsVisible
	// procedure flags: nofpo
	todo("implement");
	bool __result = _sub_1096D3D0();
	return __result;
}

_extern void _sub_1096DE70(MagnetManager *const);
void MagnetManager::Update() // 0x1096DE70
{
	// `anonymous-namespace'::MagnetManager::Update
	// static ...; // 0x1096E13D
	// static ...; // 0x1096E12C
	// static ...; // 0x1096E114
	// static ...; // 0x1096E10C
	// MagnetManager *const this;
	// long heldObjectIndex;
	// Forge::ObjectSet const &selection;
	// unsigned long playerIndex;
	{
		// s_object_data const *heldObject;
		{
			// long objectIndex;
			{
				// s_object_data *object;
			}
		}
	}
	{
		// short numProximityObjects;
		// long proximityObjects[256];
		{
			// __int32 i;
			{
				// long objectIndex;
			}
		}
	}
	// function call : unsigned long (*const)(long)
	// function call : bool (*const)(long, long *, long *)
	// function call : long (*const)()
	// function call : float (*const)(float)
	// function call : long (*const)()
	// function call : short (*const)(long, long, s_cluster_reference const *, real_point3d const *, float, long *, short)
	todo("implement");
	_sub_1096DE70(this);
}

_extern void _sub_1096D440(MagnetManager *const);
void MagnetManager::PerformPairing() // 0x1096D440
{
	// `anonymous-namespace'::MagnetManager::PerformPairing
	// static ...; // 0x1096D69C
	// static ...; // 0x1096D690
	// static ...; // 0x1096D688
	// MagnetManager *const this;
	// s_player_datum *player;
	// float shortestDistance;
	// unsigned long playerIndex;
	// real_matrix4x3 unitTransform;
	// float const minDistance;
	// float shortestUnitDistance;
	{
		// __int32 i;
		{
			// float unitDistance;
			// Forge::Magnets::Magnet const &sourceMagnet;
			{
				// __int32 j;
				{
					// float distance2;
					// Forge::Magnets::Magnet const &destMagnet;
				}
			}
		}
	}
	// function call : unsigned long (*const)(long)
	// function call : real_matrix4x3 *(*const)(long, real_matrix4x3 *)
	todo("implement");
	_sub_1096D440(this);
}

_extern void _sub_1096D940(MagnetManager *const, Forge::Magnets::Magnet const &);
void MagnetManager::RenderMagnet(Forge::Magnets::Magnet const &magnet) // 0x1096D940
{
	// `anonymous-namespace'::MagnetManager::RenderMagnet
	// static ...; // 0x1096DD1A
	// static ...; // 0x1096DD12
	// static ...; // 0x1096DD0D
	// static ...; // 0x1096DD0A
	// static ...; // 0x1096DD08
	// static ...; // 0x1096DCC0
	// static ...; // 0x1096DCB8
	// MagnetManager *const this;
	// Forge::Magnets::Magnet const &magnet;
	// __int32 v14;
	// constexpr __int32 (*const `MagnetManager::RenderMagnet'::`2'::DrawPrimitive)(__int32, __int32, void *, __int32); // constant == 10650416
	// real_vector3d forward;
	// constexpr __int32 (*const `MagnetManager::RenderMagnet'::`2'::sub_A232D0)(__int32); // constant == 10629840
	// constexpr __int32 (*const `MagnetManager::RenderMagnet'::`2'::sub_A22BA0)(); // constant == 10628000
	// float const scale;
	// constexpr void (*const `MagnetManager::RenderMagnet'::`2'::SetShaderConstant)(__int32, __int32, float const *); // constant == 10904592
	// real_vector3d left;
	// real_vector3d up;
	// float m[12];
	{
		// float const color[4];
	}
	{
	}
	// function call : void (*const)(__int32, __int32, float const *)
	// function call : void (*const)(__int32, __int32, float const *)
	// function call : void (*const)(__int32, __int32, float const *)
	// function call : __int32 (*const)()
	// function call : __int32 (*const)(__int32)
	// function call : __int32 (*const)(__int32, __int32, void *, __int32)
	// function call : __int32 (*const)(__int32, __int32, void *, __int32)
	// function call : __int32 (*const)(__int32, __int32, void *, __int32)
	// function call : __int32 (*const)(__int32, __int32, void *, __int32)
	// function call : __int32 (*const)(__int32, __int32, void *, __int32)
	// function call : __int32 (*const)(__int32, __int32, void *, __int32)
	// function call : __int32 (*const)(__int32)
	todo("implement");
	_sub_1096D940(this, magnet);
}

_extern unsigned short _sub_1096D120();
unsigned short GetPlasmaShaderTagIndex() // 0x1096D120
{
	// `anonymous-namespace'::GetPlasmaShaderTagIndex
	// procedure flags: nofpo
	// static long `GetPlasmaShaderTagIndex'::`2'::tagIndex; // 0x11353D44
	// static bool `GetPlasmaShaderTagIndex'::`2'::tagLookup; // 0x11353D40
	todo("implement");
	unsigned short __result = _sub_1096D120();
	return __result;
}

_extern void _sub_1096D750(MagnetManager *const);
void MagnetManager::Render() // 0x1096D750
{
	// `anonymous-namespace'::MagnetManager::Render
	// MagnetManager *const this;
	// void *shaderDef;
	// constexpr bool (*const `MagnetManager::Render'::`2'::UseDefaultShader)(__int32, __int32, __int32, __int32); // constant == 10629888
	// constexpr void (*const `MagnetManager::Render'::`2'::sub_A3CA60)(unsigned __int32, void *, __int32, unsigned __int32, __int32, __int32); // constant == 10734176
	// unsigned short const SHADER_TAGINDEX;
	{
		// __int32 i;
	}
	{
	}
	// function call : bool (*const)(__int32, __int32, __int32, __int32)
	// function call : void *(*const)(unsigned long, long)
	// function call : void (*const)(unsigned __int32, void *, __int32, unsigned __int32, __int32, __int32)
	todo("implement");
	_sub_1096D750(this);
}

_extern __int32 _sub_1096CAA0(s_render_model const *);
__int32 FindMagnetMarkerGroup(s_render_model const *renderModel) // 0x1096CAA0
{
	// `anonymous-namespace'::FindMagnetMarkerGroup
	// s_render_model const *renderModel;
	{
		// __int32 i;
	}
	todo("implement");
	__int32 __result = _sub_1096CAA0(renderModel);
	return __result;
}

_extern void _sub_1096CC00(unsigned __int32, std::vector<real_point3d,std::allocator<real_point3d> > &);
void GetMagnetsFromCollisionModel(unsigned __int32 objectIndex, std::vector<real_point3d,std::allocator<real_point3d> > &markers) // 0x1096CC00
{
	// `anonymous-namespace'::GetMagnetsFromCollisionModel
	// static ...; // 0x1096CDAD
	// static ...; // 0x1096CDA9
	// static ...; // 0x1096CD9C
	// static ...; // 0x1096CD6C
	// static ...; // 0x1096CD64
	// unsigned __int32 objectIndex;
	// std::vector<real_point3d,std::allocator<real_point3d> > &markers;
	{
		// collision_model_instance instance;
		{
			// s_collision_model_bsp_iterator iterator;
			{
				// c_tag_block<collision_vertex> const &vertices;
				// long node_index;
				{
					// __int32 k;
					{
						// real_matrix4x3 world_matrix;
						// real_point3d pos;
					}
				}
			}
		}
	}
	// function call : bool (*const)(collision_model_instance *, long)
	// function call : void (*const)(s_collision_model_bsp_iterator *, model_definition const *, collision_model_definition const *, unsigned char const *)
	// function call : bool (*const)(s_collision_model_bsp_iterator *)
	// function call : real_matrix4x3 *(*const)(long, real_matrix4x3 *)
	todo("implement");
	_sub_1096CC00(objectIndex, markers);
}

_extern void _sub_1096CE30(MagnetManager *const, unsigned __int32, std::vector<real_point3d,std::allocator<real_point3d> > &);
void MagnetManager::GetObjectMarkers(unsigned __int32 objectIndex, std::vector<real_point3d,std::allocator<real_point3d> > &markers) // 0x1096CE30
{
	// `anonymous-namespace'::MagnetManager::GetObjectMarkers
	// std::vector<real_point3d,std::allocator<real_point3d> > &markers;
	// __int32 const markerGroupIndex;
	// s_object_data *object;
	// s_object_definition *objectDef;
	// s_model_definition *model;
	// s_render_model *renderModel;
	{
		// s_render_model_marker_group const *markerGroup;
		{
			// __int32 i;
			{
				// float scale;
				// real_point3d const &pos;
			}
		}
	}
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	// function call : void *(*const)(unsigned long, long)
	todo("implement");
	_sub_1096CE30(this, objectIndex, markers);
}

_extern void _sub_1096C880(MagnetManager *const, unsigned __int32);
void MagnetManager::AddSourceObject(unsigned __int32 objectIndex) // 0x1096C880
{
	// `anonymous-namespace'::MagnetManager::AddSourceObject
	// static ...; // 0x1096CA0C
	// static ...; // 0x1096CA04
	// MagnetManager *const this;
	// unsigned __int32 objectIndex;
	// s_object_data *const object;
	// static std::vector<real_point3d,std::allocator<real_point3d> > `MagnetManager::AddSourceObject'::`2'::markers; // 0x1240FB68
	// real_matrix4x3 objectTransform;
	// static __int32 `MagnetManager::AddSourceObject'::`2'::$TSS0; // 0x1240FB78
	{
		// unsigned __int32 i;
	}
	// function call : real_matrix4x3 *(*const)(long, real_matrix4x3 *)
	todo("implement");
	_sub_1096C880(this, objectIndex);
}

_extern void _sub_1096C650(MagnetManager *const, unsigned __int32);
void MagnetManager::AddDestObject(unsigned __int32 objectIndex) // 0x1096C650
{
	// `anonymous-namespace'::MagnetManager::AddDestObject
	// static ...; // 0x1096C7EC
	// static ...; // 0x1096C7E4
	// MagnetManager *const this;
	// unsigned __int32 objectIndex;
	// s_object_data *object;
	// static std::vector<real_point3d,std::allocator<real_point3d> > `MagnetManager::AddDestObject'::`2'::markers; // 0x1240FB7C
	// real_matrix4x3 objectTransform;
	// static __int32 `MagnetManager::AddDestObject'::`2'::$TSS0; // 0x1240FB8C
	{
		// unsigned __int32 i;
	}
	// function call : real_matrix4x3 *(*const)(long, real_matrix4x3 *)
	todo("implement");
	_sub_1096C650(this, objectIndex);
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_render_model_marker>::try_get_element(__int32, s_render_model_marker **) const;
template s_render_model_marker * c_tag_block<s_render_model_marker>::get_element(__int32) const;
template s_render_model_marker const & c_tag_block<s_render_model_marker>::operator[](__int32) const;
template s_render_model_marker_group const & c_tag_block<s_render_model_marker_group>::operator[](__int32) const;
