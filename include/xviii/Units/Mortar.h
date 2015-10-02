#pragma once

#include "xviii/Units/UnitTile.h"

class Mortar : public UnitTile
{
public:
	Mortar(World& _world, Player* _belongsToPlayer, std::string _unitID, UnitType _type, UnitFamily _familyType, Direction _dir);

	virtual std::string rotate(Direction _dir);

	virtual std::string meleeAttack(UnitTile* _unit);
};

