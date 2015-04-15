#include "stdafx.h"
#include "Artillery.h"


Artillery::Artillery(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
UnitTile(_world, _mt19937, _belongsToPlayer, tm, fm, TextureManager::Unit::ART, UnitType::ART, UnitFamily::ART_FAMILY, _dir)
{
	deploymentCost = 3;
	limit = 5;
	
	waterCrosser = false;
	mov = maxMov;
	hp = maxhp;
}

std::string Artillery::rotate(UnitTile::Direction _dir){
	if (hasRangedAttacked){
		return NO_ROTATE_AFTER_ATTACK;
	}
	else if (hasRotated){
		return ALREADY_ROTATED;
	}
	else if (dir == _dir){
		return ALREADY_FACING + UnitTile::dirToString();
	}

	hasRotated = true;
	dir = _dir;
	updateStats();

	return SUCCESSFUL_ROTATION + UnitTile::dirToString();
}

std::string Artillery::interactWithFriendly(UnitTile* _unit){
	return{};
}

int Artillery::distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _obstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits, int coneWidth){
	return UnitTile::distanceFrom(_terrain, _validMovDirection, _validAttackDirection, _obstructionPresent, _inMovementRange, _inRangedAttackRange, true, 5);
}

std::string Artillery::meleeAttack(UnitTile* _unit){
	return _unit->meleeAttack(this);
}

std::string Artillery::rangedAttack(UnitTile* unit, int distance){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;

	float damageDealt{0};

	if (thisRoll_int >= 4 && thisRoll_int <= 6){
		if (distance <= 20 && distance >= 10){
			damageDealt = 2;
		}
		else if (distance <= 9){
			damageDealt = 4;
		}

		unit->takeDamage(damageDealt);
	}

	mov = 0;
	this->updateStats();
	unit->updateStats();
	hasRangedAttacked = true;

	return attackReport(distance, this, unit, thisRoll_int, 0, damageDealt, 0);
}