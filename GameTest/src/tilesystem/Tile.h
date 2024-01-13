#pragma once
#include "app/app.h"
#include "global/constants.h"

class Tile
{
public:
    Tile(int type, float x, float y);
    ~Tile();

    void Render();
    
    CSimpleSprite* GetSprite() const { return sprite; }
    float GetX() const { return x; }
    float GetY() const { return y; }
    int GetID() const { return id; }

    bool Collidable() const;

    bool IsPlatform() const;

private:
    int id;
    float x;
    float y;
    float width;
    float height;
    CSimpleSprite* sprite;
};

