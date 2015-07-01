#pragma once

#include "xviii/Core/Tile.h"
#include "xviii/Units/UnitTile.h"

#define TERRAINPROPERTIES\
	X(TerrainTile::TerrainType::MEADOW, Meadow, TextureManager::Terrain::MEADOW, "meadow")\
	X(TerrainTile::TerrainType::HILLS, Hills, TextureManager::Terrain::HILLS, "hills")\
	X(TerrainTile::TerrainType::MUD, Mud, TextureManager::Terrain::MUD, "mud")\
	X(TerrainTile::TerrainType::ROAD, Road, TextureManager::Terrain::ROAD, "road")\
	X(TerrainTile::TerrainType::SLOPES, Slopes, TextureManager::Terrain::SLOPES, "slopes")\
	X(TerrainTile::TerrainType::URBAN, Urban, TextureManager::Terrain::URBAN, "urban")\
	X(TerrainTile::TerrainType::WATER, Water, TextureManager::Terrain::WATER, "water")\
	X(TerrainTile::TerrainType::WOODS, Woods, TextureManager::Terrain::WOODS, "woods")\
	X(TerrainTile::TerrainType::BRIDGE, Bridge, TextureManager::Terrain::BRIDGE_VER, "bridge")\
	X(TerrainTile::TerrainType::TBRIDGE, TBridge, TextureManager::Terrain::TBRIDGE_VER, "tbridge")


class Meadow;
class Hills;
class Mud;
class Road;
class Slopes;
class Urban;
class Water;
class Woods;
class Bridge;

class TerrainLoader;
class World;
class UnitTile;

class TerrainTile : public Tile
{
public:
    struct UnitMainTypeBonus{
        UnitMainTypeBonus(UnitTile::UnitType _mainType, float _modifier, bool _isAdditional,
                          bool _inMelee, bool _inRanged, bool _whenAttacking, bool _whenDefending):
        mainType{_mainType},
        modifier{_modifier},
        isAdditional{_isAdditional},
        inMelee{_inMelee},
        inRanged{_inRanged},
        whenAttacking{_whenAttacking},
        whenDefending{_whenDefending}
        {
        }

        UnitTile::UnitType mainType;
        float modifier;
        bool isAdditional;
        bool inMelee;
        bool inRanged;
        bool whenAttacking;
        bool whenDefending;
    };

    struct UnitFamilyTypeBonus{

     UnitFamilyTypeBonus(UnitTile::UnitFamily _familyType, float _modifier, bool _isAdditional,
                          bool _inMelee, bool _inRanged, bool _whenAttacking, bool _whenDefending):
        familyType{_familyType},
        modifier{_modifier},
        isAdditional{_isAdditional},
        inMelee{_inMelee},
        inRanged{_inRanged},
        whenAttacking{_whenAttacking},
        whenDefending{_whenDefending}
        {
        }

        UnitTile::UnitFamily familyType;
        float modifier;
        bool isAdditional;
        bool inMelee;
        bool inRanged;
        bool whenAttacking;
        bool whenDefending;

    };

    struct UnitStringBonus{

     UnitStringBonus(std::string _name, float _modifier, bool _isAdditional,
                          bool _inMelee, bool _inRanged, bool _whenAttacking, bool _whenDefending):
        name{_name},
        modifier{_modifier},
        isAdditional{_isAdditional},
        inMelee{_inMelee},
        inRanged{_inRanged},
        whenAttacking{_whenAttacking},
        whenDefending{_whenDefending}
        {
        }

        std::string name;
        float modifier;
        bool isAdditional;
        bool inMelee;
        bool inRanged;
        bool whenAttacking;
        bool whenDefending;

    };

	using terrainPtr = std::unique_ptr<TerrainTile>;
	enum class TerrainType{ MEADOW, HILLS, MUD, ROAD, SLOPES, URBAN, WATER, WOODS, BRIDGE, TBRIDGE};
	enum class Orientation{VERTICAL, HORIZONTAL};

	TerrainTile(TerrainLoader& _terrainLoader, World& _world, TextureManager& tm, TextureManager::Terrain textType, TerrainType terrainType, sf::Vector2f _pos);
	virtual ~TerrainTile() = 0;

	void setPos(sf::Vector2f _pos);
	void refreshVertexArray();

	TerrainType getTerrainType() const;

	void setUnit(UnitTile* _unit);
	UnitTile* getUnit();
	void resetUnit();
    void applyModifiers(UnitTile* _unit, int _distance, bool _attacking);


    virtual void takeDamage(int dmg){};

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//Needed for double dispatch; hacky solution, possibly fix this in future
    virtual std::string callTerrainAttack(UnitTile* unit, int distance) = 0;

protected:
    TerrainLoader& terrainLoader;
	TerrainType terrainType;
	UnitTile* unit;
};

