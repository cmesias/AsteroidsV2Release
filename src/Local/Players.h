/*
 * Players.h
 *
 *  Created on: Dec 18, 2016
 *      Author: Carl
 */

#ifndef LOCAL_PLAYERS_H_
#define LOCAL_PLAYERS_H_

#include "Asteroids.h"
#include "Enemies.h"
#include "Particless.h"
#include "Explosions.h"
#include "LWIndows.h"
#include "Input.h"

#include "LTextures.h"

//Player
class Player {
public:
	int timer = 0;
	int w = 16, h = 16;
	//float x = map.x+map.w/2-32/2,
	//	  y = map.y+map.h/2-32/2;
	float x = 0,
		  y = 0;
	int panTimer 		= 0;
	int shoottimer 		= 0;
	float angle 		= 0.0,
		   radians 		= 0.0,
		   radianCos 	= 0.0,
		   radianSin 	= 0.0;
	float thrustSpeedX2 = 0.0,
		  thrustSpeedY2 = 0.0,
		  thrustSpeed 	= 0.0;
	bool camlocked 		= true;
	bool moveleft 		= false,
		 moveright 		= false,
		 moveup 		= false,
		 movedown		= false,
		 rotateLeft 	= false,
		 rotateRight 	= false;
	float AttackSpeed 	= 9.5;
	float delayT 		= 0;
	bool delay 			= false;
	bool initialshot 	= false;
	string side 		= "r";
	string powerup 		= "LAZER";
	string mode 		= "editor";
	string travelMode 	= "travel";
	string name			= "AAA";
	bool thrust 		= false;
	int thrustT 		= 0;
	bool shift 			= false;
	int timer2 			= 0;
	double time 		= 0;
	int shieldT			= 300;
	bool shield			= true;
	bool deathScreen	= false;
	bool alive			= false;
	Uint8 alpha			= 255;
	unsigned int score	= 0;
	unsigned int highscore = 0;
	int increment		= 2;
	int wave			= 0;
	int health			= 200;
	double accuracy		= 0.0;
	float totalShot		= 0;		// Total shot
	float hits			= 0;		// Total hits
	//SDL_Rect miniMap;
	int bg; 						// Background


	double tempc, temps;
	SDL_Rect continueButton[2];

	// High-Score display
	string highList[10];
	int indx = 0;
	float travel = 0.0;
	int dir = 1;


	// 0: thrust, 1: rotate left, 2: rotate right
	int moves[3];

	LTexture gPlayer;
	LTexture gShield;
	LTexture gTextt;

	void loadResources(SDL_Renderer* gRenderer);
	void freeResources();
	void init(float x, float y);
	void algo();
	void updateAlgo();
	void updateScore();
	void reset(float x, float y);
	bool checkCollision(int x, int y, int w, int h, int x2, int y2, int w2, int h2);
	void update(int screenWidth, int screenHeight, Asteroid asteroid[], Asteroid &a_dummy,
				Enemy enemy[], Enemy &e_dummy,
				Particle particle[], Particle &p_dummy,
				Explosion explosion[], Explosion &ex_dummy,
				unsigned int &HS, int &HW, int mx, int my, bool &leftclick,
				float spawnX, float spawnY,
				int mapX, int mapY, int mapW, int mapH,
				LWindow gWindow, Input &i_dummy, SDL_Renderer* gRenderer,
				LTexture gText, TTF_Font *gFont, SDL_Color color,
				Mix_Chunk *sLazer, Mix_Chunk *sAtariBoom);
	void render(int screenWidth, int screenHeight, int camx, int camy,
				SDL_Renderer* gRenderer,
				TTF_Font *gFont, TTF_Font *gFont2,
				SDL_Color color);
};

#endif /* LOCAL_PLAYERS_H_ */
