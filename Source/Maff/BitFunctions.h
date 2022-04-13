// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BitFunctions.generated.h"

typedef uint64 BitType;

UCLASS()
class MAFF_API UBitFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	//todo doesn't work with longer arrays of bits and should
	//actually work with it - Requires an underlying "true" type
	//todo make it all UFUNCTION 
	
public:
	static FString GetBitSting(BitType value, size_t width);
	static size_t GetBitTypeSize(BitType value);
	
    static BitType SetBitflag(BitType value);
	static BitType AddBitflag(BitType flag, BitType value);
	static BitType RemoveBitFlag(BitType flag, BitType value);
	static BitType ToggleBitFlag(BitType flag, BitType value);
	static BitType ClearAllFrags();
	static BitType SetAllFlags();
	
	static bool CheckBitmaskIntersect(BitType flag, BitType mask);
	static bool CheckBitmaskHas(BitType flag, BitType mask);
	static BitType PackData(BitType packed, size_t position, BitType data);
	static BitType UnPackData(BitType packed, size_t position, BitType data);
	
	static BitType BbGetIndex(size_t x, size_t y, size_t w);
	static BitType BbGetValueMask(size_t index);
	static BitType BbSetCellState(BitType board, size_t index);
	static BitType BbRemoveCellState(BitType board, size_t index);
	static BitType BbSwapCells(BitType board, size_t index1, size_t index2);
	static bool BbGetCellState(BitType board, size_t index);
	static size_t BbGetCellCount(BitType board);
	static size_t BbGetEmptyCellCount(BitType board);

	static BitType BitAdd(BitType a, BitType b);
	static BitType BitSubstract(BitType a, BitType b);
	static BitType BitMultiply(BitType a, BitType b);
	static BitType BitDivide(BitType a, BitType b);

	static void BitSwap(BitType& a, BitType& b);
	static bool BitCompareSign(BitType a, BitType b);
	static BitType BitMin(BitType a, BitType b);
	static BitType BitMax(BitType a, BitType b);
};
