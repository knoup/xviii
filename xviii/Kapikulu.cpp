#include "stdafx.h"
#include "Kapikulu.h"

#include "Player.h"

Kapikulu::Kapikulu(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Lancer(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::ARMLAN, UnitType::KAP)
{
	mov = maxMov;
	hp = maxhp;
}