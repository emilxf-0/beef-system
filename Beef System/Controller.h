#pragma once
#include "Game.h"
#include "EntityComponentSystem.h"
#include "Components.h"
#include "Input.h"

class Controller : public Component
{
public:
	TransformComponent* transform;
	RotationComponent* rotation;
	
	const Uint8* keyBoardState = SDL_GetKeyboardState(nullptr);

	Vector2D direction;

	int speed = 3;

	enum drivingState
	{
		IDLE,
		FORWARD,
		REVERSE,
		FWD_TURNING_LEFT,
		FWD_TURNING_RIGHT,
		R_TURNING_LEFT,
		R_TURNING_RIGHT
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
		auto angles = rotation->angle;
		auto angleInRadians = angles * (M_PI / 180);


		if(keyBoardState[SDL_SCANCODE_W] && keyBoardState[SDL_SCANCODE_D])
		{
			drivingDirection = FWD_TURNING_RIGHT;
		}
		else if(keyBoardState[SDL_SCANCODE_W] && keyBoardState[SDL_SCANCODE_A])
		{
			drivingDirection = FWD_TURNING_LEFT;
		}
		else if(keyBoardState[SDL_SCANCODE_S] && keyBoardState[SDL_SCANCODE_A])
		{
			drivingDirection = R_TURNING_LEFT;
		}
		else if(keyBoardState[SDL_SCANCODE_S] && keyBoardState[SDL_SCANCODE_D])
		{
			drivingDirection = R_TURNING_RIGHT;
		}
		else if(keyBoardState[SDL_SCANCODE_W])
		{
			drivingDirection = FORWARD;
		}
		else if(keyBoardState[SDL_SCANCODE_S])
		{
			drivingDirection = REVERSE;
		}
		else
		{
			drivingDirection = IDLE;
		}

		switch (drivingDirection)
		{
		case IDLE:
			std::cout << "standing still" << std::endl;
			transform->velocity.x = 0;
			transform->velocity.y = 0;
			break;

		case FORWARD:
			direction.x = SDL_cos(angleInRadians);
			direction.y = SDL_sin(angleInRadians);
			direction.normalize();

			transform->velocity.x = direction.x * speed;
			transform->velocity.y = direction.y * speed;
			break;

		case REVERSE:
			direction.x = SDL_cos(angleInRadians);
			direction.y = SDL_sin(angleInRadians);
			direction.normalize();

			transform->velocity.x = -direction.x * speed;
			transform->velocity.y = -direction.y * speed;
			break;

		case FWD_TURNING_LEFT:
			direction.x = SDL_cos(angleInRadians);
			direction.y = SDL_sin(angleInRadians);
			direction.normalize();

			transform->velocity.x = direction.x * speed;
			transform->velocity.y = direction.y * speed;
			
			rotation->angle -= 1;
			break;

		case FWD_TURNING_RIGHT:
			direction.x = SDL_cos(angleInRadians);
			direction.y = SDL_sin(angleInRadians);
			direction.normalize();

			transform->velocity.x = direction.x * speed;
			transform->velocity.y = direction.y * speed;
			
			rotation->angle += 1;
			break;

		case R_TURNING_LEFT:
			direction.x = SDL_cos(angleInRadians);
			direction.y = SDL_sin(angleInRadians);
			direction.normalize();

			transform->velocity.x = -direction.x * speed;
			transform->velocity.y = -direction.y * speed;
			
			rotation->angle += 1;
			break;

		case R_TURNING_RIGHT:
			direction.x = SDL_cos(angleInRadians);
			direction.y = SDL_sin(angleInRadians);
			direction.normalize();

			transform->velocity.x = -direction.x * speed;
			transform->velocity.y = -direction.y * speed;
			
			rotation->angle -= 1;
			break;

			std::cout << "backwards right" << std::endl;
			break;

		default:
			break;
		}


	
		}
};

