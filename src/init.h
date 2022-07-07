/* Make stuff here */

// Variables
int SCREEN_WIDTH = 1270;
int SCREEN_HEIGHT = 720;
int BLOCKCOUNT = 0;
bool debug = false;
bool leftclick = false;
int PLACING_TYPE = -1;
int HOWMANYBLOCKSW = 1;
int HOWMANYBLOCKSH = 1;
int BLOCKX;
int BLOCKY;
int BLOCKW = 32;
int BLOCKH = 32;
const int FRAMES_PER_SECOND = 60;
#define PI 3.14159265

// Window for rendering, The window renderer
LWindow gWindow;
SDL_Renderer* gRenderer12 = NULL;

// Textures
LTexture gText;
LTexture gBG;
LTexture gVisionRadius;
LTexture gBullet;
LTexture gSpawner;
LTexture gBorder[105];

// Audio
Mix_Chunk *sLazer 			= NULL;
Mix_Chunk *sAtariBoom 		= NULL;
Mix_Music *sAmbientMusic 	= NULL;
int sfxVolume				= 128;
int musicVolume 			= 50;

// Fonts
TTF_Font *gFont 			= NULL;
TTF_Font *gFont13 			= NULL;
TTF_Font *gFont26 			= NULL;

// Colors
SDL_Color black = { 0, 0, 0, 0 };
SDL_Color red = { 255, 99, 71, 255 };
SDL_Color green = { 0, 255, 0, 255 };
SDL_Color blue = { 100, 149, 237, 255 };
SDL_Color orange = { 255, 144, 20, 255 };
SDL_Color white = { 255, 255, 255, 255 };

// Clips
SDL_Rect cSpawner[3];

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

// Initialize SDL
bool init()
{
	//Initialization flag
	bool success = true;

	// Create splits
	cSpawner[0] = {0,0,32,32};
	cSpawner[1] = {32,0,32,32};
	cSpawner[2] = {64,0,32,32};

	//Initialize SDL
	if (SDL_Init( SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	} else {
		//Set texture filtering to linear
		SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0");

		//Create window
		gWindow.init(SCREEN_WIDTH, SCREEN_HEIGHT);

		//Create window
		gRenderer12 = gWindow.createRenderer();

		//Initialize renderer color
		SDL_SetRenderDrawColor(gRenderer12, 0xFF, 0xFF, 0xFF, 0xFF);

		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		IMG_Init(imgFlags);
		TTF_Init();

		//SDL_Init(SDL_INIT_EVERYTHING);

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
			Mix_GetError());
			success = false;
		}
	}
	return success;
}

// Load Media
bool loadMedia()
{
	//Loading success flag
	bool success = true;

	// Load Fonts
	gFont = TTF_OpenFont("fonts/Viga-Regular.ttf", 26);
	gFont13 = TTF_OpenFont("fonts/Viga-Regular.ttf", 13);
	gFont26 = TTF_OpenFont("fonts/Viga-Regular.ttf", 26);
	gBG.loadFromFile("img/space.png", gRenderer12);
	gBullet.loadFromFile("img/bullet.png", gRenderer12);
	gSpawner.loadFromFile("img/spawner.png", gRenderer12);
	gVisionRadius.loadFromFile("img/vr.png", gRenderer12);

	// Load border animations
	for (int i=0; i<105; i++) {
		if (i <= 9) {
			std::stringstream tempss;
			tempss << "img/border/";
			tempss << "border_0000" << i;
			tempss << ".png";
			gBorder[i].loadFromFile(tempss.str().c_str(), gRenderer12);
		}
		else if (i > 9 && i <100) {
			std::stringstream tempss;
			tempss << "img/border/";
			tempss << "border_000" << i;
			tempss << ".png";
			gBorder[i].loadFromFile(tempss.str().c_str(), gRenderer12);
		}
		else if (i >= 100) {
			std::stringstream tempss;
			tempss << "img/border/";
			tempss << "border_00" << i;
			tempss << ".png";
			gBorder[i].loadFromFile(tempss.str().c_str(), gRenderer12);
		}
	}

	// Load Audio
	sLazer = Mix_LoadWAV("sounds/shoot_3.wav");
	sAmbientMusic = Mix_LoadMUS("sounds/ambient_space.mp3");
	sAtariBoom = Mix_LoadWAV("sounds/explosion_3.wav");

	// Set Audio volume
	//Mix_VolumeChunk(sAtariBoom, 60);

	//Rendering images on images
	//texTarget = SDL_CreateTexture(gRenderer12, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 200, 200);
	//bmpSurf = IMG_Load("img/planets/planet_purple_large.png");
	//bmpTex = SDL_CreateTextureFromSurface(gRenderer12, bmpSurf);
	return success;
}

// Free SDL resources
void close()
{
	// Free fonts
	TTF_CloseFont(gFont);
	TTF_CloseFont(gFont13);
	TTF_CloseFont(gFont26);
	gFont 			= NULL;
	gFont13 		= NULL;
	gFont26 		= NULL;

	// Free textures
	gText.free();
	gBG.free();
	gVisionRadius.free();
	gBullet.free();
	gSpawner.free();

	// Free audio
	Mix_FreeChunk(sLazer);
	Mix_FreeMusic(sAmbientMusic);
	Mix_FreeChunk(sAtariBoom);
	sAtariBoom 		= NULL;
	sLazer 			= NULL;
	sAmbientMusic 	= NULL;

	//Destroy window
	SDL_DestroyRenderer(gRenderer12);
	gWindow.free();

	//Quit SDL subsystems
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

// Returns the center of two objects - returns first objects center x,y
int getCenter(int x, int w, int w2){
	int centerY = x+w/2 - w2/2;
	return centerY;
}

// Set max limits for a value
void checkMaxLimitDouble(float &value, float maxLimitNeg, float maxLimitNegNew, float maxLimitPos, float maxLimitPosNew){
	if (value < maxLimitNeg){
		value = maxLimitNegNew;
	}
	if (value > maxLimitPos){
		value= maxLimitPosNew;
	}
}

// Generate a random double number
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

// Check collision between 2 objects
bool checkCollision(int x, int y, int w, int h, int x2, int y2, int w2, int h2){
	bool collide;
	if (x+w > x2 && x < x2 + w2 && y+h > y2 && y < y2 + h2){
		collide = true;
	}else{
		collide = false;
	}
	return collide;
}
