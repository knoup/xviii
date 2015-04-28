#include "stdafx.h"
#include "Dragoon.h"

static const float infFrontFlankModifier = 0.5;
static const float infSideFlankModifier = 0.5;
static const float infRearFlankModifier = 1;

static const float cavFrontFlankModifier = 1;
static const float cavSideFlankModifier = 2;
static const float cavRearFlankModifier = 2;

float Dragoon::getFlankModifier(UnitFamily _family, Modifier _flank) const{
	if (_family == UnitFamily::INF_FAMILY || _family == UnitFamily::HINF_FAMILY){
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

Dragoon::Dragoon(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType, UnitType uType):
Cavalry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, texType, uType)
{
	mov = maxMov;
	hp = maxhp;
}

std::string Dragoon::rangedAttack(UnitTile* unit, int distance){

	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;

	float damageDealt{0};

	float distanceModifier{1};

	if (distance >= 4 && distance <= 5){
		distanceModifier = 0.5;
	}
	else if (distance >= 3 && distance <= 4){
		distanceModifier = 1;
	}
	else if (distance == 2){
		distanceModifier = 1.5;
	}

	modVector.emplace_back(Modifier::DISTANCE, distanceModifier);

	multRollByModifiers(thisRoll);
	damageDealt = thisRoll;
	unit->takeDamage(damageDealt);

	mov = 0;
	this->updateStats();
	unit->updateStats();
	hasRangedAttacked = true;

	return attackReport(distance, this, unit, thisRoll_int, 0, damageDealt, 0);
}