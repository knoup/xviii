#include "stdafx.h"
#include "Arnauts.h"


Arnauts::Arnauts(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
LightInf(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::LINF, UnitType::ARN)
{
	mov = maxMov;
	hp = maxhp;
}