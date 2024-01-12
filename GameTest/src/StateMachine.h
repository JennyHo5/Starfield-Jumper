#pragma once
#include <unordered_map>
#include "states/BaseState.h"
#include "global/constants.h"

class BaseState;

class StateMachine
{
public:
	StateMachine();

	~StateMachine();

	// Add states to the state machine
	void AddState(State state, BaseState* stateObject);

	// Change the current state
	void ChangeState(State newState);

	// Update the current state
	void Update(float deltaTime);

	// Draw the current state
	void Render();

	// Exit the current state
	void Exit();

	BaseState* GetCurrentState() { return currentState; }

private:
	std::unordered_map<State, BaseState*> stateObjects;
	BaseState* currentState;
};

