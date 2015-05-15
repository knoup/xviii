#include "stdafx.h"
#include "Gul.h"


Gul::Gul(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Lancer(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::ARMLAN, UnitType::GUL)
{
	mov = maxMov;
	hp = maxhp;
}