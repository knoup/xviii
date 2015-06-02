#pragma once

#include "World.h"
#include "UnitTile.h"
#include "TextureManager.h"
#include "FontManager.h"

#include "Infantry.h"
#include "Artillery.h"
#include "Cavalry.h"
#include "Mortar.h"
#include "General.h"
#include "global.h"

class UnitLoader;

//Since each nation will only have one unique unit (and different names/flags), I felt it would be
//unnecessary to create classes for each. The exceptions to these are Crimea, the Ottomans, and
//the Mughals, who will have different units completely. These can simply be handled in the constructor.

#define NATIONPROPERTIES\
	X(Player::Nation::AUS, TextureManager::Flag::AUS, "Austria")\
	X(Player::Nation::BAV, TextureManager::Flag::BAV, "Bavaria")\
	X(Player::Nation::COM, TextureManager::Flag::COM, "Commonwealth")\
	X(Player::Nation::CRI, TextureManager::Flag::CRI, "Crimea")\
	X(Player::Nation::FRA, TextureManager::Flag::FRA, "France")\
	X(Player::Nation::GBR, TextureManager::Flag::GBR, "GBR")\
	X(Player::Nation::IME, TextureManager::Flag::IME, "Imereti")\
	X(Player::Nation::MOL, TextureManager::Flag::MOL, "Moldavia")\
	X(Player::Nation::OTO, TextureManager::Flag::OTO, "Ottoman Empire")\
	X(Player::Nation::POR, TextureManager::Flag::POR, "Portugal")\
	X(Player::Nation::PRU, TextureManager::Flag::PRU, "Prussia")\
	X(Player::Nation::RUS, TextureManager::Flag::RUS, "Russia")\
	X(Player::Nation::SAX, TextureManager::Flag::SAX, "Saxony")\
	X(Player::Nation::SPA, TextureManager::Flag::SPA, "Spain")\
	X(Player::Nation::SWE, TextureManager::Flag::SWE, "Sweden")\
	X(Player::Nation::VEN, TextureManager::Flag::VEN, "Venice")\
	X(Player::Nation::WAL, TextureManager::Flag::WAL, "Wallachia")\
	X(Player::Nation::PER, TextureManager::Flag::PER, "Persia")

class Player
{
	friend class SpawnableUnit;
    public:
		enum class Nation{ AUS, PRU, FRA, GBR, RUS, BAV, COM, SPA, POR, VEN, SAX, SWE, OTO, CRI, IME, MOL, WAL, PER};
		Player(UnitLoader& _unitLoader, World& _world, Nation _nation, std::mt19937& _mt19937, TextureManager& _tm, FontManager& _fm, bool _spawnedAtBottom);
		
		//Returns true if successfully spawned unit
		bool spawnUnit(std::string _name, sf::Vector2i _worldCoords);
		//Returns the unit's unique ptr if successfully removed
		UnitTile::unitPtr removeUnit(sf::Vector2i _worldCoords);
		UnitTile::unitPtr removeUnit(UnitTile* _unit);
		//For loading from a save game
		void loadUnit(std::string _name, sf::Vector2i _pos, UnitTile::Direction _dir, float _hp, float _mov, bool _hasMoved, bool _hasPartialRotated, bool _hasFullRotated, bool _hasMeleeAttacked, bool _hasRangedAttacked, bool _hasHealed, bool _squareFormationActive, bool _uniqueVariable);

		inline const World& getWorld() const{ return world; };
		inline int getDeploymentPoints() const{ return deploymentPoints; };
		inline int getMaxDeploymentPoints() const{ return maxDeploymentPoints; };
		inline std::string getName() const { return name; };
		inline sf::Color getnationColour() const{ return nationColour; };
		inline Nation getNation() const{ return nation; };
		inline bool isReady() const{ return ready; };
		inline void setReady(bool _value){ ready = _value; };
		inline sf::Sprite getNationFlag() const{ return nationFlag; };
		const std::vector<SpawnableUnit>& getSpawnableUnits() const{ return spawnableUnits; };
		inline const std::vector<UnitTile::unitPtr>& getUnits() const{ return units; };
		inline UnitTile* getGeneral() const { return general; };

		//Public because there is no real reason to make it private; it needs to be
		//constantly modified...
		sf::View view;
		
		//We need to define an overloaded == function in order to use this with
		//std::vector.find()
		bool operator== (const Player& _player){
			return this == &_player;
		}

		void drawUnits(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;

    private:
		UnitLoader& unitLoader;
        World& world;
		std::vector<UnitTile::unitPtr> units;
		UnitTile* general;
		
		std::vector<SpawnableUnit> spawnableUnits;

		Nation nation;
		sf::Color nationColour{sf::Color::White};
		sf::Sprite nationFlag;
		std::string name;

		std::mt19937& mt19937;

		TextureManager& tm;
		FontManager& fm;

		int deploymentPoints;
		bool ready;

		//If this player spawned at the lower part of the map, this is true. 
		const bool spawnedAtBottom;
		static const int maxDeploymentPoints{35};

};
