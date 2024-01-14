#pragma once
#include "states\BaseState.h"
#include "Player.h"

class Player;

class PlayerIdleState: public BaseState
{
public:
	PlayerIdleState(Player* player);
	void Enter() override;
	void Update(float deltaTime) override;
	State GetType() const { return State::IDLE; }


private:
	Player* player;
};

