/*
 * LWIndows.h
 *
 *  Created on: Dec 16, 2016
 *      Author: Carl
 */

#ifndef LWINDOWS_H_
#define LWINDOWS_H_

class LWindow {
public:
	//Intializes internals
	LWindow();

	//Creates window
	bool init(int SCREEN_WIDTH, int SCREEN_HEIGHT);

	//Creates renderer from internal window
	SDL_Renderer* createRenderer();

	//Handles window events
	void handleEvent(SDL_Event& e, SDL_Renderer* gRenderer);

	//Deallocates internals
	void free();

	//Window dimensions
	int getWidth();
	int getHeight();

	//Window focii
	bool hasMouseFocus();
	bool hasKeyboardFocus();
	bool isMinimized();

	//Window data
	SDL_Window* mWindow;

private:

	//Window dimensions
	int mWidth;
	int mHeight;

	//Window focus
	bool mMouseFocus;
	bool mKeyboardFocus;
	bool mFullScreen;
	bool mMinimized;
};

#endif /* LWINDOWS_H_ */
