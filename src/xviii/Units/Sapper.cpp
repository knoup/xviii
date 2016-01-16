#include "xviii/Headers/stdafx.h"
#include "xviii/Units/Sapper.h"

#include "xviii/Core/World.h"

Sapper::Sapper(World* _world, Player* _belongsToPlayer, std::string _unitID, UnitType _type, UnitFamily _familyType, Direction _dir) :
Infantry(_world, _belongsToPlayer, _unitID, _type, _familyType, _dir)
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

        world->toggleTBridge(water, orientation);
        return {"Bridge built!"};
    }
}
