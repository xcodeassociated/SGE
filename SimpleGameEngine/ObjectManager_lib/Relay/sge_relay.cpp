#include "sge_relay.hpp"
#include <stdexcept>
#include <sge_scene.hpp>
#include <sge_object_manager.hpp>
#include <sge_director.hpp>

namespace SGE {

	Relay::Relay() {}
	Relay::~Relay() {}

	Relay* Relay::getRelay()
	{
		static Relay* relay = new Relay();
		return relay;
	}

	void Relay::registerManager(ObjectManager* m)
	{
		this->manager = m;
	}

	void Relay::registerDirector(Director* d)
	{
		this->director = d;
	}

	void Relay::relayScene(Scene::ID s) {
		this->manager->addScene(s);
	}


	void Relay::registerActionHandler(ActionHandler* h)
	{
		this->handler = h;
	}

	void Relay::relayShowScene(SceneID s)
	{
		if (this->manager->isOnScene())
		{
			throw std::runtime_error("Scene already displayed");
		}
		this->manager->showScene(s);
	}

	void Relay::relaySwapScene(SceneID s)
	{
		if (!this->manager->isOnScene())
		{
			throw std::runtime_error("No scene displayed");
		}
		this->manager->swapScene(s);
	}

	void Relay::relayDeleteScene(Scene::ID s)
	{
		this->manager->deleteScene(s);
	}

	long Relay::getNextCounter() {
		return manager->counter++;
	}

	std::pair<int, int> Relay::relayGetResolution()
	{
		return this->director->getResolution();
	}

	Camera2d* Relay::getCamera()
	{
		return this->manager->getCamera();
	}

	Object* Relay::getObjectPtr(ObjectID id)
	{
		return this->manager->getObjectPtr(id);
	}

}
