#include "hge.h"
#include "Entity.h"
#include "Unit.h"
#include "Player.h"
#include "NPC.h"
#include "hgeresource.h"
#include "hgesprite.h"
#include <vector>

HGE *hge;
Player *player;
NPC *eric;
hgeResourceManager *hgeResource;
hgeSprite *backgroundSprite;

bool InitQuit() {
	return true;
}

bool GameLoop() {
	float dt = hge->Timer_GetDelta();

	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return InitQuit();
	
	if (hge->Input_GetKeyState(HGEK_LEFT))			player->MoveLeft(dt);
	else if (hge->Input_GetKeyState(HGEK_RIGHT))	player->MoveRight(dt);
	else if (hge->Input_GetKeyState(HGEK_UP))		player->MoveUp(dt);
	else if (hge->Input_GetKeyState(HGEK_DOWN))		player->MoveDown(dt);
	else											player->MoveStop();

	if (hge->Input_GetKeyState(HGEK_SPACE))			player->Attack(dt);

	player->UpdatePos();
	eric->UpdatePos();
	return false;
}

bool RenderGraphics() {
	float dt=hge->Timer_GetDelta();

	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	backgroundSprite->RenderStretch(0, 0, 800, 600);
	player->Render(dt);	
	eric->Render(dt);
	hge->Gfx_EndScene();

	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, "AkeldamaLog.log");
	hge->System_SetState(HGE_FRAMEFUNC, GameLoop);
	hge->System_SetState(HGE_RENDERFUNC, RenderGraphics);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SHOWSPLASH, false);

	if (hge->System_Initiate()) {
		hgeResource = new hgeResourceManager("..\\Akeldama\\worldResource.txt");
		backgroundSprite = hgeResource->GetSprite("grass1");
		player = new Player();
		eric = new NPC();

		hge->System_Start();

		//hge->Texture_Free(player->GetTexture());
		//player->FreeTextures(hge);
	} else {
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}

	hge->System_Shutdown();
	hge->Release();
	return 0;
}