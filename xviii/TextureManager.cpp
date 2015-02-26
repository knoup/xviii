#include "stdafx.h"
#include "TextureManager.h"


TextureManager::TextureManager() :
textureSet{nullptr},
size{54, 54}, //Current: 54,54; Old: 36,36
counterSize{54, 34} //Current: 54,34; Old: 36,22
{
	textureSet = std::move(texturePtr(new sf::Texture()));
	textureSet->loadFromFile("assets/gfx/spriteset.png");
	
	ui = std::move(texturePtr(new sf::Texture()));
	ui->loadFromFile("assets/gfx/ui.png");

	button = std::move(texturePtr(new sf::Texture()));
	button->loadFromFile("assets/gfx/button.png");

	flags = std::move(texturePtr(new sf::Texture()));
	flags->loadFromFile("assets/gfx/flags.png");

	textureSet->setSmooth(true);
}

sf::Sprite TextureManager::getSprite(Unit type){

	sf::IntRect rekt;

	switch (type){
	case Unit::INF:
		rekt = {0, 0, counterSize.x, counterSize.y};
		break;

	case Unit::CAV:
		rekt = {0, 34, counterSize.x, counterSize.y};
		break;

	case Unit::CUIR:
		//todo
		break;

	case Unit::DRAG:
		//todo
		break;

	case Unit::LCAV:
		//todo
		break;

	case Unit::ART:
		rekt = {54, 0, counterSize.x, counterSize.y};
		break;

	case Unit::MOR:
		rekt = {54, 34, counterSize.x, counterSize.y};
		break;

	case Unit::GEN:
		rekt = {108, 0, counterSize.x, counterSize.y};
		break;
	}

	return{*textureSet, rekt};

}

sf::Sprite TextureManager::getSprite(Terrain type){

	sf::IntRect rekt;

	switch (type){
	case Terrain::MEADOW:
		rekt = {108, 34, size.x, size.y};
		break;
	}
	return{*textureSet, rekt};

}

sf::Sprite TextureManager::getSprite(UI type){

	sf::IntRect rekt;

	switch (type){
	case UI::RECTANGLE:{
		return sf::Sprite{*ui};
		}

	case UI::BUTTON:{
		return sf::Sprite{*button};
		}
	}

	return{*textureSet, rekt};

}

sf::Sprite TextureManager::getSprite(Flag type){

	sf::IntRect rekt;

	switch (type){
	case Flag::AUS:
		rekt = {0, 0, counterSize.x, counterSize.y};
		return{*flags, rekt};

	case Flag::PRU:
		rekt = {54, 0, counterSize.x, counterSize.y};
		return{*flags, rekt};
	}

}

sf::Vector2i TextureManager::getSize() const{
	return size;
}

sf::Vector2i TextureManager::getCounterSize() const{
	return counterSize;
}

sf::Texture& TextureManager::getTexture() const{
	return *textureSet;
}

//NOTE: UI and BUTTON (and obviously BLANK) are not handled here. 
sf::IntRect TextureManager::getTerrainRekt(Terrain type){

	sf::IntRect rekt;

	switch (type){
	case Terrain::MEADOW:
		rekt = {108, 34, size.x, size.y};
		break;
	}

	return rekt;

}
