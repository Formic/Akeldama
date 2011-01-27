/**
 * Player class - isA Character
 *
 * Players are unit's that are controlled by a user. The player class will track the players inventory,
 * equipment, spells and abilities, gold, etc.
 */
#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character {
	private:
		
	public:
		Player();
};

#endif