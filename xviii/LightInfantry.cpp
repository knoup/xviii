#include "stdafx.h"
#include "LightInfantry.h"


LightInfantry::LightInfantry(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Infantry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::LINF, UnitTile::UnitType::LINF)
{
	deploymentCost = 1;
	limit = 0;

	waterCrosser = true;
	mov = maxMov;
	hp = maxhp;
}

int LightInfantry::getMaxHp() const{
	return maxhp;
}

int LightInfantry::getMaxMov() const{
	return maxMov;
}

int LightInfantry::getMaxRange() const{
	return maxRange;
}

std::string LightInfantry::rangedAttack(UnitTile* unit, int distance){
	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;

	float damageDealt{0};

	float distanceModifier{1};

	if (distance >= 7 && distance <= 8){
		distanceModifier = 0.5;
	}
	else if (distance >= 3 && distance <= 6){
		distanceModifier = 1;
	}
	else if (distance >= 2 && distance <= 1){
		distanceModifier = 1.5;
	}

	modVector.emplace_back(Modifier::DISTANCE, distanceModifier);

	multRollByModifiers(thisRoll);
	damageDealt = thisRoll;
	unit->takeDamage(damageDealt);

	mov = 0;
	this->updateStats();
	unit->updateStats();
	hasAttacked = true;

	return attackReport(distance, this, unit, thisRoll_int, 0, damageDealt, 0, modVector, unit->modVector);
}