#ifndef ZOMBIE_SCENE
#define ZOMBIE_SCENE
#include <sge_game.hpp>
#include <sge_scene.hpp>
#include "Objects.hpp"

class ZombieScene : public SGE::Scene
{
	//TODO Make Game ptr part of basic class?
	SGE::Game* game = nullptr;
	std::string path;
	std::vector<Human*> humans;
public:

	ZombieScene(SGE::Game* game, const char* path);

	virtual void fetch();

	virtual ~ZombieScene();

	virtual void finalize() override;

	virtual void onDraw() override;
};

#endif
