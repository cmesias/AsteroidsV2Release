/*
 * LTextures.h
 *
 *  Created on: Dec 16, 2016
 *      Author: Carl
 */

#ifndef LTEXTURES_H_
#define LTEXTURES_H_

//Texture wrapper class
class LTexture {
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer* gRenderer);

	#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor,
			TTF_Font *gFont, SDL_Renderer* gRenderer);
	#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(SDL_Renderer* gRenderer, int x, int y, int w, int h, SDL_Rect* clip = NULL,
			double angle = 0.0, SDL_Point* center = NULL,
			SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

#endif /* LTEXTURES_H_ */
