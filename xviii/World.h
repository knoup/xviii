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

#define ERAPROPERTIES\
	X("EARLY", World::Era::EARLY)\
	X("MID", World::Era::MID)\
	X("LATE", World::Era::LATE)\
	X("ALL", World::Era::ALL)

class World : public sf::Drawable, public sf::NonCopyable
{
	friend class Ant;
	friend class RiverAnt;
	friend class SlopeAnt;
	friend class HillAnt;
	friend class SaveGame;
	//For easier access to the vertex array
	friend class TerrainTile;
public:
	enum class Era{ EARLY, MID, LATE, ALL };

	World(TextureManager& _tm, sf::Vector2i _dimensions, std::mt19937& _mt19937);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;

	void generateRandomWorld(Era _era);

	int indexAtPixelPos(sf::Vector2i _pos) const;
	int indexAtCartesianPos(sf::Vector2i _pos) const;
	int indexAtTile(Tile& _tile) const;
	sf::Vector2i cartesianPosAtIndex(int _index) const;
	sf::Vector2f pixelPosAtIndex(int _index) const;

	//Returns true if the terrain tile at this position is unoccupied
	bool canBePlacedAtPixelPos(sf::Vector2i _pos);
	bool canBePlacedAtCartesianPos(sf::Vector2i _pos);

	//Returns a [regular] pointer to the unit at this mouse coordinate position, if there is any
	UnitTile* unitAtPixelPos(sf::Vector2i _pos);
	//Takes in terrain ptr
	UnitTile* unitAtTerrain(TerrainTile* _terrain);

	TerrainTile* terrainAtPixelPos(sf::Vector2i _pos);
	TerrainTile* terrainAtCartesianPos(sf::Vector2i _pos);

	const std::vector<UnitTile*>& getDamagedUnits() const;
	const int getElapsedTurns() const{ return elapsedTurns;};
	void setElapsedTurns(int _elapsedTurns){ elapsedTurns = _elapsedTurns; };
	void incrementElapsedTurns(){ elapsedTurns+=1; };

	sf::Vector2i getDimensions() const;
	sf::Vector2i getDimensionsInPixels() const;
	World::Era getEra() const{ return era; };
	void setEra(Era _era){era = _era;}

	void addToDamagedUnits(UnitTile* unit);
	void clearDamagedUnits();

private:
	TextureManager& tm;
	sf::Vector2i dimensions;
	sf::Vector2i dimensionsInPixels;

	std::mt19937& mt19937;

	int elapsedTurns{0};
	Era era;

	//The first layer, or "terrain layer"; always drawn behind the units and only consists
	//of Terrain.
	std::vector<TerrainTile::terrainPtr> terrainLayer;


	//This vector stores pointers to the units that have been damaged during an attack. It is reset afterwards
	std::vector<UnitTile*> damagedUnits;


	//Used for drawing efficiency
	sf::VertexArray mTerrainVertices;
	sf::Texture& mTerrainTexture;

};

/*

int tileAtPosition(int x, int y) const;
sf::Vector2i tileAtPosition(int index);

*/
