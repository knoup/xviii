#pragma once

#include "xviii/Core/Player.h"

#include "xviii/Core/UnitLoader.h"

class SpawnableUnit
{
public:
	//Data members

	sf::Text unitName;
	sf::Sprite unitSprite;
	Player* player;
	UnitTile::UnitType type;

	SpawnableUnit(Player* _player, std::string _name, sf::Vector2i _coords) :
		player{_player}
	{
		unitName.setFont(player->masterManager.fontManager->getFont(FontManager::Type::Lucon));
		unitName.setColor(sf::Color::White);
		unitName.setCharacterSize(12);

		unitName.setString(_name);

		TextureManager::Unit textureType = player->masterManager.unitLoader->customClasses.at(_name).texture;
		unitSprite = player->masterManager.textureManager->getSprite(textureType);

		unitSprite.setOrigin(unitSprite.getGlobalBounds().width / 2, unitSprite.getGlobalBounds().height / 2);
		unitName.setOrigin(unitName.getLocalBounds().width / 2, unitName.getLocalBounds().height / 2);
		unitSprite.setPosition(getSelectablePos(_coords));
		unitName.setPosition({unitSprite.getPosition().x, unitSprite.getPosition().y - 30});
	}


	//Member functions

	inline int top() const{
		return unitSprite.getPosition().y - unitSprite.getLocalBounds().height / 2;
	}
	inline int left() const{
		return unitSprite.getPosition().x - unitSprite.getGlobalBounds().width / 2;
	}
	inline int bottom() const{
		return unitSprite.getPosition().y + unitSprite.getGlobalBounds().height / 2;
	}
	inline int right() const{
		return unitSprite.getPosition().x + unitSprite.getGlobalBounds().width / 2;
	}

private:
	inline sf::Vector2f getSelectablePos(sf::Vector2i coords){
		return{float(250 + ((coords.x - 1) * 100)), float(-130 + ((coords.y - 1) * 70))};
	};
};

