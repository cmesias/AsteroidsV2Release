/*
 * Settings.cpp
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
#include <sstream>
using namespace std;


#include "Settings.h"

//Get's input from user and returns it
void Settings::Menu( bool &quit, Mix_Chunk *sLazer, Mix_Chunk *sAtariBoom, int &sfxVolume, int &musicVolume, LWindow gWindow, SDL_Renderer* gRenderer, SDL_Color color, TTF_Font* gFont, LTexture gText ){

	gControls.loadFromFile("img/controls.png", gRenderer);

	// Loop
	bool loop = true;

	// Handles events
	SDL_Event e;

	// Selection menu
	string t[5];
	t[0] = "Continue";
	t[1] = "Quit";
	/*t[1] = "Video";
	t[2] = "Audio";
	t[3] = "How To Play";
	t[4] = "Quit";*/

	// Selection menu
	string a[3];
	stringstream tempsssss;
	stringstream tempis;
	tempsssss << "Music Volume: " 		  << musicVolume;
	tempis    << "Sound Effects Volume: " << sfxVolume;
	a[0] = tempsssss.str();
	a[1] = tempis.str();
	a[2] = "back";

	// Menu types
	int type = 0; // 0: Main menu, 1: Video, 2: Audio

	// Index
	int indx = 0;

	// Buttons
	bool leftKey = false,
		 rightKey = false;

	while (loop) {

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
				loop = false;
			}

			//Handle window events
			gWindow.handleEvent(e, gRenderer);

			//If Key Pressed
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
				switch (e.key.keysym.sym) {
					case SDLK_UP:
						if (indx > 0){
							indx--;
						}
						break;
					case SDLK_DOWN:
						if (type==0){
							if (indx < 1){
								indx++;
							}
						}
						if (type==2){
							if (indx < 2){
								indx++;
							}
						}
						break;
					case SDLK_w:
						if (indx > 0){
							indx--;
						}
						break;
					case SDLK_s:
						if (indx < 1){
							indx++;
						}
						if (type==2){
							if (indx < 2){
								indx++;
							}
						}
						break;
					case SDLK_RETURN:
						// Menu options
						if (type==0)
						{
							// Continue game, close menu
							if (indx==0){
								loop = false;
							}

							// Quit
							if (indx==1){
								//type = 1;
								quit = true;
								loop = false;
							}

							/*// Enter Audio settings
							if (indx==2){
								type = 2;
								indx = 0;
							}

							// Show "How To Play" screen
							if (indx==3){
								type = 3;
								indx = 0;
							}

							// Quit
							if (indx==4){
								quit = true;
								loop = false;
							}*/
						}

						// Audio options
						if (type==2)
						{
							// Play SFX
							if (indx==1){
								int randi = rand() % 2 + 1;
								if (randi==1){
									Mix_PlayChannel(-1, sLazer, 0);
								}else{
									Mix_PlayChannel(-1, sAtariBoom, 0);
								}
							}

							// back
							if (indx==2){
								type = 0;
								indx = 0;
							}
						}
						break;
					case SDLK_LEFT:
						leftKey = true;
						break;

					case SDLK_RIGHT:
						rightKey = true;
						break;
					case SDLK_ESCAPE:
						if (type==0)
						{
							loop = false;
						}
						if (type==2 || type==3)
						{
							type = 0;
							indx = 0;
						}
						break;
				}
			}
			//If Key Released
			else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
				switch (e.key.keysym.sym) {
					case SDLK_LEFT:{
						leftKey = false;

						// Audio Menu, Play SFX
						if (type==2 && indx==1){
							int randi = rand() % 2 + 1;
							if (randi==1){
								Mix_PlayChannel(-1, sLazer, 0);
							}else{
								Mix_PlayChannel(-1, sAtariBoom, 0);
							}
						}
						break;
					}
					case SDLK_RIGHT:{
						rightKey = false;

						// Audio Menu, Play SFX
						if (type==2 && indx==1){
							int randii = rand() % 2 + 1;
							if (randii==1){
								Mix_PlayChannel(-1, sLazer, 0);
							}else{
								Mix_PlayChannel(-1, sAtariBoom, 0);
							}
						}
						break;
					}
				}
			}

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (e.button.button == SDL_BUTTON_LEFT) {
					//leftclick = true;
				}
			}

			if (e.type == SDL_MOUSEBUTTONUP) {
				if (e.button.button == SDL_BUTTON_LEFT) {
					//leftclick = false;
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (e.button.button == SDL_BUTTON_RIGHT) {
				}
			}
		} // end controls

		// Left arrow key pressed
		if (leftKey)
		{
			// Audio Menu
			if (type==2)
			{
				// Music Volume
				if (indx==0){
					if (musicVolume > 0){
						musicVolume--;
						stringstream tempis;
						tempis << "Music Volume: " << musicVolume;
						a[0] = tempis.str().c_str();
						Mix_VolumeMusic(musicVolume);
					}
				}

				// SFX Volume
				if (indx==1){
					if (sfxVolume > 0){
						sfxVolume--;
						stringstream tempis;
						tempis << "Sound Effects Volume: " << sfxVolume;
						a[1] = tempis.str().c_str();
						Mix_VolumeChunk(sLazer, sfxVolume);
						Mix_VolumeChunk(sAtariBoom, sfxVolume);
					}
				}
			}
		}

		// Right arrow key pressed
		if (rightKey)
		{
			// Audio Menu
			if (type==2)
			{
				// Music Volume
				if (indx==0){
					if (musicVolume < 128){
						musicVolume++;
						stringstream tempis;
						tempis << "Music Volume: " << musicVolume;
						a[0] = tempis.str().c_str();
						Mix_VolumeMusic(musicVolume);
					}
				}

				// SFX Volume
				if (indx==1){
					if (sfxVolume < 128){
						sfxVolume++;
						stringstream tempis;
						tempis << "Sound Effects Volume: " << sfxVolume;
						a[1] = tempis.str().c_str();
						Mix_VolumeChunk(sLazer, sfxVolume);
						Mix_VolumeChunk(sAtariBoom, sfxVolume);
					}
				}
			}
		}

		//Clear screen for render?
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gRenderer);

			// Render text input
			stringstream tempss;
			tempss.str(std::string());
			tempss << "Press 'P' to enable/disable background Stars and save performance.";
			gText.loadFromRenderedText(tempss.str().c_str(), {100, 200, 200}, gFont, gRenderer);
			gText.render(gRenderer, 32, 32,gText.getWidth(), gText.getHeight());
			/*tempss.str(std::string());
			tempss << "Index: " << indx;
			gText.loadFromRenderedText(tempss.str().c_str(), color, gFont, gRenderer);
			gText.render(gRenderer, gWindow.getWidth()/2-gText.getWidth()/2, gWindow.getHeight()/2-gText.getHeight()/2-50,
									gText.getWidth(), gText.getHeight());*/

			// Render Menu options
			if (type==0){
				/*for (int i=0; i<5; i++){
					if (indx==i){
						tempss.str(std::string());
						tempss << t[i];
						gText.loadFromRenderedText(tempss.str().c_str(), {255, 144, 20}, gFont, gRenderer);
						gText.render(gRenderer, 75+7, 75*3 + i * 27,gText.getWidth(), gText.getHeight());
					}else{
						tempss.str(std::string());
						tempss << t[i];
						gText.loadFromRenderedText(tempss.str().c_str(), color, gFont, gRenderer);
						gText.render(gRenderer, 75, 75*3 + i * 27,gText.getWidth(), gText.getHeight());
					}
				}*/
				for (int i=0; i<2; i++){
					if (indx==i){
						tempss.str(std::string());
						tempss << t[i];
						gText.loadFromRenderedText(tempss.str().c_str(), {255, 144, 20}, gFont, gRenderer);
						gText.render(gRenderer, 75+7, 75*3 + i * 27,gText.getWidth(), gText.getHeight());
					}else{
						tempss.str(std::string());
						tempss << t[i];
						gText.loadFromRenderedText(tempss.str().c_str(), color, gFont, gRenderer);
						gText.render(gRenderer, 75, 75*3 + i * 27,gText.getWidth(), gText.getHeight());
					}
				}
			}

			// Render Video options
			if (type==1){

			}

			// Render Audio options
			if (type==2){
				for (int i=0; i<3; i++){
					if (indx==i){
						tempss.str(std::string());
						tempss << a[i];
						gText.loadFromRenderedText(tempss.str().c_str(), {255, 144, 20}, gFont, gRenderer);
						gText.render(gRenderer, 75, 75*3 + i * 27,gText.getWidth(), gText.getHeight());
					}else{
						tempss.str(std::string());
						tempss << a[i];
						gText.loadFromRenderedText(tempss.str().c_str(), color, gFont, gRenderer);
						gText.render(gRenderer, 75, 75*3 + i * 27,gText.getWidth(), gText.getHeight());
					}
				}
			}

			// Render How To Play options
			if (type==3){
				gControls.render(gRenderer, 0, 0, gControls.getWidth(), gControls.getHeight());
			}

		//Update screen
		SDL_RenderPresent(gRenderer);

	}
	gControls.free();
}

