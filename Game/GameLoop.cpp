#include "stdafx.h"
#include <windows.h> 
#include <math.h>  
#include "app/app.h"
#include "src/Game.h"

// The main game object
Game game;

void Init()
{
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