/*
 * Settings.h
 *
 *  Created on: Dec 19, 2016
 *      Author: Carl
 */

#ifndef LOCAL_SETTINGS_H_
#define LOCAL_SETTINGS_H_

#include "LWIndows.h"
#include "LTextures.h"

class Settings {
public:
	LTexture gControls;

	void Menu( bool &quit,
			Mix_Chunk *sLazer,
			Mix_Chunk *sAtariBoom,
			int &sfxVolume,
			int &musicVolume,
			LWindow gWindow, SDL_Renderer* gRenderer,
			SDL_Color color, TTF_Font* gFont, LTexture gText );
};


#endif /* LOCAL_SETTINGS_H_ */
