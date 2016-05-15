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

//#include "MainGameWindow.hpp"

#include "../SimpleGameEngine/SGE/SGE.hpp"

#include "../SimpleGameEngine/SGE/Action/Actions/sge_action_move.hpp"

/* ===================================================================================== */

//std::function<void(void)> nonSGE = []{
//    float gameBox[] = { SCREEN_WIDTH, SCREEN_HEIGHT };
//    MainGameWindow* mainWindow = new MainGameWindow(gameBox[0], gameBox[1]);
//
//    mainWindow->init();
//    mainWindow->show();
//
//    mainWindow->run();
//    delete mainWindow;
//};

/* ===================================================================================== */


class MainScene : public SGE::Scene{
    SGE::ObjectManager* manager = nullptr;
    
public:
    MainScene(SGE::ObjectManager* _manager) : manager(_manager) {
        
		std::string path = SGE::getPath() + "level1.txt";
		std::map<char, std::string> mask = {
//			{'.',"."},{'Z',"."},{'@',"."},
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
        
        SGE::Action* move = new SGE::ACTION::Move(100, 100, 2);
        move->setActionHandler(this->manager->getActionHandler());
        //SGE::Action::ID a1 = this->manager->addAction(move);

	}
};

class Sig : public SGE::Action
{
public:
    Sig(): Action(0.){};
    ~Sig(){};
    virtual void action_begin(SGE::Object*) noexcept override{}
    virtual void action_ends(SGE::Object*) noexcept override{}
    
    virtual void action_main(SGE::Object*) noexcept override
    {
        std::cout << "collided" << std::endl;
    }
};

class TestObject : public SGE::Reactive {
    
public:
    TestObject() : SGE::Reactive(64,64, true, new SGE::Circle(32)) {}
    TestObject(const float x, const float y) : SGE::Reactive(x,y, true, new SGE::Circle(32)) {}
    
    ~TestObject() {}
};

int main(int argc, char * argv[]) {
    std::cout.setf(std::ios::boolalpha);
    std::cout.sync_with_stdio(0);

//	SGE::Rectangle* tile = (SGE::Rectangle*)(SGE::getBaseTileShape());
//	tile->setHeight(256); //This works nicely
//	tile->setWidth(256);

	SGE::Director* director = SGE::Director::getDirector(1024,768);
	SGE::ObjectManager* manager = SGE::ObjectManager::getManager();
    
	SGE::Scene::ID S1 = director->addScene(new MainScene(manager));
    
    SGE::Object::ID camID = manager->getCameraID();
    
    SGE::Action::ID AW = manager->addAction(new SGE::ACTION::Move(0, 1000.f, 0));
    SGE::Action::ID AA = manager->addAction(new SGE::ACTION::Move(-1000.f, 0, 0));
    SGE::Action::ID AS = manager->addAction(new SGE::ACTION::Move(0, -1000.f, 0));
    SGE::Action::ID AD = manager->addAction(new SGE::ACTION::Move(1000.f, 0, 0));
    
    SGE::ActionBinder B1(camID, AW, SGE::Key::W);
    SGE::ActionBinder B2(camID, AS, SGE::Key::S);
    SGE::ActionBinder B3(camID, AA, SGE::Key::A);
    SGE::ActionBinder B4(camID, AD, SGE::Key::D);

	manager->mapAction(B1);
    manager->mapAction(B2);
    manager->mapAction(B3);
    manager->mapAction(B4);
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    SGE::Object::ID testObj0 = manager->addObject(new TestObject(128,128), S1, PATH"ZombieGame/Resources/Textures/circle.png");
    SGE::Object::ID testObj1 = manager->addObject(new TestObject, S1, PATH"ZombieGame/Resources/Textures/circle.png");
    
    SGE::Action::ID oW = manager->addAction(new SGE::ACTION::Move(0, 4.f, 0));
    SGE::Action::ID oA = manager->addAction(new SGE::ACTION::Move(-4.f, 0, 0));
    SGE::Action::ID oS = manager->addAction(new SGE::ACTION::Move(0, -4.f, 0));
    SGE::Action::ID oD = manager->addAction(new SGE::ACTION::Move(4.f, 0, 0));
    
    SGE::ActionBinder tb0(testObj0, oW, SGE::Key::Up);
    SGE::ActionBinder tb1(testObj0, oS, SGE::Key::Down);
    SGE::ActionBinder tb2(testObj0, oA, SGE::Key::Left);
    SGE::ActionBinder tb3(testObj0, oD, SGE::Key::Right);
    
    manager->mapAction(tb0);
    manager->mapAction(tb1);
    manager->mapAction(tb2);
    manager->mapAction(tb3);
    
    SGE::Action::ID Signal = manager->addAction(new Sig());
    
    auto L1 = manager->addLogic(new SGE::Logics::BasicLevelCollider(manager->getScenePtr(S1)->getLevel().getWorld(),&SGE::Logics::Collide::CircleToRectCollisionVec));
    auto L2 = manager->addLogic(new SGE::Logics::BasicCollider(testObj1,&SGE::Logics::Collide::CircleCollisionVec));

    director->addLogicBinder(S1, testObj0, L1);
    director->addLogicBinder(S1, testObj0, L2);
    
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    
	director->showScene(S1);
    
        std::string t;
        std::getline(std::cin, t);

	director->deleteScene(S1);
	
	manager->finalize();
	director->finalize();

    return 0;
}
