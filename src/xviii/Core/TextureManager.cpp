#include "xviii/Headers/stdafx.h"
#include "xviii/Core/TextureManager.h"

#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"

#include <string.h>


TextureManager::TextureManager() :
units{},
size{54, 54}, //Current: 54,54
counterSize{54, 34} //Current: 54,34
{
	terrain = std::move(texturePtr(new sf::Texture()));
	terrain->loadFromFile("assets/gfx/terrain.png");

	ui = std::move(texturePtr(new sf::Texture()));
	ui->loadFromFile("assets/gfx/ui.png");

	button = std::move(texturePtr(new sf::Texture()));
	button->loadFromFile("assets/gfx/button.png");

	flags = std::move(texturePtr(new sf::Texture()));
	flags->loadFromFile("assets/gfx/flags.png");

	boost::filesystem::recursive_directory_iterator end;

	for (boost::filesystem::recursive_directory_iterator it("assets/gfx/units"); it != end; ++it){
       std::string name = it->path().filename().leaf().stem().string();

       texturePtr texture = texturePtr(new sf::Texture());
       texture->loadFromFile("assets/gfx/units/" + name + ".png");

       if(!units.count(name)){
            units.insert(std::pair<std::string, texturePtr>(name, std::move(texture)));
            units[name]->setSmooth(true);
       }
	}
}

sf::Sprite TextureManager::getUnitSprite(std::string _textureID){
    if(units.count(_textureID)){
        return sf::Sprite{*(units[_textureID])};
    }
    //If the ID does not exist, return an empty sprite; to be changed later (?)
    else{
        return{};
    }
}

sf::Sprite TextureManager::getSprite(Terrain type){

	sf::IntRect rekt;

	switch (type){
	case Terrain::MEADOW:
		rekt = {0, 0, size.x, size.y};
		break;

	case Terrain::HILLS:
		rekt = {size.x, 0, size.x, size.y};
		break;

	case Terrain::MUD:
		rekt = {2 * size.x, 0, size.x, size.y};
		break;

	case Terrain::ROAD:
		rekt = {3 * size.x, 0, size.x, size.y};
		break;

	case Terrain::SLOPES:
		rekt = {0, size.y, size.x, size.y};
		break;

	case Terrain::URBAN:
		rekt = {size.x, size.y, size.x, size.y};
		break;

	case Terrain::WATER:
		rekt = {2 * size.x, size.y, size.x, size.y};
		break;

	case Terrain::WOODS:
		rekt = {3 * size.x, size.y, size.x, size.y};
		break;

    case Terrain::BRIDGE_VER:
        rekt = {0, 2*size.y, size.x, size.y};
        break;

    case Terrain::BRIDGE_HOR:
        rekt = {size.x, 2*size.y, size.x, size.y};
        break;

    case Terrain::TBRIDGE_VER:
        rekt = {2*size.x, 2*size.y, size.x, size.y};
        break;

    case Terrain::TBRIDGE_HOR:
        rekt = {3*size.x, 2*size.y, size.x, size.y};
        break;

    case Terrain::BLANK:
        return{};
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

	return{};

}

sf::Sprite TextureManager::getSprite(Flag type){

	sf::IntRect rekt;

	switch (type){
	case Flag::AUS:
		rekt = {0, 0, counterSize.x, counterSize.y};
		break;

	case Flag::PRU:
		rekt = {counterSize.x, 0, counterSize.x, counterSize.y};
		break;

	case Flag::FRA:
		rekt = {2 * counterSize.x, 0, counterSize.x, counterSize.y};
		break;

	case Flag::GBR:
		rekt = {3 * counterSize.x, 0, counterSize.x, counterSize.y};
		break;

	case Flag::RUS:
		rekt = {0, counterSize.y, counterSize.x, counterSize.y};
		break;

	case Flag::BAV:
		rekt = {counterSize.x, counterSize.y, counterSize.x, counterSize.y};
		break;

	case Flag::COM:
		rekt = {2 * counterSize.x, counterSize.y, counterSize.x, counterSize.y};
		break;

	case Flag::SPA:
		rekt = {3 * counterSize.x, counterSize.y, counterSize.x, counterSize.y};
		break;

	case Flag::POR:
		rekt = {0, 2 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Flag::VEN:
		rekt = {counterSize.x, 2 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Flag::SAX:
		rekt = {2 * counterSize.x, 2 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Flag::SWE:
		rekt = {3 * counterSize.x, 2 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Flag::OTO:
		rekt = {0, 3 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Flag::CRI:
		rekt = {counterSize.x, 3 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Flag::IME:
		rekt = {2 * counterSize.x, 3 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Flag::MOL:
		rekt = {3 * counterSize.x, 3 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Flag::WAL:
		rekt = {0, 4 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Flag::PER:
		rekt = {counterSize.x, 4 * counterSize.y, counterSize.x, counterSize.y};
		break;

    case Flag::DEN:
        rekt = {2 * counterSize.x, 4 * counterSize.y, counterSize.x, counterSize.y};
		break;
	}

	return{*flags, rekt};

}
