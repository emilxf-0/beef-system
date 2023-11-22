#pragma once
#include "Game.h"
#include "EntityComponentSystem.h"
#include "Components.h"
#include "Input.h"
#include "Vector2D.h"

class ControllerComponent : public Component
{
public:
	TransformComponent* transform;
	RotationComponent* rotation;

	const Uint8* keyBoardState = SDL_GetKeyboardState(nullptr);

	Vector2D direction = Vector2D(0, 0);
	double angleInRadians = 0.0;

	float speed = 3;
	float const ANGLE_INCREMENT = 3.0f;

	bool playerController = true;

	ControllerComponent() = default;

	ControllerComponent(bool isPlayer)
	{
		playerController = isPlayer;
	}

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

	void setSpeed(float speed)
	{
		this->speed = speed;
	}

private:
	void updateDirection()
	{
		angleInRadians = rotation->angle * (M_PI / 180);

		direction.x = SDL_cos(angleInRadians);
		direction.y = SDL_sin(angleInRadians);
		direction.normalize();

		if(!playerController)
		{
			drivingDirection = FORWARD;
			return;
		}

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
		if (!playerController)
			return;

		if (keyBoardState[SDL_SCANCODE_A])
		{
			if (drivingDirection == REVERSE)
			{
				rotation->angle += ANGLE_INCREMENT;
				return;
			}

			rotation->angle -= ANGLE_INCREMENT;

		}
		else if (keyBoardState[SDL_SCANCODE_D])
		{
			if (drivingDirection == REVERSE)
			{
				rotation->angle -= ANGLE_INCREMENT;
				return;
			}
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
			transform->velocity.x = direction.x * speed;
			transform->velocity.y = direction.y * speed;
			break;

		case REVERSE:
			transform->velocity.x = -direction.x * speed;
			transform->velocity.y = -direction.y * speed;
			break;

		default:
			break;
		}

	}



};
