#pragma once

#include "xviii/Core/Tile.h"

#define TERRAINPROPERTIES\
	X(TerrainTile::TerrainType::MEADOW, Meadow, TextureManager::Terrain::MEADOW, "meadow")\
	X(TerrainTile::TerrainType::HILLS, Hills, TextureManager::Terrain::HILLS, "hills")\
	X(TerrainTile::TerrainType::MUD, Mud, TextureManager::Terrain::MUD, "mud")\
	X(TerrainTile::TerrainType::ROAD, Road, TextureManager::Terrain::ROAD, "road")\
	X(TerrainTile::TerrainType::SLOPES, Slopes, TextureManager::Terrain::SLOPES, "slopes")\
	X(TerrainTile::TerrainType::URBAN, Urban, TextureManager::Terrain::URBAN, "urban")\
	X(TerrainTile::TerrainType::WATER, Water, TextureManager::Terrain::WATER, "water")\
	X(TerrainTile::TerrainType::WOODS, Woods, TextureManager::Terrain::WOODS, "woods")


class Meadow;
class Hills;
class Mud;
class Road;
class Slopes;
class Urban;
class Water;
class Woods;

class World;
class UnitTile;

class TerrainTile : public Tile
{
public:
	using terrainPtr = std::unique_ptr<TerrainTile>;
	enum class TerrainType{ MEADOW, HILLS, MUD, ROAD, SLOPES, URBAN, WATER, WOODS };

	TerrainTile(World& _world, TextureManager& tm, TextureManager::Terrain textType, TerrainType terrainType, sf::Vector2f _pos);
	virtual ~TerrainTile() = 0;

	void setPos(sf::Vector2f _pos);

	TerrainType getTerrainType() const;

	void setUnit(UnitTile* _unit);
	UnitTile* getUnit();
	void resetUnit();
	virtual void applyModifiers(UnitTile* _unit, int _distance, bool _attacking){};


	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

protected:
	TerrainType terrainType;
	UnitTile* unit;
};

