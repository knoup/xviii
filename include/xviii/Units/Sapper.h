#pragma once

#include "xviii/Units/Infantry.h"

class Sapper : public Infantry
{
public:
	Sapper(UnitLoader& _unitLoader, World& _world, boost::random::mt19937&, Player* _belongsToPlayer, TextureManager& _tm, FontManager& _fm, TextureManager::Unit _texture, std::string _name, UnitType _type, UnitFamily _familyType, Direction _dir);
	virtual std::string terrainAttack(Water* water, int distance);
};

