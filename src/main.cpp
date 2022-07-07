#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <time.h>       /* time */
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream, std::stringbuf
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <math.h>       /* atan2 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mouse.h>

using namespace std;

#include "Local/LTextures.h"
#include "Local/LWindows.h"
#include "Local/Timers.h"
#include "init.h"

//Map size
class Map {
public:
	int x = 0;
	int y = 0;
	int w = 1280;
	int h = 720;

	// Render map
	void render(int camx, int camy){
		SDL_Rect MapRect = { this->x-camx, this->y-camy, this->w, this->h };
		SDL_SetRenderDrawColor(gRenderer12, 255, 255, 255, 255);
		SDL_RenderDrawRect(gRenderer12, &MapRect);
	}
}map;

#include "Local/Particless.h"
#include "Local/Explosions.h"
#include "Local/Enemies.h"
#include "Local/Asteroids.h"
#include "Local/Spawners.h"
#include "Local/Input.h"
#include "Local/Settings.h"
#include "Local/Players.h"
#include "Local/Mixed.h"

//TODO [x] - get name of player
//TODO [ ] - after player death, send name and score to server for storing leader boards


int main(int argc, char **argv)
{
	// Initialize SDL
	init();
	SDL_ShowCursor(false);

	// Load SDL media
	loadMedia();

	// Make random actually random
	srand(time(0));

	// Handles events
	SDL_Event e;

	// Basic world variables
	bool quit = false;
	float camx = 0,
		  camy = 0;
	int mx, my;
	int mouseWheelY;
	int HW 	   		= 0;

	// Class instance
	Particle part;
	Explosion explosions;
	Enemy enem;
	Asteroid aste;
	Spawner spaw;
	Input input;
	Settings settings;
	Player player;
	Mixed mix;

	// Class instance, multiple
	static Particle particle[1024];
	static Explosion explosion[100];
	static Asteroid asteroid[128];
	static Enemy enemy[8];
	static Spawner spawner[200];

	// Class initialization
	part.loadTexture(gRenderer12);
	part.initParticle(particle);
	explosions.loadResources(gRenderer12);
	explosions.init(explosion);
	aste.loadResources(gRenderer12);
	aste.initAsteroid(asteroid);
	enem.loadResources(gRenderer12);
	enem.init(enemy);
	spaw.init(spawner);

	// Player initialization
	player.loadResources(gRenderer12);
	player.init(map.x+map.w/2-player.w/2, map.y+map.h/2-player.h/2);
	player.algo();
	player.updateScore();

	//Particles
	int ptimer = 0;

    //Keep track of the current frame
	int frame = 0;
    bool cap = true;
    Timer fps;

    // World volume
	Mix_FadeInMusic(sAmbientMusic, -1, 0);
	Mix_VolumeMusic(musicVolume);

	// Test area
	bool enableSpaceParticles = true;
	int frameTest = 0;
	double frameTimer = 0.0;

	while (!quit)
	{
        //Start the frame timer
        fps.start();

        // Test area
        frameTimer += 1;
        if (frameTimer > 4) {
        	frameTimer = 0;
        	frameTest++;
        	if (frameTest > 104) {
        		frameTest = 1;
        	}
        }

    	//Center camera
        if (player.camlocked){
            camx = player.x + player.w/2 - gWindow.getWidth()/2;
            camy = player.y + player.h/2 - gWindow.getHeight()/2;
        }else{
            camx = map.x + map.w/2 - gWindow.getWidth()/2;
            camy = map.y + map.h/2 - gWindow.getHeight()/2;
        }


		//Get mouse X, and Y position and store it on mx, and my
		SDL_GetMouseState(&mx, &my);
		BLOCKX = mx+camx;
		BLOCKY = my+camy;

		if (debug){
			player.mode = "editor";
		}
		if (!debug){
			player.mode = "player";
		}

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			//Handle window events
			gWindow.handleEvent(e, gRenderer12);

			//If Key Pressed
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
				switch (e.key.keysym.sym) {
				case SDLK_a:
					//player.moveleft = true;
					player.rotateLeft = true;
					break;
				case SDLK_d:
					//player.moveright = true;
					player.rotateRight = true;
					break;
				case SDLK_w:
					player.thrust = true;
					break;
				case SDLK_t:
					if (player.travelMode == "travel"){
						player.travelMode = "fight";
					}else{player.travelMode = "travel";}
					break;
				case SDLK_y:
					player.camlocked = ( !player.camlocked );
					break;
				case SDLK_ESCAPE:
					settings.Menu( quit, sLazer, sAtariBoom, sfxVolume, musicVolume,
								   gWindow, gRenderer12, white, gFont26, gText);
					break;
				case SDLK_SPACE:
					player.initialshot = true;
					break;
				case SDLK_p:
					if (enableSpaceParticles) {
						enableSpaceParticles = false;
					}else{
						enableSpaceParticles = true;
					}
					break;
				}
			}
			//If Key Released
			else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
				switch (e.key.keysym.sym) {
				case SDLK_a:
					player.rotateLeft = false;
					break;
				case SDLK_d:
					player.rotateRight = false;
					break;
				case SDLK_w:
					player.thrust = false;
					break;
				case SDLK_LSHIFT:
					player.shift = false;
					break;
				case SDLK_SPACE:
					player.initialshot = false;
					break;
				}
			}

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (e.button.button == SDL_BUTTON_LEFT) {
					leftclick = true;
					//player.initialshot = true;
				}
			}

			if (e.type == SDL_MOUSEBUTTONUP) {
				if (e.button.button == SDL_BUTTON_LEFT) {
					leftclick = false;
					//player.initialshot = false;
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (e.button.button == SDL_BUTTON_RIGHT) {
					//
				}
			}
		} // end controls

		// Start timer to spawn our "stars"
		if (enableSpaceParticles) {
			ptimer += 1;
			if (ptimer > 10){
				ptimer = 0;
				for (int i=0; i<100; i++){
					int randAlpha = rand() % 100+150;
					int cW = gWindow.getWidth() + 200;
					int cH = gWindow.getHeight() + 200;
					int randW = rand() % cW;
					int randH = rand() % cH;
					SDL_Color tempColor = { rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1};
					int randl = rand() % 5 + 5;
					int randw = rand() % 2 + 2;

					part.fireParticle(particle, 0, "stars",
											0-100 + randW, 0-100 + randH,
											10/randl, 10/randl,
											0,
											0.0,0.0, 1, randAlpha,
											100, 1, 0.0, 0.0, 0.0,
											tempColor, randl);
				}
			}
		}

		// Update explosions
		explosions.update(explosion, 1);

		// Update Particles
		part.updateParticles(particle, map.x, map.y, map.w, map.h);

		// Update Asteroids
		aste.updateAsteroid(asteroid, explosion, explosions, particle, part, player.alive, player.shield, player.score, enem.mileScore,
												 player.x+player.w/2, player.y+player.h/2, player.w/2,
												 player.health, mx+camx, my+camy, camx, camy, gWindow.getWidth(), gWindow.getHeight(),
												 map.x, map.y, map.w, map.h,
												 sAtariBoom);

		// Update Player Particle & Asteroid collision check
		mix.checkCollisionParticleAsteroid(particle, asteroid, player, part.PARTICLES);

		// Update Player Particle & Enemy collision check
		mix.checkCollisionParticleEnemy(particle, enemy, player, part.PARTICLES);

		// Update Enemy Particle & Player collision check
		mix.checkCollisionParticlePlayer(particle, player, part.PARTICLES);

		// Update Spawner: spawns an Asteroid
		spaw.update(spawner, asteroid, aste, player.x+player.w/2, player.y+player.h/2, mx+camx, my+camy, camx, camy);

		// Update Player
		player.update(gWindow.getWidth(), gWindow.getHeight(), asteroid, aste,
					  enemy, enem,
					  particle, part,
					  explosion, explosions,
					  player.highscore, HW, mx, my, leftclick,
					  map.x+map.w/2-player.w/2, map.y+map.h/2-player.h/2,
					  map.x, map.y, map.w, map.h,
					  gWindow, input, gRenderer12,
					  gText, gFont26, white,
					  sLazer, sAtariBoom);
		//player.updateAlgo();

		// Update Enemy
		enem.update(enemy,
					particle, part,
					explosion, explosions,
					player.x+player.w/2, player.y+player.h/2, player.w/2,
					player.score, map.x, map.y, map.w, map.h,
					sLazer, sAtariBoom);

		// Update Asteroids: Wave re-spawn
		mix.spawnAsteroidsNow2(spawner, spaw, enemy, enem, asteroid, aste, player, map.x, map.y, map.w, map.h);

		// Clear Screen
		SDL_SetRenderDrawColor(gRenderer12, 10, 0, 10, 255);
		SDL_RenderClear(gRenderer12);

			// Render background
			if (player.bg==1){
				gBG.render(gRenderer12, 0-1000-camx/7,0-490-camy/7, gBG.getWidth(), gBG.getHeight());
			}else if (player.bg==2){
				gBG.render(gRenderer12, 0-2000-camx/7,0-1400-camy/7, gBG.getWidth(), gBG.getHeight());
			}

			// Render particles (some particles are used as actual bullets)
			part.renderParticle(particle, camx, camy, 1, gRenderer12);

			// Render Colonies that spawn Enemies
			explosions.render(explosion, camx, camy, gRenderer12);

			// Render Asteroid
			aste.renderAsteroid(asteroid, camx, camy, gRenderer12);

			// Render Colonies that spawn Asteroids
			spaw.render(spawner, camx, camy, gRenderer12, gSpawner, &cSpawner[0]);

			// Render Enemies
			enem.render(enemy, camx, camy, gRenderer12);

			// Render our player
			player.render(gWindow.getWidth(), gWindow.getHeight(), camx, camy, gRenderer12, gFont13, gFont26, white);

			// Render border animations
			gBorder[frameTest].render(gRenderer12, 0-camx, 0-180-camy, 1280, 720/2);
			gBorder[frameTest].render(gRenderer12, 0-camx, 360+180-camy, 1280, 720/2);
			gBorder[frameTest].render(gRenderer12, 0-360-camx, 0+180-camy, 720, 720/2, NULL, 90);
			gBorder[frameTest].render(gRenderer12, 640+280-camx, 0+180-camy, 720, 720/2, NULL, 90);

			// Render map
			//map.render(camx, camy);
			std::stringstream tempsi;

			tempsi.str( std::string() );
			tempsi << "Highest Score: " << player.highscore;
			gText.loadFromRenderedText(tempsi.str().c_str(), orange, gFont26, gRenderer12);
			gText.render(gRenderer12, gWindow.getWidth()-gText.getWidth()-15, 5, gText.getWidth(), gText.getHeight());

			// TODO - FIX so it is changed real time
			tempsi.str( std::string() );
			tempsi << "Score: " << player.score;
			gText.loadFromRenderedText(tempsi.str().c_str(), white, gFont26, gRenderer12);
			gText.render(gRenderer12, gWindow.getWidth()-gText.getWidth()-15, 31, gText.getWidth(), gText.getHeight());

			tempsi.str( std::string() );
			tempsi << "Health: " << player.health;
			gText.loadFromRenderedText(tempsi.str().c_str(), green, gFont26, gRenderer12);
			gText.render(gRenderer12, gWindow.getWidth()-gText.getWidth()-15, 58, gText.getWidth(), gText.getHeight());

			// Hide Cursor
			// SDL_ShowCursor(0);

		// Update screem
		SDL_RenderPresent(gRenderer12);

		// Increment the frame counter
		frame++;

		// If we want to cap the frame rate
		if( ( cap == true ) && ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) )
		{
			// Sleep the remaining frame time
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
		}
	}
	close();			// Free resources and close SDL
	part.freeTexture();
	explosions.freeResources();
	enem.freeResources();
	aste.freeResources();;
	player.freeResources();
	return 0;
}
