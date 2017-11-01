//
// Created by Janusz Majchrzak on 30/10/2017.
//

#ifndef SGE_ZOMBIEGAME_SGE_LOGIC_BIND_HPP
#define SGE_ZOMBIEGAME_SGE_LOGIC_BIND_HPP

#include "sge_logic_id.hpp"
#include "sge_object_bind.hpp"

namespace SGE {

	/**
     * \brief 
     */
    class LogicBind
    {
	    /**
         * \brief 
         */
        LogicID logic;
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
        LogicBind(LogicID logic, ObjectID object);

	    /**
         * \brief 
         * \return 
         */
        LogicID getLogic();

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
