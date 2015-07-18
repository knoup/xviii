#pragma once

#include "xviii/Units/UnitTile.h"

class Infantry : public UnitTile
{
public:
	Infantry(World& _world, Player* _belongsToPlayer, TextureManager::Unit _texture, std::string _name, UnitType _type, UnitFamily _familyType, Direction _dir);

	//Infantry's moveTo is overloaded because of the rule: INF can either MOVE, PARTIALLY ROTATE, or FULLY ROTATE in addition to attacking.
	std::string moveTo(TerrainTile* terrainTile);

	virtual std::string rotate(Direction _dir);

	virtual std::string meleeAttack(UnitTile* _unit);

	virtual std::string meleeAttack(Infantry* inf);
	virtual std::string meleeAttack(Cavalry* cav);
	virtual std::string meleeAttack(Artillery* art);
	virtual std::string meleeAttack(Mortar* mor);
};

