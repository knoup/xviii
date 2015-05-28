#include "stdafx.h"
#include "KurdishInf.h"


KurdishInf::KurdishInf(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
LightInf(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::LINF, UnitType::KINF)
{
	mov = maxMov;
	hp = maxhp;

	rangedAttackDistValues.clear();
	rangedAttackDistValues.emplace_back(3, 8, 0.5);
	rangedAttackDistValues.emplace_back(2, 2, 1);

	skirmish = true;
}