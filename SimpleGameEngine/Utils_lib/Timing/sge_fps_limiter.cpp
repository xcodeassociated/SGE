#include "sge_fps_limiter.hpp"
#include <SDL2/SDL.h>

#if !defined(_WIN32)
float SGE::delta_time = 0;
#endif

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
	this->time = boost::posix_time::microsec_clock::local_time();
}

void SGE::FpsLimiter::setMaxFPS(float maxFPS)
{
	_maxFPS = maxFPS;
}

void SGE::FpsLimiter::begin()
{
	_startTicks = SDL_GetTicks();
	boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration diff = now - this->time;
	this->time = now;
    delta_time = diff.total_milliseconds() * 0.001f;
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

void SGE::FpsLimiter::reset()
{
	delta_time = 0;
	this->time = boost::posix_time::microsec_clock::local_time();
}
