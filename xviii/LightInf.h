#pragma once

#include "Infantry.h"

class LightInf : public Infantry
{
public:
	LightInf(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const; 
	
	//Overloaded for the cone width of 3
	virtual int distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _obstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits, int coneWidth);

	virtual std::string rangedAttack(UnitTile* unit, int distance);

private:
	static const int maxhp{9};
	static const int maxMov{9};
	static const int maxRange{8};
};

