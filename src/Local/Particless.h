/*
 * Particless.h
 *
 *  Created on: Dec 16, 2016
 *      Author: Carl
 */



#ifndef LOCAL_PARTICLESS_H_
#define LOCAL_PARTICLESS_H_

#include "LTextures.h"

class Particle {
public:
	float x, y;
	float w, h;
	int alpha;
	int alphaspeed;
	int time;
	int deathTimer;
	int deathTimerSpeed;
	float angle;
	double vX, vY;
	double speed;
	double angleSpe, angleDir;
	bool onScreen;
	bool alive;
	bool collide;
	string side;
	string type;
	int damage;
	SDL_Color color;
	int layer;

	int PARTICLES = 0;
	LTexture gParticles;					// Particle Textures
	SDL_Rect cParticles[ 6 ];				// [0: Blue], [1: Green], [2: Orange], [3: Red], [4: White], [5: Yellow] Particle

	bool sizeDeath;
	float deathSpe;

	void loadTexture(SDL_Renderer* gRenderer);
	void freeTexture();
	void setClips(SDL_Rect &tempRect, int x, int y, int w, int h);
	void initParticle(Particle particle[]);
	void spawnParticleAngle(Particle particle[],
			int playerx, int playery,
			int w, int h,
			double angle, double speed,
			int alpha, int alphaspeed,
			int deathTimer, int deathTimerSpeed,
			double damage, string type,
			SDL_Color color, int layer,
			int angleSpe, int angleDir,
			bool sizeDeath, float deathSpe);
	void fireParticle(Particle particle[], int damage, string type,
										   int spawnx, int spawny, int w, int h,
										   double speed, float vX, float vY,
										   int alphaspeed, int alpha,
										   int deathTimer, int deathTimerSpeed, double angle, double angleSpe, double angleDir,
										   SDL_Color color, int layer);

	void spawnStars(Particle particle[], int x, int y, float w, float h, int alphaspeed, int alpha, int camx, int camy, SDL_Color color, int layer);
	void fireParticle2(Particle particle[], int damage, int spawnx, int spawny, int w, int h, int targetx,int targety,
											int alphaspeed, int alpha,
											int deathTimer, int deathTimerSpeed,
											double speed, string type,
											SDL_Color color, int layer);
	void updateParticles(Particle particle[], int mapX, int mapY, int mapW, int mapH);
	void renderParticle(Particle particle[], int camX, int camY, float playerZ, SDL_Renderer* gRenderer);

};

#endif /* LOCAL_PARTICLESS_H_ */
