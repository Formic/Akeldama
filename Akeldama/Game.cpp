/**
 * Akeldama V 0.1
 * 
 * Author: Blake Sleight
 * Init Date: November 10 2010 
 * 
 * Credits: HAAF'S GAME ENGINE (HGE)- the game engine being used
 *			Current sprites are not mine, due to terrible artistic skills. Original sprites
 *		        will be used when development is further
 *
 *
 * Summary: 2D RPG that will have a zelda-esk look and feel with a Diablo-esk style of gameplay.
 *
 * Currently working on: AI is incomplete. Currently has vision detection and a patrol system in place. Adding
 *						 ability to move to position to attack player as well as not being able to see through
 *                       objects that are solid, and see over (or through) objects that are set to such. 
 *						 Rendering is not currently handled by the entity class, but will be.
 */

/**
 * Game.cpp
 *
 * Sets up HGE and runs the main game loop.
 *
 */
#include "hge.h"
#include "Entity.h"
#include "Character.h"
#include "Player.h"
#include "NPC.h"
#include "Building.h"
#include "hgeresource.h"
#include "hgesprite.h"
#include "hgefont.h"
#include <vector>
#include <sstream>

//-=-=-=-=-=-=-=-=-=Globals=-=-=-=-=-=-=-=-=-=-=-=-
HGE *hge;
Player *player;
NPC *eric;
Building *building;
hgeResourceManager *hgeResource;
hgeSprite *backgroundSprite;
hgeFont* font;
int screenWidth = 800;
int screenHeight = 600;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

/**
 * Development function used to draw the NPC's vision radius and NPC's cone of vision.
 *
 */
void DrawVision(float cx, float cy, float Radius, int Segments, Direction direction) {  

  //left vision coordinate holder
  float x1 = 0;
  float y1 = 0;
  //right vision coordinate holder
  float x2 = 0;
  float y2 = 0;

  float EachAngle;
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

  //draw cone of vision lines
  hge->Gfx_RenderLine(cx, cy, x1+cx, y1+cy);
  hge->Gfx_RenderLine(cx, cy, x2+cx, y2+cy);
 
  //draw the vision radius
  EachAngle = 2.0 * M_PI / (float)Segments;
  x2 = Radius;
  y2 = 0.0;
 
  for(float a=0; a<= (2.0*M_PI + EachAngle); a+=EachAngle) {
    x1 = x2;
    y1 = y2;
    x2 = Radius * cos(a);
    y2 = Radius * sin(a);
    hge->Gfx_RenderLine(x1+cx, y1+cy, x2+cx, y2+cy);
  }
} 

/**
 * Function fired when user attempts to quit.
 *
 * TODO: Confirm and save game data
 * 
 * Return true to quit the game.
 */
bool InitQuit() {
	return true;
}

/**
 * Handles the Input recieved and the updating of entity positions
 *
 * Returns false to continue game loop. Returns true to end game loop.
 */
bool GameLoop() {
	//Change in time used to calculate movement rendering
	float dt = hge->Timer_GetDelta();

	//Handle user attempting to quit
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) 
		if(InitQuit())
			return true;
	
	//Input from user. Only one direction is allowed at a time
	if (hge->Input_GetKeyState(HGEK_LEFT))			player->MoveLeft(dt);
	else if (hge->Input_GetKeyState(HGEK_RIGHT))	player->MoveRight(dt);
	else if (hge->Input_GetKeyState(HGEK_UP))		player->MoveUp(dt);
	else if (hge->Input_GetKeyState(HGEK_DOWN))		player->MoveDown(dt);
	else											player->MoveStop();

	//Other input from user aside from movement
	if (hge->Input_GetKeyState(HGEK_SPACE))			player->Attack(dt);

	//Update entities on map
	//TODO: dynamically update all entities on the screen, not just these listed
	player->UpdatePos(dt);
	eric->UpdatePos(dt);

	//Continue game loop
	return false;
}

/**
 * Renders all of the entities on screen
 *
 * TODO: Replace a mass background image with tiles from the level script
 * TODO: Loop through all entities and have them render themselves
 */
bool RenderGraphics() {
	float dt=hge->Timer_GetDelta();

	hge->Gfx_BeginScene();

	hge->Gfx_Clear(0);
	backgroundSprite->RenderStretch(0, 0, 800, 600);
	backgroundSprite->RenderStretch(-800, -600, 0, 0);
	backgroundSprite->RenderStretch(-800, 0, 0, 600);
	backgroundSprite->RenderStretch(0, -600, 800, 0);
	player->Render(dt);	
	eric->Render(dt);
	building->Render(dt);

	//development text and npc vision
	//TODO: create development consol to replace need
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
	font->Render((player->GetXPos() - 0.5*screenWidth) + 5, (player->GetYPos() - 0.5*screenHeight) + 5, HGETEXT_LEFT, sstr.str().c_str());
	DrawVision(eric->GetXPos(), eric->GetYPos(), eric->GetVisionRadius(), 60, eric->GetDirection());

	//Center camera on player
	hge->Gfx_SetTransform(0 , 0, -(player->GetXPos() - 0.5*screenWidth), -(player->GetYPos() - 0.5*screenHeight), 0, 1, 1);

	hge->Gfx_EndScene();

	//always return false
	return false;
}

/**
 * Main function. Sets up hge system, and loads in necessary files
 *
 */
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
		building = new Building(350, 150);

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