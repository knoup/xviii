#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Slopes.h"


Slopes::Slopes(World& _world, sf::Vector2f _pos) :
TerrainTile(_world, TextureManager::Terrain::SLOPES, TerrainType::SLOPES, _pos)
{
}

std::string Slopes::callTerrainAttack(UnitTile* unit, int distance){
    return(unit->terrainAttack(this, distance));
}
