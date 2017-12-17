//
//  main.cpp
//  ZombieGame
//
//  Created by Hamashy on 13.02.2016.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#include <iostream>
#include <thread>
#include <set>
#include <ctime>
#include <fstream>
#include <random>    

#include "SGE.hpp"

class MainScene : public SGE::Scene
{
    SGE::Game* game = nullptr;
    
public:
    MainScene(SGE::Game* game) : game(game)
	{
        
		std::string path = PATH"ZombieGame/Levels/level1.txt";
		std::map<char, std::string> mask = {
			{'R', PATH"ZombieGame/Resources/Textures/red_bricks.png"},
			{'B', PATH"ZombieGame/Resources/Textures/red_bricks.png"},
			{'G', PATH"ZombieGame/Resources/Textures/glass.png"},
			{'L', PATH"ZombieGame/Resources/Textures/light_bricks.png"}
        };

		this->loadLevel(path.c_str(), mask);
	}

    ~MainScene()
    {
        std::cout << "~MainScene" << std::endl;
    }

	void finalize() override
	{
	}
    
	void onDraw() override
	{
	}
};

class GOTO : public SGE::Action
{
    SGE::Object* object = nullptr;

public:
    GOTO(SGE::Object* object) : Action(true), object(object)
	{
	}

    virtual void action_begin() noexcept override
    {
    }
    
    virtual void action_main() noexcept override
    {
		this->object->setPosition(200, 200);
		//NOTE: we don't want this action to be active forever
		this->active = false;
	}

	virtual void action_ends() noexcept override
	{
	}

    virtual std::vector<SGE::Object*> getObjects() const override
    {
        return std::vector<SGE::Object*>{this->object};
    }
};

class TestObject : public SGE::Reactive
{
public:
    TestObject() : SGE::Reactive(64, 64, true, new SGE::Circle(32))
    {
    }

    TestObject(const float x, const float y) : SGE::Reactive(x, y, true, new SGE::Circle(32))
    {
    }
};

SGE::Shape* getCircle()
{
	static SGE::Circle c(32, false);
	return &c;
}

class BiCollider : public SGE::Logic
{
	SGE::Object* player = nullptr;
    SGE::Object* opponent = nullptr;

public:
	BiCollider(SGE::Object* player, SGE::Object* opponent) : Logic(SGE::LogicPriority::Highest), player(player), opponent(opponent)
	{
	}

	virtual void performLogic() override
	{
		SGE::Circle* selfCircle = reinterpret_cast<SGE::Circle*>(this->player->getShape());
		SGE::Circle* oponCircle = reinterpret_cast<SGE::Circle*>(this->opponent->getShape());
		glm::vec2 selfPos = this->player->getPosition();
		glm::vec2 oponPos = this->opponent->getPosition();
		glm::vec2 pen = selfPos - oponPos;
		float distance = glm::length(pen);
		float radiuses = selfCircle->getRadius() + oponCircle->getRadius();

		if (distance < radiuses)
		{
			float move = (radiuses - distance)*0.5;
			pen = glm::normalize(pen)*move;
			this->sendAction(new SGE::ACTION::Move(this->player, pen.x, pen.y, true));
			this->sendAction(new SGE::ACTION::Move(this->opponent, -pen.x,-pen.y, true));
		}
	}
};

class Portal : public SGE::Reactive
{
public:
    using SGE::Reactive::Reactive;

    Portal(float x, float y) : SGE::Reactive(x, y, true, new SGE::Rectangle(64, 64))
    {}
};

class PortalAction : public SGE::Action
{
public:
	PortalAction() : SGE::Action(true)
	{
	}

	virtual void action_begin() override
	{
		std::cout << "portal::begin" << std::endl;
	}

	virtual void action_main() override
	{
        std::cout << "portal::main" << std::endl;
		//NOTE: we DON'T want this action to be active forever -- only when the logic condition form Portal is met
		this->active = false;
	}

	virtual void action_ends() override
	{
		std::cout << "portal::end" << std::endl;
	}

    virtual std::vector<SGE::Object*> getObjects() const override
    {
        return {};
    }

};

class PortalLogic : public SGE::Logics::Collide
{
    SGE::Object* portal = nullptr;
    SGE::Object* player = nullptr;

public:
    PortalLogic(SGE::Object* portal, SGE::Object* player)
            : SGE::Logics::Collide(SGE::LogicPriority::Highest), portal(portal), player(player)
    {
    }

    virtual void performLogic() override
    {
        if (this->collideWithDifferentShape(this->portal, this->player))
        {
            try
            {
                SGE::ACTION::Move* moveAction = dynamic_cast<SGE::ACTION::Move*>(this->CircleToRectCollisionVec(
                        this->portal, this->player));

                this->sendAction(moveAction);
                this->sendAction(new PortalAction);
            }
            catch (const std::bad_cast& exception)
            {
                std::cerr << exception.what() << std::endl;
            }
        }
    }
};

