#include "stdafx.h"
#include "Woods.h"

#include "UnitTile.h"

Woods::Woods(World& _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_world, tm, TextureManager::Terrain::WOODS, TerrainType::WOODS, _pos)
{
}

void Woods::applyModifiers(UnitTile* _unit, int _distance, bool _attacking){

	/*TENTATIVE
	if (_unit->getUnitFamilyType() != UnitTile::UnitFamily::LINF_FAMILY
		||
		_unit->getUnitFamilyType() != UnitTile::UnitFamily::IRR_FAMILY){

		if (_distance > 1 && _attacking){
			_unit->modVector.emplace_back(UnitTile::Modifier::TERRAIN, -2, true);
		}

	}*/
}
