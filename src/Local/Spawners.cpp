/*
 * Spawners.cpp
 *
 *  Created on: Dec 18, 2016
 *      Author: Carl
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
using namespace std;

#include "Asteroids.h"
#include "Spawners.h"

// Generate random number
double fRandS(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

// Initialize Spawner
void Spawner::init(Spawner spawner[]) {
	for (int i = 0; i < 200; i++) {
		spawner[i].x 			= 0;
		spawner[i].y 			= 0;
		spawner[i].w 			= 0;
		spawner[i].h 			= 0;
		spawner[i].spawnTimer 	= 0;
		spawner[i].spawned 		= 0;
		spawner[i].maxSpawn 	= 10;
		spawner[i].clipIndex 	= 0;
		spawner[i].type 		= "";
		spawner[i].alive 		= false;
		spawner[i].moused 		= false;
	}
}

// Spawn a spawner
void Spawner::spawn(Spawner spawner[], int x, int y, int w, int h) {
	for (int i = 0; i < 200; i++){
		if (!spawner[i].alive){
			if (index == 1){spawner[i].type = "asteroid";}
			spawner[i].x 			= x;
			spawner[i].y 			= y;
			spawner[i].w 			= w;
			spawner[i].h 			= h;
			spawner[i].spawnTimer 	= 0;
			spawner[i].spawned 		= 0;
			spawner[i].maxSpawn 	= 1;
			spawner[i].moused 		= false;
			spawner[i].alive 		= true;
			count++;
			break;
		}
	}
}

// Remove a spawner
void Spawner::remove(Spawner spawner[]) {
	for (int i = 0; i < 200; i++) {
		if (spawner[i].alive) {
			if (spawner[i].moused) {
				spawner[i].alive = false;
				count--;
			}
		}
	}
}

// Update Spawner
void Spawner::update(Spawner spawner[], Asteroid asteroid[], Asteroid &a_dummy, int targetX, int targetY, int mx, int my, int camx, int camy){
	for (int i = 0; i < 200; i++){
		if (spawner[i].alive)
		{
			// Mouse on Spawner
			if (mx > spawner[i].x && mx < spawner[i].x + spawner[i].w &&
				my > spawner[i].y && my < spawner[i].y + spawner[i].h) {
				spawner[i].moused = true;
			} else {
				spawner[i].moused = false;
			}

			// Update Asteroid
			if (spawner[i].type == "asteroid")
			{
				// Spawn Asteroid after x milliseconds
				spawner[i].spawnTimer += 1;
				if (spawner[i].spawnTimer > 60)
				{
					spawner[i].spawnTimer 	= 0;
					spawner[i].spawned 	   += 1;
		            int randAngle 			= fRandS(0.0, 360.0);
		            a_dummy.spawnAsteroidAngle(asteroid, spawner[i].x, spawner[i].y, spawner[i].w, spawner[i].h,
		    									 randAngle, 0.5);
				}

				// Destroy Spawner after max spawns has been reached
				if (spawner[i].spawned >= spawner[i].maxSpawn){
					spawner[i].alive = false;
					count--;
				}

				// Do animations
				if (spawner[i].spawnTimer >= 0 && spawner[i].spawnTimer < 10) {
					spawner[i].clipIndex = 0;
				}
				if (spawner[i].spawnTimer >= 10 && spawner[i].spawnTimer < 20) {
					spawner[i].clipIndex = 1;
				}
				if (spawner[i].spawnTimer >= 20 && spawner[i].spawnTimer <= 30) {
					spawner[i].clipIndex = 2;
				}
				if (spawner[i].spawnTimer >= 30 && spawner[i].spawnTimer < 40) {
					spawner[i].clipIndex = 1;
				}
				if (spawner[i].spawnTimer >= 40 && spawner[i].spawnTimer < 50) {
					spawner[i].clipIndex = 1;
				}
				if (spawner[i].spawnTimer >= 50 && spawner[i].spawnTimer <= 60) {
					spawner[i].clipIndex = 2;
				}
			}
		}
	}
}

// Render Spawner
void Spawner::render(Spawner spawner[], int camx, int camy, SDL_Renderer* gRenderer, LTexture &gSpawner, SDL_Rect cSpawner[]) {
	for (int i = 0; i < 200; i++) {
		if (spawner[i].alive) {
			gSpawner.render(gRenderer, spawner[i].x-camx, spawner[i].y-camy, spawner[i].w, spawner[i].h, &cSpawner[spawner[i].clipIndex]);
			/*SDL_Rect spawnerRect = { spawner[i].x-camx, spawner[i].y-camy, spawner[i].w, spawner[i].h};
			SDL_SetRenderDrawColor(gRenderer, 244, 144, 20, 255);
			SDL_RenderDrawRect(gRenderer, &spawnerRect);*/
		}
	}
}
