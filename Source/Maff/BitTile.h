// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BitTile.generated.h"

UCLASS()
class MAFF_API ABitTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABitTile();
	bool selected = false;
	bool easeIn = true;
	void ResetScale();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	float t = 0;
	FVector StartSCale{0, 0, 0};
	FVector CurrentScale{0, 0, 0};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere);
	FVector EndOffset{0.5f, 0.5f, 0.1f};
	
	UPROPERTY(EditAnywhere);
	float duration = 0.6;
};
