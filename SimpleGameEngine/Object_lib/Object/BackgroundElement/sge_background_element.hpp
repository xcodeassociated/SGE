#ifndef sge_background_element_h
#define sge_background_element_h

#include "sge_object.hpp"
#include <string>

namespace SGE {
    class BackgroundElement : public Object{
	protected:
		std::string path;

	public:
	    BackgroundElement(float x, float y, std::string path);

	    const std::string& getPath() const;
    };
    
}

#endif /* sge_background_element_h */
