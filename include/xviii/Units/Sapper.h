#pragma once

#include "xviii/Units/Infantry.h"

class Sapper : public Infantry
{
public:
	Sapper(World& _world, Player* _belongsToPlayer, TextureManager::Unit _texture, std::string _name, UnitType _type, UnitFamily _familyType, Direction _dir);
	virtual std::string terrainAttack(Water* water, int distance);
};

