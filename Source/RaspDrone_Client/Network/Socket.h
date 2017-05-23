// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Networking.h"
#include "ListenRunnable.h"
#include "Socket.generated.h"

UCLASS()
class RASPDRONE_CLIENT_API ASocket : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

private: 
	
	FSocket* Socket;

	bool _startTCPReceiver(
		const FString& address, 
		const int32 port
	);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Networking")
	bool StartTCPReceiver(
		const FString& address, 
		const int32 port
	);

	UFUNCTION(BlueprintCallable, Category = "Networking")
	bool SendMessage(FString string);
};
