// Fill out your copyright notice in the Description page of Project Settings.


#include "BitTestActor.h"

#include "BitFunctions.h"

// Sets default values
ABitTestActor::ABitTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABitTestActor::PrintBit(int attribute)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *UBitFunctions::GetBitSting(attribute, 0));
}

void ABitTestActor::PrintBit(int attribute, int width)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *UBitFunctions::GetBitSting(attribute, width));
}

void ABitTestActor::Print(FString str)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
}

// Called when the game starts or when spawned
void ABitTestActor::BeginPlay()
{
	Super::BeginPlay();
	int MAGIC = 1 << 4; //0001 0000
	int INTEL = 1 << 3; //0000 1000
	int CHAR  = 1 << 2; //0000 0100
	int FLY   = 1 << 1; //0000 0010
	int INV   = 1;      //0000 0001

	Print("setting");
	int attribute = 0;
	PrintBit(attribute); //0000 0000
	attribute = UBitFunctions::SetBitflag(INV);
	PrintBit(attribute); //0000 0001

	Print("adding");
	attribute = UBitFunctions::AddBitflag(attribute, FLY);
	PrintBit(attribute); //0000 0011
	attribute = UBitFunctions::AddBitflag(attribute, CHAR);
	PrintBit(attribute); //0000 0111

	Print("checking on");
	int has = UBitFunctions::CheckBitmaskIntersect(attribute, FLY);
	PrintBit(has); //0000 0001
	has = UBitFunctions::CheckBitmaskIntersect(attribute, MAGIC);
	PrintBit(has); //0000 0000
	has = UBitFunctions::CheckBitmaskIntersect(attribute, MAGIC | FLY);
	PrintBit(has); //0000 0001
	has = UBitFunctions::CheckBitmaskIntersect(attribute, CHAR | FLY);
	PrintBit(has); //0000 0001
	
	Print("checking and equal");
	has = UBitFunctions::CheckBitmaskHas(attribute, FLY);
	PrintBit(has); //0000 0001
	has = UBitFunctions::CheckBitmaskHas(attribute, MAGIC);
	PrintBit(has); //0000 0000
	has = UBitFunctions::CheckBitmaskHas(attribute, MAGIC | FLY);
	PrintBit(has); //0000 0000
	has = UBitFunctions::CheckBitmaskHas(attribute, CHAR | FLY);
	PrintBit(has); //0000 0001
	
	Print("removing");
	attribute = UBitFunctions::RemoveBitFlag(attribute, FLY);
	PrintBit(attribute); //0000 0101
	attribute = UBitFunctions::RemoveBitFlag(attribute, CHAR);
	PrintBit(attribute); //0000 0001

	Print("toggling");
	attribute = UBitFunctions::ToggleBitFlag(attribute, MAGIC);
	PrintBit(attribute); //0001 0001
	attribute = UBitFunctions::ToggleBitFlag(attribute, MAGIC);
	PrintBit(attribute); //0000 0001

	Print("setting clearing all");
	attribute = UBitFunctions::SetAllFlags();
	PrintBit(attribute); //1111 1111
	attribute = UBitFunctions::ClearAllFrags();
	PrintBit(attribute); //0000 0000
	
	Print("packing");
	attribute = UBitFunctions::PackData(attribute, 24, INV);
	PrintBit(attribute);
	attribute = UBitFunctions::PackData(attribute, 16, INV);
	PrintBit(attribute);
	attribute = UBitFunctions::PackData(attribute, 8, INV);
	PrintBit(attribute);
	attribute = UBitFunctions::PackData(attribute, 0, INV);
	PrintBit(attribute);

	Print("unpacking");
	int packed = attribute;
	attribute = UBitFunctions::UnPackData(packed, 24, INV);
	PrintBit(attribute);
	attribute = UBitFunctions::UnPackData(packed, 16, INV);
	PrintBit(attribute);
	attribute = UBitFunctions::UnPackData(packed, 8, INV);
	PrintBit(attribute);
	attribute = UBitFunctions::UnPackData(packed, 0, INV);
	PrintBit(attribute);

	Print("bitboard");
	int bitboard = 0;
	bitboard = UBitFunctions::BbSetCellState(bitboard, UBitFunctions::BbGetIndex(0, 0, 8));
	PrintBit(bitboard, 8);
	bitboard = UBitFunctions::BbSetCellState(bitboard, UBitFunctions::BbGetIndex(1, 1, 8));
	PrintBit(bitboard, 8);

	bool bit = UBitFunctions::BbGetCellState(bitboard, UBitFunctions::BbGetIndex(0, 0, 8));
	PrintBit(bit); //0000 0001
	bit = UBitFunctions::BbGetCellState(bitboard, UBitFunctions::BbGetIndex(2, 2, 8));
	PrintBit(bit); //0000 0000
	int count = UBitFunctions::BbGetCellCount(bitboard);
	PrintBit(count); //0000 0010
	count = UBitFunctions::BbGetEmptyCellCount(bitboard);
	PrintBit(count); //0000 0010

	
}


