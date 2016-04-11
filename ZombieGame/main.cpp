//
//  main.cpp
//  ZombieGame
//
//  Created by Hamashy on 13.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#include <iostream>
#include <thread>
#include <chrono>

#include "MainGameWindow.hpp"

#include "../SimpleGameEngine/SGE/SGE.hpp"

std::function<void(void)> game = []{
    
};

class MainScene :public SGE::Scene
{
public:
	MainScene() {
		std::string path = SGE::getPath() + "level1.txt";
		std::map<char, std::string> mask = {
			{'.',"."},{'Z',"."},{'@',"."},
			{'R',PATH"ZombieGame/Resources/Textures/red_bricks.png"},
			{'B',PATH"ZombieGame/Resources/Textures/red_bricks.png"},
			{'G',PATH"ZombieGame/Resources/Textures/glass.png"},
			{'L',PATH"ZombieGame/Resources/Textures/light_bricks.png"} };

		this->loadLevel(path.c_str(), mask);
	}

	void finalize()
	{

	}

	void onDraw()
	{

	}
};

int main(int argc, char * argv[]) {
    std::cout.setf(std::ios::boolalpha);

	SGE::Director* director = SGE::Director::getDirector(1024,768);
	SGE::ObjectManager* manager = SGE::ObjectManager::getManager();

//		float gameBox[] = { SCREEN_WIDTH, SCREEN_HEIGHT };
//		MainGameWindow* mainWindow = new MainGameWindow(gameBox[0], gameBox[1]);

	SGE::Scene::ID S1 = director->addScene(new MainScene);

	director->showScene(S1);

	//std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	std::string t;
	std::getline(std::cin, t);

	director->deleteScene(S1);
	
	manager->finalize();
	director->finalize();

/*	manager->_init([mainWindow]() {
		mainWindow->init();
		mainWindow->show();
	});

	manager->_play([mainWindow]() {
		mainWindow->run();
		//delete mainWindow;
	});
    //game();
 */   
    return 0;
}
