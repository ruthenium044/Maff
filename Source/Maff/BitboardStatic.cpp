// Fill out your copyright notice in the Description page of Project Settings.

#include "BitboardStatic.h"
#include "BitFunctions.h"
#include "BitTile.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ABitboardStatic::ABitboardStatic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABitboardStatic::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction(TEXT("MouseLeftClicked"),IE_Pressed, this, &ABitboardStatic::HandleLMBPressed);
	PlayerInputComponent->BindAction(TEXT("MouseLeftClicked"),IE_Released, this, &ABitboardStatic::HandleLMBReleased);
	PlayerInputComponent->BindAction(TEXT("MouseRightClicked"),IE_Pressed, this, &ABitboardStatic::HandleRMBPressed);
	PlayerInputComponent->BindAction(TEXT("MouseWheelUp"),IE_Pressed, this, &ABitboardStatic::HandleWheelUp);
	PlayerInputComponent->BindAction(TEXT("MouseWheelDown"),IE_Pressed, this, &ABitboardStatic::HandleWheelDown);
}

void ABitboardStatic::HandleLMBPressed(FKey key)
{
	if (isMouseOnGrid)
	{
		for (int i = 0; i < selectionTiles.Num(); ++i)
		{
			int index = UBitFunctions::BbGetIndex(mousePosGrid.X, mousePosGrid.Y, gridSize.X);
			if (UBitFunctions::BbGetCellState(objBitboards[i], index))
			{
				PickUpTile(i, index);
			}
			else
			{
				SpawnTree(mousePosGrid.X, mousePosGrid.Y,tileToPlace);
			}
		}
		
	}
}

void ABitboardStatic::HandleLMBReleased(FKey key)
{
	if (isMouseOnGrid && pickedUpTile)
	{
		int newIndex = UBitFunctions::BbGetIndex(mousePosGrid.X, mousePosGrid.Y, gridSize.X);
		if(!GetCellState(newIndex))
		{
			ChangeTilesPosition(newIndex);
			//AdjustAllPositions(mousePosGrid.X, mousePosGrid.Y);
		}
		else
		{
			objects[pickedUpTileType][pickedUpTileIndex]->SetActorLocation(pickedUpPos);
			
		}
		pickedUpTile = nullptr;
	}
}

void ABitboardStatic::HandleRMBPressed(FKey key)
{
	bool once = true;
	if (isMouseOnGrid)
	{
		for (int i = 0; i < selectionTiles.Num(); ++i)
		{
			if(once && RemoveTree(mousePosGrid.X, mousePosGrid.Y,i))
			{
				once = false;
			}
			else if(!once)
			{
				ResetPosition(mousePosGrid.X, mousePosGrid.Y,i);
			}
		}
	}
}

void ABitboardStatic::HandleWheelUp(FKey key)
{
	DeselectTile();
	tileToPlace--;
	SelectTile();
}

void ABitboardStatic::HandleWheelDown(FKey key)
{
	DeselectTile();
	tileToPlace++;
	SelectTile();
}

bool ABitboardStatic::GetCellState(int newIndex)
{
	for (int i = 0; i < selectionTiles.Num(); ++i)
	{
		if (UBitFunctions::BbGetCellState(objBitboards[i], newIndex))
		{
			return true;
		}
	}
	return false;
}

void ABitboardStatic::PickUpTile(int i, int index)
{
	pickedUpTileType = i;
	pickedUpTileIndex = index;
	pickedUpPos = objects[i][index]->GetActorLocation();
	pickedUpTile = true;
}

void ABitboardStatic::ChangeTilesPosition(int newIndex)
{
	ABitTile* temp = objects[pickedUpTileType][pickedUpTileIndex];
	objects[pickedUpTileType][pickedUpTileIndex] = objects[pickedUpTileType][newIndex];
	objects[pickedUpTileType][newIndex] = temp;
	objBitboards[pickedUpTileType] = UBitFunctions::BbSwapCells(objBitboards[pickedUpTileType],
																pickedUpTileIndex,newIndex);
}

