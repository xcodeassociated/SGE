//
//  Timing.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 12.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef Timing_h
#define Timing_h

namespace SGE {
    
    class FpsLimiter {
        float _fps, _maxFPS, _frameTime;
        unsigned int _startTicks;

	    void calculateFPS();

    public:

	    FpsLimiter();

	    ~FpsLimiter();

	    void init(float maxFPS);

	    void setMaxFPS(float maxFPS);

	    void begin();

	    float end();
    };
    
}


#endif /* Timing_h */
