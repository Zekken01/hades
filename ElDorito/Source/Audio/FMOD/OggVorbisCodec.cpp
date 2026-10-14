/* ---------- headers */

#include "hades/hades.h"

#include "Blam/fmod/fmod_functions.inl"
#include "ChatCommands/ChatCommandMap.hpp"

#include <vorbis/vorbisfile.h>

#include <Windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <wchar.h>
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <limits>
#include <tuple>
#include <type_traits>
#include <utility>

/* ---------- forward declarations */

struct FMOD_CODEC_STATE;
namespace Audio
{
	namespace FMOD
	{
		class CMemoryReadStream;
		class COggVorbisDecoder;
		struct IReadStream;
	}
}

namespace Audio {}
using namespace ::Audio;

/* ---------- constants */

/* ---------- definitions */

// Audio::FMOD::IReadStream is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// Audio::FMOD::CMemoryReadStream is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

// Audio::FMOD::COggVorbisDecoder is defined in hades/recovered_types.h, which the synthesised
// templates in hades/recovered_templates.h inherit from.

/* ---------- prototypes */

namespace Audio
{
	namespace FMOD
	{
		extern FMOD_RESULT __stdcall CodecOpenCallback(FMOD_CODEC_STATE *codec_state, unsigned __int32 usermode, FMOD_CREATESOUNDEXINFO *userexinfo);
		extern FMOD_RESULT __stdcall CodecCloseCallback(FMOD_CODEC_STATE *codec_state);
		extern FMOD_RESULT __stdcall CodecReadCallback(FMOD_CODEC_STATE *codec_state, void *buffer, unsigned __int32 sizebytes, unsigned __int32 *bytesread);
		extern FMOD_RESULT __stdcall CodecSetPositionCallback(FMOD_CODEC_STATE *codec_state, __int32 subsound, unsigned __int32 position, unsigned __int32 postype);
		extern FMOD_RESULT __stdcall StreamOpenCallback(char const *name, __int32 unicode, unsigned __int32 *fileSize, void **handle, void **userData);
		extern FMOD_RESULT __stdcall StreamCloseCallback(void *handle, void *userData);
		extern FMOD_RESULT __stdcall StreamReadCallback(void *handle, void *buffer, unsigned __int32 sizebytes, unsigned __int32 *bytesread, void *userData);
		extern FMOD_RESULT __stdcall StreamSeekCallback(void *handle, unsigned __int32 pos, void *userData);
		extern void RegisterOggVorbisCodec(FMOD_SYSTEM *system, __int32 priority);
		extern FMOD_RESULT CreateOggVorbisStream(FMOD_SYSTEM *system, void *data, unsigned __int32 length, unsigned __int32 mode, FMOD_SOUND **sound);
	}
}

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Audio
{
	namespace FMOD
	{


		_inline CMemoryReadStream::CMemoryReadStream(void *buffer, __int32 length) // 0x106CAEB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "??0CMemoryReadStream@FMOD@Audio@@QAE@PAXH@Z");
			// __int32 length;

			m_buffer = (char *)buffer;
			m_length = length;
			m_position = 0;
		}

		// mangled_x86(MANGLED_DEFAULT, "??0IReadStream@FMOD@Audio@@QAE@XZ"); no body to assert in
		_inline IReadStream::IReadStream() = default; // 0x106CAF30

		// mangled_x86(MANGLED_DEFAULT, "??1CMemoryReadStream@FMOD@Audio@@UAE@XZ"); no body to assert in
		_inline CMemoryReadStream::~CMemoryReadStream() = default; // 0x106CAF60

		_inline __int32 CMemoryReadStream::Read(void *buffer, __int32 bytes) // 0x106CB890
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Read@CMemoryReadStream@FMOD@Audio@@UAEHPAXH@Z");
			// __int32 bytes;
			// __int32 n;

			__int32 n = std::min(m_length - m_position, bytes);
			memcpy(buffer, m_buffer + m_position, n);
			m_position += n;
			return n;
		}

		_inline void CMemoryReadStream::Seek(long long offset, __int32 type) // 0x106CBB80
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Seek@CMemoryReadStream@FMOD@Audio@@UAEX_JH@Z");
			// __int32 type;

			switch (type)
			{
			case 0:
				m_position = offset;
				break;
			case 1:
				m_position += offset;
				break;
			case 2:
				m_position = m_length + offset;
				break;
			}
		}

		_inline long long CMemoryReadStream::GetPosition() const // 0x106CB4B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetPosition@CMemoryReadStream@FMOD@Audio@@UBE_JXZ");
			// Audio::FMOD::CMemoryReadStream const *const this;

			return m_position;
		}

		_inline long long CMemoryReadStream::GetLength() const // 0x106CB480
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?GetLength@CMemoryReadStream@FMOD@Audio@@UBE_JXZ");
			// Audio::FMOD::CMemoryReadStream const *const this;

			return m_length;
		}

		_inline bool COggVorbisDecoder::Init(Audio::FMOD::IReadStream *stream) // 0x106CB4E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Init@COggVorbisDecoder@FMOD@Audio@@QAE_NPAUIReadStream@23@@Z");
			// static ...; // 0x106CB664
			// static ...; // 0x106CB65C
			// Audio::FMOD::COggVorbisDecoder *const this;
			// Audio::FMOD::IReadStream *stream;
			// __int32 ret;
			// vorbis_info *vi;
			// ov_callbacks callbacks;
			// function call : long long () const

			m_stream = stream;
			memset(&m_waveformat, 0, sizeof(m_waveformat));
			memset(m_vf, 0, sizeof(m_vf));
			ov_callbacks callbacks = { OggVorbisReadCallback, OggVorbisSeekCallback, OggVorbisCloseCallback, OggVorbisTellCallback };
			__int32 ret = ov_open_callbacks(this, (OggVorbis_File *)m_vf, NULL, 0, callbacks);
			if (ret != 0)
				return false;
			vorbis_info *vi = ov_info((OggVorbis_File *)m_vf, -1);
			if (!vi)
				return false;
			m_waveformat.format = FMOD_SOUND_FORMAT_PCM16;
			m_waveformat.channels = vi->channels;
			m_waveformat.blockalign = vi->channels * 2;
			m_waveformat.frequency = vi->rate;
			m_waveformat.lengthbytes = (unsigned __int32)((Audio::FMOD::IReadStream *)m_stream)->GetLength();
			m_waveformat.lengthpcm = (unsigned __int32)ov_pcm_total((OggVorbis_File *)m_vf, -1);
			return true;
		}

		_inline void COggVorbisDecoder::Release() // 0x106CBAB0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Release@COggVorbisDecoder@FMOD@Audio@@QAEXXZ");
			// Audio::FMOD::COggVorbisDecoder *const this;
			// function call : void *(unsigned __int32)

			ov_clear((OggVorbis_File *)m_vf);
			delete (Audio::FMOD::IReadStream *)m_stream;
			m_stream = nullptr;
		}

		_inline bool COggVorbisDecoder::SetPosition(long long pcm) // 0x106CBC10
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?SetPosition@COggVorbisDecoder@FMOD@Audio@@QAE_N_J@Z");
			// long long pcm;

			return ov_pcm_seek((OggVorbis_File *)m_vf, pcm) == 0;
		}

		_inline __int32 COggVorbisDecoder::Read(char *buffer, __int32 sizebytes) // 0x106CB950
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?Read@COggVorbisDecoder@FMOD@Audio@@QAEHPADH@Z");
			// __int32 sizebytes;

			return ov_read((OggVorbis_File *)m_vf, buffer, sizebytes, 0, 2, 1, NULL);
		}

		_inline unsigned __int32 COggVorbisDecoder::OggVorbisReadCallback(void *ptr, unsigned __int32 size, unsigned __int32 nmemb, void *datasource) // 0x106CB700
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OggVorbisReadCallback@COggVorbisDecoder@FMOD@Audio@@CAIPAXII0@Z");
			// void *datasource;
			// Audio::FMOD::COggVorbisDecoder *instance;
			// function call : __int32 (void *, __int32)

			COggVorbisDecoder *instance = (COggVorbisDecoder *)datasource;
			return ((Audio::FMOD::IReadStream *)instance->m_stream)->Read(ptr, size * nmemb);
		}

		_inline __int32 COggVorbisDecoder::OggVorbisSeekCallback(void *datasource, long long offset, __int32 whence) // 0x106CB790
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OggVorbisSeekCallback@COggVorbisDecoder@FMOD@Audio@@CAHPAX_JH@Z");
			// __int32 whence;
			// Audio::FMOD::COggVorbisDecoder *instance;
			// function call : void (long long, __int32)

			COggVorbisDecoder *instance = (COggVorbisDecoder *)datasource;
			((Audio::FMOD::IReadStream *)instance->m_stream)->Seek(offset, whence);
			return 0;
		}

		_inline __int32 COggVorbisDecoder::OggVorbisCloseCallback(void *datasource) // 0x106CB6E0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OggVorbisCloseCallback@COggVorbisDecoder@FMOD@Audio@@CAHPAX@Z");
			// void *datasource;

			return 0;
		}

		_inline long COggVorbisDecoder::OggVorbisTellCallback(void *datasource) // 0x106CB820
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?OggVorbisTellCallback@COggVorbisDecoder@FMOD@Audio@@CAJPAX@Z");
			// void *datasource;
			// Audio::FMOD::COggVorbisDecoder *instance;
			// function call : long long () const

			COggVorbisDecoder *instance = (COggVorbisDecoder *)datasource;
			return (long)((Audio::FMOD::IReadStream *)instance->m_stream)->GetPosition();
		}
	}
}


