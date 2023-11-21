#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"

class RotationComponent : public Component, public Serializable
{

public:

	SDL_Point rotationCenter;
	double angle = 0;

	RotationComponent() = default;

	RotationComponent(double angle)
	{
		this->angle = angle;
	}


	void init() override
	{
	
	}

	void update() override
	{
		//angle += 1;
	}

	void serializeToJSON(json& data) override
	{
		data["Angle"] = angle;
	}

	void deserializeFromJSON(json& data) override
	{
		angle = data["Angle"];
	}
	
};