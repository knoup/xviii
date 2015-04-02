#pragma once

#include "TextureManager.h"

#include "UnitTile.h"
#include "TerrainTile.h"

class World : public sf::Drawable, public sf::NonCopyable
{
public:
	World(TextureManager& _tm, sf::Vector2i _dimensions);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;

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
