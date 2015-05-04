#include "stdafx.h"
#include "ArtGuard.h"


ArtGuard::ArtGuard(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType, UnitType uType) :
Infantry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, texType, uType)
{
	mov = maxMov;
	hp = maxhp;
}

std::string ArtGuard::rangedAttack(UnitTile* unit, int distance){
	std::uniform_int_distribution<int> distribution(1, 6);

	int thisRoll_int{distribution(mt19937)};

	float thisRoll = thisRoll_int;

	float damageDealt{0};

	float distanceModifier{0.5};

	modVector.emplace_back(Modifier::DISTANCE, distanceModifier);

	multRollByModifiers(thisRoll);
	damageDealt += thisRoll;
	unit->takeDamage(damageDealt, distance);

	mov = 0;
	this->updateStats();
	unit->updateStats();
	hasRangedAttacked = true;

	return attackReport(distance, this, unit, thisRoll_int, 0, damageDealt, 0);
}