#ifndef SGE_ACTION_HANDLER_HPP
#define SGE_ACTION_HANDLER_HPP

#include "../include/sge_include.hpp"

#include "../Action/sge_action.hpp"

namespace SGE{
	enum class Key
	{
		W = SDLK_w
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
        std::vector<Action*> actions; //TODO: queue instead of vector !!!
        
    public:

        ActionHandler(void) : actions{} {
            
        }
        
		void handleInputAction(ActionBinder::Bind bind)
		{
			std::cerr << "Input handled\n";
		}

        void addAction(ActionID ){
        }
        
        void performAllActions(){
            for (auto& act : this->actions){
                act->action_begin();
                act->action_main();
                act->action_ends();
            }
            this->actions.erase(actions.begin(), actions.end());
        }
        
        void foo(){
            std::cerr << "ACTION!" << std::endl;
        }
    };

}

#endif // !SGE_ACTION_HANDLER_HPP
