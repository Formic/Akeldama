#include "NPC.h"
#include "hgeresource.h"

const float NPC::maxAllottedDistanceFromPath = 30;
const float NPC::visionAngle = 25;

NPC::NPC() : Character(2, DOWN) {
	resourceManager = new hgeResourceManager("..\\Akeldama\\playerResource.txt");
	animation = resourceManager->GetAnimation("faceDown");
	//animation->Play();
	SetPos(300, 100);

	path = new vector<pair<float, Direction>*>();

	//temp crap
	visionRadius = 200;

	path->push_back(new pair<float, Direction>(0.5, NONE));
	path->push_back(new pair<float, Direction>(100, DOWN));
	path->push_back(new pair<float, Direction>(1, NONE));
	path->push_back(new pair<float, Direction>(200, RIGHT));
	path->push_back(new pair<float, Direction>(1, NONE));
	path->push_back(new pair<float, Direction>(50, UP));
	path->push_back(new pair<float, Direction>(0.5, NONE));
	nextIterator = 1;
	distanceOffPath = 0;
	distanceOnCurrentPathVector = 0;
	currentPathVector = path->begin();
}
NPC::~NPC() {
	
}

float NPC::UpdatePos(float dt) {
	UpdateVision(dt);
	HandleIntelligence(dt);
	return 0;//Unit::UpdatePos(dt);
}
void NPC::UpdateVision(float dt) {
	
}
void NPC::HandleIntelligence(float dt) {
	if (IsPlayerInSight()) {
		if (IsPlayerInRange()) {
			Attack(dt);
		} else MoveToPlayer();
	} else Patrol(dt);
}
bool NPC::IsPlayerInSight() {

	float pXPos = GetPlayer()->GetXPos();
	float pYPos = GetPlayer()->GetYPos();

	//if The player is outside of the radius, this NPC cannot see the player
	if (abs(xPos - pXPos) > visionRadius || abs(yPos - pYPos) > visionRadius)
		return false;

	//check to see if player is within cone of vision
	float dy, dx;
	float angle = 25 * 180/M_PI;
	
	//get player angle
	dy = yPos - pYPos;
	dx = xPos - pXPos;
	float playerAngle = atan2f(dy, dx) * 180/M_PI;

	if (direction == DOWN)
		if (playerAngle > -90 + visionAngle || playerAngle < -90 - visionAngle)
			return false;
	if (direction == UP)
		if (playerAngle > 90 + visionAngle || playerAngle < 90 - visionAngle)
			return false;
	if (direction == RIGHT)
		if ((playerAngle > -180 + visionAngle && playerAngle < 0) || (playerAngle < 180 - visionAngle && playerAngle > 0))
			return false;
	if (direction == LEFT)
		if (playerAngle > 0 + visionAngle || playerAngle < 0 - visionAngle)
			return false;

	//check to see if there is an object blocking vision of player

	return true;
}
bool NPC::IsPlayerInRange() {
	return true;
}
void NPC::MoveToPlayer() {

}
void NPC::Patrol(float dt) {
	if (distanceOnCurrentPathVector >= (*currentPathVector)->first) {
		if ((*currentPathVector == path->back() && nextIterator > 0) 
		 || (*currentPathVector == path->front() && nextIterator < 0)) {
			nextIterator *= -1;
			InvertPath();
		} else {
			currentPathVector += nextIterator;	
		}
		distanceOnCurrentPathVector = 0;
	}
	switch ((*currentPathVector)->second) {
		case UP:
			MoveUp(dt);
			break;
		case DOWN:
			MoveDown(dt);
			break;
		case LEFT:
			MoveLeft(dt);
			break;
		case RIGHT:
			MoveRight(dt);
			break;
		case NONE:
			MoveStop();
			break;
	} 
	if ((*currentPathVector)->second == NONE)
		distanceOnCurrentPathVector += dt;
	else
		distanceOnCurrentPathVector += Character::UpdatePos(dt);
}
void NPC::InvertPath() {
  vector<pair<float, Direction>*>::iterator i;
  for (i=path->begin(); i < path->end(); i++ ) {
	  Direction d = (*i)->second;
	  Direction newDirection;
	  switch (d) {
		case UP:
			newDirection = DOWN;
			break;
		case DOWN:
			newDirection = UP;
			break;
		case LEFT:
			newDirection = RIGHT;
			break;
		case RIGHT:
			newDirection = LEFT;
			break;
		default:
			newDirection = d;
	  }
	  (*i)->second = newDirection;
  }
}
float NPC::GetLeftVisionAngle() {

	return 0;
}
float NPC::GetRightVisionAngle() {

	return 0;
}