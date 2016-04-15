//
//  sge_logic.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 15/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_logic_h
#define sge_logic_h

namespace SGE {
    
    class Logic{
    protected:
        bool isOn;
        
    public:
        
        virtual void performLogic(void) = 0;
        
        virtual void setOn(bool e) final {
            this->isOn = e;
        }
        
        virtual bool getOn(void) final {
            return this->isOn;
        }
        
        virtual ~Logic() = 0;
        
    };
    
}


#endif /* sge_logic_h */
