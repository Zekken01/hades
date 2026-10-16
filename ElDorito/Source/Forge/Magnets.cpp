/* ---------- headers */

#include "Forge/Magnets.hpp"
#include "hades/hades.h"

#include "Modules/ModuleForge.hpp"

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

#include "Utils/Logger.hpp"  // hades: added for 0x1096D1B0
#include "Blam/Cache/StringIdCache.hpp"  // hades: added for 0x1096D1B0

#include "Forge/ForgeUtil.hpp"  // hades: added for 0x1096CE30

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
		void GetObjectMarkers(unsigned __int32, std::vector<real_point3d> &);
		void AddSourceObject(unsigned __int32);
		void AddDestObject(unsigned __int32);
		void PerformPairing();
	};
	static_assert(sizeof(MagnetManager) == 30744, "Invalid MagnetManager size");

}
using namespace hades_file_local;
/* ---------- prototypes */

extern float (*const game_ticks_to_seconds)(float);  // hades: added for 0x1096DE70
extern long (*const game_time_get)();  // hades: added for 0x1096DE70
namespace Forge { namespace Selection { extern Forge::ObjectSet &GetSelection(); } }  // hades: added for 0x1096DE70

extern float distance_squared3d(real_point3d const *p1, real_point3d const *p2);  // hades: added for 0x1096D440

real_point3d *matrix4x3_inverse_transform_point(real_matrix4x3 const *matrix, real_point3d const *point, real_point3d *result);  // hades: added for 0x1096CC00

real_point3d *matrix4x3_transform_point(real_matrix4x3 const *matrix, real_point3d const *point, real_point3d *result);  // hades: added for 0x1096C650

namespace hades_file_local { extern Forge::Magnets::MagnetPair const nullMagnetPair; }  // hades: added for 0x1096CB80

long tag_find_by_name(unsigned long group_tag, char const *name);  // hades: added for 0X1096D120

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
void GetMagnetsFromCollisionModel(unsigned __int32 objectIndex, std::vector<real_point3d> &markers);

/* ---------- globals */

/* ---------- private variables */

namespace hades_file_local
{
	extern char const *MARKER_GROUP_NAME; // 0x11353D3C
	std::unique_ptr<MagnetManager> s_MagnetManager; // 0x1240FB54
	extern unsigned long markerGroupName; // 0x1240FB58
}
using namespace hades_file_local;
/* ---------- public code */

namespace Forge
{
	namespace Magnets
	{
		bool Initialize() // 0x1096D1B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Initialize@Magnets@Forge@@YA_NXZ");

			markerGroupName = Blam::Cache::StringIDCache::GetCurrent()->GetStringId(MARKER_GROUP_NAME);
			if (!s_MagnetManager)
			{
				s_MagnetManager = std::make_unique<MagnetManager>();
				if (!s_MagnetManager)
				{
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Game, Utils::LogLevel::Error, "Failed to initialize magnets. Out of memory");
					return false;
				}
			}
			return true;
		}

		void Shutdown() // 0x1096DE20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Shutdown@Magnets@Forge@@YAXXZ");

			s_MagnetManager.reset(nullptr);
		}

		void Update() // 0x1096E210
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Update@Magnets@Forge@@YAXXZ");

			if (!MagnetsEnabled())
				return;

			if (s_MagnetManager)
				s_MagnetManager->Update();
		}

		void Render() // 0x1096D8C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Render@Magnets@Forge@@YAXXZ");

			if (!MagnetsEnabled() || !MagnetsVisible())
				return;

			if (s_MagnetManager)
				s_MagnetManager->Render();
		}

		Forge::Magnets::MagnetPair const &GetMagnetPair() // 0x1096CB80
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetMagnetPair@Magnets@Forge@@YAABUMagnetPair@12@XZ");

			if (!s_MagnetManager || !MagnetsEnabled())
			{
				return nullMagnetPair;
			}

			return s_MagnetManager->GetMagnetPair();
		}
	}
}

