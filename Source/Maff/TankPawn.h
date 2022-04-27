// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

UCLASS()
class MAFF_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	ATankPawn();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleVerticalAxis();
	void HandleHorizontalAxis();

};
