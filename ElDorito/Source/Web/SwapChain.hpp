#ifndef __WEB_SWAPCHAIN_HPP__
#define __WEB_SWAPCHAIN_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "CommandMap.hpp"
#include "CommandScript.hpp"
#include "mods/mod_package_updater.hpp"
#include "Player/PlayerEmblemGenerator.hpp"

#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <queue>
#include <stack>

/* ---------- forward declarations */

namespace Web
{
	namespace Browser
	{
		class SwapChain;
	}
}

/* ---------- constants */

/* ---------- definitions */

#pragma pack(push, 4)
namespace Web
{
	namespace Browser
	{
		class SwapChain
		{
		public:
			public:
			struct Buffer
			{
				unsigned __int32 version = 0; // 0x0
				IDirect3DTexture9 *texture = nullptr; // 0x4
				void *handle = nullptr; // 0x8
				Buffer(Buffer const &);
				_inline Buffer() = default;  // hades: implicit - new Buffer() zero-fills before calling it
				Buffer &operator=(Buffer const &);
				_inline ~Buffer();
			};
			static_assert(sizeof(Buffer) == 12, "Invalid Buffer size");
			struct BufferHolder
			{
				_inline BufferHolder();
				_inline BufferHolder(Web::Browser::SwapChain *owner, Buffer *buffer);
				bool IsValid() const;
				~BufferHolder();
				Buffer *operator->();
				Buffer *Remove();
			private:
				Web::Browser::SwapChain *m_owner; // 0x0
				Buffer *m_buffer; // 0x4
			};
			static_assert(sizeof(BufferHolder) == 8, "Invalid BufferHolder size");
			public:
			SwapChain(Web::Browser::SwapChain const &);
			SwapChain(IDirect3DDevice9 *device, __int32 bufferCount);
			Web::Browser::SwapChain &operator=(Web::Browser::SwapChain const &);
			~SwapChain();
			Buffer *Flip();
			BufferHolder AcquireBuffer();
			void ReturnBuffer(Buffer *buffer);
			void PushBuffer(Buffer *buffer);
			bool BufferIsValid(Buffer const *buffer) const;
			void ResizeBuffers(__int32 width, __int32 height);
			void Release();
		private:
			void ReturnBufferLocked(Buffer *buffer);
			void DeleteBuffers();
			IDirect3DDevice9 *m_device; // 0x0
			__int32 m_bufferCount; // 0x4
			unsigned __int32 m_bufferVersion; // 0x8
			std::mutex m_mutex; // 0xC
			std::condition_variable m_emptyCond; // 0x3C
			std::queue<Buffer *> m_queue; // 0x64
			std::stack<Buffer *> m_pool; // 0x78
			Buffer *m_frontBuffer; // 0x8C
			bool m_released; // 0x90
		};
	}
}

#pragma pack(pop)
static_assert(sizeof(Web::Browser::SwapChain) == 148, "Invalid Web::Browser::SwapChain size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		// SwapChain::Buffer::Buffer() (0x10C77670) is the implicit constructor:
		// the members carry default initializers in the class.
		//
		//
		//
		//
		//
		//
		//

		_inline SwapChain::Buffer::~Buffer() // 0x10C77A40
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1Buffer@SwapChain@Browser@Web@@QAE@XZ");

			texture->Release();
			handle = nullptr;
		}

		_inline SwapChain::BufferHolder::BufferHolder(Web::Browser::SwapChain *owner, Web::Browser::SwapChain::Buffer *buffer) // 0x10C776C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0BufferHolder@SwapChain@Browser@Web@@QAE@PAV123@PAUBuffer@123@@Z");

			m_owner = owner;
			m_buffer = (Buffer *)buffer;
		}

		_inline SwapChain::BufferHolder::BufferHolder() // 0x10C77700
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0BufferHolder@SwapChain@Browser@Web@@QAE@XZ");

			m_owner = nullptr;
			m_buffer = nullptr;
		}
	}
}

/* ---------- private code */

#endif // __WEB_SWAPCHAIN_HPP__
