Uses <a href="http://sfml-dev.org/">SFML 2.1</a> and several <a href="http://www.boost.org/">Boost</a> modules.Inspired by, and continutally developed with, the ideas and input of a friend.

Items of Note
-----------------------

 *This is my first real project, hence the generally amateurish code. 

 *This file may or may not be 100% updated

 *There is code for random menu wallpapers. My personal collection is nearly 30MB in size, and thus I won't upload it on Github for the time being. However, you are free to place your own images in the dir assets/gfx/backgrounds.

General
-------
	There are four types of actions:


	1) MOVEMENT

	2) PARTIAL ROTATION
			*Left/Right (90 degrees)

	3) FULL ROTATION
			*180 degrees

	4) ATTACK
			*Includes Firing/Charging/Healing


*INF can either MOVE, PARTIALLY ROTATE, or FULLY ROTATE in addition to attacking.

*CAV can either FULLY ROTATE, or PARTIALLY ROTATE in addition to moving

*However, unless otherwise stated, units may not ROTATE or MOVE at all AFTER attacking.

*INF by default features a square formation mechanic (although this can be removed/defined)
for other units as well). SF status can be toggled with F; while a unit is 
in SF, any melee enemy attack will use the modifier of that enemy's SQUAREFORMATIONMODIFIER.


*ART by default features a limber mechanic (although this can be removed/defined)
for other units as well). Limber status can be toggled with L; while a unit is 
limbered, it can move, but cannot attack, and vice cersa when it is unlimbered.
Note that a unit going from limbered to unlimbered needs to wait one turn before
it can attack.


*d stands for [6-sided] die; the roll result is multiplied by the modifier, such that
 a roll of 4 with modifiers of 0.5d and 1d will yield 2 and 4 DMG respectively


*Incremental modifiers always come after multiplicational ones; a Cuirassier 4 rolling
 against a Dragoon will get a resultant roll of 9 [(2x4) + 1], not 10 [2x(4+1)].


*When a player's GENERAL dies, inflict 2 DMG to all friendly units. Generals may
heal a friendly unit for 2 HP once per turn, by default.


Unit Types 
-------------------

There are 7 types of MAIN classes:

The "big three":


	INF (Infantry)
	CAV (Cavalry)
	ART (Artillery)


And then the rest:

	GEN (General) - behaves the same as Cavalry, except has a hardcoded limit of 1.
	In addition, if allied units are between 34 and 21 tiles away (radius) from
	the general, they get only 75% of their maximum movement at the start of
	the turn. If they are further than 34, they get only 65%.

	ARTGUARD (Artillery Guard) - behaves the same as Infantry, except for that any
	adjacent artillery tile will be immune to attacks from the enemy until the
	ARTGUARD is either killed or moved away.

	SAPPER (Sapper/engineer) - behaves the same as Infantry, but has a unique ability;
	is able to construct bridges by "attacking" water tiles.

Please note that details (HP, MOV, LIMIT, attacking capabilities, etc.) are defined
in assets/units. All units must, however, be based on one of these 7 classes.

See the readme in assets/units for more details and further explanation of game
mechanics.


Ranged Combat Rules
-------------------


The player rolls a die and the result is multiplied by the unit's dist./dir. modifier.

EXAMPLE:

Player 1 has INF shooting at Player 2's CAV from 2 tiles away.
Since INF has a modifier of 2d while shooting from this distance, his roll is multiplied by 2.
Player 1 rolls 4 and inflicts 8 DMG on Player  2's CAV.


A unit's cone width determines the horizontal range of their capabilities.


Melee Combat Rules
-------------------


	INF vs INF

		*Roll dice

		*If difference between player 1 and 2 is less than 3, player with highest roll inflicts 1 DMG

		*If both get the same roll, both take 1 DMG

		*Otherwise, inflict 2 DMG


	CAV vs CAV:

		*Roll dice

		*Same rules as INF vs INF.

	INF vs CAV

		*Roll dice

		*Player with higher roll wins

		*If CAV wins, inflict 4 DMG

		*If equal rolls, CAV takes 1 DMG and INF takes 0.5 DMG

		*If INF wins, inflict 2 DMG (and receive 1)

	INF/CAV vs ART

		*Only INF/CAV rolls

		*If INF/CAV rolls 3 or more, inflict 2 DMG. If 2 or less, both INF/CAV and ART take 3 DMG.


	INF/CAV vs MOR

		*Only INF/CAV rolls

		*If INF/CAV rolls 3 or more, inflict 2 DMG. If 2 or less, INF/CAV take 0.5 DMG, MOR takes 2 DMG.



In-Game
-------

During the setup phase, each player deploys their units on the game board.
Players are limited to the far reaches of the map during this phase. In
order to deploy a unit, you may either click on its sprite or use the
keyboard shortcuts.

The indicators under the counters represent the unit's current direction,
health, and movement points, respectively. A unit with W 5 4 under it would
therefore represent a state in which it is facing westward, has 5 HP remaining,
and 4 movement points.

During the playing phase, players successively command their units by clicking
on the desired unit and giving it movement/attack/rotation orders while
selected (see below). The currently selected unit is outlined in yellow, while
units that have already attacked this turn are outlined in red.

Line of Sight & Weather
--------------

In addition to movement points and max attacking range, units are limited by their
line of sight. 

Each unit has a primary and secondary visual range. Enemy units outside the primary,
but within the secondary, are seen only as flags and their location may be inaccurate.
Units outside of the secondary range are completely invisible. 

A unit can neither move to a tile, nor attack an enemy, that has an
enemy unit in the way. Friendly units can move past each other; however, whether
they can fire "above" units in the way is determined in their .txt.

XVIII also features a dynamic weather system. Every once in a while, the weather
changes, and with it, the visual range of all units is, too, affected. The values
are as follows, with P representing primary and S secondary visual range:

	Light fog: -2P, -2S

	Heavy fog: -4P, -4S

	Light rain: -1P, -1S

	Heavy rain: -2P, -2S


Additionally, both primary and secondary visual ranges are halved during the 
night hours (1900 - 5000).

Every in-game turn represents the passage of 15 minutes.

Keyboard shortcuts & mouse commands
------------------------------------

---Menu Phase---

	W/Up/S/Down keys & Return

Two premade save files are provided for those who just want to dive in without bothering to set up.

---Nation Selection Phase---

	Left/A/Right/D keys & Return

---Setup & Playing Phases---

	H - Hide UI
	R - reset zoom level
	WASD - pan view
	dash (-) - zoom out
	equal (=) - zoom in
	Mouse wheel - zoom out/in

---Setup Phase---

	LMB - place unit on tile
	RMB - deselect currently selected sprite, or delete unit at tile

---Playing Phase---

	LMB - select a unit and issue movement/attack orders
	RMB - deselect currently selected unit/dismiss current message
	L - Toggle limber

	Up/down/left/right arrow keys - rotate a unit North, South, East, and West respectively

	Z - save
