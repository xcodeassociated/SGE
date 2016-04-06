#ifndef sge_relay_h
#define sge_relay_h

#include "../ObjectManager/sge_object_manager.hpp"
#include "../Director/sge_director.hpp"

namespace SGE {
	class Relay final {
	private:
		ObjectManager* manager = nullptr;
		Director* director = nullptr;
		

	public:
		Relay(ObjectManager* o, Director* d) : manager(o), director(d) {}
		
		Relay* getRelay()
		{
			static Relay* relay = new Relay(ObjectManager::getManager(), Director::getDirector());
			return relay;
		}

		void relayScene(Scene::ID scene) {
			this->manager->addScene(scene);
		}
	};


}


#endif /* sge_relay_h */