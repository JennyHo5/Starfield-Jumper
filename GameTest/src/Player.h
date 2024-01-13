#pragma once
#include "Entity.h"
#include "states/player/PlayerIdleState.h"
#include "states/player/PlayerWalkingState.h"
#include "states/player/PlayerJumpState.h"
#include "states/player/PlayerFallingState.h"
#include "states/player/PlayerDeadState.h"
#include "states/player/PlayerWinState.h"


class PlayerIdleState;
class PlayerWalkingState;
class PlayerJumpState;
class PlayerFallingState;
class PlayerAttackState;
class PlayerDeadState;
class PlayerWinState;

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
    void CheckUpCollisions();

    int GetScore() const { return score; }
    void AddScore(int add) { score += add; }

    bool GetIsWin() const { return isWin; }
    void SetWin() { isWin = true; }

private:
    int score;
    bool isWin;
};

