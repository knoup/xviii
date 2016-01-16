#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/RiverAnt.h"


RiverAnt::RiverAnt(World* _world, int _lifetime) :
Ant{_world, TerrainTile::TerrainType::WATER, _lifetime},
initialDirection{0}
{
}

void RiverAnt::crawl(){
	//So long as we are still alive and within bounds
	while (lifetime > 0){

		sf::Vector2f currentPos{world->terrainLayer[currentIndex]->getPixelPos()};


		boost::random::uniform_int_distribution<int> randomDirectionDist(1, 8);
		int randomDirection{randomDirectionDist(world->masterManager.mapSeedEngine)};


		 boost::random::uniform_int_distribution<int> randDist(1, 100);
		int randNum{randDist(world->masterManager.mapSeedEngine)};


        world->terrainLayer[currentIndex] = std::move(std::unique_ptr<Water>(new Water{world, currentPos}));


		const sf::Vector2i currentCartesianPos{world->cartesianPosAtIndex(currentIndex)};

		//And finally, switch the currentIndex index to a tile in a random direction. To do this, we'll use our cartesian coordinates. We
		//also check if the new tile is already the same terrain type we are trying to spawn; if so we keep going in the same direction
		//until that is not the case

		sf::Vector2i newCartesianPos{currentCartesianPos};

		//initialDirection is initialised as 0; the first direction chosen is assigned
		if (initialDirection == 0){
			initialDirection = randomDirection;
		}

		//To simulate a 75% chance of flowing in the initial direction
		boost::random::uniform_int_distribution<int> chance(1, 100);
		int randomRoll{chance(world->masterManager.mapSeedEngine)};

		if (randomRoll <= 75){
			randomDirection = initialDirection;
		}

        //For caching purposes, and clarity:
        int index = world->indexAtCartesianPos(newCartesianPos);
		//If the tile we are moving to is a water tile
			//move ant in that direction again until that is not the case
		while (world->terrainLayer[index]->getTerrainType() == type && lifetime > 0){
			increment(randomDirection, newCartesianPos);
			index = world->indexAtCartesianPos(newCartesianPos);
		}

		//Set the index to the new coordinates
		currentIndex = world->indexAtCartesianPos(newCartesianPos);

		//Decrement our lifetime
		--lifetime;
	}
}
