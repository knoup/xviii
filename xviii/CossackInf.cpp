#include "stdafx.h"
#include "CossackInf.h"


CossackInf::CossackInf(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Infantry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::INF, UnitTile::UnitType::COSINF)
{
	deploymentCost = 1;
	limit = 0;

	waterCrosser = false;
	mov = maxMov;
	hp = maxhp;
}

int CossackInf::getMaxHp() const{
	return maxhp;
}

int CossackInf::getMaxMov() const{
	return maxMov;
}

int CossackInf::getMaxRange() const{
	return maxRange;
}