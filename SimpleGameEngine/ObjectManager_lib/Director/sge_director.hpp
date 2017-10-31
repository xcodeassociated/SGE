#ifndef sge_director_h
#define sge_director_h

#include <vector>
#include <sge_logic.hpp>
#include <sge_scene.hpp>

namespace SGE {

    class Director final{
	private:
		ObjectManager* manager = nullptr;
		int Width = 0;
		int Height = 0;

	    Director(int w, int h);
	    ~Director(); //Will prevent user form deleting Director, should be useful with ARC system in place.
		
		std::vector<SceneID> scenes;

	public:
	    static Director* getDirector(int w = 0, int h = 0);

	    std::pair<int, int> getResolution();

	    Scene::ID addScene(Scene* scene);

	    void deleteScene(Scene::ID scene);

	    void addLogicBinder(Scene::ID scene, Logic::Binder logic);

	    void addLogicBinder(Scene::ID scene, Object::ID obj, Logic::ID logic);

	    void unbindLogic(Scene::ID scene, Object::ID obj, Logic::ID logic);

	    void showScene(Scene::ID scene);

	    void swapScene(Scene::ID scene);

	    void finalize();

	    /**
	     * \brief Current Current way of connecting OM and Director
	     * \param objectManager pointer to OM Singleton
	     * \todo: Change this? Some Bootstraper perhaps?
	     */
	    void bindManager(ObjectManager* objectManager);
    };
    
}

#endif /* sge_director_h */
