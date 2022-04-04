// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BitFunctions.generated.h"

typedef int BitType;

UCLASS()
class MAFF_API UBitFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
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

	static BitType GetIndex(size_t x, size_t y, size_t w);
	static BitType GetVelueMask(size_t index);
	static BitType SetCellState(BitType board, size_t index);
	static bool GetCellState(BitType board, size_t index);
	static size_t GetCellCount(BitType board);
	static size_t GetEmptyCellCount(BitType board);
	
};
