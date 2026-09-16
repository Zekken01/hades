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
		_extern void _sub_106CAFB0(Audio::FMOD::IReadStream *const);

		extern CMemoryReadStream* _sub_106CAEB0(Audio::FMOD::CMemoryReadStream *const, void *, __int32);
		_inline CMemoryReadStream::CMemoryReadStream(void *buffer, __int32 length) // 0x106CAEB0
		{
			mangled_x86(MANGLED_TODO, "??0CMemoryReadStream@FMOD@Audio@@QAE@PAXH@Z");
			// __int32 length;
			todo("implement");
			_sub_106CAEB0(this, buffer, length);
		}

		// mangled_x86(MANGLED_DEFAULT, "??0IReadStream@FMOD@Audio@@QAE@XZ"); no body to assert in
		_inline IReadStream::IReadStream() = default; // 0x106CAF30

		// mangled_x86(MANGLED_DEFAULT, "??1CMemoryReadStream@FMOD@Audio@@UAE@XZ"); no body to assert in
		_inline CMemoryReadStream::~CMemoryReadStream() = default; // 0x106CAF60

		_extern __int32 _sub_106CB890(Audio::FMOD::CMemoryReadStream *const, void *, __int32);
		_inline __int32 CMemoryReadStream::Read(void *buffer, __int32 bytes) // 0x106CB890
		{
			mangled_x86(MANGLED_TODO, "?Read@CMemoryReadStream@FMOD@Audio@@UAEHPAXH@Z");
			// __int32 bytes;
			// __int32 n;
			todo("implement");
			__int32 __result = _sub_106CB890(this, buffer, bytes);
			return __result;
		}

		_extern void _sub_106CBB80(Audio::FMOD::CMemoryReadStream *const, long long, __int32);
		_inline void CMemoryReadStream::Seek(long long offset, __int32 type) // 0x106CBB80
		{
			mangled_x86(MANGLED_TODO, "?Seek@CMemoryReadStream@FMOD@Audio@@UAEX_JH@Z");
			// __int32 type;
			todo("implement");
			_sub_106CBB80(this, offset, type);
		}

		_extern long long _sub_106CB4B0(Audio::FMOD::CMemoryReadStream const *const);
		_inline long long CMemoryReadStream::GetPosition() const // 0x106CB4B0
		{
			mangled_x86(MANGLED_TODO, "?GetPosition@CMemoryReadStream@FMOD@Audio@@UBE_JXZ");
			// Audio::FMOD::CMemoryReadStream const *const this;
			todo("implement");
			long long __result = _sub_106CB4B0((Audio::FMOD::CMemoryReadStream const *)this);
			return __result;
		}

		_extern long long _sub_106CB480(Audio::FMOD::CMemoryReadStream const *const);
		_inline long long CMemoryReadStream::GetLength() const // 0x106CB480
		{
			mangled_x86(MANGLED_TODO, "?GetLength@CMemoryReadStream@FMOD@Audio@@UBE_JXZ");
			// Audio::FMOD::CMemoryReadStream const *const this;
			todo("implement");
			long long __result = _sub_106CB480((Audio::FMOD::CMemoryReadStream const *)this);
			return __result;
		}

		_extern bool _sub_106CB4E0(Audio::FMOD::COggVorbisDecoder *const, Audio::FMOD::IReadStream *);
		_inline bool COggVorbisDecoder::Init(Audio::FMOD::IReadStream *stream) // 0x106CB4E0
		{
			mangled_x86(MANGLED_TODO, "?Init@COggVorbisDecoder@FMOD@Audio@@QAE_NPAUIReadStream@23@@Z");
			// static ...; // 0x106CB664
			// static ...; // 0x106CB65C
			// Audio::FMOD::COggVorbisDecoder *const this;
			// Audio::FMOD::IReadStream *stream;
			// __int32 ret;
			// vorbis_info *vi;
			// ov_callbacks callbacks;
			// function call : long long () const
			todo("implement");
			bool __result = _sub_106CB4E0(this, stream);
			return __result;
		}

		_extern void _sub_106CBAB0(Audio::FMOD::COggVorbisDecoder *const);
		_inline void COggVorbisDecoder::Release() // 0x106CBAB0
		{
			mangled_x86(MANGLED_TODO, "?Release@COggVorbisDecoder@FMOD@Audio@@QAEXXZ");
			// Audio::FMOD::COggVorbisDecoder *const this;
			// function call : void *(unsigned __int32)
			todo("implement");
			_sub_106CBAB0(this);
		}

		_extern bool _sub_106CBC10(Audio::FMOD::COggVorbisDecoder *const, long long);
		_inline bool COggVorbisDecoder::SetPosition(long long pcm) // 0x106CBC10
		{
			mangled_x86(MANGLED_TODO, "?SetPosition@COggVorbisDecoder@FMOD@Audio@@QAE_N_J@Z");
			// long long pcm;
			todo("implement");
			bool __result = _sub_106CBC10(this, pcm);
			return __result;
		}

		_extern __int32 _sub_106CB950(Audio::FMOD::COggVorbisDecoder *const, char *, __int32);
		_inline __int32 COggVorbisDecoder::Read(char *buffer, __int32 sizebytes) // 0x106CB950
		{
			mangled_x86(MANGLED_TODO, "?Read@COggVorbisDecoder@FMOD@Audio@@QAEHPADH@Z");
			// __int32 sizebytes;
			todo("implement");
			__int32 __result = _sub_106CB950(this, buffer, sizebytes);
			return __result;
		}

		_extern unsigned __int32 _sub_106CB700(void *, unsigned __int32, unsigned __int32, void *);
		_inline unsigned __int32 COggVorbisDecoder::OggVorbisReadCallback(void *ptr, unsigned __int32 size, unsigned __int32 nmemb, void *datasource) // 0x106CB700
		{
			mangled_x86(MANGLED_TODO, "?OggVorbisReadCallback@COggVorbisDecoder@FMOD@Audio@@CAIPAXII0@Z");
			// void *datasource;
			// Audio::FMOD::COggVorbisDecoder *instance;
			// function call : __int32 (void *, __int32)
			todo("implement");
			unsigned __int32 __result = _sub_106CB700(ptr, size, nmemb, datasource);
			return __result;
		}

		_extern __int32 _sub_106CB790(void *, long long, __int32);
		_inline __int32 COggVorbisDecoder::OggVorbisSeekCallback(void *datasource, long long offset, __int32 whence) // 0x106CB790
		{
			mangled_x86(MANGLED_TODO, "?OggVorbisSeekCallback@COggVorbisDecoder@FMOD@Audio@@CAHPAX_JH@Z");
			// __int32 whence;
			// Audio::FMOD::COggVorbisDecoder *instance;
			// function call : void (long long, __int32)
			todo("implement");
			__int32 __result = _sub_106CB790(datasource, offset, whence);
			return __result;
		}

		_extern __int32 _sub_106CB6E0(void *);
		_inline __int32 COggVorbisDecoder::OggVorbisCloseCallback(void *datasource) // 0x106CB6E0
		{
			mangled_x86(MANGLED_TODO, "?OggVorbisCloseCallback@COggVorbisDecoder@FMOD@Audio@@CAHPAX@Z");
			// void *datasource;
			todo("implement");
			__int32 __result = _sub_106CB6E0(datasource);
			return __result;
		}

		_extern long _sub_106CB820(void *);
		_inline long COggVorbisDecoder::OggVorbisTellCallback(void *datasource) // 0x106CB820
		{
			mangled_x86(MANGLED_TODO, "?OggVorbisTellCallback@COggVorbisDecoder@FMOD@Audio@@CAJPAX@Z");
			// void *datasource;
			// Audio::FMOD::COggVorbisDecoder *instance;
			// function call : long long () const
			todo("implement");
			long __result = _sub_106CB820(datasource);
			return __result;
		}
	}
}

