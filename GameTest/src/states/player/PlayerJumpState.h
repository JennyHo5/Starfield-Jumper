#pragma once
#include "Player.h"
#include "states\BaseState.h"

class Player;

class PlayerJumpState:
    public BaseState
{
public:
	PlayerJumpState(Player* player);
	void Enter() override;
	void Update(float deltaTime) override;

private:
	Player* player;
};

