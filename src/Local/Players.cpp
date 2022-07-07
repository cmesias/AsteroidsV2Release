/*
 * Players.cpp
 *
 *  Created on: Dec 18, 2016
 *      Author: Carl
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mouse.h>

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

#include "Asteroids.h"
#include "Enemies.h"
#include "Enemies.h"
#include "Particless.h"
#include "Explosions.h"
#include "Input.h"

#include "Players.h"

// Generate a random double number
double fRandP(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

// Check collision between 2 objects
bool Player::checkCollision(int x, int y, int w, int h, int x2, int y2, int w2, int h2){
	bool collide;
	if (x+w > x2 && x < x2 + w2 && y+h > y2 && y < y2 + h2){
		collide = true;
	}else{
		collide = false;
	}
	return collide;
}

// Load asteroid resources
void Player::loadResources(SDL_Renderer* gRenderer){
	gPlayer.loadFromFile("img/player.png", gRenderer);
	gShield.loadFromFile("img/shield.png", gRenderer);
}

// Free asteroid resources
void Player::freeResources(){
	gPlayer.free();
	gShield.free();
	gTextt.free();
}

// Initialize Algorithm
void Player::algo(){
	/*for (int i = 0; i < 3; i++){
		moves[i] = rand() % 3 + 1;
	}*/
	moves[0] = 3;
	moves[1] = 1;
	moves[2] = 1;
}


// Update Algorithm
void Player::updateAlgo(){
	/*int randi = rand() % 10 + 1;

	if (randi==4){
		this->initialshot = true;
	}

	if (randi==3){
		this->thrust = true;
	}else{
		this->thrust = false;
	}

	if (randi==2){
		this->rotateLeft = true;
	}else if (randi==3){
		this->rotateRight = true;
	}else{
		this->rotateLeft = false;
		this->rotateRight = false;
	}*/
}

// Initializer Player
void Player::init(float x, float y){
	this->x = x;
	this->y = y;
	this->accuracy				= 0.0;
	this->hits					= 0.0;
	this->totalShot				= 0.0;
	this->score 				= 0;
	this->wave 					= 0;
	this->increment	 			= 2;
	this->thrustSpeedX2 		= 0.0;
	this->thrustSpeedY2 		= 0.0;
	this->delayT 				= 0;
	this->health				= 200;
	this->delay 				= false;
	this->initialshot 			= false;
	this->thrust 				= false;
	this->deathScreen 			= false;
	this->alive 				= true;
	this->bg 					= rand() % 2 + 1;
}

// Load Player score data
void Player::updateScore(){
	indx = 0;
	ifstream fileO("highscores.txt");
	string str;
	bool getHighest = true;
	while (getline(fileO, str))
	{
		// Read current line
		istringstream iss(str);
		string temps[2];
		iss >> temps[0] >> temps[1];

		// Store first line as highscore
		if (getHighest){
			getHighest = false;
			this->highscore = atoi(temps[1].c_str());
		}

		// Load highscore data
		stringstream tempss;
		tempss << temps[0] << " " << temps[1];
		highList[indx] = tempss.str().c_str();
		indx++;
	}

	fileO.close();
	cout << "DONE" << endl;
}

// Reset game
void Player::reset(float x, float y){
	this->x 					= x;
	this->y 					= y;
	this->accuracy				= 0.0;
	this->hits					= 0.0;
	this->totalShot				= 0.0;
	this->score 				= 0;
	this->wave 					= 0;
	this->increment	 			= 2;
	this->thrustSpeedX2 		= 0.0;
	this->thrustSpeedY2 		= 0.0;
	this->delayT 				= 0;
	this->health				= 200;
	this->delay 				= false;
	this->initialshot 			= false;
	this->thrust 				= false;
	this->deathScreen 			= false;
	this->alive 				= true;
	this->bg 					= rand() % 2 + 1;
}

