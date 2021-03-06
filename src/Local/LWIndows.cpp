/*
 * LWIndows.cpp
 *
 *  Created on: Dec 16, 2016
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

#include "LWIndows.h"

LWindow::LWindow() {
	//Initialize non-existant window
	mWindow = NULL;
	mMouseFocus = false;
	mKeyboardFocus = false;
	mFullScreen = false;
	mMinimized = false;
	mWidth = 0;
	mHeight = 0;
}

bool LWindow::init(int SCREEN_WIDTH, int SCREEN_HEIGHT) {
	//Create window
	mWindow = SDL_CreateWindow("Adventures of Space Wars",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN ); // SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS);/// | SDL_WINDOW_MAXIMIZED);
	if (mWindow != NULL) {
		mMouseFocus = true;
		mKeyboardFocus = true;
		mWidth = SCREEN_WIDTH;
		mHeight = SCREEN_HEIGHT;
	}

	return mWindow != NULL;
}

SDL_Renderer* LWindow::createRenderer() {
	return SDL_CreateRenderer(mWindow, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void LWindow::handleEvent(SDL_Event& e, SDL_Renderer* gRenderer) {
	//Set window mode to borderless at all times
	//SDL_SetWindowBordered(gWindow.mWindow,SDL_FALSE);

	//Window event occuredw
	if (e.type == SDL_WINDOWEVENT) {
		//Caption update flag
		bool updateCaption = false;

		switch (e.window.event) {
		//Get new dimensions and repaint on winwdow size change
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			mWidth = e.window.data1;
			mHeight = e.window.data2;
			SDL_RenderPresent(gRenderer);
			break;

			//Repaint on exposurew
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(gRenderer);
			break;

			//Mouse entered window
		case SDL_WINDOWEVENT_ENTER:
			mMouseFocus = true;
			updateCaption = true;
			break;

			//Mouse left window
		case SDL_WINDOWEVENT_LEAVE:
			mMouseFocus = false;
			updateCaption = true;
			break;

			//Window has keyboard focus
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			mKeyboardFocus = true;
			updateCaption = true;
			break;

			//Window lost keyboard focus
		case SDL_WINDOWEVENT_FOCUS_LOST:
			mKeyboardFocus = false;
			updateCaption = true;
			break;

			//Window minimized
		case SDL_WINDOWEVENT_MINIMIZED:
			mMinimized = true;
			break;

			//Window maxized
		case SDL_WINDOWEVENT_MAXIMIZED:
			mMinimized = false;
			break;

			//Window restored
		case SDL_WINDOWEVENT_RESTORED:
			mMinimized = false;
			break;
		}

		//Update window caption with new data
		if (updateCaption) {
			std::stringstream caption;
			caption << "Asteroids - MouseFocus:"
					<< ((mMouseFocus) ? "On" : "Off") << " KeyboardFocus:"
					<< ((mKeyboardFocus) ? "On" : "Off");
			SDL_SetWindowTitle(mWindow, caption.str().c_str());
		}
	}
	//Enter exit full screen on return key
	//else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F11) {
		if (mFullScreen) {
			SDL_SetWindowFullscreen(mWindow, SDL_FALSE);
			mFullScreen = false;
		} else {
			SDL_SetWindowFullscreen(mWindow, SDL_TRUE);
			mFullScreen = true;
			mMinimized = false;
		}
	}
}

void LWindow::free() {
	if (mWindow != NULL) {
		SDL_DestroyWindow(mWindow);
	}

	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;
}

int LWindow::getWidth() {
	return mWidth;
}

int LWindow::getHeight() {
	return mHeight;
}

bool LWindow::hasMouseFocus() {
	return mMouseFocus;
}

bool LWindow::hasKeyboardFocus() {
	return mKeyboardFocus;
}

bool LWindow::isMinimized() {
	return mMinimized;
}
