#pragma once

#include "xviii/Terrain/TerrainTile.h"

class Water : public TerrainTile
{
public:
	Water(World* _world, sf::Vector2f _pos);

	virtual std::string callTerrainAttack(UnitTile* unit, int distance);

	//Obviously, stopping in water is never a possibility
	inline virtual bool unitCanStopHere(UnitTile*){return false;};
	//canCrossHere() is also overloaded; it is identical to TerrainTile's version in every way
	//except that it will default to false if there is no water entry in unitIDMovementCapabilities
    virtual bool unitCanCrossHere(UnitTile* _unit);
};

