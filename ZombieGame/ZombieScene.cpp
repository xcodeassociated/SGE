#include <sge_macro.hpp>
#include "ZombieScene.hpp"
#include "Logics.hpp"
#include "Actions.hpp"
#include <sge_logic_collide_level_precise.hpp>
#include <sge_logic_move.hpp>
#include <sge_logic_camera_zoom.hpp>
#include <sge_input_binder.hpp>
#include <fstream>
#include <set>
#include <functional>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include "Logics/World/sge_worldstep.hpp"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "sge_director.hpp"

void ZListener::BeginContact(b2Contact* contact)
{
	b2Fixture* A = contact->GetFixtureA();
	b2Fixture* B = contact->GetFixtureB();
	if (isCat(A, Category::Human) && isCat(B, Category::ZombieSensor))
	{
		reinterpret_cast<Human*>(B->GetUserData())->getBodies().push_front(reinterpret_cast<Human*>(A->GetUserData()));
	}
	else if (isCat(A, Category::ZombieSensor) && isCat(B, Category::Human))
	{
		reinterpret_cast<Human*>(A->GetUserData())->getBodies().push_front(reinterpret_cast<Human*>(B->GetUserData()));
	}
	else if (isCat(A, Category::Zombie) && isCat(B, Category::HumanSensor))
	{
		reinterpret_cast<Human*>(B->GetUserData())->getBodies().push_front(reinterpret_cast<Human*>(A->GetUserData()));
	}
	else if (isCat(A, Category::HumanSensor) && isCat(B, Category::Zombie))
	{
		reinterpret_cast<Human*>(B->GetUserData())->getBodies().push_front(reinterpret_cast<Human*>(A->GetUserData()));
	}
	else if (isCat(A, Category::Human) && isCat(B, Category::Zombie))
	{
		reinterpret_cast<Human*>(A->GetUserData())->Zombify();
	}
	else if (isCat(A, Category::Zombie) && isCat(B, Category::Human))
	{
		reinterpret_cast<Human*>(B->GetUserData())->Zombify();
	}
}//We really need a better way of texturing objects
void ZListener::EndContact(b2Contact* contact)
{
	b2Fixture* A = contact->GetFixtureA();
	b2Fixture* B = contact->GetFixtureB();
	if (isCat(A, Category::Human) && isCat(B, Category::ZombieSensor))
	{
		reinterpret_cast<Human*>(B->GetUserData())->getBodies().remove(reinterpret_cast<Human*>(A->GetUserData()));
	}
	else if (isCat(A, Category::ZombieSensor) && isCat(B, Category::Human))
	{
		reinterpret_cast<Human*>(A->GetUserData())->getBodies().remove(reinterpret_cast<Human*>(B->GetUserData()));
	}
	else if (isCat(A, Category::Zombie) && isCat(B, Category::HumanSensor))
	{
		reinterpret_cast<Human*>(B->GetUserData())->getBodies().remove(reinterpret_cast<Human*>(A->GetUserData()));
	}
	else if (isCat(A, Category::HumanSensor) && isCat(B, Category::Zombie))
	{
		reinterpret_cast<Human*>(B->GetUserData())->getBodies().remove(reinterpret_cast<Human*>(A->GetUserData()));
	}
}

SGE::GLTexture ZombieScene::zombieTexture;
SGE::GLTexture ZombieScene::deadZombieTexture;
SGE::GLTexture ZombieScene::deadHumanTexture;
b2Filter ZombieScene::zombieFilter;
b2Filter ZombieScene::zombieSensorFilter;
b2Filter ZombieScene::playerFilter;
b2Filter ZombieScene::humanFilter;
b2Filter ZombieScene::humanSensorFilter;
b2CircleShape ZombieScene::sensorShape;
b2FixtureDef ZombieScene::sensorFixture;
b2BodyDef ZombieScene::humanBodyDef;
b2CircleShape ZombieScene::humanShape;
b2PolygonShape ZombieScene::worldShape;
b2BodyDef ZombieScene::worldBodyDef;
b2Filter ZombieScene::worldFilter;

