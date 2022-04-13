// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Bouncee.generated.h"

//Functions transfered from:
//https://github.com/DeadMadman/Bouncee
UCLASS()
class MAFF_API UBouncee : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    static float Linear(float t);
    static float SpikeLinear(float t);
    static float InSine(float t);
    static float OutSine(float t);
    static float InOutSine(float t);
    static float SpikeSine(float t);
    static float InQuad(float t);
    static float OutQuad(float t);
    static float InOutQuad(float t);
    static float SpikeQuad(float t);
    static float InCub(float t);
    static float OutCub(float t);
    static float InOutCub(float t);
    static float SpikeCub(float t);
    static float InQuart(float t);
    static float OutQuart(float t);
    static float InOutQuart(float t);
    static float SpikeQuart(float t);
    static float InQuint(float t);
    static float OutQuint(float t);
    static float InOutQuint(float t);
    static float SpikeQuint(float t);
    static float InExpo(float t);
    static float OutExpo(float t);
    static float InOutExpo(float t);
    static float SpikeExpo(float t);
    static float InCircular(float t);
    static float OutCircular(float t);
    static float InOutCircular(float t);
    static float SpikeCircular(float t);
    static float InBounce(float t);
    static float OutBounce(float t);
    static float InOutBounce(float t);
    static float SpikeBounce(float t);
    static float InElastic(float t, float amplitude, float period);
    static float InElastic(float t);
    static float OutElastic(float t);
    static float InOutElastic(float t);
    static float SpikeElastic(float t);
    static float InBack(float t);
    static float OutBack(float t);
    static float InOutBack(float t);
    static float SpikeBack(float t);
    //Helper functions
    static float Invert(float t);
};
