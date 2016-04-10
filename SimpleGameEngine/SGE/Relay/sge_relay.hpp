#ifndef sge_relay_h
#define sge_relay_h

#include "sge_relay.hpp"

namespace SGE {
	class Object;
	class Scene;
	class Director;
	class ObjectManager;
	class SceneID;
	class ObjectID;

	Relay::Relay(ObjectManager* o, Director* d): manager(o), director(d) {}

	static Relay* Relay::getRelay()
	{
		static Relay* relay = new Relay(ObjectManager::getManager(), Director::getDirector());
		return relay;
	}

	void Relay::relayScene(Scene::ID s) {
		this->manager->addScene(s);
	}

	void Relay::relayDeleteScene(Scene::ID s)
	{
	//	this->manager->deleteScene(s);
	}

	long Relay::getNextCounter() {
		return manager->counter++;
	}
}


#endif /* sge_relay_h */