void ABitboardStatic::DeselectTile()
{
	selectionTiles[tileToPlace]->selected = false;
	selectionTiles[tileToPlace]->ResetScale();
}

void ABitboardStatic::SelectTile()
{
	int size = bitObjsBPs.Num();
	tileToPlace = ((tileToPlace % size) + size) % size;
	selectionTiles[tileToPlace]->selected = true;
}

// Spawns
void ABitboardStatic::SpawnTile(TArray<TSubclassOf<ABitTile>>& bitBPs,
                                TArray<uint64>& bitboard, TArray<ABitTile*>& tileActors, int x, int y, int tileType)
{
	bitboard[tileType] = UBitFunctions::BbSetCellState
		(bitboard[tileType], UBitFunctions::BbGetIndex(x, y, gridSize.X));
	tileActors[UBitFunctions::BbGetIndex(x, y, gridSize.X)] =
		GetWorld()->SpawnActor<ABitTile>(bitBPs[tileType], GetTileCenter(x, y), GetActorRotation());
}

void ABitboardStatic::RemoveTile(TArray<uint64>& bitboard, TArray<ABitTile*>& tileActors, int x, int y, int tileType) const
{
	bitboard[tileType] = UBitFunctions::BbRemoveCellState
		(bitboard[tileType], UBitFunctions::BbGetIndex(x, y, gridSize.X));
	tileActors[UBitFunctions::BbGetIndex(x, y, gridSize.X)]->Destroy();
	//todo pool it damn it
}

bool ABitboardStatic::RemoveTree(int x, int y, int tileType)
{
	if (UBitFunctions::BbGetCellState(objBitboards[tileType], UBitFunctions::BbGetIndex(x, y, gridSize.X)))
	{
		RemoveTile(objBitboards, objects[tileType], x, y, tileType);
		return true;
	}
	return false;
}

void ABitboardStatic::SpawnTree(int x, int y, int tileType)
{
	if (CheckIfCanSpawn(x, y, tileType))
	{
		SpawnTile(bitObjsBPs, objBitboards, objects[tileType], x, y, tileType);
		AdjustPosition(x, y, tileType);
	}
}

void ABitboardStatic::SpawnAllTiles()
{
	for (int x = 0; x < gridSize.X; ++x)
	{
		for (int y = 0; y < gridSize.Y; ++y)
		{
			int rand = FMath::RandRange(0, bitTilesBPs.Num() - 1);
			SpawnTile(bitTilesBPs, tileBitboards, tiles, x, y, rand);
		}
	}
}

bool ABitboardStatic::CheckIfCanSpawn(int x, int y, int treeType)
{
	if (UBitFunctions::BbGetCellState(objBitboards[treeType], UBitFunctions::BbGetIndex(x, y, gridSize.X)) ||
		UBitFunctions::BbGetCellState(tileBitboards[6], UBitFunctions::BbGetIndex(x, y, gridSize.X)))
	{
		return false;
	}
	switch (treeType)
	{
	case 0: //green
		return UBitFunctions::BbGetCellState(tileBitboards[0], UBitFunctions::BbGetIndex(x, y, gridSize.X));
	case 1: //orange
		return UBitFunctions::BbGetCellState(tileBitboards[1], UBitFunctions::BbGetIndex(x, y, gridSize.X));
	case 2: //purple
		return UBitFunctions::BbGetCellState(tileBitboards[2], UBitFunctions::BbGetIndex(x, y, gridSize.X));
	case 3: //red
		return UBitFunctions::BbGetCellState(tileBitboards[3], UBitFunctions::BbGetIndex(x, y, gridSize.X));
	case 4: //pink
		return UBitFunctions::BbGetCellState(tileBitboards[2] | tileBitboards[3], UBitFunctions::BbGetIndex(x, y, gridSize.X));
	case 5: //blue
		return UBitFunctions::BbGetCellState(tileBitboards[4] | tileBitboards[5], UBitFunctions::BbGetIndex(x, y, gridSize.X));
	case 6: //white
		return UBitFunctions::BbGetCellState(tileBitboards[5], UBitFunctions::BbGetIndex(x, y, gridSize.X));
	default:
		return false;
	}
}