/* ---------- private code */

_inline MagnetManager::MagnetManager() // 0x1096C1A0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "??0MagnetManager@hades_file_local@@QAE@XZ");

	m_LastCheck = 0;
	m_NumSourceMagnets = 0;
	m_NumDestMagnets = 0;
}

namespace Forge
{
	namespace Magnets
	{

	}
}

_inline Forge::Magnets::MagnetPair const &MagnetManager::GetMagnetPair() const // 0x1096CB50
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMagnetPair@MagnetManager@hades_file_local@@QBEABUMagnetPair@Magnets@Forge@@XZ");

	return m_MagnetPairing;
}

bool MagnetsEnabled() // 0x1096D360
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?MagnetsEnabled@@YA_NXZ");

	return Modules::ModuleForge::Instance().VarMagnetsEnabled->ValueInt;
}

bool MagnetsVisible() // 0x1096D3D0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?MagnetsVisible@@YA_NXZ");

	return Modules::ModuleForge::Instance().VarMagnetsVisible->ValueInt;
}

void MagnetManager::Update() // 0x1096DE70
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Update@MagnetManager@hades_file_local@@QAEXXZ");

	unsigned long playerIndex = ((unsigned long (*)(long))0x589C30)(0);
	if (playerIndex == -1)
		return;
	long heldObjectIndex;
	if (!((bool (*)(long, long *, long *))0x59A6F0)(playerIndex, &heldObjectIndex, nullptr) || heldObjectIndex == -1)
	{
		m_NumSourceMagnets = 0;
		m_NumDestMagnets = 0;
		return;
	}
	Forge::ObjectSet const &selection = Forge::Selection::GetSelection();
	m_NumSourceMagnets = 0;
	AddSourceObject(heldObjectIndex);
	if (selection.Contains(heldObjectIndex))
	{
		s_object_data const *heldObject = object_get(heldObjectIndex);
		long objectIndex = heldObject->first_child_object_index;
		while (objectIndex != -1 && m_NumSourceMagnets < 512)
		{
			s_object_data *object = object_get(objectIndex);
			AddSourceObject(objectIndex);
			objectIndex = object->next_object_index;
		}
	}
	if (game_ticks_to_seconds((float)(game_time_get() - m_LastCheck)) > 0.3f)
	{
		m_LastCheck = game_time_get();
		s_object_data const *heldObject = object_get(heldObjectIndex);
		long proximityObjects[256];
		short numProximityObjects = ((short (*)(long, long, s_cluster_reference const *, real_point3d const *, float, long *, short))0xB35B60)(0, 0, (s_cluster_reference const *)&heldObject->location, &heldObject->bounding_sphere_center, heldObject->bounding_sphere_radius, proximityObjects, 256);
		m_NumDestMagnets = 0;
		for (__int32 i = 0; i < numProximityObjects; i++)
		{
			long objectIndex = proximityObjects[i];
			if (objectIndex == heldObjectIndex)
				continue;
			AddDestObject(objectIndex);
		}
		PerformPairing();
	}
}

