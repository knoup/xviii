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

void PBridge::flip(Orientation _or){
    if(_or == Orientation::HORIZONTAL){
        sprite = world.tm.getSprite(TextureManager::Terrain::PBRIDGE_HOR);
    }
    else if(_or == Orientation::VERTICAL){
        sprite = world.tm.getSprite(TextureManager::Terrain::PBRIDGE_VER);
    }
}

std::string PBridge::callTerrainAttack(UnitTile* unit, int distance){
    return(unit->terrainAttack(this, distance));
}
