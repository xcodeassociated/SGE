//
//  Timing.hpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 12.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef Timing_h
#define Timing_h

#ifdef _WIN32
	#ifdef SHARED
		#include <utils_export.h>
	#else
		#define UTILS_EXPORT extern
	#endif

	#include <boost/config/platform/win32.hpp>
#else
	#define UTILS_EXPORT extern
#endif

#include <boost/date_time/posix_time/posix_time.hpp>

namespace SGE
{
    class Logger;

    UTILS_EXPORT float delta_time;

    class FpsLimiter {
	    float _fps = 0;
	    float _maxFPS = 0;
	    float _frameTime = 0;
	    unsigned int _startTicks = 0;
		boost::posix_time::ptime time;

	    void calculateFPS();

    public:
	    void init(float maxFPS);
	    void setMaxFPS(float maxFPS);

	    void begin();
	    float end();
		void reset();
    };
    
}


#endif /* Timing_h */
