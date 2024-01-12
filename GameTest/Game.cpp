#include "stdafx.h"
#include <windows.h> 
#include <math.h>  
#include "app/app.h"
#include "src/StateMachine.h"
#include "src/states/game/PlayState.h"
#include "src/states/game/StartState.h"
#include "src/manager/StateMachineManager.h"

// State machine for the whole game
StateMachine* gStateMachine = StateMachineManager::GetInstance();

void Init()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	// Initialize state machine for the game
	gStateMachine->AddState(State::START, new StartState());
	gStateMachine->AddState(State::PLAY, new PlayState());
	gStateMachine->ChangeState(State::START);
}

// deltaTime is the elapsed time since the last update in ms
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
void Update(float deltaTime)
{
	gStateMachine->Update(deltaTime);
}

void Render()
{
	gStateMachine->Render(); 
}

void Shutdown()
{
	gStateMachine->Exit();
}