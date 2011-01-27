/**
 * Character class - isA Entity
 *
 * Characters are entities that can move in all 4 directions, with seperate animations for each direction.
 * A character can attack and take damage.
 */
#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"
#include "Spell.h"

class Character : public Entity {
	private:
		float dx;
		float dy;
		void init();
		float cooldownDt;
		vector<Spell*> spells;

		static const float globalCooldown;

	protected:
		int life;
		float speed;
		Direction direction;

	public:
		Character(float speed, Direction direction);
		~Character();
		void MoveLeft(float dt);
		void MoveRight(float dt);
		void MoveUp(float dt);
		void MoveDown(float dt);
		void MoveStop();
		void SetPos(float x, float y);
		void Render(float dt);
		void Attack(float dt);
		void TakeDamage(int damage);

		virtual float UpdatePos(float dt);

		int GetLife() { return life; }
		Direction GetDirection() { return direction; }
};

#endif