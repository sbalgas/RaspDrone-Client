// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/UserDefinedStruct.h"
#include "PIDStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPIDStruct
{
	GENERATED_BODY()
	
	/** Es ROLL, PITCH o YAW ?  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PID")
	FString Type;

	/** La proporcional */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PID")
	float P;
	
	/** La integral */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PID")
	float I;

	/** La derivada */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PID")
	float D;

	FPIDStruct(){
		Type = "";
		P = 0;
		I = 0;
		D = 0;
	}

	/** Obtener un JSON con los valores del PID */
	FString getJsonString(){
		TSharedPtr< FJsonObject > JsonObj = MakeShareable(new FJsonObject);

		JsonObj->SetStringField("Type", Type);
		JsonObj->SetNumberField("P", P);
		JsonObj->SetNumberField("I", I);
		JsonObj->SetNumberField("D", D);

		FString OutputString;
		TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(JsonObj.ToSharedRef(), Writer);

		UE_LOG(LogTemp, Warning, TEXT("%s"), *OutputString);

		return OutputString;
	
	}

	void setPIDArray(TArray<int32> newPid){
		P = newPid[0];
		I = newPid[1];
		D = newPid[2];
	}
	
};
