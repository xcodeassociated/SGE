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
#include <set>
#include <time.h>
#include <fstream>
#include <random>    

#include "SGE.hpp"
#include "sge_action_move.hpp"
//TODO: check it!!
#include "sge_mouse.hpp" // ??? was comment out!

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Logics/Colliders/sge_logic_collide.hpp"
#include "Logics/Colliders/sge_logic_collide_level_precise.hpp"
#include "Logics/Colliders/sge_logic_collide_basic.hpp"
#include "Logics/Movers/sge_logic_move.hpp"
#include "Logics/Camera/sge_logic_camera_zoom.hpp"
#include <sge_macro.hpp>

class MainScene : public SGE::Scene{
    SGE::ObjectManager* manager = nullptr;
    
public:
    MainScene(SGE::ObjectManager* _manager) : manager(_manager) {
        
		std::string path = PATH"ZombieGame/Levels/level1.txt";
		std::map<char, std::string> mask = {
			{'R',PATH"ZombieGame/Resources/Textures/red_bricks.png"},
			{'B',PATH"ZombieGame/Resources/Textures/red_bricks.png"},
			{'G',PATH"ZombieGame/Resources/Textures/glass.png"},
			{'L',PATH"ZombieGame/Resources/Textures/light_bricks.png"} };

		this->loadLevel(path.c_str(), mask);
	}

	void finalize() override
	{
        ;
	}
    
	void onDraw() override
	{
        //debug only:
        std::cerr << "onDraw!" << std::endl;
        
        SGE::Action* move = new SGE::ACTION::Move(100, 100, 2);
        //SGE::Action::ID a1 = this->manager->addAction(move);

	}
};

class GOTO : public SGE::Action
{
public:
    GOTO(): Action(0.){};
    virtual void action_begin(const SGE::ObjectBind& ) noexcept override{}
    virtual void action_ends(const SGE::ObjectBind&) noexcept override{}
    
    virtual void action_main(const SGE::ObjectBind& b) noexcept override
    {
		b[0]->setPosition(200, 200);
    }
};

class TestObject : public SGE::Reactive {
    
public:
    TestObject() : SGE::Reactive(64,64, true, new SGE::Circle(32)) {}
    TestObject(const float x, const float y) : SGE::Reactive(x,y, true, new SGE::Circle(32)) {}
    
    ~TestObject() {}
};

SGE::Shape* getCircle()
{
	static SGE::Circle c(32, false);
	return &c;
}

class BiCollider : public SGE::Logic
{
	SGE::Object::ID player;
public:
	BiCollider(SGE::Object::ID player) : Logic(SGE::LogicPriority::Highest), player(player) {}

	void performLogic(const SGE::ObjectBind& obj) override
	{
		SGE::Circle* selfCircle = reinterpret_cast<SGE::Circle*>(player.getObject()->getShape());
		SGE::Circle* oponCircle = reinterpret_cast<SGE::Circle*>(obj[0].getObject()->getShape());
		glm::vec2 selfPos = player.getObject()->getPosition();
		glm::vec2 oponPos = obj[0].getObject()->getPosition();
		glm::vec2 pen = selfPos - oponPos;
		float distance = glm::length(pen);
		float radiuses = selfCircle->getRadius() + oponCircle->getRadius();
		if (distance < radiuses)
		{
			float move = (radiuses - distance)*0.5;
			pen = glm::normalize(pen)*move;
			this->sendAction(player, SGE::Action::ID(new SGE::ACTION::Move(pen.x, pen.y, 0)));
			this->sendAction(obj[0], SGE::Action::ID(new SGE::ACTION::Move(-pen.x,-pen.y,0)));
		}
	}
};

class LogicSwitch : public SGE::Action {
private:
	SGE::Logic::ID logic;

public:
	LogicSwitch(SGE::Logic::ID id) : logic(id) {}

	void action_begin(const SGE::ObjectBind&) override {

	}
	
	void action_main(const SGE::ObjectBind&) override {
		logic->toggleOn();
	}
	
	void action_ends(const SGE::ObjectBind&) override {

	}
};

class Human : public SGE::Being
{
	glm::vec2 velocity = {3.f,0.f};
	unsigned int counter = 1;
	unsigned int maxCount = 0;
public:
	Human(const float x, const float y) : Being(x,y,true,getCircle())
	{}
	Human(const float x, const float y, const unsigned int max) : Being(x, y, true, getCircle()), maxCount(max)
	{}

	void setMaxCount(const unsigned int max)
	{
		this->maxCount = max;
	}

	unsigned int getCounter()
	{
		if (this->counter) return --this->counter;
		else return (this->counter = this->maxCount);
	}

	glm::vec2 getVelocity() const
	{
		return this->velocity;
	}

	void setVelocity(const glm::vec2 vel)
	{
		this->velocity = vel;
	}
};

