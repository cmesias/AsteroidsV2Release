/*
 * Asteroids.h
 *
 *  Created on: Dec 18, 2016
 *      Author: Carl
 */

#ifndef LOCAL_ASTEROIDS_H_
#define LOCAL_ASTEROIDS_H_


#include "LTextures.h"
#include "Particless.h"
#include "Explosions.h"

class Asteroid {
public:
	float x,y,w,h;
	float angle;
	int angleSpe, angleDir;
	float vX,vY;
	float speed;
	bool alive;
	bool collision;
	bool MouseOnAsteroid;
	bool onScreen;
	string type;
	int health;
	bool damaged; 		//Asteroid is damaged
	int damagedTimer;	//Asteroid damaged animation timer
	int ASTEROIDS 	= 0;
	bool asteroidsClear	= true;

	// Texture
	LTexture gAsteroid;
	SDL_Rect rAsteroid[3];

	void loadResources(SDL_Renderer* gRenderer);

	void freeResources();

	void initAsteroid(Asteroid asteroid[]);

	void spawnAsteroidAngle(Asteroid asteroid[],
			int x, int y,
			int w, int h,
			double angle, double speed);

	void spawnAsteroid(Asteroid asteroid[], int spawnx, int spawny, int w, int h, int targetx,int targety, float speed, string type);

	void configAsteroid(Asteroid asteroid[], int command, int mx, int my);

	void copyAsteroidOnMouse(Asteroid asteroid[], int &BLOCKX, int &BLOCKY, int &BLOCKW, int &BLOCKH);

	void updateAsteroid(Asteroid asteroid[],
						Explosion explosion[], Explosion &g_dummy0,
						Particle particle[], Particle &p_dummy,
						bool alive, bool shield,
						unsigned int &score, int &mileScore, int visionX, int visionY, int objectRadius,
						int &health, int mx, int my, int camx, int camy,
						int screenWidth, int screenHeight,
						int mapX, int mapY, int mapW, int mapH,
						Mix_Chunk *sAtariBoom);

	void renderAsteroid(Asteroid asteroid[], int camx, int camy, SDL_Renderer* gRenderer);
};

#endif /* LOCAL_ASTEROIDS_H_ */
