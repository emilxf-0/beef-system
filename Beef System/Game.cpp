
#include "Game.h"

#include "CharacterEntity.h"
#include "ColliderComponent.h"
#include "Map.h"
#include "Components.h"
#include "Collision.h"
#include "TimerComponent.h"
#include "TrafficLightEntity.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Manager manager;

auto& wall(manager.addEntity());
auto& enemy(manager.addEntity());
auto& trafficLight = manager.addEntity<TrafficLightEntity>(5);

auto& player = manager.addEntity<CharacterEntity>("assets/cars/player_car.png", 150, 0);


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

	manager.init();

	enemy.addComponent<TransformComponent>(200, 200);
	enemy.addComponent<SpriteComponent>("assets/cars/enemy_car.png");
	enemy.addComponent<ColliderComponent>("enemy");

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 150, 300, 1);
	wall.addComponent<SpriteComponent>("assets/environment/grass.png");
	wall.addComponent<ColliderComponent>("wall");

	trafficLight.getComponent<ColliderComponent>().scaleColliderUniform(30);
	trafficLight.getComponent<ColliderComponent>().debugCollider(true);

	player.getComponent<ColliderComponent>().debugCollider(true);


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


void Game::update(float deltaTime)
{
	manager.refresh();
	manager.update();

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider, trafficLight.getComponent<ColliderComponent>().collider))
	{
		
	}

	if (trafficLight.getComponent<TimerComponent>().timerDone)
	{
		trafficLight.switchToNextColor();
	}
}


void Game::render(float interpolation)
{
	if (renderer == nullptr)
	{
			return;
	}

	SDL_RenderClear(renderer);
	map->DrawMap();
	manager.draw(interpolation);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

