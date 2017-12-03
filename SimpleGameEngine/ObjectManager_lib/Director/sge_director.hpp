#ifndef sge_director_h
#define sge_director_h

#include <vector>
#include <sge_logic.hpp>
#include <sge_scene.hpp>

namespace SGE {

	/**
     * \brief 
     */
    class Director final{
	private:
	    /**
		 * \brief 
		 */
		ObjectManager* manager = nullptr;
	    /**
		 * \brief 
		 */
		int Width = 0;
	    /**
		 * \brief 
		 */
		int Height = 0;

	    /**
	     * \brief 
	     * \param w 
	     * \param h 
	     */
	    Director(int w, int h);
	    /**
	     * \brief 
	     */
	    ~Director(); //Will prevent user form deleting Director, should be useful with ARC system in place.
		
	    /**
		 * \brief 
		 */
		std::vector<Scene*> scenes;

	public:
	    /**
	     * \brief 
	     * \param w 
	     * \param h 
	     * \return 
	     */
	    static Director* getDirector(int w = 0, int h = 0);

	    /**
	     * \brief 
	     * \return 
	     */
	    std::pair<int, int> getResolution();

	    /**
	     * \brief 
	     * \param scene 
	     * \return 
	     */
	    Scene* addScene(Scene* scene);

	    /**
	     * \brief 
	     * \param scene 
	     */
	    void deleteScene(Scene* scene);

	    /**
	     * \brief 
	     * \param scene 
	     * \param logic 
	     */
	    void addLogicBinder(Scene* scene, Logic::Binder logic);

	    /**
	     * \brief 
	     * \param scene 
	     * \param obj 
	     * \param logic 
	     */
	    void addLogicBinder(Scene* scene, Object* obj, Logic* logic);

	    /**
	     * \brief 
	     * \param scene 
	     * \param obj 
	     * \param logic 
	     */
	    void unbindLogic(Scene* scene, Object* obj, Logic* logic);

	    /**
	     * \brief 
	     * \param scene 
	     */
	    void showScene(Scene* scene);

	    /**
	     * \brief 
	     * \param scene 
	     */
	    void swapScene(Scene* scene);

	    /**
	     * \brief 
	     */
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