class HumanRandomMovement : public SGE::Logic
{
	std::default_random_engine engine;
	std::uniform_real_distribution<float> angle;
	float speed;
	glm::vec2 velocity;
public:
	HumanRandomMovement() :Logic(SGE::LogicPriority::Mid), angle(glm::radians(-90.f), glm::radians(90.f)) {}

	void performLogic(const SGE::ObjectBind& humanID) override
	{
		
		auto human = reinterpret_cast<Human*>(humanID[0].getObject());
		velocity = human->getVelocity();
		if (human->getCounter() == 0)
		{
//			std::cout << velocity.x << ' ' << velocity.y << " | ";
			velocity = glm::rotate(velocity,angle(engine));
			human->setVelocity(velocity);
//			std::cout << velocity.x << ' ' << velocity.y << std::endl;
		}
		this->sendAction(humanID[0], SGE::ActionID(new SGE::ACTION::Move(velocity.x, velocity.y,0)));
		//human->setPosition(human->getX()+velocity.x, human->getY()+velocity.y);
	}
};

class DynamicVectorLogic : public SGE::Logic
{
	std::vector<SGE::Object::ID>& vec;
	SGE::Logic* logic;
public:
	DynamicVectorLogic(std::vector<SGE::Object::ID>& vector, SGE::Logic* logic): Logic(logic->getPriority()), vec(vector), logic(logic)
	{}

	void performLogic(const SGE::ObjectBind&) override
	{
		for (size_t i = 0; i < vec.size(); ++i)
		{
			logic->performLogic(vec[i]);
		}
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

	void performLogic(const SGE::ObjectBind& obj) override
	{
		this->snapped = isPressed(snapKey); //We need to be able to send signals to actions, like sending actions to objects
		glm::vec2 move = { 0,0 };
		if(!this->snapped)
		{
			move = this->snapTo.getObject()->getPosition();
			obj[0].getObject()->setPosition(move.x, move.y); //Replace with action, i.e. GoTo
		}
		else
		{
			if(isPressed(this->up)) move.y += this->speed;
			if(isPressed(this->down)) move.y -= this->speed;
			if(isPressed(this->right)) move.x += this->speed;
			if(isPressed(this->left)) move.x -= this->speed;
			this->sendAction(obj[0], SGE::Action::ID(new SGE::ACTION::Move(move.x, move.y, 0)));
		}
	}
};

class MouseClickedAction : public SGE::Action {
public:
    MouseClickedAction(): Action(0.f){};
    
    virtual void action_begin(const SGE::ObjectBind&) noexcept override{}
    virtual void action_ends(const SGE::ObjectBind&) noexcept override{}
    
