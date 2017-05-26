// Fill out your copyright notice in the Description page of Project Settings.

#include "RaspDrone_Client.h"
#include "ListenRunnable.h"

ListenRunnable* ListenRunnable::Runnable = NULL;

ListenRunnable::ListenRunnable(FSocket* newSocket, FOnMessageReceived* OnMessageEvent){
	//Link to where data should be stored
	Socket = newSocket;
	OnMessageReceived = OnMessageEvent;
	Thread = FRunnableThread::Create(this, TEXT("ListenRunnable"), 0, TPri_BelowNormal); //windows default = 8mb for thread, could specify more
}
 
ListenRunnable::~ListenRunnable(){
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
	FString Msg;
	uint32 size;
	uint32 dataSize = 0;
	
	FDroneStatus droneStatus;
	TSharedPtr<FJsonObject> JsonObject;

	while (StopTaskCounter.GetValue() == 0) {
		//FPlatformProcess::Sleep(1);
		FPlatformProcess::Sleep(0.01);

		if (Socket->HasPendingData(size) ){
			dataSize = 0;		
			
			FArrayReaderPtr Datagram = MakeShareable(new FArrayReader(true)); 
			Datagram->Init(FMath::Min(dataSize, 65507u), size); 

			int32 BytesRead = 0; 
			if (Socket->Recv(Datagram->GetData(), Datagram->Num(), BytesRead)) { 
				char* Data = (char*)Datagram->GetData();
				Data[BytesRead] = '\0'; 
				Msg = FString(Data);

				TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(*Msg);
				if (FJsonSerializer::Deserialize(JsonReader, JsonObject)) {

					if (JsonObject->HasField("MotorFL")){
						droneStatus.MotorFL = JsonObject->GetIntegerField("MotorFL");	
					}
					
					if (JsonObject->HasField("MotorFR")){
						droneStatus.MotorFR = JsonObject->GetIntegerField("MotorFR");	
					}

					if (JsonObject->HasField("MotorBL")){
						droneStatus.MotorBL = JsonObject->GetIntegerField("MotorBL");	
					}

					if (JsonObject->HasField("MotorBR")){
						droneStatus.MotorBR = JsonObject->GetIntegerField("MotorBR");	
					}

					if (JsonObject->HasField("CPU")){
						droneStatus.CPU = JsonObject->GetIntegerField("CPU");	
					}

					if (JsonObject->HasField("RAM")){
						droneStatus.RAM = JsonObject->GetIntegerField("RAM");	
					}

					if (JsonObject->HasField("Temperature")){
						droneStatus.Temperature = JsonObject->GetIntegerField("Temperature");	
					}

					if (JsonObject->HasField("NetUp")){
						droneStatus.NetUp = JsonObject->GetIntegerField("NetUp");	
					}
					if (JsonObject->HasField("NetDown")){
						droneStatus.NetDown = JsonObject->GetIntegerField("NetDown");	
					}

					if (JsonObject->HasField("Yaw")){
						droneStatus.Yaw = JsonObject->GetIntegerField("Yaw");	
					}

					if (JsonObject->HasField("Pitch")){
						droneStatus.Pitch = JsonObject->GetIntegerField("Pitch");	
					}

					if (JsonObject->HasField("Roll")){
						droneStatus.Roll = JsonObject->GetIntegerField("Roll");	
					}

					OnMessageReceived->Broadcast(droneStatus);	
				}

			} 
		}
		
	}
	UE_LOG(LogTemp, Warning, TEXT("exit"));
 
	return 0;
}
 
void ListenRunnable::Stop(){
	UE_LOG(LogTemp, Warning, TEXT("STOP FUNCTION"));
	StopTaskCounter.Increment();
	if (Socket)
		Socket->Close();
	/*if (clientSocket)
		clientSocket->Close();*/
}
 
ListenRunnable* ListenRunnable::JoyInit(FSocket* newSocket, FOnMessageReceived* OnMessageEvent) {
	//Create new instance of thread if it does not exist
	//		and the platform supports multi threading!
	if (!Runnable && FPlatformProcess::SupportsMultithreading())
		Runnable = new ListenRunnable(newSocket, OnMessageEvent);			
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
 
