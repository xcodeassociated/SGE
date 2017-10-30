#ifndef SGE_GAME_HPP
#define SGE_GAME_HPP

namespace SGE {

    class InputHandler;
    class ObjectManager;
    class ActionHandler;
    class FpsLimiter;

    class Game {
        ObjectManager* manager = nullptr;
        FpsLimiter* limiter = nullptr;
        bool playing = false;
        float time = 0, fps = 0;
        InputHandler *input_handler = nullptr;
        ActionHandler *action_handler = nullptr;

        void processInputs(void); // Not used now - a candidate for deletion
        void performActions(void);

        void performLogics(void);

    public:
        Game(ObjectManager *, ActionHandler *);

        void run(void);

        void stop(void);

        void draw(void);

        void setInputHandler(InputHandler *);
    };

}

#endif // !SGE_GAME_HPP
