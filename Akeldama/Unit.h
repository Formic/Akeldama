#ifndef UNIT_H
#define UNIT_H

#include "hgeresource.h"
#include "Entity.h"
#include "Spell.h"

class Unit : public Entity {
	private:
		
		float dx;
		float dy;
		float speed;
		float friction;
		void init();
		float cooldownDt;
		Direction direction;
		std::vector<Spell*> spells;

		static const float globalCooldown;

	protected:
		
		hgeResourceManager *resourceManager;

	public:
		Unit(float speed, Direction direction);
		~Unit();
		void MoveLeft(float dt);
		void MoveRight(float dt);
		void MoveUp(float dt);
		void MoveDown(float dt);
		void UpdatePos();
		void MoveStop();
		void SetPos(float x, float y);
		void Render(float dt);
		void Attack(float dt);
};

#endif