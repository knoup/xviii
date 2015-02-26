#pragma once

#include "Tile.h"

//Terain tiles don't really need a sprite, but we're still going to inherit from
//tile for all the other functionality. Hence, we're just going to set a blank textured sprite.
//Note we still need the sprite to be the correct size for location information

class TerrainTile : public Tile
{
public:
	using terrainPtr = std::unique_ptr<TerrainTile>;
	enum class TerrainType{MEADOW};

	TerrainTile(TextureManager& tm, TerrainType type, sf::Vector2f _pos);
	virtual ~TerrainTile();

	void setPos(sf::Vector2f _pos);
	sf::Vector2f getPos() const;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

protected:
	TerrainType terrainType;
};

