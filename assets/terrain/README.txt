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
	DEFINE:MAIN:INF:-2,1,0,1,1,0
	DEFINE:FAMILY:CAV:0.5,0,0,1,0,1
	DEFINE:STRING:Ottoman Inf: ...
}

There are 3 ways to specify a bonus: via MAIN, FAMILY, or STRING.

MAIN uses the unit's main type to determine if the bonus will apply, FAMILY uses
the unit's family type, and STRING uses the unit's name.

The meaning of the parameters are as follows:

1st: modifier value
2nd: modifier is multiplicational (0) or additional (1)
3rd: modifier applies in melee
4th: modifier applies in ranged
5th: modifier applies when attacking
6th: modifier applies when defending