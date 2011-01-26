/**
 * Entity class
 *
 * All objects drawn to the screen inherit from entity. This class handles 
 * positioning, rendering, and collision detection. 
 *
 * Each time an entity is created, it is stored in a static list. This is used for collision detection
 * and rendering. When an entity is deleted, it is removed from the list.
 */
#ifndef ENTITY_H
#define ENTITY_H

#include "hgeanim.h"
#include "hgeresource.h"
#include "Enums.h"
#include <vector>

using namespace std;

class Entity {	
	private:
		static Entity* player; //track the player entity, used for NPC AI purposes
	protected:
		//-= Member variables =-
		float friction; //used in calculating movement
		float xPos;
		float yPos;
		hgeAnimation* animation; //animation (sprites) of entity
		bool collideable; //can this entity be collided into
		bool canSeeThrough; //NPC players can see through this entity
		bool canShootThrough; //Spells/Bullets can pass through (over) this object)
		hgeResourceManager *resourceManager;
		
		//-= Static member variables =-
		static vector<Entity*>* entities; //A static list of every entity on screen

		//-= Methods =-
		bool Collides(Entity* A, Entity* B);
		Entity* Collides();

		//-= Static methods =-
		static void SetPlayer(Entity* p) { player = p; }
		static Entity* GetPlayer() { return player; }
	public:
		Entity(bool collideable);
		Entity(float xPos, float yPos, bool collideable);
		~Entity();

		virtual void TakeDamage(int damage) { } //override if entity can take dmg

		//-= Getters/Setters =-
		hgeAnimation* GetAnimation() { return animation; }
		float GetXPos() { return xPos; }
		float GetYPos() { return yPos; }
		void SetAnimation(hgeAnimation* animation) { this->animation = animation; }
		virtual float GetWidth() { return animation->GetWidth(); }
		virtual float GetHeight() { return animation->GetHeight(); }
		
		static void DeleteEntity(Entity* entity);
};

#endif