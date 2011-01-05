#include "Spell.h"

Spell::Spell(float speed, float xPos, float yPos, float range, Direction direction) : Entity(false) {
	resourceManager = new hgeResourceManager("..\\Akeldama\\spellResource.txt");
	animation = resourceManager->GetAnimation("fireball1");
	animation->Play();
	animation->SetHotSpot(0, (48/2) + 0.5);

	damageValue = 5;

	if (direction == UP)
		yPos -= animation->GetHeight()/2;
	else if (direction == DOWN)
		yPos += animation->GetHeight()/2;
	else if (direction == LEFT)
		xPos -= animation->GetWidth()/2;
	else if (direction == RIGHT)
		xPos += animation->GetWidth()/2;

	this->speed = speed;
	this->xPos = xPos;
	this->yPos = yPos;
	this->range = range;
	this->direction = direction;

	dx = 0;
	dy = 0;
	distance = 0;
}
Spell::~Spell() {

}
bool Spell::Render(float dt) {
	UpdatePos(dt);
	animation->RenderEx(xPos, yPos, GetRotation());
	animation->Update(dt);
	if (distance > range)
		return true;
	return false;
}
void Spell::UpdatePos(float dt) {
	if (direction == UP) {
		dy=-speed*dt;
	} else if (direction == DOWN) {
		dy=speed*dt;
	} else if (direction == LEFT) {
		dx=-speed*dt;
	} else if (direction == RIGHT) {
		dx=speed*dt;
	}

	xPos+=dx;
	yPos+=dy;

	distance += abs(dx) + abs(dy);

	Entity* entity = collides();
	if (entity) {
		xPos -=dx;
		yPos-=dy;
		Impact(entity);
	}
	
}
float Spell::GetRotation() {
	
	if (direction == RIGHT) 
		return 0;
	if (direction == DOWN)
		return (90*M_PI)/180;
	if (direction == LEFT)
		return M_PI;
	return (270*M_PI)/180;
}
void Spell::Impact(Entity *entity) {
	/*Unit* unit = static_cast<Unit*> (entity);
	if (unit != NULL)
		unit->TakeDamage(damageValue, damageType);*/
	entity->TakeDamage(damageValue);
}
