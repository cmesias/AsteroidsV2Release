/*
 * Spawners.h
 *
 *  Created on: Dec 18, 2016
 *      Author: Carl
 */

#ifndef LOCAL_SPAWNERS_H_
#define LOCAL_SPAWNERS_H_

#include "Asteroids.h"

class Spawner {
public:
	int x,y,w,h;
	int spawnTimer;
	int spawned;
	int maxSpawn;
	bool alive;
	bool moused;
	string type;

	int count = 0;
	int index = 1;

	// clips
	int clipIndex;

	// Initialize Spawner
	void init(Spawner spawner[]);

	// Spawn a Spawner
	void spawn(Spawner spawner[], int x, int y, int w, int h);

	// Remove Spawner
	void remove(Spawner spawner[]);

	// Update Spawner
	void update(Spawner spawner[], Asteroid asteroid[], Asteroid &a, int targetX, int targetY, int mx, int my, int camx, int camy);

	// Render Spawner
	void render(Spawner spawner[], int camx, int camy, SDL_Renderer* gRenderer, LTexture &gSpawner, SDL_Rect cSpawner[]);
};

#endif /* LOCAL_SPAWNERS_H_ */
