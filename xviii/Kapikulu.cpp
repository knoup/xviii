#include "stdafx.h"
#include "Kapikulu.h"

Kapikulu::Kapikulu(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Cuirassier(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::CUIR, UnitType::KAP)
{
	deploymentCost = 3;
	limit = 5;

	waterCrosser = true;
	mov = maxMov;
	hp = maxhp;
}

int Kapikulu::getMaxHp() const{
	return maxhp;
}

int Kapikulu::getMaxMov() const{
	return maxMov;
}

int Kapikulu::getMaxRange() const{
	return maxRange;
}