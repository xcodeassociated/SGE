#include "IntroScene.hpp"
#include "sge_shape_rectangle.hpp"
#include "Objects.hpp"
#include "sge_game.hpp"
#include "Logics.hpp"
#include "Actions.hpp"
#include "sge_director.hpp"

IntroScene::IntroScene(SGE::Scene* next, const char* path) : path(path), next(next)
{
}

void IntroScene::loadScene()
{
	auto o = new Image(0, 0, new SGE::Rectangle(1024, 768, true));
	auto g = SGE::Game::getGame();
	g->textureObject(o, path);
	this->addObject(o);
	this->addLogic(new Timer(5, new Load(next)));
	g->getCamera()->setPosition(0, 0);
	g->getCamera()->setScale(1.f);
}

IntroScene::~IntroScene()
{
}

void IntroScene::finalize()
{
}

void IntroScene::onDraw()
{
	auto g = SGE::Game::getGame();
	g->getCamera()->setPosition(0, 0);
	g->getCamera()->setScale(1.f);
	SGE::Director::getDirector()->unloadScene(next);
}

void EndScene::loadScene()
{
	auto o = new Image(0, 0, new SGE::Rectangle(1024, 768, true));
	auto g = SGE::Game::getGame();
	g->textureObject(o, path);
	this->addObject(o);
	this->addLogic(new OnKey(SGE::Key::Return, next));
	g->getCamera()->setPosition(0, 0);
	g->getCamera()->setScale(1.f);
}
