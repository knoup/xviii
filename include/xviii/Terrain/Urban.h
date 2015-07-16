#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Urban : public TerrainTile
{
public:
	Urban(World& _world, sf::Vector2f _pos);
	virtual std::string callTerrainAttack(UnitTile* unit, int distance);
};

