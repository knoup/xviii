#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/BridgeAnt.h"


BridgeAnt::BridgeAnt(TerrainLoader& _terrainLoader, World& _world, int _lifetime) :
Ant{_terrainLoader, _world, TerrainTile::TerrainType::PBRIDGE, _lifetime}
{
}

void BridgeAnt::crawl(){
    //BridgeAnt is unique in that it doesn't really care about its lifetime; it simply gives every
    //water tile a 3% chance of turning into a bridge.

    for(auto& terrainTile : world->terrainLayer){
        if(terrainTile->getTerrainType() == TerrainTile::TerrainType::WATER){
            //Simulate a % chance of a bridge spawning..

            boost::random::uniform_int_distribution<int> chance(1, 100);
            int randomRoll{chance(world->mt19937)};

            if(!(randomRoll <= 10)){
                continue;
            }

            sf::Vector2i currentPos = terrainTile->getCartesianPos();
            world->togglePBridge(terrainTile.get());
            int index = world->indexAtCartesianPos(currentPos);

            //Make sure bridges are properly connected:
            if(world->terrainLayer[index]->getTerrainType() == TerrainTile::TerrainType::PBRIDGE){
                bool northernLandConnection{true};
                bool southernLandConnection{true};
                bool easternLandConnection{true};
                bool westernLandConnection{true};

                sf::Vector2i northIndex = currentPos;
                northIndex.y -= 1;
                TerrainTile* northTile = world->terrainAtCartesianPos(northIndex);

                sf::Vector2i southIndex = currentPos;
                southIndex.y += 1;
                TerrainTile* southTile = world->terrainAtCartesianPos(southIndex);

                sf::Vector2i eastIndex = currentPos;
                eastIndex.x += 1;
                TerrainTile* eastTile = world->terrainAtCartesianPos(eastIndex);

                sf::Vector2i westIndex = currentPos;
                westIndex.x -= 1;
                TerrainTile* westTile = world->terrainAtCartesianPos(westIndex);

                if(northTile != nullptr){
                    if(northTile->getTerrainType() == TerrainTile::TerrainType::WATER){
                        northernLandConnection = false;
                    }
                }

                if(southTile != nullptr){
                    if(southTile->getTerrainType() == TerrainTile::TerrainType::WATER){
                        southernLandConnection = false;
                    }
                }

                if(eastTile != nullptr){
                    if(eastTile->getTerrainType() == TerrainTile::TerrainType::WATER){
                        easternLandConnection = false;
                    }
                }

                if(westTile != nullptr){
                    if(westTile->getTerrainType() == TerrainTile::TerrainType::WATER){
                        westernLandConnection = false;
                    }
                }

                bool verticalConnection = northernLandConnection && southernLandConnection;
                bool horizontalConnection = easternLandConnection && westernLandConnection;

                if(!verticalConnection && !horizontalConnection){
                    //If there are no connections (north & south or east & west), pick a random way to go: 1 for vertical, 2 horizontal
                    boost::random::uniform_int_distribution<int> randDirGen(1, 1);
                    int randDir{randDirGen(world->mt19937)};

                    sf::Vector2i tempCartesianPos = currentPos;
                    TerrainTile* nextTile = nullptr;

                    if(randDir == 1){
                        if(!northernLandConnection){

                            tempCartesianPos.y -= 1;

                            TerrainTile* nextTile = world->terrainAtCartesianPos(tempCartesianPos);

                            //..keep on going up the Y axis, filling water with bridges if needed
                            while(nextTile != nullptr){
                                if(nextTile->getTerrainType() == TerrainTile::TerrainType::WATER){
                                    world->togglePBridge(nextTile);
                                    tempCartesianPos.y -= 1;
                                    nextTile = world->terrainAtCartesianPos(tempCartesianPos);
                                }
                                else{
                                    break;
                                }
                            }

                        }

                        //When that's done, snap back to the "original bridge tile and go DOWN the Y axis
                        if(!southernLandConnection){

                            tempCartesianPos = currentPos;
                            tempCartesianPos.y += 1;

                            nextTile = world->terrainAtCartesianPos(tempCartesianPos);

                             while(nextTile != nullptr){
                                if(nextTile->getTerrainType() == TerrainTile::TerrainType::WATER){
                                    world->togglePBridge(nextTile);
                                    tempCartesianPos.y += 1;
                                    nextTile = world->terrainAtCartesianPos(tempCartesianPos);
                                }
                                else{
                                    break;
                                }
                            }

                        }

                    }
                    else if(randDir == 2){
                        //TODO
                    }
                }
            }
        }
    }
}
