#ifndef __WEB_WEBFILEREADHANDLER_HPP__
#define __WEB_WEBFILEREADHANDLER_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"

#include <fstream>
#include <memory>
#include <string>

/* ---------- forward declarations */

namespace Web
{
	namespace Browser
	{
		class CWebFileReadHandler;
	}
}

/* ---------- constants */

/* ---------- definitions */

namespace Web
{
	namespace Browser
	{
		class CWebFileReadHandler :
			public CefStreamReader,
			public virtual CefBaseRefCounted
		{
		public:
			CWebFileReadHandler(std::string const &filepath, long long offset, long long length);
			virtual ~CWebFileReadHandler();
			virtual unsigned __int32 Read(void *ptr, unsigned __int32 size, unsigned __int32 n);
			virtual __int32 Seek(long long offset, __int32 whence);
			virtual long long Tell();
			virtual __int32 Eof();
			virtual bool MayBlock();
		private:
			std::ifstream m_stream; // 0x8
			long long m_baseOffset; // 0xC0
			long long m_length; // 0xC8
			long long m_position; // 0xD0
			CefRefCount ref_count_; // 0xD8
		public:
			virtual _inline void AddRef() const;
			virtual _inline bool Release() const;
			virtual _inline bool HasOneRef() const;
			virtual _inline bool HasAtLeastOneRef() const;
		};
		static_assert(sizeof(Web::Browser::CWebFileReadHandler) == 232, "Invalid Web::Browser::CWebFileReadHandler size");
	}
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		inline void CWebFileReadHandler::AddRef() const // 0x10CB7970
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?AddRef@CWebFileReadHandler@Browser@Web@@UBEXXZ");

			ref_count_.AddRef();
		}

		inline bool CWebFileReadHandler::HasAtLeastOneRef() const // 0x10CB7AB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HasAtLeastOneRef@CWebFileReadHandler@Browser@Web@@UBE_NXZ");

			return ref_count_.HasAtLeastOneRef();
		}

		inline bool CWebFileReadHandler::HasOneRef() const // 0x10CB7B10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?HasOneRef@CWebFileReadHandler@Browser@Web@@UBE_NXZ");

			return ref_count_.HasOneRef();
		}

		inline bool CWebFileReadHandler::Release() const // 0x10CB7C90
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Release@CWebFileReadHandler@Browser@Web@@UBE_NXZ");

			if (ref_count_.Release())
			{
				delete static_cast<CWebFileReadHandler const *>(this);
				return true;
			}

			return false;
		}
	}
}

/* ---------- private code */

#endif // __WEB_WEBFILEREADHANDLER_HPP__
