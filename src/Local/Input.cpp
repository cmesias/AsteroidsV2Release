/*
 * Input.cpp
 *
 *  Created on: Dec 18, 2016
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
#include <sstream>
using namespace std;

#include "Input.h"



//Get's input from user and returns it
void Input::getInput( string &name, LWindow gWindow, SDL_Renderer* gRenderer,
					  SDL_Color color, LTexture gText, TTF_Font* gFont ){

	//Loop bool
	bool getInput = true;

	//Store user input in string
	string inputString = name.c_str();

	//Start getting input from user
	SDL_StartTextInput();

	string slash = "_";
	int timer;

	while (getInput) {

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				getInput = false;
			}

			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_BACKSPACE&& inputString.length() > 0) {
					inputString.pop_back();
				}
				else if (e.key.keysym.sym== SDLK_c&& SDL_GetModState() & KMOD_CTRL) {
					SDL_SetClipboardText(inputString.c_str());
				}
				else if (e.key.keysym.sym== SDLK_v&& SDL_GetModState() & KMOD_CTRL) {
					inputString = SDL_GetClipboardText();
				}
			}
			else if (e.type == SDL_TEXTINPUT) {
				if (!((e.text.text[0] == 'c' || e.text.text[0] == 'C')&& (e.text.text[0] == 'v' || e.text.text[0] == 'V')&& SDL_GetModState() & KMOD_CTRL)) {
					inputString += e.text.text;
				}
			}

			if (inputString.length() > 3){
				inputString.pop_back();
			}

			//Handle window events
			gWindow.handleEvent(e, gRenderer);

			//If Key Pressed
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					getInput 	= false;
					break;
				case SDLK_RETURN:
					getInput 	= false;
					name 		= inputString.c_str();
					break;
				}
			}
		}

		//Clear screen for render?
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gRenderer);

			//Render text input
			gText.loadFromRenderedText("Enter a desired name.", color, gFont, gRenderer);
			gText.render(gRenderer, gWindow.getWidth()/2-gText.getWidth()/2, gWindow.getHeight()/2-gText.getHeight()/2-33*2,gText.getWidth(), gText.getHeight());

			stringstream tempss;
				timer += 1;
				if (timer > 30){
					timer = 0;
					if (slash=="_"){
						slash = "";
					}else{
						slash = "_";
					}
				}
				tempss << inputString << slash;
				gText.loadFromRenderedText(tempss.str().c_str(), color, gFont, gRenderer);
			gText.render(gRenderer, gWindow.getWidth()/2-gText.getWidth()/2, gWindow.getHeight()/2-gText.getHeight()/2,gText.getWidth(), gText.getHeight());

		//Update screen
		SDL_RenderPresent(gRenderer);

	}
}


