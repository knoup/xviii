#include "stdafx.h"
#include "KhevKveitebi.h"


KhevKveitebi::KhevKveitebi(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) : 
FootGuard(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::HINF, UnitTile::UnitType::KKV)
{
	deploymentCost = 1;
	limit = 0;

	waterCrosser = false;
	mov = maxMov;
	hp = maxhp;
}

void KhevKveitebi::preAttack(UnitTile* unit, bool attacking){
	if (unit->getUnitFamilyType() == UnitFamily::CAV_FAMILY){
		this->modVector.emplace_back(Modifier::ADDITIONAL, -1);
	}
}