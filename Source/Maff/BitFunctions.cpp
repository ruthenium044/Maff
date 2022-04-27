// Fill out your copyright notice in the Description page of Project Settings.


#include "BitFunctions.h"

FString UBitFunctions::GetBitSting(BitType value, int64 width)
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

int64 UBitFunctions::GetBitTypeSize(BitType value)
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

BitType UBitFunctions::PackData(BitType packed, int64 position, BitType data)
{
	packed |= (data << position);
	return packed;
}

BitType UBitFunctions::UnPackData(BitType packed, int64 position, BitType data)
{
	int mask = data << position;
	return (packed & mask) >> position;
}

BitType UBitFunctions::BbGetIndex(int64 x, int64 y, int64 w)
{
	return x * w + y;
}

BitType UBitFunctions::BbGetValueMask(int64 index)
{
	return static_cast<BitType>(1) << index;
}

BitType UBitFunctions::BbSetCellState(BitType board, int64 index)
{
	BitType newBit = BbGetValueMask(index);
	return AddBitflag(board, newBit);
}

BitType UBitFunctions::BbRemoveCellState(BitType board, int64 index)
{
	BitType newBit = BbGetValueMask(index);
	return RemoveBitFlag(board, newBit);
}

BitType UBitFunctions::BbSwapCells(BitType board, int64 index1, int64 index2)
{
	if (BbGetCellState(board, index1) && !BbGetCellState(board, index2) ||
		BbGetCellState(board, index2) && !BbGetCellState(board, index1))
	{
		board = BbRemoveCellState(board, index1);
		board = BbSetCellState(board, index2);
	}
	return board;
}

bool UBitFunctions::BbGetCellState(BitType board, int64 index)
{
	BitType mask = BbGetValueMask(index);
	return CheckBitmaskIntersect(board, mask);
}

int64 UBitFunctions::BbGetCellCount(BitType board)
{
	int64 count = 0;
	while(board != 0)
	{
		board &= board - 1;
		count++;
	}
	return count;
}

int64 UBitFunctions::BbGetEmptyCellCount(BitType board)
{
	return GetBitTypeSize(board) - BbGetCellCount(board);
}

BitType UBitFunctions::BitAdd(BitType a, BitType b)
{
	while (b != 0) 
	{ 
		int c = a & b;   
		a = a ^ b;  
		b = c << 1; 
	} 
	return a; 
}

BitType UBitFunctions::BitSubstract(BitType a, BitType b)
{
	while (b != 0) 
	{ 
		int borrow = (~a) & b; 
		a = a ^ b; 
		b = borrow << 1; 
	} 
	return a;
}

BitType UBitFunctions::BitMultiply(BitType a, BitType b)
{
	int answer = 0; 
	int count = 0; 
	while (b != 0) 
	{ 
		if (b % 2 == 1)
		{               
			answer += a << count;
		}
		count++; 
		b /= 2; 
	} 
	return answer;
}

BitType UBitFunctions::BitDivide(BitType a, BitType b)
{
	//todo impliment this
	return 0;
}

void UBitFunctions::BitSwap(BitType& a, BitType& b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}

bool UBitFunctions::BitCompareSign(BitType a, BitType b)
{
	return 0 <= (a ^ b); 
}

BitType UBitFunctions::BitMin(BitType a, BitType b)
{
	return b ^ ((a ^ b) & -((a < b)?1:0));
}

BitType UBitFunctions::BitMax(BitType a, BitType b)
{
	return a ^ ((a ^ b) & -((a < b)?1:0));
}
