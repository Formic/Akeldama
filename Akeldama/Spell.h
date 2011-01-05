#ifndef SPELL_H
#define SPELL_H

#include "hgeresource.h"
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
		hgeResourceManager *resourceManager;

		float GetRotation();
		void Impact(Entity* entity);

	public:
		Spell(float speed, float xPos, float yPos, float rane, Direction direction);
		~Spell();
		bool Render(float dt);
		void UpdatePos(float dt);
};

#endif