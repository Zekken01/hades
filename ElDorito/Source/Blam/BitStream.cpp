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
	void BitStream::SetData(unsigned char *data, __int32 sizeBytes) // 0x1092A3E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SetData@BitStream@Blam@@QAEXPAEH@Z");
		// __int32 sizeBytes;

		m_dataStart = data;
		m_dataEnd = data + sizeBytes;
		m_dataSizeBytes = sizeBytes;
		Reset(None);
	}

	void BitStream::Reset(Blam::BitStream::State state) // 0x1092A370
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?Reset@BitStream@Blam@@AAEXW4State@12@@Z");
		// Blam::BitStream::State state;
		// void (*const Reset)(Blam::BitStream *, Blam::BitStream::State);
		// function call : void (*const)(Blam::BitStream *, Blam::BitStream::State)

		void (__thiscall *const Reset)(Blam::BitStream *, Blam::BitStream::State) = (void(__thiscall *const)(Blam::BitStream *, Blam::BitStream::State))0x559be0;

		Reset(this, state);
	}

	void BitStream::BeginWriting(__int32 alignmentsBits) // 0x10929F40
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?BeginWriting@BitStream@Blam@@QAEXH@Z");
		// __int32 alignmentsBits;

		m_dataAlignmentBits = alignmentsBits;
		Reset(Writing);
	}

	void BitStream::FinishWriting(__int32 *bitsWritten) // 0x1092A150
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?FinishWriting@BitStream@Blam@@QAEXPAH@Z");
		// __int32 *bitsWritten;
		// void (*const FinishWriting)(Blam::BitStream *, __int32 *);
		// function call : void (*const)(Blam::BitStream *, __int32 *)

		void (__thiscall *const FinishWriting)(Blam::BitStream *, __int32 *) = (void(__thiscall *const)(Blam::BitStream *, __int32 *))0x5580d0;

		FinishWriting(this, bitsWritten);
	}

	void BitStream::BeginReading(__int32 alignmentsBits) // 0x10929EF0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?BeginReading@BitStream@Blam@@QAEXH@Z");
		// __int32 alignmentsBits;

		Reset(Reading);
	}

	void BitStream::FinishReading() // 0x1092A0E0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?FinishReading@BitStream@Blam@@QAEXXZ");
		// Blam::BitStream *const this;
		// void (*const FinishReading)(Blam::BitStream *);
		// function call : void (*const)(Blam::BitStream *)

		void (__thiscall *const FinishReading)(Blam::BitStream *) = (void(__thiscall *const)(Blam::BitStream *))0x5580c0;

		FinishReading(this);
	}

	bool BitStream::BeginConsistencyCheck(__int32 alignmentsBits) // 0x10929E90
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?BeginConsistencyCheck@BitStream@Blam@@QAE_NH@Z");
		// __int32 alignmentsBits;

		Reset(ConsistencyCheck);
		return true;
	}

	void BitStream::FinishConsistencyCheck() // 0x1092A070
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?FinishConsistencyCheck@BitStream@Blam@@QAEXXZ");
		// Blam::BitStream *const this;
		// void (*const FinishConistencyCheck)(Blam::BitStream *);
		// function call : void (*const)(Blam::BitStream *)

		void (__thiscall *const FinishConistencyCheck)(Blam::BitStream *) = (void(__thiscall *const)(Blam::BitStream *))0x5580b0;

		FinishConistencyCheck(this);
	}

	void BitStream::DiscardRemainingData() // 0x1092A020
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?DiscardRemainingData@BitStream@Blam@@QAEXXZ");
		// Blam::BitStream *const this;

		m_currentMemoryBitPosition = m_dataSizeBytes * 8;
		m_accumulator = 0;
		m_accumulatorBitsUsed = 0;
	}

	bool BitStream::ReadBit() // 0x1092A1F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ReadBit@BitStream@Blam@@AAE_NXZ");
		// Blam::BitStream *const this;
		// bool (*const ReadBit)(Blam::BitStream *);
		// function call : bool (*const)(Blam::BitStream *)

		bool (__thiscall *const ReadBit)(Blam::BitStream *) = (bool(__thiscall *const)(Blam::BitStream *))0x558570;

		return ReadBit(this);
	}

	unsigned long long BitStream::ReadBits(__int32 bits) // 0x1092A260
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ReadBits@BitStream@Blam@@AAE_KH@Z");
		// __int32 bits;
		// unsigned long long (*const ReadBits64)(Blam::BitStream *, __int32);
			// unsigned __int32 (*const ReadBits32)(Blam::BitStream *, __int32);
		// function call : unsigned __int32 (*const)(Blam::BitStream *, __int32)
		// function call : unsigned long long (*const)(Blam::BitStream *, __int32)

		if (bits <= 32)
		{
			unsigned long (__thiscall *const ReadBitsImpl)(BitStream *, __int32) = (unsigned long (__thiscall *)(BitStream *, __int32))0x5589A0;
			return ReadBitsImpl(this, bits);
		}

		unsigned long long (__thiscall *const ReadBitsLongImpl)(BitStream *, __int32) = (unsigned long long (__thiscall *)(BitStream *, __int32))0x559160;
		return ReadBitsLongImpl(this, bits);
	}

	void BitStream::WriteBits(unsigned long long val, __int32 bits) // 0x1092A460
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?WriteBits@BitStream@Blam@@AAEX_KH@Z");
		// __int32 bits;
		// unsigned long long masked;
			// void (*const WriteBits)(Blam::BitStream *, unsigned long long, __int32);
		// function call : void (*const)(Blam::BitStream *, unsigned long long, __int32)

		unsigned long long masked = val & ~(-1LL << bits);
		if (BitsAvailable(bits))
		{
			m_currentStreamBitPosition += bits;
			m_accumulatorBitsUsed += bits;
			m_accumulator <<= bits;
			m_accumulator |= masked;
		}
		else
		{
			void (__thiscall *const WriteBits)(Blam::BitStream *, unsigned long long, __int32) = (void(__thiscall *const)(Blam::BitStream *, unsigned long long, __int32))0x559EB0;
			WriteBits(this, masked, bits);
		}
	}

	void BitStream::ReadBlock(unsigned __int32 bits, unsigned char *out) // 0x1092A300
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ReadBlock@BitStream@Blam@@QAEXIPAE@Z");
		// unsigned char *out;
		// void (*const ReadBlock)(Blam::BitStream *, unsigned char *, unsigned __int32);
		// function call : void (*const)(Blam::BitStream *, unsigned char *, unsigned __int32)

		void (__thiscall *const ReadBlock)(Blam::BitStream *, unsigned char *, unsigned __int32) = (void(__thiscall *const)(Blam::BitStream *, unsigned char *, unsigned __int32))0x558740;

		ReadBlock(this, out, bits);
	}

	void BitStream::WriteBlock(unsigned __int32 bits, unsigned char const *data) // 0x1092A580
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?WriteBlock@BitStream@Blam@@QAEXIPBE@Z");
		// unsigned char const *data;
		// void (*const WriteBlock)(Blam::BitStream *, unsigned char const *, unsigned __int32, __int32);
		// function call : void (*const)(Blam::BitStream *, unsigned char const *, unsigned __int32, __int32)

		void (__thiscall *const WriteBlockImpl)(BitStream *, unsigned char const *, unsigned __int32, __int32) = (void(__thiscall *const)(BitStream *, unsigned char const *, unsigned __int32, __int32))0x55a000;

		WriteBlockImpl(this, data, bits, 0);
	}
}

/* ---------- private code */
