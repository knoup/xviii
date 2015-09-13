Valid terrain inputs:

meadow
hills
mud
road
slopes
urban
woods

If you do not define anything here, there will simply be no terrain effects.

Usage:

DEFINE_TERRAIN:woods
{
	BONUS:MAIN:INF:-2,1,0,1,1,0
	BONUS:FAMILY:CAV:0.5,0,0,1,0,1
	BONUS:UNITID:Ottoman Inf: ...
}

To specify a bonus, begin the entry with BONUS:. There are 3 ways to specify a bonus: via MAIN, FAMILY, or UNITID.

MAIN uses the unit's main type to determine if the bonus will apply, FAMILY uses
the unit's family type, and UNITID uses the unit's ID (name of its .txt file). Note that bonuses stack.

The meaning of the parameters are as follows:

1st: modifier value
2nd: modifier is multiplicational (0) or additional (1)
3rd: modifier applies in melee
4th: modifier applies in ranged
5th: modifier applies when attacking
6th: modifier applies when defending


-----------------------------------

To specify movement capabilities, begin the entry with BONUS:MOV. Only STRING (the unit's name) is possible, at the moment. 

The first number should be true (1) if a unit can CROSS this tile, and 0 if not.

The second number should be true (1) if a unit can STOP in this tile, and 0
if not.

Note that by default, units can cross and stop in all tiles except water. Note that units need to be able to both stop in and cross a tile in order to be able to stop in it.

DEFINE_TERRAIN:woods
{
	BONUS:MAIN:INF:-2,1,0,1,1,0
	BONUS:MOV:Artillery:0,0
}


In the case of water, only crossing it is possible, and this is defined via the WATERCROSSER flag in the unit's definition file. Entries for water in this file won't have any effect.