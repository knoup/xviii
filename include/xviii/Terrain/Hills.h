#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Hills : public TerrainTile
{
public:
	Hills(World* _world, sf::Vector2f _pos);
	virtual std::string callTerrainAttack(UnitTile* unit, int distance);
};

