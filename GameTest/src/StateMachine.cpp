#include "stdafx.h"
#include "StateMachine.h"

StateMachine::StateMachine():
    currentState(nullptr)
{}

StateMachine::~StateMachine() {
    // Cleanup allocated memory in the destructor
    for (auto& entry : stateObjects) {
        delete entry.second;
    }
}

void StateMachine::AddState(State state, BaseState* stateObject) {
    stateObjects[state] = stateObject;
}

void StateMachine::ChangeState(State newState) {
    if (currentState != nullptr)
        currentState->Exit();

    auto it = stateObjects.find(newState);
    if (it != stateObjects.end()) {
        currentState = it->second;
        currentState->Enter(); // Call Enter when changing state
    }
    else {
        printf("State not found!\n");
    }
}

void StateMachine::Update(float deltaTime) {

    if (currentState != nullptr) {
        currentState->Update(deltaTime);
    }
    else {
        printf("Current state is nullptr!\n");
    }
}

void StateMachine::Render() {
    currentState->Render();
}

void StateMachine::Exit() {
    currentState->Exit();
}
