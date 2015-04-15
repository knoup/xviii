#include "stdafx.h"
#include "OttoInf.h"


OttoInf::OttoInf(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
Infantry(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::INF, UnitTile::UnitType::OINF)
{
	deploymentCost = 1;
	limit = 0;

	waterCrosser = false;
	mov = maxMov;
	hp = maxhp;
}

int OttoInf::getMaxHp() const{
	return maxhp;
}

int OttoInf::getMaxMov() const{
	return maxMov;
}

int OttoInf::getMaxRange() const{
	return maxRange;
}

void OttoInf::preAttack(UnitTile* unit, bool attacking){
	if (unit->getUnitFamilyType() == UnitFamily::CAV_FAMILY){
		this->modVector.emplace_back(Modifier::ADDITIONAL, -1);
	}
}