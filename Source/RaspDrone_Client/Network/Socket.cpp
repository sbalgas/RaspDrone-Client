// Fill out your copyright notice in the Description page of Project Settings.

#include "RaspDrone_Client.h"
#include "Socket.h"


// Sets default values
ASocket::ASocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASocket::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