namespace Audio
{
	namespace FMOD
	{
		FMOD_RESULT __stdcall CodecOpenCallback(FMOD_CODEC_STATE *codec_state, unsigned __int32 usermode, FMOD_CREATESOUNDEXINFO *userexinfo) // 0x106CB130
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?CodecOpenCallback@FMOD@Audio@@YG?AW4FMOD_RESULT@@PAUFMOD_CODEC_STATE@@IPAUFMOD_CREATESOUNDEXINFO@@@Z");
			// FMOD_CREATESOUNDEXINFO *userexinfo;
			// Audio::FMOD::COggVorbisDecoder *decoder;

			COggVorbisDecoder *decoder = (COggVorbisDecoder *)userexinfo->userdata;
			codec_state->waveformat = &decoder->m_waveformat;
			codec_state->numsubsounds = 0;
			codec_state->plugindata = decoder;
			return FMOD_OK;
		}
	}
}


namespace Audio
{
	namespace FMOD
	{
		FMOD_RESULT __stdcall CodecCloseCallback(FMOD_CODEC_STATE *codec_state) // 0x106CB0B0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?CodecCloseCallback@FMOD@Audio@@YG?AW4FMOD_RESULT@@PAUFMOD_CODEC_STATE@@@Z");
			// FMOD_CODEC_STATE *codec_state;
			// Audio::FMOD::COggVorbisDecoder *decoder;

