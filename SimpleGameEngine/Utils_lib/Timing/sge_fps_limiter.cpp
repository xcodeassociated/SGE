#include "sge_fps_limiter.hpp"

#include <SDL2/SDL.h>

void SGE::FpsLimiter::calculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;
	static float prevTicks = SDL_GetTicks();

	float currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = currentTicks;

	int count;

	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		_fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		_fps = 60.0f;
	}
}

SGE::FpsLimiter::FpsLimiter()
{
}

SGE::FpsLimiter::~FpsLimiter()
{
}

void SGE::FpsLimiter::init(float maxFPS)
{
	setMaxFPS(maxFPS);
}

void SGE::FpsLimiter::setMaxFPS(float maxFPS)
{
	_maxFPS = maxFPS;
}

void SGE::FpsLimiter::begin()
{
	_startTicks = SDL_GetTicks();
}

float SGE::FpsLimiter::end()
{
	calculateFPS();

	float frameTicks = SDL_GetTicks() - _startTicks;
	if (1000.0f / _maxFPS > frameTicks)
	{
		SDL_Delay((Uint32)(1000.0f / _maxFPS - frameTicks));
	}

	return _fps;
}
