// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Public/Containers/Array.h"
#include "BitTile.h"

#include "BitboardStatic.generated.h"

UCLASS()
class MAFF_API ABitboardStatic : public APawn
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ABitboardStatic();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void HandleLMB(FKey key);
	void HandleRMB(FKey key);
	void HandleWheelUp(FKey key);
	void HandleWheelDown(FKey key);
	void DeselectTile();
	void SelectTile();
	
	void SpawnTile(TArray<TSubclassOf<ABitTile>>& bitBPs, TArray<uint64>& bitboard,
		TArray<ABitTile*>& tileActors, int x, int y, int index);
	void RemoveTile(TArray<uint64>& bitboard, TArray<ABitTile*>& tileActors, int x, int y, int index) const;
	void SpawnTree(int x, int y, int tileType);
	bool RemoveTree(int x, int y, int tileType);
	void SpawnAllTiles();
	bool CheckIfCanSpawn(int x, int y, int treeType);
	
	void AdjustPosition(int x, int y, int treeType);
	void ResetPosition(int x, int y, int treeType);

	FVector GetTileCenter(int x, int y) const;
	FIntVector WorldToGrid(FVector pos) const;
	FVector GridToWorld(FIntVector coord);
	void InitializeArrays();

	UPROPERTY(EditAnywhere)
	FVector2D tileSize {100, 100};
private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	APlayerController* controller;
	FIntVector mousePosGrid{0, 0, 0};
	bool isMouseOnGrid = false;
	int tileToPlace = 0;

	FVector2D gridSize{8, 8};
	float offsetX = gridSize.X * tileSize.X / 2 - tileSize.X / 2;
	float offsetY = gridSize.Y * tileSize.Y / 2 - tileSize.Y / 2;

	FVector treeOffset {-20, 20, 0};

	TArray<uint64> tileBitboards;
	TArray<ABitTile*> tiles;
	TArray<uint64> objBitboards;
	TArray<TArray<ABitTile*>> objects;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABitTile>> bitTilesBPs;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABitTile>> bitObjsBPs;
	UPROPERTY(EditInstanceOnly)
	TArray<ABitTile*> selectionTiles;
};

