#pragma once

#include "xviii/Units/UnitTile.h"

class Mortar : public UnitTile
{
public:
	Mortar(World& _world, Player* _belongsToPlayer, std::string _unitID, UnitType _type, UnitFamily _familyType, Direction _dir);

	//Overloaded for artillery and mortar due to the differing rules in what constitutes an obscured LoS; art/mor don't care if there are units
	//(both friendly and enemy) in the way. Simply calls UnitTile's function with canShootOverUnits being set to true
	virtual sf::Vector2i distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _rangedObstructionPresent, bool& _meleeObstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits = false, int coneWidth = 1);

	virtual std::string rotate(Direction _dir);

	virtual std::string meleeAttack(UnitTile* _unit);
};

