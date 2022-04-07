// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Public/Containers/Array.h"
#include "BitTile.h"

#include "BitboardStatic.generated.h"

UCLASS()
class MAFF_API ABitboardStatic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABitboardStatic();
	void SpawnTile(TArray<TSubclassOf<ABitTile>>& bitBPs, TArray<uint64>& bitboard,
		TArray<ABitTile*>& tileActors, int x, int y, int index);
	void SpawnAllTiles();
	void SpawnTree(int x, int y, int index);
	void SpawnAllTrees();

	UPROPERTY(EditAnywhere)
	float tileSizeX = 100;
	UPROPERTY(EditAnywhere)
	float tileSizeY = 100;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	APlayerController* controller;
	
	int tilesX = 8;
	int tilesY = 8;
	float offsetX = tilesX * tileSizeX / 2;
	float offsetY = tilesY * tileSizeY / 2;

	TArray<uint64> tileBitboards;
	TArray<ABitTile*> tiles;
	TArray<uint64> objBitboards;
	TArray<ABitTile*> objects;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABitTile>> bitTilesBPs;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABitTile>> bitObjsBPs;
	
};