    virtual void action_main(const SGE::ObjectBind& b) noexcept override{
		//assert((n - o) == 2);
		SGE::MouseObject* mouse = dynamic_cast<SGE::MouseObject*>(b[0].getObject());
		SGE::Object* p = b[1].getObject();
        glm::vec2 coords = mouse->getMouseCoords();
        SGE::ObjectManager* manager = SGE::ObjectManager::getManager();
        SGE::Camera2d* cam = dynamic_cast<SGE::Camera2d*>(manager->getCameraID().getObject());
        glm::vec2 worldCoords = SGE::screenToWorld(cam->getPosition(), coords, (double)cam->getScale());
		std::cout << "[Clicked] - x: " << worldCoords.x << ", y: " << worldCoords.y << std::endl;
		std::cout << "[Player ] - x: " << p->getX() << ", y: " << p->getY() << std::endl; //print out mouse click event - but not in a world coords.
    }
};

int main(int argc, char * argv[]) {
    std::cout.setf(std::ios::boolalpha);
    std::cout.sync_with_stdio(false);

	SGE::Director* director = SGE::Director::getDirector(1024,768);
	SGE::ObjectManager* manager = SGE::ObjectManager::getManager();
    
	SGE::Scene::ID S1 = director->addScene(new MainScene(manager));
    
    SGE::Object::ID camID = manager->getCameraID();
    SGE::Object::ID mouseID = manager->getMouse();
    
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    SGE::Object::ID testObj0 = manager->addObject(new TestObject, S1, PATH"ZombieGame/Resources/Textures/circle.png");
    SGE::Object::ID testObj1 = manager->addObject(new TestObject(200,200), S1, PATH"ZombieGame/Resources/Textures/circle.png");
    
    SGE::Action::ID oW = manager->addAction(new SGE::ACTION::Move(0, 4.f, 0));
    SGE::Action::ID oA = manager->addAction(new SGE::ACTION::Move(-4.f, 0, 0));
    SGE::Action::ID oS = manager->addAction(new SGE::ACTION::Move(0, -4.f, 0));
    SGE::Action::ID oD = manager->addAction(new SGE::ACTION::Move(4.f, 0, 0));

    SGE::InputBinder tb0(testObj0, oW, SGE::Key::Up);
    SGE::InputBinder tb1(testObj0, oS, SGE::Key::Down);
    SGE::InputBinder tb2(testObj0, oA, SGE::Key::Left);
    SGE::InputBinder tb3(testObj0, oD, SGE::Key::Right);
    
	manager->mapAction(tb0);
	manager->mapAction(tb1);
	manager->mapAction(tb2);
	manager->mapAction(tb3);



    //add mouse click action to the game (on camera object)
    SGE::Action::ID click = manager->addAction(new MouseClickedAction);
	SGE::InputBinder clickBind({ mouseID,testObj1 }, click, SGE::Key::MOUSE_LEFT_BUTTON);
    manager->mapAction(clickBind);
    
    //auto L1 = manager->addLogic(new SGE::Logics::BasicLevelCollider(manager->getScenePtr(S1)->getLevel().getWorld(), &SGE::Logics::Collide::CircleToRectCollisionVec));
	auto L1 = manager->addLogic(new SGE::Logics::PreciseLevelCollider(manager->getScenePtr(S1)->getLevel().getWorld()));
	SGE::Action::ID toggle = manager->addAction(new LogicSwitch(L1));
	SGE::Object::ID cto = manager->addObject(new SGE::VoidObject());
	manager->mapAction(SGE::InputBinder(cto,toggle,SGE::Key::O));

	auto L2a = manager->addLogic(new SGE::Logics::BasicCollider(testObj1, &SGE::Logics::Collide::CircleCollisionVec));
	auto L2b = manager->addLogic(new SGE::Logics::BasicCollider(testObj0, &SGE::Logics::Collide::CircleCollisionVec));
	auto L3 = manager->addLogic(new SGE::Logics::SimpleMove(4.f,SGE::Key::W,SGE::Key::S, SGE::Key::A, SGE::Key::D));


	auto camLogic = manager->addLogic(new SnapCamera(8, SGE::Key::Up, SGE::Key::Down, SGE::Key::Left, SGE::Key::Right, SGE::Key::Space, testObj1));
	auto camZoom = manager->addLogic(new SGE::Logics::CameraZoom(0.1f,1.f,0.15f,SGE::Key::Q, SGE::Key::E));

    director->addLogicBinder(S1, testObj0, L2a);
	director->addLogicBinder(S1, testObj1, L2b);
	director->addLogicBinder(S1, testObj1, L3);
	director->addLogicBinder(S1, testObj0, L1);
	director->addLogicBinder(S1, testObj1, L1);
	director->addLogicBinder(S1, camID, camLogic);
	director->addLogicBinder(S1, camID, camZoom);

    //Testing collisions - move tile to create space too tight for circle to enter.
	auto testTile = SGE::Object::ID(&(manager->getScenePtr(S1)->getLevel().getWorld().front()));
	auto moveTile = manager->addLogic(new SGE::Logics::SimpleMove(4.f, SGE::Key::I, SGE::Key::K, SGE::Key::J, SGE::Key::L));
	director->addLogicBinder(S1, testTile, moveTile);

	auto reset = manager->addAction(new GOTO());
	manager->mapAction(SGE::InputBinder(testObj1, reset, SGE::Key::B));

	// !Testing collisions
    std::string path = PATH"ZombieGame/Levels/level1.txt";
    std::vector<std::string> l;
    std::fstream is;
    is.open(path);
    std::string s;
	is >> s;
    while (is >> s){
        l.push_back(s);
    }
    
    std::vector<std::pair<float, float>> free;
    
    int x = 0, y = 0; const int w = 64, h = 64;
    
    for (auto& ee : l){
        for (auto& e : ee){
            if (e == '.'){
                free.push_back(std::make_pair(x * w, (y * h) ));
            }x++;
        }y++;
        x = 0;
    }
    
    const int humans = 100;
    srand(time(NULL));

    std::set<int> r;
    for (int i = 0; i < humans; i++){
        int index = rand() % free.size();
        r.insert(index);
        std::cout << index << std::endl;
    }
    
    std::vector<SGE::Object::ID> humans_id;
    for (const int& e : r){
        std::pair<float, float> pos = free.at(e);
        SGE::Object::ID temp = manager->addObject(new Human(pos.first, pos.second,120), S1, PATH"ZombieGame/Resources/Textures/circle.png");
        humans_id.push_back(temp);
       
        std::cout << free.at(e).first << ", " << free.at(e).second << std::endl;
    }

	auto MoveHumans = manager->addLogic(new DynamicVectorLogic(humans_id,new HumanRandomMovement()));
	auto CollideLevelHumans = manager->addLogic(new DynamicVectorLogic(humans_id,manager->getLogicPtr(L1)));
	auto CollidePlayer = manager->addLogic(new DynamicVectorLogic(humans_id, new BiCollider(testObj1)));

	director->addLogicBinder(S1, testObj0, MoveHumans);
	director->addLogicBinder(S1, testObj0, CollidePlayer);
	director->addLogicBinder(S1, testObj0, CollideLevelHumans);
	

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

	director->showScene(S1);
    
        std::string t;
        std::getline(std::cin, t);

	director->deleteScene(S1);
	
	manager->finalize();
	director->finalize();

    return 0;
}
