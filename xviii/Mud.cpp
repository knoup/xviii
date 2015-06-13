#include "stdafx.h"
#include "Mud.h"

#include "UnitTile.h"


Mud::Mud(World& _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_world, tm, TextureManager::Terrain::MUD, TerrainType::MUD, _pos)
{
}

void Mud::applyModifiers(UnitTile* _unit, int _distance, bool _attacking){

	//Melee modifiers
	//////////////////////////////////////////////
	if (_distance == 1){
		if (_unit->getUnitType() == UnitTile::UnitType::CAV){
			_unit->modVector.emplace_back(UnitTile::Modifier::TERRAIN, -2, true);
		}
		
		if (_attacking){
			 if (_unit->getUnitType() == UnitTile::UnitType::INF){
				_unit->modVector.emplace_back(UnitTile::Modifier::TERRAIN, -1, true);
			}
		}
	}


	//Ranged modifiers
	//////////////////////////////////////////////
	else if (_distance > 1){
		if (_attacking){
			_unit->modVector.emplace_back(UnitTile::Modifier::TERRAIN, -1, true);
		}
	}
}