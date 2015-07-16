#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Hills.h"


Hills::Hills(World& _world, sf::Vector2f _pos) :
TerrainTile(_world, TextureManager::Terrain::HILLS, TerrainType::HILLS, _pos)
{
}

std::string Hills::callTerrainAttack(UnitTile* unit, int distance){
    return(unit->terrainAttack(this, distance));
}
