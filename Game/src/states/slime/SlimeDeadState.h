#pragma once
#include "enemy\Slime.h"
#include ".\states\BaseState.h"

class Slime;

class SlimeDeadState :
    public BaseState
{
public:
	SlimeDeadState(Slime* slime);
	void Enter() override;
	void Update(float deltaTime) override;
	State GetType() const { return State::SLIME_DEAD; }

private:
	Slime* slime;
	int animTimer;
};

