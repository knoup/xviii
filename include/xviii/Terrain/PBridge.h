#pragma once

#include "xviii/Terrain/TerrainTile.h"

class PBridge : public TerrainTile
{
public:
	PBridge(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos);

    inline void setHp(int _hp){hp = _hp;};
    inline int getHp(){return hp;};

    virtual void takeDamage(int dmg);

private:
    int hp;
};

