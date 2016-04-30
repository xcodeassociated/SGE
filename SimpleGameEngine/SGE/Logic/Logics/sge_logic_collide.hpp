//
//  sge_logic_collide.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 15/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_logic_collide_h
#define sge_logic_collide_h

#include "../sge_logic.hpp"

namespace SGE {
    class Object;
    class ObjectID;
    
    namespace Logics{
        
        class Collide : public Logic{
        public:
            using collisionFunc = std::function<Action::ID(Object::ID, Object::ID)>;

        protected:
            
            virtual bool collideWithSameShape(Object* self, Object* oponent){
                
                ShapeType commonShape = self->getShape()->getType();
                
                switch (commonShape){
                    case ShapeType::Circle:{
                        
                    }break;
                        
                    case ShapeType::Rectangle:{
                        
                    }break;

					case ShapeType::None:
					{
						return false;
					}
                }
                
                return 0;
            }
            
            virtual bool collideWithDifferentShape(Object* self, Object* oponent){
                
                ShapeType selfShapeType = self->getShape()->getType();
                ShapeType oponentShapeType = oponent->getShape()->getType();
                
                if (selfShapeType == ShapeType::None || oponentShapeType == ShapeType::None)
                    return false;
                
                if ((selfShapeType == ShapeType::Circle && oponentShapeType == ShapeType::Rectangle) || (selfShapeType == ShapeType::Rectangle && oponentShapeType == ShapeType::Circle))
                {
                    
                    
                }
                return false;
            }
            
            collisionFunc onCollision;
            
            Collide(collisionFunc e) : Logic(Priority::Highest), onCollision(e) {
                ;
            }
            
        };
        
    }
}

#endif /* sge_logic_collide_h */
