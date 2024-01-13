#include "stdafx.h"
#include "StateMachine.h"

StateMachine::StateMachine()
{}

void StateMachine::AddState(State state, std::unique_ptr<BaseState> stateObject) {
    stateObjects[state] = std::move(stateObject);
}

void StateMachine::ChangeState(State newState) {
    if (currentState != nullptr)
        currentState->Exit();

    auto it = stateObjects.find(newState);
    if (it != stateObjects.end()) {
        currentState = it->second.get();
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
