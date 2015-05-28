#pragma once

#include "TerrainTile.h"
#include "FontManager.h"

#include <random>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <math.h>

#include "messages.h"

class UnitLoader;

#define MAINTYPEPROPERTIES\
	X("INF", UnitTile::UnitType::INF, Infantry)\
	X("CAV", UnitTile::UnitType::CAV, Cavalry)\
	X("MOR", UnitTile::UnitType::MOR, Mortar)\
	X("GEN", UnitTile::UnitType::GEN, General)\
	X("ARTGUARD", UnitTile::UnitType::ARTGUARD, Infantry)


#define FAMILYTYPEPROPERTIES\
	X("LINF", UnitTile::UnitFamily::LINF_FAMILY)\
	X("INF", UnitTile::UnitFamily::INF_FAMILY)\
	X("HINF", UnitTile::UnitFamily::HINF_FAMILY)\
	X("CAV", UnitTile::UnitFamily::CAV_FAMILY)\
	X("ART", UnitTile::UnitFamily::ART_FAMILY)\


class Player;

class Infantry;
class Cavalry;
class Artillery;
class Mortar;
class General;

class UnitTile : public Tile
{
public:
	using unitPtr = std::unique_ptr<UnitTile>;

	enum class Direction{ N, E, S, W };

	enum class Modifier{NONE, ADDITIONAL, DMG, ATK, DISTANCE, FRONT_FLANK, SIDE_FLANK, REAR_FLANK};

	enum class UnitType{INF, CAV, ART, MOR, GEN, ARTGUARD};

	//Each UnitFamily generally has its own combat rules. LINF, however, does not, and for the moment, HINF's
	//is identical to INF.
	enum class UnitFamily{LINF_FAMILY, INF_FAMILY, HINF_FAMILY, CAV_FAMILY, ART_FAMILY};

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

	struct RangedAttackRange{
		RangedAttackRange(int _lower, int _upper, float _distModifier, bool _modifierIsDamage = false, int _lowerDieThreshold = 1, int _upperDieThreshold = 6) :
			lowerThreshold{_lower},
			upperThreshold{_upper},
			lowerDieThreshold{_lowerDieThreshold},
			upperDieThreshold{_upperDieThreshold},
			distModifier{_distModifier}
		{
		}

		//The lower and upper thresholds specify the range at which the accompanying distModifier will 
		//take effect. For example, if:
		//lowerThreshold = 3;
		//upperThreshold = 5;
		//distModifier = 1.5;
		//Then the unit will get a distance modifier of 1.5 when shooting at a distance between 3 and 5 (inclusive)

		//The optional lower and upper die roll variables only allow damage to be inflicted if the player's roll
		//is between their values; it defaults to 1 and 6

		//The optional modifierIsDamage variable specifies whether the distModifier is a multiplicational damage modifier 
		//or directly damage (1.5d or 1.5 dmg)

		int lowerThreshold;
		int upperThreshold;

		int lowerDieThreshold;
		int upperDieThreshold;

		float distModifier;
		bool modifierIsDamage;
	};

	struct HealingRange{
		HealingRange(int _lower, int _upper, float _healingAmount) :
			lowerThreshold{_lower},
			upperThreshold{_upper},
			healingAmount{_healingAmount}
		{
		}

		//Note that an upper and lower threshold of both 0 means unlimited healing range

		int lowerThreshold;
		int upperThreshold;
		float healingAmount;
	};

	UnitTile(UnitLoader& _unitLoader, World& _world, std::mt19937&, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, TextureManager::Unit id, UnitType type, UnitFamily familyType, Direction _dir);
	//Create a virtual destructor, signifying this is an abstract class
	virtual ~UnitTile() = 0;

	//Getters
	//////////////////////////////////////////////////////////////////////////////////////////////////

	//Non-Virtual
	inline TerrainTile* getTerrain() const{ return terrain; };
	inline Player* getPlayer() const{ return player; };
	inline UnitType getUnitType() const{ return unitType; };
	inline UnitFamily getUnitFamilyType() const { return unitFamilyType; };
	inline float gethp() const{ return hp; };
	inline int getMov() const{	return mov;	};
	inline UnitTile::Direction getDir() const{ return dir; };

	inline bool getHasMoved() const{ return hasMoved; };
	inline bool getHasPartialRotated() const{ return hasPartialRotated; };
	inline bool getHasFullRotated() const{ return hasFullRotated; };
	inline bool getHasAnyRotated() const{ return (hasPartialRotated || hasFullRotated); };
	inline bool getHasMeleeAttacked() const{ return hasMeleeAttacked; };
	inline bool getHasRangedAttacked() const{ return hasRangedAttacked; };
	inline bool getHasAnyAttacked() const{ return (hasMeleeAttacked || hasRangedAttacked); };
	inline bool getHasHealed() const{ return hasHealed; };

	bool getMelee() const;
	bool getSkirmish() const;
	bool getFrightening() const;
	bool getLancer() const;

	//Virtual
	inline virtual int getCost() const{ return 100; };
	inline virtual int getLimit() const{ return 1; };
	inline virtual int getMaxHp() const{ return 0; };
	inline virtual int getMaxMov() const{ return 0; };
	int getMaxRange() const;

	bool canHeal() const;
	bool canRangedAttack() const;
	

