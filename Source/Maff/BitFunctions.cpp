// Fill out your copyright notice in the Description page of Project Settings.


#include "BitFunctions.h"

FString UBitFunctions::GetBitSting(BitType value, size_t width)
{
	FString str = "";
	for (int i = sizeof(value) * 8 - 1; i >= 0; --i)
	{
		BitType mask = BbGetValueMask(i);
		BitType bit = CheckBitmaskIntersect(value, mask);
		str.AppendInt(bit);
		if (i % 4 == 0)
		{
			str.Append(" ");
		}
		if (width != 0 && i % width == 0)
		{
			str.Append("\n");
		}
	}
	return str;
}

size_t UBitFunctions::GetBitTypeSize(BitType value)
{
	return sizeof(value) * 8;
}

BitType UBitFunctions::SetBitflag(BitType value)
{
	return value;
}

BitType UBitFunctions::AddBitflag(BitType flag, BitType value)
{
	flag |= value;
	return flag;
}

BitType UBitFunctions::RemoveBitFlag(BitType flag, BitType value)
{
	flag &= ~value;
	return flag;
}

BitType UBitFunctions::ToggleBitFlag(BitType flag, BitType value)
{
	flag ^= value;
	return flag;
}

BitType UBitFunctions::ClearAllFrags()
{
	return 0;
}

BitType UBitFunctions::SetAllFlags()
{
	return ~0;
}

bool UBitFunctions::CheckBitmaskIntersect(BitType flag, BitType mask)
{
	return (flag & mask) != 0;
}

bool UBitFunctions::CheckBitmaskHas(BitType flag, BitType mask)
{
	return (flag & mask) == mask;
}

BitType UBitFunctions::PackData(BitType packed, size_t position, BitType data)
{
	packed |= (data << position);
	return packed;
}

BitType UBitFunctions::UnPackData(BitType packed, size_t position, BitType data)
{
	int mask = data << position;
	return (packed & mask) >> position;
}

BitType UBitFunctions::BbGetIndex(size_t x, size_t y, size_t w)
{
	return x * w + y;
}

BitType UBitFunctions::BbGetValueMask(size_t index)
{
	return static_cast<BitType>(1) << index;
}

BitType UBitFunctions::BbSetCellState(BitType board, size_t index)
{
	BitType newBit = BbGetValueMask(index);
	return AddBitflag(board, newBit);
}

bool UBitFunctions::BbGetCellState(BitType board, size_t index)
{
	BitType mask = BbGetValueMask(index);
	return CheckBitmaskIntersect(board, mask);
}

size_t UBitFunctions::BbGetCellCount(BitType board)
{
	size_t count = 0;
	while(board != 0)
	{
		board &= board - 1;
		count++;
	}
	return count;
}

size_t UBitFunctions::BbGetEmptyCellCount(BitType board)
{
	return GetBitTypeSize(board) - BbGetCellCount(board);
}
