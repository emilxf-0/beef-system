#pragma once

#include "EntityComponentSystem.h"
#include "Components.h"
#include "HandleData.h"

class CharacterEntity :
    public Entity
{
private:
	HandleData importer;

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

    // Save the entire entity state to a file
    void saveEntityState(const std::string& filePath) {
        json entityData;

        // Serialize each component's data
		for (auto& component : { &getComponent<TransformComponent>() } )
		{
        	component->serializeToJSON(entityData);
        }

		importer.saveData(filePath, entityData);
    }

    //// Load the entire entity state from a file
    //void loadEntityState(const std::string& filePath) {
    //    json entityData;

    //    // Load the entity state
    //    importer.loadData(filePath, entityData);

    //    // Deserialize each component's data
    //    for (auto& component : components) {
    //        component->deserializeFromJSON(entityData);
    //    }
    //}

};
