#pragma once

#include "xviii/Core/FontManager.h"
#include "xviii/Core/Tile.h"

#include <boost/random.hpp>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <math.h>

#include "xviii/Headers/messages.h"

#define MAINTYPEPROPERTIES\
	X("INF", UnitTile::UnitType::INF, Infantry)\
	X("CAV", UnitTile::UnitType::CAV, Cavalry)\
	X("ART", UnitTile::UnitType::ART, Artillery)\
	X("MOR", UnitTile::UnitType::MOR, Mortar)\
	X("GEN", UnitTile::UnitType::GEN, General)\
	X("ARTGUARD", UnitTile::UnitType::ARTGUARD, Infantry)\
	X("SAP", UnitTile::UnitType::SAP, Sapper)


#define FAMILYTYPEPROPERTIES\
	X("LINF", UnitTile::UnitFamily::LINF_FAMILY)\
	X("INF", UnitTile::UnitFamily::INF_FAMILY)\
	X("HINF", UnitTile::UnitFamily::HINF_FAMILY)\
	X("CAV", UnitTile::UnitFamily::CAV_FAMILY)\
	X("ART", UnitTile::UnitFamily::ART_FAMILY)\
	X("IRR", UnitTile::UnitFamily::IRR_FAMILY)


class TerrainTile;
class Bridge;
class Hills;
class Meadow;
class Mud;
class Road;
class Slopes;
class TBridge;
class Urban;
class Water;
class Woods;
class UnitLoader;
class Player;

class Infantry;
class Cavalry;
class Artillery;
class Mortar;
class General;
class Sapper;

class UnitTile : public Tile
{
public:
	using unitPtr = std::unique_ptr<UnitTile>;

	enum class Direction{ N, E, S, W };

	enum class Modifier{NONE, TERRAIN, BONUS, ATK, DFND, DISTANCE, FRONT_FLANK, SIDE_FLANK, REAR_FLANK, SQUARE_FORMATION};

	enum class UnitType{INF, CAV, ART, MOR, GEN, ARTGUARD, SAP};

	//Each UnitFamily generally has its own combat rules. LINF, however, does not, and for the moment, HINF's
	//is identical to INF.
	enum class UnitFamily{LINF_FAMILY, INF_FAMILY, HINF_FAMILY, CAV_FAMILY, ART_FAMILY, IRR_FAMILY};

	//Used for storing modifier information

	struct ModifierReport{

		ModifierReport(Modifier _modType, float _modFloat, bool _additional) :
		modType{_modType},
		modFloat{_modFloat},
		additional{_additional}
		{
		}

		Modifier modType;
		float modFloat;
		bool additional;
	};

	struct RangedAttackRange{
		RangedAttackRange(int _lowerThreshold, int _upperThreshold, float _distModifier, bool _modifierIsDamage, int _lowerDieThreshold, int _upperDieThreshold) :
			lowerThreshold{_lowerThreshold},
			upperThreshold{_upperThreshold},
			distModifier{_distModifier},
			modifierIsDamage{_modifierIsDamage},
			lowerDieThreshold{_lowerDieThreshold},
			upperDieThreshold{_upperDieThreshold}
		{
		}

		//The lower and upper thresholds specify the range at which the accompanying distModifier will
		//take effect. For example, if:
		//lowerThreshold = 3;
		//upperThreshold = 5;
		//distModifier = 1.5;
		//Then the unit will get a distance modifier of 1.5 when shooting at a distance between 3 and 5 (inclusive)

		//The lower and upper die roll variables only allow damage to be inflicted if the player's roll
		//is between their values; it defaults to 1 and 6

		//The optional modifierIsDamage variable specifies whether the distModifier is a multiplicational damage modifier
		//or directly damage (1.5d or 1.5 dmg)

		int lowerThreshold;
		int upperThreshold;

		float distModifier;
		bool modifierIsDamage;

		int lowerDieThreshold;
		int upperDieThreshold;
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

	struct FlankModifiers{
		FlankModifiers(UnitTile::UnitType _type) :
			type{_type}
		{
		}

		UnitTile::UnitType type;
		float front{1};
		float side{1};
		float rear{1};
	};

	struct BonusVSMainType{
		BonusVSMainType(UnitType _mainType, float _modifier, bool _modifierIsAdditional, bool _whenAttacking, bool _whenDefending) :
			mainType{_mainType}, modifier{_modifier}, modifierIsAdditional{_modifierIsAdditional}, whenAttacking{_whenAttacking}, whenDefending{_whenDefending}
		{}

