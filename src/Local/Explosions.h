/*
 * Explosions.h
 *
 *  Created on: Dec 18, 2016
 *      Author: Carl
 */

#ifndef LOCAL_EXPLOSIONS_H_
#define LOCAL_EXPLOSIONS_H_

#include "LTextures.h"

class Explosion {
public:
	int x,
		y,
		w,
		h;
	int animTimer;
	int animFrame;
	int alpha;
	bool alive;
	string type;
	int EXPLOSION_COUNT 		= 0;		// Current number of explosions
	const int EXPLOSION_MAX 	= 100;		// Max number of explosions
	LTexture gExplosion;					// Explosion Textures
	LTexture gExplosionBlue;				// Explosion Textures
	SDL_Rect rExplosion[6];					// Explosion Texture clips
	SDL_Rect rExplosionBlue[6];				// Explosion Texture blue clips

	void loadResources(SDL_Renderer* gRenderer);

	void freeResources();

	void setClips(SDL_Rect &tempRect, int x, int y, int w, int h);

	void init(Explosion explosion[]);

	void spawn(Explosion explosion[], int x, int y, int w, int h, int alpha, string type, Mix_Chunk *sAtariBoom);

	void update(Explosion explosion[], int mode);

	void render(Explosion explosion[], int camX, int camY, SDL_Renderer* gRenderer);
};

#endif /* LOCAL_EXPLOSIONS_H_ */
