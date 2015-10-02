#pragma once

#include "xviii/Core/MasterManager.h"

#include "xviii/Units/UnitTile.h"
#include "xviii/Terrain/TerrainTile.h"
#include <unordered_set>

#include "xviii/Terrain/Meadow.h"
#include "xviii/Terrain/Hills.h"
#include "xviii/Terrain/Mud.h"
#include "xviii/Terrain/Slopes.h"
#include "xviii/Terrain/Road.h"
#include "xviii/Terrain/Hills.h"
#include "xviii/Terrain/Urban.h"
#include "xviii/Terrain/Water.h"
#include "xviii/Terrain/Woods.h"
#include "xviii/Terrain/Bridge.h"
#include "xviii/Terrain/TBridge.h"

#define ERAPROPERTIES\
	X("EARLY", World::Era::EARLY)\
	X("MID", World::Era::MID)\
	X("LATE", World::Era::LATE)\
	X("ALL", World::Era::ALL)

//The first number indicates how much shorter the unit view distance is during this weather,
//the second, how much further the flag view distance is

#define WEATHERPROPERTIES\
	X("light fog", World::Weather::LIGHT_FOG, 2, 2)\
    X("heavy fog", World::Weather::HEAVY_FOG, 4, 4)\
	X("light rain", World::Weather::LIGHT_RAIN, 1, 1)\
	X("heavy rain", World::Weather::HEAVY_RAIN, 2, 2)


class TerrainLoader;

class World : public sf::Drawable, public sf::NonCopyable
{
	friend class Ant;
	friend class RiverAnt;
	friend class SlopeAnt;
	friend class HillAnt;
	friend class BridgeAnt;
	friend class SaveGame;
	//For easier access to the vertex array
	friend class TerrainTile;
public:

    ////////////////////////////////////////////
    static const int minutesPerTurn{15};
    ////////////////////////////////////////////

	enum class Era{ EARLY, MID, LATE, ALL };

	enum class Weather
                {
                LIGHT_FOG,
                HEAVY_FOG,
                LIGHT_RAIN,
                HEAVY_RAIN
                };

    //A basic 24h clock
	struct Time{

        Time(){
            set(10, 0);
        }

        void set(int _hour, int _minutes){
            int appendedHours = _minutes/60;
            int resultantMinutes = _minutes%60;

            _hour += appendedHours;
            HHMM.second = resultantMinutes;

            if(_hour > 23){
                HHMM.first = 0;
            }
            //In case a negative hour is somehow passed as an argument
            else if(_hour < 0){
                HHMM.first = 12;
            }

            else{
                HHMM.first = _hour;
            }
        }

        void increment(){
            set(HHMM.first, HHMM.second+minutesPerTurn);
        }

        std::pair<int,int> getTime(){
            return HHMM;
        }

        private:
            std::pair<int,int> HHMM;

	};

	World(MasterManager& _mManager, sf::Vector2i _dimensions);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;

	void generateRandomWorld(Era _era);

	int indexAtPixelPos(sf::Vector2i _pos) const;
	int indexAtCartesianPos(sf::Vector2i _pos) const;
	int indexAtTile(Tile& _tile) const;
	sf::Vector2i cartesianPosAtIndex(int _index) const;
	sf::Vector2i cartesianPosAtPixelPos(sf::Vector2i _pos) const;
	sf::Vector2f pixelPosAtCartesianPos(sf::Vector2i _pos) const;
	sf::Vector2f pixelPosAtIndex(int _index) const;

	//Returns true if the terrain tile at this position is unoccupied
	bool canBePlacedAtPixelPos(sf::Vector2i _pos);
	bool canBePlacedAtCartesianPos(sf::Vector2i _pos);

	bool pixelPosOutOfBounds(sf::Vector2i _pos);
	bool cartesianPosOutOfBounds(sf::Vector2i _pos);

	//Returns a [regular] pointer to the unit at this mouse coordinate position, if there is any
	UnitTile* unitAtPixelPos(sf::Vector2i _pos);
	UnitTile* unitAtTerrain(TerrainTile* _terrain);

	TerrainTile* terrainAtPixelPos(sf::Vector2i _pos);
	TerrainTile* terrainAtCartesianPos(sf::Vector2i _pos);

	const std::vector<UnitTile*>& getDamagedUnits() const;
	const int getElapsedTurns() const{ return elapsedTurns;};
	void setElapsedTurns(int _elapsedTurns){ elapsedTurns = _elapsedTurns; };
	void incrementElapsedTurns(){ elapsedTurns+=1; };

	sf::Vector2i getDimensions() const;
	sf::Vector2i getDimensionsInPixels() const;
	inline World::Era getEra() const{ return era; };
	inline std::vector<std::pair<Weather,int>>& getWeatherEffects() {return weatherEffects;};
	inline void setEra(Era _era){era = _era;}
	inline void addWeatherEffect(Weather _weatherEffect, int _weatherTime){weatherEffects.push_back(std::make_pair(_weatherEffect, _weatherTime));};

	inline Time& getCurrentTime(){return currentTime;};

	void addToDamagedUnits(UnitTile* unit);
	void clearDamagedUnits();

	//These functions replace the water tile with a P/T bridge, or destroy it and replace it
	//with a water tile, depending on what the tile is.
	void toggleBridge(TerrainTile* terrain, TerrainTile::Orientation _or);
	void toggleTBridge(TerrainTile* terrain, TerrainTile::Orientation _or);

    //This function ensures the connection variables for bridges are properly set
    void connectBridges();

    //This function finds all temporary bridges between the current and destination tile (minus one) and decrements
    //one hit point (used when units cross it)
    void wearDownTempBridges(TerrainTile* currentTile, TerrainTile* destinationTile);

    void turnlyUpdate();

    void calculateViewDistance(UnitTile* unit);

    void highlightVisibleTiles();

    //Ants and Tiles use this too; since they will always exist in a world, there is no point in them having
    //duplicate references to the master manager.
    MasterManager& masterManager;

private:
    void addWeather();

    int getWeatherUnitViewDistance() const;
    int getWeatherFlagViewDistance() const;

	sf::Vector2i dimensions;
	sf::Vector2i dimensionsInPixels;

	int elapsedTurns{0};
	Era era;

	std::vector<std::pair<Weather,int>> weatherEffects;
	Time currentTime;

	//The first layer, or "terrain layer"; always drawn behind the units and only consists
	//of Terrain.
	std::vector<TerrainTile::terrainPtr> terrainLayer;
	//Also, store regular pointers of bridges in these vectors, for convenience
	std::vector<Bridge*> permanentBridges;
	std::vector<TBridge*> temporaryBridges;


	//This vector stores pointers to the units that have been damaged during an attack. It is reset afterwards
	std::vector<UnitTile*> damagedUnits;

    std::unordered_set<TerrainTile*> visibleTiles;

	//Used for drawing efficiency
	sf::VertexArray mTerrainVertices;
	sf::Texture& mTerrainTexture;

};

/*

int tileAtPosition(int x, int y) const;
sf::Vector2i tileAtPosition(int index);

*/
