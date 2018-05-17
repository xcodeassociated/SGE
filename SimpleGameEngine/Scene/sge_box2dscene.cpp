#include "sge_box2dscene.hpp"
#include "../Object/Reactive/sge_reactive.hpp"

SGE::Box2DScene::Box2DScene(const b2Vec2& gravity) : world(gravity)
{
}

SGE::Box2DScene::Box2DScene(const b2World& world) : world(world)
{
}

void SGE::Box2DScene::addReactive(Reactive* object, const b2BodyDef* bodyDef)
{
	this->Scene::addObject(object);
	object->setBody(this->world.CreateBody(bodyDef));
}
