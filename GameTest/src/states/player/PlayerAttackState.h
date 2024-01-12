#pragma once
#include "states/BaseState.h"
#include "Player.h"

class Player;

class PlayerAttackState :
    public BaseState
{
public:
	PlayerAttackState(Player* player);
	void Enter() override;
	void Update(float deltaTime) override;

private:
	Player* player;
	int animTimer;
};

