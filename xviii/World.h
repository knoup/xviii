#pragma once

#include "TextureManager.h"

#include "UnitTile.h"
#include "TerrainTile.h"

#include "Meadow.h"
#include "Hills.h"
#include "Mud.h"
#include "Slopes.h"
#include "Road.h"
#include "Hills.h"
#include "Urban.h"
#include "Water.h"
#include "Woods.h"

class World : public sf::Drawable, public sf::NonCopyable
{
public:
	World(TextureManager& _tm, sf::Vector2i _dimensions, std::mt19937& _mt19937);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;

	struct Ant{
		Ant(World* _world, TerrainTile::TerrainType _type, int _lifetime) :
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

		World* world;
		TerrainTile::TerrainType type;
		int currentIndex;
		//How many terrain tiles it will end up modifying
		int lifetime;

		//Adjusts currentIndex according to the direction
		void increment(int dir, sf::Vector2i& newCartesianCoords){
			//North
			if (dir == 1 && newCartesianCoords.y > 0){
				newCartesianCoords.y -= 1;
			}
			//East
			else if (dir == 2 && newCartesianCoords.x < world->getDimensions().x - 1){
				newCartesianCoords.x += 1;
			}
			//South
			else if (dir == 3 && newCartesianCoords.y < world->getDimensions().y - 1){
				newCartesianCoords.y += 1;
			}
			//West
			else if (dir == 4 && newCartesianCoords.x > 0){
				newCartesianCoords.x -= 1;
			}
			//If at the edge of the map, kill the ant
			else{
				lifetime = 0;
			}

		}

		void crawl(){
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
				int randomDirection{randomDirectionDist(world->mt19937)};

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
	};


	void generate();

	int indexAtMouseCoords(sf::Vector2i _pos);
	int indexAtCartesianCoords(sf::Vector2i _pos);
	int indexAtTile(Tile& _tile);
	sf::Vector2i cartesianCoordsAtIndex(int _index);

	//Places a unit at the specified tile, if it is unoccupied
	bool placeAt(sf::Vector2i _pos, UnitTile::unitPtr ptr);

	//Returns a [regular] pointer to the unit at this mouse coordinate position, if there is any
	UnitTile* unitAtMouseCoords(sf::Vector2i _pos);

	//Overloaded version that takes in a terrain pointer:
	//TODO: some optimising of this would be nice
	UnitTile* unitAt(TerrainTile* _terrain);

	TerrainTile* terrainAtMouseCoords(sf::Vector2i _pos);
	TerrainTile* terrainAtCartesianCoords(sf::Vector2i _pos);

	//Deletes and returns a [unique] pointer to the unit at this mouse coordinate position
	UnitTile::unitPtr removeUnit(sf::Vector2i _pos);
	//Completely removes from play a unit
	UnitTile::unitPtr removeUnit(UnitTile* _ptr);

	//Overloaded function that removes a unit if you have a pointer to it already
	//UnitTile::unitPtr removeUnit(UnitTile* _ptr);

	//Returns a reference to the combat layer
	const std::vector<UnitTile::unitPtr>& getCombatLayer() const;

	sf::Vector2i getDimensions() const;
	sf::Vector2i getDimensionsInPixels() const;

	const std::vector<UnitTile*>& getDamagedUnits() const;
	void addToDamagedUnits(UnitTile* unit);
	void clearDamagedUnits();

	std::mt19937& getmt19937();

private:
	TextureManager& tm;
	sf::Vector2i dimensions;
	sf::Vector2i dimensionsInPixels;

	std::mt19937& mt19937;

	//The first layer, or "terrain layer"; always drawn behind the units and only consists
	//of Terrain.
	std::vector<TerrainTile::terrainPtr> terrainLayer;

	//The second layer, or "combat layer"; contains the actual units.

	std::vector<UnitTile::unitPtr> unitLayer;

	//The final vector is reset every turn; it contains the units that have been damaged this attack
	std::vector<UnitTile*> damagedUnits;


	//Used for drawing efficiency
	sf::VertexArray mVertices;
	sf::Texture& mTexture;

};

/*

int tileAtPosition(int x, int y) const;
sf::Vector2i tileAtPosition(int index);

*/
