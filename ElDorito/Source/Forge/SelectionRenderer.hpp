#ifndef __FORGE_SELECTIONRENDERER_HPP__
#define __FORGE_SELECTIONRENDERER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Forge/Geoemetry.hpp"
#include "Forge/Magnets.hpp"

/* ---------- constants */

namespace Forge
{
	namespace SelectionRenderer
	{
		enum RendererImplementationType
		{
			eRendererSpecialHud = 0,
			eRendererImplicit,
		};
	}
}

/* ---------- definitions */

/* ---------- prototypes */

namespace Forge
{
	namespace SelectionRenderer
	{
		extern void ApplyPatches();
		extern void Update();
		extern void SetEnabled(bool enabled);
		extern void SetRendererType(Forge::SelectionRenderer::RendererImplementationType type);
		extern void Initialize();
		extern void Dispose();
	}
}

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __FORGE_SELECTIONRENDERER_HPP__
