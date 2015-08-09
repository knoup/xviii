#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Water : public TerrainTile
{
public:
	Water(World& _world, sf::Vector2f _pos);

	virtual std::string callTerrainAttack(UnitTile* unit, int distance);
	inline virtual bool unitCanStopHere(UnitTile* _unit){return false;};
    inline virtual bool unitCanCrossHere(UnitTile* _unit){return false;};
};

