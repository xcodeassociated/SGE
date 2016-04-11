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

#include "../SimpleGameEngine/SGE/Action/Actions/sge_action_move.hpp"

/* ===================================================================================== */

std::function<void(void)> nonSGE = []{
    float gameBox[] = { SCREEN_WIDTH, SCREEN_HEIGHT };
    MainGameWindow* mainWindow = new MainGameWindow(gameBox[0], gameBox[1]);

    mainWindow->init();
    mainWindow->show();

    mainWindow->run();
    delete mainWindow;
};

/* ===================================================================================== */


class MainScene : public SGE::Scene{
    SGE::ObjectManager* manager = nullptr;
    
public:
    MainScene(SGE::ObjectManager* _manager) : manager(_manager) {
        
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
        ;
	}
    
	void onDraw()
	{
        //debug only:
        std::cerr << "onDraw!" << std::endl;
        
        /*
            so we, can also add an action here, just before the game loop starts.
         */
        SGE::Action* move = new SGE::ACTION::Move;
        move->setObjectManager(this->manager->getActionHandler());
        this->manager->addAction(move);

	}
};

int main(int argc, char * argv[]) {
    std::cout.setf(std::ios::boolalpha);

	SGE::Director* director = SGE::Director::getDirector(1024,768);
	SGE::ObjectManager* manager = SGE::ObjectManager::getManager();

	SGE::Scene::ID S1 = director->addScene(new MainScene(manager));

        /*
            look... we are able to perform an action on objects without any scene loaded.
            so we can move object, setting up the scene objects and so on... in the background.
         
            we need to be able to get action id! >>> SGE::Action::ID <<<
         */
        SGE::Action* move = new SGE::ACTION::Move;
        move->setObjectManager(manager->getActionHandler());
        manager->addAction(move);
    
    
	director->showScene(S1);
    
        std::string t;
        std::getline(std::cin, t);

	director->deleteScene(S1);
	
	manager->finalize();
	director->finalize();

    return 0;
}
