#pragma once

#include "TextureManager.h"

class World;

class Tile : public sf::Drawable
{
public:
	using tilePtr = std::unique_ptr<Tile>;
	Tile(World& _world, TextureManager& tm, TextureManager::Unit id);
	Tile(World& _world, TextureManager& tm, TextureManager::Terrain id);
	//Create a virtual destructor, signifying this is an abstract class
	virtual ~Tile() = 0;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

	sf::Vector2i getCartesianPos() const;
	sf::Vector2f getPixelPos() const;

	void setHighlighted(bool _value);

	int top() const;
	int left() const;
	int bottom() const;
	int right() const;
protected:
	sf::Sprite sprite;
	bool highlighted;
	World& world;
};

