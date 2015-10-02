#pragma once

#include "xviii/Units/UnitTile.h"

class Artillery : public UnitTile
{
public:
	Artillery(World& _world, Player* _belongsToPlayer, std::string _unitID, UnitType _type, UnitFamily _familyType, Direction _dir);

	virtual std::string rotate(Direction _dir);

	virtual std::string meleeAttack(UnitTile* _unit);
};

