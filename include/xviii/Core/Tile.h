#pragma once

#include "xviii/Core/MasterManager.h"

class World;
class UnitTile;
class MasterManager;

class Tile : public sf::Drawable
{
public:
	using tilePtr = std::unique_ptr<Tile>;
	Tile(World* _world, std::string textureID);
	Tile(World* _world, TextureManager::Terrain id);
    //The copy constructor and = operator for this class have been disabled
	//Copy constructor
	Tile(const Tile&) = delete;
	//Operator=
	Tile & operator=(const Tile&) = delete;
	//Create a virtual destructor, signifying this is an abstract class
	virtual ~Tile() = 0;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

	sf::Vector2i getCartesianPos() const;
	sf::Vector2f getPixelPos() const;
	sf::Vector2f getPixelPosCenter() const;

	void setHighlighted(bool _value);
	void setColor(sf::Color _color);

	int top() const;
	int left() const;
	int bottom() const;
	int right() const;
protected:
	World* world;
	sf::Sprite sprite;
	bool highlighted;
};