		UnitTile::UnitType mainType;
		float modifier;
		bool modifierIsAdditional;
		bool whenAttacking;
		bool whenDefending;
	};

	struct BonusVSFamilyType{
		BonusVSFamilyType(UnitFamily _familyType, float _modifier, bool _modifierIsAdditional, bool _whenAttacking, bool _whenDefending) :
			familyType{_familyType}, modifier{_modifier}, modifierIsAdditional{_modifierIsAdditional}, whenAttacking{_whenAttacking}, whenDefending{_whenDefending}
		{}

		UnitTile::UnitFamily familyType;
		float modifier;
		bool modifierIsAdditional;
		bool whenAttacking;
		bool whenDefending;
	};

	struct BonusVsUnitID{
		BonusVsUnitID(std::string _unitID, float _modifier, bool _modifierIsAdditional, bool _whenAttacking, bool _whenDefending) :
			unitID{_unitID}, modifier{_modifier}, modifierIsAdditional{_modifierIsAdditional}, whenAttacking{_whenAttacking}, whenDefending{_whenDefending}
		{}

		std::string unitID;
		float modifier;
		bool modifierIsAdditional;
		bool whenAttacking;
		bool whenDefending;
	};

	UnitTile(World* _world, Player* _belongsToPlayer, std::string _unitID, UnitType _type, UnitFamily _familyType, Direction _dir);
    //The copy constructor and = operator for this class have been disabled, as they are not only unnecessary, but require careful
    //attention should they ever be used. Two units can not share the same terrain tile, so one will have to be manually assigned.
    //Additionally, this class is abstract. All things considered, these functions are not needed and wouldn't ever be used.
    //Copy constructor
	UnitTile(const UnitTile&) = delete;
	//Operator=
	UnitTile & operator=(const UnitTile&) = delete;
	//Create a virtual destructor, signifying this is an abstract class
	virtual ~UnitTile() = 0;

	//Getters
	//////////////////////////////////////////////////////////////////////////////////////////////////

	inline TerrainTile* getTerrain() const{ return terrain; };
	inline Player* getPlayer() const{ return player; };
	inline UnitType getUnitType() const{ return unitType; };
	inline UnitFamily getUnitFamilyType() const { return unitFamilyType; };
	inline float gethp() const{ return hp; };
	inline int getMov() const{	return mov;	};
	inline UnitTile::Direction getDir() const{ return dir; };
	inline std::string getUnitID() const{return unitID;};
	inline std::string getDisplayName() const{ return displayName; };
	inline std::string getShortDisplayName() const {return shortDisplayName;};

	inline bool getHasMoved() const{ return hasMoved; };
	inline bool getHasPartialRotated() const{ return hasPartialRotated; };
	inline bool getHasFullRotated() const{ return hasFullRotated; };
	inline bool getHasAnyRotated() const{ return (hasPartialRotated || hasFullRotated); };
	inline int getMeleeAttacks() const{return meleeAttacks;};
	inline bool getHasMeleeAttacked() const{ return meleeAttacks > 0; };
	inline int getRangedAttacks() const {return rangedAttacks;};
	inline bool getHasRangedAttacked() const{ return rangedAttacks > 0; };
	inline bool getHasAnyAttacked() const{ return ((meleeAttacks > 0) || (rangedAttacks > 0)); };
	inline bool getHasHealed() const{ return hasHealed; };

	inline bool canMeleeAttack() const {return meleeAttacks < getChargesPerTurn(); };
	inline bool canRangedAttack() const {return rangedAttacks < getShotsPerTurn(); };

	bool getMelee() const;
	bool getSkirmish() const;
	bool getFrightening() const;
	bool getHalfRangedDamage() const;
	bool getCanShootOverUnits() const;
	bool getCanShootTwice() const;

	int getChargesPerTurn() const;
	int getShotsPerTurn() const;

	int getMaxRange() const;
	bool canHeal() const;
	bool hasRangedCapability() const;
	bool canAttackBridge() const;

	int getCost() const;
	int getLimit() const;
	int getMaxHp() const;
	int getMaxMov() const;
	int getConeWidth() const;

	float getFlankModifier(UnitType _mainType, Modifier _flank) const;

	inline sf::Vector2i getTruePosition(){return truePosition;};
	inline sf::Vector2i getPerceivedPosition(){return perceivedPosition;};

