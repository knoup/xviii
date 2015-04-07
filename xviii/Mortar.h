#pragma once

#include "UnitTile.h"


class Mortar : public UnitTile
{
public:
	Mortar(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir);

	//Overloaded for artillery and mortar due to the differing rules in what constitutes an obscured LoS; art/mor don't care if there are units 
	//(both friendly and enemy) in the way. Simply calls UnitTile's function with canShootOverUnits being set to true
	virtual int distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _obstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits = false, int coneWidth = 1);

	virtual std::string rotate(Direction _dir);
	virtual std::string interactWithFriendly(UnitTile* _unit);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

	virtual std::string meleeAttack(UnitTile* _unit);

	virtual std::string rangedAttack(UnitTile* unit, int distance);

private:
	static const int maxhp{2};
	static const int maxMov{0};
	static const int maxRange{15};
};

