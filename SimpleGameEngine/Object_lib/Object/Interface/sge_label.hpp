#ifndef sge_label_h
#define sge_label_h

#include "sge_interface.hpp"

namespace SGE {
    
	/**
     * \brief 
     */
    class Label : public Interface{
		
	public:
	    /**
		 * \brief 
		 * \param text 
		 */
		void setText(const char* text);
	    /**
		 * \brief 
		 */
		void setFont(); //todo add font type argument
	    /**
		 * \brief 
		 */
		void setFontSize(); //todo add font size type
    };
    
}

#endif /* sge_label_h */
