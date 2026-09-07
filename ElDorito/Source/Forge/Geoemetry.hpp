#ifndef __FORGE_GEOEMETRY_HPP__
#define __FORGE_GEOEMETRY_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

/* ---------- forward declarations */

namespace Forge
{
	namespace hades_file_local_Forge
	{
		struct VertexPosUV;
	}
	using namespace hades_file_local_Forge;
}

/* ---------- constants */

/* ---------- definitions */

namespace Forge
{
	namespace hades_file_local_Forge
	{
		namespace Geoemetry
		{
			struct VertexPosUV
			{
				float X; // 0x0
				float Y; // 0x4
				float Z; // 0x8
				float U; // 0xC
				float V; // 0x10
			};
			static_assert(sizeof(Forge::Geoemetry::VertexPosUV) == 20, "Invalid Forge::Geoemetry::VertexPosUV size");
		}
	}
	using namespace hades_file_local_Forge;
}
/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __FORGE_GEOEMETRY_HPP__
