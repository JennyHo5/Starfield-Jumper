#include "stdafx.h"
#include "GameLevel.h"

GameLevel::GameLevel(TileMap* tm, std::vector<Entity*>* es, std::vector<GameObject*>* go):
    tileMap(tm), entities(es), gameObjects(go) 
{}

GameLevel::~GameLevel() {
    delete tileMap;
    for (Entity* e : *entities) {
        delete e;
    }
    delete entities;

    for (GameObject* o : *gameObjects) {
        delete o;
    }
    delete gameObjects;
}

void GameLevel::Init() {}

void GameLevel::Update(float deltaTime) {
    for (Entity* e : *entities) {
        if (e->IsDead()) {
            RemoveEntity(e);
        }
        else
            e->Update(deltaTime);
    }
}

void GameLevel::Render() {
    tileMap->Render();
    for (Entity* e : *entities) {
        e->Render();
    }
}


void GameLevel::AddEntity(Entity* e) {
    entities->push_back(e);
}

void GameLevel::RemoveEntity(Entity* e) {
    auto it = std::find(entities->begin(), entities->end(), e);

    if (it != entities->end()) {
        entities->erase(it);
        delete e;
    }
}