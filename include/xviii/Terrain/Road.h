#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Road : public TerrainTile
{
public:
	Road(World& _world, sf::Vector2f _pos);
	virtual std::string callTerrainAttack(UnitTile* unit, int distance);
};

