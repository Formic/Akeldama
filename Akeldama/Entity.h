#ifndef ENTITY_H
#define ENTITY_H

#include "hgeanim.h"
#include "Enums.h"
#include <vector>

using namespace std;

class Entity {	
	private:
		//track the player entity, used for AI purposes
		static Entity* player;
	protected:
		float friction;
		float xPos;
		float yPos;
		hgeAnimation* animation;
		bool collideable;
		
		//A static list of every entity on screen
		static vector<Entity*>* entities;

		bool Collides(Entity* A, Entity* B);
		Entity* Collides();
		static void SetPlayer(Entity* p) { player = p; }
		static Entity* GetPlayer() { return player; }
	public:
		Entity(bool collideable);
		Entity(float xPos, float yPos, bool collideable);
		~Entity();
		hgeAnimation* GetAnimation() { return animation; }
		float GetXPos() { return xPos; }
		float GetYPos() { return yPos; }
		void SetAnimation(hgeAnimation* animation) { this->animation = animation; }
		virtual float GetWidth() { return animation->GetWidth(); }
		virtual float GetHeight() { return animation->GetHeight(); }
		virtual void TakeDamage(int damage) { }
		
		
		static void DeleteEntity(Entity* entity);
};

#endif