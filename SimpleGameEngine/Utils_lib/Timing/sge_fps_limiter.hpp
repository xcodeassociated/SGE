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
