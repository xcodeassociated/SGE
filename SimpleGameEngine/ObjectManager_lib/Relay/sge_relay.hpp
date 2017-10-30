#ifndef sge_relay_interface_h
#define sge_relay_interface_h

#include <utility>

namespace SGE {
    class Camera2d;
	class Object;
	class Scene;
	class Director;
	class ObjectManager;
	class SceneID;
	class ObjectID;
    class ActionHandler;

	class Relay final {
	private:
		ObjectManager* manager = nullptr;
		Director* director = nullptr;
        ActionHandler* handler = nullptr;
		Relay();
		~Relay();

	public:
		static Relay* getRelay();
		
		std::pair<int, int> relayGetResolution();
		void registerManager(ObjectManager* m);
		void registerDirector(Director* d);
        void registerActionHandler(ActionHandler* h);
		void relayScene(SceneID s);
		void relayShowScene(SceneID s);
		void relaySwapScene(SceneID s);
		void relayDeleteScene(SceneID s);
		long getNextCounter();
        Camera2d* getCamera();
        Object* getObjectPtr(ObjectID id);
        
	};
}


#endif /* sge_relay_interface_h */
