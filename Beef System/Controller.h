#pragma once
#include "Game.h"
#include "EntityComponentSystem.h"
#include "Components.h"
#include "Input.h"
#include "Vector2D.h"

class Controller : public Component
{
public:
	TransformComponent* transform;
	RotationComponent* rotation;

	const Uint8* keyBoardState = SDL_GetKeyboardState(nullptr);

	Vector2D direction = Vector2D(0, 0);
	double angleInRadians = 0.0;

	float const SPEED = 3;
	float const ANGLE_INCREMENT = 1.0f;

	enum drivingState
	{
		IDLE,
		FORWARD,
		REVERSE,
	};

	drivingState drivingDirection;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		rotation = &entity->getComponent<RotationComponent>();
		drivingDirection = IDLE;
	}

	void update() override
	{

		updateDirection();
		updateRotation();
		updateVelocity();
	}

private:
	void updateDirection()
	{
		angleInRadians = rotation->angle * (M_PI / 180);

		direction.x = SDL_cos(angleInRadians);
		direction.y = SDL_sin(angleInRadians);
		direction.normalize();

		if (keyBoardState[SDL_SCANCODE_W])
		{
			drivingDirection = FORWARD;
		}
		else if (keyBoardState[SDL_SCANCODE_S])
		{
			drivingDirection = REVERSE;
		}
		else
		{
			drivingDirection = IDLE;
		}

	}

	void updateRotation()
	{
		if (keyBoardState[SDL_SCANCODE_A])
		{
			rotation->angle -= ANGLE_INCREMENT;
		}
		else if (keyBoardState[SDL_SCANCODE_D])
		{
			rotation->angle += ANGLE_INCREMENT;
		}
	}

	void updateVelocity()
	{

		switch (drivingDirection)
		{
		case IDLE:
			transform->velocity.x = 0;
			transform->velocity.y = 0;
			break;

		case FORWARD:
			transform->velocity.x = direction.x * SPEED;
			transform->velocity.y = direction.y * SPEED;
			break;

		case REVERSE:
			transform->velocity.x = -direction.x * SPEED;
			transform->velocity.y = -direction.y * SPEED;
			break;

		default:
			break;
		}

	}

};
