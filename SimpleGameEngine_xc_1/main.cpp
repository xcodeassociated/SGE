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

std::function<void(void)> game = []{
    
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
    
    delete mainWindow;
    
};

int main(int argc, char * argv[]) {
    std::cout.setf(std::ios::boolalpha);

    std::cout << ">>    Game started!" << std::endl << std::endl;
    
    //socket.io - "make instance" test...
    std::cout << ">>    Socket.IO > test: " << std::endl;
    sio::client* s = new sio::client();
    delete s;
    std::cout << std::endl;
    
    //run game
    game();
    
    
    std::cout << std::endl << ">>    Game exit!" << std::endl;
    return 0;
}

/**
 
TODO:
    
    >>  With the singleton class memory management the ARC is required! - early implement try..

*/