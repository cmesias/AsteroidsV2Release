/*
 * Mixed.h
 *
 *  Created on: Dec 19, 2016
 *      Author: Carl
 */

/* Functions that use multiple Classes */

#ifndef LOCAL_MIXED_H_
#define LOCAL_MIXED_H_

#include "Particless.h"
#include "Asteroids.h"
#include "Enemies.h"
#include "Spawners.h"
#include "Players.h"

class Mixed {
public:

	// Check collision between Particle & Asteroid
	void checkCollisionParticleAsteroid(Particle particle[], Asteroid asteroid[], Player &player, int PARTICLES);

	// Check collision between Particle & Enemy
	void checkCollisionParticleEnemy(Particle particle[], Enemy enemy[], Player &player, int PARTICLES);

	// Check collision between Particle & Player
	void checkCollisionParticlePlayer(Particle particle[], Player &player, int PARTICLES);

	// Spawn Asteroids upon destroying all Asteroids
	void spawnAsteroidsNow2(Spawner spawner[], Spawner &s_dummy,
							Enemy enemy[], Enemy &e_dummy,
							Asteroid asteroid[], Asteroid &a_dummy,
							Player &player,
							int mapX, int mapY, int mapW, int mapH);
};

#endif /* LOCAL_MIXED_H_ */
