#include "Building.h"

Building::Building(float xPos, float yPos) : Entity(xPos, yPos, true) {
	resourceManager = new hgeResourceManager("..\\Akeldama\\buildingResource.txt");
	animation = resourceManager->GetAnimation("house");
}

void Building::Render(float dt) {
	animation->Render(xPos, yPos);
}