#include "stdafx.h"
#include "KudzeKaci.h"


KudzeKaci::KudzeKaci(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) : 
LightInf(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::LINF, UnitType::KACI)
{
	mov = maxMov;
	hp = maxhp;

	rangedAttackDistValues.clear();
	rangedAttackDistValues.emplace_back(4, 7, 0.5);
	rangedAttackDistValues.emplace_back(3, 4, 1);
	rangedAttackDistValues.emplace_back(2, 2, 1.5);
}