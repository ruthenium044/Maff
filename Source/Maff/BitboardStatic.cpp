// Fill out your copyright notice in the Description page of Project Settings.


#include "BitboardStatic.h"

#include "BitFunctions.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ABitboardStatic::ABitboardStatic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABitboardStatic::SpawnTile(TArray<TSubclassOf<ABitTile>>& bitBPs ,TArray<uint64>& bitboard, int x, int y, int rand)
{
	FVector pos(x * tileSizeX - offsetX, y * tileSizeY - offsetY, 0);
	pos += GetActorLocation();
			
	bitboard[rand] = UBitFunctions::BbSetCellState
		(bitboard[rand], UBitFunctions::BbGetIndex(x, y, tilesX));
	GetWorld()->SpawnActor<AActor>(bitBPs[rand], pos, GetActorRotation());
}

void ABitboardStatic::SpawnAllTiles()
{
	for (int x = 0; x < tilesX; ++x)
	{
		for (int y = 0; y < tilesY; ++y)
		{
			int rand = FMath::RandRange(0, bitTilesBPs.Num() - 1);
			SpawnTile(bitTilesBPs, tileBitboards,x, y, rand);
		}
	}
}

void ABitboardStatic::SpawnAllTrees()
{
	for (int x = 0; x < tilesX; ++x)
	{
		for (int y = 0; y < tilesY; ++y)
		{
			if (UBitFunctions::BbGetCellState(tileBitboards[0],
			                                  UBitFunctions::BbGetIndex(x, y, tilesX)))
			{
				SpawnTile(bitObjsBPs, objBitboards,x, y, 0);
			}
			
			if (UBitFunctions::BbGetCellState(tileBitboards[4],
													  UBitFunctions::BbGetIndex(x, y, tilesX)))
			{
				SpawnTile(bitObjsBPs, objBitboards,x, y, 4);
			}
			
			if (UBitFunctions::BbGetCellState(tileBitboards[2] | tileBitboards[3],
			                                  UBitFunctions::BbGetIndex(x, y, tilesX)))
			{
				SpawnTile(bitObjsBPs, objBitboards,x, y, 5);
			}
		}
	}
}

// Called when the game starts or when spawned
void ABitboardStatic::BeginPlay()
{
	Super::BeginPlay();

	for(auto& tile : bitTilesBPs)
	{
		tileBitboards.Add(UBitFunctions::ClearAllFrags());
	}
	for(auto& tile : bitObjsBPs)
	{
		objBitboards.Add(UBitFunctions::SetBitflag(187649984473770));
	}
	
	SpawnAllTiles();
	SpawnAllTrees();
}

// Called every frame
void ABitboardStatic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


