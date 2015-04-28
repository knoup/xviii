#include "stdafx.h"
#include "Janissary.h"

Janissary::Janissary(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Grenadier(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::GRE, UnitTile::UnitType::JAN)
{
	deploymentCost = 1;
	limit = 0;

	
	mov = maxMov;
	hp = maxhp;
}