			COggVorbisDecoder *decoder = (COggVorbisDecoder *)codec_state->plugindata;
			decoder->Release();
			delete decoder;
			return FMOD_OK;
		}
	}
}


namespace Audio
{
	namespace FMOD
	{
		FMOD_RESULT __stdcall CodecReadCallback(FMOD_CODEC_STATE *codec_state, void *buffer, unsigned __int32 sizebytes, unsigned __int32 *bytesread) // 0x106CB180
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?CodecReadCallback@FMOD@Audio@@YG?AW4FMOD_RESULT@@PAUFMOD_CODEC_STATE@@PAXIPAI@Z");
			// unsigned __int32 *bytesread;
			// Audio::FMOD::COggVorbisDecoder *decoder;

			COggVorbisDecoder *decoder = (COggVorbisDecoder *)codec_state->plugindata;
			*bytesread = decoder->Read((char *)buffer, sizebytes);
			return FMOD_OK;
		}
	}
}


namespace Audio
{
	namespace FMOD
	{
		FMOD_RESULT __stdcall CodecSetPositionCallback(FMOD_CODEC_STATE *codec_state, __int32 subsound, unsigned __int32 position, unsigned __int32 postype) // 0x106CB1F0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?CodecSetPositionCallback@FMOD@Audio@@YG?AW4FMOD_RESULT@@PAUFMOD_CODEC_STATE@@HII@Z");
			// unsigned __int32 postype;
			// Audio::FMOD::COggVorbisDecoder *decoder;

			COggVorbisDecoder *decoder = (COggVorbisDecoder *)codec_state->plugindata;
			decoder->SetPosition(position);
			return FMOD_OK;
		}
	}
}


namespace Audio
{
	namespace FMOD
	{
		FMOD_RESULT __stdcall StreamOpenCallback(char const *name, __int32 unicode, unsigned __int32 *fileSize, void **handle, void **userData) // 0x106CBCC0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?StreamOpenCallback@FMOD@Audio@@YG?AW4FMOD_RESULT@@PBDHPAIPAPAX2@Z");
			// void **userData;
			// long long filesize;
			// Audio::FMOD::IReadStream *stream;
			// function call : void (long long, __int32)
			// function call : long long () const
			// function call : void (long long, __int32)

