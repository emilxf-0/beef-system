#pragma once


#include "EntityComponentSystem.h"
#include "Components.h"
class CharacterEntity :
    public Entity
{
public:

	std::string sprite = "assets/default.png";
	float startX, startY;
	float rotation;
	std::string tag = "character";

	CharacterEntity() = default;


	void init() override
	{
		this->addComponent<TransformComponent>();
		this->addComponent<RotationComponent>();
		this->addComponent<SpriteComponent>(sprite);
		this->addComponent<Controller>();
		this->addComponent<ColliderComponent>(tag);
	}


};

