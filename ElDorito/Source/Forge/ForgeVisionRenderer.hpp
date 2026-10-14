#ifndef __FORGE_FORGEVISIONRENDERER_HPP__
#define __FORGE_FORGEVISIONRENDERER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Blam/math/color_definitions.hpp"
#include "Forge/Geoemetry.hpp"
#include "Forge/Magnets.hpp"

/* ---------- forward declarations */

struct real_argb_color;
namespace Forge
{
	class CForgeVisionRenderer;
}

/* ---------- constants */

/* ---------- definitions */

namespace Forge
{
	class CForgeVisionRenderer
	{
	public:
		static void Generate(long windowIndex, long playerIndex, long unitIndex, void const *windowData, bool pass);
		static void GetVisionColors(real_argb_color *colors);
		static void Render(long windowIndex, void *view);
		static long GetMaskBitmap(long *bitmapIndex);
		static _inline bool VisibleThroughWalls();
		static _inline bool IsActive();
		static void SetActive(bool active);
		static void Update();
	private:
		static void OnActivate();
		static bool m_bActive;
		static bool m_visibleThroughWalls;
	};
	static_assert(sizeof(Forge::CForgeVisionRenderer) == 1, "Invalid Forge::CForgeVisionRenderer size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Forge
{
	inline bool CForgeVisionRenderer::VisibleThroughWalls() // 0x108F8CF0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?VisibleThroughWalls@CForgeVisionRenderer@Forge@@SA_NXZ");
		// procedure flags: nofpo

		return m_visibleThroughWalls;
	}

	inline bool CForgeVisionRenderer::IsActive() // 0x108E41E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?IsActive@CForgeVisionRenderer@Forge@@SA_NXZ");
		// procedure flags: nofpo

		return m_bActive;
	}
}

/* ---------- private code */

#endif // __FORGE_FORGEVISIONRENDERER_HPP__
