#ifndef __BLAM_BITSTREAM_HPP__
#define __BLAM_BITSTREAM_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"
#include "Utils/Bits.hpp"
#include <type_traits>

/* ---------- forward declarations */

struct t_arg0;
namespace Blam
{
	class BitStream;
}

/* ---------- constants */

/* ---------- definitions */

namespace Blam
{
	class BitStream
	{
	public:
		public:
		enum State
		{
			None = 0,
			Writing,
			WriteFinished,
			Reading,
			ConsistencyCheck,
			ReadFinished,
		};
		struct Stream
		{
			__int32 memoryBitPosition; // 0x0
			__int32 streamBitPosition; // 0x4
			unsigned long long accumulator; // 0x8
			__int32 accumulatorBitsUsed; // 0x10
		};
		static_assert(sizeof(Stream) == 24, "Invalid Stream size");
		public:
		BitStream(unsigned char *, __int32);
		BitStream();
		State GetState() const;
		_inline __int32 SizeBytes() const;
		_inline __int32 StreamBitPosition() const;
		__int32 MemoryBitPosition() const;
		bool Overflowed() const;
		void SetData(unsigned char *data, __int32 sizeBytes);
		void BeginWriting(__int32 alignmentsBits);
		void FinishWriting(__int32 *bitsWritten);
		void BeginReading(__int32 alignmentsBits);
		void FinishReading();
		bool BeginConsistencyCheck(__int32 alignmentsBits);
		void FinishConsistencyCheck();
		void DiscardRemainingData();
		_inline bool ReadBool();
		_inline void WriteBool(bool b);
		void ReadBlock(unsigned __int32 bits, unsigned char *out);
		void WriteBlock(unsigned __int32 bits, unsigned char const *data);
	private:
		_inline __int32 GetAvailableBits() const;
		_inline bool BitsAvailable(__int32 bits) const;
		bool ReadBit();
		unsigned long long ReadBits(__int32 bits);
		void WriteBits(unsigned long long val, __int32 bits);
		void Reset(State state);
		unsigned char *m_dataStart; // 0x0
		unsigned char *m_dataEnd; // 0x4
		__int32 m_dataSizeBytes; // 0x8
		__int32 m_dataAlignmentBits; // 0xC
		State m_state; // 0x10
		bool m_errorOccured; // 0x14
		unsigned char __pad0[3]; // 0x15
		__int32 m_currentMemoryBitPosition; // 0x18
		__int32 m_currentStreamBitPosition; // 0x1C
		unsigned long long m_accumulator; // 0x20
		__int32 m_accumulatorBitsUsed; // 0x28
		unsigned char *m_currentDataHead; // 0x2C
		__int32 m_positionStackDepth; // 0x30
		unsigned char __pad1[4]; // 0x34
		Stream m_positionStack[4]; // 0x38
		__int32 unk98; // 0x98
		__int32 unk9C; // 0x9C
	public:
		// `?A_P` in the decorated name is a deduced return; writing
		// `std::make_unsigned_t<t_arg0>` out decorates as the concrete type and
		// pairs with nothing.
		template<typename t_arg0>
		auto Read(__int32 bits);
		template<typename t_arg0>
		auto Read(t_arg0 minValue, t_arg0 maxValue);
		template<typename t_arg0, int t_arg1>
		bool ReadString(t_arg0 (&)[t_arg1]);
		template<typename t_arg0, int t_arg1>
		void ReadStringFixed(t_arg0 (&)[t_arg1]);
		template<typename t_arg0>
		t_arg0 ReadUnsigned(__int32 bits);
		template<typename t_arg0>
		t_arg0 ReadUnsigned(t_arg0 minValue, t_arg0 maxValue);
		template<typename t_arg0>
		void Write(t_arg0 val, __int32 bits);
		template<typename t_arg0>
		void Write(t_arg0 val, t_arg0 minValue, t_arg0 maxValue);
		template<typename t_arg0, int t_arg1>
		void WriteString(t_arg0 const (&)[t_arg1]);
		template<typename t_arg0, int t_arg1>
		void WriteStringFixed(t_arg0 const (&)[t_arg1]);
		template<typename t_arg0>
		void WriteUnsigned(t_arg0 val, __int32 bits);
		template<typename t_arg0>
		void WriteUnsigned(t_arg0 val, t_arg0 minValue, t_arg0 maxValue);
	};
	static_assert(sizeof(Blam::BitStream) == 160, "Invalid Blam::BitStream size");
}

/* ---------- prototypes */

/* ---------- globals */

/* ---------- public code */

namespace Blam
{
	inline __int32 BitStream::SizeBytes() const // 0x10ACE5C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?SizeBytes@BitStream@Blam@@QBEHXZ");

		return m_dataSizeBytes;
	}

	inline __int32 BitStream::StreamBitPosition() const // 0x10ACE5F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?StreamBitPosition@BitStream@Blam@@QBEHXZ");

		return m_currentStreamBitPosition;
	}

	inline bool BitStream::ReadBool() // 0x107F00A0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?ReadBool@BitStream@Blam@@QAE_NXZ");

		return ReadBit();
	}
}

