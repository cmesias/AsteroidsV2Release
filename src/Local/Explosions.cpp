/*
 * Explosions.cpp
 *
 *  Created on: Dec 18, 2016
 *      Author: Carl
 */

#include <SDL2/SDL.h>
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
using namespace std;

#include "Explosions.h"

// Clip function
void Explosion::setClips(SDL_Rect &tempRect, int x, int y, int w, int h){
	tempRect.x = x;
	tempRect.y = y;
	tempRect.w = w;
	tempRect.h = h;
}

// Load explosions resources
void Explosion::loadResources(SDL_Renderer* gRenderer)
{
	// Textures
	gExplosion.loadFromFile("img/explosion/explosion.png", gRenderer);
	gExplosionBlue.loadFromFile("img/explosion/explosion-blue.png", gRenderer);
	setClips(rExplosion[0], 0, 0, 64, 64);
	setClips(rExplosion[1], 64, 0, 64, 64);
	setClips(rExplosion[2], 64, 0, 64, 64);
	setClips(rExplosion[3], 192, 0, 64, 64);
	setClips(rExplosion[4], 256, 0, 64, 64);
	setClips(rExplosion[5], 320, 0, 64, 64);
	setClips(rExplosionBlue[0], 0, 0, 64, 64);
	setClips(rExplosionBlue[1], 64, 0, 64, 64 );
	setClips(rExplosionBlue[2], 128, 0, 64, 64 );
	setClips(rExplosionBlue[3], 192, 0, 64, 64);
	setClips(rExplosionBlue[4], 256, 0, 64, 64 );
	setClips(rExplosionBlue[5], 320, 0, 64, 64 );

	//gExplosion.setBlendMode(SDL_BLENDMODE_ADD);
	//gExplosionBlue.setBlendMode(SDL_BLENDMODE_ADD);
}

// Free explosion resources
void Explosion::freeResources(){
	gExplosion.free();
	gExplosionBlue.free();
}

//Declare explosions
void Explosion::init(Explosion explosion[]) {
	for (int i = 0; i < EXPLOSION_MAX; i++) {
		explosion[i].animTimer = 0;
		explosion[i].animFrame = 1;
		explosion[i].alive = false;
		explosion[i].type = "";
	}
}
//Spawn an explosion
void Explosion::spawn(Explosion explosion[], int x, int y, int w, int h, int alpha, string type, Mix_Chunk *sAtariBoom) {
	for (int i = 0; i < EXPLOSION_MAX; i++) {
		if (!explosion[i].alive) {
			explosion[i].type = type;
			explosion[i].x = x;
			explosion[i].y = y;
			explosion[i].w = w;
			explosion[i].h = h;
			explosion[i].animTimer = 0;
			explosion[i].animFrame = 1;
			explosion[i].alpha = 255;
			explosion[i].alive = true;
			EXPLOSION_COUNT++;
			//Play sound effect of explosion
			Mix_Pause(3);
			Mix_PlayChannel(3, sAtariBoom, 0);
			break;
		}
	}
}

//Update Explosion
void Explosion::update(Explosion explosion[], int mode) {
	for (int i = 0; i < EXPLOSION_MAX; i++) {
		if (explosion[i].alive) {
			//If player is in 'Game' mode then disable enemy movement
			if (mode == 1){
				//Start animation
				explosion[i].animTimer += 1;
				if (explosion[i].animTimer > 5){
					explosion[i].animTimer = 0;
					explosion[i].animFrame += 1;
				}
				//Stop animation after 24*6 frames, and remove explosion
				if (explosion[i].animFrame > 6){
					explosion[i].animTimer = 0;
					explosion[i].animFrame = 1;
					explosion[i].alive = false;
					EXPLOSION_COUNT--;
				}
			}
		}
	}
}
//Render explosion
void Explosion::render(Explosion explosion[], int camX, int camY, SDL_Renderer* gRenderer) {
	for (int i = 0; i < EXPLOSION_MAX; i++) {
		if (explosion[i].alive) {
			if (explosion[i].type == "normal"){
				if (explosion[i].animFrame == 1){
					gExplosion.render(gRenderer, explosion[i].x - camX, explosion[i].y - camY,explosion[i].w, explosion[i].h, &rExplosion[0]);
				}
				if (explosion[i].animFrame == 2){
					gExplosion.render(gRenderer, explosion[i].x - camX, explosion[i].y - camY,explosion[i].w, explosion[i].h, &rExplosion[1]);
				}
				if (explosion[i].animFrame == 3){
					gExplosion.render(gRenderer, explosion[i].x - camX, explosion[i].y - camY,explosion[i].w, explosion[i].h, &rExplosion[2]);
				}
				if (explosion[i].animFrame == 4){
					gExplosion.render(gRenderer, explosion[i].x - camX, explosion[i].y - camY,explosion[i].w, explosion[i].h, &rExplosion[3]);
				}
				if (explosion[i].animFrame == 5){
					gExplosion.render(gRenderer, explosion[i].x - camX, explosion[i].y - camY,explosion[i].w, explosion[i].h, &rExplosion[4]);
				}
				if (explosion[i].animFrame == 6){
					gExplosion.render(gRenderer, explosion[i].x - camX, explosion[i].y - camY,explosion[i].w, explosion[i].h, &rExplosion[5]);
				}
			}
			if (explosion[i].type == "blue"){
				if (explosion[i].animFrame == 1){
					gExplosionBlue.render(gRenderer, explosion[i].x - camX, explosion[i].y - camY,explosion[i].w, explosion[i].h, &rExplosionBlue[0]);
				}
				if (explosion[i].animFrame == 2){
					gExplosionBlue.render(gRenderer, explosion[i].x - camX, explosion[i].y - camY,explosion[i].w, explosion[i].h, &rExplosionBlue[1]);
				}
				if (explosion[i].animFrame == 3){
					gExplosionBlue.render(gRenderer, explosion[i].x - camX, explosion[i].y - camY,explosion[i].w, explosion[i].h, &rExplosionBlue[2]);
				}
				if (explosion[i].animFrame == 4){
					gExplosionBlue.render(gRenderer, explosion[i].x - camX, explosion[i].y - camY,explosion[i].w, explosion[i].h, &rExplosionBlue[3]);
				}
				if (explosion[i].animFrame == 5){
					gExplosionBlue.render(gRenderer, explosion[i].x - camX, explosion[i].y - camY,explosion[i].w, explosion[i].h, &rExplosionBlue[4]);
				}
				if (explosion[i].animFrame == 6){
					gExplosionBlue.render(gRenderer, explosion[i].x - camX, explosion[i].y - camY,explosion[i].w, explosion[i].h, &rExplosionBlue[5]);
				}
			}
		}
	}
}
