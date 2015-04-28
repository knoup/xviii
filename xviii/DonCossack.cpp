#include "stdafx.h"
#include "DonCossack.h"

DonCossack::DonCossack(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
LightCav(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::LCAV, UnitType::DON)
{
	deploymentCost = 3;
	limit = 5;

	waterCrosser = true;
	mov = maxMov;
	hp = maxhp;
}