void MagnetManager::PerformPairing() // 0x1096D440
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?PerformPairing@MagnetManager@hades_file_local@@AAEXXZ");

	m_MagnetPairing.IsValid = false;
	unsigned long playerIndex = reinterpret_cast<unsigned long (*)(long)>(0x589C30)(0);
	s_player_datum *player = players_get()->try_and_get(playerIndex);
	if (!player)
		return;
	real_matrix4x3 unitTransform;
	reinterpret_cast<void (*)(long, real_matrix4x3 *)>(0xB2EC60)(player->unit_index, &unitTransform);
	float shortestDistance = 999.0f;
	float shortestUnitDistance = 999.0f;
	float const minDistance = Utils::Singleton<Modules::ModuleForge>::Instance().VarMagnetsStrength->ValueFloat;
	for (__int32 i = 0; i < m_NumSourceMagnets; i++)
	{
		Forge::Magnets::Magnet const &sourceMagnet = m_SourceMagnets[i];
		float unitDistance = distance_squared3d(&unitTransform.position, &sourceMagnet.Position);
		if (m_MagnetPairing.IsValid && unitDistance > shortestUnitDistance)
			continue;
		for (__int32 j = 0; j < m_NumDestMagnets; j++)
		{
			Forge::Magnets::Magnet const &destMagnet = m_DestMagnets[j];
			float distance2 = distance_squared3d(&sourceMagnet.Position, &destMagnet.Position);
			if (minDistance * minDistance > distance2 && shortestDistance > distance2)
			{
				shortestUnitDistance = unitDistance;
				shortestDistance = distance2;
				m_MagnetPairing.IsValid = true;
				m_MagnetPairing.Source = &m_SourceMagnets[i];
				m_MagnetPairing.Dest = &m_DestMagnets[j];
			}
		}
	}
}

void MagnetManager::RenderMagnet(Forge::Magnets::Magnet const &magnet) // 0x1096D940
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?RenderMagnet@MagnetManager@hades_file_local@@QAEXABUMagnet@Magnets@Forge@@@Z");

	if (m_MagnetPairing.IsValid && (m_MagnetPairing.Dest == &magnet || m_MagnetPairing.Source == &magnet))
	{
		float const color[4] = { 2.0f, 0.0f, 0.0f, 2.0f };
		((void (*)(__int32, __int32, float const *))0xA66410)(20, 1, color);
	}
	else
	{
		float const color[4] = { 0.0f, 0.0f, 2.0f, 2.0f };
		((void (*)(__int32, __int32, float const *))0xA66410)(20, 1, color);
	}
	float const scale = 0.05f;
	real_vector3d forward = { 1.0f, 0.0f, 0.0f };
	real_vector3d left = { 0.0f, 1.0f, 0.0f };
	real_vector3d up = { 0.0f, 0.0f, 1.0f };
	float m[12] =
	{
		forward.i * scale, left.i * scale, up.i * scale, magnet.Position.x,
		forward.j * scale, left.j * scale, up.j * scale, magnet.Position.y,
		forward.k * scale, left.k * scale, up.k * scale, magnet.Position.z,
	};
	((void (*)(__int32, __int32, float const *))0xA66410)(24, 3, m);
	__int32 v14 = ((__int32 (*)())0xA22BA0)();
	((__int32 (*)(__int32))0xA232D0)(1);
	((__int32 (*)(__int32, __int32, void *, __int32))0xA28330)(5, 2, (void *)(Forge::hades_file_local_Forge::Geoemetry::BOX_VERTICES + 0), 20);
	((__int32 (*)(__int32, __int32, void *, __int32))0xA28330)(5, 2, (void *)(Forge::hades_file_local_Forge::Geoemetry::BOX_VERTICES + 4), 20);
	((__int32 (*)(__int32, __int32, void *, __int32))0xA28330)(5, 2, (void *)(Forge::hades_file_local_Forge::Geoemetry::BOX_VERTICES + 8), 20);
	((__int32 (*)(__int32, __int32, void *, __int32))0xA28330)(5, 2, (void *)(Forge::hades_file_local_Forge::Geoemetry::BOX_VERTICES + 12), 20);
	((__int32 (*)(__int32, __int32, void *, __int32))0xA28330)(5, 2, (void *)(Forge::hades_file_local_Forge::Geoemetry::BOX_VERTICES + 16), 20);
	((__int32 (*)(__int32, __int32, void *, __int32))0xA28330)(5, 2, (void *)(Forge::hades_file_local_Forge::Geoemetry::BOX_VERTICES + 20), 20);
	((__int32 (*)(__int32))0xA232D0)(v14);
}

