#include "stdafx.h"
#include "Deli.h"

Deli::Deli(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
LightCav(_world, _mt19937, _belongsToPlayer, tm, fm,_dir, TextureManager::Unit::LCAV, UnitType::DELI)
{
	deploymentCost = 3;
	limit = 5;

	waterCrosser = true;
	mov = maxMov;
	hp = maxhp;
}

int Deli::getMaxHp() const{
	return maxhp;
}

int Deli::getMaxMov() const{
	return maxMov;
}

int Deli::getMaxRange() const{
	return maxRange;
}

void Deli::preAttack(UnitTile* unit, bool attacking){
	if (unit->getUnitFamilyType() == UnitFamily::CAV_FAMILY){
		this->modVector.emplace_back(Modifier::ADDITIONAL, 1);
	}
}