// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BitFunctions.generated.h"

UCLASS()
class MAFF_API UBitFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
    int SetBitflag(int value);
	int AddBitflag(int flag, int value);
	int RemoveBitFlag(int flag, int value);

	bool CheckBitmaskOr(int flag, int mask);
	bool CheckBitmaskAnd(int flag, int mask);

	
};
