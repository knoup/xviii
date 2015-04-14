#include "stdafx.h"
#include "CrimeanCav.h"


static const float infFrontFlankModifier = 0.5;
static const float infSideFlankModifier = 0.5;
static const float infRearFlankModifier = 1;

static const float cavFrontFlankModifier = 1;
static const float cavSideFlankModifier = 2;
static const float cavRearFlankModifier = 2;

float CrimeanCav::getFlankModifier(UnitFamily _family, Modifier _flank) const{
	if (_family == UnitFamily::INF_FAMILY){
		switch (_flank){
		case Modifier::FRONT_FLANK:
			return infFrontFlankModifier;
			break;

		case Modifier::SIDE_FLANK:
			return infSideFlankModifier;
			break;

		case Modifier::REAR_FLANK:
			return infRearFlankModifier;
			break;
		}
	}

	else if (_family == UnitFamily::CAV_FAMILY){
		switch (_flank){
		case Modifier::FRONT_FLANK:
			return cavFrontFlankModifier;
			break;

		case Modifier::SIDE_FLANK:
			return cavSideFlankModifier;
			break;

		case Modifier::REAR_FLANK:
			return cavRearFlankModifier;
			break;
		}
	}

	//If unit is neither in INF or CAV family, return 0. Modifiers of 0 will be ignored.
	else{
		return 0;
	}
}

CrimeanCav::CrimeanCav(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Cavalry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::LCAV, UnitType::CRICAV)
{
	deploymentCost = 3;
	limit = 5;

	waterCrosser = true;
	mov = maxMov;
	hp = maxhp;
}

std::string CrimeanCav::rotate(UnitTile::Direction _dir){
	if (hasMeleeAttacked){
		return "Cannot rotate after melee attacking";
	}
	else if (hasRotated){
		return "Already rotated this turn";
	}
	else if (dir == _dir){
		return "Already facing " + UnitTile::dirToString();
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

	return "Successfully rotated to " + UnitTile::dirToString();
}


int CrimeanCav::getMaxHp() const{
	return maxhp;
}

int CrimeanCav::getMaxMov() const{
	return maxMov;
}

int CrimeanCav::getMaxRange() const{
	return maxRange;
}

std::string CrimeanCav::rangedAttack(UnitTile* unit, int distance){
	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;

	float damageDealt{0};

	float distanceModifier{1};

	if (distance >= 3 && distance <= 8){
		distanceModifier = 0.5;
	}
	else if (distance >= 1 && distance <= 2){
		distanceModifier = 1;
	}

	modVector.emplace_back(Modifier::DISTANCE, distanceModifier);

	multRollByModifiers(thisRoll);
	damageDealt = thisRoll;
	unit->takeDamage(damageDealt);

	mov = 0;
	this->updateStats();
	unit->updateStats();
	hasRangedAttacked = true;

	return attackReport(distance, this, unit, thisRoll_int, 0, damageDealt, 0, modVector, unit->modVector);
}