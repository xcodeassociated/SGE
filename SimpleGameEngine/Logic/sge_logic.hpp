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
	#ifdef SGE_SHARED
		#include <logic_export.h>
	#else
		#define LOGIC_EXPORT
	#endif
#else
	#define LOGIC_EXPORT
#endif

#include "../Object/sge_logic_priority.hpp"


class DynamicVectorLogic;

namespace SGE
{
	class Logic;
	class Action;
	class Object;
	class ActionHandler;
	class Game;
	/**
     * \brief 
     */
    class Logic
	{
		friend class Game;
		friend class DynamicVectorLogic;

	public:
	    /**
		 * \brief 
		 */
		using Priority = LogicPriority;
	    /**
         * \brief 
         */
        virtual void performLogic() = 0;

    protected:
	    /**
		 * \brief 
		 */
		static LOGIC_EXPORT ActionHandler* action_handler;

	    /**
	     * \brief 
	     * \param _p 
	     */
	    explicit Logic(Priority _p);

	    /**
         * \brief 
         */
        bool isOn = true;
	    /**
		 * \brief 
		 */
		Priority priority;

	    /**
	     * \brief 
	     * \param obj 
	     * \param action 
	     */
	    void sendAction(Action* action) const;

    public:

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
	    virtual bool getOn() final;

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
