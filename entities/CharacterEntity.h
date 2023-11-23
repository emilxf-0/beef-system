#pragma once

#include "EntityComponentSystem.h"
#include "components/Components.h"
#include "data/HandleData.h"

class CharacterEntity :
    public Entity
{
private:
	HandleData importer;

public:

	std::string sprite = "assets/default.png";
	float startX = 0;
	float startY = 0;
	float rotation = 0;
	std::string tag = "character";
	bool hasController = false;

	CharacterEntity() = default;

	CharacterEntity(const std::string& sprite, float x, float y, float rotation, bool controller)
	{
		this->sprite = sprite;
		startX = x;
		startY = y;
		hasController = controller;
		this->rotation = rotation;
	}

	void init() override
	{
		this->addComponent<TransformComponent>(startX, startY);
		this->addComponent<RotationComponent>(rotation);
		this->addComponent<SpriteComponent>(sprite);
		this->addComponent<ColliderComponent>(tag);
		this->addComponent<TraitComponent>();

		if (!hasController)
		{
			this->addComponent<ControllerComponent>(false);
			return;
		}
		this->addComponent<ControllerComponent>();
	}

    // Save the entire entity state to a file
	void saveEntityState(const std::string& filePath) {
		json entityData;

		// Serialize each component's data
		for (const auto& component : getComponents())
		{
			auto* serializableComponent = dynamic_cast<Serializable*>(component.get());
			if (serializableComponent) {
				serializableComponent->serializeToJSON(entityData);
			}

			importer.saveData(filePath, entityData);
		}
	}

    // Load the entire entity state from a file
    void loadEntityState(const std::string& filePath) {
        json entityData;

        // Load the entity state
		importer.loadData(filePath, entityData);

        // Deserialize each component's data
		for (const auto& component : getComponents())
		{
			auto* serializableComponent = dynamic_cast<Serializable*>(component.get());
			if (serializableComponent) {
				serializableComponent->deserializeFromJSON(entityData);
			}
		}
    }

};
