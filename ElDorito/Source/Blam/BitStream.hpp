#ifndef __BLAM_BITSTREAM_HPP__
#define __BLAM_BITSTREAM_HPP__
#pragma once

/* ---------- headers */

#include "hades/hades.h"

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
		template<typename t_arg0>
		t_arg0 Read(__int32 bits);
		unsigned long Read(long minValue, long maxValue);
		template<typename t_arg0, typename t_arg1>
		bool ReadString(t_arg1);
		template<typename t_arg0, typename t_arg1>
		void ReadStringFixed(t_arg1);
		template<typename t_arg0>
		t_arg0 ReadUnsigned(__int32 bits);
		template<typename t_arg0>
		t_arg0 ReadUnsigned(t_arg0 minValue, t_arg0 maxValue);
		template<typename t_arg0>
		void Write(t_arg0 val, __int32 bits);
		template<typename t_arg0>
		void Write(t_arg0 val, t_arg0 minValue, t_arg0 maxValue);
		template<typename t_arg0, typename t_arg1>
		void WriteString(t_arg1);
		template<typename t_arg0, typename t_arg1>
		void WriteStringFixed(t_arg1);
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
	_extern __int32 _sub_10ACE5C0(Blam::BitStream const *const);
	_inline __int32 BitStream::SizeBytes() const // 0x10ACE5C0
	{
		mangled_x86(MANGLED_TODO, "?SizeBytes@BitStream@Blam@@QBEHXZ");
		// Blam::BitStream const *const this;
		todo("implement");
		__int32 __result = _sub_10ACE5C0((Blam::BitStream const *)this);
		return __result;
	}

	_extern __int32 _sub_10ACE5F0(Blam::BitStream const *const);
	_inline __int32 BitStream::StreamBitPosition() const // 0x10ACE5F0
	{
		mangled_x86(MANGLED_TODO, "?StreamBitPosition@BitStream@Blam@@QBEHXZ");
		// Blam::BitStream const *const this;
		todo("implement");
		__int32 __result = _sub_10ACE5F0((Blam::BitStream const *)this);
		return __result;
	}

	_extern bool _sub_107F00A0(Blam::BitStream *const);
	_inline bool BitStream::ReadBool() // 0x107F00A0
	{
		mangled_x86(MANGLED_TODO, "?ReadBool@BitStream@Blam@@QAE_NXZ");
		// Blam::BitStream *const this;
		todo("implement");
		bool __result = _sub_107F00A0(this);
		return __result;
	}
}

template<typename t_arg0>
_inline t_arg0 Blam::BitStream::ReadUnsigned(__int32 bits)
{
	mangled_prefix_assert("??$ReadUnsigned@");
	todo("implement");
	return todo_result<t_arg0>();
}

template<typename t_arg0>
_inline t_arg0 Blam::BitStream::ReadUnsigned(t_arg0 minValue, t_arg0 maxValue)
{
	mangled_prefix_assert("??$ReadUnsigned@");
	todo("implement");
	return todo_result<t_arg0>();
}

namespace Blam
{
	_extern void _sub_107F00F0(Blam::BitStream *const, bool);
	_inline void BitStream::WriteBool(bool b) // 0x107F00F0
	{
		mangled_x86(MANGLED_TODO, "?WriteBool@BitStream@Blam@@QAEX_N@Z");
		// bool b;
		todo("implement");
		_sub_107F00F0(this, b);
	}

	_extern __int32 _sub_1092A1C0(Blam::BitStream const *const);
	_inline __int32 BitStream::GetAvailableBits() const // 0x1092A1C0
	{
		mangled_x86(MANGLED_TODO, "?GetAvailableBits@BitStream@Blam@@ABEHXZ");
		// Blam::BitStream const *const this;
		todo("implement");
		__int32 __result = _sub_1092A1C0((Blam::BitStream const *)this);
		return __result;
	}

	_extern bool _sub_10929FA0(Blam::BitStream const *const, __int32);
	_inline bool BitStream::BitsAvailable(__int32 bits) const // 0x10929FA0
	{
		mangled_x86(MANGLED_TODO, "?BitsAvailable@BitStream@Blam@@ABE_NH@Z");
		// __int32 bits;
		todo("implement");
		bool __result = _sub_10929FA0((Blam::BitStream const *)this, bits);
		return __result;
	}
}

/* ---------- private code */

#endif // __BLAM_BITSTREAM_HPP__
