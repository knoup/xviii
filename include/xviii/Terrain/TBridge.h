#pragma once

#include "xviii/Terrain/TerrainTile.h"

class TBridge : public TerrainTile
{
public:
	TBridge(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos);

    inline void setHp(int _hp){hp = _hp;};
    inline int getHp(){return hp;};

    virtual void takeDamage(int dmg);

    //By default, the bridge spawns with its VER (vertical) version. You can use this to flip it.
    void flip(sf::Sprite _sprite){sprite = _sprite;};

    virtual std::string callTerrainAttack(UnitTile* unit, int distance);

private:
    int hp;
};

