#ifndef sge_scene_h
#define sge_scene_h

#include <vector>
#include <map>
#include <sge_id.hpp>
#include <sge_logic.hpp>
#include <sge_level.hpp>

namespace SGE {
	
	class Scene;
	class Director;
	class ObjectManager;

	class SceneID final : public ID {
		friend class Director;
		friend class ObjectManager;

		Scene* scene;

	public:
		SceneID(const long id, Scene* s);
	};

    class Scene{
	private:
		using LogicVector = std::vector<Logic::Binder>;
        using ObjectVector= std::vector<ObjectID>;
        
		Level level;
		LogicVector Logics;
        ObjectVector* Objects = nullptr;

	public:
		bool TextureLoaded = false;
		using ID = SceneID;

	    LogicVector& getLogics();

		virtual ~Scene() = default;

	    virtual void loadLevel(const char* path, std::map<char, std::string> levelMask) final;

	    virtual Level& getLevel() final;

	    virtual void BindObjects(ObjectVector* obj) final;

	    virtual ObjectVector& getObjects() final;

		virtual void finalize() = 0;
        virtual void onDraw() = 0;

    };
    
}

#endif /* sge_scene_h */