	//Each class will have an overloaded definition returning its specific flank modifier for either 
	//INF or CAV family units. In the interest of keeping the modifiers static, each class will have 
	//its own implementation of essentially the same function.
	inline virtual float getFlankModifier(UnitFamily _family, Modifier _flank) const{ return 0; };

	//////////////////////////////////////////////////////////////////////////////////////////////////

	//Setters
	//////////////////////////////////////////////////////////////////////////////////////////////////

	inline void sethp(float _hp){ hp = _hp; };
	inline void setMov(float _mov){ mov = _mov; };
	inline void setDir(Direction _dir){ dir = _dir; };
	inline void setHasMoved(bool _hasMoved){ hasMoved = _hasMoved; };
	inline void setHasPartialRotated(bool _hasPartialRotated){ hasPartialRotated = _hasPartialRotated; };
	inline void setHasFullRotated(bool _hasFullRotated){ hasFullRotated = _hasFullRotated; };
	inline void setHasMeleeAttacked(bool _value){ hasMeleeAttacked = _value; };
	inline void setHasRangedAttacked(bool _value){ hasRangedAttacked = _value; };
	inline void setHasHealed(bool _value){ hasHealed = _value; };

	//////////////////////////////////////////////////////////////////////////////////////////////////

	//The following are applicable only for some children
	inline virtual void setUniqueVariable(bool _uniqueVariable){};
	inline virtual bool getUniqueVariable() const{ return false; };

	//////////////////////////////////////////////////////////////////////////////////////////////////

	//Other - Virtual
	//////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void takeDamage(UnitTile* attacker, float& _dmg, int distance);
	virtual std::string moveTo(TerrainTile* _terrainTile);
	//Called at the end of every turn;
	virtual void reset();
	inline virtual std::string rotate(Direction _dir){ return{}; };

	//This function is unit-specific, and checks for such things as vs. family bonuses/maluses. The bool specifies
	//whether the unit is attacking or defending
	inline virtual void preMeleeAttack(UnitTile* unit, bool attacking){};

	//Needed for double dispatch
	virtual std::string meleeAttack(UnitTile* _unit) = 0;

	inline virtual std::string meleeAttack(Infantry* inf){ return{}; };
	inline virtual std::string meleeAttack(Cavalry* cav){ return{}; };
	inline virtual std::string meleeAttack(Artillery* art){ return{}; };
	inline virtual std::string meleeAttack(Mortar* mor){ return{}; };

	virtual std::string rangedAttack(UnitTile* unit, int distance);

	//Further documented in UnitTile.cpp
	virtual sf::Vector2i distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _obstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits = false, int coneWidth = 1);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	//////////////////////////////////////////////////////////////////////////////////////////////////


	//Other - Non Virtual
	//////////////////////////////////////////////////////////////////////////////////////////////////
	std::string heal(UnitTile* _unit);
	std::string beHealed(float num);
	void calculateEffectiveMov();

	//Returns true if dead
	bool removeIfDead();

	UnitTile::Direction opposite(UnitTile::Direction _dir);

	//Spawn is very similar to moveTo, but is only used during the setup phase; it costs no movement 
	void spawn(TerrainTile* terrainTile);

	//This function is in charge of initiating combat by determining distance, flank, etc. and calling either
	//meleeAttack() or rangedAttack()
	std::string attack(UnitTile* _unit);

	bool isHostile(UnitTile* _tile);

    //Manages the position of the sf::Text numbers (hp and movement)
	void updateStats();

	//Overloaded version that only gets the distance and doesn't take in bools
	int distanceFrom(Tile* _tile);

	std::string dirToString();
	std::string modToString(ModifierReport _mod);
	std::string typeToString();

	std::string attackReport(int distance, UnitTile* attacker, UnitTile* defender, int attackerRoll, int defenderRoll, float attackerInflicted, float defenderInflicted, bool retreat = false);	

	void multRollByModifiers(float &originalRoll);
	std::string roundFloat(const double x);

	//////////////////////////////////////////////////////////////////////////////////////////////////

	//Data member
	std::vector<ModifierReport> modVector;

protected:
	std::mt19937& mt19937;

	//Pointer to the player the unit belongs to
	Player* player;

	//The unit's current direction (NESW)
	Direction dir;

	//In addition to each player having a flag, each unit itself must have a flag sprite too
	sf::Sprite unitFlag;
	//Pointer to the terrain tile that the unit is on. This is only to be used for units, to indicate
	//where they are easily and efficiently, since a unit must always be on a terrain tile
	TerrainTile* terrain;

	//For (yellow) outlining
	sf::RectangleShape yellowOutline;
	//For (red) outlining
	sf::RectangleShape redOutline;

	//The visual representations of the stats
    sf::Text dirText;
	sf::Text hpText;
	sf::Text movText;

	//This string serves both as a name and as a unique ID to the custom defined unit type
	std::string name;

	UnitType unitType;
	UnitFamily unitFamilyType;

	UnitLoader& unitLoader;

	float hp;
	int mov;

	bool hasMoved{false};
	bool hasPartialRotated{false};
	bool hasFullRotated{false};
	bool hasMeleeAttacked{false};
	bool hasRangedAttacked{false};
	bool hasHealed{false};
};

