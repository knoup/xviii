#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Bridge : public TerrainTile
{
public:
	Bridge(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos);

    inline void setHp(int _hp){hp = _hp;};
    inline int getHp(){return hp;};

    void takeDamage(int dmg);

    //By default, the bridges spawn with a blank texture; flip() must be called after spawning to determine its
    //correct direction. I know I should probably have this in the constructor, but then the bridge constructor signature
    //would differ from all the other terrain tiles and it wouldn't be properly usable in a macro anymore.
    virtual void flip(Orientation _or);

    Orientation getOrientation(){return orientation;};

    virtual std::string callTerrainAttack(UnitTile* unit, int distance);

    bool northernConnection{false};
    bool southernConnection{false};
    bool easternConnection{false};
    bool westernConnection{false};

    //Connects the bridge to any surrounding bridges
    void connect();

    //Disconnects the bridge from all surrounding bridges; used just before the bridge is deleted
    void disconnect();

protected:
    int hp;
    Orientation orientation;
};

