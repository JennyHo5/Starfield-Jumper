#include "stdafx.h"
#include "StateMachineManager.h"

// Initialize the static member variable
StateMachine* StateMachineManager::instance = nullptr;

StateMachineManager::StateMachineManager()
{
}

StateMachineManager::~StateMachineManager() {
    if (instance != nullptr)
        delete instance;
}

// Function to get the single instance of StateMachine
StateMachine* StateMachineManager::GetInstance() {
    if (instance == nullptr) {
        instance = new StateMachine();
    }
    return instance;
}
