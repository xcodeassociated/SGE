#include "sge_scene.hpp"
#include "sge_logic_bind.hpp"
#include <sge_level_parser.hpp>

SGE::SceneID::SceneID(const long id, Scene* s): ID(id), scene(s)
{
}

SGE::Scene::LogicVector& SGE::Scene::getLogics()
{
	return this->Logics;
}

void SGE::Scene::loadLevel(const char* path, std::map<char, std::string> levelMask)
{
	LevelParser parser(path, levelMask);
	this->level = parser.parse();
	this->TextureLoaded = true;
}

SGE::Level& SGE::Scene::getLevel()
{
	return this->level;
}

void SGE::Scene::BindObjects(ObjectVector* obj)
{
	this->Objects = obj;
}

SGE::Scene::ObjectVector& SGE::Scene::getObjects()
{
	return *this->Objects;
}
