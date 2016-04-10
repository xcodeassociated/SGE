#ifndef sge_background_element_h
#define sge_background_element_h

#include "../Object/sge_object.hpp"
#include "../TextureLoader/sge_glTexture.hpp"

namespace SGE {
    
    class BackgroundElement : public Object{
	protected:
		std::string path;

	public:
		BackgroundElement(std::string path): path(path)
		{
		}

		const std::string& getPath() const
		{
			return this->path;
		}
    };
    
}

#endif /* sge_background_element_h */