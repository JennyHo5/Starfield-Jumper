#pragma once
#include "Player.h"
#include ".\states\BaseState.h"
#include "game.h"

class Game;
class Player;

class PlayerWinState :
    public BaseState
{
public:
	PlayerWinState(Player* player);
	void Enter() override;
	void Update(float deltaTime) override;

private:
	Player* player;

};

