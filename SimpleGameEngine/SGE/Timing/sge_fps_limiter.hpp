//
//  Timing.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 12.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef Timing_h
#define Timing_h

#include "../include/sge_include.hpp"

namespace SGE {
    
    class FpsLimiter {
        float _fps, _maxFPS, _frameTime;
        unsigned int _startTicks;
        
        void calculateFPS(){
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
            if (currentFrame < NUM_SAMPLES) {
                count = currentFrame;
            } else {
                count = NUM_SAMPLES;
            }
            
            float frameTimeAverage = 0;
            for (int i = 0; i < count; i++) {
                frameTimeAverage += frameTimes[i];
            }
            frameTimeAverage /= count;
            
            if (frameTimeAverage > 0) {
                _fps = 1000.0f / frameTimeAverage;
            } else {
                _fps = 60.0f;
            }
        }
        
    public:
        
        FpsLimiter(){
            
        }
        
        ~FpsLimiter(){
            
        }
        
        void init(float maxFPS){
            setMaxFPS(maxFPS);
        }
        
        void setMaxFPS(float maxFPS){
            _maxFPS = maxFPS;
        }
        
        void begin(){
            _startTicks = SDL_GetTicks();
        }
        
        float end(){
            calculateFPS();
            
            float frameTicks = SDL_GetTicks() - _startTicks;
            if (1000.0f / _maxFPS > frameTicks) {
                SDL_Delay((Uint32)(1000.0f / _maxFPS - frameTicks));
            }
            
            return _fps;
        }
       
    };
    
}


#endif /* Timing_h */
