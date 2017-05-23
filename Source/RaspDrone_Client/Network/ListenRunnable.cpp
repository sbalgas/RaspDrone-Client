// Fill out your copyright notice in the Description page of Project Settings.

#include "RaspDrone_Client.h"
#include "ListenRunnable.h"

ListenRunnable* ListenRunnable::Runnable = NULL;

ListenRunnable::ListenRunnable(FSocket* newSocket){
	//Link to where data should be stored
	Socket = newSocket;
 
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
				Msg = UTF8_TO_TCHAR(Data); 
			} 
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
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
 
ListenRunnable* ListenRunnable::JoyInit(FSocket* newSocket) {
	//Create new instance of thread if it does not exist
	//		and the platform supports multi threading!
	if (!Runnable && FPlatformProcess::SupportsMultithreading())
		Runnable = new ListenRunnable(newSocket);			
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
 
