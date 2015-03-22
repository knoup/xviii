#pragma once

#include "TextureManager.h"

class Tile : public sf::Drawable
{
public:
	using tilePtr = std::unique_ptr<Tile>;
	Tile(TextureManager& tm, TextureManager::Unit id);
	Tile(TextureManager& tm, TextureManager::Terrain id);
	//Create a virtual destructor, signifying this is an abstract class
	virtual ~Tile() = 0;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

	void setHighlighted(bool _value);

	int top() const;
	int left() const;
	int bottom() const;
	int right() const;
protected:
	sf::Sprite sprite;
	bool highlighted;
};
