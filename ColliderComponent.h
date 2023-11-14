#pragma once

#include <string>
#include "SDL.h"
#include "Components.h"

class ColliderComponent : public Component
{
public:

	SDL_Rect collider;
	std::string tag;
	bool scaled = false;
	bool debug = false;

	TransformComponent* transform;

	ColliderComponent() = default;

	ColliderComponent(const std::string& tag)
	{
		this->tag = tag;
	}


	void init() override
	{
		if(!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		if (!scaled)
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}
	}

	void draw(float interpolation) override
	{
		if (debug)
		{
			SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);

			// Draw the collider rectangle
			SDL_RenderDrawRect(Game::renderer, &collider);

			// Reset the renderer color (you might want to change it based on your game's color scheme)
			SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
		}
	}


	void scaleColliderUniform(const int scale)
	{
		collider.w = transform->width * scale;
		collider.h = transform->height * scale;

		collider.x -= collider.w / 2;
		collider.y -= collider.h / 2;

		scaled = true;
	}

	void debugCollider(bool isActive)
	{
		debug = isActive;
	}

};
