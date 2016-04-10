//
//  main.cpp
//  ZombieGame
//
//  Created by Hamashy on 13.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#include <iostream>

#include "MainGameWindow.hpp"

#include "../SimpleGameEngine/SGE/SGE.hpp"

std::function<void(void)> game = []{
    
};

int main(int argc, char * argv[]) {
    std::cout.setf(std::ios::boolalpha);

	SGE::Director* director = SGE::Director::getDirector();
	SGE::ObjectManager* manager = SGE::ObjectManager::getManager();

		float gameBox[] = { SCREEN_WIDTH, SCREEN_HEIGHT };
		MainGameWindow* mainWindow = new MainGameWindow(gameBox[0], gameBox[1]);

	SGE::Scene::ID S1 = director->addScene(new SGE::Scene);

	manager->_init([mainWindow]() {
		mainWindow->init();
		mainWindow->show();
	});

	manager->_play([mainWindow]() {
		mainWindow->run();
		//delete mainWindow;
	});
    //game();
    
    return 0;
}
