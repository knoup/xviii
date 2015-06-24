#include "xviii/Headers/stdafx.h"
#include "xviii/Core/TextureManager.h"


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

	case Unit::LCAV:
		rekt = {counterSize.x, 0, counterSize.x, counterSize.y};
		break;

	case Unit::CAV:
		rekt = {2 * counterSize.x, 0, counterSize.x, counterSize.y};
		break;

	case Unit::CUIR:
		rekt = {0, counterSize.y, counterSize.x, counterSize.y};
		break;

	case Unit::MOR:
		rekt = {counterSize.x, counterSize.y, counterSize.x, counterSize.y};
		break;

	case Unit::ART:
		rekt = {2 * counterSize.x, counterSize.y, counterSize.x, counterSize.y};
		break;

	case Unit::SAP:
		rekt = {0, 2 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Unit::DRAG:
		rekt = {counterSize.x, 2 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Unit::GRE:
		rekt = {2 * counterSize.x, 2 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Unit::GEN:
		rekt = {0, 3 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Unit::HINF:
		rekt = {counterSize.x, 3 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Unit::LINF:
		rekt = {2 * counterSize.x, 3 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Unit::ARTGUARD:
		rekt = {0, 4 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Unit::PIKE:
		rekt = {counterSize.x, 4 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Unit::LAN:
		rekt = {2 * counterSize.x, 4 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Unit::ARMLAN:
		rekt = {0, 5 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Unit::IRR:
		rekt = {counterSize.x, 5 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Unit::HARCH:
		rekt = {2 * counterSize.x, 5 * counterSize.y , counterSize.x, counterSize.y};
		break;

	case Unit::LART:
		rekt = {0, 6 * counterSize.y, counterSize.x, counterSize.y};
		break;

	case Unit::LDRAG:
		rekt = {counterSize.x, 6 * counterSize.y, counterSize.x, counterSize.y};
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
