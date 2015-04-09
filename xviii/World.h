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
			current{0}
		{
			//Initialise the ant's beginning tile to a random tile in the world; because the dimensions start
			//from 1 and not 0, subtract one to get the true coordinate
			std::uniform_int_distribution<int> xDist{0, world->getDimensions().x - 1};
			std::uniform_int_distribution<int> yDist{0, world->getDimensions().y - 1};

			int xCoord = xDist(world->mt19937);
			int yCoord = yDist(world->mt19937);

			current = world->indexAtCartesianCoords({xCoord,yCoord});

			crawl();
		}

		World* world;
		TerrainTile::TerrainType type;
		//The current index
		int current;

		int lifetime;

		void crawl(){
			//So long as we are alive and the current index is within bounds of the world
			while (lifetime > 0 && current >= 0 && current < world->getDimensions().x * world->getDimensions().y){

				sf::IntRect currentRekt{};
				sf::Vector2f currentPos{world->terrainLayer[current]->getPos()}; 
				//Create new terrain as needed, type associations defined in TERRAINPROPERTIES (TerrainTile.h)
				switch (type){
					#define X(_type, cl, texture, str)\
					case(_type):\
						world->terrainLayer[current] = std::move(std::unique_ptr<cl>(new cl{world->tm, currentPos}));\
						currentRekt = world->tm.getTerrainRekt(texture);\
						break;
					TERRAINPROPERTIES
					#undef X
				}

				//Update the vertex array at this tile:
				sf::Vector2i currentCartesianPos{world->cartesianCoordsAtIndex(current)};

				sf::Vertex* quad = &world->mVertices[(currentCartesianPos.x + currentCartesianPos.y*world->getDimensions().x) * 4];

				quad[0].position = sf::Vector2f(currentCartesianPos.x * world->tm.getSize().x, currentCartesianPos.y * world->tm.getSize().y);
				quad[1].position = sf::Vector2f((currentCartesianPos.x + 1) * world->tm.getSize().x, currentCartesianPos.y *world->tm.getSize().y);
				quad[2].position = sf::Vector2f((currentCartesianPos.x + 1) * world->tm.getSize().x, (currentCartesianPos.y + 1)*world->tm.getSize().y);
				quad[3].position = sf::Vector2f(currentCartesianPos.x * world->tm.getSize().x, (currentCartesianPos.y + 1)*world->tm.getSize().y);

				quad[0].texCoords = sf::Vector2f(currentRekt.left, currentRekt.top);
				quad[1].texCoords = sf::Vector2f(currentRekt.left + currentRekt.width, currentRekt.top);
				quad[2].texCoords = sf::Vector2f(currentRekt.left + currentRekt.width, currentRekt.top + currentRekt.height);
				quad[3].texCoords = sf::Vector2f(currentRekt.left, currentRekt.top + currentRekt.height);

				//Decrement our lifetime
				--lifetime;
				//And finally, switch the current index to a tile in a random direction
				current++;
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
