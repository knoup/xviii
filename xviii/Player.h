#pragma once

#include "World.h"
#include "UnitTile.h"
#include "TextureManager.h"
#include "FontManager.h"

#include "Infantry.h"
#include "Artillery.h"
#include "Cavalry.h"
#include "Cuirassier.h"
#include "Dragoon.h"
#include "LightCav.h"
#include "Mortar.h"
#include "General.h"

#include "global.h"

class Player
{
    public:
		enum class Nation{ AUS, PRU, FRA, GBR, RUS, BAV, COM, SPA, POR, VEN, SAX, SWE};
		Player(World& _world, Nation _nation, std::mt19937& _mt19937, TextureManager& _tm, FontManager& _fm, bool _spawnedAtBottom);
		
		//Returns true if successfully spawned unit
		bool spawnUnit(UnitTile::UnitType _type, sf::Vector2i _worldCoords);
		//For loading from a save game
		void loadUnit(UnitTile::UnitType _type, sf::Vector2i _pos, UnitTile::Direction _dir, float _hp, float _mov, bool _hasMoved, bool _hasRotated, bool _hasAttacked, bool _hasHealed);

		//Returns true if succesfully removed unit
		bool removeUnit(sf::Vector2i _worldCoords);

        const World& getWorld() const;
		int getDeploymentPoints() const;
		std::string getName() const;

		bool isReady() const;
		void setReady(bool _value);

		//Public because there is no real reason to make it private; it needs to be
		//constantly modified...
		sf::View view;
		
		//We need to define an overloaded == function in order to use this with
		//std::vector.find()
		bool operator== (const Player& _player){
			return this == &_player;
		}

		sf::Sprite nationToSprite(Player::Nation _nation);

		sf::Sprite getFlag() const;
		sf::Color getColour() const;
		Nation getNation() const;

    private:
        World& world;

		Nation nation;
		sf::Color nationColour{sf::Color::White};
		sf::Sprite playerFlag;
		std::string name;

		std::mt19937& mt19937;

		TextureManager& tm;
		FontManager& fm;

		int deploymentPoints;
		bool ready;

		//If this player spawned at the lower part of the map, this is true. 
		const bool spawnedAtBottom;

};
