#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int MS_PER_UPDATE = 1000 / FPS;

	static const int WIDTH = 800;
	static const int HEIGHT = 640;

	Uint64 currentTime;

	game = new Game();

	game->init("Beef game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);

	float previousTime = SDL_GetTicks64();
	float lag = 0.0f;
	float deltaTime = 0.0f;
	float renderTime = 0.0f;

	while (game->running())
	{
		currentTime = SDL_GetTicks64();
		renderTime = currentTime - previousTime;

		deltaTime = renderTime / 1000;

		previousTime = currentTime;
		lag += renderTime;

		game->handleEvents();

		while (lag >= MS_PER_UPDATE)
		{
			game->update(deltaTime);
			lag -= MS_PER_UPDATE;
		}

		game->render(lag / MS_PER_UPDATE);
	}

	game->clean();

	return 0;
}
