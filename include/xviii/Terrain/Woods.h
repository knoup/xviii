#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Woods : public TerrainTile
{
public:
	Woods(World& _world, TextureManager& tm, sf::Vector2f _pos);
	virtual void applyModifiers(UnitTile* _unit, int _distance, bool _attacking);
};

