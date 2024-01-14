#pragma once
#include "App\app.h"

class GameObject
{

public:
	GameObject(float x, float y, float width, float height, CSimpleSprite* sprite);
	~GameObject();

	void Render();

	float GetX() const { return x; }
	float GetY() const { return y; }
	float GetWidth() const { return width; }
	float GetHeight() const { return height; }

	CSimpleSprite* GetSprite() const { return sprite; }

private:
	float x;
	float y;
	float width;
	float height;
	CSimpleSprite* sprite;
};

