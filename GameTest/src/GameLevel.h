#pragma once
#include "tilesystem/TileMap.h"
#include "Entity.h"
#include "GameObject.h"

class Entity;

class GameLevel {
public:
    GameLevel(std::unique_ptr<TileMap> tileMap, std::vector<Entity*>* entities, std::vector<GameObject*>* gameObjects);
    ~GameLevel();

    void Init();
    void Update(float deltaTime);
    void Render();

    void AddEntity(Entity*);
    void RemoveEntity(Entity*);
    void AddGameObject(GameObject*);
    void RemoveGameObject(GameObject*);

    const TileMap* GetTileMap() const { return tileMap.get(); }
    std::vector<Entity*>* GetEntities() const { return entities; }
    std::vector<GameObject*>* GetGameObjects() const { return gameObjects; }

private:
    std::unique_ptr<TileMap> tileMap;
    std::vector<Entity*>* entities; //enemies
    std::vector<GameObject*>* gameObjects; //decorations
};

