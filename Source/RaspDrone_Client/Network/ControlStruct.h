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
	float Forward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	float Back;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	float Left;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	float Right;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	float TurnLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	float TurnRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	float GoUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	float GoDown;

	FControlStruct(){
		Forward = 0;
		Back = 0;
		Left = 0;
		Right = 0;
		TurnLeft = 0;
		TurnRight = 0;
		GoUp = 0;
		GoDown = 0;
	}
	
};
