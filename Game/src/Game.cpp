#include "stdafx.h"
#include "Game.h"

std::unique_ptr<StateMachine> Game::stateMachine;  // Definition of the static member variable

Game::Game()
{
	stateMachine = std::make_unique<StateMachine>();
}


StateMachine* Game::GetStateMachine() {
    return stateMachine.get();
}

void Game::Init()
{
	// Initialize state machine for the game
	stateMachine->AddState(State::START, std::make_unique<StartState>());
	stateMachine->AddState(State::PLAY, std::make_unique<PlayState>());
	stateMachine->ChangeState(State::START);
}

// deltaTime is the elapsed time since the last update in ms
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
void Game::Update(float deltaTime)
{
	stateMachine->Update(deltaTime);
}

void Game::Render()
{
	stateMachine->Render();
}

void Game::Exit()
{
	stateMachine->Exit();
}
