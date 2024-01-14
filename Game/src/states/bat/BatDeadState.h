#pragma once
#include "enemy\Bat.h"
#include ".\states\BaseState.h"

class Bat;

class BatDeadState :
	public BaseState
{
public:
	BatDeadState(Bat* bat);
	void Enter() override;
	void Update(float deltaTime) override;
	State GetType() const { return State::BAT_DEAD; }


private:
	Bat* bat;
	int animTimer;
};

