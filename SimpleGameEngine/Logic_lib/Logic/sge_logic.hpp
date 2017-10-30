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

#include "sge_id.hpp"
#include "sge_object.hpp"
#include "sge_logic_id.hpp"
#include "sge_action_handler.hpp"

class DynamicVectorLogic;

namespace SGE {
	class Logic;
	class LogicBind;
	class ObjectManager;
	class Game;

    class Logic{
		friend class Game;
		friend class ObjectManager;

		friend class DynamicVectorLogic;

	public:
		using Priority = LogicPriority;
        virtual void performLogic(const ObjectBind&) = 0;
    protected:
		static LOGIC_EXPORT ActionHandler* action_handler;

	    Logic(Priority _p);

        bool isOn = true;
		Priority priority = Priority::Low;

	    void sendAction(Object::ID obj, Action::ID action) const;

    public:
		using ID = LogicID;
		using Binder = LogicBind;


	    Priority getPriority() const;

	    virtual void setOn(bool e) final;

	    virtual bool getOn(void) final;

	    virtual void toggleOn() final;

        virtual ~Logic() = 0;
        
    };

}


#endif /* sge_logic_h */
