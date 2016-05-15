#ifndef sge_reactive_h
#define sge_reactive_h

#include "../sge_object.hpp"

namespace SGE {
    
    class Reactive : public Object{
    protected:
        double lifeTime = 0;
        
    public:
        using Object::Object;
        
    };
    
}

#endif /* sge_reactive_h */
