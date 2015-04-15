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
#include "Akinci.h"
#include "Deli.h"
#include "Timarioti.h"
#include "Kapikulu.h"
#include "Grenadier.h"
#include "Janissary.h"
#include "OttoInf.h"
#include "LightInf.h"
#include "Sapper.h"
#include "CrimeanCav.h"
#include "CossackInf.h"
#include "KhevMkhedrebi.h"
#include "PitsisKatsebi.h"
#include "DonCossack.h"
#include "AbrMkhedrebi.h"
#include "MetTop.h"
#include "KudzeKaci.h"
#include "FootGuard.h"

#include "global.h"

//Since each nation will only have one unique unit (and different names/flags), I felt it would be
//unnecessary to create classes for each. The exceptions to these are Crimea, the Ottomans, and
//the Mughals, who will have different units completely. These can simply be handled in the constructor.

#define NATIONPROPERTIES\
	X(Player::Nation::AUS, TextureManager::Flag::AUS, "Austria")\
	X(Player::Nation::PRU, TextureManager::Flag::PRU, "Prussia")\
	X(Player::Nation::FRA, TextureManager::Flag::FRA, "France")\
	X(Player::Nation::GBR, TextureManager::Flag::GBR, "GBR")\
	X(Player::Nation::RUS, TextureManager::Flag::RUS, "Russia")\
	X(Player::Nation::BAV, TextureManager::Flag::BAV, "Bavaria")\
	X(Player::Nation::COM, TextureManager::Flag::COM, "Commonwealth")\
	X(Player::Nation::SPA, TextureManager::Flag::SPA, "Spain")\
	X(Player::Nation::POR, TextureManager::Flag::POR, "Portugal")\
	X(Player::Nation::VEN, TextureManager::Flag::VEN, "Venice")\
	X(Player::Nation::SAX, TextureManager::Flag::SAX, "Saxony")\
	X(Player::Nation::SWE, TextureManager::Flag::SWE, "Sweden")\
	X(Player::Nation::OTO, TextureManager::Flag::OTO, "Ottoman Empire")\
	X(Player::Nation::CRI, TextureManager::Flag::CRI, "Crimea")\
	X(Player::Nation::IME, TextureManager::Flag::IME, "Imereti")

class Player
{
    public:
		struct SpawnableUnit{
			sf::Text unitName;
			sf::Sprite unitSprite;
			UnitTile::UnitType type;

			SpawnableUnit(UnitTile::UnitType _type) :
				//Just the type used before it is properly loaded
				type{_type}
			{
			}

			int top() const{
				return unitSprite.getPosition().y - unitSprite.getLocalBounds().height / 2;
			}
			int left() const{
				return unitSprite.getPosition().x - unitSprite.getGlobalBounds().width / 2;
			}
			int bottom() const{
				return unitSprite.getPosition().y + unitSprite.getGlobalBounds().height / 2;
			}
			int right() const{
				return unitSprite.getPosition().x + unitSprite.getGlobalBounds().width / 2;
			}
		};


		enum class Nation{ AUS, PRU, FRA, GBR, RUS, BAV, COM, SPA, POR, VEN, SAX, SWE, OTO, CRI, IME};
		Player(World& _world, Nation _nation, std::mt19937& _mt19937, TextureManager& _tm, FontManager& _fm, bool _spawnedAtBottom);
		
		//Returns true if successfully spawned unit
		bool spawnUnit(UnitTile::UnitType _type, sf::Vector2i _worldCoords);
		//For loading from a save game
		void loadUnit(UnitTile::UnitType _type, sf::Vector2i _pos, UnitTile::Direction _dir, float _hp, float _mov, bool _hasMoved, bool _hasRotated, bool _hasMeleeAttacked, bool _hasRangedAttacked, bool _hasHealed);

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

		sf::Sprite getFlag() const;
		sf::Color getColour() const;
		Nation getNation() const;

		std::vector<SpawnableUnit>& getSpawnableUnits();

    private:
        World& world;
		
		std::vector<SpawnableUnit> spawnableUnits;

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
