// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BitTestActor.generated.h"

UCLASS()
class MAFF_API ABitTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABitTestActor();
	void PrintBit(int attribute);
	void PrintBit(int attribute, int width);
	void Print(FString str);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
