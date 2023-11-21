﻿#pragma once

#include "Components.h"
#include "Serializable.h"
#include "Vector2D.h"
#include <unordered_map>

class TransformComponent : public Component, public Serializable
{

public:

	Vector2D position;
	Vector2D velocity;
	Vector2D lastPosition;
	std::unordered_map<std::string, int> transformData;


	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;


	TransformComponent()
	{
		position.x = 0.0f;
		position.y = 0.0f;
	}


	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int s)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = s;
	}

	void init() override
	{
		velocity.x = 0;
		velocity.y = 0;
	}

	void update() override
	{
		lastPosition = position;
		position.x += velocity.x;
		position.y += velocity.y;
	}

	void serializeToJSON(json& data) override
	{
		data["Position X"] = position.x;
	}

	void deserializeFromJSON(json& data)
	{
		position.x = data["Position X"];
	}


};