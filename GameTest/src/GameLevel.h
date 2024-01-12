#pragma once
#include "tilesystem/TileMap.h"
#include "Entity.h"
#include "GameObject.h"

class Entity;

class GameLevel {
public:
    GameLevel(TileMap* tileMap, std::vector<Entity*>* entities, std::vector<GameObject*>* gameObjects);
    ~GameLevel();

    void Init();
    void Update(float deltaTime);
    void Render();

    void AddEntity(Entity*);
    void RemoveEntity(Entity*);
    void AddGameObject(GameObject*);
    void RemoveGameObject(GameObject*);

    TileMap* GetTileMap() const { return tileMap; }
    std::vector<Entity*>* GetEntities() const { return entities; }
    std::vector<GameObject*>* GetGameObjects() const { return gameObjects; }

private:
    TileMap* tileMap;
    std::vector<Entity*>* entities; //enemies
    std::vector<GameObject*>* gameObjects; //decorations
};

