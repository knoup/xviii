#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Slopes : public TerrainTile
{
public:
	Slopes(World& _world, sf::Vector2f _pos);
	virtual std::string callTerrainAttack(UnitTile* unit, int distance);
};

