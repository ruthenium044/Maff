// Fill out your copyright notice in the Description page of Project Settings.


#include "BitTile.h"

#include "Bouncee.h"

// Sets default values
ABitTile::ABitTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABitTile::ResetScale()
{
	SetActorScale3D(StartSCale);
}

// Called when the game starts or when spawned
void ABitTile::BeginPlay()
{
	Super::BeginPlay();
	StartSCale = GetActorScale();
	CurrentScale = StartSCale;
	SetActorScale3D(EndOffset);
}

float PingPong(float t, float len)
{
	float len2 = len * 2;
	t = FMath::Clamp(t - FMath::Floor(t / len2) * len2, 0.0f, len2);
	return (len - FMath::Abs(t - len)) / len;
}

// Called every frame
void ABitTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (easeIn)
	{
		float frac = UBouncee::OutQuart(t);
		CurrentScale = FMath::Lerp(EndOffset, StartSCale, frac);
		SetActorScale3D(CurrentScale);
		t += DeltaTime / duration;
		if (t > 1)
		{
			SetActorScale3D(StartSCale);
			easeIn = false;
		}
	}
	else if (selected)
	{
		float frac = PingPong(t, duration);
		frac = UBouncee::OutQuad(frac);
		CurrentScale = FMath::Lerp(StartSCale, StartSCale + EndOffset, frac);
		SetActorScale3D(CurrentScale);
		t += DeltaTime;
	}
}

