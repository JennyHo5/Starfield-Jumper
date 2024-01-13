#include "stdafx.h"
#include "GameLevel.h"

GameLevel::GameLevel(std::unique_ptr<TileMap> tm):
    tileMap(std::move(tm))
{}

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

    for (const auto& o : gameObjects) {
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

void GameLevel::AddGameObject(std::unique_ptr<GameObject> o) {
    gameObjects.push_back(std::move(o));
}

void GameLevel::RemoveGameObject(GameObject* o) {
    gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(),
        [o](const std::unique_ptr<GameObject>& ptr) {
            return ptr.get() == o;
        }),
        gameObjects.end());
}