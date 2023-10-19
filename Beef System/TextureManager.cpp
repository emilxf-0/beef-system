#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* path)
{
	SDL_Surface* tempSurface = IMG_Load(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, double angle,
                          SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, texture, &src, &dest, angle, NULL, flip);
}


