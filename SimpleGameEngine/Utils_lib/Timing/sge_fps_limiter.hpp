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
#include <utils_export.h>
#include <boost/config/platform/win32.hpp>
#else
#define UTILS_EXPORT extern
#endif

#include <boost/date_time/posix_time/posix_time.hpp>

namespace SGE
{
    class Logger;

    UTILS_EXPORT float delta_time;

	/**
     * \brief 
     */
    class FpsLimiter {
	    /**
	     * \brief 
	     */
	    float _fps;
	    /**
	     * \brief 
	     */
	    float _maxFPS;
	    /**
	     * \brief 
	     */
	    float _frameTime;
	    /**
	     * \brief 
	     */
	    unsigned int _startTicks;

		boost::posix_time::ptime time;

	    /**
	     * \brief 
	     */
	    void calculateFPS();

    public:

	    /**
	     * \brief 
	     */
	    FpsLimiter();

	    /**
	     * \brief 
	     */
	    ~FpsLimiter();

	    /**
	     * \brief 
	     * \param maxFPS 
	     */
	    void init(float maxFPS);

	    /**
	     * \brief 
	     * \param maxFPS 
	     */
	    void setMaxFPS(float maxFPS);

	    /**
	     * \brief 
	     */
	    void begin();

	    /**
	     * \brief 
	     * \return 
	     */
	    float end();
    };
    
}


#endif /* Timing_h */
