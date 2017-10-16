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
#include "sge_action.hpp"

class DynamicVectorLogic;

namespace SGE {
	class LogicBind;

	class LogicID : public ID
	{
	friend class ObjectManager;
	friend class Logic;

		Logic* logic;
		LogicID(const long id, Logic* logic);
	public:
		LogicID(Logic* logic);

		Logic* getLogic() const;

		Logic* operator->() const;
    };

    class Logic{
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

	class LogicBind
	{
		LogicID logic;
		ObjectBind bind;
	public:
		LogicBind(Logic::ID logic, Object::ID object) : logic(logic), bind(object) {}

		LogicID getLogic()
		{
			return this->logic;
		}

		ObjectBind& getObject()
		{
			return this->bind;
		}

		bool operator==(const LogicBind& b) const
		{
			return logic == b.logic&&bind[0] == b.bind[0];
		}

		bool operator<(const LogicBind& other) const
		{
			if(bind[0].getID() == other.bind[0].getID())
			{
				return this->logic->getPriority() < other.logic->getPriority();
			}
			return bind[0].getID() < other.bind[0].getID();
		}
	};
}


#endif /* sge_logic_h */
