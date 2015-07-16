#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Urban.h"

#include "xviii/Units/UnitTile.h"

Urban::Urban(World& _world, sf::Vector2f _pos) :
TerrainTile(_world, TextureManager::Terrain::URBAN, TerrainType::URBAN, _pos)
{
}

std::string Urban::callTerrainAttack(UnitTile* unit, int distance){
    return(unit->terrainAttack(this, distance));
}
