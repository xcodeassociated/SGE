#ifndef sge_scene_h
#define sge_scene_h

#include "../ID/sge_id.hpp"
#include "../Sprite/sge_vertex.hpp"
#include "../BackgroundElement/sge_background_element.hpp"
#include "../LevelParser/sge_level_parser.hpp"
#include <map>
#include <string>
#include <vector>

namespace SGE {
	
	class Scene;
	class Director;
	class ObjectManager;

	class SceneID final : public ID {
		friend class Director;
		friend class ObjectManager;

		Scene* scene;

	public:
		SceneID(const long id, Scene* s) : ID(id), scene(s) {};
	};

    class Scene{
	private:
		std::vector<BackgroundElement> background;
																						
	public:
		bool TextureLoaded = false;
		using ID = SceneID;

		virtual ~Scene() = default;

		virtual void loadLevel(const char* path, std::map<char, std::string> levelMask) final
		{
			LevelParser parser(path, levelMask);
			this->background = std::move(parser.parse());
			this->TextureLoaded = true;
		}

		virtual std::vector<BackgroundElement>& getBackground() final
		{
			return this->background;
		}

		virtual void finalize() = 0;
		virtual void onDraw() = 0;
    };
    
}

#endif /* sge_scene_h */