			IReadStream *stream = (IReadStream *)name;
			stream->Seek(0, 2);
			long long filesize = stream->GetPosition();
			stream->Seek(0, 0);
			*handle = stream;
			*fileSize = (unsigned __int32)filesize;
			return FMOD_OK;
		}
	}
}


namespace Audio
{
	namespace FMOD
	{
		FMOD_RESULT __stdcall StreamCloseCallback(void *handle, void *userData) // 0x106CBCA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?StreamCloseCallback@FMOD@Audio@@YG?AW4FMOD_RESULT@@PAX0@Z");
			// void *userData;

			return FMOD_OK;
		}
	}
}


namespace Audio
{
	namespace FMOD
	{
		FMOD_RESULT __stdcall StreamReadCallback(void *handle, void *buffer, unsigned __int32 sizebytes, unsigned __int32 *bytesread, void *userData) // 0x106CBDA0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?StreamReadCallback@FMOD@Audio@@YG?AW4FMOD_RESULT@@PAX0IPAI0@Z");
			// void *userData;
			// Audio::FMOD::IReadStream *stream;
			// function call : __int32 (void *, __int32)

			IReadStream *stream = (IReadStream *)handle;
			*bytesread = stream->Read(buffer, sizebytes);
			return FMOD_OK;
		}
	}
}


namespace Audio
{
	namespace FMOD
	{
		FMOD_RESULT __stdcall StreamSeekCallback(void *handle, unsigned __int32 pos, void *userData) // 0x106CBE20
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?StreamSeekCallback@FMOD@Audio@@YG?AW4FMOD_RESULT@@PAXI0@Z");
			// void *userData;
			// Audio::FMOD::IReadStream *stream;
			// function call : void (long long, __int32)

			IReadStream *stream = (IReadStream *)handle;
			stream->Seek(pos, 0);
			return FMOD_OK;
		}

		void RegisterOggVorbisCodec(FMOD_SYSTEM *system, __int32 priority) // 0x106CB9C0
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?RegisterOggVorbisCodec@FMOD@Audio@@YAXPAUFMOD_SYSTEM@@H@Z");
			// static ...; // 0x106CBA6C
			// static ...; // 0x106CBA64
			// FMOD_SYSTEM *system;
			// __int32 priority;
			// FMOD_CODEC_DESCRIPTION codec;

			FMOD_CODEC_DESCRIPTION codec = { "FMOD Codec Ogg Vorbis", 0x00010000, 0, FMOD_TIMEUNIT_PCM, CodecOpenCallback, CodecCloseCallback, CodecReadCallback, nullptr, CodecSetPositionCallback, nullptr, nullptr };
			FMOD_System_CreateCodec(system, &codec, priority);
		}
	}
}


namespace Audio
{
	namespace FMOD
	{
		FMOD_RESULT CreateOggVorbisStream(FMOD_SYSTEM *system, void *data, unsigned __int32 length, unsigned __int32 mode, FMOD_SOUND **sound) // 0x106CB250
		{
			mangled_x86(MANGLED_KNOWN_GOOD, "?CreateOggVorbisStream@FMOD@Audio@@YA?AW4FMOD_RESULT@@PAUFMOD_SYSTEM@@PAXIIPAPAUFMOD_SOUND@@@Z");
			// void *data;
			// unsigned __int32 length;
			// unsigned __int32 mode;
			// FMOD_SOUND **sound;
			// Audio::FMOD::COggVorbisDecoder *decoder;
			// FMOD_CREATESOUNDEXINFO info;
			// Audio::FMOD::IReadStream *stream;
			// FMOD_RESULT result;

			IReadStream *stream = new CMemoryReadStream(data, length);
			COggVorbisDecoder *decoder = new COggVorbisDecoder();
			if (!decoder->Init(stream))
				return FMOD_ERR_INTERNAL;
			FMOD_CREATESOUNDEXINFO info;
			memset(&info, 0, sizeof(info));
			info.cbsize = sizeof(info);
			info.useropen = StreamOpenCallback;
			info.userclose = StreamCloseCallback;
			info.userseek = StreamSeekCallback;
			info.userread = StreamReadCallback;
			info.userdata = decoder;
			FMOD_RESULT result = FMOD_System_CreateSound(system, (char const *)stream, mode, &info, sound);
			return result;
		}
	}
}

/* ---------- private code */