class LogicSwitch : public SGE::Action
{
	SGE::Logic* logic = nullptr;

public:
	LogicSwitch(SGE::Logic* id) : SGE::Action(true), logic(id) {}

	void action_begin() override
	{
	}

	void action_main() override
	{
		logic->toggleOn();
		//NOTE: we want this action to be active forever
	}

	void action_ends() override
	{
	}

    virtual std::vector<SGE::Object*> getObjects() const override
    {
        return {};
    }
};

class Human : public SGE::Being
{
	glm::vec2 velocity = {3.f,0.f};
	unsigned int counter = 1;
	unsigned int maxCount = 0;

public:
	Human(const float x, const float y) : SGE::Being(x, y, true, getCircle())
	{
    }

	Human(const float x, const float y, const unsigned int max) : SGE::Being(x, y, true, getCircle()), maxCount(max)
	{
    }

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
    Human* human = nullptr;
	std::default_random_engine engine;
	std::uniform_real_distribution<float> angle;
	glm::vec2 velocity;

public:
	explicit HumanRandomMovement(Human* human)
            : Logic(SGE::LogicPriority::Mid), human(human), angle(glm::radians(-90.f), glm::radians(90.f))
    {
    }

	virtual void performLogic() override
	{
		this->velocity = this->human->getVelocity();
		if (this->human->getCounter() == 0)
		{
			this->velocity = glm::rotate(this->velocity, this->angle(this->engine));
			this->human->setVelocity(this->velocity);
		}
		this->sendAction(new SGE::ACTION::Move(this->human, velocity.x, velocity.y, true));
	}
};

class SnapCamera : public SGE::Logic
{
	const float speed = 0;
	const SGE::Key up, down, left, right, snapKey;
	bool snapped = true;
	SGE::Object* snapTo = nullptr;
    SGE::Object* object = nullptr;

public:
	SnapCamera(const float speed, const SGE::Key up, const SGE::Key down, const SGE::Key left, const SGE::Key right, const SGE::Key snapKey, SGE::Object* snapTo, SGE::Object* object)
		: Logic(SGE::LogicPriority::Highest), speed(speed), up(up), down(down), left(left), right(right), snapKey(snapKey), snapTo(snapTo), object(object)
    {
    }

	~SnapCamera() = default;

	void performLogic() override
	{
		this->snapped = isPressed(snapKey); //We need to be able to send signals to actions, like sending actions to objects
		glm::vec2 move = {0, 0};
		if(!this->snapped)
		{
			move = this->snapTo->getPosition();
			this->object->setPosition(move.x, move.y); //Replace with action, i.e. GoTo
		}
		else
		{
			if(isPressed(this->up)) move.y += this->speed;
			if(isPressed(this->down)) move.y -= this->speed;
			if(isPressed(this->right)) move.x += this->speed;
			if(isPressed(this->left)) move.x -= this->speed;
			this->sendAction(new SGE::ACTION::Move(this->object, move.x, move.y, true));
		}
	}
};

class MouseClickedAction : public SGE::Action
{
    SGE::MouseObject* mouseObject = nullptr;
    SGE::Object* player = nullptr;

public:
    MouseClickedAction(SGE::MouseObject* mouseObject, SGE::Object* player)
            : Action(true), mouseObject(mouseObject), player(player)
	{
	}
    
    virtual void action_begin() noexcept override
	{
	}

    virtual void action_ends() noexcept override
	{
	}
    
    virtual void action_main() noexcept override
    {
        glm::vec2 coords = this->mouseObject->getMouseCoords();
        SGE::Game* game = SGE::Game::getGame();
        SGE::Camera2d* cam = game->getCamera();
        glm::vec2 worldCoords = SGE::screenToWorld(coords, cam->getPosition(), (double)cam->getScale());

		std::cout << "[Clicked] - x: " << worldCoords.x << ", y: " << worldCoords.y << std::endl;
		std::cout << "[Player ] - x: " << this->player->getX() << ", y: " << this->player->getY() << std::endl;

		//NOTE: we want this action to be active forever
    }

    virtual std::vector<SGE::Object*> getObjects() const override
    {
        return std::vector<SGE::Object*>{this->player, this->mouseObject};
    }
};

