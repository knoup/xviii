#pragma once

#include "TerrainTile.h"
#include "FontManager.h"

#include <random>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <math.h>

#include "global.h"

//The last entry, the texture enum, is used only for the selectable units at selection menu. They are NOT used to determine
//actual unit sprites past that point.
#define UNITPROPERTIES\
	X(UnitTile::UnitType::ART, Artillery, "art", TextureManager::Unit::ART)\
	X(UnitTile::UnitType::CAV, Cavalry, "cav", TextureManager::Unit::CAV)\
	X(UnitTile::UnitType::CUIR, Cuirassier, "cuir", TextureManager::Unit::CUIR )\
	X(UnitTile::UnitType::DRAG, Dragoon, "drag", TextureManager::Unit::DRAG)\
	X(UnitTile::UnitType::GEN, General, "gen", TextureManager::Unit::GEN)\
	X(UnitTile::UnitType::INF, Infantry, "inf", TextureManager::Unit::INF)\
	X(UnitTile::UnitType::LCAV, LightCav, "lcav", TextureManager::Unit::LCAV)\
	X(UnitTile::UnitType::MOR, Mortar, "mor", TextureManager::Unit::MOR)\
	X(UnitTile::UnitType::AKINCI, Akinci, "akinci", TextureManager::Unit::DRAG)\
	X(UnitTile::UnitType::DELI, Deli, "deli", TextureManager::Unit::LCAV)\
	X(UnitTile::UnitType::TIM, Timarioti, "tim", TextureManager::Unit::CAV)\
	X(UnitTile::UnitType::KAP, Kapikulu, "kap", TextureManager::Unit::CUIR)\
	X(UnitTile::UnitType::GRE, Grenadier, "gre", TextureManager::Unit::GRE)\
	X(UnitTile::UnitType::JAN, Janissary, "jan", TextureManager::Unit::GRE)\
	X(UnitTile::UnitType::OINF, OttoInf, "o inf", TextureManager::Unit::INF)\
	X(UnitTile::UnitType::LINF, LightInf, "linf", TextureManager::Unit::LINF)\
	X(UnitTile::UnitType::SAP, Sapper, "sap", TextureManager::Unit::SAP)\
	X(UnitTile::UnitType::CRICAV, CrimeanCav, "cr cav", TextureManager::Unit::LCAV)\
	X(UnitTile::UnitType::COSINF, CossackInf, "cos inf", TextureManager::Unit::INF)\
	X(UnitTile::UnitType::KMKH, KhevMkhedrebi, "khev mkh", TextureManager::Unit::CUIR)\
	X(UnitTile::UnitType::PIT, PitsisKatsebi, "pit kat", TextureManager::Unit::CAV)\
	X(UnitTile::UnitType::DON, DonCossack, "don cos", TextureManager::Unit::LCAV)\
	X(UnitTile::UnitType::AMKH, AbrMkhedrebi, "abr mkh", TextureManager::Unit::DRAG)\
	X(UnitTile::UnitType::METTOP, MetTop, "met top", TextureManager::Unit::INF)\
	X(UnitTile::UnitType::KACI, KudzeKaci, "kud kaci", TextureManager::Unit::LINF)\
	X(UnitTile::UnitType::FOOT, FootGuard, "footguard", TextureManager::Unit::HINF)\
	X(UnitTile::UnitType::KKV, KhevKveitebi, "khev kvei", TextureManager::Unit::HINF)\
	X(UnitTile::UnitType::HUS, Hussar, "hussar", TextureManager::Unit::LCAV)\
	X(UnitTile::UnitType::COUR, Courtin, "courtin", TextureManager::Unit::CAV)\
	X(UnitTile::UnitType::SEG, Segbans, "segbans", TextureManager::Unit::DRAG)\
	X(UnitTile::UnitType::BOY, Boyar, "boyar", TextureManager::Unit::CUIR)\
	X(UnitTile::UnitType::DOR, Dorunaby, "dorunaby", TextureManager::Unit::GRE)\
	X(UnitTile::UnitType::VIT, Vitae, "vitae", TextureManager::Unit::LINF)\
	X(UnitTile::UnitType::ARN, Arnauts, "arnauts", TextureManager::Unit::INF)\

class Player;

class Infantry;
class Cavalry;
class Cuirassier;
class Dragoon;
class LightCav;
class Artillery;
class Mortar;
class General;
class Akinci;
class Deli;
class Timarioti;
class Kapikulu;
class Grenadier;
class Janissary;
class OttoInf;
class LightInf;
class Sapper;
class CrimeanCav;
class CossackInf;
class KhevMkhedrebi;
class PitsisKatsebi;
class DonCossack;
class AbrMkhedrebi;
class MetTop;
class KudzeKaci;
class FootGuard;
class KhevKveitebi;
class Hussar;
class Courtin;
class Segbans;
class Boyar;
class Dorunaby;
class Vitae;
class Arnauts;

