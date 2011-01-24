#include "hge.h"
#include "Entity.h"
#include "Unit.h"
#include "Player.h"
#include "NPC.h"
#include "hgeresource.h"
#include "hgesprite.h"
#include "hgefont.h"
#include <vector>
#include <sstream>

HGE *hge;
Player *player;
NPC *eric;
hgeResourceManager *hgeResource;
hgeSprite *backgroundSprite;
hgeFont* font;
int screenWidth = 800;
int screenHeight = 600;

//temp to draw vision radius for visual purposes
void DrawVision(float cx, float cy, float Radius, int Segments, Direction direction)
{
  float EachAngle;
  float a;
  float x1 = 0;
  float x2 = 0;
  float y1 = 0;
  float y2 = 0;

  float degree = 25;
  float angle = degree * M_PI / 180;

  switch (direction) {
	case UP:
		y1 = -Radius * cos(angle);
		x1 = Radius * sin(-angle);
		y2 = -Radius * cos(angle);
		x2 = Radius * sin(angle);
		break;
	case DOWN:
		y1 = Radius * cos(angle);
		x1 = Radius * sin(angle);
		y2 = Radius * cos(angle);
		x2 = Radius * sin(-angle);
		break;
	case LEFT:
		x1 = -Radius * cos(angle);
		y1 = Radius * sin(angle);
		x2 = -Radius * cos(angle);
		y2 = Radius * sin(-angle);
		break;
	case RIGHT:
		x1 = Radius * cos(angle);
		y1 = Radius * sin(-angle);
		x2 = Radius * cos(angle);
		y2 = Radius * sin(angle);
		break;
  }
  hge->Gfx_RenderLine(cx, cy, x1+cx, y1+cy);
  hge->Gfx_RenderLine(cx, cy, x2+cx, y2+cy);
 
  EachAngle = 2.0 * M_PI / (float)Segments;
 
  x2 = Radius;
  y2 = 0.0;
 
  for(a=0; a<= (2.0*M_PI + EachAngle); a+=EachAngle) {
    x1 = x2;
    y1 = y2;
    x2 = Radius * cos(a);
    y2 = Radius * sin(a);
    hge->Gfx_RenderLine(x1+cx, y1+cy, x2+cx, y2+cy);
  }
} 

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

	player->UpdatePos(dt);
	eric->UpdatePos(dt);
	return false;
}

bool RenderGraphics() {
	float dt=hge->Timer_GetDelta();

	hge->Gfx_BeginScene();

	hge->Gfx_Clear(0);
	backgroundSprite->RenderStretch(0, 0, 800, 600);
	player->Render(dt);	
	eric->Render(dt);
	std::stringstream sstr;
	sstr << "Player Life: ";
	sstr << player->GetLife();
	sstr << "\nEric Life: ";
	sstr << eric->GetLife();

	float dy = eric->GetYPos() - player->GetYPos();
	float dx = eric->GetXPos() - player->GetXPos();
	float angle = atan2f(dy, dx) * 180/M_PI;
	sstr << "\nAngle: ";
	sstr << angle;
	
	font->Render(5, 5, HGETEXT_LEFT, sstr.str().c_str());
	DrawVision(eric->GetXPos(), eric->GetYPos(), eric->GetVisionRadius(), 60, eric->GetDirection());

	hge->Gfx_SetTransform(0 , 0, -(player->GetXPos() - 0.5*screenWidth), -(player->GetYPos() - 0.5*screenHeight), 0, 1, 1);

	hge->Gfx_EndScene();

	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, "AkeldamaLog.log");
	hge->System_SetState(HGE_FRAMEFUNC, GameLoop);
	hge->System_SetState(HGE_RENDERFUNC, RenderGraphics);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, screenWidth);
	hge->System_SetState(HGE_SCREENHEIGHT, screenHeight);
	hge->System_SetState(HGE_SHOWSPLASH, false);

	if (hge->System_Initiate()) {
		hgeResource = new hgeResourceManager("..\\Akeldama\\worldResource.txt");
		backgroundSprite = hgeResource->GetSprite("grass1");
		player = new Player();
		eric = new NPC();

		font = new hgeFont("font1.fnt");
		font->SetScale(0.7);

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