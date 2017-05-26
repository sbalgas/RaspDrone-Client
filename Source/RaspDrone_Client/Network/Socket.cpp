// Fill out your copyright notice in the Description page of Project Settings.

#include "RaspDrone_Client.h"
#include "ListenRunnable.h"
#include "Socket.h"


// Sets default values
ASocket::ASocket(){
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASocket::BeginPlay(){
	Super::BeginPlay();
}

void ASocket::BeginDestroy(){
	Super::BeginDestroy();
	ListenRunnable::Shutdown();
}

// Called every frame
void ASocket::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

bool ASocket::StartTCPReceiver(const FString& address, const int32 port) {
	addressConnected = address;
	portConnected = port;
	if (this->_startTCPReceiver(address, port)){
		ListenRunnable::JoyInit(Socket, &OnMessageReceived);
		this->OnConnected();
		return true;
	}
	return false;
}

bool ASocket::_startTCPReceiver(const FString& address, const int32 port){
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	FIPv4Address ip;

	if (!FIPv4Address::Parse(address, ip))
		return false;

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	return Socket->Connect(*addr);
}

bool ASocket::SendMessage(FString string){

	TCHAR *serializedChar = string.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);
	int32 sent = 0;

	return Socket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);
}

void ASocket::OnConnected_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("ON CONNECT"));
}
