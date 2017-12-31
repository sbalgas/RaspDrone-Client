// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/UserDefinedStruct.h"
#include "OrderStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FOrderStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network")
	FString Order;

	FOrderStruct(){
		Order = "";
	}

	/** Obtener un JSON con los valores */
	FString getJsonString(){
		TSharedPtr< FJsonObject > JsonObj = MakeShareable(new FJsonObject);

		JsonObj->SetStringField("Order", Order);

		FString OutputString;
		TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
		FJsonSerializer::Serialize(JsonObj.ToSharedRef(), Writer);

		return OutputString;	
	}
	
};
