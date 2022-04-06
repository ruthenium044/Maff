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
	void SpawnTile(TArray<TSubclassOf<ABitTile>>& bitBPs ,TArray<uint64>& bitboard, int x, int y, int rand);
	void SpawnAllTiles();
	void SpawnAllTrees();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	float tileSizeX = 100;
	float tileSizeY = 100;
	
	float offsetX = tilesX * tileSizeX / 2;
	float offsetY = tilesY * tileSizeY / 2;
	
	static constexpr int tilesX = 8;
	static constexpr int tilesY = 8;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABitTile>> bitTilesBPs;
	TArray<uint64> tileBitboards;
	ABitTile* tiles[tilesX][tilesY];
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABitTile>> bitObjsBPs;
	TArray<uint64> objBitboards;
	ABitTile* objects[tilesX][tilesY];
	
};
