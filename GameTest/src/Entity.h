#pragma once
#include "App/app.h"
#include "StateMachine.h"
#include "GameLevel.h"

class GameLevel;

class Entity
{
public:
	Entity(float x, float y, float width, float height, CSimpleSprite* sprite, GameLevel& level);
	~Entity();

	void ChangeState(State state);

	void Update(float deltaTime);
	void Render();

	bool Collides(Entity* e) const;

	float GetX() const { return x; }
	float GetY() const { return y; }
	void SetX(float newX);
	void SetY(float newY);

	float GetDx() const { return dx; }
	float GetDy() const { return dy; }
	void SetDx(float newDx);
	void SetDy(float newDy);

	float GetWidth() const { return width; }
	float GetHeight() const { return height; }
	void SetWidth(float newWidth);
	void SetHeight(float newHeight);

	CSimpleSprite* GetSprite() const { return sprite; }

	bool GetDirection() const { return direction; }
	void SetDirection(bool d) { direction = d; }

	GameLevel* GetGameLevel() { return &level; }
	StateMachine* GetStateMachine() { return &stateMachine; }

	bool IsDead() const { return isDead; }
	void SetDead() { isDead = true; }

protected:
	// Draw CollideBox's line, for debugging
	void DrawCollideBox();

	bool isDead;
	float x; // Left
	float y; //Bottom
	float dx;
	float dy;
	float width;
	float height;
	CSimpleSprite* sprite;
	bool direction; // left = 0, right = 1
	StateMachine stateMachine;
	GameLevel& level;// Reference to level for tests against other entities + objects
};

