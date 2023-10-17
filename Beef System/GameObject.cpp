#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int startPosX, int startPosY)
{
	objTexture = TextureManager::LoadTexture(textureSheet);

	xpos = startPosX;
	ypos = startPosY;
}

void GameObject::Update()
{
	xpos++;
	ypos++;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}


