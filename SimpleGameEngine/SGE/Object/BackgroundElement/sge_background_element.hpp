#ifndef sge_background_element_h
#define sge_background_element_h

#include "../sge_object.hpp"

namespace SGE {
	Shape* getBaseTileShape();

    class BackgroundElement : public Object{
	protected:
		std::string path;

	public:
		BackgroundElement(float x,float y,std::string path): Object(x,y,true,getBaseTileShape()), path(path)
		{
		}

		const std::string& getPath() const
		{
			return this->path;
		}
    };
    
}

#endif /* sge_background_element_h */
