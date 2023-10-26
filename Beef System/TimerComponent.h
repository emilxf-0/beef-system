#pragma once
#include <SDL_timer.h>

#include "EntityComponentSystem.h"
class TimerComponent :
    public Component
{
public:
    bool timerDone;
    float startTime = 0.0f;
    float currentTime = 0.0f;
    float timeInSeconds = 0.0f;
    float timer = 4.0f;

    TimerComponent() = default;

    void init() override
    {
    	startTime = SDL_GetTicks64();
    }

    void update() override
    {
        timerDone = false;
    	currentTime = SDL_GetTicks64();
        timeInSeconds = (currentTime - startTime) / 1000;

       
	    if (timeInSeconds >= timer)
	    {

            std::cout << "Beep beep" << std::endl;
            timerDone = true;
	    	startTime = SDL_GetTicks64();
	    }
    }
};

