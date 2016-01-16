#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/BridgeAnt.h"


BridgeAnt::BridgeAnt(World* _world, int _lifetime) :
Ant{_world, TerrainTile::TerrainType::BRIDGE, _lifetime}
{
}

void BridgeAnt::crawl(){
    //BridgeAnt is unique in that its lifetime is actually the % chance that each
    //water tile will spawn a bridge (or series of bridges). Note that even when
    //this happens, there is a chance for the bridge to be discarded if it
    //intersects other bridges inappropriately (further outlined below)

    for(auto& terrainTile : world->terrainLayer){
        if(terrainTile->getTerrainType() == TerrainTile::TerrainType::WATER){
            //Simulate a lifetime% chance of a bridge spawning..

            boost::random::uniform_int_distribution<int> chance(1, 100);
            int randomRoll{chance(world->masterManager.mapSeedEngine)};

            if(!(randomRoll <= lifetime)){
                continue;
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //
            //
            //The way bridge spawning works is briefly outlined, as follows:
            //First, a random orientation is chosen: either horizontal or vertical
            //
            //For example, if the bridge is horizontal, all tiles on the same X axis are iterated
            //through to ensure the bridge connects 2 non-water tiles, and does not intersect
            //another bridge of the opposite orientation.
            //
            //Every tile that is checked is added to a vector of pointers, bridgesToBuild.
            //
            //For example, let - represent horizontal bridges and | vertical, and w water. Spawn will
            //represent the initial chosen tile.
            //
            //            |-------spawn wwwwwwwwwwwwww
            //
            //In the illustration, the bridges fill up west of spawn until either a land tile, or a bridge of
            //opposite orientation, is hit. Each of the water tiles where this bridge will be built are added to
            //the vector bridgesToBuild.
            //
            //When a non-water tile is encountered: if it is a land tile, the bridge simply pops back to spawn and
            //iterates on the other side. If it is a bridge of opposite orientation, the entire chain of
            //bridges is simply not built by setting validSequenceOfBridges to false, which makes it so that none of the
            //water tiles in bridgesToBuild get bridges built over them . This ensures no weird intersecting bridges are generated.
            //
            //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            bool validSequenceOfBridges{true};
            std::vector<TerrainTile*> bridgesToBuild;

            sf::Vector2i currentPos = terrainTile->getCartesianPos();

            boost::random::uniform_int_distribution<int> randDirGen(1, 2);
            int randDir{randDirGen(world->masterManager.mapSeedEngine)};

            TerrainTile::Orientation orientation;

            if(randDir == 1){
                orientation = TerrainTile::Orientation::VERTICAL;
            }
            else if (randDir == 2){
                orientation = TerrainTile::Orientation::HORIZONTAL;
            }

            bridgesToBuild.push_back(terrainTile.get());
            int index = world->indexAtCartesianPos(currentPos);

            //Ensure bridges are properly connected to land

            //We initialise these as true so that in the case of, for example, the northern tile
            //being out of bounds, the game won't try to create a bridge there and CTD
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
                else if(northTile->getTerrainType() == TerrainTile::TerrainType::BRIDGE){
                    Bridge* p = static_cast<Bridge*>(northTile);
                    if(p->getOrientation() != orientation){
                       northernLandConnection = false;
                    }
                }
            }

            if(southTile != nullptr){
                if(southTile->getTerrainType() == TerrainTile::TerrainType::WATER){
                    southernLandConnection = false;
                }
                else if(southTile->getTerrainType() == TerrainTile::TerrainType::BRIDGE){
                    Bridge* p = static_cast<Bridge*>(southTile);
                    if(p->getOrientation() != orientation){
                       southernLandConnection = false;
                    }
                }
            }

            if(eastTile != nullptr){
                if(eastTile->getTerrainType() == TerrainTile::TerrainType::WATER){
                    easternLandConnection = false;
                }
                else if(eastTile->getTerrainType() == TerrainTile::TerrainType::BRIDGE){
                    Bridge* p = static_cast<Bridge*>(eastTile);
                    if(p->getOrientation() != orientation){
                       easternLandConnection = false;
                    }
                }
            }

            if(westTile != nullptr){
                if(westTile->getTerrainType() == TerrainTile::TerrainType::WATER){
                    westernLandConnection = false;
                }
                else if(westTile->getTerrainType() == TerrainTile::TerrainType::BRIDGE){
                    Bridge* p = static_cast<Bridge*>(westTile);
                    if(p->getOrientation() != orientation){
                       westernLandConnection = false;
                    }
                }
            }

            bool verticalConnection = northernLandConnection && southernLandConnection;
            bool horizontalConnection = easternLandConnection && westernLandConnection;

            sf::Vector2i tempCartesianPos = currentPos;
            TerrainTile* nextTile = nullptr;

            if(orientation == TerrainTile::Orientation::VERTICAL){
                if(!northernLandConnection){

                    tempCartesianPos.y -= 1;

                    TerrainTile* nextTile = world->terrainAtCartesianPos(tempCartesianPos);

                    //..keep on going up the Y axis, filling water with bridges if needed
                    while(nextTile != nullptr && validSequenceOfBridges){
                        if(nextTile->getTerrainType() == TerrainTile::TerrainType::WATER){
                            bridgesToBuild.push_back(world->terrainAtCartesianPos(tempCartesianPos));
                        }
                        else if(nextTile->getTerrainType() == TerrainTile::TerrainType::BRIDGE){
                            Bridge* p = static_cast<Bridge*>(nextTile);
                            if(p->getOrientation() != orientation){
                                validSequenceOfBridges = false;
                            }
                        }
                        else{
                            break;
                        }

                        tempCartesianPos.y -= 1;
                        nextTile = world->terrainAtCartesianPos(tempCartesianPos);
                    }

                }

                //When that's done, snap back to the "original bridge tile and go DOWN the Y axis
                if(!southernLandConnection){

                    tempCartesianPos = currentPos;
                    tempCartesianPos.y += 1;

                    nextTile = world->terrainAtCartesianPos(tempCartesianPos);

                     while(nextTile != nullptr && validSequenceOfBridges){
                        if(nextTile->getTerrainType() == TerrainTile::TerrainType::WATER){
                            bridgesToBuild.push_back(world->terrainAtCartesianPos(tempCartesianPos));
                        }
                        else if(nextTile->getTerrainType() == TerrainTile::TerrainType::BRIDGE){
                            Bridge* p = static_cast<Bridge*>(nextTile);
                            if(p->getOrientation() != orientation){
                                validSequenceOfBridges = false;
                            }
                        }
                        else{
                            break;
                        }

                        tempCartesianPos.y += 1;
                        nextTile = world->terrainAtCartesianPos(tempCartesianPos);
                    }

                }

            }


            else if(orientation == TerrainTile::Orientation::HORIZONTAL){
                if(!westernLandConnection){

                    tempCartesianPos.x -= 1;

                    TerrainTile* nextTile = world->terrainAtCartesianPos(tempCartesianPos);

                    //..keep on going up the X axis, filling water with bridges if needed
                    while(nextTile != nullptr && validSequenceOfBridges){
                        if(nextTile->getTerrainType() == TerrainTile::TerrainType::WATER){
                            bridgesToBuild.push_back(world->terrainAtCartesianPos(tempCartesianPos));
                        }
                        else if(nextTile->getTerrainType() == TerrainTile::TerrainType::BRIDGE){
                            Bridge* p = static_cast<Bridge*>(nextTile);
                            if(p->getOrientation() != orientation){
                                validSequenceOfBridges = false;
                            }
                        }
                        else{
                            break;
                        }

                        tempCartesianPos.x -= 1;
                        nextTile = world->terrainAtCartesianPos(tempCartesianPos);
                    }

                }

                //When that's done, snap back to the "original bridge tile and go DOWN the X axis
                if(!easternLandConnection){

                    tempCartesianPos = currentPos;
                    tempCartesianPos.x += 1;

                    nextTile = world->terrainAtCartesianPos(tempCartesianPos);

                     while(nextTile != nullptr && validSequenceOfBridges){
                        if(nextTile->getTerrainType() == TerrainTile::TerrainType::WATER){
                            bridgesToBuild.push_back(world->terrainAtCartesianPos(tempCartesianPos));
                        }
                        else if(nextTile->getTerrainType() == TerrainTile::TerrainType::BRIDGE){
                            Bridge* p = static_cast<Bridge*>(nextTile);
                            if(p->getOrientation() != orientation){
                                validSequenceOfBridges = false;
                            }
                        }
                        else{
                            break;
                        }

                        tempCartesianPos.x += 1;
                        nextTile = world->terrainAtCartesianPos(tempCartesianPos);
                    }

                }

            }



            if(validSequenceOfBridges){
                for (auto& bridge : bridgesToBuild){
                    world->toggleBridge(bridge, orientation);
                }
            }

        }
    }
}

