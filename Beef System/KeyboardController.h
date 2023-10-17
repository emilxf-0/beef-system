#pragma once
#include "Game.h"
#include "EntityComponentSystem.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		auto key = Game::event.key.keysym.sym;

		if(Game::event.type == SDL_KEYDOWN)
		{
			switch (key)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				break;

			case SDLK_a:
				transform->velocity.x = -1;
				break;

			case SDLK_s:
				transform->velocity.y = 1;
				break;

			case SDLK_d:
				transform->velocity.x = 1;
				break;

			default:
				break;
			}
		}

		if(Game::event.type == SDL_KEYUP)
		{

			switch (key)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				break;

			case SDLK_a:
				transform->velocity.x = 0;
				break;

			case SDLK_s:
				transform->velocity.y = 0;
				break;

			case SDLK_d:
				transform->velocity.x = 0;
				break;

			default:
				break;
			}
		}
	}
};