unsigned short GetPlasmaShaderTagIndex() // 0x1096D120
{

	static bool tagLookup = true;
	static long tagIndex = -1;

	if (tagLookup && tagIndex == -1)
	{
		tagIndex = tag_find_by_name(0x726D7368, "objects\\multi\\shaders\\multiplayer_object_plasma");
		if (tagIndex == -1)
			tagLookup = false;
	}

	return tagIndex;
}

void MagnetManager::Render() // 0x1096D750
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?Render@MagnetManager@hades_file_local@@QAEXXZ");

	unsigned short const SHADER_TAGINDEX = GetPlasmaShaderTagIndex();
	if (!((bool (*)(__int32, __int32, __int32, __int32))0xA23300)(64, 0x14, 0, 0))
		return;

	void *shaderDef = tag_get(0x726D2020, SHADER_TAGINDEX);
	((void (*)(unsigned __int32, void *, __int32, unsigned __int32, __int32, __int32))0xA3CA60)(SHADER_TAGINDEX, shaderDef, 20, 0, 5, 1);

	for (__int32 i = 0; i < m_NumDestMagnets; i++)
		RenderMagnet(m_DestMagnets[i]);

	for (__int32 i = 0; i < m_NumSourceMagnets; i++)
		RenderMagnet(m_SourceMagnets[i]);
}

__int32 FindMagnetMarkerGroup(s_render_model const *renderModel) // 0x1096CAA0
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?FindMagnetMarkerGroup@@YAHPBUs_render_model@@@Z");

	if (!markerGroupName)
		return -1;

	for (__int32 i = 0; i < renderModel->marker_groups.count; i++)
	{
		if (renderModel->marker_groups[i].name == markerGroupName)
			return i;
	}

	return -1;
}

void GetMagnetsFromCollisionModel(unsigned __int32 objectIndex, std::vector<real_point3d> &markers) // 0x1096CC00
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetMagnetsFromCollisionModel@@YAXIAAV?$vector@Ureal_point3d@@V?$allocator@Ureal_point3d@@@std@@@std@@@Z");

	collision_model_instance instance;
	if (((bool (*)(collision_model_instance *, long))0x980E40)(&instance, objectIndex))
	{
		s_collision_model_bsp_iterator iterator;
		((void (*)(s_collision_model_bsp_iterator *, model_definition const *, collision_model_definition const *, unsigned char const *))0x980AF0)(&iterator, instance.model, instance.collision_model, instance.permutations);
		while (((bool (*)(s_collision_model_bsp_iterator *))0x980BC0)(&iterator))
		{
			long node_index = iterator.m_bsp3d_reference & 0xFF;
			c_tag_block<collision_vertex> const &vertices = iterator.m_bsp.bsp->vertices;
			for (__int32 k = 0; k < vertices.count; k++)
			{
				real_point3d pos;
				matrix4x3_transform_point(&instance.nodes[node_index], &vertices[k].position, &pos);
				real_matrix4x3 world_matrix;
				((real_matrix4x3 *(*)(long, real_matrix4x3 *))0xB2EC60)(objectIndex, &world_matrix);
				matrix4x3_inverse_transform_point(&world_matrix, &pos, &pos);
				markers.emplace_back(pos.x, pos.y, pos.z);
			}
		}
	}
}