bool ZombieScene::init()
{
	playerFilter.categoryBits = uint16(Category::Player);
	playerFilter.maskBits = Category::Player | Category::Human | Category::Zombie | Category::Level;

	zombieFilter.categoryBits = uint16(Category::Zombie);
	zombieFilter.maskBits = Category::Player | Category::Human | Category::Zombie | Category::Level | Category::HumanSensor;

	zombieSensorFilter.categoryBits = uint16(Category::ZombieSensor);
	zombieSensorFilter.maskBits = uint16(Category::Human);

	humanFilter.categoryBits = uint16(Category::Human);
	humanFilter.maskBits = Category::Player | Category::Human | Category::Zombie | Category::Level | Category::ZombieSensor;

	humanSensorFilter.categoryBits = uint16(Category::HumanSensor);
	humanSensorFilter.maskBits = uint16(Category::Zombie);

	sensorShape.m_p = b2Vec2_zero;
	sensorShape.m_radius = 64.f * 5;

	sensorFixture.isSensor = true;
	sensorFixture.shape = &sensorShape;

	humanBodyDef.fixedRotation = true;
	humanBodyDef.type = b2_dynamicBody;

	humanShape.m_radius = 32;
	humanShape.m_p = b2Vec2_zero;

	worldBodyDef.type = b2_staticBody;
	worldShape.SetAsBox(32, 32);

	worldFilter.categoryBits = uint16(Category::Level);
	worldFilter.maskBits = Category::Player | Category::Human | Category::Zombie;

	return true;
}

void ZombieScene::zombify(Human* human)
{
	++this->zombieCount;
	b2Body* body = human->getBody();
	for(b2Fixture* next = body->GetFixtureList(), *temp = nullptr; next!=nullptr ; next=temp)
	{
		temp = next->GetNext();
		body->DestroyFixture(next);
	}
	human->texture = zombieTexture;
	human->setSpeed(8 * 64.f);
	human->addFixture(sensorFixture)->SetFilterData(zombieSensorFilter);
	human->addFixture(humanShape)->SetFilterData(zombieFilter);
}

ZombieScene::ZombieScene(SGE::Game* game, const char* path) : Box2DScene(b2Vec2_zero), game(game), path(path)
{
	static bool initialized = init();
}

