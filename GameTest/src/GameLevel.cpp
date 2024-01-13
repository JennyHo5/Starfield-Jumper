#include "stdafx.h"
#include "GameLevel.h"

GameLevel::GameLevel(std::unique_ptr<TileMap> tm, std::vector<GameObject*>* go):
    tileMap(std::move(tm)), gameObjects(go) 
{}

GameLevel::~GameLevel() {
    for (GameObject* o : *gameObjects) {
        delete o;
    }
    delete gameObjects;
}

void GameLevel::Update(float deltaTime) {
    for (const auto & e : entities) {
        if (e) {
            if (e->IsDead()) {
                RemoveEntity(e.get());
            }
            else
                e->Update(deltaTime);
        }
    }
}

void GameLevel::Render() {
    tileMap->Render();

    for (GameObject* o : *gameObjects) {
        o->Render();
    }

    for (const auto& e : entities) {
        e->Render();
    }
}


void GameLevel::AddEntity(std::unique_ptr<Entity> e) {
    entities.push_back(std::move(e));
}

void GameLevel::RemoveEntity(const Entity* e) {
    entities.erase(std::remove_if(entities.begin(), entities.end(),
        [e](const std::unique_ptr<Entity>& ptr) {
            return ptr.get() == e;
        }),
        entities.end());
}

void GameLevel::AddGameObject(GameObject* o) {
    gameObjects->push_back(o);
}

void GameLevel::RemoveGameObject(GameObject* o) {
    auto it = std::find(gameObjects->begin(), gameObjects->end(), o);

    if (it != gameObjects->end()) {
        gameObjects->erase(it);
        delete o;
    }
}