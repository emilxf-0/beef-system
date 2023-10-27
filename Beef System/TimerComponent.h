#pragma once
#include <SDL_timer.h>

#include "EntityComponentSystem.h"
class TimerComponent :
    public Component
{
private:
    const int CONVERT_TO_MILLISECONDS = 1000;


public:
    bool timerDone;
    Uint64 startTime = 0;
    Uint64 currentTime = 0;
    Uint64 timeInSeconds = 0;
    Uint64 timer = 1;

    TimerComponent() = default;

    void init() override
    {
    	startTime = SDL_GetTicks64();
    }

    void update() override
    {
        timerDone = false;
    	currentTime = SDL_GetTicks64();
        timeInSeconds = currentTime - startTime;

       
	    if (timeInSeconds >= timer * CONVERT_TO_MILLISECONDS)
	    {

            std::cout << "Beep beep" << std::endl;
            timerDone = true;
            startTime = currentTime;
	    }
    }
};

