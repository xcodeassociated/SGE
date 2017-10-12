//
//  sge_logic.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 15/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_logic_h
#define sge_logic_h

#include "sge_action_handler.hpp"

class DynamicVectorLogic;

namespace SGE {
	class Logic;
	class LogicBind;
	class ActionHandler;
	class ObjectManager;

	class LogicID : public ID
	{
	friend class ObjectManager;
	friend class Logic;

		Logic* logic;
		LogicID(const long id, Logic* logic) : ID(id), logic(logic) {}
	public:
		LogicID(Logic* logic) : ID(-1L), logic(logic) {}

		Logic* getLogic() const {
			return logic;
		}

		Logic* operator->() const {
			return logic;
		}
    };

    class Logic{
		friend class ObjectManager;
		friend class DynamicVectorLogic;

	public:
		using Priority = LogicPriority;
        virtual void performLogic(const ObjectBind&) = 0;
    protected:
		static ActionHandler* action_handler;

		Logic(Priority _p): priority(_p){}

        bool isOn = true;
		Priority priority = Priority::Low;

		void sendAction(Object::ID obj,Action::ID action) const
		{
			action_handler->performSingleAction(ActionBind(obj, action), this->priority);
		}

    public:
		using ID = LogicID;
		using Binder = LogicBind;

		
        
        Priority getPriority() const{
            return this->priority;
        }
       
        virtual void setOn(bool e) final {
            this->isOn = e;
        }
        
        virtual bool getOn(void) final {
            return this->isOn;
        }
        
		virtual void toggleOn() final {
			this->isOn = !this->isOn;
		}

        virtual ~Logic() = 0;
        
    };
    
    inline Logic::~Logic(){}
    
	ActionHandler* Logic::action_handler = nullptr;

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
