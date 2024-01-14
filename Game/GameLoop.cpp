#include "stdafx.h"
#include <windows.h> 
#include <math.h>  
#include "app/app.h"
#include "src/StateMachine.h"
#include "src/states/game/PlayState.h"
#include "src/states/game/StartState.h"
#include "src/Game.h"

// State machine for the whole game
Game game;

void Init()
{
	//AllocConsole();
	//freopen("CONOUT$", "w", stdout);

	game.Init();
}

// deltaTime is the elapsed time since the last update in ms
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
void Update(float deltaTime)
{
	game.Update(deltaTime);
}

void Render()
{
	game.Render(); 
}

void Shutdown()
{
	game.Exit();
}