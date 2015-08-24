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

	for (boost::filesystem::recursive_directory_iterator it("assets/gfx/factions"); it != end; ++it){
       std::string name = it->path().filename().leaf().stem().string();

       texturePtr texture = texturePtr(new sf::Texture());
       texture->loadFromFile("assets/gfx/factions/" + name + ".png");

       if(!flags.count(name)){
            flags.insert(std::pair<std::string, texturePtr>(name, std::move(texture)));
            flags[name]->setSmooth(true);
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

sf::Sprite TextureManager::getFlagSprite(std::string _textureID){
    if(flags.count(_textureID)){
        return sf::Sprite{*(flags[_textureID])};
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
