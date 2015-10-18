//
//  main.cpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 16.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#include <iostream>

#include "SGE/include/sge_include.hpp"
#include "SGE/MainGameWindow/sge_mainGame.hpp"
#include "SGE/Sprite/sge_sprite.hpp"

int main(int argc, const char * argv[]) {
    
    SGE::MainGameWindow* mainWindow = new SGE::MainGameWindow(1024, 768);
    mainWindow->init();
    mainWindow->show();

    SGE::Sprite* sprite0 = new SGE::Sprite();
    sprite0->init(-0.5f, -0.5f, 1.0f, 1.0f);
    mainWindow->addSprite(sprite0, 0);
    
    mainWindow->run();

    
    
    std::getchar();
    delete mainWindow; 
    
    return 0;
}
