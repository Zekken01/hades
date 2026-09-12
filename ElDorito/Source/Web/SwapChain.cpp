/* ---------- headers */

#include "Web/SwapChain.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Player/PlayerEmblemGenerator.hpp"
#include "Utils/Singleton.hpp"

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
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <cstdlib>
#include <deque>
#include <exception>
#include <functional>
#include <limits>
#include <mutex>
#include <queue>
#include <ratio>
#include <stack>
#include <stdexcept>
#include <stop_token>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <utility>

/* ---------- forward declarations */

struct lambda_1;
namespace Web
{
	namespace Browser
	{
		class SwapChain;
	}
}

namespace Utils {}
using namespace ::Utils;
namespace Web {}
using namespace ::Web;
namespace Web
{
	namespace Browser {}
	using namespace Web::Browser;
}

/* ---------- constants */

/* ---------- definitions */

//class Web::Browser::SwapChain::AcquireBuffer::__l2::<lambda_1>
//{
//public:
//	bool operator()() const;
//	<lambda_1>(Web::Browser::SwapChain::AcquireBuffer::__l2::<lambda_1> &);
//	<lambda_1>(Web::Browser::SwapChain *);
//private:
//	Web::Browser::SwapChain *__this; // 0x0
//public:
//	Web::Browser::SwapChain::AcquireBuffer::__l2::<lambda_1> &operator=(Web::Browser::SwapChain::AcquireBuffer::__l2::<lambda_1> const &);
//};
//static_assert(sizeof(Web::Browser::SwapChain::AcquireBuffer::__l2::<lambda_1>) == 4, "Invalid Web::Browser::SwapChain::AcquireBuffer::__l2::<lambda_1> size");

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Web
{
	namespace Browser
	{
		extern SwapChain* _sub_10C77740(Web::Browser::SwapChain *const, IDirect3DDevice9 *, __int32);
		SwapChain::SwapChain(IDirect3DDevice9 *device, __int32 bufferCount) // 0x10C77740
		{
			mangled_x86(MANGLED_TODO, "??0SwapChain@Browser@Web@@QAE@PAUIDirect3DDevice9@@H@Z");
			// __int32 bufferCount;
			todo("implement");
			_sub_10C77740(this, device, bufferCount);
		}

		SwapChain::~SwapChain() // 0x10C77AF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1SwapChain@Browser@Web@@QAE@XZ");
			// Web::Browser::SwapChain *const this;

			DeleteBuffers();
		}

		extern SwapChain::Buffer *_sub_10C78200(Web::Browser::SwapChain *const);
		Web::Browser::SwapChain::Buffer *SwapChain::Flip() // 0x10C78200
		{
			mangled_x86(MANGLED_TODO, "?Flip@SwapChain@Browser@Web@@QAEPAUBuffer@123@XZ");
			// static ...; // 0x10C78340
			// static ...; // 0x10C78334
			// static ...; // 0x10C7832C
			// Web::Browser::SwapChain *const this;
			// std::scoped_lock<std::mutex> lock;
			{
				// Web::Browser::SwapChain::Buffer *buff;
			}
			todo("implement");
			Web::Browser::SwapChain::Buffer * __result = _sub_10C78200(this);
			return __result;
		}

		extern SwapChain::BufferHolder _sub_10C77E40(Web::Browser::SwapChain *const);
		Web::Browser::SwapChain::BufferHolder SwapChain::AcquireBuffer() // 0x10C77E40
		{
			mangled_x86(MANGLED_TODO, "?AcquireBuffer@SwapChain@Browser@Web@@QAE?AUBufferHolder@123@XZ");
			// static ...; // 0x10C77F98
			// static ...; // 0x10C77F8C
			// static ...; // 0x10C77F84
			// Web::Browser::SwapChain *const this;
			// std::unique_lock<std::mutex> lock;
			// Web::Browser::SwapChain::Buffer *buffer;
			todo("implement");
			Web::Browser::SwapChain::BufferHolder __result = _sub_10C77E40(this);
			return __result;
		}

		void SwapChain::ReturnBuffer(Web::Browser::SwapChain::Buffer *buffer) // 0x10C788C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ReturnBuffer@SwapChain@Browser@Web@@QAEXPAUBuffer@123@@Z");
			// static ...; // 0x10C7896C
			// static ...; // 0x10C78964
			// Web::Browser::SwapChain *const this;
			// Web::Browser::SwapChain::Buffer *buffer;
			// std::scoped_lock<std::mutex> lock;

			std::scoped_lock<std::mutex> lock(m_mutex);

			ReturnBufferLocked(buffer);
		}

		_extern void _sub_10C783A0(Web::Browser::SwapChain *const, Web::Browser::SwapChain::Buffer *);
		void SwapChain::PushBuffer(Web::Browser::SwapChain::Buffer *buffer) // 0x10C783A0
		{
			mangled_x86(MANGLED_TODO, "?PushBuffer@SwapChain@Browser@Web@@QAEXPAUBuffer@123@@Z");
			// static ...; // 0x10C784B0
			// static ...; // 0x10C784A8
			// Web::Browser::SwapChain *const this;
			// Web::Browser::SwapChain::Buffer *buffer;
			// std::scoped_lock<std::mutex> lock;
			todo("implement");
			_sub_10C783A0(this, buffer);
		}

		bool SwapChain::BufferIsValid(Web::Browser::SwapChain::Buffer const *buffer) const // 0x10C78000
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?BufferIsValid@SwapChain@Browser@Web@@QBE_NPBUBuffer@123@@Z");
			// Web::Browser::SwapChain::Buffer const *buffer;

			return !m_released && buffer->version == m_bufferVersion;
		}

		_extern void _sub_10C78610(Web::Browser::SwapChain *const, __int32, __int32);
		void SwapChain::ResizeBuffers(__int32 width, __int32 height) // 0x10C78610
		{
			mangled_x86(MANGLED_TODO, "?ResizeBuffers@SwapChain@Browser@Web@@QAEXHH@Z");
			// static ...; // 0x10C78808
			// static ...; // 0x10C78800
			// Web::Browser::SwapChain *const this;
			// __int32 width;
			// __int32 height;
			// std::scoped_lock<std::mutex> lock;
			{
				// __int32 i;
				{
					// Web::Browser::SwapChain::Buffer *buffer;
					// HRESULT hr;
				}
			}
			// function call : HRESULT (unsigned __int32, unsigned __int32, unsigned __int32, unsigned long, _D3DFORMAT, _D3DPOOL, IDirect3DTexture9 **, void **)
			todo("implement");
			_sub_10C78610(this, width, height);
		}

		void SwapChain::ReturnBufferLocked(Web::Browser::SwapChain::Buffer *buffer) // 0x10C789B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ReturnBufferLocked@SwapChain@Browser@Web@@AAEXPAUBuffer@123@@Z");
			// Web::Browser::SwapChain::Buffer *buffer;

			if (buffer->version != m_bufferVersion)
			{
				delete buffer;
			}
			else
			{
				m_pool.push(buffer);
			}

			m_emptyCond.notify_one();
		}

		_extern void _sub_10C78070(Web::Browser::SwapChain *const);
		void SwapChain::DeleteBuffers() // 0x10C78070
		{
			mangled_x86(MANGLED_TODO, "?DeleteBuffers@SwapChain@Browser@Web@@AAEXXZ");
			// Web::Browser::SwapChain *const this;
			todo("implement");
			_sub_10C78070(this);
		}

		_extern void _sub_10C78510(Web::Browser::SwapChain *const);
		void SwapChain::Release() // 0x10C78510
		{
			mangled_x86(MANGLED_TODO, "?Release@SwapChain@Browser@Web@@QAEXXZ");
			// static ...; // 0x10C785D8
			// static ...; // 0x10C785CC
			// static ...; // 0x10C785C4
			// Web::Browser::SwapChain *const this;
			{
				// std::scoped_lock<std::mutex> lock;
			}
			todo("implement");
			_sub_10C78510(this);
		}
	}
}

/* ---------- private code */
