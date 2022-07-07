/*
 * Mixed.cpp
 *
 *  Created on: Dec 19, 2016
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
using namespace std;

#include "Particless.h"
#include "Asteroids.h"
#include "Enemies.h"
#include "Players.h"
#include "Mixed.h"

// Check collision: Player Particle and Asteroid
void Mixed::checkCollisionParticleAsteroid(Particle particle[], Asteroid asteroid[], Player &player, int PARTICLES) {
	for (int i = 0; i < 1024; i++) {
		for (int j = 0; j < 128; j++) {
			if (particle[i].alive) {
				if (particle[i].type == "LAZER"){
					if (asteroid[j].alive){
						if (particle[i].x + particle[i].w > asteroid[j].x && particle[i].x < asteroid[j].x + asteroid[j].w
								&& particle[i].y + particle[i].h > asteroid[j].y
								&& particle[i].y < asteroid[j].y + asteroid[j].h) {
							particle[i].collide = true;
						} else {
							particle[i].collide = false;
						}
						if (particle[i].collide){
							particle[i].time = 0;
							particle[i].alive = false;
							PARTICLES--;

							asteroid[j].damaged = true;
							asteroid[j].health -= particle[i].damage;

							player.hits++;
						}
					}
				}
			}
		}
	}
}


// Check collision: Player Particle and Enemy
void Mixed::checkCollisionParticleEnemy(Particle particle[], Enemy enemy[], Player &player, int PARTICLES) {
	for (int i = 0; i < 1024; i++) {
		for (int j = 0; j < 8; j++) {
			if (particle[i].alive) {
				if (particle[i].type == "LAZER"){
					if (enemy[j].alive){
						if (particle[i].x + particle[i].w > enemy[j].x && particle[i].x < enemy[j].x + enemy[j].w
								&& particle[i].y + particle[i].h > enemy[j].y
								&& particle[i].y < enemy[j].y + enemy[j].h) {
							particle[i].collide = true;
						} else {
							particle[i].collide = false;
						}
						if (particle[i].collide){
							particle[i].time = 0;
							particle[i].alive = false;
							PARTICLES--;

							enemy[j].damaged = true;
							enemy[j].health -= particle[i].damage;

							player.hits++;
						}
					}
				}
			}
		}
	}
}

// Check collision: Enemy Particle and Player
void Mixed::checkCollisionParticlePlayer(Particle particle[], Player &player, int PARTICLES) {
	for (int i = 0; i < 1024; i++) {
		for (int j = 0; j < 128; j++) {
			if (particle[i].alive) {
				if (particle[i].type == "LAZER_E"){
					if (player.alive){
						if (particle[i].x + particle[i].w > player.x && particle[i].x < player.x + player.w
								&& particle[i].y + particle[i].h > player.y
								&& particle[i].y < player.y + player.h) {
							particle[i].collide = true;
						} else {
							particle[i].collide = false;
						}
						if (particle[i].collide){
							particle[i].time = 0;
							particle[i].alive = false;
							PARTICLES--;

							player.health -= particle[i].damage;
						}
					}
				}
			}
		}
	}
}

// Spawn an Asteroid using a Spawn Point
void Mixed::spawnAsteroidsNow2(Spawner spawner[], Spawner &s_spawn,
							   Enemy enemy[], Enemy &e_dummy,
							   Asteroid asteroid[], Asteroid &a_dummy,
							   Player &player,
							   int mapX, int mapY, int mapW, int mapH)
{
	// Spawn an enemy after X amount of scores
	if (e_dummy.mileScore > 1000 * (player.increment/2)){
		e_dummy.mileScore = 0;
		e_dummy.SPAWN_ENEMY = true;
		cout << "SPAWNED?" << endl;
	}

	// Spawn new wave of Enemies
	if (e_dummy.SPAWN_ENEMY){
		int randi, randw, randh;
			randi = rand() % 4 + 1;
			switch (randi){
				case 1:{
					//TODO - make Enemy X coordinate spawn more random
					for (int j=0; j<e_dummy.ENEMY_SPAWN; j++){
						randw = rand() % 5 + 1;
						randh = rand() % 656;
						e_dummy.spawn(enemy, mapX-64 - (64*randw), mapY+randh, 64, 32, 0.5, 0.0, 5);
						cout << "SPAWNED" << endl;
					}
					break;
				}
				case 2:{
					for (int j=0; j<e_dummy.ENEMY_SPAWN; j++){
						randw = rand() % 5 + 1;
						randh = rand() % 656;
						e_dummy.spawn(enemy, mapX-64 - (64*randw), mapY+randh, 64, 32, 0.5, 0.0, 5);
					}
					break;
				}
				case 3:{
					for (int j=0; j<e_dummy.ENEMY_SPAWN; j++){
						randw = rand() % 5 + 1;
						randh = rand() % 656;
						e_dummy.spawn(enemy, mapX+mapW + (64*randw), mapY+randh, 64, 32, -0.5, 0.0, 5);
					}
					break;
				}
				case 4:{
					for (int j=0; j<e_dummy.ENEMY_SPAWN; j++){
						randw = rand() % 5 + 1;
						randh = rand() % 656;
						e_dummy.spawn(enemy, mapX+mapW + (64*randw), mapY+randh, 64, 32, -0.5, 0.0, 5);
					}
					break;
				}
			}

		// Increase enemy count
		if (e_dummy.ENEMY_SPAWN < 5){
			e_dummy.ENEMY_SPAWN++;
		}

		// Stop spawning Enemies
		e_dummy.SPAWN_ENEMY 	= false;
	}

	// Check if there is 0 Asteroids
	if (a_dummy.asteroidsClear){
		if (a_dummy.ASTEROIDS <= 0){
			a_dummy.asteroidsClear = false;
			player.increment += rand() % 2 + 1;
			player.wave++;

			for (int i=0; i<1+player.increment; i++){
				int randVar 	= rand() % 3 + 1;
				int randx 		= rand() % 1248;
				int randy 		= rand() % 688;
				int randw 		= 4;
				int randh 		= 4;
				switch (randVar){
					case 1:
						randw = 48;
						randh = 48;
					break;
					case 2:
						randw = 96;
						randh = 96;
					break;
					case 3:
						randw = 128;
						randh = 128;
					break;
				}
				randx = rand() % 1248;
				randy = rand() % 688;
				s_spawn.spawn(spawner, 0+randx, 0+randy, randw, randh);
			}

			// Give Player a 180 ms shield
			player.shield			= true;
			player.shieldT			= 180;
		}
	}

	// Start checking for no Asteroids, once we've spawned an Asteroid
	if (a_dummy.ASTEROIDS > 0){
		a_dummy.asteroidsClear = true;
	}
}
