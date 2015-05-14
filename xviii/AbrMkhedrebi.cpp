#include "stdafx.h"
#include "AbrMkhedrebi.h"


AbrMkhedrebi::AbrMkhedrebi(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Dragoon(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::DRAG, UnitType::AMKH)
{
	mov = maxMov;
	hp = maxhp;
}