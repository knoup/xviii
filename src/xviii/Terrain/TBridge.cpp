#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/TBridge.h"

#include "xviii/Core/World.h"


TBridge::TBridge(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, sf::Vector2f _pos) :
Bridge(_terrainLoader, _world, tm, _pos)
{
}


void TBridge::flip(Orientation _or){
    if(_or == Orientation::HORIZONTAL){
        orientation = Orientation::HORIZONTAL;
        sprite.setTextureRect(world.tm.getSprite(TextureManager::Terrain::TBRIDGE_HOR).getTextureRect());
    }
    else if(_or == Orientation::VERTICAL){
        orientation = Orientation::VERTICAL;
        sprite.setTextureRect(world.tm.getSprite(TextureManager::Terrain::TBRIDGE_VER).getTextureRect());
    }

    refreshVertexArray();
}


std::string TBridge::callTerrainAttack(UnitTile* unit, int distance){
    return(unit->terrainAttack(this, distance));
}
