#pragma once

#include "EntityComponentSystem.h"
#include "Components.h"
class CharacterEntity :
    public Entity
{
public:

	std::string sprite = "assets/default.png";
	float startX = 0;
	float startY = 0;
	float rotation;
	std::string tag = "character";

	CharacterEntity() = default;

	CharacterEntity(const std::string& sprite, float x, float y)
	{
		this->sprite = sprite;
		startX = x;
		startY = y;
	}

	void init() override
	{
		this->addComponent<TransformComponent>(startX, startY);
		this->addComponent<RotationComponent>();
		this->addComponent<SpriteComponent>(sprite);
		this->addComponent<Controller>();
		this->addComponent<ColliderComponent>(tag);
	}
};
