#include "stdafx.h"
#include "GameStateMachine.h"

// Initialize the static member variable
StateMachine* GameStateMachine::instance = nullptr;

GameStateMachine::GameStateMachine()
{
}

GameStateMachine::~GameStateMachine() {
    if (instance != nullptr)
        delete instance;
}

// Function to get the single instance of StateMachine
StateMachine* GameStateMachine::GetInstance() {
    if (instance == nullptr) {
        instance = new StateMachine();
    }
    return instance;
}
