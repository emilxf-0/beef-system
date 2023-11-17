#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw(float interpolation) {}

	virtual ~Component() = default;
};

class Entity
{
public:
	virtual void init() {}

	void update()
	{
		for (auto& component : components) component->update();
	}

	void draw(float interpolation)
	{
		for (auto& component : components) component->draw(interpolation);
	}
	bool isActive() const { return active; }
	void destroy() { active = false; }

	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs >
	T& addComponent(TArgs&&... mArgs)
	{
		T* component(new T(std::forward<TArgs>(mArgs)...));
		component->entity = this;
		std::unique_ptr<Component> unique_ptr{ component };
		components.emplace_back(std::move(unique_ptr));

		componentArray[getComponentTypeID<T>()] = component;
		componentBitSet[getComponentTypeID<T>()] = true;

		component->init();
		return *component;
	}

	template<typename T> T& getComponent() const
	{
		auto ptr = componentArray[getComponentTypeID<T>()];
		if (ptr)
		{
			return *static_cast<T*>(ptr);
		}
		else
		{
			throw std::out_of_range("Component not found");
		}
	}

	const std::vector<std::unique_ptr<Component>>& getComponents() const {
		return components;
	}

private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray = {};
	ComponentBitSet componentBitSet;


};

class Manager
{
private: std::vector<std::unique_ptr<Entity>> entities;

public:
	void init()
	{
		for (auto& entity : entities) entity->init();
	}

	void update()
	{
		for (auto& entity : entities) entity->update();
	}
	void draw(float interpolation)
	{
		for (auto& entity : entities) entity->draw(interpolation);
	}

	void refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	Entity& addEntity()
	{
		Entity* entity = new Entity();
		std::unique_ptr<Entity> unique_ptr{ entity };
		entities.emplace_back(std::move(unique_ptr));
		return *entity;

	}

	template <typename EntityType, typename... Args>
	EntityType& addEntity(Args&&... args)
	{
		EntityType* entity = new EntityType(std::forward<Args>(args)...);
		std::unique_ptr<Entity> unique_ptr{ entity };
		entities.emplace_back(std::move(unique_ptr));
		return *entity;
	}

};

