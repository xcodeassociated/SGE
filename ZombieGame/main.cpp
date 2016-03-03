//
//  main.cpp
//  ZombieGame
//
//  Created by Hamashy on 13.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
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
    
    game();
    
    return 0;
}
