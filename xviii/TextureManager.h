#pragma once

class TextureManager : public sf::NonCopyable
{
public:
	using texturePtr = std::unique_ptr<sf::Texture>;

	enum class Unit{INF, CAV, CUIR, LCAV, DRAG, 
					ART, MOR, GEN, GRE, LINF, 
					SAP, HINF, ARTGUARD, PIKE, LAN,
					ARMLAN, IRR, HARCH};

	enum class Terrain{MEADOW, HILLS, MUD, ROAD, SLOPES, URBAN, WATER, WOODS};
	enum class UI{RECTANGLE, BUTTON};
	enum class Flag{AUS,PRU,FRA, GBR, RUS, BAV, COM, SPA, POR, VEN, SAX, SWE, OTO, CRI, IME, MOL, WAL, PER};

	TextureManager();

	sf::Sprite getSprite(Unit type);
	sf::Sprite getSprite(Terrain type);
	sf::Sprite getSprite(UI type);
	sf::Sprite getSprite(Flag type);

	inline sf::Vector2i getSize() const{ return size; };
	inline sf::Vector2i getCounterSize() const{ return counterSize; };
    //Used for the vertex array (for terrain tiles)	
	inline sf::Texture& getTerrainTexture() const{ return *terrain; };
	// Used for the vertex array(for unit tiles)
	inline sf::Texture& getUnitTexture() const{ return *units; };

private:
	//The unit sprites
	texturePtr units;
	//The terrain
	texturePtr terrain;
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

