#pragma once

#include "xviii/Terrain/TerrainTile.h"

class PBridge : public TerrainTile
{
public:
	PBridge(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos);
	virtual void takeDamage(UnitTile* attacker, float& _dmg, int distance){};

    inline void setHp(int _hp){hp = _hp;};
    inline int getHp(){return hp;};

    virtual void takeDamage(int dmg);

private:
    int hp;
};

