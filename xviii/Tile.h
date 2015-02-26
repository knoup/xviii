#pragma once

#include "TextureManager.h"

class Tile : public sf::Drawable
{
public:
	enum class Type{INF, CAV, ART, MOR, GEN, TERRAIN};
	using tilePtr = std::unique_ptr<Tile>;
	Tile(TextureManager& tm, TextureManager::Unit id);
	Tile(TextureManager& tm, TextureManager::Terrain id);
	//Create a virtual destructor, signifying this is an abstract class
	virtual ~Tile() = 0;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void setHighlightColor(sf::Color _color);
	void setHighlighted(bool _value);
	//Resets the rekt outline color to yellow
	void resetHighlightedColor();

	int top() const;
	int left() const;
	int bottom() const;
	int right() const;
protected:
	sf::Sprite sprite;
	//The additional rectangle shape here is just for the
	//convenient outlining feature
	sf::RectangleShape rekt;
	bool highlighted;
};

