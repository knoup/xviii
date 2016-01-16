#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Woods.h"

#include "xviii/Units/UnitTile.h"

Woods::Woods(World* _world, sf::Vector2f _pos) :
TerrainTile(_world, TextureManager::Terrain::WOODS, TerrainType::WOODS, _pos)
{
}

std::string Woods::callTerrainAttack(UnitTile* unit, int distance){
    return(unit->terrainAttack(this, distance));
}
