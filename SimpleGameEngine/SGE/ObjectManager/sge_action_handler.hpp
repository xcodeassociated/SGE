#ifndef SGE_ACTION_HANDLER_HPP
#define SGE_ACTION_HANDLER_HPP

#include "../Action/sge_action.hpp"

namespace SGE{
    
    class ActionHandler {
        std::vector<Action*> actions; //TODO: queue instead of vector !!!
        
    public:
        ActionHandler(void) : actions{} {
            
        }
        
        void addAction(Action* _action){
            this->actions.push_back(_action);
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
