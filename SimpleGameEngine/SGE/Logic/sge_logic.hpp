//
//  sge_logic.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 15/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_logic_h
#define sge_logic_h

namespace SGE {
	class Logic;
	class ActionHandler;
	class ObjectManager;

	class LogicID : public ID
	{
	friend class ObjectManager;
		Logic* logic;
	public:
		LogicID(const long id, Logic* logic) : ID(id), logic(logic) {}
	};

    class Logic{
		friend class ObjectManager;
    protected:
		static ActionHandler* aHandler;

        bool isOn;
        
		virtual void performLogic(Object* obj) = 0;

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

			bool operator==(const Binder& b)
			{
				return logic == b.logic&&object == b.object;
			}
    		
		};
       
        virtual void setOn(bool e) final {
            this->isOn = e;
        }
        
        virtual bool getOn(void) final {
            return this->isOn;
        }
        
        virtual ~Logic() = 0;
        
    };
    
	ActionHandler* Logic::aHandler = nullptr;
}


#endif /* sge_logic_h */
