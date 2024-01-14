#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject(float x, float y, float width, float height, CSimpleSprite* sprite) :
	x(x),
	y(y),
	width(width),
	height(height),
	sprite(sprite)
{
	sprite->SetPosition(x, y);
}

GameObject::~GameObject() {
	if (sprite != nullptr)
		delete sprite;
}

void GameObject::Render() {
	sprite->Draw();
}
