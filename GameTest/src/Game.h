#pragma once
#include "StateMachine.h"

class StateMachine;

class Game
{

public:
	// Function to get the single instance of StateMachine
	static StateMachine* GetInstance();

private: 
	Game();
	~Game();
	static StateMachine* instance; // The single instance of the StateMachine
};

