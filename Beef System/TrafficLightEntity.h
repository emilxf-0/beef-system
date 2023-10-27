#pragma once
#include "EntityComponentSystem.h"
#include "Components.h"
class TrafficLightEntity :
    public Entity
{
private:
    SpriteComponent* redLight;
    SpriteComponent* yellowLight;
    SpriteComponent* greenLight;
    SpriteComponent* currentLight;

    TimerComponent* timer;

    enum trafficState
    {
        RED,
        YELLOW,
        GREEN
    };

public:
	trafficState color = RED;

    TrafficLightEntity() = default;

    void init() override
	{
        redLight = &addComponent<SpriteComponent>("assets/props/red_light.png");
        yellowLight = &addComponent<SpriteComponent>("assets/props/yellow_light.png");
        greenLight = &addComponent<SpriteComponent>("assets/props/green_light.png");
        currentLight = &addComponent<SpriteComponent>();

        currentLight->setTexture(redLight->getTexture());
        timer = &addComponent<TimerComponent>();

	}

   
    void switchToNextColor()
    {
	    switch (color)
	    {
	    case RED:
            currentLight->setTexture(redLight->getTexture());
            color = YELLOW;
            break;
	    case YELLOW:
            currentLight->setTexture(yellowLight->getTexture());
            color = GREEN;
            break;
        case GREEN:
            currentLight->setTexture(greenLight->getTexture());
            color = RED;
            break;
	    }
    }
    

};

