#ifndef ZOMBIE_SCENE
#define ZOMBIE_SCENE
#include <sge_game.hpp>
#include <sge_scene.hpp>
#include <sge_box2dscene.hpp>
#include "Objects.hpp"

class CullingListener : public b2ContactListener
{
protected:
	SGE::Camera2d* camera = SGE::Game::getGame()->getCamera();
	unsigned short camCategory = (unsigned short)(Category::Camera);
	bool cull(b2Fixture* A, b2Fixture* B);
	bool uncull(b2Fixture* A, b2Fixture* B);
public:
	virtual void BeginContact(b2Contact* contact) override;
	virtual void EndContact(b2Contact* contact) override;
	
};

class ZListener : public CullingListener
{
public:
	virtual void BeginContact(b2Contact* contact) override;

	virtual void EndContact(b2Contact* contact) override;
};

class ZombieScene : public SGE::Box2DScene
{	
protected:
	//TODO Make Game ptr part of basic class?
	SGE::Game* game = nullptr;
	std::string path;
	std::vector<Human*> humans;
	std::size_t zombieCount = 0;
	std::size_t killCount = 0;

	static b2Filter zombieFilter;
	static b2Filter zombieSensorFilter;
	static b2Filter playerFilter;
	static b2Filter humanFilter;
	static b2Filter humanSensorFilter;
	static b2CircleShape sensorShape;
	static b2FixtureDef sensorFixture;
	static b2BodyDef humanBodyDef;
	static b2CircleShape humanShape;
	static b2PolygonShape worldShape;
	static b2BodyDef worldBodyDef;
	static b2Filter worldFilter;
	static bool init();
public:
	void zombify(Human* human);
	SGE::Scene* endScene;

	static b2FixtureDef corpseFixture;
	static SGE::GLTexture zombieTexture;
	static SGE::GLTexture deadZombieTexture;
	static SGE::GLTexture deadHumanTexture;

	ZombieScene(SGE::Game* game, const char* path);

	virtual void loadScene() override;
	virtual void unloadScene() override;

	virtual ~ZombieScene();

	virtual void finalize() override;

	virtual void onDraw() override;
	virtual void addReactive(SGE::Reactive* object, const b2BodyDef* bodyDef) override;
};

#endif
