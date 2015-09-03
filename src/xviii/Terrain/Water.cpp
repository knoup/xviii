#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Water.h"

#include "xviii/Core/World.h"
#include "xviii/Core/UnitLoader.h"

Water::Water(World& _world, sf::Vector2f _pos) :
TerrainTile(_world, TextureManager::Terrain::WATER, TerrainType::WATER, _pos)
{
}

std::string Water::callTerrainAttack(UnitTile* unit, int distance){
    return(unit->terrainAttack(this, distance));
}

bool Water::unitCanCrossHere(UnitTile* _unit){
   return (world.masterManager.unitLoader->customClasses.at(_unit->getUnitID()).waterCrosser);
}
