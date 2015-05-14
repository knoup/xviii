#include "stdafx.h"
#include "Mutteferrika.h"


Mutteferrika::Mutteferrika(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Dragoon(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::DRAG, UnitType::MUT)
{
	mov = maxMov;
	hp = maxhp;
}