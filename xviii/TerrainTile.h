#pragma once

#include "Tile.h"

#define TERRAINPROPERTIES\
	X(TerrainTile::TerrainType::MEADOW, Meadow, "meadow")\
	X(TerrainTile::TerrainType::HILLS, Hills, "hills")\
	X(TerrainTile::TerrainType::MUD, Mud, "mud")\
	X(TerrainTile::TerrainType::ROAD, Road, "road")\
	X(TerrainTile::TerrainType::SLOPES, Slopes, "slopes")\
	X(TerrainTile::TerrainType::URBAN, Urban, "urban")\
	X(TerrainTile::TerrainType::WATER, Water, "water")\
	X(TerrainTile::TerrainType::WOODS, Woods, "woods")


class Meadow;
class Hills;
class Mud;
class Road;
class Slopes;
class Urban;
class Water;
class Woods;


class TerrainTile : public Tile
{
public:
	using terrainPtr = std::unique_ptr<TerrainTile>;
	enum class TerrainType{ MEADOW, HILLS, MUD, ROAD, SLOPES, URBAN, WATER, WOODS };

	TerrainTile(TextureManager& tm, TextureManager::Terrain textType, TerrainType terrainType, sf::Vector2f _pos);
	virtual ~TerrainTile() = 0;

	void setPos(sf::Vector2f _pos);
	sf::Vector2f getPos() const;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

protected:
	TerrainType terrainType;
};