extern FMOD_RESULT _sub_106CB130(FMOD_CODEC_STATE *, unsigned __int32, FMOD_CREATESOUNDEXINFO *);
namespace Audio
{
	namespace FMOD
	{
		FMOD_RESULT __stdcall CodecOpenCallback(FMOD_CODEC_STATE *codec_state, unsigned __int32 usermode, FMOD_CREATESOUNDEXINFO *userexinfo) // 0x106CB130
		{
			mangled_x86(MANGLED_TODO, "?CodecOpenCallback@FMOD@Audio@@YG?AW4FMOD_RESULT@@PAUFMOD_CODEC_STATE@@IPAUFMOD_CREATESOUNDEXINFO@@@Z");
			// FMOD_CREATESOUNDEXINFO *userexinfo;
			// Audio::FMOD::COggVorbisDecoder *decoder;
			todo("implement");
			FMOD_RESULT __result = _sub_106CB130(codec_state, usermode, userexinfo);
			return __result;
		}
	}
}

extern FMOD_RESULT _sub_106CB0B0(FMOD_CODEC_STATE *);
namespace Audio
{
	namespace FMOD
	{
		FMOD_RESULT __stdcall CodecCloseCallback(FMOD_CODEC_STATE *codec_state) // 0x106CB0B0
		{
			mangled_x86(MANGLED_TODO, "?CodecCloseCallback@FMOD@Audio@@YG?AW4FMOD_RESULT@@PAUFMOD_CODEC_STATE@@@Z");
			// FMOD_CODEC_STATE *codec_state;
			// Audio::FMOD::COggVorbisDecoder *decoder;
			todo("implement");
			FMOD_RESULT __result = _sub_106CB0B0(codec_state);
			return __result;
		}
	}
}

