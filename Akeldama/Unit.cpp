#include "Unit.h"

const float Unit::globalCooldown = 0.5;

Unit::Unit(float speed, Direction direction) : Entity(true) {
	this->speed = speed;
	this->direction = direction;

	init();
}
Unit::~Unit() {

}
void Unit::init() {
	dx = 0;
	dy = 0;
	friction = 0.98f;
	cooldownDt = globalCooldown;
}
void Unit::MoveLeft(float dt) {
	animation = resourceManager->GetAnimation("faceSideways");
	animation->SetFlip(true, false);
	direction = LEFT;
	dx-=speed*dt;
	animation->Resume();
}
void Unit::MoveRight(float dt) {
	animation = resourceManager->GetAnimation("faceSideways");
	animation->SetFlip(false, false);
	direction = RIGHT;
	dx+=speed*dt;
	animation->Resume();
}
void Unit::MoveUp(float dt) {
	animation = resourceManager->GetAnimation("faceUp");
	direction = UP;
	dy-=speed*dt;
	animation->Resume();
}
void Unit::MoveDown(float dt) {
	animation = resourceManager->GetAnimation("faceDown");
	direction = DOWN;
	dy+=speed*dt;
	animation->Resume();
}
void Unit::MoveStop() {
	animation->Stop();
}
void Unit::UpdatePos() {
	float oldXPos = xPos;
	float oldYPos = yPos;

	dx*=friction;
	dy*=friction;
	xPos+=dx;
	yPos+=dy;
	
	if (this->collides()) {
		xPos = oldXPos;
		yPos = oldYPos;
	}
}
void Unit::SetPos(float xPos, float yPos) {
	this->xPos = xPos;
	this->yPos = yPos;
}
void Unit::Render(float dt) {
	animation->Render(xPos, yPos);
	animation->Update(dt);

	for (int i=0; i < (int)spells.size(); i++) {
		if (spells[i]->Render(dt)) {
			Spell* newReference = spells[i];
			for (std::vector<Spell*>::iterator j = spells.begin(); j != spells.end(); j++) {
				if (*j == spells[i]) {
					spells.erase(j);
					break;
				}
			}
			delete newReference;
		}
	}
			
	if (cooldownDt < globalCooldown)
		cooldownDt += dt;

}
void Unit::Attack(float dt) {
	if (cooldownDt >= globalCooldown) {
		cooldownDt = 0;
		float x = xPos;
		float y = yPos;

		if (direction == UP)
			y -= animation->GetHeight()/2;
		else if (direction == DOWN)
			y += animation->GetHeight()/2;
		else if (direction == LEFT)
			x -= animation->GetWidth()/2;
		else if (direction == RIGHT)
			x += animation->GetWidth()/2;

		Spell *s = new Spell(750.0, x, y, 700, direction);
		spells.push_back(s);
	}
}
