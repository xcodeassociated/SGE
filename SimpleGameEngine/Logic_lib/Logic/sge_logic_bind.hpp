//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_LOGIC_BIND_HPP
#define SGE_ZOMBIEGAME_SGE_LOGIC_BIND_HPP

#include "sge_object_bind.hpp"

namespace SGE {
	class Logic;
	class Object;

	/**
     * \brief 
     */
    class LogicBind
    {
	    /**
         * \brief 
         */
        Logic* logic;
	    /**
         * \brief 
         */
        ObjectBind bind;
    public:
	    /**
         * \brief 
         * \param logic 
         * \param object 
         */
        LogicBind(Logic* logic, Object* object);

	    /**
         * \brief 
         * \return 
         */
        Logic* getLogic();

	    /**
         * \brief 
         * \return 
         */
        ObjectBind& getObject();

	    /**
         * \brief 
         * \param b 
         * \return 
         */
        bool operator==(const LogicBind& b) const;

	    /**
         * \brief 
         * \param other 
         * \return 
         */
        bool operator<(const LogicBind& other) const;
    };

}


#endif //SGE_ZOMBIEGAME_SGE_LOGIC_BIND_HPP
