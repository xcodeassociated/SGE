#ifndef INTRO_SCENE
#define INTRO_SCENE
#include <sge_scene.hpp>

class IntroScene : public SGE::Scene
{
	std::string path;
	SGE::Scene* next;
public:

	IntroScene(SGE::Scene* next, const char* path);

	virtual void loadScene() override;

	virtual ~IntroScene();

	virtual void finalize() override;

	virtual void onDraw() override;
};

#endif
