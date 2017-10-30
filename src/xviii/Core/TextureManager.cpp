#include "xviii/Headers/stdafx.h"
#include "xviii/Core/TextureManager.h"

#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"

#include <string.h>


TextureManager::TextureManager(boost::random::mt19937& _randomEngine) :
units{},
flags{},
weather{},
randomBackground{nullptr},
terrain{nullptr},
ui{nullptr},
button{nullptr},
generalRange1{nullptr},
generalRange2{nullptr},
generalDead{nullptr},
size{54, 54}, //Current: 54,54
counterSize{54, 34} //Current: 54,34
{
	terrain = std::move(texturePtr(new sf::Texture()));
	terrain->loadFromFile("assets/gfx/terrain/terrain.png");

	ui = std::move(texturePtr(new sf::Texture()));
	ui->loadFromFile("assets/gfx/interface/ui.png");

	button = std::move(texturePtr(new sf::Texture()));
	button->loadFromFile("assets/gfx/interface/button.png");

    generalRange1 = std::move(texturePtr(new sf::Texture()));
	generalRange1->loadFromFile("assets/gfx/interface/range1.png");

    generalRange2 = std::move(texturePtr(new sf::Texture()));
	generalRange2->loadFromFile("assets/gfx/interface/range2.png");

    generalDead = std::move(texturePtr(new sf::Texture()));
	generalDead->loadFromFile("assets/gfx/interface/generaldead.png");

	boost::filesystem::recursive_directory_iterator rEnd;

	for (boost::filesystem::recursive_directory_iterator it(std::string("assets/gfx/units")); it != rEnd; ++it){
       std::string name = it->path().filename().leaf().stem().string();

       texturePtr texture = texturePtr(new sf::Texture());
       texture->loadFromFile("assets/gfx/units/" + name + ".png");

       if(!units.count(name)){
            units.insert(std::pair<std::string, texturePtr>(name, std::move(texture)));
            units[name]->setSmooth(true);
       }
	}

	for (boost::filesystem::recursive_directory_iterator it(std::string("assets/gfx/factions")); it != rEnd; ++it){
       std::string name = it->path().filename().leaf().stem().string();

       texturePtr texture = texturePtr(new sf::Texture());
       texture->loadFromFile("assets/gfx/factions/" + name + ".png");

       if(!flags.count(name)){
            flags.insert(std::pair<std::string, texturePtr>(name, std::move(texture)));
            flags[name]->setSmooth(true);
       }
	}

	for (boost::filesystem::recursive_directory_iterator it(std::string("assets/gfx/weather")); it != rEnd; ++it){
       std::string name = it->path().filename().leaf().stem().string();

       texturePtr texture = texturePtr(new sf::Texture());
       texture->loadFromFile("assets/gfx/weather/" + name + ".png");

       if(!weather.count(name)){
            weather.insert(std::pair<std::string, texturePtr>(name, std::move(texture)));
            weather[name]->setSmooth(true);
       }
	}


	randomBackground = std::move(std::unique_ptr<sf::Texture>(new sf::Texture()));

	std::vector<boost::filesystem::path> paths;
	boost::filesystem::directory_iterator end;

	if (boost::filesystem::exists(std::string("assets/gfx/backgrounds"))){
		for (boost::filesystem::directory_iterator it(std::string("assets/gfx/backgrounds")); it != end; ++it){
			paths.push_back(it->path());
		}
	}

	if (!paths.empty()){
		boost::random::uniform_int_distribution<int> dist(0, paths.size() - 1);
		int randomIndex{dist(_randomEngine)};
		std::string randomPath{paths[randomIndex].string()};

		randomBackground->loadFromFile(randomPath);
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

sf::Sprite TextureManager::getWeatherSprite(std::string _textureID){
    if(weather.count(_textureID)){
        return sf::Sprite{*(weather[_textureID])};
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

    case UI::GENERALRANGE1:{
        return sf::Sprite{*generalRange1};
        }

    case UI::GENERALRANGE2:{
        return sf::Sprite{*generalRange2};
        }

    case UI::GENERALDEAD:{
        return sf::Sprite{*generalDead};
        }
	}

	return{};
}

sf::Sprite TextureManager::getRandomBackground(){
    return {*randomBackground, sf::IntRect(0,0, randomBackground->getSize().x, randomBackground->getSize().y)};
}
