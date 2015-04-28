#include "stdafx.h"
#include "KhevMkhedrebi.h"

KhevMkhedrebi::KhevMkhedrebi(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Cuirassier(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::CUIR, UnitType::KMKH)
{
	mov = maxMov;
	hp = maxhp;
}