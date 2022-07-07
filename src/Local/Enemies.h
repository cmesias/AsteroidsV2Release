/*
 * Enemies.h
 *
 *  Created on: Dec 18, 2016
 *      Author: Carl
 */

#ifndef LOCAL_ENEMIES_H_
#define LOCAL_ENEMIES_H_

#include "LTextures.h"
#include "Particless.h"
#include "Explosions.h"

class Enemy {
public:
	float x, y;
	int w, h;
	int timer;
	float vX, vY, speed;
	int health;
	int damagedTimer;
	bool damaged;
	bool collide;
	bool alive;

	const int Max 		= 8;		// Max number of Enemies
	int ENEMY_COUNT 	= 0;		// Current number of Enemies
	int ENEMY_SPAWN 	= 1;		// Max amount of enemies that can be spawned at the same time
	int mileScore		= 0; 		// Every 1000 score, spawn an enemy
	bool SPAWN_ENEMY	= false;	// Every accumulated 1000 score from the Player, we spawn an Enemy

	// Texture
	LTexture gEnemyShip;

	// Colors
	SDL_Color black = { 0, 0, 0, 0 };
	SDL_Color red = { 255, 99, 71, 255 };
	SDL_Color green = { 0, 255, 0, 255 };
	SDL_Color blue = { 100, 149, 237, 255 };
	SDL_Color orange = { 255, 144, 20, 255 };
	SDL_Color white = { 255, 255, 255, 255 };

	void loadResources(SDL_Renderer* gRenderer);

	void freeResources();

	void init(Enemy enemy[]);

	void spawn(Enemy enemy[], float x, float y, int w, int h, double vX, double vY, double speed);

	void update(Enemy enemy[],
			Particle particle[], Particle &p_dummy,
			Explosion explosion[], Explosion &e_dummy,
			float targetX, float targetY, int objectRadius,
			unsigned int &score, int mapX, int mapY, int mapW, int mapH,
			Mix_Chunk *sLazer, Mix_Chunk *sAtariBoom);

	void render(Enemy enemy[], int camx, int camy, SDL_Renderer* gRenderer);


};

#endif /* LOCAL_ENEMIES_H_ */
