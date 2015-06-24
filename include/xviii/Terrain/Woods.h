#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Woods : public TerrainTile
{
public:
	Woods(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos);
	virtual std::string callTerrainAttack(UnitTile* unit, int distance);
};

