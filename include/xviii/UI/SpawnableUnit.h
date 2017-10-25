#pragma once

#include "xviii/Core/Player.h"

#include "xviii/Core/UnitLoader.h"

class SpawnableUnit
{
public:
	SpawnableUnit(Player* _player, std::string _unitID, sf::Vector2i _coords);
	//Copy constructor
	SpawnableUnit(const SpawnableUnit& _spawnableUnit);
	//Operator=
	SpawnableUnit & operator=(const SpawnableUnit& _spawnableUnit);

    //Data members

    std::string unitID;
	sf::Text unitName;
	sf::Sprite unitSprite;
	Player* player;
	UnitTile::UnitType type;

    ///////////////////////////////

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
		return{float(250 + ((coords.x - 1) * 100)), float(44 + ((coords.y - 1) * 70))};
	};
};

