//
//  sge_logic.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 15/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_logic_h
#define sge_logic_h

#ifdef _WIN32
#include <logic_export.h>
#else
#define LOGIC_EXPORT
#endif

#include "sge_logic_priority.hpp"


class DynamicVectorLogic;

namespace SGE {
	class Logic;
	class Action;
	class Object;
	class LogicBind;
	class ObjectManager;
	class Game;
	class ObjectBind;
	class ActionHandler;
	/**
     * \brief 
     */
    class Logic{
		friend class Game;
		friend class ObjectManager;

		friend class DynamicVectorLogic;

	public:
	    /**
		 * \brief 
		 */
		using Priority = LogicPriority;
	    /**
         * \brief 
         */
        virtual void performLogic(const ObjectBind&) = 0;
    protected:
	    /**
		 * \brief 
		 */
		static LOGIC_EXPORT ActionHandler* action_handler;

	    /**
	     * \brief 
	     * \param _p 
	     */
	    Logic(Priority _p);

	    /**
         * \brief 
         */
        bool isOn = true;
	    /**
		 * \brief 
		 */
		Priority priority;// = Priority::Low;

	    /**
	     * \brief 
	     * \param obj 
	     * \param action 
	     */
	    void sendAction(Object* obj, Action* action) const;

    public:
	  
    	/**
		 * \brief 
		 */
		using Binder = LogicBind;

	    /**
	     * \brief 
	     * \return 
	     */
	    Priority getPriority() const;

	    /**
	     * \brief 
	     * \param e 
	     */
	    virtual void setOn(bool e) final;

	    /**
	     * \brief 
	     * \return 
	     */
	    virtual bool getOn(void) final;

	    /**
	     * \brief 
	     */
	    virtual void toggleOn() final;

	    /**
         * \brief 
         */
        virtual ~Logic() = 0;
        
    };

}


#endif /* sge_logic_h */
