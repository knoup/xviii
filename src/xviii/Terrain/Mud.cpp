#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Mud.h"

#include "xviii/Units/UnitTile.h"


Mud::Mud(World& _world, sf::Vector2f _pos) :
TerrainTile(_world, TextureManager::Terrain::MUD, TerrainType::MUD, _pos)
{
}

std::string Mud::callTerrainAttack(UnitTile* unit, int distance){
    return(unit->terrainAttack(this, distance));
}
