#ifndef sge_action_h
#define sge_action_h



namespace SGE {
    class ActionHandler;
    
    class Action{
    protected:
        double duration = 0;
        ActionHandler* action_handler = nullptr;
        
    public:
        virtual void action_begin(void) noexcept = 0;
        virtual void action_main(void) noexcept = 0;
        virtual void action_ends(void) noexcept = 0;

        virtual void setObjectManager(ActionHandler*) noexcept = 0;
        
    };
    
}
#endif /* sge_action_h */