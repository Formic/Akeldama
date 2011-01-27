/**
 * Spell class - isA Entity
 *
 * Spells are non-collideable entities. The have a maximum range and a speed. On impact the spell invokes
 * the takeDamage method on the entity it collides with.
 */
#ifndef SPELL_H
#define SPELL_H

#include "Entity.h"
#include <math.h>

class Spell : public Entity {
	private:
		float dx;
		float dy;
		float speed;
		float distance;
		float range;
		int damageValue;
		Direction direction;

		float GetRotation();
		void Impact(Entity* entity);

	public:
		Spell(float speed, float xPos, float yPos, float range, Direction direction);
		~Spell();
		bool Render(float dt);
		void UpdatePos(float dt);
};

#endif