/* ---------- headers */

#include "hades/hades.h"

#include "Blam/BitStream.hpp"
#include "Blam/memory/bitstream.hpp"
#include "ChatCommands/ChatCommandMap.hpp"

#include <Windows.h>
#include <cstddef>
#include <cstdlib>
#include <type_traits>

/* ---------- forward declarations */

namespace Blam
{
	class BitStream;
}

namespace Utils {}
using namespace ::Utils;
namespace Blam {}
using namespace ::Blam;

/* ---------- constants */

/* ---------- definitions */

/* ---------- prototypes */

/* ---------- globals */

/* ---------- private variables */

/* ---------- public code */

namespace Blam
{
	_extern void _sub_1092A3E0(Blam::BitStream *const, unsigned char *, __int32);
	void BitStream::SetData(unsigned char *data, __int32 sizeBytes) // 0x1092A3E0
	{
		mangled_x86(MANGLED_TODO, "?SetData@BitStream@Blam@@QAEXPAEH@Z");
		// __int32 sizeBytes;
		todo("implement");
		_sub_1092A3E0(this, data, sizeBytes);
	}

	_extern void _sub_1092A370(Blam::BitStream *const, Blam::BitStream::State);
	void BitStream::Reset(Blam::BitStream::State state) // 0x1092A370
	{
		mangled_x86(MANGLED_TODO, "?Reset@BitStream@Blam@@AAEXW4State@12@@Z");
		// Blam::BitStream::State state;
		// void (*const Reset)(Blam::BitStream *, Blam::BitStream::State);
		// function call : void (*const)(Blam::BitStream *, Blam::BitStream::State)
		todo("implement");
		_sub_1092A370(this, state);
	}

	_extern void _sub_10929F40(Blam::BitStream *const, __int32);
	void BitStream::BeginWriting(__int32 alignmentsBits) // 0x10929F40
	{
		mangled_x86(MANGLED_TODO, "?BeginWriting@BitStream@Blam@@QAEXH@Z");
		// __int32 alignmentsBits;
		todo("implement");
		_sub_10929F40(this, alignmentsBits);
	}

	_extern void _sub_1092A150(Blam::BitStream *const, __int32 *);
	void BitStream::FinishWriting(__int32 *bitsWritten) // 0x1092A150
	{
		mangled_x86(MANGLED_TODO, "?FinishWriting@BitStream@Blam@@QAEXPAH@Z");
		// __int32 *bitsWritten;
		// void (*const FinishWriting)(Blam::BitStream *, __int32 *);
		// function call : void (*const)(Blam::BitStream *, __int32 *)
		todo("implement");
		_sub_1092A150(this, bitsWritten);
	}

	_extern void _sub_10929EF0(Blam::BitStream *const, __int32);
	void BitStream::BeginReading(__int32 alignmentsBits) // 0x10929EF0
	{
		mangled_x86(MANGLED_TODO, "?BeginReading@BitStream@Blam@@QAEXH@Z");
		// __int32 alignmentsBits;
		todo("implement");
		_sub_10929EF0(this, alignmentsBits);
	}

	_extern void _sub_1092A0E0(Blam::BitStream *const);
	void BitStream::FinishReading() // 0x1092A0E0
	{
		mangled_x86(MANGLED_TODO, "?FinishReading@BitStream@Blam@@QAEXXZ");
		// Blam::BitStream *const this;
		// void (*const FinishReading)(Blam::BitStream *);
		// function call : void (*const)(Blam::BitStream *)
		todo("implement");
		_sub_1092A0E0(this);
	}

	_extern bool _sub_10929E90(Blam::BitStream *const, __int32);
	bool BitStream::BeginConsistencyCheck(__int32 alignmentsBits) // 0x10929E90
	{
		mangled_x86(MANGLED_TODO, "?BeginConsistencyCheck@BitStream@Blam@@QAE_NH@Z");
		// __int32 alignmentsBits;
		todo("implement");
		bool __result = _sub_10929E90(this, alignmentsBits);
		return __result;
	}

