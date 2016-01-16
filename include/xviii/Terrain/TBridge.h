#pragma once

#include "xviii/Terrain/Bridge.h"

class TBridge : public Bridge
{
public:
	TBridge(World* _world, sf::Vector2f _pos);

    virtual void takeDamage(int dmg);

    virtual void flip(Orientation _or);

    virtual std::string callTerrainAttack(UnitTile* unit, int distance);

    //If called with argument true, set the tile's sprite to the proper bridge tile.
    //Otherwise, set it to water.
    void makeBridgeVisible(bool _value);
    bool visible{true};
};

