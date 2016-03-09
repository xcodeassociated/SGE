//
//  main.cpp
//  SimpleGameEngine_xc_1
//
//  Created by Hamashy on 16.10.2015.
//  Copyright © 2015 Hamashy. All rights reserved.
//

#include <iostream>

#include "MainGameWindow.hpp"

std::function<void(void)> game = []{
    float gameBox[] = {SCREEN_WIDTH, SCREEN_HEIGHT};
    
    MainGameWindow* mainWindow = new MainGameWindow(gameBox[0], gameBox[1]);
    mainWindow->init();
    mainWindow->show();
    
    mainWindow->run();
    
    delete mainWindow;
    
};

int main(int argc, char * argv[]) {
    std::cout.setf(std::ios::boolalpha);

    std::cout << ">>    Game started!" << std::endl << std::endl;
    
    //run game
	game();
    
    std::cout << std::endl << ">>    Game exit!" << std::endl;
    return 0;
}
