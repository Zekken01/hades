/* ---------- headers */

#include "Web/SwapChain.hpp"
#include "hades/hades.h"

#include "ChatCommands/ChatCommandMap.hpp"
#include "Player/PlayerEmblemGenerator.hpp"
#include "Utils/Singleton.hpp"

#include "Utils/Logger.hpp"  // hades: added for 0x10C78610

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
		SwapChain::SwapChain(IDirect3DDevice9 *device, __int32 bufferCount) : m_device(device), m_bufferCount(bufferCount), m_bufferVersion(0), m_frontBuffer(nullptr), m_released(false) /* hades-mem-init:  */ // 0x10C77740
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0SwapChain@Browser@Web@@QAE@PAUIDirect3DDevice9@@H@Z");
		}

		SwapChain::~SwapChain() // 0x10C77AF0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??1SwapChain@Browser@Web@@QAE@XZ");

			DeleteBuffers();
		}

		Web::Browser::SwapChain::Buffer *SwapChain::Flip() // 0x10C78200
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Flip@SwapChain@Browser@Web@@QAEPAUBuffer@123@XZ");

			std::scoped_lock<std::mutex> lock(m_mutex);
			if (m_released)
				return nullptr;
			if (m_queue.size())
			{
				Buffer *buff = m_queue.front();
				m_queue.pop();
				if (m_frontBuffer)
					ReturnBufferLocked(m_frontBuffer);
				m_frontBuffer = buff;
			}
			return m_frontBuffer;
		}

		Web::Browser::SwapChain::BufferHolder SwapChain::AcquireBuffer() // 0x10C77E40
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?AcquireBuffer@SwapChain@Browser@Web@@QAE?AUBufferHolder@123@XZ");

			std::unique_lock<std::mutex> lock(m_mutex);
			m_emptyCond.wait(lock, [this] { return m_released || !m_pool.empty(); });
			if (m_released)
				return BufferHolder();

			Buffer *buffer = m_pool.top();
			m_pool.pop();
			return BufferHolder(this, buffer);
		}

		void SwapChain::ReturnBuffer(Web::Browser::SwapChain::Buffer *buffer) // 0x10C788C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ReturnBuffer@SwapChain@Browser@Web@@QAEXPAUBuffer@123@@Z");

			std::scoped_lock<std::mutex> lock(m_mutex);

			ReturnBufferLocked(buffer);
		}

		void SwapChain::PushBuffer(Web::Browser::SwapChain::Buffer *buffer) // 0x10C783A0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?PushBuffer@SwapChain@Browser@Web@@QAEXPAUBuffer@123@@Z");

			std::scoped_lock<std::mutex> lock(m_mutex);
			if (!BufferIsValid(buffer))
			{
				delete buffer;
				return;
			}
			m_queue.push(buffer);
		}

		bool SwapChain::BufferIsValid(Web::Browser::SwapChain::Buffer const *buffer) const // 0x10C78000
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?BufferIsValid@SwapChain@Browser@Web@@QBE_NPBUBuffer@123@@Z");

			return !m_released && buffer->version == m_bufferVersion;
		}

		void SwapChain::ResizeBuffers(__int32 width, __int32 height) // 0x10C78610
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ResizeBuffers@SwapChain@Browser@Web@@QAEXHH@Z");

			std::scoped_lock<std::mutex> lock(m_mutex);
			m_bufferVersion++;
			DeleteBuffers();
			for (__int32 i = 0; i < m_bufferCount; i++)
			{
				Buffer *buffer = new Buffer();
				buffer->version = m_bufferVersion;
				HRESULT hr = m_device->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &buffer->texture, &buffer->handle);
				if (FAILED(hr))
				{
					Utils::Singleton<Utils::Logger>::Instance().Log(Utils::LogTypes::Graphics, Utils::LogLevel::Info, "Web::Browser::SwapChain::ResizeBuffers:89 - SwapChain Failed to create buffer #%d. Width: %d, Height: %d, Error: %x", i, width, height, hr);
					break;
				}
				m_pool.push(buffer);
			}
			m_emptyCond.notify_one();
		}

		void SwapChain::ReturnBufferLocked(Web::Browser::SwapChain::Buffer *buffer) // 0x10C789B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?ReturnBufferLocked@SwapChain@Browser@Web@@AAEXPAUBuffer@123@@Z");

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

		void SwapChain::DeleteBuffers() // 0x10C78070
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?DeleteBuffers@SwapChain@Browser@Web@@AAEXXZ");

			while (!m_pool.empty())
			{
				delete m_pool.top();
				m_pool.pop();
			}
			while (!m_queue.empty())
			{
				delete m_queue.front();
				m_queue.pop();
			}
			if (m_frontBuffer)
			{
				delete m_frontBuffer;
				m_frontBuffer = nullptr;
			}
		}

		void SwapChain::Release() // 0x10C78510
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Release@SwapChain@Browser@Web@@QAEXXZ");

			{
				std::scoped_lock<std::mutex> lock(m_mutex);

				m_released = true;
				DeleteBuffers();
			}

			m_emptyCond.notify_one();
		}
	}
}

/* ---------- private code */
