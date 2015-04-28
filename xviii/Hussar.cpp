#include "stdafx.h"
#include "Hussar.h"

Hussar::Hussar(World& _world, std::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, UnitTile::Direction _dir) :
LightCav(_world, _mt19937, _belongsToPlayer, tm, fm, _dir, TextureManager::Unit::LCAV, UnitType::HUS)
{
	mov = maxMov;
	hp = maxhp;
}

void Hussar::preAttack(UnitTile* unit, bool attacking){
	if (attacking){
		this->modVector.emplace_back(Modifier::ATK, 1);
	}
	if (unit->getUnitFamilyType() == UnitFamily::LINF_FAMILY){
		this->modVector.emplace_back(Modifier::ADDITIONAL, 1);
	}
}