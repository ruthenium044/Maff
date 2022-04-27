
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Maffs.generated.h"

/**
 * 
 */
UCLASS()
class MAFF_API UMaffs : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Maff")
	static int64 Square(int64 value);
	UFUNCTION(BlueprintCallable, Category = "Maff")
	static int64 SquareRoot(int64 value);

	UFUNCTION(BlueprintCallable, Category = "Maff")
	static int64 Magnitude(FVector vector);
	UFUNCTION(BlueprintCallable, Category = "Maff")
	static int64 Distance(FVector vector1, FVector vector2);
	UFUNCTION(BlueprintCallable, Category = "Maff")
	static int64 Dot(FVector vector1, FVector vector2);
	UFUNCTION(BlueprintCallable, Category = "Maff")
	static FVector Normalize(FVector vector);
	
	UFUNCTION(BlueprintCallable, Category = "Maff")
	static int64 AngleRad(FVector vector1, FVector vector2);
	UFUNCTION(BlueprintCallable, Category = "Maff")
	static int64 RadToDeg(int64 value);
	UFUNCTION(BlueprintCallable, Category = "Maff")
	static int64 DegToRad(int64 value);


	UFUNCTION(BlueprintCallable, Category = "Maff")
	static FVector RotateX(FVector vector, float angle, bool clockwise);
	UFUNCTION(BlueprintCallable, Category = "Maff")
	static FVector RotateY(FVector vector, float angle, bool clockwise);
	UFUNCTION(BlueprintCallable, Category = "Maff")
	static FVector RotateZ(FVector vector, float angle, bool clockwise);
	
};
