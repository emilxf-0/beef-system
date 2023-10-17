#pragma once
#include "Game.h"

class GameObject
{
public:
	GameObject(const char* textureSheet, int startPosX, int startPosY);
	~GameObject();

	void Update();
	void Render();

private:

	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};

