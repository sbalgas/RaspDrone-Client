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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	int32 PIDMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	float PIDValue;

	FControlStruct(){
		Throttle = 0;
		Roll = 0;
		Pitch = 0;
		Yaw = 0;
		PIDMode = 0;
		PIDValue = 0;
	}

	FString getJsonString(){


		// create a Json object and add a string field
		TSharedPtr< FJsonObject > JsonObj = MakeShareable(new FJsonObject);

		JsonObj->SetNumberField("Throttle", Throttle);
		JsonObj->SetNumberField("Roll", Roll);
		JsonObj->SetNumberField("Pitch", Pitch);
		JsonObj->SetNumberField("Yaw", Yaw);

		JsonObj->SetNumberField("PIDMode", PIDMode);
		JsonObj->SetNumberField("PIDValue", PIDValue);

		FString OutputString;
		TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(JsonObj.ToSharedRef(), Writer);
		return OutputString;
	
	}
	
};
