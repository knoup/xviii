#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Meadow : public TerrainTile
{
public:
	Meadow(World* _world, sf::Vector2f _pos);
	virtual std::string callTerrainAttack(UnitTile* unit, int distance);
};
