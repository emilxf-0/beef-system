#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update(float deltaTime);
	void render(float interpolate);
	void clean();

	bool running() { return isRunning; }
	static SDL_Renderer* renderer;
	static SDL_Event event;

private:
	bool isRunning;
	int count;
	SDL_Window* window;
};
