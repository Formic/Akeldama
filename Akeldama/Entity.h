#ifndef ENTITY_H
#define ENTITY_H

#include "hgeanim.h"
#include "Enums.h"
#include <vector>

class Entity {	
	protected:
		float xPos;
		float yPos;
		hgeAnimation* animation;
		Entity* collides();
		bool collideable;
		
		//A static list of every entity on screen
		static std::vector<Entity*>* entities;
	public:
		Entity(bool collideable);
		Entity(float xPos, float yPos, bool collideable);
		~Entity();
		hgeAnimation *GetAnimation() { return animation; }
		
		static void DeleteEntity(Entity* entity);
};

#endif