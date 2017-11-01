#ifndef sge_background_element_h
#define sge_background_element_h

#include "sge_object.hpp"
#include <string>

namespace SGE {
	/**
     * \brief 
     */
    class BackgroundElement : public Object{
	protected:
	    /**
		 * \brief 
		 */
		std::string path;

	public:
	    /**
	     * \brief 
	     * \param x 
	     * \param y 
	     * \param path 
	     */
	    BackgroundElement(float x, float y, std::string path);

	    /**
	     * \brief 
	     * \return 
	     */
	    const std::string& getPath() const;
    };
    
}

#endif /* sge_background_element_h */
