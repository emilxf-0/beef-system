#pragma once

#include "Components.h"
#include "Game.h"
#include "RotationComponent.h"
#include "SDL.h"
#include "TextureManager.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	RotationComponent* rotation;

	SpriteComponent() = default;

	SpriteComponent(const std::string& path)
	{
		setTexture(path);
	}

	~SpriteComponent() override
	{
		SDL_DestroyTexture(texture);
	}

	void setTexture(const std::string& path)
	{
		texture = TextureManager::LoadTexture(path);
	}

	void setTexture(SDL_Texture* newTexture)
	{
		this->texture = newTexture;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}

		transform = &entity->getComponent<TransformComponent>();

		if (!entity->hasComponent<RotationComponent>())
		{
			entity->addComponent<RotationComponent>();
		}
		rotation = &entity->getComponent<RotationComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override
	{
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw(float interpolation) override
	{
		int interpolatedX = static_cast<int>(transform->position.x * (1.0f - interpolation) +
			(transform->lastPosition.x * interpolation));
		int interpolatedY = static_cast<int>(transform->position.y * (1.0f - interpolation) +
			(transform->lastPosition.y * interpolation));

		destRect.x = interpolatedX;
		destRect.y = interpolatedY;

		TextureManager::Draw(texture, srcRect, destRect, rotation->angle, SDL_FLIP_NONE);
	}

	SDL_Texture* getTexture()
	{
		return texture;
	}

};
