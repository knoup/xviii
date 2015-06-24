#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Slopes.h"


Slopes::Slopes(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_terrainLoader, _world, tm, TextureManager::Terrain::SLOPES, TerrainType::SLOPES, _pos)
{
}

std::string Slopes::callTerrainAttack(UnitTile* unit, int distance){
    return(unit->terrainAttack(this, distance));
}
