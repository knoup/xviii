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
	BONUS:STRING:Ottoman Inf: ...
}

To specify a bonus, begin the entry with BONUS:. There are 3 ways to specify a bonus: via MAIN, FAMILY, or STRING.

MAIN uses the unit's main type to determine if the bonus will apply, FAMILY uses
the unit's family type, and STRING uses the unit's name. Note that bonuses DO stack.

The meaning of the parameters are as follows:

1st: modifier value
2nd: modifier is multiplicational (0) or additional (1)
3rd: modifier applies in melee
4th: modifier applies in ranged
5th: modifier applies when attacking
6th: modifier applies when defending


-----------------------------------

To specify movement capabilities, begin the entry with MOV. Only STRING (the unit's name) is possible, at the moment.

DEFINE_TERRAIN:woods
{
	BONUS:MAIN:INF:-2,1,0,1,1,0
	MOV:Artillery:0,0
}

IMPORTANT: Do not make seperate DEFINE { } blocks for BONUS and MOV entries