	//These 2 functions get the unit's default view distances (those defined in the .txts)...

	int getDefaultUnitViewDistance() const;
	int getDefaultFlagViewDistance() const;

	//...while these 2 get the true view distances, as affected by weather.

	inline int getCurrentUnitViewDistance() const{return currentUnitViewDistance;};
	inline int getCurrentFlagViewDistance() const{return currentFlagViewDistance;};

	//////////////////////////////////////////////////////////////////////////////////////////////////

	//Setters
	//////////////////////////////////////////////////////////////////////////////////////////////////

	inline void sethp(float _hp){ hp = _hp; };
	inline void setMov(float _mov){ mov = _mov; };
	inline void setDir(Direction _dir){ dir = _dir; };
	inline void setHasMoved(bool _hasMoved){ hasMoved = _hasMoved; };
	inline void setHasPartialRotated(bool _hasPartialRotated){ hasPartialRotated = _hasPartialRotated; };
	inline void setHasFullRotated(bool _hasFullRotated){ hasFullRotated = _hasFullRotated; };
	inline void setMeleeAttacks(int _value){ meleeAttacks = _value; };
	inline void setRangedAttacks(int _value){ rangedAttacks = _value; };
	inline void setHasHealed(bool _value){ hasHealed = _value; };

	//Component-related things
	//////////////////////////////////////////////////////////////////////////////////////////////////

	inline void setSquareFormationActive(bool _value){ squareFormationActive = _value; };
	inline void setLimber(bool _value){ limber = _value; };
	inline void setLancerBonusReady(bool _value){ lancerBonusReady = _value; };

	inline bool getSquareFormationActive() const { return squareFormationActive; };
	inline bool getLimber() const { return limber; };
	inline bool getLancerBonusReady() const { return lancerBonusReady; };

	std::string toggleSquareFormationActive();
	std::string toggleLimber();

	bool hasSquareFormationAbility() const;
	bool hasLimberAbility() const;
	bool hasLancerAbility() const;

	inline void setCurrentUnitViewDistance(int _int){currentUnitViewDistance = _int;};
	inline void setCurrentFlagViewDistance(int _int){currentFlagViewDistance = _int;};

	//////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////

	//Other - Virtual
	//////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void takeDamage(UnitTile* attacker, float& _dmg, int distance);
	virtual std::string moveTo(TerrainTile* _terrainTile);
	//Called at the end of every turn;
	virtual void reset();
	inline virtual std::string rotate(Direction){ return{}; };

	void applyBonusModifiers(UnitTile* _unit, bool _attacking);
	void applyFlankModifier(Modifier _flank, UnitTile* _enemy);
	void applyTerrainModifiers(TerrainTile* _terrain, int _distance, bool _attacking);

	void playMoveToAnimation(TerrainTile* _terrain);

	//Needed for double dispatch
	virtual std::string meleeAttack(UnitTile* _unit) = 0;

	inline virtual std::string meleeAttack(Infantry*){ return{}; };
	inline virtual std::string meleeAttack(Cavalry*){ return{}; };
	inline virtual std::string meleeAttack(Artillery*){ return{}; };
	inline virtual std::string meleeAttack(Mortar*){ return{}; };

	virtual std::string rangedAttack(UnitTile* unit, int distance);


    //IMPORTANT NOTE:
    //terrainAttack() should not increment rangedAttacks or meleeAttacks itself; rather,
    //the logic for this is handled in the attack() function.

    virtual std::string terrainAttack(TerrainTile* terrain, int distance);

    //Bridge attacking behavior is shared by all units
    virtual std::string terrainAttack(Bridge* bridge, int distance);
    virtual std::string terrainAttack(TBridge* tBridge, int distance);

    //Whereas the rest, not necessarily
    virtual std::string terrainAttack(Hills*, int /*distance*/){return {"Attacked terrain"};};
    virtual std::string terrainAttack(Slopes*, int /*distance*/){return {"Attacked terrain"};};
    virtual std::string terrainAttack(Meadow*, int /*distance*/){return {"Attacked terrain"};};
    virtual std::string terrainAttack(Mud*, int /*distance*/){return {"Attacked terrain"};};
    virtual std::string terrainAttack(Urban*, int /*distance*/){return {"Attacked terrain"};};
    virtual std::string terrainAttack(Water*, int /*distance*/){return {"Attacked terrain"};};
    virtual std::string terrainAttack(Woods*, int /*distance*/){return {"Attacked terrain"};};

