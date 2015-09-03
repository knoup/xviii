#include "xviii/Headers/stdafx.h"
#include "xviii/Units/Mortar.h"

#include "xviii/Terrain/TerrainTile.h"

Mortar::Mortar(World& _world, Player* _belongsToPlayer, std::string _unitID, UnitType _type, UnitFamily _familyType, Direction _dir) :
UnitTile(_world, _belongsToPlayer, _unitID, _type, _familyType, _dir)
{
}


std::string Mortar::rotate(UnitTile::Direction _dir){
	if (getSquareFormationActive() && hasSquareFormationAbility()){
		return SF_ACTIVE;
	}

	bool oppositeRotation{_dir == opposite(dir)};

	if (hasRangedAttacked){
		return NO_ROTATE_AFTER_ATTACK;
	}
	else if (getHasAnyRotated()){
		return ALREADY_ROTATED;
	}
	else if (dir == _dir){
		return ALREADY_FACING + UnitTile::dirToString();
	}

	if (oppositeRotation){
		hasFullRotated = true;
	}
	else{
		hasPartialRotated = true;
	}

	dir = _dir;
	updateStats();

	return SUCCESSFUL_ROTATION + UnitTile::dirToString();
}

sf::Vector2i Mortar::distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _rangedObstructionPresent, bool& _meleeObstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits, int coneWidth){
	return UnitTile::distanceFrom(_terrain, _validMovDirection, _validAttackDirection, _rangedObstructionPresent, _meleeObstructionPresent, _inMovementRange, _inRangedAttackRange, true, 5);
}

std::string Mortar::meleeAttack(UnitTile* _unit){
	return _unit->meleeAttack(this);
}