void MagnetManager::GetObjectMarkers(unsigned __int32 objectIndex, std::vector<real_point3d> &markers) // 0x1096CE30
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?GetObjectMarkers@MagnetManager@hades_file_local@@AAEXIAAV?$vector@Ureal_point3d@@V?$allocator@Ureal_point3d@@@std@@@std@@@Z");

	s_object_data *object = object_get(objectIndex);
	s_object_definition *objectDef = (s_object_definition *)tag_get('obje', object->definition_index);
	if (!objectDef)
		return;
	if (objectDef->model.index == -1)
		return;
	s_model_definition *model = (s_model_definition *)tag_get('hlmt', objectDef->model.index);
	if (!model)
		return;
	if (model->render_model.index == -1)
		return;
	s_render_model *renderModel = (s_render_model *)tag_get('mode', model->render_model.index);
	if (!renderModel)
		return;
	if (Utils::Singleton<Modules::ModuleForge>::Instance().VarMagnetAutogen->ValueInt > 0)
	{
		GetMagnetsFromCollisionModel(objectIndex, markers);
		return;
	}
	__int32 const markerGroupIndex = FindMagnetMarkerGroup(renderModel);
	if (markerGroupIndex != -1)
	{
		s_render_model_marker_group const *markerGroup = &renderModel->marker_groups[markerGroupIndex];
		for (__int32 i = 0; i < markerGroup->markers.count; i++)
		{
			real_point3d const &pos = markerGroup->markers[i].position;
			float scale = object->scale;
			if (scale == 0.0f)
				scale = 1.0f;
			markers.emplace_back(pos.x * scale, pos.y * scale, pos.z * scale);
		}
		return;
	}
	else if (Forge::ObjectIsForgeScenery(objectIndex))
	{
		GetMagnetsFromCollisionModel(objectIndex, markers);
	}
}

void MagnetManager::AddSourceObject(unsigned __int32 objectIndex) // 0x1096C880
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?AddSourceObject@MagnetManager@hades_file_local@@AAEXI@Z");

	s_object_data *const object = object_get(objectIndex);
	if (!object)
		return;
	real_matrix4x3 objectTransform;
	((real_matrix4x3 *(*)(long, real_matrix4x3 *))0xB2EC60)(objectIndex, &objectTransform);
	static std::vector<real_point3d> markers;
	markers.clear();
	GetObjectMarkers(objectIndex, markers);
	for (unsigned __int32 i = 0; i < markers.size(); i++)
	{
		if (m_NumSourceMagnets >= 512)
			break;
		matrix4x3_transform_point(&objectTransform, &markers[i], &m_SourceMagnets[m_NumSourceMagnets].Position);
		m_NumSourceMagnets++;
	}
}

void MagnetManager::AddDestObject(unsigned __int32 objectIndex) // 0x1096C650
{
	mangled_x86(MANGLED_KNOWN_GOOD, "?AddDestObject@MagnetManager@hades_file_local@@AAEXI@Z");

	s_object_data *object = object_get(objectIndex);
	if (!object || object->map_variant_index == -1)
		return;
	real_matrix4x3 objectTransform;
	((real_matrix4x3 *(*)(long, real_matrix4x3 *))0xB2EC60)(objectIndex, &objectTransform);
	static std::vector<real_point3d> markers;
	markers.clear();
	GetObjectMarkers(objectIndex, markers);
	for (unsigned __int32 i = 0; i < markers.size(); i++)
	{
		if (m_NumDestMagnets >= 2048)
			break;
		matrix4x3_transform_point(&objectTransform, &markers[i], &m_DestMagnets[m_NumDestMagnets].Position);
		m_NumDestMagnets++;
	}
}

/* ---------- template instantiations */

// Emitted so that the members the original object carried are in ours too.
// Nothing calls them; an explicit instantiation is how a template member
// reaches an object without being used. Generated - see build_instantiations.py.

template bool c_tag_block<s_render_model_marker>::try_get_element(__int32, s_render_model_marker **) const;
template s_render_model_marker * c_tag_block<s_render_model_marker>::get_element(__int32) const;
template s_render_model_marker const & c_tag_block<s_render_model_marker>::operator[](__int32) const;
template s_render_model_marker_group const & c_tag_block<s_render_model_marker_group>::operator[](__int32) const;

/* ---------- data definitions */

// Initial values as linked into mtndew.dll. Defined after every use, so calls
// through the constant pointers still load them from memory, as the original's did.
namespace hades_file_local { Forge::Magnets::MagnetPair const nullMagnetPair = {}; }
namespace hades_file_local { char const *MARKER_GROUP_NAME = "sandbox_magnet"; }
namespace hades_file_local { unsigned long markerGroupName; }
