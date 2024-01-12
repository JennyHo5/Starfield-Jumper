#pragma once
#include "states/BaseState.h"
#include "Player.h"

class Player;

class PlayerWalkingState :
    public BaseState
{
public:
	PlayerWalkingState(Player* player);
	void Enter() override;
	void Update(float deltaTime) override;

private:
	Player* player;

};

