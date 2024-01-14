#pragma once
#include "StateMachine.h"
#include "states/game/StartState.h"
#include "states/game/PlayState.h"


class StateMachine;
class StartState;
class PlayState;

class Game
{

public:
	Game();
	void Init();
	void Update(float deltaTime);
	void Render();
	void Exit();
	static StateMachine* GetStateMachine();

private: 

	static std::unique_ptr<StateMachine> stateMachine;
};