extern FMOD_RESULT _sub_106CB180(FMOD_CODEC_STATE *, void *, unsigned __int32, unsigned __int32 *);
namespace Audio
{
	namespace FMOD
	{
		FMOD_RESULT __stdcall CodecReadCallback(FMOD_CODEC_STATE *codec_state, void *buffer, unsigned __int32 sizebytes, unsigned __int32 *bytesread) // 0x106CB180
		{
			mangled_x86(MANGLED_TODO, "?CodecReadCallback@FMOD@Audio@@YG?AW4FMOD_RESULT@@PAUFMOD_CODEC_STATE@@PAXIPAI@Z");
			// unsigned __int32 *bytesread;
			// Audio::FMOD::COggVorbisDecoder *decoder;
			todo("implement");
			FMOD_RESULT __result = _sub_106CB180(codec_state, buffer, sizebytes, bytesread);
			return __result;
		}
	}
}

extern FMOD_RESULT _sub_106CB1F0(FMOD_CODEC_STATE *, __int32, unsigned __int32, unsigned __int32);
namespace Audio
{
	namespace FMOD
	{
		FMOD_RESULT __stdcall CodecSetPositionCallback(FMOD_CODEC_STATE *codec_state, __int32 subsound, unsigned __int32 position, unsigned __int32 postype) // 0x106CB1F0
		{
			mangled_x86(MANGLED_TODO, "?CodecSetPositionCallback@FMOD@Audio@@YG?AW4FMOD_RESULT@@PAUFMOD_CODEC_STATE@@HII@Z");
			// unsigned __int32 postype;
			// Audio::FMOD::COggVorbisDecoder *decoder;
			todo("implement");
			FMOD_RESULT __result = _sub_106CB1F0(codec_state, subsound, position, postype);
			return __result;
		}
	}
}

extern FMOD_RESULT _sub_106CBCC0(char const *, __int32, unsigned __int32 *, void **, void **);
namespace Audio
{
	namespace FMOD
	{
		FMOD_RESULT __stdcall StreamOpenCallback(char const *name, __int32 unicode, unsigned __int32 *fileSize, void **handle, void **userData) // 0x106CBCC0
		{
			mangled_x86(MANGLED_TODO, "?StreamOpenCallback@FMOD@Audio@@YG?AW4FMOD_RESULT@@PBDHPAIPAPAX2@Z");
			// void **userData;
			// long long filesize;
			// Audio::FMOD::IReadStream *stream;
			// function call : void (long long, __int32)
			// function call : long long () const
			// function call : void (long long, __int32)
			todo("implement");
			FMOD_RESULT __result = _sub_106CBCC0(name, unicode, fileSize, handle, userData);
			return __result;
		}
	}
}

