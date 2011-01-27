#include "Player.h"
#include "hgeresource.h"

Player::Player() : Character(5, UP) {
	resourceManager = new hgeResourceManager("..\\Akeldama\\playerResource.txt");
	animation = this->resourceManager->GetAnimation("faceUp");
	animation->Play();
	SetPlayer(this);
	SetPos(0, 0);
}