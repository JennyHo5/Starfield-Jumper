#include "stdafx.h"
#include "Entity.h"

Entity::Entity(float x, float y, float width, float height, CSimpleSprite* sprite, GameLevel& l) :
	x(x),
	y(y),
	dx(0),
	dy(0),
	width(width),
	height(height),
	sprite(sprite),
	direction(1),
	level(l),
	isDead(false)
{
	sprite->SetPosition(x, y);
}

Entity::~Entity() {
	if (sprite != nullptr)
		delete sprite;
}

void Entity::ChangeState(State state) {
	stateMachine.ChangeState(state);
}


void Entity::Update(float deltaTime) {
	sprite->Update(deltaTime);
	stateMachine.Update(deltaTime);
}

bool Entity::Collides(Entity* entity) const {
	return !(x - width / 2 > entity->GetX() + entity->GetWidth() / 2 || entity->GetX() - entity->GetWidth() / 2 > x + width / 2 ||
			y - height / 2 > entity->GetY() + entity->GetHeight() / 2 || entity->GetY() - entity->GetHeight() > y + height / 2);
}

void Entity::Render() {
	sprite->Draw();
	DrawCollideBox();
}

void Entity::SetX(float newX) { 
	x = newX; 
}

void Entity::SetY(float newY) { 
	y = newY; 
}

void Entity::SetDx(float newDx) { 
	dx = newDx; 
}

void Entity::SetDy(float newDy) { 
	dy = newDy; 
}

void Entity::SetWidth(float newWidth) {
	width = newWidth;
}

void Entity::SetHeight(float newHeight) {
	height = newHeight;
}

void Entity::DrawCollideBox() {

	// Calculate the rectangle position based on the object's position and size
	float rectLeft = x - width / 2;
	float rectBottom = y - height / 2;
	float rectTop = rectBottom + height;
	float rectRight = rectLeft + width;

	// Draw the four lines representing the sides of the rectangle
	App::DrawLine(rectLeft, rectTop, rectRight, rectTop, 0, 255, 0);    // Top line
	App::DrawLine(rectRight, rectTop, rectRight, rectBottom, 0, 255, 0); // Right line
	App::DrawLine(rectRight, rectBottom, rectLeft, rectBottom, 0, 255, 0); // Bottom line
	App::DrawLine(rectLeft, rectBottom, rectLeft, rectTop, 0, 255, 0);   // Left line

}