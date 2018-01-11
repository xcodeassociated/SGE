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

ZombieScene::ZombieScene(SGE::Game* game, const char* path) : game(game), path(path), world(b2Vec2_zero)
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
	Player* player = new Player(200, 200);

	player->setBody(world.CreateBody(&humanBodyDef));
	player->addFixture(humanShape);
	player->body->SetLinearDamping(10);

	game->textureObject(player, PATH"ZombieGame/Resources/Textures/circle.png");
	this->addObject(player);

	SGE::Action* click = new MouseClickedAction(mouse, player);
	SGE::InputBinder clickBind(click, SGE::Key::MOUSE_LEFT_BUTTON);
	game->mapAction(clickBind);

	//auto L1 = new SGE::Logics::PreciseLevelCollider(player, this->getLevel().getWorld());
	//SGE::Action* toggle = new LogicSwitch(L1);
	//game->mapAction(SGE::InputBinder(toggle, SGE::Key::O));

	auto L3 = new SimpleMove(player, 300.f, SGE::Key::W, SGE::Key::S, SGE::Key::A, SGE::Key::D);

	auto camLogic = new SnapCamera(8, SGE::Key::Up, SGE::Key::Down, SGE::Key::Left, SGE::Key::Right, SGE::Key::Space, player, camera);
	auto camZoom = new SGE::Logics::CameraZoom(camera, 0.1f, 1.f, 0.15f, SGE::Key::Q, SGE::Key::E);

	this->addLogic(new StepWorld(&this->world));
	//this->addLogic(L1);
	this->addLogic(L3);
	//this->addLogic(L1);
	this->addLogic(camLogic);
	this->addLogic(camZoom);

	//auto testTile = &(this->getLevel().getWorld().front());
	//auto moveTileLogic = new SGE::Logics::SimpleMove(testTile, 200.f, SGE::Key::I, SGE::Key::K, SGE::Key::J, SGE::Key::L);
	//this->addLogic(moveTileLogic);

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
				free.push_back(std::make_pair(x * w, (y * h)));
			}
			else if (e == '*') {
				portal_location = std::make_pair(x * w, (y * h));
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
		this->addObject(temp);
		this->humans.push_back(temp);
		temp->setBody(world.CreateBody(&humanBodyDef));
		temp->addFixture(humanShape);
	}

	/*for (auto human : this->humans)
	{
		this->addLogic(new BiCollider(human, player));
		this->addLogic(new SGE::Logics::PreciseLevelCollider(human, this->getLevel().getWorld()));
	}*/
	this->addLogic(new HumanRandomMovement(&this->humans));
	SGE::Object* portal = new Portal(portal_location.first-64, portal_location.second+16);
	game->textureObject(portal, PATH"ZombieGame/Resources/Textures/glass.png");
	this->addObject(portal);

	b2Body* portalBody = this->world.CreateBody(&worldBodyDef);
	portalBody->SetTransform(b2Vec2(portal->getX(), portal->getY()), 0);
	portalBody->CreateFixture(&worldShape, 0);

	//SGE::Logic* portalLogic = new PortalLogic(portal, player);
	//this->addLogic(portalLogic);

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
