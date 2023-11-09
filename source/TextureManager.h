#pragma once
#include "Game.h"

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const std::string& path);
	static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, double angle, SDL_RendererFlip flip);
	static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
};

