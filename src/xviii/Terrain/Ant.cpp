#include "xviii/Headers/stdafx.h"
#include "xviii/Terrain/Ant.h"

#include "xviii/Core/World.h"

Ant::Ant(World* _world, TerrainTile::TerrainType _type, int _lifetime) :
world(_world),
type{_type},
lifetime{_lifetime},
currentIndex{0}
{
	//Initialise the ant's beginning tile to a random tile in the world; because the dimensions start
	//from 1 and not 0, subtract one to get the true coordinate
	boost::random::uniform_int_distribution<int> xDist{0, world->getDimensions().x - 1};
	boost::random::uniform_int_distribution<int> yDist{0, world->getDimensions().y - 1};

	int xCoord = xDist(world->masterManager.mapSeedEngine);
	int yCoord = yDist(world->masterManager.mapSeedEngine);

	currentIndex = world->indexAtCartesianPos({xCoord, yCoord});
}

Ant::~Ant(){
}

void Ant::increment(int dir, sf::Vector2i& cartesianCoords){
	int maxWorldX{world->getDimensions().x - 1};
	int maxWorldY{world->getDimensions().y - 1};

	//North
	if (dir == 1 && cartesianCoords.y > 0){
		cartesianCoords.y -= 1;
	}
	//East
	else if (dir == 2 && cartesianCoords.x < maxWorldX){
		cartesianCoords.x += 1;
	}
	//South
	else if (dir == 3 && cartesianCoords.y < maxWorldY){
		cartesianCoords.y += 1;
	}
	//West
	else if (dir == 4 && cartesianCoords.x > 0){
		cartesianCoords.x -= 1;
	}
	//Northeast
	else if (dir == 5 && cartesianCoords.y > 0 && cartesianCoords.x < maxWorldX){
		cartesianCoords.y -= 1;
		cartesianCoords.x += 1;
	}
	//Southeast
	else if (dir == 6 && cartesianCoords.y < maxWorldY && cartesianCoords.x < maxWorldX){
		cartesianCoords.y += 1;
		cartesianCoords.x += 1;
	}
	//Southwest
	else if (dir == 7 && cartesianCoords.y < maxWorldY && cartesianCoords.x > 0){
		cartesianCoords.y += 1;
		cartesianCoords.x -= 1;
	}
	//Northwest
	else if (dir == 8 && cartesianCoords.y > 0 && cartesianCoords.x > 0){
		cartesianCoords.y -= 1;
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

		sf::Vector2f currentPos{world->terrainLayer[currentIndex]->getPixelPos()};

		//Create new terrain as needed, type associations defined in TERRAINPROPERTIES (TerrainTile.h)
		switch (type){
			//type, class, texture, string
			#define X(_type, cl, texture, str)\
					case(_type):\
						world->terrainLayer[currentIndex] = std::move(std::unique_ptr<cl>(new cl{world, currentPos}));\
						break;
			TERRAINPROPERTIES
			#undef X
		}

		const sf::Vector2i currentCartesianPos{world->cartesianPosAtIndex(currentIndex)};

		//And finally, switch the currentIndex index to a tile in a random direction. To do this, we'll use our cartesian coordinates. We
		//also check if the new tile is already the same terrain type we are trying to spawn; if so we keep going in the same direction
		//until that is not the case

		sf::Vector2i newCartesianPos{currentCartesianPos};

		boost::random::uniform_int_distribution<int> randomDirectionDist(1, 8);
		int randomDirection{randomDirectionDist(world->masterManager.mapSeedEngine)};

		//If the tile we are moving to is the same type
		//move ant in that direction again until that is not the case
		while (world->terrainLayer[world->indexAtCartesianPos(newCartesianPos)]->getTerrainType() == type && lifetime > 0){
			increment(randomDirection, newCartesianPos);
		}

		//Set the index to the new coordinates
		currentIndex = world->indexAtCartesianPos(newCartesianPos);

		//Decrement our lifetime
		--lifetime;
	}
}
