#pragma once

#include "TerrainTile.h"

class Mud : public TerrainTile
{
public:
	Mud(World& _world, TextureManager& tm, sf::Vector2f _pos);
	virtual void applyModifiers(UnitTile* _unit, int _distance, bool _attacking);
};