void ABitboardStatic::AdjustPosition(int x, int y, int treeType)
{
	int index = UBitFunctions::BbGetIndex(x, y, gridSize.X);
	for (int i = 0; i < selectionTiles.Num(); ++i)
	{
		for (int j = 0; j < selectionTiles.Num(); ++j)
		{
			if (treeType == i && UBitFunctions::BbGetCellState(objBitboards[j], index))
			{
				FVector location = objects[i][index]->GetActorLocation();
				objects[i][index]->SetActorLocation(location + treeOffset);
				location = objects[j][index]->GetActorLocation();
				objects[j][index]->SetActorLocation(location - treeOffset);
			}
		}
	}
}

void ABitboardStatic::AdjustAllPositions(int x, int y)
{
	for (int i = 0; i < selectionTiles.Num(); ++i)
	{
		AdjustPosition(x, y, i);
	}
}

void ABitboardStatic::ResetPosition(int x, int y, int treeType)
{
	int index = UBitFunctions::BbGetIndex(x, y, gridSize.X);
	if (UBitFunctions::BbGetCellState(objBitboards[treeType], index))
	{
		objects[treeType][index]->SetActorLocation(GetTileCenter(x, y));
	}
}

// Grids
FVector ABitboardStatic::GetTileCenter(int x, int y) const
{
	FVector pos(x * tileSize.X - offsetX, y * tileSize.Y - offsetY, 0);
	return pos += GetActorLocation();
}

FIntVector ABitboardStatic::WorldToGrid(FVector pos) const
{
	FIntVector coord = {FMath::RoundToInt((pos.X + offsetX) / tileSize.X),
						FMath::RoundToInt((pos.Y + offsetY) / tileSize.Y), 0};
	return coord;
}

FVector ABitboardStatic::GridToWorld(FIntVector coord)
{
	int index = UBitFunctions::BbGetIndex(coord.X, coord.Y, gridSize.X);
	bool checkBounds = coord.X >= 0 && coord.X < gridSize.X && coord.Y >= 0 && coord.Y < gridSize.Y;
	if (checkBounds && index < gridSize.X * gridSize.Y && index >= 0)
	{
		return tiles[index]->GetActorLocation();
	}
	return FVector::ZeroVector;
}

void ABitboardStatic::InitializeArrays()
{
	for(auto& tile : bitTilesBPs)
	{
		tileBitboards.Add(UBitFunctions::ClearAllFrags());
	}
	tiles.Init(nullptr, gridSize.X * gridSize.Y);
	
	for(int i = 0; i < bitObjsBPs.Num(); i++)
	{
		objBitboards.Add(UBitFunctions::ClearAllFrags());
		TArray<ABitTile*> temp;
		temp.Init(nullptr, gridSize.X * gridSize.Y);
		objects.Add(temp);
	}
}

// Called when the game starts or when spawned
void ABitboardStatic::BeginPlay()
{
	Super::BeginPlay();
	controller = GetWorld()->GetFirstPlayerController();
	controller->SetShowMouseCursor(true);
	
	InitializeArrays();
	SpawnAllTiles();
	SelectTile();
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
	mousePosGrid = gridPos;
	FVector worldPos = GridToWorld(gridPos);
	
	if (worldPos == FVector::ZeroVector)
	{
		if (pickedUpTile)
		{
			objects[pickedUpTileType][pickedUpTileIndex]->SetActorLocation(intersectPoint);
		}
		isMouseOnGrid = false;
	}
	else
	{
		if (pickedUpTile)
		{
			objects[pickedUpTileType][pickedUpTileIndex]->SetActorLocation(worldPos);
		}
		isMouseOnGrid = true;
	}
}
