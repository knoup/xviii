#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Road.h"


Road::Road(World* _world, sf::Vector2f _pos) :
TerrainTile(_world, TextureManager::Terrain::ROAD, TerrainType::ROAD, _pos)
{
}

std::string Road::callTerrainAttack(UnitTile* unit, int distance){
    return(unit->terrainAttack(this, distance));
}
