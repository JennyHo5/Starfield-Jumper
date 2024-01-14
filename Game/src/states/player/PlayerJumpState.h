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
	State GetType() const { return State::JUMP; }


private:
	Player* player;
};

