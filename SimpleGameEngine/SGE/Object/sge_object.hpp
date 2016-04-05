#ifndef sge_object_h
#define sge_object_h

#include "../ID/sge_id.hpp"

namespace SGE {
    
    class Object{
		
	public:
		class ID: public SGE::ID{
			Object* obj;
		public:
			ID(Object* o) : obj(o){
			}
		}
	
		virtual void update()=0;
		virtual void draw()=0;
    };
    
}

#endif /* sge_object_h */