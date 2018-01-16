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
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include "Logics/World/sge_worldstep.hpp"
#include "Box2D/Dynamics/Contacts/b2Contact.h"

ZombieScene::ZombieScene(SGE::Game* game, const char* path) : Box2DScene(b2Vec2_zero), game(game), path(path)
{
}

void ZombieScene::loadScene()
{
	std::map<char, std::string> mask = {
		{ 'R', PATH"ZombieGame/Resources/Textures/red_bricks.png" },
		{ 'B', PATH"ZombieGame/Resources/Textures/red_bricks.png" },
		{ 'G', PATH"ZombieGame/Resources/Textures/glass.png" },
		{ 'L', PATH"ZombieGame/Resources/Textures/light_bricks.png" }
	};
	this->Scene::loadLevel(this->path.c_str(), mask);

	b2BodyDef worldBodyDef;
	worldBodyDef.type = b2_staticBody;

	b2PolygonShape worldShape;
	worldShape.SetAsBox(32, 32);

	for(SGE::WorldElement& e: this->getLevel().getWorld())
	{
		b2Body* body = world.CreateBody(&worldBodyDef);
		body->SetTransform(b2Vec2(e.getX(), e.getY()), 0);
		body->CreateFixture(&worldShape, 0);
	}
	
	b2BodyDef humanBodyDef;
	humanBodyDef.fixedRotation = true;
	humanBodyDef.type = b2_dynamicBody;
	
	b2CircleShape humanShape;
	humanShape.m_radius = 32;
	humanShape.m_p = b2Vec2_zero;

	SGE::Camera2d* camera = game->getCamera();
	camera->setScale(0.5f);
	SGE::MouseObject* mouse = game->getMouse();
	Player* player = new Player(200, 200,true,getCircle());
	
	b2Filter playerFilter;
	playerFilter.categoryBits = uint16(Category::Player);
	playerFilter.maskBits = Category::Player | Category::Human | Category::Zombie | Category::Level;

	game->textureObject(player, PATH"ZombieGame/Resources/Textures/circle.png");
	this->addObject(player,&humanBodyDef);
	player->addFixture(humanShape);
	player->getBody()->SetLinearDamping(10);
	player->getBody()->GetFixtureList()->SetFilterData(playerFilter);

	SGE::Action* click = new MouseClickedAction(mouse, player);
	SGE::InputBinder clickBind(click, SGE::Key::MOUSE_LEFT_BUTTON);
	game->mapAction(clickBind);

	auto L3 = new SimpleMove(player, 300.f, SGE::Key::W, SGE::Key::S, SGE::Key::A, SGE::Key::D);

	auto camLogic = new SnapCamera(8, SGE::Key::Up, SGE::Key::Down, SGE::Key::Left, SGE::Key::Right, SGE::Key::Space, player, camera);
	auto camZoom = new SGE::Logics::CameraZoom(camera, 0.1f, 1.f, 0.15f, SGE::Key::Q, SGE::Key::E);

	this->addLogic(new SGE::WorldStep(&this->world,2,4));
	this->addLogic(L3);
	this->addLogic(camLogic);
	this->addLogic(camZoom);

	auto reset = new GOTO(player);
	game->mapAction(SGE::InputBinder(reset, SGE::Key::B));

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

	b2Filter humanFilter;
	humanFilter.categoryBits = uint16(Category::Human);
	humanFilter.maskBits = Category::Player | Category::Human | Category::Zombie | Category::Level | Category::ZombieSensor;

	b2CircleShape sensorShape;
	sensorShape.m_p = b2Vec2_zero;
	sensorShape.m_radius = 32 * 3;

	b2FixtureDef Sensor;
	Sensor.isSensor = true;
	Sensor.shape = &sensorShape;
	Sensor.filter.categoryBits = uint16(Category::HumanSensor);
	Sensor.filter.maskBits = uint16(Category::Zombie);

	for (const int& e : r)
	{
		std::pair<float, float> pos = free.at(e);
		Human* temp = new Human(pos.first, pos.second, 60 + rand() % 120);
		game->textureObject(temp, PATH"ZombieGame/Resources/Textures/circle.png");
		this->addObject(temp,&humanBodyDef);
		this->humans.push_back(temp);
		temp->addFixture(humanShape)->SetFilterData(humanFilter);
		temp->addFixture(Sensor);
	}

	b2Filter zombieFilter;
	zombieFilter.categoryBits = uint16(Category::Zombie);
	zombieFilter.maskBits = Category::Player | Category::Human | Category::Zombie | Category::Level | Category::HumanSensor;

	b2Filter zombieSensorFilter;
	zombieSensorFilter.categoryBits = uint16(Category::ZombieSensor);
	zombieSensorFilter.maskBits = uint16(Category::Human);

	auto changeToZombie = [zombieFilter,zombieSensorFilter](Human* human)
	{
		b2Fixture* fixture = human->getBody()->GetFixtureList();
		fixture->SetFilterData(zombieFilter);
		fixture->GetNext()->SetFilterData(zombieSensorFilter);
	};
	changeToZombie(this->humans.at(0));

	this->addLogic(new HumanRandomMovement(&this->humans));
	SGE::Reactive* portal = new Portal(float(portal_location.first), float(portal_location.second));
	game->textureObject(portal, PATH"ZombieGame/Resources/Textures/glass.png");
	this->addObject(portal,&worldBodyDef);
	portal->getBody()->CreateFixture(&worldShape, 0);

	SGE::Action* portalAction = new PortalAction;
	game->mapAction(SGE::InputBinder(portalAction, SGE::Key::P));
}

ZombieScene::~ZombieScene()
{
	std::cout << "~MainScene" << std::endl;
}

template<typename Vec>
void vec_clear(Vec vec)
{
	for (auto h : vec)
	{
		delete h;
	}
	vec.clear();
}

void ZombieScene::finalize()
{
	
	vec_clear(this->humans);
	vec_clear(this->getLogics());
	vec_clear(this->getActions());
	vec_clear(this->getObjects());
}

void ZombieScene::onDraw()
{
}