    //Just a shortcut for the below function
    sf::Vector2i distanceFrom(TerrainTile* _destinationTile, bool& _validMovDirection, bool& _validAttackDirection, bool& _rangedObstructionPresent, bool& _meleeObstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange);
	//Further documented in UnitTile.cpp
    sf::Vector2i distanceFrom(TerrainTile* _destinationTile, bool& _validMovDirection, bool& _validAttackDirection, bool& _rangedObstructionPresent, bool& _meleeObstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool _canShootOverUnits, int _coneWidth);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	//////////////////////////////////////////////////////////////////////////////////////////////////


	//Other - Non Virtual
	//////////////////////////////////////////////////////////////////////////////////////////////////
	bool appropriateBridgeConnectionPresent(Bridge* _bridge);

	void setSpritePixelPos(sf::Vector2f _pos);

	void stun();
	std::string heal(UnitTile* _unit);
	std::string beHealed(float num);
	void calculateEffectiveMov();

	//Returns true if dead
	bool removeIfDead();

	UnitTile::Direction opposite(UnitTile::Direction _dir);

	//Spawn is very similar to moveTo, but is only used during the setup phase; it costs no movement
	void spawn(TerrainTile* terrainTile);

	//This function is in charge of initiating combat by determining distance, flank, etc., setting up modifiers,
	//and calling either meleeAttack() or rangedAttack(). It takes in a TerrainTile rather than a UnitTile in case
	//the player wants to attack a tile with no units on it (such as a bridge). If there is a unit on it, we can
	//easily get it with _terrain->getUnit();
	//The bool parameter attackTerrain specifies whether terrain damage should be applied.
	std::string attack(TerrainTile* _terrain);

	bool isHostile(UnitTile* _tile);

    //Manages the position of the sf::Text numbers (hp and movement)
	void updateStats(bool randomisePerceivedPosition = false);

	//Overloaded version that only gets the distance and doesn't take in bools
	int distanceFrom(Tile* _tile);

	std::string dirToString();
	std::string modToString(ModifierReport _mod);

	std::string attackReport(int distance, UnitTile* attacker, UnitTile* defender, int attackerRoll, int defenderRoll, float attackerInflicted, float defenderInflicted, bool retreat = false);

	void multRollByModifiers(float &originalRoll);
	std::string roundFloat(const double x);

	inline void resetTerrain(){terrain = nullptr;};

	//////////////////////////////////////////////////////////////////////////////////////////////////

	//Data member
	std::vector<ModifierReport> modVector{};

	bool drawUnit{true};
	bool drawFlag{true};

protected:
    void setTerrain(TerrainTile* _terrain);

	Player* player;

	Direction dir;

	sf::Vector2i truePosition{};
	sf::Vector2i perceivedPosition{};

    //These are initialised to the defaults defined in the unit's .txt; they are modified by
    //World::calculateViewDistance() when it is called.

	int currentUnitViewDistance{};
	int currentFlagViewDistance{};

	sf::Sprite unitFlag{};
	//Pointer to the terrain tile that the unit is on. This is only to be used for units, to indicate
	//where they are easily and efficiently, since a unit must always be on a terrain tile
	TerrainTile* terrain;

	mutable sf::RectangleShape outline{};

	//The visual representations of the stats
    sf::Text dirText{};
	sf::Text hpText{};
	sf::Text movText{};


	sf::Sprite generalRange1{};
	sf::Sprite generalRange2{};
	sf::Sprite generalDead{};
    //Only one of these will be drawn at a time
	bool drawGeneralRange1{false};
	bool drawGeneralRange2{false};
	bool drawGeneralDead{false};

	std::string unitID;
	std::string displayName{};
	std::string shortDisplayName{};

	UnitType unitType;
	UnitFamily unitFamilyType;

	float hp;
	int mov;

	//Since these will need to be accessed very frequently, we'll "cache" them as data members

	int coneWidth;
	bool canShootOverUnits;

	//Pseudo-components:not all units will make use of these

	/////////////////////////////////////////

	//Square Formation component
	bool squareFormationActive{false};

	//Limber component
	bool limber{true};

	//Lancer bonus component
	bool lancerBonusReady{false};

	/////////////////////////////////////////

	bool hasMoved{false};
	bool hasPartialRotated{false};
	bool hasFullRotated{false};
	int meleeAttacks{0};
	int rangedAttacks{0};
	bool hasHealed{false};
};