class UnitTile : public Tile
{
public:
	using unitPtr = std::unique_ptr<UnitTile>;
	enum class Direction{ N, E, S, W };
	enum class Modifier{NONE, ADDITIONAL, ATK, DISTANCE, FRONT_FLANK, SIDE_FLANK, REAR_FLANK};
	enum class UnitType{INF, CAV, CUIR, LCAV, DRAG, ART, MOR, GEN, AKINCI, DELI, TIM, KAP, GRE, JAN, OINF, LINF, SAP, CRICAV, COSINF, KMKH, AMKH, PIT, DON, METTOP, KACI, FOOT, KKV, HUS, COUR, SEG, BOY, DOR, VIT, ARN};
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

	UnitTile(World& _world, std::mt19937&, Player* _belongsToPlayer, TextureManager& tm, FontManager& fm, TextureManager::Unit id, UnitType type, UnitFamily familyType, Direction _dir);
	//Create a virtual destructor, signifying this is an abstract class
	virtual ~UnitTile() = 0;

	//Very, very useful
	std::string roundFloat(const double x);

	UnitType getUnitType() const;
	UnitFamily getUnitFamilyType() const;

	virtual int getCost() const;
	virtual int getLimit() const;

	float gethp() const;
	int getMov() const;

	virtual void takeDamage(float& _dmg, int distance);
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
	virtual std::string heal(float num);

	virtual int getMaxHp() const;
	virtual int getMaxMov() const;
	virtual int getMaxRange() const;
	inline virtual bool getCanMelee() const{ return true; };

	//This function is in charge of initiating combat by determining distance, flank, etc. and calling either
	//meleeAttack() or rangedAttack()
	std::string attack(UnitTile* _unit);
	//This function is unit-specific, and checks for such things as vs. family bonuses/maluses. The bool specifies
	//whether the unit is attacking or defending
	virtual void preMeleeAttack(UnitTile* unit, bool attacking);

	//Needed for double dispatch
	virtual std::string meleeAttack(UnitTile* _unit) = 0;

	virtual std::string meleeAttack(Infantry* inf);
	virtual std::string meleeAttack(Cavalry* cav);
	virtual std::string meleeAttack(Artillery* art);
	virtual std::string meleeAttack(Mortar* mor);

	virtual std::string rangedAttack(UnitTile* unit, int distance);

	//Each class will have an overloaded definition returning its specific flank modifier for either 
	//INF or CAV family units. In the interest of keeping the modifiers static, each class will have 
	//its own implementation of essentially the same function.
	virtual float getFlankModifier(UnitFamily _family, Modifier _flank) const;

	TerrainTile* getTerrain() const;
	Player* getPlayer() const;
	
	bool isHostile(UnitTile* _tile);
	//void highlightEnemy();

    //Manages the position of the sf::Text numbers (hp and movement)
	void updateStats();

	//Further documented in UnitTile.cpp
	virtual int distanceFrom(TerrainTile* _terrain, bool& _validMovDirection, bool& _validAttackDirection, bool& _obstructionPresent, bool& _inMovementRange, bool& _inRangedAttackRange, bool canShootOverUnits = false, int coneWidth = 1);
	//Overloaded version that only gets the distance and doesn't take in bools
	int distanceFrom(Tile* _tile);

	std::string dirToString();
	std::string modToString(ModifierReport _mod);
	std::string typeToString();

	std::string attackReport(int distance, UnitTile* attacker, UnitTile* defender, int attackerRoll, int defenderRoll, float attackerInflicted, float defenderInflicted, bool retreat = false);

	bool getHasMoved() const;
	bool getHasRotated() const;
	bool getHasMeleeAttacked() const;
	bool getHasRangedAttacked() const;
	virtual bool getHasHealed() const;

	void sethp(float _hp);
	void setMov(float _mov);
	void setDir(Direction _dir);
	void setHasMoved(bool _hasMoved);
	void setHasRotated(bool _hasRotated);
	void setHasMeleeAttacked(bool _value);
	void setHasRangedAttacked(bool _value);

	//The following are applicable only for some children; the definition in UnitTile will be
	//blank
	virtual void setHasHealed(bool _hasHealed);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	std::vector<ModifierReport> modVector;

	//Only ever needs to be used internally; making these so I don't have to copy and paste the same
	//code 20 times
	void multRollByModifiers(float &originalRoll);

protected:
	std::string outOfRange();

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

	UnitType unitType;
	UnitFamily unitFamilyType;

	float hp;
	int mov;

	//For (yellow) outlining
	sf::RectangleShape yellowOutline;
	//For (red) outlining
	sf::RectangleShape redOutline;

	//The visual representations of the stats
    sf::Text dirText;
	sf::Text hpText;
	sf::Text movText;

	bool hasMoved{false};
	bool hasRotated{false};
	bool hasMeleeAttacked{false};
	bool hasRangedAttacked{false};
};

