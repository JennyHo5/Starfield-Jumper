#pragma once
#include <unordered_map>
#include "states/BaseState.h"
#include "global/constants.h"

class BaseState;

class StateMachine
{
public:
	StateMachine();

	// Add states to the state machine
	void AddState(State state, std::unique_ptr<BaseState> stateObject);

	// Change the current state
	void ChangeState(State newState);

	// Update the current state
	void Update(float deltaTime);

	// Draw the current state
	void Render();

	// Exit the current state
	void Exit();

	const BaseState* GetCurrentState() { return currentState; }

private:
	std::unordered_map<State, std::unique_ptr<BaseState>> stateObjects;
	BaseState* currentState;
};

