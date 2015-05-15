#include "stdafx.h"
#include "PitsisKatsebi.h"

PitsisKatsebi::PitsisKatsebi(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Cuirassier(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::CAV, UnitType::PIT)
{
	mov = maxMov;
	hp = maxhp;

	rangedAttackDistValues.clear();
	rangedAttackDistValues.emplace_back(4, 5, 0.5);
	rangedAttackDistValues.emplace_back(3, 4, 1);
	rangedAttackDistValues.emplace_back(2, 2, 1.5);
}