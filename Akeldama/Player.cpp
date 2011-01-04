#include "Player.h"
#include "hgeresource.h"

Player::Player() : Unit(5, UP) {
	resourceManager = new hgeResourceManager("..\\Akeldama\\playerResource.txt");
	animation = this->resourceManager->GetAnimation("faceUp");
	animation->Play();
	SetPos(300, 500);
}