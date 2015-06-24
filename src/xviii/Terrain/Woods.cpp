#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Woods.h"

#include "xviii/Units/UnitTile.h"

Woods::Woods(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_terrainLoader, _world, tm, TextureManager::Terrain::WOODS, TerrainType::WOODS, _pos)
{
}

std::string Woods::callTerrainAttack(UnitTile* unit, int distance){
    return(unit->terrainAttack(this, distance));
}
