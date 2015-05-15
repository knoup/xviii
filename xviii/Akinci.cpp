#include "stdafx.h"
#include "Akinci.h"


Akinci::Akinci(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
LightCav(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::DRAG, UnitType::AKINCI)
{
	mov = maxMov;
	hp = maxhp;

	rangedAttackDistValues.clear();
	rangedAttackDistValues.emplace_back(3, 8, 0.5);
	rangedAttackDistValues.emplace_back(2, 2, 1);
}
