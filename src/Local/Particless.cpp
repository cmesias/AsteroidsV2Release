/*
 * Particless.cpp
 *
 *  Created on: Dec 16, 2016
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

#include "Players.h"
#include "Particless.h"



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////// ENEMY BULLETS //////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------------------------------------------------------//

void Particle::setClips(SDL_Rect &tempRect, int x, int y, int w, int h){
	tempRect.x = x;
	tempRect.y = y;
	tempRect.w = w;
	tempRect.h = h;
}

void Particle::loadTexture(SDL_Renderer* gRenderer){
	setClips(cParticles[0], 0, 0, 8, 8);
	setClips(cParticles[1], 8, 0, 8, 8 );
	setClips(cParticles[2], 16, 0, 8, 8);
	setClips(cParticles[3], 24, 0, 8, 8);
	setClips(cParticles[4], 32, 0, 8, 8);
	setClips(cParticles[5], 48, 0, 8, 8);
	gParticles.loadFromFile("img/particle/particles.png", gRenderer);
	gParticles.setBlendMode(SDL_BLENDMODE_ADD);
}

void Particle::freeTexture(){
	gParticles.free();
}

void Particle::initParticle(Particle particle[]) {
	for (int i = 0; i < 1024; i++) {
		particle[i].x = 0;
		particle[i].y = 0;
		particle[i].w = 4;
		particle[i].h = 4;
		particle[i].alpha = 255;
		particle[i].time = 0;
		particle[i].alphaspeed = 0;
		particle[i].deathTimer = 100;
		particle[i].deathTimerSpeed = 1;
		particle[i].speed = 0.00;
		particle[i].vX = 0.00;
		particle[i].vY = 0.00;
		particle[i].speed = 0.00;
		particle[i].angle = 0.00;
		particle[i].angleSpe = 0;
		particle[i].angleDir = 0;
		particle[i].onScreen = false;
		particle[i].collide = false;
		particle[i].alive = false;
		particle[i].sizeDeath 		= false;
		particle[i].deathSpe 		= 0;
		particle[i].side = "";
		particle[i].type = "";
		particle[i].damage = 0;
		particle[i].color = { 255, 255, 255, 255 };
	}
}

// Spawn a Particle: moves based on angle given and fixed speed
void Particle::spawnParticleAngle(Particle particle[],
		int playerx, int playery,
		int w, int h,
		double angle, double speed,
		int alpha, int alphaspeed,
		int deathTimer, int deathTimerSpeed,
		double damage, string type,
		SDL_Color color, int layer,
		int angleSpe, int angleDir,
		bool sizeDeath, float deathSpe) {
	for (int i = 0; i < 1024; i++)
	{
		if (!particle[i].alive)
		{
			particle[i].time 			= 0;
			particle[i].angle 			= angle;
			particle[i].speed 			= speed;
			particle[i].vX 				= (cos( (3.14159265/180)*(angle) ));
			particle[i].vY 				= (sin( (3.14159265/180)*(angle) ));
			particle[i].type 			= type;
			particle[i].damage 			= damage;
			particle[i].x 				= playerx + (rand() % 4 + 2 * (cos( (3.14159265/180)*(angle) )));
			particle[i].y 				= playery + (rand() % 4 + 2 * (sin( (3.14159265/180)*(angle) )));
			particle[i].w 				= w;
			particle[i].h 				= h;
			particle[i].alphaspeed 		= alphaspeed;
			particle[i].alpha 			= alpha;
			particle[i].deathTimer 		= deathTimer;
			particle[i].deathTimerSpeed = deathTimerSpeed;
			particle[i].side 			= "";
			particle[i].angleSpe		= angleSpe;
			particle[i].angleDir		= angleDir;
			particle[i].sizeDeath 		= sizeDeath;
			particle[i].deathSpe 		= deathSpe;
			particle[i].onScreen 		= false;
			particle[i].collide 		= false;
			particle[i].alive 			= true;
			particle[i].color 			= color;
			particle[i].layer 			= layer;
			PARTICLES++;
			break;
		}
	}
}

// Spawn a Particle: moves based on a fixed velocity given and fixed speed
void Particle::fireParticle(Particle particle[], int damage, string type,
									   int spawnx, int spawny, int w, int h,
									   double speed, float vX, float vY,
									   int alphaspeed, int alpha,
									   int deathTimer, int deathTimerSpeed, double angle, double angleSpe, double angleDir,
									   SDL_Color color, int layer) {
	for (int i = 0; i < 1024; i++) {
		if (!particle[i].alive) {
			particle[i].damage 			= damage;
			particle[i].type 			= type;
			particle[i].alphaspeed 		= alphaspeed;
			particle[i].alpha  			= alpha;
			particle[i].x  				= spawnx;
			particle[i].y  				= spawny;
			particle[i].w  				= w;
			particle[i].h  				= h;
			particle[i].speed  			= speed;
			particle[i].angle 			= angle;
			particle[i].angleSpe		= angleSpe;
			particle[i].angleDir		= angleDir;
			particle[i].vX  			= vX;
			particle[i].vY  			= vY;
			particle[i].deathTimer 		= deathTimer;
			particle[i].deathTimerSpeed = deathTimerSpeed;
			particle[i].sizeDeath 		= false;
			particle[i].deathSpe 		= 0;
			particle[i].time 			= 0;
			particle[i].side 			= "";
			particle[i].onScreen 		= false;
			particle[i].collide 		= false;
			particle[i].alive 			= true;
			particle[i].color 			= color;
			particle[i].layer 			= layer;
			//particle[i].angle 		= atan2 ( radianSin, radianCos) * 180 / PI;
			PARTICLES++;
			break;
		}
	}
}

// Spawn particles: represent stars
void Particle::spawnStars(Particle particle[], int x, int y, float w, float h, int alphaspeed, int alpha, int camx, int camy, SDL_Color color, int layer){
	fireParticle(particle, 0, "stars",
							x,y,w, h,
							0,
							0.0,0.0, alphaspeed, alpha,
							100, 1, 0.0, 0.0, 0.0,
							color, layer);
}

// Spawn a Particle: moves based on location of a target given
void Particle::fireParticle2(Particle particle[], int damage, int spawnx, int spawny, int w, int h, int targetx,int targety,
										int alphaspeed, int alpha,
										int deathTimer, int deathTimerSpeed,
										double speed, string type,
										SDL_Color color, int layer) {
	for (int i = 0; i < 1024; i++) {
		if (!particle[i].alive) {
			particle[i].damage 			= damage;
			particle[i].alpha  			= alpha;
			particle[i].deathTimer 		= deathTimer;
			particle[i].alphaspeed 		= alphaspeed;
			particle[i].deathTimerSpeed = deathTimerSpeed;
			particle[i].type 			= type;
			particle[i].x 				= spawnx;
			particle[i].y 				= spawny;
			particle[i].w 				= w;
			particle[i].h 				= h;
			particle[i].speed 			= speed;
			float bmx 					= targetx;
			float bmy 					= targety;
			float distance 				= sqrt((bmx - spawnx) * (bmx - spawnx - particle[i].w / 2) +
											   (bmy - spawny) * (bmy - spawny - particle[i].h / 2));
			particle[i].vX 				= particle[i].speed  *  (bmx - spawnx - particle[i].w / 2) / distance;
			particle[i].vY 				= particle[i].speed  *  (bmy - spawny - particle[i].h / 2) / distance;
			particle[i].angle 			= atan2(bmy - particle[i].y, bmx - particle[i].x);
			particle[i].angle 			= particle[i].angle * (180 / 3.1416);
			particle[i].angleSpe		= 0;
			particle[i].angleDir		= 0;
			particle[i].sizeDeath 		= false;
			particle[i].deathSpe 		= 0;
			particle[i].time 			= 0;
			particle[i].side 			= "";
			particle[i].collide 		= false;
			particle[i].onScreen 		= false;
			particle[i].alive 			= true;
			particle[i].color 			= color;
			particle[i].layer 			= layer;
			PARTICLES++;
			break;
		}
	}
}

// Update Particles
void Particle::updateParticles(Particle particle[], int mapX, int mapY, int mapW, int mapH) {
	for (int i = 0; i < 1024; i++) {
		if (particle[i].alive)
		{
			// Particle spin
			particle[i].angle += particle[i].angleSpe * particle[i].angleDir;

			// Particle movement
			particle[i].x += particle[i].vX * particle[i].speed;
			particle[i].y += particle[i].vY * particle[i].speed;

			// Particle death
			particle[i].time += particle[i].deathTimerSpeed;

			// Player lazer particles
			if (particle[i].type == "LAZER")
			{
				// Particle map collision
				if (particle[i].x+particle[i].w < mapX) {
					particle[i].x = mapX+mapW-particle[i].w;
				}
				if (particle[i].x > mapX+mapW) {
					particle[i].x = mapX-particle[i].w;
				}
				if (particle[i].y+particle[i].h < mapY) {
					particle[i].y = mapY+mapH-particle[i].h;
				}
				if (particle[i].y > mapY+mapH) {
					particle[i].y = mapY-particle[i].h;
				}

				//Update particles angle based on its X and Y velocities
				particle[i].angle = atan2 ( particle[i].vY, particle[i].vX) * 180 / 3.14159265;

				// Particle death
				if (particle[i].time > particle[i].deathTimer) {
					particle[i].alive = false;
					PARTICLES--;
				}
			}

			// Enemy lazer particles
			if (particle[i].type == "LAZER_P")
			{
				// Particle death
				if (particle[i].time > particle[i].deathTimer) {
					particle[i].alive = false;
					PARTICLES--;
				}
			}

			// Star particles
			if (particle[i].type == "stars"){

				// Particle death
				if (particle[i].time > particle[i].deathTimer) {
					particle[i].alive = false;
					PARTICLES--;
				}

				// Particle death
				particle[i].alpha -= particle[i].alphaspeed;
				if (particle[i].alpha < 0) {
					particle[i].alive = false;
					PARTICLES--;
				}

				// Particle death upon size
				/*if (particle[i].sizeDeath) {
					particle[i].w -= particle[i].deathSpe;
					particle[i].h -= particle[i].deathSpe;

					if (particle[i].w <= 0 || particle[i].h <= 0){
						particle[i].alive = false;
						PARTICLES--;
					}
				}*/
			}
		}
	}
}

