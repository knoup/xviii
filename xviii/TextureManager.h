#pragma once

class TextureManager : public sf::NonCopyable
{
public:
	using texturePtr = std::unique_ptr<sf::Texture>;

	enum class Unit{INF, CAV, CUIR, LCAV, DRAGOON, ART, MOR, GEN};
	enum class Terrain{MEADOW};
	enum class UI{RECTANGLE, BUTTON};
	enum class Flag{AUS,PRU};

	TextureManager();

	sf::Sprite getSprite(Unit type);
	sf::Sprite getSprite(Terrain type);
	sf::Sprite getSprite(UI type);
	sf::Sprite getSprite(Flag type);

	sf::Vector2i getSize() const;
	sf::Vector2i getCounterSize() const;

    //Used for the vertex array (for terrain tiles)
	sf::Texture& getTexture() const;
	sf::IntRect getTerrainRekt(Terrain type);

private:
	//The unit sprites
	texturePtr textureSet;
	//The rectangular UI bar at the bottom
	texturePtr ui;
	//Ready/next turn button
	texturePtr button;
	//The flags
	texturePtr flags;

	//This should correspond to the FULL size of each [Terrain] tile
	//for everything to work properly
	sf::Vector2i size;

	//The size of the counter itself and only:
	sf::Vector2i counterSize;

};

