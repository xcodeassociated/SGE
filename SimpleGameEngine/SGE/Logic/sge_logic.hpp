//
//  sge_logic.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 15/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_logic_h
#define sge_logic_h

#include "../ObjectManager/sge_action_handler.hpp"

class DynamicVectorLogic;

namespace SGE {
	class Logic;
	class ActionHandler;
	class ObjectManager;

	class LogicID : public ID
	{
	friend class ObjectManager;
	friend class Logic;

		Logic* logic;
	public:
		LogicID(const long id, Logic* logic) : ID(id), logic(logic) {}
    };

    class Logic{
		friend class ObjectManager;
		friend class DynamicVectorLogic;

	public:
		using Priority = LogicPriority;
        virtual void performLogic(Object::ID obj) = 0;
    protected:
		static ActionHandler* action_handler;

		Logic(Priority _p): priority(_p){}

        bool isOn = true;
		Priority priority = Priority::Low;

		void sendAction(Object::ID obj,Action::ID action) const
		{
			action_handler->performSingleAction(Bind(obj, action), this->priority);
		}

    public:
		using ID = LogicID;


		class Binder
		{
			LogicID logic;
			ObjectID object;
		public:
			Binder(Logic::ID logic, Object::ID object) : logic(logic), object(object) {}

			LogicID getLogic()
			{
				return this->logic;
			}

			ObjectID getObject()
			{
				return this->object;
			}

			bool operator==(const Binder& b) const
			{
				return logic == b.logic&&object == b.object;
			}

			bool operator<(const Binder& other) const
			{
				if(object.getID()==other.object.getID())
				{
					return logic.logic->priority < other.logic.logic->priority;
				}
				return object.getID() < other.object.getID();
			}
		};
        
        Priority getPriority() const{
            return this->priority;
        }
       
        virtual void setOn(bool e) final {
            this->isOn = e;
        }
        
        virtual bool getOn(void) final {
            return this->isOn;
        }
        
        virtual ~Logic() = 0;
        
    };
    
    Logic::~Logic(){}
    
	ActionHandler* Logic::action_handler = nullptr;
}


#endif /* sge_logic_h */
