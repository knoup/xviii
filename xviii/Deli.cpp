#include "stdafx.h"
#include "Deli.h"

Deli::Deli(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
LightCav(_world, _mt19937, _belongsToPlayer, tm, fm,_dir, TextureManager::Unit::LCAV, UnitType::DELI)
{
	mov = maxMov;
	hp = maxhp;
}

void Deli::preMeleeAttack(UnitTile* unit, bool attacking){
	if (unit->getUnitFamilyType() == UnitFamily::CAV_FAMILY){
		this->modVector.emplace_back(Modifier::ADDITIONAL, 1);
	}
}