extern FMOD_RESULT _sub_106CBCA0(void *, void *);
namespace Audio
{
	namespace FMOD
	{
		FMOD_RESULT __stdcall StreamCloseCallback(void *handle, void *userData) // 0x106CBCA0
		{
			mangled_x86(MANGLED_TODO, "?StreamCloseCallback@FMOD@Audio@@YG?AW4FMOD_RESULT@@PAX0@Z");
			// void *userData;
			todo("implement");
			FMOD_RESULT __result = _sub_106CBCA0(handle, userData);
			return __result;
		}
	}
}

extern FMOD_RESULT _sub_106CBDA0(void *, void *, unsigned __int32, unsigned __int32 *, void *);
namespace Audio
{
	namespace FMOD
	{
		FMOD_RESULT __stdcall StreamReadCallback(void *handle, void *buffer, unsigned __int32 sizebytes, unsigned __int32 *bytesread, void *userData) // 0x106CBDA0
		{
			mangled_x86(MANGLED_TODO, "?StreamReadCallback@FMOD@Audio@@YG?AW4FMOD_RESULT@@PAX0IPAI0@Z");
			// void *userData;
			// Audio::FMOD::IReadStream *stream;
			// function call : __int32 (void *, __int32)
			todo("implement");
			FMOD_RESULT __result = _sub_106CBDA0(handle, buffer, sizebytes, bytesread, userData);
			return __result;
		}
	}
}

extern FMOD_RESULT _sub_106CBE20(void *, unsigned __int32, void *);
namespace Audio
{
	namespace FMOD
	{
		FMOD_RESULT __stdcall StreamSeekCallback(void *handle, unsigned __int32 pos, void *userData) // 0x106CBE20
		{
			mangled_x86(MANGLED_TODO, "?StreamSeekCallback@FMOD@Audio@@YG?AW4FMOD_RESULT@@PAXI0@Z");
			// void *userData;
			// Audio::FMOD::IReadStream *stream;
			// function call : void (long long, __int32)
			todo("implement");
			FMOD_RESULT __result = _sub_106CBE20(handle, pos, userData);
			return __result;
		}

		_extern void _sub_106CB9C0(FMOD_SYSTEM *, __int32);
		void RegisterOggVorbisCodec(FMOD_SYSTEM *system, __int32 priority) // 0x106CB9C0
		{
			mangled_x86(MANGLED_TODO, "?RegisterOggVorbisCodec@FMOD@Audio@@YAXPAUFMOD_SYSTEM@@H@Z");
			// static ...; // 0x106CBA6C
			// static ...; // 0x106CBA64
			// FMOD_SYSTEM *system;
			// __int32 priority;
			// FMOD_CODEC_DESCRIPTION codec;
			todo("implement");
			_sub_106CB9C0(system, priority);
		}
	}
}

extern FMOD_RESULT _sub_106CB250(FMOD_SYSTEM *, void *, unsigned __int32, unsigned __int32, FMOD_SOUND **);
namespace Audio
{
	namespace FMOD
	{
		FMOD_RESULT CreateOggVorbisStream(FMOD_SYSTEM *system, void *data, unsigned __int32 length, unsigned __int32 mode, FMOD_SOUND **sound) // 0x106CB250
		{
			mangled_x86(MANGLED_TODO, "?CreateOggVorbisStream@FMOD@Audio@@YA?AW4FMOD_RESULT@@PAUFMOD_SYSTEM@@PAXIIPAPAUFMOD_SOUND@@@Z");
			// void *data;
			// unsigned __int32 length;
			// unsigned __int32 mode;
			// FMOD_SOUND **sound;
			// Audio::FMOD::COggVorbisDecoder *decoder;
			// FMOD_CREATESOUNDEXINFO info;
			// Audio::FMOD::IReadStream *stream;
			// FMOD_RESULT result;
			todo("implement");
			FMOD_RESULT __result = _sub_106CB250(system, data, length, mode, sound);
			return __result;
		}
	}
}

/* ---------- private code */
