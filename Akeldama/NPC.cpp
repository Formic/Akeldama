#include "NPC.h"
#include "hgeresource.h"

NPC::NPC() : Unit(5, DOWN) {
	resourceManager = new hgeResourceManager("..\\Akeldama\\NPCResource.txt");
	animation = this->resourceManager->GetAnimation("Eric");
	animation->Play();
	SetPos(300, 100);
}