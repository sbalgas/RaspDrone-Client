// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/UserDefinedStruct.h"
#include "ControlStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FControlStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	float Throttle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	float Roll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	float Pitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	float Yaw;

	FControlStruct(){
		Throttle = 0;
		Roll = 0;
		Pitch = 0;
		Yaw = 0;
	}
	
};
