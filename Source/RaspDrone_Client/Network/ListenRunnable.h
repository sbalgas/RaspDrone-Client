// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Networking.h"
#include "Socket.h"
/**
 * 
 */

class RASPDRONE_CLIENT_API ListenRunnable : public FRunnable {

	static ListenRunnable* Runnable;
	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;
 
	/** The Data Ptr */
	FSocket* Socket;
  
	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	FOnMessageReceived *OnMessageReceived;

public:
	ListenRunnable(FSocket* newSocket, FOnMessageReceived* OnMessageEvent);
	virtual ~ListenRunnable();
 
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();

	void EnsureCompletion();
 
	static ListenRunnable* JoyInit(FSocket* newSocket, FOnMessageReceived* OnMessageEvent);
	
	static void Shutdown();
};
