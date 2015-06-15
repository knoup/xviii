#include "xviii/Headers/stdafx.h"
#include "xviii/Core/FontManager.h"


FontManager::FontManager()
{
	lucon.loadFromFile("assets/fonts/lucon.ttf");
	arial.loadFromFile("assets/fonts/arial.ttf");
	eighteen.loadFromFile("assets/fonts/eighteen.ttf");
}

const sf::Font& FontManager::getFont(Type _type) const{
	switch (_type){
	case Lucon:
		return lucon;
		break;
	case Arial:
		return arial;
		break;
	case Eighteen:
		return eighteen;
		break;
	}
}
