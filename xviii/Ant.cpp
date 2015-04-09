#include "stdafx.h"
#include "Ant.h"

#include "World.h"

Ant::Ant(World* _world, TerrainTile::TerrainType _type, int _lifetime) :
world{_world},
type{_type},
lifetime{_lifetime},
currentIndex{0}
{
	//Initialise the ant's beginning tile to a random tile in the world; because the dimensions start
	//from 1 and not 0, subtract one to get the true coordinate
	std::uniform_int_distribution<int> xDist{0, world->getDimensions().x - 1};
	std::uniform_int_distribution<int> yDist{0, world->getDimensions().y - 1};

	int xCoord = xDist(world->mt19937);
	int yCoord = yDist(world->mt19937);

	currentIndex = world->indexAtCartesianCoords({xCoord, yCoord});
	crawl();
}

void Ant::increment(int dir, sf::Vector2i& cartesianCoords){
	//North
	if (dir == 1 && cartesianCoords.y > 0){
		cartesianCoords.y -= 1;
	}
	//East
	else if (dir == 2 && cartesianCoords.x < world->getDimensions().x - 1){
		cartesianCoords.x += 1;
	}
	//South
	else if (dir == 3 && cartesianCoords.y < world->getDimensions().y - 1){
		cartesianCoords.y += 1;
	}
	//West
	else if (dir == 4 && cartesianCoords.x > 0){
		cartesianCoords.x -= 1;
	}
	//If at the edge of the map, kill the ant
	else{
		lifetime = 0;
	}
}

void Ant::crawl(){
	//So long as we are still alive and within bounds
	while (lifetime > 0){

		sf::IntRect currentRekt{};
		sf::Vector2f currentPos{world->terrainLayer[currentIndex]->getPos()};

		//Create new terrain as needed, type associations defined in TERRAINPROPERTIES (TerrainTile.h)
		switch (type){
			#define X(_type, cl, texture, str)\
					case(_type):\
						world->terrainLayer[currentIndex] = std::move(std::unique_ptr<cl>(new cl{world->tm, currentPos}));\
						currentRekt = world->tm.getTerrainRekt(texture);\
						break;
			TERRAINPROPERTIES
			#undef X
		}

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

		std::uniform_int_distribution<int> randomDirectionDist(1, 4);
		int randomDirection{randomDirectionDist(world->getmt19937())};

		//If the tile we are moving to is the same type 
		//move ant in that direction again until that is not the case
		while (world->terrainLayer[world->indexAtCartesianCoords(newCartesianPos)]->getTerrainType() == type && lifetime > 0){
			increment(randomDirection, newCartesianPos);
			currentIndex = world->indexAtCartesianCoords(newCartesianPos);
		}

		//Set the index to the new coordinates
		currentIndex = world->indexAtCartesianCoords(newCartesianPos);

		//Decrement our lifetime
		--lifetime;
	}
}