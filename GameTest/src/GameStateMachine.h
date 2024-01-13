#pragma once
#include "StateMachine.h"

class StateMachine;

class GameStateMachine
{

public:
	// Function to get the single instance of StateMachine
	static StateMachine* GetInstance();

private: 
	GameStateMachine();
	~GameStateMachine();
	static StateMachine* instance; // The single instance of the StateMachine
};

