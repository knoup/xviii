#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Water : public TerrainTile
{
public:
	Water(World& _world, sf::Vector2f _pos);

	virtual std::string callTerrainAttack(UnitTile* unit, int distance);
};

