#pragma once
#include "StateMachine.h"

class StateMachine;

class StateMachineManager
{

public:
	// Function to get the single instance of StateMachine
	static StateMachine* GetInstance();

private: 
	StateMachineManager();
	~StateMachineManager();
	static StateMachine* instance; // The single instance of the StateMachine
};

