#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/TBridge.h"

#include "xviii/Core/World.h"


TBridge::TBridge(World& _world, sf::Vector2f _pos) :
Bridge(_world, _pos)
{
    //If we don't manually change this, TBridge's type will default to Bridge's, which is TerrainType::BRIDGE
    //It's a hacky solution but rather than change all terrain constructors just for this case, I opted for this
    //instead
    terrainType = TerrainType::TBRIDGE;
    //Same for health initialisation
    hp = 3;
    hpText.setString(std::to_string(hp));
}

void TBridge::takeDamage(int dmg){
    hp -= dmg;
    hpText.setString(std::to_string(hp));

    if(hp < 0.9){
        //When "untoggling" a bridge, the second argument doesn't really matter
        world.toggleTBridge(this, orientation);
    }
};

void TBridge::flip(Orientation _or){
    if(_or == Orientation::HORIZONTAL){
        orientation = Orientation::HORIZONTAL;
        sprite.setTextureRect(world.masterManager.textureManager->getSprite(TextureManager::Terrain::TBRIDGE_HOR).getTextureRect());
    }
    else if(_or == Orientation::VERTICAL){
        orientation = Orientation::VERTICAL;
        sprite.setTextureRect(world.masterManager.textureManager->getSprite(TextureManager::Terrain::TBRIDGE_VER).getTextureRect());
    }

    refreshVertexArray();
}


std::string TBridge::callTerrainAttack(UnitTile* unit, int distance){
    return(unit->terrainAttack(this, distance));
}