// Update Player
void Player::update(int screenWidth, int screenHeight, Asteroid asteroid[], Asteroid &a_dummy,
					Enemy enemy[], Enemy &e_dummy,
					Particle particle[], Particle &p_dummy,
					Explosion explosion[], Explosion &ex_dummy,
					unsigned int &HS, int &HW, int mx, int my, bool &leftclick,
					float spawnX, float spawnY,
					int mapX, int mapY, int mapW, int mapH,
					LWindow gWindow, Input &i_dummy, SDL_Renderer* gRenderer,
					LTexture gText, TTF_Font *gFont, SDL_Color color,
					Mix_Chunk *sLazer, Mix_Chunk *sAtariBoom)
{
	if (this->alive){
		// Set mini map
		/*miniMap.w = 160;
		miniMap.h = 160;
		miniMap.x = screenWidth-miniMap.w-20;
		miniMap.y = screenHeight-miniMap.h-20;*/

		//Moving Player
		if (this->moveleft) {
			this->thrustSpeedX2 -= 0.1;
		}else if (this->moveright) {
			this->thrustSpeedX2 += 0.1;
		}
		if (this->moveup) {
			this->thrustSpeedY2 -= 0.1;
		} else if (this->movedown) {
			this->thrustSpeedY2 += 0.1;
		}

		//Ship follows mouse
		/*if (this->travelMode == "fight"){
			this->angle = atan2(my+camy - this->y-this->h/2,mx+camx - this->x-this->w/2);
			this->angle = this->angle * (180 / 3.1416);

			//Set player angle max limits
			if (this->angle < 0) {
				this->angle = 360 - (-this->angle);
			}
		}*/

		//Ship follows rotation
		if (this->travelMode == "travel")
		{
			//Add players angle with the rotation speed; Calculate players radian
			//this->angle = atan2(my- this->y-this->h/2,mx- this->x-this->w/2);
			//this->angle = this->angle * (180 / 3.1416);

			//Angle/Rotation of Player
			if (this->rotateLeft) {
				this->angle -= 4;
			} else if (this->rotateRight) {
				this->angle += 4;
			}
			if (this->angle < 0) {
				this->angle = 360 - (-this->angle);
			}
			this->radians = (3.1415926536/180)*(this->angle);
			//this->radianCos = floor(cos(this->radians)*10+0.5)/10;
			//this->radianSin = floor(sin(this->radians)*10+0.5)/10;


			//Accelerate Player
			if (this->thrust){
				this->thrustSpeedX2 += cos(this->radians) * 0.05;
				this->thrustSpeedY2 += sin(this->radians) * 0.05;

				// Thrust effect
				this->thrustT += 1;
				if (this->thrustT > 2){
					this->thrustT = 0;
					float x1, x2, y1, y2, anglet;
					int rands, randd, randdd;
					//SDL_Color tempColor = { rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1};
					SDL_Color tempColor = { 255, 255, 255 };
					x1 				= this->x+this->w/2,
					y1 				= this->y+this->h/2;
					x2 				= this->x+this->w/2 + cos(this->radians),
					y2 				= this->y+this->h/2 + sin(this->radians);
					anglet 			= atan2(y1 - y2, x1 - x2);
					anglet 			= anglet * (180 / 3.1416);
					rands 			= rand() % 3 + 6;
					randd			= rand() % 2 + 1;
					if (randd==1) {randdd = 1;} else {randdd = -1;}
					p_dummy.spawnParticleAngle(particle,
									   this->x+this->w/2-rands/2, this->y+this->h/2-rands/2,
									   rands, rands,
									   anglet, rand() % 2 + 2,
									   rand() % 150 + 50, 4,
									   100, 0,
									   0.0, "stars",
									   tempColor, 1,
									   rand() % 4 + 5, randdd,
									   false, 0);
				}
			}else{

			    // Use Stokes' law to apply drag to the ship
				this->thrustSpeedX2 = this->thrustSpeedX2 - this->thrustSpeedX2 * 0.001;
				this->thrustSpeedY2 = this->thrustSpeedY2 - this->thrustSpeedY2 * 0.001;
			}

			//Add player velocity
			this->x += this->thrustSpeedX2;
			this->y += this->thrustSpeedY2;

			if (this->thrustSpeedX2 > 40) {
				this->thrustSpeedX2 = 40;
			}
			if (this->thrustSpeedX2 < -40) {
				this->thrustSpeedX2 = -40;
			}
			if (this->thrustSpeedY2 > 40) {
				this->thrustSpeedY2 = 40;
			}
			if (this->thrustSpeedY2 < -40) {
				this->thrustSpeedY2 = -40;
			}
		}

		// Player shoot
		if (this->mode == "player")
		{
			if (!this->delay)
			{
				if (this->initialshot)
				{
					this->initialshot = false;
					//this->delay = true;

					// Remove shield
					/*if (this->shield){
						this->shield 	= false;
						this->shieldT 	= 300;
					}*/

					// Shoot particle
					if (this->powerup == "LAZER") {
						this->totalShot++;

						//Mix_PlayChannel(-1, sLazer, 0);
						//float randAccuracy = fRandP(0.0, 12.0);
						/*spawnParticleAngle(particle,
										   this->x+this->w/2-47/2+(cos(this->radians)*16),
										   this->y+this->h/2-34/2+(sin(this->radians)*16),
										   47, 34,
										   this->angle+(-6.0+randAccuracy), 9,
										   255, 1,
										   200, 2,
										   100);*/
						Mix_PlayChannel(-1, sLazer, 0);
						float randAccuracy = fRandP(0.0, 2.0);
						p_dummy.spawnParticleAngle(particle,
								   this->x+this->w/2-4/2+(cos(this->radians)*16),
								   this->y+this->h/2-4/2+(sin(this->radians)*16),
								   4, 4,
								   this->angle+(-1.0+randAccuracy), 16,
								   255, 0,
								   100, 2,
								   100, "LAZER",
								   color, 1,
								   1, 1,
								   false, 0);
					}
				}
			}
			//Start delay timer after our first shot!
			if (this->delay) {
				this->delayT += this->AttackSpeed*6;
				if (this->delayT > 60) {
					this->delay = false;
					this->delayT = 0;
				}
			}
		}

		// Player shield
		if (this->shield){
			this->shieldT -= 1;
			if (this->shieldT <= 0){
				this->shieldT 	= 300;
				this->shield 	= false;
			}
		}

		// Update Player score and Wave
		if (this->score > HS){
			HS 	= this->score;
		}
		if (this->wave > HW){
			HW 	= this->wave;
		}

		// Player death
		if (this->health <=0)
		{
			// Reset health
			this->health = 0;

			// Reset some accumulated stuff
			e_dummy.ENEMY_SPAWN = 1;
			e_dummy.mileScore	= 0;
			e_dummy.SPAWN_ENEMY	= false;

			// Set variables
			this->shieldT 		= 300;
			this->shield 		= true;
			this->alive 		= false;
			this->deathScreen 	= true;

			//Spawn explosion after asteroid death
			ex_dummy.spawn(explosion, this->x+this->w/2-this->w/2, this->y+this->h/2-this->h/2,
									  this->w, this->h, 255, "normal", sAtariBoom);

			// Clear Enemies
			for (int i = 0; i < e_dummy.Max; i++) {
				enemy[i].alive = false;
			}
			e_dummy.ENEMY_COUNT = 0;

			// Send high score to server
			/*std::stringstream tempSS;
			tempSS << "GO" 			<< "\n"
				   << "Carl"	    << "\n"
				   << this->score;
			UDPpacket *p;
			p = SDLNet_AllocPacket(512);
			p->data = (Uint8*) tempSS.str().c_str();
			p->address.host = srvadd.host;
			p->address.port = srvadd.port;
			p->len = strlen(tempSS.str().c_str()) + 1;
			SDLNet_UDP_Send(sd, -1, p);
			SDLNet_FreePacket(p);*/
		}

		// Player boundaries
		if (this->x+this->w < mapX) {
			this->x = mapX+mapW-this->w;
		}
		if (this->x > mapX+mapW) {
			this->x = mapX-this->w;
		}
		if (this->y+this->h < mapY) {
			this->y = mapY+mapH-this->h;
		}
		if (this->y > mapY+mapH) {
			this->y = mapY-this->h;
		}
	}else{
			// Death Screen
			if (this->deathScreen)
			{
				// Set button position
				continueButton[0] = {screenWidth/2-96/2-100,
									screenHeight/2-gTextt.getHeight()/2,
									96,
									33};
				continueButton[1] = {screenWidth/2-96/2+100, screenHeight/2-gTextt.getHeight()/2, 96, 33};

				// Left click
				if (leftclick)
				{
					// Option: Yes, reset everything
					if (checkCollision(mx, my, 1, 1, continueButton[0].x, continueButton[0].y, continueButton[0].w, continueButton[0].h))
					{
						leftclick			= false;
						//////////////////////////////////////////////////////////////
						//---------------------- Save High-Score -------------------//
						i_dummy.getInput(this->name,
								gWindow,
								gRenderer,
								color,
								gText,
								gFont);
						ifstream fileOS("highscores.txt");
						string str;
						stringstream tempss;
						bool replace = true;
						while (getline(fileOS, str)){
							// Read current line
							istringstream iss(str);
							string temps[2];
							iss >> temps[0] >> temps[1];
							cout << temps[0] << ": " << temps[1] << endl;

							// Save score if higher, else keep old score
							if (this->score > atoi( temps[1].c_str() )){
								if (replace){
									replace = false;
									tempss << this->name << " " << this->score << endl;
								}else{
									tempss << temps[0] << " " << temps[1] << endl;
								}
							}else{
								tempss << temps[0] << " " << temps[1] << endl;
							}
						}
						fileOS.close();

						// Overwrite "highscores.txt"
						ofstream fileS;
						fileS.open("highscores.txt");
						fileS << tempss.str().c_str();
						fileS.close();
						//---------------------- Save High-Score -------------------//
						//////////////////////////////////////////////////////////////

						// Reset Player
						reset(spawnX, spawnY);

						// Update score display
						updateScore();

						// Reset Asteroids
						for (int i = 0; i < 128; i++) {asteroid[i].alive = false;}
						a_dummy.ASTEROIDS = 0;

						// Hide Cursor
						SDL_ShowCursor(false);
					}

					// Option: No, go to Main Menu
					if (checkCollision(mx, my, 1, 1, continueButton[1].x, continueButton[1].y, continueButton[1].w, continueButton[1].h))
					{
						leftclick			= false;
						//////////////////////////////////////////////////////////////
						//----------------------------------------------------------//
						//---------------------- Save High-Score -------------------//
						i_dummy.getInput(this->name,
								gWindow,
								gRenderer,
								color,
								gText,
								gFont);
						ifstream fileO("highscores.txt");
						string str;
						stringstream tempss;
						bool replace = true;
						while (getline(fileO, str)){
							// Read current line
							istringstream iss(str);
							string temps[2];
							iss >> temps[0] >> temps[1];
							cout << temps[0] << ": " << temps[1] << endl;

							// Save score if higher, else keep old score
							if (this->score > atoi( temps[1].c_str() )){
								if (replace){
									replace = false;
									tempss << this->name << " " << this->score << endl;
								}else{
									tempss << temps[0] << " " << temps[1] << endl;
								}
							}else{
								tempss << temps[0] << " " << temps[1] << endl;
							}
						}
						fileO.close();

						// Overwrite "highscores.txt"
						ofstream fileS;
						fileS.open("highscores.txt");
						fileS << tempss.str().c_str();
						fileS.close();

						// Update score display
						updateScore();
						//---------------------- Save High-Score -------------------//
						//----------------------------------------------------------//
						//////////////////////////////////////////////////////////////

						this->deathScreen = false;
					}
				}
			// Menu Screen
			}else{
				// Set button position
				continueButton[0] = {screenWidth/2-96/2, screenHeight/2-gTextt.getHeight()/2, 96, 33};

				// Left click
				if (leftclick)
				{
					// Option: Play
					if (checkCollision(mx, my, 1, 1, continueButton[0].x, continueButton[0].y, continueButton[0].w, continueButton[0].h))
					{
						// Reset Player
						reset(spawnX, spawnY);

						// Reset Asteroids
						for (int i = 0; i < 128; i++) {asteroid[i].alive = false;}
						a_dummy.ASTEROIDS = 0;

						// Hide Cursor
						SDL_ShowCursor(false);
					}
				}
			}
	}
}

