#pragma once
#include "Entity.h"
#include "states/player/PlayerIdleState.h"
#include "states/player/PlayerWalkingState.h"
#include "states/player/PlayerJumpState.h"
#include "states/player/PlayerFallingState.h"
#include "states/player/PlayerAttackState.h"
#include "states/player/PlayerDeadState.h"


class PlayerIdleState;
class PlayerWalkingState;
class PlayerJumpState;
class PlayerFallingState;
class PlayerAttackState;
class PlayerDeadState;

enum PlayerAnimation
{
    IDLE,
    WALKING,
    JUMP,
    FALLING,
    ATTACK,
    DEAD
};

class Player : public Entity
{
public:
    Player(float x, float y, GameLevel& level);
    void SetAnimation(PlayerAnimation anim);
    void SetFrame(int id);

    void CheckLeftCollisions();
    void CheckRightCollisions();
    void CheckBottomCollisions();

    bool InAttackRate(Entity*) const;

    bool IsDead() const { return isDead; }
    void SetDead() { isDead = true; }

private:
    bool isDead;
};

