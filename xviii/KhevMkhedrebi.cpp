#include "stdafx.h"
#include "KhevMkhedrebi.h"

KhevMkhedrebi::KhevMkhedrebi(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Cuirassier(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::CUIR, UnitType::MKH)
{
	deploymentCost = 3;
	limit = 5;

	waterCrosser = true;
	mov = maxMov;
	hp = maxhp;
}

int KhevMkhedrebi::getMaxHp() const{
	return maxhp;
}

int KhevMkhedrebi::getMaxMov() const{
	return maxMov;
}

int KhevMkhedrebi::getMaxRange() const{
	return maxRange;
}