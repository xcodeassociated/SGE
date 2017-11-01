//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_LOGIC_ID_HPP
#define SGE_ZOMBIEGAME_SGE_LOGIC_ID_HPP

#include "sge_id.hpp"

namespace SGE {

    class Logic;
    class Game;
    class ObjectManager;

	/**
     * \brief ID for Logics
     */
    class LogicID : public ID
    {
        friend class Game;
        friend class ObjectManager;

        friend class Logic;

	    /**
         * \brief Pointer to Logic
         */
        Logic* logic;
	    /**
         * \brief 
         * \param id 
         * \param logic 
         */
        LogicID(const long id, Logic* logic);
    public:
	    /**
         * \brief 
         * \param logic 
         */
        LogicID(Logic* logic);

	    /**
         * \brief 
         * \return 
         */
        Logic* getLogic() const;

	    /**
         * \brief 
         * \return 
         */
        Logic* operator->() const;
    };

}


#endif //SGE_ZOMBIEGAME_SGE_LOGIC_ID_HPP
