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

void ABitboardStatic::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction(TEXT("MouseLeftClicked"),IE_Pressed, this, &ABitboardStatic::HandleLMB);
}

void ABitboardStatic::HandleLMB(FKey key)
{
	SpawnTree(0,0,4);
}

void ABitboardStatic::SpawnTile(TArray<TSubclassOf<ABitTile>>& bitBPs,
                                TArray<uint64>& bitboard, TArray<ABitTile*>& tileActors, int x, int y, int rand)
{
	FVector pos(x * tileSizeX - offsetX, y * tileSizeY - offsetY, 0);
	pos += GetActorLocation();
			
	bitboard[rand] = UBitFunctions::BbSetCellState
		(bitboard[rand], UBitFunctions::BbGetIndex(x, y, tilesX));
	tileActors[UBitFunctions::BbGetIndex(x, y, tilesX)] =
		GetWorld()->SpawnActor<ABitTile>(bitBPs[rand], pos, GetActorRotation());
}

void ABitboardStatic::SpawnTree(int x, int y, int index)
{
	SpawnTile(bitObjsBPs, objBitboards, objects, x, y, index);
}

void ABitboardStatic::SpawnAllTiles()
{
	for (int x = 0; x < tilesX; ++x)
	{
		for (int y = 0; y < tilesY; ++y)
		{
			int rand = FMath::RandRange(0, bitTilesBPs.Num() - 1);
			SpawnTile(bitTilesBPs, tileBitboards, tiles, x, y, rand);
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
				SpawnTree(x, y, 0);
			}
			if (UBitFunctions::BbGetCellState(tileBitboards[4],
			UBitFunctions::BbGetIndex(x, y, tilesX)))
			{
				SpawnTree(x, y, 4);
			}
			if (UBitFunctions::BbGetCellState(tileBitboards[2] | tileBitboards[3],
			UBitFunctions::BbGetIndex(x, y, tilesX)))
			{
				SpawnTree(x, y, 5);
			}
		}
	}
}

FIntVector ABitboardStatic::WorldToGrid(FVector pos)
{
	FIntVector coord = {FMath::RoundToInt((pos.X + offsetX) / tileSizeX),
						FMath::RoundToInt((pos.Y + offsetY) / tileSizeY), 0};
	return coord;
}

FVector ABitboardStatic::GridToWorld(FIntVector coord)
{
	int index = UBitFunctions::BbGetIndex(coord.X, coord.Y, tilesX);
	bool checkBounds = coord.X >= 0 && coord.X < tilesX && coord.Y >= 0 && coord.Y < tilesY;
	if (checkBounds && index < tilesX * tilesY && index >= 0)
	{
		return tiles[index]->GetActorLocation();
	}
	return FVector::ZeroVector;
}

// Called when the game starts or when spawned
void ABitboardStatic::BeginPlay()
{
	Super::BeginPlay();
	controller = GetWorld()->GetFirstPlayerController();
	controller->SetShowMouseCursor(true);
	
	for(auto& tile : bitTilesBPs)
	{
		tileBitboards.Add(UBitFunctions::ClearAllFrags());
	}
	for(auto& tile : bitObjsBPs)
	{
		objBitboards.Add(UBitFunctions::SetAllFlags());
	}
	tiles.Init(nullptr, tilesX * tilesY);
	objects.Init(nullptr, tilesX * tilesY);
	
	SpawnAllTiles();
	//SpawnAllTrees();
	SpawnTree(0, 0, 0);
}

// Called every frame
void ABitboardStatic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//controller->GetMousePosition(mousePos.X, mousePos.Y);

	FVector outpos;
	FVector outdir;
	if(!controller->DeprojectMousePositionToWorld(outpos, outdir))
	{
		return;
	}
	FPlane plane{GetActorLocation(), GetActorUpVector()};
	FVector intersectPoint = FMath::RayPlaneIntersection(outpos, outdir, plane);

	FIntVector gridPos = WorldToGrid(intersectPoint);
	FVector worldPos = GridToWorld(gridPos);
	
	if (worldPos == FVector::ZeroVector)
	{
		objects[0]->SetActorLocation(intersectPoint);
	}
	else
	{
		objects[0]->SetActorLocation(worldPos);
	}
}


