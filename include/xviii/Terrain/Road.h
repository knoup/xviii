#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Road : public TerrainTile
{
public:
	Road(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos);
	virtual std::string callTerrainAttack(UnitTile* unit, int distance);
};

