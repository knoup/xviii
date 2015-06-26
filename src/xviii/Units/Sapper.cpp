#include "xviii/Headers/stdafx.h"
#include "xviii/Units/Sapper.h"

#include "xviii/Core/World.h"

Sapper::Sapper(UnitLoader& _unitLoader, World& _world, boost::random::mt19937& _mt19937, Player* _belongsToPlayer, TextureManager& _tm, FontManager& _fm, TextureManager::Unit _texture, std::string _name, UnitType _type, UnitFamily _familyType, Direction _dir) :
Infantry(_unitLoader, _world, _mt19937, _belongsToPlayer, _tm, _fm, _texture, _name, _type, _familyType, _dir)
{
}

std::string Sapper::terrainAttack(Water* water, int distance){
    if(distance > 1){
        return {"Must be adjacent to water tile to construct bridge"};
    }
    else{
        TerrainTile::Orientation orientation;

        if(dir == Direction::N || dir == Direction::S){
            orientation = TerrainTile::Orientation::VERTICAL;
        }
        else{
           orientation = TerrainTile::Orientation::HORIZONTAL;
        }

        world.toggleTBridge(water, orientation);
        return {"Bridge built!"};
    }
}
