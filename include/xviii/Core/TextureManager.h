#pragma once

#include <boost/random.hpp>
#include <boost/random/random_device.hpp>

class TextureManager
{
public:
	using texturePtr = std::unique_ptr<sf::Texture>;

	enum class Terrain{MEADOW, HILLS, MUD, ROAD, SLOPES, URBAN, WATER, WOODS, BRIDGE_VER, BRIDGE_HOR, TBRIDGE_VER, TBRIDGE_HOR, BLANK};
	enum class UI{RECTANGLE, BUTTON};

	TextureManager(boost::random::mt19937& _randomEngine);
    //The copy constructor and = operator for this class have been disabled
	//Copy constructor
	TextureManager(const TextureManager&) = delete;
	//Operator=
	TextureManager & operator=(const TextureManager&) = delete;

	sf::Sprite getUnitSprite(std::string _textureID);
	sf::Sprite getFlagSprite(std::string _textureID);
	sf::Sprite getWeatherSprite(std::string _textureID);
	sf::Sprite getSprite(Terrain type);
	sf::Sprite getSprite(UI type);
    sf::Sprite getRandomBackground();

	inline sf::Vector2i getSize() const{ return size; };
	inline sf::Vector2i getCounterSize() const{ return counterSize; };
    //Used for the vertex array (for terrain tiles)
	inline sf::Texture& getTerrainTexture() const{ return *terrain; };

private:
	std::map<std::string, texturePtr> units;
	std::map<std::string, texturePtr> flags;
	std::map<std::string, texturePtr> weather;

    //A random image from the backgrounds folder. Note that it is only randomised once on launch.
    texturePtr randomBackground;
    //The terrain tileset
	texturePtr terrain;
	//The rectangular UI bar at the bottom
	texturePtr ui;
	//Ready/next turn button
	texturePtr button;

	//This should correspond to the FULL size of each [Terrain] tile
	//for everything to work properly
	sf::Vector2i size;

	//The size of the unit counters (ideally smaller than the full terrain tile size)
	sf::Vector2i counterSize;

};

