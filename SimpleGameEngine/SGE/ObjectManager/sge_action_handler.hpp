#ifndef SGE_ACTION_HANDLER_HPP
#define SGE_ACTION_HANDLER_HPP

#include "../include/sge_include.hpp"

#include "../Action/sge_action.hpp"
#include "../Relay/sge_relay_interface.hpp"

namespace SGE{
	enum class Key
	{
		W = SDLK_w,
        A = SDLK_a,
        S = SDLK_s,
        D = SDLK_d,
	};

	class ActionBinder
	{
	public:
		using Bind = std::pair<ObjectID, ActionID>;

	private:
		Bind bind;
		Key kid;

	public:
		ActionBinder(Object::ID object, Action::ID action, Key key):
			bind(object,action),
			kid(key)
		{}

		Bind getBind() const
		{
			return this->bind;
		}

		Key getKey() const
		{
			return this->kid;
		}
	};

    class ActionHandler {
        Relay* relay = Relay::getRelay();
        std::vector<Action*> actions; //TODO: queue instead of vector !!!
        
    public:

        ActionHandler(void) : actions{} {
            
        }
        
		void handleInputAction(ActionBinder::Bind bind)
		{
            Action* act_ptr = bind.second.getAction();
            Object* obj_ptr = this->relay->getObjectPtr(bind.first);
            
            act_ptr->action_main(obj_ptr);
            
			std::cerr << "Input handled\n";
		}

        void addAction(ActionID ){
        }
        
        void performAllActions(){
            for (auto& act : this->actions){
                act->action_begin(nullptr);
                act->action_main(nullptr);
                act->action_ends(nullptr);
            }
            this->actions.erase(actions.begin(), actions.end());
        }
        
        void foo(){
            std::cerr << "ACTION!" << std::endl;
        }
    };

}

#endif // !SGE_ACTION_HANDLER_HPP
