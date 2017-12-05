#ifndef SGE_GAME_HPP
#define SGE_GAME_HPP

#include <memory>

namespace SGE {

    class InputHandler;
    class ObjectManager;
    class ActionHandler;
    class FpsLimiter;
    class Logger;

    class Game {

        std::shared_ptr<Logger> logger = nullptr;

	    /**
         * \brief 
         */
        ObjectManager* manager = nullptr;
	    /**
         * \brief 
         */
        FpsLimiter* limiter = nullptr;
	    /**
         * \brief 
         */
        bool playing = false;
	    /**
	     * \brief 
	     */
	    float time = 0;
	    /**
	     * \brief 
	     */
	    float fps = 0;
	    /**
	     * \brief 
	     */
	    InputHandler *input_handler = nullptr;
	    /**
         * \brief 
         */
        ActionHandler *action_handler = nullptr;

	    /**
         * \brief 
         */
        void processInputs(void); // Not used now - a candidate for deletion
	    /**
         * \brief 
         */
        void performActions(void);

	    /**
         * \brief 
         */
        void performLogics(void);

    public:
	    /**
         * \brief 
         */
        Game(ObjectManager *, ActionHandler *);

	    /**
         * \brief 
         */
        void run(void);

	    /**
         * \brief 
         */
        void stop(void);

	    /**
         * \brief 
         */
        void draw(void);

	    /**
         * \brief 
         */
        void setInputHandler(InputHandler *);
    };

}

#endif // !SGE_GAME_HPP
