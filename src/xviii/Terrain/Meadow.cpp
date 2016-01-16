#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Meadow.h"


Meadow::Meadow(World* _world, sf::Vector2f _pos) :
TerrainTile(_world, TextureManager::Terrain::MEADOW, TerrainType::MEADOW, _pos)
{
}

std::string Meadow::callTerrainAttack(UnitTile* unit, int distance){
    return(unit->terrainAttack(this, distance));
}
