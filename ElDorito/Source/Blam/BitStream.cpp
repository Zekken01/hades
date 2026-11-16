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
		m_dataStart = data;
		m_dataEnd = data + sizeBytes;
		m_dataSizeBytes = sizeBytes;
		Reset(None);
	}

	void BitStream::Reset(Blam::BitStream::State state) // 0x1092A370
	{
		void (__thiscall *const Reset)(Blam::BitStream *, Blam::BitStream::State) = (void(__thiscall *const)(Blam::BitStream *, Blam::BitStream::State))0x559be0;

		Reset(this, state);
	}

	void BitStream::BeginWriting(__int32 alignmentsBits) // 0x10929F40
	{
		m_dataAlignmentBits = alignmentsBits;
		Reset(Writing);
	}

	void BitStream::FinishWriting(__int32 *bitsWritten) // 0x1092A150
	{
		void (__thiscall *const FinishWriting)(Blam::BitStream *, __int32 *) = (void(__thiscall *const)(Blam::BitStream *, __int32 *))0x5580d0;

		FinishWriting(this, bitsWritten);
	}

	void BitStream::BeginReading(__int32 alignmentsBits) // 0x10929EF0
	{
		Reset(Reading);
	}

	void BitStream::FinishReading() // 0x1092A0E0
	{
		void (__thiscall *const FinishReading)(Blam::BitStream *) = (void(__thiscall *const)(Blam::BitStream *))0x5580c0;

		FinishReading(this);
	}

	bool BitStream::BeginConsistencyCheck(__int32 alignmentsBits) // 0x10929E90
	{
		Reset(ConsistencyCheck);
		return true;
	}

	void BitStream::FinishConsistencyCheck() // 0x1092A070
	{
		void (__thiscall *const FinishConistencyCheck)(Blam::BitStream *) = (void(__thiscall *const)(Blam::BitStream *))0x5580b0;

		FinishConistencyCheck(this);
	}

	void BitStream::DiscardRemainingData() // 0x1092A020
	{
		m_currentMemoryBitPosition = m_dataSizeBytes * 8;
		m_accumulator = 0;
		m_accumulatorBitsUsed = 0;
	}

	bool BitStream::ReadBit() // 0x1092A1F0
	{
		bool (__thiscall *const ReadBit)(Blam::BitStream *) = (bool(__thiscall *const)(Blam::BitStream *))0x558570;

		return ReadBit(this);
	}

	unsigned long long BitStream::ReadBits(__int32 bits) // 0x1092A260
	{
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
		void (__thiscall *const ReadBlock)(Blam::BitStream *, unsigned char *, unsigned __int32) = (void(__thiscall *const)(Blam::BitStream *, unsigned char *, unsigned __int32))0x558740;

		ReadBlock(this, out, bits);
	}

	void BitStream::WriteBlock(unsigned __int32 bits, unsigned char const *data) // 0x1092A580
	{
		void (__thiscall *const WriteBlockImpl)(BitStream *, unsigned char const *, unsigned __int32, __int32) = (void(__thiscall *const)(BitStream *, unsigned char const *, unsigned __int32, __int32))0x55a000;

		WriteBlockImpl(this, data, bits, 0);
	}
}

/* ---------- private code */
