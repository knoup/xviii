#include "stdafx.h"
#include "Azaps.h"


Azaps::Azaps(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType, UnitType uType) :
Infantry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, texType, uType)
{
	mov = maxMov;
	hp = maxhp;

	rangedAttackDistValues.clear();
	rangedAttackDistValues.emplace_back(3, 6, 0.5);
	rangedAttackDistValues.emplace_back(2, 2, 1);
}