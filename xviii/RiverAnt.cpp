#include "stdafx.h"
#include "RiverAnt.h"


RiverAnt::RiverAnt(World* _world, int _lifetime) : 
Ant{_world, TerrainTile::TerrainType::WATER, _lifetime},
lastDirection{0}
{
}

void RiverAnt::crawl(){
	//So long as we are still alive and within bounds
	while (lifetime > 0){

		sf::IntRect currentRekt{};
		sf::Vector2f currentPos{world->terrainLayer[currentIndex]->getPos()};

		world->terrainLayer[currentIndex] = std::move(std::unique_ptr<Water>(new Water{world->tm, currentPos})); 
		currentRekt = world->tm.getTerrainRekt(TextureManager::Terrain::WATER);

		//Update the vertex array at this tile:
		const sf::Vector2i currentCartesianPos{world->cartesianCoordsAtIndex(currentIndex)};

		sf::Vertex* quad = &world->mVertices[(currentCartesianPos.x + currentCartesianPos.y*world->getDimensions().x) * 4];

		quad[0].position = sf::Vector2f(currentCartesianPos.x * world->tm.getSize().x, currentCartesianPos.y * world->tm.getSize().y);
		quad[1].position = sf::Vector2f((currentCartesianPos.x + 1) * world->tm.getSize().x, currentCartesianPos.y *world->tm.getSize().y);
		quad[2].position = sf::Vector2f((currentCartesianPos.x + 1) * world->tm.getSize().x, (currentCartesianPos.y + 1)*world->tm.getSize().y);
		quad[3].position = sf::Vector2f(currentCartesianPos.x * world->tm.getSize().x, (currentCartesianPos.y + 1)*world->tm.getSize().y);

		quad[0].texCoords = sf::Vector2f(currentRekt.left, currentRekt.top);
		quad[1].texCoords = sf::Vector2f(currentRekt.left + currentRekt.width, currentRekt.top);
		quad[2].texCoords = sf::Vector2f(currentRekt.left + currentRekt.width, currentRekt.top + currentRekt.height);
		quad[3].texCoords = sf::Vector2f(currentRekt.left, currentRekt.top + currentRekt.height);

		//And finally, switch the currentIndex index to a tile in a random direction. To do this, we'll use our cartesian coordinates. We
		//also check if the new tile is already the same terrain type we are trying to spawn; if so we keep going in the same direction 
		//until that is not the case

		sf::Vector2i newCartesianPos{currentCartesianPos};

		std::uniform_int_distribution<int> randomDirectionDist(1, 8);
		int randomDirection{randomDirectionDist(world->mt19937)};

		//Since direction is initialised as 0 at the start, ignore this the first time it is run
		if (lastDirection != 0){
			//To simulate a 75% chance of the direction going on in the same direction
			//This solution is temporary; a better one that makes the river look more realistic
			//should be found
			std::uniform_int_distribution<int> chance(1, 100);
			int randomRoll{chance(world->mt19937)};

			if (randomRoll <= 75){
				randomDirection = lastDirection;
			}
		}

		//If the tile we are moving to is the same type
		//move ant in that direction again until that is not the case
		while (world->terrainLayer[world->indexAtCartesianCoords(newCartesianPos)]->getTerrainType() == type && lifetime > 0){
			increment(randomDirection, newCartesianPos);
			currentIndex = world->indexAtCartesianCoords(newCartesianPos);
		}

		lastDirection = randomDirection;
		//Set the index to the new coordinates
		currentIndex = world->indexAtCartesianCoords(newCartesianPos);

		//Decrement our lifetime
		--lifetime;
	}
}
