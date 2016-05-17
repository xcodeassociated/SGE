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

bool isPressed(SGE::Key key)
{
	static const Uint8* const state = SDL_GetKeyboardState(nullptr);
	return state[SDL_GetScancodeFromKey(SDL_Keycode(key))];
}

class SimpleMove : public SGE::Logic
{
	const float speed = 0;
	const SGE::Key up, down, left, right;
public:
	SimpleMove(const float speed, const SGE::Key up, const SGE::Key down, const SGE::Key left, const SGE::Key right)
		:Logic(SGE::LogicPriority::Highest), speed(speed), up(up), down(down), left(left), right(right){}
	~SimpleMove() = default;

	void performLogic(SGE::Object::ID obj) override
	{
		glm::vec2 move = { 0,0 };
		if(isPressed(this->up)) move.y+= this->speed;
		if(isPressed(this->down)) move.y -= this->speed;
		if(isPressed(this->right)) move.x += this->speed;
		if(isPressed(this->left)) move.x -= this->speed;
		this->sendAction(obj, SGE::Action::ID(0, new SGE::ACTION::Move(move.x, move.y, 0)));
	}
};

class SnapCamera : public SGE::Logic
{
	const float speed = 0;
	const SGE::Key up, down, left, right, snapKey;
	bool snapped = true;
	SGE::Object::ID snapTo;
public:
	SnapCamera(const float speed, const SGE::Key up, const SGE::Key down, const SGE::Key left, const SGE::Key right, const SGE::Key snapKey, SGE::Object::ID snapTo)
		:Logic(SGE::LogicPriority::Highest), speed(speed), up(up), down(down), left(left), right(right), snapKey(snapKey) ,snapTo(snapTo){}
	~SnapCamera() = default;

	void performLogic(SGE::Object::ID obj) override
	{
		this->snapped = isPressed(snapKey); //We need to be able to send signals to actions, like sending actions to objects
		glm::vec2 move = { 0,0 };
		if(!this->snapped)
		{
			move = this->snapTo.getObject()->getPosition();
			obj.getObject()->setPosition(move.x, move.y); //Replace with action, i.e. GoTo
		}
		else
		{
			if(isPressed(this->up)) move.y += this->speed;
			if(isPressed(this->down)) move.y -= this->speed;
			if(isPressed(this->right)) move.x += this->speed;
			if(isPressed(this->left)) move.x -= this->speed;
			this->sendAction(obj, SGE::Action::ID(0, new SGE::ACTION::Move(move.x, move.y, 0)));
		}
	}
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
        
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    SGE::Object::ID testObj0 = manager->addObject(new TestObject(128,64), S1, PATH"ZombieGame/Resources/Textures/circle.png");
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
        
    auto L1 = manager->addLogic(new SGE::Logics::BasicLevelCollider(manager->getScenePtr(S1)->getLevel().getWorld(), &SGE::Logics::Collide::CircleToRectCollisionVec));
    auto L2a = manager->addLogic(new SGE::Logics::BasicCollider(testObj1, &SGE::Logics::Collide::CircleCollisionVec));
	auto L2b = manager->addLogic(new SGE::Logics::BasicCollider(testObj0, &SGE::Logics::Collide::CircleCollisionVec));
	auto L3 = manager->addLogic(new SimpleMove(4.f,SGE::Key::W,SGE::Key::S, SGE::Key::A, SGE::Key::D));

	auto camLogic = manager->addLogic(new SnapCamera(8, SGE::Key::Up, SGE::Key::Down, SGE::Key::Left, SGE::Key::Right, SGE::Key::Space, testObj1));

    director->addLogicBinder(S1, testObj0, L2a);
	director->addLogicBinder(S1, testObj1, L2b);
	director->addLogicBinder(S1, testObj1, L3);
	director->addLogicBinder(S1, testObj0, L1);
	director->addLogicBinder(S1, testObj1, L1);
	director->addLogicBinder(S1, camID, camLogic);
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    
	director->showScene(S1);
    
        std::string t;
        std::getline(std::cin, t);

	director->deleteScene(S1);
	
	manager->finalize();
	director->finalize();

    return 0;
}
