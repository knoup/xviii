#include "stdafx.h"
#include "Boyar.h"

#include "Player.h"

Boyar::Boyar(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Lancer(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::LAN, UnitType::BOY)
{
	mov = maxMov;
	hp = maxhp;
}
