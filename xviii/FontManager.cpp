#include "stdafx.h"
#include "FontManager.h"


FontManager::FontManager()
{
	lucon.loadFromFile("assets/fonts/lucon.ttf");
	arial.loadFromFile("assets/fonts/arial.ttf");
}

const sf::Font& FontManager::getFont(Type _type) const{
	switch (_type){
	case Lucon:
		return lucon;
		break;
	case Arial:
		return arial;
		break;
	}
}