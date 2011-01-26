#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"
#include "Spell.h"

class Unit : public Entity {
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
		Unit(float speed, Direction direction);
		~Unit();
		void MoveLeft(float dt);
		void MoveRight(float dt);
		void MoveUp(float dt);
		void MoveDown(float dt);
		virtual float UpdatePos(float dt);
		void MoveStop();
		void SetPos(float x, float y);
		void Render(float dt);
		void Attack(float dt);
		void TakeDamage(int damage);
		int GetLife() { return life; }
		Direction GetDirection() { return direction; }
};

#endif