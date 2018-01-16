#ifndef ZOMBIE_SCENE
#define ZOMBIE_SCENE
#include <sge_game.hpp>
#include <sge_scene.hpp>
#include <sge_box2dscene.hpp>
#include "Objects.hpp"

class ZombieScene : public SGE::Box2DScene
{	
protected:
	//TODO Make Game ptr part of basic class?
	SGE::Game* game = nullptr;
	std::string path;
	std::vector<Human*> humans;

	static SGE::GLTexture zombieTexture;
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

	static bool init();
	static void zombify(Human* human);
public:

	ZombieScene(SGE::Game* game, const char* path);

	virtual void loadScene() override;

	virtual ~ZombieScene();

	virtual void finalize() override;

	virtual void onDraw() override;
};

#endif
