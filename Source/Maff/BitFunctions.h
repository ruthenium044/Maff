// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BitFunctions.generated.h"

typedef int64 BitType;

UCLASS()
class MAFF_API UBitFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	//todo doesn't work with longer arrays of bits and should
	//actually work with it - Requires an underlying "true" type
	//todo make it all UFUNCTION
	
public:
	static FString GetBitSting(BitType value, int64 width);
	static int64 GetBitTypeSize(BitType value);
	
    static BitType SetBitflag(BitType value);
	static BitType AddBitflag(BitType flag, BitType value);
	static BitType RemoveBitFlag(BitType flag, BitType value);
	static BitType ToggleBitFlag(BitType flag, BitType value);
	static BitType ClearAllFrags();
	static BitType SetAllFlags();	
	
	static bool CheckBitmaskIntersect(BitType flag, BitType mask);
	static bool CheckBitmaskHas(BitType flag, BitType mask);
	static BitType PackData(BitType packed, int64 position, BitType data);
	static BitType UnPackData(BitType packed, int64 position, BitType data);
	
	static BitType BbGetIndex(int64 x, int64 y, int64 w);
	static BitType BbGetValueMask(int64 index);
	static BitType BbSetCellState(BitType board, int64 index);
	static BitType BbRemoveCellState(BitType board, int64 index);
	static BitType BbSwapCells(BitType board, int64 index1, int64 index2);
	static bool BbGetCellState(BitType board, int64 index);
	static int64 BbGetCellCount(BitType board);
	static int64 BbGetEmptyCellCount(BitType board);

	static BitType BitAdd(BitType a, BitType b);
	static BitType BitSubstract(BitType a, BitType b);
	static BitType BitMultiply(BitType a, BitType b);
	static BitType BitDivide(BitType a, BitType b);

	static void BitSwap(BitType& a, BitType& b);
	static bool BitCompareSign(BitType a, BitType b);
	static BitType BitMin(BitType a, BitType b);
	static BitType BitMax(BitType a, BitType b);
};
