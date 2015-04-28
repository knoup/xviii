#include "stdafx.h"
#include "AbrMkhedrebi.h"


AbrMkhedrebi::AbrMkhedrebi(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Dragoon(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::DRAG, UnitType::AMKH)
{
	deploymentCost = 3;
	limit = 5;

	waterCrosser = true;
	mov = maxMov;
	hp = maxhp;
}

std::string AbrMkhedrebi::rotate(UnitTile::Direction _dir){
	if (hasMeleeAttacked){
		return NO_ROTATE_AFTER_MELEE;
	}
	else if (hasRotated){
		return ALREADY_ROTATED;
	}
	else if (dir == _dir){
		return ALREADY_FACING + UnitTile::dirToString();
	}
	//If it was a full rotation
	if (_dir == opposite(dir)){
		//Due to the rule that cav cannot attack after full rotation, and to simplify matters, I set the
		//hasAttacked variables to true here
		hasMeleeAttacked = true;
		hasRangedAttacked = true;
		mov = 2;
	}

	hasRotated = true;
	dir = _dir;
	updateStats();

	return SUCCESSFUL_ROTATION + UnitTile::dirToString();
}