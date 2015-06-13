#include "stdafx.h"
#include "Woods.h"

#include "UnitTile.h"

Woods::Woods(World& _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_world, tm, TextureManager::Terrain::WOODS, TerrainType::WOODS, _pos)
{
}

void Woods::applyModifiers(UnitTile* _unit, int _distance, bool _attacking){
	
	//Melee modifiers
	//////////////////////////////////////////////
	if (_distance == 1){
		if (_unit->getUnitType() == UnitTile::UnitType::CAV){
			_unit->modVector.emplace_back(UnitTile::Modifier::TERRAIN, -2, true);
		}
	}

	//Ranged modifiers
	//////////////////////////////////////////////
	else if (_distance >= 1){
		if (_attacking){
			if (_unit->getUnitFamilyType() != UnitTile::UnitFamily::LINF_FAMILY
				||
				_unit->getUnitFamilyType() != UnitTile::UnitFamily::IRR_FAMILY){

					_unit->modVector.emplace_back(UnitTile::Modifier::TERRAIN, -2, true);
			}
		}
	}
}
