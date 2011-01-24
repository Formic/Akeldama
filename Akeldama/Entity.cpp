#include "Entity.h"

vector<Entity*>* Entity::entities = new vector<Entity*>();
Entity* Entity::player;

Entity::Entity(bool collideable) {
	this->collideable = collideable;

	friction = 0.98f;
	entities->push_back(this);
}
Entity::Entity(float xPos, float yPos, bool collideable) {
	this->xPos = xPos;
	this->yPos = yPos;
	this->collideable = collideable;

	friction = 0.98f;
	entities->push_back(this);
}
Entity::~Entity() {
	DeleteEntity(this);
}


Entity* Entity::Collides() {
	for (vector<Entity*>::iterator i = entities->begin(); i != entities->end(); i++) {
		Entity* entity = *i;

		if (Collides(this, entity))
			return entity;
	}
	return NULL;
}
bool Entity::Collides(Entity* A, Entity* B) {
	//can't colide with itself
	if (A == B)
		return false;

	if (!B->collideable)
		return false;

	float AHeight = A->GetHeight();
	float AWidth = A->GetWidth();
	float BHeight = B->GetHeight();
	float BWidth = B->GetWidth();

	float ATop = A->yPos + (AHeight / 2);
	float ABottom = A->yPos - (AHeight / 2);
	float ALeft = A->xPos - (AWidth / 2);
	float ARight = A->xPos + (AWidth / 2);

	float BTop = B->yPos + (BHeight / 2);
	float BBottom = B->yPos - (BHeight / 2);
	float BLeft = B->xPos - (BWidth / 2);
	float BRight = B->xPos + (BWidth / 2);

	if (ABottom > BTop) return false;
	if (ATop < BBottom) return false;

	if (ALeft > BRight) return false;
	if (ARight < BLeft) return false;

	return true;
}
void Entity::DeleteEntity(Entity* entity) {
	
	for (vector<Entity*>::iterator i = entities->begin(); i != entities->end(); i++) {
		if (*i == entity) {
			entities->erase(i);
			break;
		}
	}
}
