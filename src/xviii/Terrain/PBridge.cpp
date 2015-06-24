#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/PBridge.h"

#include "xviii/Core/World.h"


PBridge::PBridge(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos) :
TerrainTile(_terrainLoader, _world, tm, TextureManager::Terrain::PBRIDGE_VER, TerrainType::PBRIDGE, _pos),
hp{5}
{
}

void PBridge::takeDamage(int dmg){
    hp -= dmg;
    if(hp < 0.9){
        world.togglePBridge(this);
    }
};

std::string PBridge::callTerrainAttack(UnitTile* unit, int distance){
    return(unit->terrainAttack(this, distance));
}
