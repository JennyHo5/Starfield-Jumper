#include "stdafx.h"
#include "Game.h"

// Initialize the static member variable
StateMachine* Game::instance = nullptr;

Game::Game()
{
}

Game::~Game() {
    if (instance != nullptr)
        delete instance;
}

// Function to get the single instance of StateMachine
StateMachine* Game::GetInstance() {
    if (instance == nullptr) {
        instance = new StateMachine();
    }
    return instance;
}
