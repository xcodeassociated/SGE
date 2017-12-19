#include "IntroScene.hpp"
#include "sge_shape_rectangle.hpp"
#include "Objects.hpp"
#include "sge_game.hpp"
#include "Logics.hpp"
#include "Actions.hpp"

IntroScene::IntroScene(SGE::Scene* next, const char* path) : path(path), next(next)
{
}

void IntroScene::loadScene()
{
	auto o = new Image(0, 0, new SGE::Rectangle(1300, 600, true));
	auto g = SGE::Game::getGame();
	g->textureObject(o, path);
	this->addObject(o);
	this->addLogic(new Timer(10, new Load(next)));
	this->state = SGE::SceneState::Ready;
	g->getCamera()->setPosition(0, 0);
	g->getCamera()->setScale(1.28f);
}

IntroScene::~IntroScene()
{
}

void IntroScene::finalize()
{
}

void IntroScene::onDraw()
{
}