template<typename t_arg0>
_inline auto Blam::BitStream::Read(__int32 bits)
{
	mangled_prefix_assert("??$Read@");

	return ReadUnsigned<std::make_unsigned_t<t_arg0> >(bits);
}

template<typename t_arg0>
_inline auto Blam::BitStream::Read(t_arg0 minValue, t_arg0 maxValue)
{
	mangled_prefix_assert("??$Read@");

	return ReadUnsigned<std::make_unsigned_t<t_arg0> >(minValue, maxValue);
}

template<typename t_arg0>
_inline t_arg0 Blam::BitStream::ReadUnsigned(__int32 bits)
{
	mangled_prefix_assert("??$ReadUnsigned@");

	return static_cast<t_arg0>(ReadBits(bits));
}

template<typename t_arg0>
_inline t_arg0 Blam::BitStream::ReadUnsigned(t_arg0 minValue, t_arg0 maxValue)
{
	mangled_prefix_assert("??$ReadUnsigned@");

	return ReadUnsigned<t_arg0>(Utils::Bits::CountBits(maxValue - minValue));
}

template<typename t_arg0>
_inline void Blam::BitStream::Write(t_arg0 val, __int32 bits)
{
	mangled_prefix_assert("??$Write@");

	WriteUnsigned<std::make_unsigned_t<t_arg0> >(val, bits);
}

template<typename t_arg0>
_inline void Blam::BitStream::Write(t_arg0 val, t_arg0 minValue, t_arg0 maxValue)
{
	mangled_prefix_assert("??$Write@");

	WriteUnsigned<std::make_unsigned_t<t_arg0> >(val, minValue, maxValue);
}

template<typename t_arg0>
_inline void Blam::BitStream::WriteUnsigned(t_arg0 val, __int32 bits)
{
	mangled_prefix_assert("??$WriteUnsigned@");

	WriteBits(val, bits);
}

template<typename t_arg0>
_inline void Blam::BitStream::WriteUnsigned(t_arg0 val, t_arg0 minValue, t_arg0 maxValue)
{
	mangled_prefix_assert("??$WriteUnsigned@");

	WriteUnsigned<unsigned long long>(val - minValue, Utils::Bits::CountBits(maxValue - minValue));
}

template<typename t_arg0, int t_arg1>
_inline bool Blam::BitStream::ReadString(t_arg0 (&str)[t_arg1])
{
	mangled_prefix_assert("??$ReadString@");

	// Length
	auto length = ReadUnsigned<size_t>(0U, t_arg1 - 1);
	if (length >= t_arg1)
		return false;

	// String
	memset(&str, 0, t_arg1 * sizeof(t_arg0));
	ReadBlock(length * sizeof(t_arg0) * 8, reinterpret_cast<unsigned char *>(&str));
	return true;
}

template<typename t_arg0, int t_arg1>
_inline void Blam::BitStream::ReadStringFixed(t_arg0 (&str)[t_arg1])
{
	mangled_prefix_assert("??$ReadStringFixed@");

	ReadBlock((t_arg1 - 1) * sizeof(t_arg0) * 8, reinterpret_cast<unsigned char *>(&str));
	str[t_arg1 - 1] = 0;
}

template<typename t_arg0, int t_arg1>
_inline void Blam::BitStream::WriteString(t_arg0 const (&str)[t_arg1])
{
	mangled_prefix_assert("??$WriteString@");

	// Compute length
	size_t length = 0;
	while (length < t_arg1 - 1 && str[length])
		length++;

	// Write length
	WriteUnsigned<unsigned long long>(length, 0U, t_arg1 - 1);

	// Write string
	WriteBlock(length * sizeof(t_arg0) * 8, reinterpret_cast<unsigned char const *>(&str));
}

template<typename t_arg0, int t_arg1>
_inline void Blam::BitStream::WriteStringFixed(t_arg0 const (&str)[t_arg1])
{
	mangled_prefix_assert("??$WriteStringFixed@");

	WriteBlock((t_arg1 - 1) * sizeof(t_arg0) * 8, reinterpret_cast<unsigned char const *>(&str));
}
namespace Blam
{
	inline void BitStream::WriteBool(bool b) // 0x107F00F0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?WriteBool@BitStream@Blam@@QAEX_N@Z");

		WriteUnsigned(b, 1);
	}

	inline __int32 BitStream::GetAvailableBits() const // 0x1092A1C0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?GetAvailableBits@BitStream@Blam@@ABEHXZ");

		return 64 - m_accumulatorBitsUsed;
	}

	inline bool BitStream::BitsAvailable(__int32 bits) const // 0x10929FA0
	{
		mangled_x86(MANGLED_KNOWN_GOOD, "?BitsAvailable@BitStream@Blam@@ABE_NH@Z");

		return bits <= GetAvailableBits();
	}
}

/* ---------- private code */

#endif // __BLAM_BITSTREAM_HPP__
