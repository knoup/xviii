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
	if (hasRotated){
		return "Cannot rotate any more";
	}
	else if (dir == _dir){
		return "Already facing " + UnitTile::dirToString();
	}

	hasRotated = true;
	dir = _dir;
	updateStats();

	return "Successfully rotated to " + UnitTile::dirToString();
}

std::string Artillery::interactWithFriendly(UnitTile* _unit){
	return{};
}

int Artillery::getMaxHp() const{
	return maxhp;
}

int Artillery::getMaxMov() const{
	return maxMov;
}

int Artillery::getMaxRange() const{
	return maxRange;
}

int Artillery::distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _obstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits, int coneWidth){
	return UnitTile::distanceFrom(_terrain, _validMovDirection, _validAttackDirection, _obstructionPresent, _inMovementRange, _inRangedAttackRange, true, 3);
}

std::string Artillery::meleeAttack(UnitTile* _unit){
	//rangedAttack() is called in UnitTile's initial meleeAttack(UnitTile*) function;
	//we don't need to do anything here, since this unit cannot melee
	return{};
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
	hasAttacked = true;

	return attackReport(distance, this, unit, thisRoll_int, 0, damageDealt, 0, modVector, unit->modVector);
}