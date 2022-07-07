/*
 * Input.h
 *
 *  Created on: Dec 18, 2016
 *      Author: Carl
 */

#ifndef LOCAL_INPUT_H_
#define LOCAL_INPUT_H_

#include "LWIndows.h"
#include "LTextures.h"

class Input {
public:
	void getInput(string &name, LWindow gWindow, SDL_Renderer* gRenderer,
				  SDL_Color color, LTexture gText, TTF_Font* gFont);
};

#endif /* LOCAL_INPUT_H_ */
