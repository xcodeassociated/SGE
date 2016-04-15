#ifndef sge_reactive_h
#define sge_reactive_h

#include "../sge_object.hpp"

namespace SGE {
    
    class Reactive : public Object{
    protected:
        double lifeTime = 0;
        std::string texture_path;
        
    public:
        Reactive(std::string s) : texture_path(s) {
            ;
        }
        
        virtual const std::string& getPath(void) const noexcept final {
            return this->getPath();
        }
    };
    
}

#endif /* sge_reactive_h */