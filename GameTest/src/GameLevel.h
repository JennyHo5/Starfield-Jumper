#pragma once
#include "tilesystem/TileMap.h"
#include "Entity.h"
#include "GameObject.h"

class Entity;

class GameLevel {
public:
    GameLevel(std::unique_ptr<TileMap> tileMap);

    void Update(float deltaTime);
    void Render();

    void AddEntity(std::unique_ptr<Entity> e);
    void RemoveEntity(const Entity* e);
    void AddGameObject(std::unique_ptr<GameObject>);
    void RemoveGameObject(GameObject*);

    const TileMap* GetTileMap() const { return tileMap.get(); }

    const std::vector<std::unique_ptr<Entity>>& GetEntities() const { return entities; }

    const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() const { return gameObjects; }

private:
    std::unique_ptr<TileMap> tileMap;
    std::vector<std::unique_ptr<Entity>> entities; // enemies and player
    std::vector<std::unique_ptr<GameObject>> gameObjects; // decorations
};

