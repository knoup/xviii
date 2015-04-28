#include "stdafx.h"
#include "TextureManager.h"


TextureManager::TextureManager() :
units{nullptr},
size{54, 54}, //Current: 54,54
counterSize{54, 34} //Current: 54,34
{
	units = std::move(texturePtr(new sf::Texture()));
	units->loadFromFile("assets/gfx/spriteset.png");

	terrain = std::move(texturePtr(new sf::Texture()));
	terrain->loadFromFile("assets/gfx/terrain.png");
	
	ui = std::move(texturePtr(new sf::Texture()));
	ui->loadFromFile("assets/gfx/ui.png");

	button = std::move(texturePtr(new sf::Texture()));
	button->loadFromFile("assets/gfx/button.png");

	flags = std::move(texturePtr(new sf::Texture()));
	flags->loadFromFile("assets/gfx/flags.png");

	units->setSmooth(true);
}

sf::Sprite TextureManager::getSprite(Unit type){

	sf::IntRect rekt;

	switch (type){
	case Unit::INF:
		rekt = {0, 0, counterSize.x, counterSize.y};
		break;

	case Unit::CAV:
		rekt = {108, 0, counterSize.x, counterSize.y};
		break;

	case Unit::CUIR:
		rekt = {0, 34	, counterSize.x, counterSize.y};
		break;

	case Unit::DRAG:
		rekt = {54, 68, counterSize.x, counterSize.y};
		break;

	case Unit::LCAV:
		rekt = {54, 0, counterSize.x, counterSize.y};
		break;

	case Unit::ART:
		rekt = {108, 34, counterSize.x, counterSize.y};
		break;

	case Unit::MOR:
		rekt = {54, 34, counterSize.x, counterSize.y};
		break;

	case Unit::GEN:
		rekt = {0, 102, counterSize.x, counterSize.y};
		break;

	case Unit::GRE:
		rekt = {108, 68, counterSize.x, counterSize.y};
		break;
		
	case Unit::LINF:
		rekt = {108, 102, counterSize.x, counterSize.y};
		break;

	case Unit::SAP:
		rekt = {0, 68, counterSize.x, counterSize.y};
		break;

	case Unit::HINF:
		rekt = {54, 102, counterSize.x, counterSize.y};
		break;
	}

	return{*units, rekt};

}

sf::Sprite TextureManager::getSprite(Terrain type){

	sf::IntRect rekt;

	switch (type){
	case Terrain::MEADOW:
		rekt = {0, 0, size.x, size.y};
		break;

	case Terrain::HILLS:
		rekt = {54, 0, size.x, size.y};
		break;

	case Terrain::MUD:
		rekt = {108, 0, size.x, size.y};
		break;

	case Terrain::ROAD:
		rekt = {162, 0, size.x, size.y};
		break;

	case Terrain::SLOPES:
		rekt = {0, 54, size.x, size.y};
		break;

	case Terrain::URBAN:
		rekt = {54, 54, size.x, size.y};
		break;

	case Terrain::WATER:
		rekt = {108, 54, size.x, size.y};
		break;

	case Terrain::WOODS:
		rekt = {162, 54, size.x, size.y};
		break;
	}

	return{*terrain, rekt};

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

}

sf::Sprite TextureManager::getSprite(Flag type){

	sf::IntRect rekt;

	switch (type){
	case Flag::AUS:
		rekt = {0, 0, counterSize.x, counterSize.y};
		break;

	case Flag::PRU:
		rekt = {54, 0, counterSize.x, counterSize.y};
		break;

	case Flag::FRA:
		rekt = {108, 0, counterSize.x, counterSize.y};
		break;

	case Flag::GBR:
		rekt = {162, 0, counterSize.x, counterSize.y};
		break;

	case Flag::RUS:
		rekt = {0, 34, counterSize.x, counterSize.y};
		break;

	case Flag::BAV:
		rekt = {54, 34, counterSize.x, counterSize.y};
		break;
		
	case Flag::COM:
		rekt = {108, 34, counterSize.x, counterSize.y};
		break;

	case Flag::SPA:
		rekt = {162, 34, counterSize.x, counterSize.y};
		break;

	case Flag::POR:
		rekt = {0, 68, counterSize.x, counterSize.y};
		break;

	case Flag::VEN:
		rekt = {54, 68, counterSize.x, counterSize.y};
		break;

	case Flag::SAX:
		rekt = {108, 68, counterSize.x, counterSize.y};
		break;

	case Flag::SWE:
		rekt = {162, 68, counterSize.x, counterSize.y};
		break;

	case Flag::OTO:
		rekt = {0, 102, counterSize.x, counterSize.y};
		break;

	case Flag::CRI:
		rekt = {54, 102, counterSize.x, counterSize.y};
		break;

	case Flag::IME:
		rekt = {108, 102, counterSize.x, counterSize.y};
		break;

	case Flag::MOL:
		rekt = {162, 102, counterSize.x, counterSize.y};
		break;
	}

	return{*flags, rekt};

}

sf::Vector2i TextureManager::getSize() const{
	return size;
}

sf::Vector2i TextureManager::getCounterSize() const{
	return counterSize;
}

sf::Texture& TextureManager::getTerrainTexture() const{
	return *terrain;
}