	_extern void _sub_1092A070(Blam::BitStream *const);
	void BitStream::FinishConsistencyCheck() // 0x1092A070
	{
		mangled_x86(MANGLED_TODO, "?FinishConsistencyCheck@BitStream@Blam@@QAEXXZ");
		// Blam::BitStream *const this;
		// void (*const FinishConistencyCheck)(Blam::BitStream *);
		// function call : void (*const)(Blam::BitStream *)
		todo("implement");
		_sub_1092A070(this);
	}

	_extern void _sub_1092A020(Blam::BitStream *const);
	void BitStream::DiscardRemainingData() // 0x1092A020
	{
		mangled_x86(MANGLED_TODO, "?DiscardRemainingData@BitStream@Blam@@QAEXXZ");
		// Blam::BitStream *const this;
		todo("implement");
		_sub_1092A020(this);
	}

	_extern bool _sub_1092A1F0(Blam::BitStream *const);
	bool BitStream::ReadBit() // 0x1092A1F0
	{
		mangled_x86(MANGLED_TODO, "?ReadBit@BitStream@Blam@@AAE_NXZ");
		// Blam::BitStream *const this;
		// bool (*const ReadBit)(Blam::BitStream *);
		// function call : bool (*const)(Blam::BitStream *)
		todo("implement");
		bool __result = _sub_1092A1F0(this);
		return __result;
	}

	_extern unsigned long long _sub_1092A260(Blam::BitStream *const, __int32);
	unsigned long long BitStream::ReadBits(__int32 bits) // 0x1092A260
	{
		mangled_x86(MANGLED_TODO, "?ReadBits@BitStream@Blam@@AAE_KH@Z");
		// __int32 bits;
		// unsigned long long (*const ReadBits64)(Blam::BitStream *, __int32);
		{
			// unsigned __int32 (*const ReadBits32)(Blam::BitStream *, __int32);
		}
		// function call : unsigned __int32 (*const)(Blam::BitStream *, __int32)
		// function call : unsigned long long (*const)(Blam::BitStream *, __int32)
		todo("implement");
		unsigned long long __result = _sub_1092A260(this, bits);
		return __result;
	}

	_extern void _sub_1092A460(Blam::BitStream *const, unsigned long long, __int32);
	void BitStream::WriteBits(unsigned long long val, __int32 bits) // 0x1092A460
	{
		mangled_x86(MANGLED_TODO, "?WriteBits@BitStream@Blam@@AAEX_KH@Z");
		// __int32 bits;
		// unsigned long long masked;
		{
			// void (*const WriteBits)(Blam::BitStream *, unsigned long long, __int32);
		}
		// function call : void (*const)(Blam::BitStream *, unsigned long long, __int32)
		todo("implement");
		_sub_1092A460(this, val, bits);
	}

	_extern void _sub_1092A300(Blam::BitStream *const, unsigned __int32, unsigned char *);
	void BitStream::ReadBlock(unsigned __int32 bits, unsigned char *out) // 0x1092A300
	{
		mangled_x86(MANGLED_TODO, "?ReadBlock@BitStream@Blam@@QAEXIPAE@Z");
		// unsigned char *out;
		// void (*const ReadBlock)(Blam::BitStream *, unsigned char *, unsigned __int32);
		// function call : void (*const)(Blam::BitStream *, unsigned char *, unsigned __int32)
		todo("implement");
		_sub_1092A300(this, bits, out);
	}

	_extern void _sub_1092A580(Blam::BitStream *const, unsigned __int32, unsigned char const *);
	void BitStream::WriteBlock(unsigned __int32 bits, unsigned char const *data) // 0x1092A580
	{
		mangled_x86(MANGLED_TODO, "?WriteBlock@BitStream@Blam@@QAEXIPBE@Z");
		// unsigned char const *data;
		// void (*const WriteBlock)(Blam::BitStream *, unsigned char const *, unsigned __int32, __int32);
		// function call : void (*const)(Blam::BitStream *, unsigned char const *, unsigned __int32, __int32)
		todo("implement");
		_sub_1092A580(this, bits, data);
	}
}

/* ---------- private code */
