#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Mud.h"

#include "xviii/Units/UnitTile.h"


Mud::Mud(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_terrainLoader, _world, tm, TextureManager::Terrain::MUD, TerrainType::MUD, _pos)
{
}

std::string Mud::callTerrainAttack(UnitTile* unit, int distance){
    return(unit->terrainAttack(this, distance));
}
