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
        
        class Collide : public Logic{
        public:
            using collisionFunc = std::function<Action::ID(Object::ID, Object::ID)>;

	        static ActionID RectangleCollisionVec(Object::ID still, Object::ID toMove);

	        static ActionID CircleCollisionVec(Object::ID still, Object::ID toMove);

	        static ActionID CircleToRectCollisionVec(Object::ID still, Object::ID toMove);

        protected:

	        virtual bool collideWithSameShape(Object* self, Object* oponent);

	        virtual bool collideWithDifferentShape(Object* self, Object* oponent);

	        virtual bool collideWithEdgesDifferentShape(Object* self, Object* oponent);

            collisionFunc onCollision;
            
            Collide(collisionFunc e) : Logic(Priority::Highest), onCollision(e) {
                ;
            }
            
        };
        
    }
}

#endif /* sge_logic_collide_h */
