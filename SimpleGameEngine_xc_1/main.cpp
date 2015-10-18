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
    sprite0->init(-1.0f, -1.0f, 1.0f, 1.0f,
                  "/Users/Hamashy/Desktop/GameEngine.repo/SimpleGameEngine_xc_1/Resources/jimmyJump_pack/PNG/CharacterRight_Standing.png");
    
    SGE::Sprite* sprite1 = new SGE::Sprite();
    sprite1->init(0.f, 0.f, 1.0f, 1.0f,
                  "/Users/Hamashy/Desktop/GameEngine.repo/SimpleGameEngine_xc_1/Resources/jimmyJump_pack/PNG/CharacterRight_Standing.png");
    
    mainWindow->addSprite(sprite0, 0);
    mainWindow->addSprite(sprite1, 1);

    
    mainWindow->run();
    
    
    std::getchar();
    delete mainWindow; 
    
    return 0;
}

/**
 
TODO:
    
    >>  With the singleton class memory management the ARC is required! - early implement try..

*/