#ifndef __WEB_WEBRENDERHANDLERNULL_HPP__
#define __WEB_WEBRENDERHANDLERNULL_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "Web/WebRenderHandlerOsr.hpp"

/* ---------- forward declarations */

namespace Web
{
	namespace Browser
	{
		class RenderHandlerOsr;
		class WebRendererRenderNull;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Web
{
	namespace Browser
	{
		class WebRendererRenderNull :
			public Web::Browser::RenderHandlerOsr,
			public virtual CefBaseRefCounted
		{
		public:
			virtual void AddRef() const;
			virtual bool Release() const;
			virtual bool HasOneRef() const;
			virtual bool HasAtLeastOneRef() const;
		private:
			CefRefCount ref_count_; // 0x8
		public:
			WebRendererRenderNull(); /* compiler_generated() */
			virtual ~WebRendererRenderNull() = default; /* compiler_generated() */
		};
	}
}

// static_assert(sizeof(Web::Browser::WebRendererRenderNull) == 16, "Invalid Web::Browser::WebRendererRenderNull size");
// Withheld: the compiler lays this type out through a base a
// real header declares, and that layout contradicts the size
// the PDB recorded. Derives from CefRenderHandler (CEF 101).

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

/* ---------- private code */

#endif // __WEB_WEBRENDERHANDLERNULL_HPP__
