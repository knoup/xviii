#include "stdafx.h"
#include "Dorunaby.h"


Dorunaby::Dorunaby(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType, UnitType uType) :
Infantry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::GRE, UnitType::DOR)
{
	mov = maxMov;
	hp = maxhp;
}