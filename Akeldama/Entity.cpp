#include "Entity.h"

std::vector<Entity*>* Entity::entities = new std::vector<Entity*>();

Entity::Entity(bool collideable) {
	this->collideable = collideable;

	entities->push_back(this);
}
Entity::Entity(float xPos, float yPos, bool collideable) {
	this->xPos = xPos;
	this->yPos = yPos;
	this->collideable = collideable;

	entities->push_back(this);
}
Entity::~Entity() {
	DeleteEntity(this);
}


Entity* Entity::collides() {
	for (std::vector<Entity*>::iterator i = entities->begin(); i != entities->end(); i++) {
		Entity* entity = *i;

		//can't colide with itself
		if (this == entity)
			continue;

		if (!entity->collideable)
			continue;

		float thisHeight = this->animation->GetHeight();
		float thisWidth = this->animation->GetWidth();
		float otherHeight = entity->animation->GetHeight();
		float otherWidth = entity->animation->GetWidth();

		float thisTop = this->yPos + (thisHeight / 2);
		float thisBottom = this->yPos - (thisHeight / 2);
		float thisLeft = this->xPos - (thisWidth / 2);
		float thisRight = this->xPos + (thisWidth / 2);

		float otherTop = entity->yPos + (otherHeight / 2);
		float otherBottom = entity->yPos - (otherHeight / 2);
		float otherLeft = entity->xPos - (otherWidth / 2);
		float otherRight = entity->xPos + (otherWidth / 2);

		if (thisBottom > otherTop) continue;
		if (thisTop < otherBottom) continue;

		if (thisLeft > otherRight) continue;
		if (thisRight < otherLeft) continue;

		return entity;
	}
	return NULL;
}
void Entity::DeleteEntity(Entity* entity) {
	
	for (std::vector<Entity*>::iterator i = entities->begin(); i != entities->end(); i++) {
		if (*i == entity) {
			entities->erase(i);
			break;
		}
	}
}
