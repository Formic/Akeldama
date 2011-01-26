/**
 * Building class -isA Entity
 * 
 * Simple entity that uses resources from the buildingResource.txt
 */
#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"

class Building : public Entity {
	
	public:
		Building(float xPos, float yPos);
		void Render(float dt);
};

#endif