int main(int argc, char * argv[])
{
    std::cout.setf(std::ios::boolalpha);
    std::cout.sync_with_stdio(true);

	SGE::Director* director = SGE::Director::getDirector(1024, 768);
	SGE::Game* game = SGE::Game::getGame();
	game->bindDirector(director);
	game->init(60);

	SGE::Camera2d* camera = game->getCamera();
	SGE::MouseObject* mouse = game->getMouse();

	SGE::Scene* S1 = director->addScene(new MainScene(game));

	SGE::Object* testObj0 = new TestObject;
    SGE::Object* testObj1 = new TestObject(200, 200);
    game->textureObject(testObj0, PATH"ZombieGame/Resources/Textures/circle.png");
    game->textureObject(testObj1, PATH"ZombieGame/Resources/Textures/circle.png");
	S1->addObject(testObj0);
	S1->addObject(testObj1);

    SGE::Action* oW = new SGE::ACTION::Move(testObj0, 0, 4.f, 0);
    SGE::Action* oA = new SGE::ACTION::Move(testObj0, -4.f, 0, 0);
    SGE::Action* oS = new SGE::ACTION::Move(testObj0, 0, -4.f, 0);
    SGE::Action* oD = new SGE::ACTION::Move(testObj0, 4.f, 0, 0);

    SGE::InputBinder tb0(oW, SGE::Key::Up);
    SGE::InputBinder tb1(oS, SGE::Key::Down);
    SGE::InputBinder tb2(oA, SGE::Key::Left);
    SGE::InputBinder tb3(oD, SGE::Key::Right);
    
	game->mapAction(tb0);
	game->mapAction(tb1);
	game->mapAction(tb2);
	game->mapAction(tb3);

    SGE::Action* click = new MouseClickedAction(mouse, testObj1);
	SGE::InputBinder clickBind(click, SGE::Key::MOUSE_LEFT_BUTTON);
	game->mapAction(clickBind);
    
	auto L1 = new SGE::Logics::PreciseLevelCollider(testObj1, S1->getLevel().getWorld());
	SGE::Action* toggle = new LogicSwitch(L1);
	game->mapAction(SGE::InputBinder(toggle, SGE::Key::O));

	auto L2a = new SGE::Logics::BasicCollider(testObj1, testObj0, &SGE::Logics::Collide::CircleCollisionVec);
	auto L2b = new SGE::Logics::BasicCollider(testObj0, testObj1, &SGE::Logics::Collide::CircleCollisionVec);
	auto L3 = new SGE::Logics::SimpleMove(testObj1, 200.f, SGE::Key::W,SGE::Key::S, SGE::Key::A, SGE::Key::D);

	auto camLogic = new SnapCamera(8, SGE::Key::Up, SGE::Key::Down, SGE::Key::Left, SGE::Key::Right, SGE::Key::Space, testObj1, camera);
	auto camZoom = new SGE::Logics::CameraZoom(camera, 0.1f, 1.f, 0.15f, SGE::Key::Q, SGE::Key::E);

    S1->addLogic(L2a);
    S1->addLogic(L1);
    S1->addLogic(L2b);
	S1->addLogic(L3);
    S1->addLogic(L1);
    S1->addLogic(camLogic);
    S1->addLogic(camZoom);

	auto testTile = &(S1->getLevel().getWorld().front());
	auto moveTileLogic = new SGE::Logics::SimpleMove(testTile, 4.f, SGE::Key::I, SGE::Key::K, SGE::Key::J, SGE::Key::L);
    S1->addLogic(moveTileLogic);

	auto reset = new GOTO(testObj1);
	game->mapAction(SGE::InputBinder(reset, SGE::Key::B));

    std::string path = PATH"ZombieGame/Levels/level1.txt";
    std::vector<std::string> l;
    std::fstream is;
    is.open(path);
    std::string s;
	is >> s;
    while (is >> s)
    {
        l.push_back(s);
    }

    std::pair<int, int> portal_location;
    std::vector<std::pair<float, float>> free;
    int x = 0, y = 0; const int w = 64, h = 64;
    
    for (auto& ee : l)
    {
        for (auto& e : ee)
        {
            if (e == '.')
            {
                free.push_back(std::make_pair(x * w, (y * h) ));
            } else if (e == '*') {
                portal_location = std::make_pair(x * w, (y * h));
            }
            x++;
        }y++;
        x = 0;
    }



    SGE::Object* portal = new Portal(portal_location.first, portal_location.second);
	game->textureObject(portal, PATH"ZombieGame/Resources/Textures/glass.png");
    S1->addObject(portal);

    SGE::Logic* portalLogic = new PortalLogic(portal, testObj1);
    S1->addLogic(portalLogic);


	SGE::Action* portalAction = new PortalAction;
	game->mapAction(SGE::InputBinder(portalAction, SGE::Key::P));


	const int humans = 100;
    srand(time(NULL));

    std::set<int> r;
    for (int i = 0; i < humans; i++)
    {
        int index = rand() % free.size();
        r.insert(index);
    }
    
    std::vector<Human*> humansVec;
    for (const int& e : r)
    {
        std::pair<float, float> pos = free.at(e);
		Human* temp = new Human(pos.first, pos.second, 120);
		game->textureObject(temp, PATH"ZombieGame/Resources/Textures/circle.png");
		S1->addObject(temp);
        humansVec.push_back(temp);
    }

    for (auto human : humansVec)
    {
        S1->addLogic(new HumanRandomMovement(human));
        S1->addLogic(new BiCollider(human, testObj1));
        S1->addLogic(new BiCollider(human, testObj0));
        S1->addLogic(new SGE::Logics::PreciseLevelCollider(human, S1->getLevel().getWorld()));
    }

	

	director->showScene(S1);

    //...

	director->deleteScene(S1);
	
	game->finalize();
	director->finalize();

    return 0;
}
