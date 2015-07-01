#pragma once

#include "xviii/Terrain/Bridge.h"

class TBridge : public Bridge
{
public:
	TBridge(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos);

    virtual void flip(Orientation _or);

    virtual std::string callTerrainAttack(UnitTile* unit, int distance);
};

