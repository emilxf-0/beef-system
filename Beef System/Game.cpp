
#include "Game.h"

#include "ColliderComponent.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Manager manager;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());
auto& enemy(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flag = 0;
	if(fullscreen)
	{
		flag = SDL_WINDOW_FULLSCREEN;
	}

	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);

		if(window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if(renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created!" << std::endl;
		}

		isRunning = true;
	}


	map = new Map();

	player.addComponent<TransformComponent>();
	player.addComponent<RotationComponent>();
	player.addComponent<SpriteComponent>("assets/cars/player_car.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	enemy.addComponent<TransformComponent>(200, 200);
	enemy.addComponent<SpriteComponent>("assets/cars/enemy_car.png");
	enemy.addComponent<ColliderComponent>("enemy");

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 150, 300, 1);
	wall.addComponent<SpriteComponent>("assets/environment/grass.png");
	wall.addComponent<ColliderComponent>("wall");
}


void Game::handleEvents()
{

	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}

}


void Game::update()
{
	manager.refresh();
	manager.update();

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider))
	{
		player.getComponent<TransformComponent>().scale = 10;
	}
}


void Game::render()
{
	if (renderer == nullptr)
	{
			return;
	}

	SDL_RenderClear(renderer);
	map->DrawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

