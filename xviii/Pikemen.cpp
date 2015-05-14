#include "stdafx.h"
#include "Pikemen.h"


Pikemen::Pikemen(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir, TextureManager::Unit texType, UnitType uType) :
Infantry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, texType, uType)
{
	mov = maxMov;
	hp = maxhp;
}

void Pikemen::preMeleeAttack(UnitTile* unit, bool attacking){
	if (unit->getUnitFamilyType() == UnitFamily::CAV_FAMILY){
		this->modVector.emplace_back(Modifier::ADDITIONAL, 2);
	}
	
	if (attacking){
		this->modVector.emplace_back(Modifier::ADDITIONAL, -1);
	}
	else{
		this->modVector.emplace_back(Modifier::ADDITIONAL, 1);
	}
}