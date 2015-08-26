#pragma once

#include "xviii/Core/World.h"
#include "xviii/Units/UnitTile.h"

#include "xviii/Core/MasterManager.h"

#include "xviii/Units/Infantry.h"
#include "xviii/Units/Artillery.h"
#include "xviii/Units/Cavalry.h"
#include "xviii/Units/Mortar.h"
#include "xviii/Units/General.h"
#include "xviii/Units/Sapper.h"
#include "xviii/Headers/global.h"

class SpawnableUnit;

class Player
{
	friend class SpawnableUnit;
    public:
		Player(MasterManager& _masterManager, World& _world, std::string _factionID, bool _spawnedAtBottom);

		//Returns true if successfully spawned unit
		bool spawnUnit(std::string _name, sf::Vector2i _worldCoords);
		//Returns the unit's unique ptr if successfully removed
		UnitTile::unitPtr removeUnit(sf::Vector2i _worldCoords);
		UnitTile::unitPtr removeUnit(UnitTile* _unit);
		//For loading from a save game
		void loadUnit(std::string _name, sf::Vector2i _pos, UnitTile::Direction _dir, float _hp, float _mov, bool _hasMoved, bool _hasPartialRotated, bool _hasFullRotated, bool _hasMeleeAttacked, bool _hasRangedAttacked, bool _hasHealed, bool _squareFormationActive, bool _limber, bool _lancerBonusReady);

		inline const World& getWorld() const{ return world; };
		inline int getDeploymentPoints() const{ return deploymentPoints; };
		inline int getMaxDeploymentPoints() const{ return maxDeploymentPoints; };
		inline sf::Color getnationColour() const{ return nationColour; };
		inline std::string getFactionID() const{ return factionID; };
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
        MasterManager& masterManager;

        World& world;
		std::vector<UnitTile::unitPtr> units;
		UnitTile* general;

		std::vector<SpawnableUnit> spawnableUnits;

		std::string factionID;
		sf::Color nationColour{sf::Color::White};
		sf::Sprite nationFlag;

		int deploymentPoints;
		bool ready;

		//If this player spawned at the lower part of the map, this is true.
		const bool spawnedAtBottom;
		static const int maxDeploymentPoints{35};

};
