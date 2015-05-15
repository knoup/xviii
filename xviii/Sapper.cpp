#include "stdafx.h"
#include "Sapper.h"


Sapper::Sapper(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Infantry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::SAP, UnitTile::UnitType::SAP)
{
	mov = maxMov;
	hp = maxhp;

	rangedAttackDistValues.clear();
	rangedAttackDistValues.emplace_back(3, 4, 0.5);
	rangedAttackDistValues.emplace_back(2, 2, 1);
}