#include "stdafx.h"
#include "Artillery.h"

#include "Player.h"

Artillery::Artillery(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
UnitTile(_world, _mt19937, _belongsToPlayer, tm, fm, TextureManager::Unit::ART, UnitType::ART, _dir)
{
	deploymentCost = 3;
	limit = 5;

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

std::string Artillery::attack(UnitTile* _unit, int distance, UnitTile::Modifier flank){
	return _unit->attack(this, distance, flank);
}

std::string Artillery::attack(Infantry* inf, int distance, UnitTile::Modifier flank){
	return rangedAttack(inf, distance);
}

std::string Artillery::attack(Cavalry* cav, int distance, UnitTile::Modifier flank){
	return rangedAttack(cav, distance);
}

std::string Artillery::attack(Cuirassier* cuir, int distance, UnitTile::Modifier flank){
	return rangedAttack(cuir, distance);
}

std::string Artillery::attack(Dragoon* drag, int distance, UnitTile::Modifier flank){
	return rangedAttack(drag, distance);
}

std::string Artillery::attack(LightCav* lcav, int distance, UnitTile::Modifier flank){
	return rangedAttack(lcav, distance);
}

std::string Artillery::attack(Artillery* art, int distance, UnitTile::Modifier flank){
	return rangedAttack(art, distance);
}

std::string Artillery::attack(Mortar* mor, int distance, UnitTile::Modifier flank){
	return rangedAttack(mor, distance);
}

std::string Artillery::attack(General* gen, int distance, UnitTile::Modifier flank){
	return rangedAttack(gen, distance);
}

std::string Artillery::rangedAttack(UnitTile* unit, int distance){
	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;

	float damageDealt{0};

	if (distance > maxRange){
		return outOfRange();
	}

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