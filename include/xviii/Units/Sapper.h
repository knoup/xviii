#pragma once

#include "xviii/Units/Infantry.h"

class Sapper : public Infantry
{
public:
	Sapper(World* _world, Player* _belongsToPlayer, std::string _unitID, UnitType _type, UnitFamily _familyType, Direction _dir);
	virtual std::string terrainAttack(Water* water, int distance);
};

