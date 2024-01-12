#pragma once
#include "tilesystem/TileMap.h"
#include "Entity.h"

class Entity;

class GameLevel {
public:
    GameLevel(TileMap* tileMap, std::vector<Entity*>* entities);
    ~GameLevel();

    void Init();
    void Update(float deltaTime);
    void Render();

    void AddEntity(Entity*);
    void RemoveEntity(Entity*);
    TileMap* GetTileMap() const { return tileMap; }
    std::vector<Entity*>* GetEntities() const { return entities; }

private:
    TileMap* tileMap;
    std::vector<Entity*>* entities; //enemies
};

