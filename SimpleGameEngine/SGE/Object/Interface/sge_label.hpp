#ifndef sge_label_h
#define sge_label_h

#include "sge_interface.hpp"

namespace SGE {
    
    class Label : public Interface{
		
	public:
		void setText(const char* text);
		void setFont(); //todo add font type argument
		void setFontSize(); //todo add font size type
    };
    
}

#endif /* sge_label_h */