void Particle::renderParticle(Particle particle[], int camX, int camY, float playerZ, SDL_Renderer* gRenderer) {
	for (int i = 0; i < 1024; i++) {
		if (particle[i].alive) {

			// Render Player lazer particle
			if (particle[i].type == "LAZER") {
				/*SDL_Rect tempRect = {particle[i].x - camX,
						   particle[i].y - camY,
						   particle[i].w,  particle[i].h};
				SDL_SetRenderDrawColor(gRenderer, 255,255,255,255);
				SDL_RenderFillRect(gRenderer, &tempRect);*/

				gParticles.setAlpha(particle[i].alpha);
				gParticles.setColor(255, 255, 255);
				gParticles.render(gRenderer, particle[i].x - camX,particle[i].y - camY,
						 particle[i].w, particle[i].h,
						 &cParticles[1], particle[i].angle);
			}

			// Render Enemy lazer particle
			if (particle[i].type == "LAZER_E") {
				/*SDL_Rect tempRect = {particle[i].x - camX,
						   particle[i].y - camY,
						   particle[i].w,  particle[i].h};
				SDL_SetRenderDrawColor(gRenderer, 255,255,255,255);
				SDL_RenderFillRect(gRenderer, &tempRect);*/

				gParticles.setAlpha(particle[i].alpha);
				gParticles.setColor(255, 255, 255);
				gParticles.render(gRenderer, particle[i].x - camX,particle[i].y - camY,
						 particle[i].w, particle[i].h,
						 &cParticles[3], particle[i].angle);
			}

			// Render stars particle
			if (particle[i].type == "stars") {

				/*SDL_Rect tempRect = {particle[i].x - camX/particle[i].layer,particle[i].y - camY/particle[i].layer,
						   particle[i].w,  particle[i].h};
				SDL_SetRenderDrawColor(gRenderer, particle[i].color.r, particle[i].color.g, particle[i].color.b,1);
				SDL_RenderFillRect(gRenderer, &tempRect);*/

				gParticles.setAlpha(particle[i].alpha);
				gParticles.setColor(particle[i].color.r, particle[i].color.g, particle[i].color.b);
				gParticles.render(gRenderer, particle[i].x - camX/particle[i].layer,particle[i].y - camY/particle[i].layer,
											 particle[i].w, particle[i].h,
											 &cParticles[4], particle[i].angle);
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------------------//
////////////////////////////////////////////////////////// ENEMY BULLETS //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

