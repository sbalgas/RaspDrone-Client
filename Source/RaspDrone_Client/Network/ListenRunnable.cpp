// Fill out your copyright notice in the Description page of Project Settings.

#include "RaspDrone_Client.h"
#include "ListenRunnable.h"

ListenRunnable* ListenRunnable::Runnable = NULL;

ListenRunnable::ListenRunnable(FSocket* newSocket, FOnMessageReceived* OnMessageEvent, FDroneStatus& TheDroneStatus) {
	//Link to where data should be stored
	Socket = newSocket;
	OnMessageReceived = OnMessageEvent;
	droneStatus = &TheDroneStatus;

	Thread = FRunnableThread::Create(this, TEXT("ListenRunnable"), 0, TPri_BelowNormal); //windows default = 8mb for thread, could specify more
}

ListenRunnable::~ListenRunnable() {
	UE_LOG(LogTemp, Warning, TEXT("delete thread"));
	//delete Runnable;
	Thread = NULL;
}

bool ListenRunnable::Init() {
	// Initialize
	UE_LOG(LogTemp, Warning, TEXT("Initialize"));
	return true;
}

uint32 ListenRunnable::Run() {

	FPlatformProcess::Sleep(0.03);

	TArray<uint8> ReceivedData;
	uint32 Size;
	int32 Read = 0;
	
	//UE_LOG(LogTemp, Warning, TEXT("tick %s"), DeltaTime);
	
	while (StopTaskCounter.GetValue() == 0) {
		FPlatformProcess::Sleep(0.001);

		if (!Socket->HasPendingData(Size))
			continue;
		ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));

		Read = 0;
		if (!Socket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read))
			continue;

		ReceivedData.RemoveAt(Read, ReceivedData.Num() - Read, false);

		if (ReceivedData.Num() <= 0)
			continue;
		
		FMemoryReader MemoryReader(ReceivedData);
		FString Msg = FString((char*)(ReceivedData.GetData()));

		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(*Msg);

		if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid()) {
			UE_LOG(LogTemp, Warning, TEXT("Error, no se puede deserializar: %s"), *Msg);
			continue;
		}

		if (JsonObject->HasField("MotorFL")) {
			droneStatus->MotorFL = JsonObject->GetIntegerField("MotorFL");
		}
		
		if (JsonObject->HasField("MotorFR")) {
			droneStatus->MotorFR = JsonObject->GetIntegerField("MotorFR");
		}

		if (JsonObject->HasField("MotorBL")) {
			droneStatus->MotorBL = JsonObject->GetIntegerField("MotorBL");
		}

		if (JsonObject->HasField("MotorBR")) {
			droneStatus->MotorBR = JsonObject->GetIntegerField("MotorBR");
		}

		if (JsonObject->HasField("CPU")) {
			droneStatus->CPU = JsonObject->GetIntegerField("CPU");
		}

		if (JsonObject->HasField("RAM")) {
			droneStatus->RAM = JsonObject->GetIntegerField("RAM");
		}

		if (JsonObject->HasField("Temperature")) {
			droneStatus->Temperature = JsonObject->GetIntegerField("Temperature");
		}

		if (JsonObject->HasField("NetUp")) {
			droneStatus->NetUp = JsonObject->GetIntegerField("NetUp");
		}
		if (JsonObject->HasField("NetDown")) {
			droneStatus->NetDown = JsonObject->GetIntegerField("NetDown");
		}

		if (JsonObject->HasField("Yaw")) {
			droneStatus->Yaw = JsonObject->GetNumberField("Yaw");
		}

		if (JsonObject->HasField("Pitch")) {
			droneStatus->Pitch = JsonObject->GetNumberField("Pitch");
		}

		if (JsonObject->HasField("Roll")) {
			droneStatus->Roll = JsonObject->GetNumberField("Roll");
		}

		if (JsonObject->HasField("PidRollError")) {
			droneStatus->PIDRollError = JsonObject->GetNumberField("PidRollError");
		}

		if (JsonObject->HasField("PidPitchError")) {
			droneStatus->PIDPitchError = JsonObject->GetNumberField("PidPitchError");
		}

		if (JsonObject->HasField("PidYawError")) {
			droneStatus->PIDYawError = JsonObject->GetNumberField("PidYawError");
		}

	}
	UE_LOG(LogTemp, Warning, TEXT("exit"));
	return 0;
}

void ListenRunnable::Stop() {
	UE_LOG(LogTemp, Warning, TEXT("STOP FUNCTION"));
	StopTaskCounter.Increment();
	if (Socket)
		Socket->Close();
	/*if (clientSocket)
	clientSocket->Close();*/
}

ListenRunnable* ListenRunnable::JoyInit(FSocket* newSocket, FOnMessageReceived* OnMessageEvent, FDroneStatus& TheDroneStatus) {
	if (!Runnable && FPlatformProcess::SupportsMultithreading())
		Runnable = new ListenRunnable(newSocket, OnMessageEvent, TheDroneStatus);
	return Runnable;
}

void ListenRunnable::EnsureCompletion() {
	Stop();
	Thread->WaitForCompletion();
}

void ListenRunnable::Shutdown() {
	if (Runnable) {
		Runnable->EnsureCompletion();
		delete Runnable;
		Runnable = NULL;
	}
}

void ListenRunnable::Tick(float DeltaTime){
	//Runnable->DeltaTime = DeltaTime;
}