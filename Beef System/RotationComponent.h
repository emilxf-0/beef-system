#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"

class RotationComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Rect srcRect, destRect;

public:

	SDL_Point rotationCenter;
	double angle = 0;

	RotationComponent() = default;


	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		rotationCenter = { transform->width / 2, transform->height / 2 };

		std::cout << "rotation!" << std::endl;
	}

	void update() override
	{
		angle += 1;
	}
};