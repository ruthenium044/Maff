// Fill out your copyright notice in the Description page of Project Settings.


#include "BitFunctions.h"

FString UBitFunctions::GetBitSting(BitType value, size_t width)
{
	FString str = "";
	for (int i = sizeof(value) * 8 - 1; i >= 0; --i)
	{
		BitType mask = 1 << i;
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

int UBitFunctions::SetBitflag(BitType value)
{
	return value;
}

int UBitFunctions::AddBitflag(BitType flag, BitType value)
{
	flag |= value;
	return flag;
}

int UBitFunctions::RemoveBitFlag(BitType flag, BitType value)
{
	flag &= ~value;
	return flag;
}

int UBitFunctions::ToggleBitFlag(BitType flag, BitType value)
{
	flag ^= value;
	return flag;
}

int UBitFunctions::ClearAllFrags()
{
	return 0;
}

int UBitFunctions::SetAllFlags()
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

int UBitFunctions::PackData(BitType packed, size_t position, BitType data)
{
	packed |= (data << position);
	return packed;
}

int UBitFunctions::UnPackData(BitType packed, size_t position, BitType data)
{
	int mask = data << position;
	return (packed & mask) >> position;
}

int UBitFunctions::GetIndex(size_t x, size_t y, size_t w)
{
	return x * w + y;
}

int UBitFunctions::GetVelueMask(size_t index)
{
	return 1L << index;
}

int UBitFunctions::SetCellState(BitType board, size_t index)
{
	BitType newBit = GetVelueMask(index);
	return AddBitflag(board, newBit);
}

bool UBitFunctions::GetCellState(BitType board, size_t index)
{
	BitType mask = GetVelueMask(index);
	return CheckBitmaskIntersect(board, mask);
}

size_t UBitFunctions::GetCellCount(BitType board)
{
	size_t count = 0;
	while(board != 0)
	{
		board &= board - 1;
		count++;
	}
	return count;
}

size_t UBitFunctions::GetEmptyCellCount(BitType board)
{
	return GetBitTypeSize(board) - GetCellCount(board);
}