// Render Player
void Player::render(int screenWidth, int screenHeight, int camx, int camy,
					SDL_Renderer* gRenderer,
					TTF_Font *gFont, TTF_Font *gFont2,
					SDL_Color color)
{
	// Player alive
	if (this->alive){

		// Render Player
		gPlayer.render(gRenderer, this->x-camx, this->y-camy,
					   this->w, this->h, NULL,
					   this->angle);

		// Render Shield
		if (this->shield){
			gShield.render(gRenderer, this->x-4-camx, this->y-4-camy,
						   24, 24);

			SDL_Rect tempRect = {this->x-camx, this->y-16-camy, (this->w*this->shieldT)/300, 3};
			SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
			SDL_RenderFillRect(gRenderer, &tempRect);

		}

		//TODO make minimap relative to players position
		// Render minimap
		/*SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(gRenderer, &miniMap);

		SDL_RenderDrawPoint(gRenderer, 10, 10);*/


	// Player death, or menu screen
	}else{
		// Player death screen
		if (this->deathScreen)
		{
			SDL_ShowCursor(true);
			// Render Text
			gTextt.loadFromRenderedText("You have died. Continue?", color, gFont2, gRenderer);
			gTextt.render(gRenderer, screenWidth/2-gTextt.getWidth()/2, screenHeight/2-gTextt.getHeight()/2-50, gTextt.getWidth(), gTextt.getHeight());

			// Render buttons: Yes or No
			SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
			SDL_RenderDrawRect(gRenderer, &continueButton[0]);

			SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(gRenderer, &continueButton[1]);

			// Render button texts: Yes or No
			gTextt.loadFromRenderedText("Yes", color, gFont2, gRenderer);
			gTextt.render(gRenderer,  continueButton[0].x+continueButton[0].w/2-gTextt.getWidth()/2,
									 continueButton[0].y+continueButton[0].h/2-gTextt.getHeight()/2,
									 gTextt.getWidth(), gTextt.getHeight());

			gTextt.loadFromRenderedText("No", color, gFont2, gRenderer);
			gTextt.render(gRenderer,  continueButton[1].x+continueButton[1].w/2-gTextt.getWidth()/2,
									 continueButton[1].y+continueButton[1].h/2-gTextt.getHeight()/2,
									 gTextt.getWidth(), gTextt.getHeight());
		// Player Menu screen
		}else{
			this->travel += 0.05 * this->dir;
			if (this->travel > 10){
				this->dir = -1;
			}
			if (this->travel < -10){
				this->dir = 1;
			}

			//Display high score
			for (int i=0; i<10; i++){
				istringstream tempString(highList[i].c_str());
				string line;
				while (getline(tempString, line)) {
					istringstream iss(line);
					string temps[2];
					iss >> temps[0] >> temps[1];

					gTextt.loadFromRenderedText(temps[0].c_str(), color, gFont, gRenderer);
					gTextt.setAlpha(255-i*10);
					gTextt.render(gRenderer, continueButton[0].x+this->travel,
							continueButton[0].y+continueButton[0].h+20+i*14,
							gTextt.getWidth(), gTextt.getHeight());


					gTextt.loadFromRenderedText(temps[1].c_str(), color, gFont, gRenderer);
					gTextt.setAlpha(255-i*10);
					gTextt.render(gRenderer, continueButton[0].x+continueButton[0].w-gTextt.getWidth()+this->travel,
							continueButton[0].y+continueButton[0].h+20+i*14,
							gTextt.getWidth(), gTextt.getHeight());
				}
			}

			// Render buttons: Play
			SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
			SDL_RenderDrawRect(gRenderer, &continueButton[0]);

			// Render Text
			gTextt.loadFromRenderedText("PLAY", color, gFont2, gRenderer);
			gTextt.render(gRenderer, continueButton[0].x+continueButton[0].w/2-gTextt.getWidth()/2,
									 continueButton[0].y+continueButton[0].h/2-gTextt.getHeight()/2,
									 gTextt.getWidth(), gTextt.getHeight());
		}
	}

	// Debug
	// Render Player collision box
	//SDL_Rect tempRect {player.x-camx, player.y-camy, player.w, player.h};
	//SDL_SetRenderDrawColor(gRenderer, 255, 244, 20, 255);
	//SDL_RenderDrawRect(gRenderer, &tempRect);

	//  Player UI
	/*if (this->travelMode == "travel"){
		gTextt.loadFromRenderedText("travel", {0,255,0,0}, gFont13);
		gTextt.render(gRenderer, 5, 5, gTextt.getWidth(), gTextt.getHeight());
	}
	if (this->travelMode == "fight"){
		gTextt.loadFromRenderedText("fight", {255,0,0,0}, gFont13);
		gTextt.render(gRenderer, 5, 5, gTextt.getWidth(), gTextt.getHeight());
	}
	if (this->camlocked){
		gTextt.loadFromRenderedText("cam: locked", {0,255,0,0}, gFont13);
		gTextt.render(gRenderer, 5, 18, gTextt.getWidth(), gTextt.getHeight());
	}

	if (!this->camlocked){
		gTextt.loadFromRenderedText("cam: unlocked", {255,0,0,0}, gFont13);
		gTextt.render(gRenderer, 5, 18, gTextt.getWidth(), gTextt.getHeight());
	}*/
}

