#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Woods : public TerrainTile
{
public:
	Woods(World& _world, sf::Vector2f _pos);
	virtual std::string callTerrainAttack(UnitTile* unit, int distance);
};

