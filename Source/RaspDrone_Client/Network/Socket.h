// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Networking.h"
#include "ControlStruct.h"
#include "PIDStruct.h"
#include "OrderStruct.h"
#include "Socket.generated.h"

USTRUCT(BlueprintType)
struct FDroneStatus
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network")
	int32 MotorFL = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network")
	int32 MotorFR = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network")
	int32 MotorBL = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network")
	int32 MotorBR = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network")
	int32 CPU = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network")
	int32 RAM = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network")
	int32 Temperature = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network")
	int32 NetUp = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network")
	int32 NetDown = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network")
	float Roll = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network")
	float Pitch = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network")
	float Yaw = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network|PID")
	float PIDRollError = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network|PID")
	float PIDPitchError = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network|PID")
	float PIDYawError = 0;

};

class ListenRunnable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageReceived, FPIDStruct, message);

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
	bool isConnected = false;

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
	bool SendMessageString(FString string);

	UFUNCTION(BlueprintCallable, Category = "Networking")
	bool SendMessageControl(FControlStruct control);

	UFUNCTION(BlueprintCallable, Category = "Networking")
	bool SendMessageOrder(FOrderStruct order);

	UFUNCTION(BlueprintNativeEvent, Category = "Networking")
	void OnConnected();
	void OnConnected_Implementation();

	UPROPERTY(BlueprintAssignable)
	FOnMessageReceived OnMessageReceived;

	UPROPERTY(BlueprintReadOnly, Category = "Networking")
	FDroneStatus droneStatus;

	UPROPERTY(BlueprintReadOnly, Category = "Networking")
	FString addressConnected;
	UPROPERTY(BlueprintReadOnly, Category = "Networking")	
	int32 portConnected;
};


