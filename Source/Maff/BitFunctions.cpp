// Fill out your copyright notice in the Description page of Project Settings.


#include "BitFunctions.h"

int UBitFunctions::SetBitflag(int value)
{
	return value;
}

int UBitFunctions::AddBitflag(int flag, int value)
{
	flag |= value;
	return flag;
}

int UBitFunctions::RemoveBitFlag(int flag, int value)
{
	flag &= ~value;
	return flag;
}

bool UBitFunctions::CheckBitmaskOr(int flag, int mask)
{
	return (flag & mask) != 0;
}

bool UBitFunctions::CheckBitmaskAnd(int flag, int mask)
{
	return (flag & mask) != mask;
}
