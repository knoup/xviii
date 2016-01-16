#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Mud : public TerrainTile
{
public:
	Mud(World* _world, sf::Vector2f _pos);
	virtual std::string callTerrainAttack(UnitTile* unit, int distance);
};

