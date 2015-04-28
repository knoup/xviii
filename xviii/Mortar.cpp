#include "stdafx.h"
#include "Mortar.h"

Mortar::Mortar(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
UnitTile(_world, _mt19937, _belongsToPlayer, tm, fm, TextureManager::Unit::MOR, UnitType::MOR, UnitFamily::ART_FAMILY, _dir)
{
	deploymentCost = 2;
	limit = 5;

	waterCrosser = false;
	mov = maxMov;
	hp = maxhp;
}


std::string Mortar::rotate(UnitTile::Direction _dir){
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

std::string Mortar::interactWithFriendly(UnitTile* _unit){
	return{};
}

int Mortar::distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _obstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits, int coneWidth){
	return UnitTile::distanceFrom(_terrain, _validMovDirection, _validAttackDirection, _obstructionPresent, _inMovementRange, _inRangedAttackRange, true, 5);
}

std::string Mortar::meleeAttack(UnitTile* _unit){
	return _unit->meleeAttack(this);
}

std::string Mortar::rangedAttack(UnitTile* unit, int distance){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;

	float damageDealt{0};

	multRollByModifiers(thisRoll);

	if (thisRoll_int >= 4 && thisRoll_int <= 6){
		damageDealt = 3;

		unit->takeDamage(damageDealt);
	}

	mov = 0;
	this->updateStats();
	unit->updateStats();
	hasRangedAttacked = true;

	return attackReport(distance, this, unit, thisRoll_int, 0, damageDealt, 0);
}