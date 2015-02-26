#pragma once

#include "TerrainTile.h"
#include "FontManager.h"

#include <random>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <math.h>

/*
TODO:

-Add LoS to movement


*/

class Player;
class World;

//A bit of forward declarations for the overloaded attack functions
class Infantry;
class Cavalry;
class Cuirassier;
class LightCav;
class Artillery;
class Mortar;
class General;

/*
	Note: due to the fact that static/const variables cannot be modified in derived classes,
	many functions that would otherwise have just inherited one clean function from UnitTile
	have to be redefined in each derived class. I found no other cleaner way around this;
	however, it is also useful in that it lets me give slightly different definitions
	to accomodate each class. 
	
	For example, the heal() function would be identical for all; it would, however, be
	unneccessary to have a body that does anything for the General class, since there can
	only ever be one general per player and he cannot heal himself. Also, not all the 
	derived classes need the same bools (only General needs hasHealed, only Infantry needs
	hasMoved, and so on).
*/


class UnitTile : public Tile
{
public:
	using unitPtr = std::unique_ptr<UnitTile>;
	enum class Direction{ N, E, S, W };
	enum class Modifier{NONE, CUIRASSIER, DISTANCE, FRONT_FLANK, SIDE_FLANK, REAR_FLANK};
	enum class UnitType{INF, CAV, CUIR, LCAV, DRAGOON, ART, MOR, GEN};

	//Used for storing modifier information

	struct ModifierReport{

		ModifierReport(Modifier _modType, float _modFloat) : 
		modType{_modType},
		modFloat{_modFloat}
		{
		}

		Modifier modType;
		float modFloat;
	};

	UnitTile(World& _world, std::mt19937&, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, TextureManager::Unit id, UnitType type, Direction _dir);
	//Create a virtual destructor, signifying this is an abstract class
	virtual ~UnitTile() = 0;

	//Very, very useful
	std::string roundFloat(const double x);

	UnitType getUnitType() const;

	int getCost() const;
	int getLimit() const;

	float gethp() const;
	int getMov() const;

	virtual void takeDamage(float _dmg);
	//Returns true if dead
	bool removeIfDead();

	UnitTile::Direction getDir() const;

	UnitTile::Direction opposite(UnitTile::Direction _dir);

	//Spawn is very similar to moveTo, but is only used during the setup phase; it costs no movement 
	void spawn(TerrainTile* terrainTile);

	//MAIN VIRTUAL FUNCTIONS:
	//They return strings for the output log...

    virtual std::string moveTo(TerrainTile* _terrainTile);
	//Called at the end of every turn;
	virtual void reset();
	virtual std::string rotate(Direction _dir);
	//Mainly used for the general to invoke the heal() function, but could be used for other things as well
	//hence the name
	virtual std::string interactWithFriendly(UnitTile* _unit);
	virtual std::string heal();

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;

	//This function is in charge of casting and then calling the appropriate overloaded class functions
	//below (see each derived's .cpp for the details of implementation). It also determines whether the combat
	//is melee or ranged
	std::string attack(UnitTile* _unit);

	virtual std::string attack(Infantry* inf, int distance, UnitTile::Modifier flank);
	virtual std::string attack(Cavalry* cav, int distance, UnitTile::Modifier flank);
	virtual std::string attack(Cuirassier* cuir, int distance, UnitTile::Modifier flank);
	virtual std::string attack(LightCav* lcav, int distance, UnitTile::Modifier flank);
	virtual std::string attack(Artillery* art, int distance, UnitTile::Modifier flank);
	virtual std::string attack(Mortar* mor, int distance, UnitTile::Modifier flank);
	virtual std::string attack(General* gen, int distance, UnitTile::Modifier flank);

	virtual std::string rangedAttack(UnitTile* unit, int distance);

	TerrainTile* getTilePos() const;
	Player* getPlayer() const;
	
	bool isHostile(UnitTile* _tile);
	//void highlightEnemy();

    //Manages the position of the sf::Text numbers (hp and movement)
	void updateStats();

	//Further documented in UnitTile.cpp
	virtual int distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _obstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits = false, int coneWidth = 1);
	//Overloaded version that only gets the distance and doesn't take in bools
	int distanceFrom(Tile* _tile);

	std::string dirToString(Direction _dir);
	std::string modToString(Modifier _mod);
	std::string typeToString(UnitType _type);

	std::string attackReport(int distance, UnitTile* attacker, UnitTile* defender, int attackerRoll, int defenderRoll, float attackerInflicted, float defenderInflicted, std::vector<ModifierReport>& thisModifiers, std::vector<ModifierReport>& enemyModifiers);

	bool getHasMoved() const;
	bool getHasRotated() const;
	bool getHasAttacked() const;
	bool getHasHealed() const;

	void sethp(float _hp);
	void setMov(float _mov);
	void setHasMoved(bool _hasMoved);
	void setHasRotated(bool _hasRotated);
	void setHasAttacked(bool _hasAttacked);
	//The following are applicable only for some children; the definition in UnitTile will be
	//blank
	void setHasHealed(bool _hasHealed);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	std::vector<ModifierReport> modVector;

	//Only ever needs to be used internally; making these so I don't have to copy and paste the same
	//code 20 times
	void multRollByModifiers(float &originalRoll);

protected:
	std::string outOfRange();

	World& world;
	std::mt19937& mt19937;

	//Pointer to the player the unit belongs to
	Player* player;

	//The unit's current direction (NESW)
	Direction dir;

	//In addition to each player having a flag, each unit itself must have a flag sprite too
	sf::Sprite unitFlag;
	
	//Pointer to the terrain tile that the unit is on. This is only to be used for units, to indicate
	//where they are easily and efficiently, since a unit must always be on a terrain tile
	TerrainTile* at;

	UnitType unitType;


	int deploymentCost;

	//0 represents no limit
	int limit;

	float hp;
	int mov;

	//The visual representations of the stats
    sf::Text dirText;
	sf::Text hpText;
	sf::Text movText;

	bool hasMoved{false};
	bool hasRotated{false};
	bool hasAttacked{false};

	bool waterCrosser{false};
};

