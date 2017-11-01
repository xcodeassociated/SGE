//
//  sge_logic_collide.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 15/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_logic_collide_h
#define sge_logic_collide_h

#include "sge_logic.hpp"
#include <functional>

namespace SGE {
    class Object;
    class ObjectID;
    
    namespace Logics{
        
	    /**
         * \brief 
         */
        class Collide : public Logic{
        public:
	        /**
             * \brief 
             */
            using collisionFunc = std::function<Action::ID(Object::ID, Object::ID)>;

	        /**
	         * \brief 
	         * \param still 
	         * \param toMove 
	         * \return 
	         */
	        static ActionID RectangleCollisionVec(Object::ID still, Object::ID toMove);

	        /**
	         * \brief 
	         * \param still 
	         * \param toMove 
	         * \return 
	         */
	        static ActionID CircleCollisionVec(Object::ID still, Object::ID toMove);

	        /**
	         * \brief 
	         * \param still 
	         * \param toMove 
	         * \return 
	         */
	        static ActionID CircleToRectCollisionVec(Object::ID still, Object::ID toMove);

        protected:

	        /**
	         * \brief 
	         * \param self 
	         * \param oponent 
	         * \return 
	         */
	        virtual bool collideWithSameShape(Object* self, Object* oponent);

	        /**
	         * \brief 
	         * \param self 
	         * \param oponent 
	         * \return 
	         */
	        virtual bool collideWithDifferentShape(Object* self, Object* oponent);

	        /**
	         * \brief 
	         * \param self 
	         * \param oponent 
	         * \return 
	         */
	        virtual bool collideWithEdgesDifferentShape(Object* self, Object* oponent);

	        /**
             * \brief 
             */
            collisionFunc onCollision;

	        /**
	         * \brief 
	         * \param e 
	         */
	        Collide(collisionFunc e);
        };
        
    }
}

#endif /* sge_logic_collide_h */