void ZombieScene::loadScene()
{
	this->killCount = 0;
	this->zombieCount = 0;
	std::map<char, std::string> mask = {
		{ 'R', PATH"ZombieGame/Resources/Textures/red_bricks.png" },
		{ 'B', PATH"ZombieGame/Resources/Textures/red_bricks.png" },
		{ 'G', PATH"ZombieGame/Resources/Textures/glass.png" },
		{ 'L', PATH"ZombieGame/Resources/Textures/light_bricks.png" }
	};
	this->Scene::loadLevel(this->path.c_str(), mask);

	for(SGE::WorldElement& e: this->getLevel().getWorld())
	{
		b2Body* body = world.CreateBody(&worldBodyDef);
		body->SetTransform(b2Vec2(e.getX(), e.getY()), 0);
		body->CreateFixture(&worldShape, 0)->SetFilterData(worldFilter);
	}

	SGE::Object* Dummy1 = new Image(-1000, -1000);
	game->textureObject(Dummy1, PATH"ZombieGame/Resources/Textures/deadzombie.png");
	deadZombieTexture = Dummy1->texture;
	this->addObject(Dummy1);
	SGE::Object* Dummy2 = new Image(-1000, -1000);
	game->textureObject(Dummy2, PATH"ZombieGame/Resources/Textures/deadhuman.png");
	deadHumanTexture = Dummy2->texture;
	this->addObject(Dummy2);

	SGE::Camera2d* camera = game->getCamera();
	camera->setScale(0.5f);
	SGE::MouseObject* mouse = game->getMouse();

	Player* player = new Player(200, 200,true,getCircle());

	auto L3 = new SimpleMove(player, 8*10*64.f, SGE::Key::W, SGE::Key::S, SGE::Key::A, SGE::Key::D);

	auto camLogic = new SnapCamera(8, SGE::Key::Up, SGE::Key::Down, SGE::Key::Left, SGE::Key::Right, SGE::Key::O, player, camera);
	auto camZoom = new SGE::Logics::CameraZoom(camera, 0.1f, 1.f, 0.15f, SGE::Key::Q, SGE::Key::E);

	this->addLogic(new SGE::WorldStep(&this->world,2,4));
	this->addLogic(L3);
	this->addLogic(camLogic);
	this->addLogic(camZoom);
	
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
				free.push_back(std::make_pair(float(x * w), float(y * h)));
			}
			else if (e == '*') {
				portal_location = std::make_pair(x * w, y * h);
			}
			x++;
		}y++;
		x = 0;
	}

	const int humans = 100;
	srand(time(NULL));

	std::set<int> r;
	for (int i = 0; i < humans; i++)
	{
		int index = rand() % free.size();
		r.insert(index);
	}

	for (const int& e : r)
	{
		std::pair<float, float> pos = free.at(e);
		Human* temp = new Human(pos.first, pos.second, 60 + rand() % 120);
		game->textureObject(temp, PATH"ZombieGame/Resources/Textures/circle.png");
		this->addReactive(temp,&humanBodyDef);
		this->humans.push_back(temp);
		temp->addFixture(sensorFixture)->SetFilterData(humanSensorFilter);
		temp->addFixture(humanShape)->SetFilterData(humanFilter);
	}

	this->zombify(this->humans.at(0));
	game->textureObject(this->humans.at(0), PATH"ZombieGame/Resources/Textures/zombie.png");
	zombieTexture = this->humans.at(0)->texture;
	this->humans.at(0)->Zombify();

	this->addLogic(new HumanMovement(&this->humans,std::bind(&ZombieScene::zombify,this,std::placeholders::_1),&world));
	SGE::Reactive* portal = new Portal(float(portal_location.first), float(portal_location.second));
	game->textureObject(portal, PATH"ZombieGame/Resources/Textures/glass.png");
	this->addReactive(portal,&worldBodyDef);
	portal->getBody()->CreateFixture(&worldShape, 0);

	world.SetContactListener(new ZListener());

	Pointer* pointer = new Pointer();
	this->addObject(pointer);
	this->game->textureObject(pointer, PATH"ZombieGame/Resources/Textures/pointer.png");
	
	this->addLogic(new AimPointer(&this->world, player, pointer, mouse, camera, this->killCount, 8 * 64.f));
	this->addLogic(new WinCondition(this->zombieCount, this->killCount, endScene));

	//Puts player on top
	game->textureObject(player, PATH"ZombieGame/Resources/Textures/player.png");
	this->addReactive(player, &humanBodyDef);
	player->addFixture(humanShape);
	player->getBody()->SetLinearDamping(64);
	player->getBody()->GetFixtureList()->SetFilterData(playerFilter);
}

void ZombieScene::unloadScene()
{
	this->finalize();
	while(this->world.GetBodyList())
	{
		this->world.DestroyBody(this->world.GetBodyList());
	}
}

ZombieScene::~ZombieScene()
{
	std::cout << "~MainScene" << std::endl;
}

template<typename Vec>
void vec_clear(Vec& vec)
{
	for (auto h : vec)
	{
		delete h;
	}
	vec.clear();
}

void ZombieScene::finalize()
{
	this->level.clear();
	this->humans.clear();
	vec_clear(this->getLogics());
	vec_clear(this->getActions());
	vec_clear(this->getObjects());
}

void ZombieScene::onDraw()
{
}
