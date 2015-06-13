#include "stdafx.h"
#include "Mud.h"

#include "UnitTile.h"


Mud::Mud(World& _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_world, tm, TextureManager::Terrain::MUD, TerrainType::MUD, _pos)
{
}

void Mud::applyModifiers(UnitTile* _unit, int _distance, bool _attacking){

	/* TENTATIVE
	if (_unit->getUnitType() == UnitTile::UnitType::CAV){
		if (_distance == 1){
			_unit->modVector.emplace_back(UnitTile::Modifier::TERRAIN, -2, true);
		}
	}

	else if (_unit->getUnitType() == UnitTile::UnitType::INF){
		if (_attacking && _distance == 1){
			_unit->modVector.emplace_back(UnitTile::Modifier::TERRAIN, -1, true);
		}
	}*/
}