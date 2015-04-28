#include "stdafx.h"
#include "Dorunaby.h"


Dorunaby::Dorunaby(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType, UnitType uType) :
Infantry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::INF, UnitType::DOR)
{
	deploymentCost = 1;
	limit = 0;


	mov = maxMov;
	hp = maxhp;
}