//
//  main.cpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 16.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#include <iostream>

#include "SGE/include/SGE_include.hpp"
#include "SGE/MainGameWindow/MainGameWindow.hpp"

int main(int argc, const char * argv[]) {
    
    SGE::MainGameWindow* mainWindow = new SGE::MainGameWindow();
    mainWindow->init();
    mainWindow->show();
    mainWindow->gameLoop();
    
    std::getchar();
    delete mainWindow;
    
    return 0;
}
