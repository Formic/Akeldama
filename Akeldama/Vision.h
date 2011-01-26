#ifndef VISION_H
#define VISION_H

#include "Entity.h"

class Vision : public Entity {
	private:
		float width;
		float height;
	public:
		Vision(float xPos, float yPos, float width, float height) : Entity(xPos, yPos, false) {
			this->width = width;
			this->height = height;
		}
		float GetWidth() { return width; }
		float GetHeight() { return height; }
		float GetXPos() { return xPos; }
		float GetYPos() { return yPos; }
		
};

#endif