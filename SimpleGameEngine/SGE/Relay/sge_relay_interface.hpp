#ifndef sge_relay_interface_h
#define sge_relay_interface_h

namespace SGE {
	class Object;
	class Scene;
	class Director;
	class ObjectManager;
	class SceneID;
	class ObjectID;

	class Relay final {
	private:
		ObjectManager* manager = nullptr;
		Director* director = nullptr;
		Relay(ObjectManager* o, Director* d);
		~Relay();

	public:
		static Relay* getRelay();
		void relayScene(SceneID s);
		void relayDeleteScene(SceneID s);
		long getNextCounter();
	};
}


#endif /* sge_relay_interface_h */