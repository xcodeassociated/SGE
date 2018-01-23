#ifndef INTRO_SCENE
#define INTRO_SCENE
#include <sge_scene.hpp>

class IntroScene : public SGE::Scene
{
protected:
	std::string path;
	SGE::Scene* next;
public:

	IntroScene(SGE::Scene* next, const char* path);

	virtual void loadScene() override;

	virtual ~IntroScene();

	virtual void finalize() override;

	virtual void onDraw() override;
};

class EndScene: public IntroScene
{
public:
	using IntroScene::IntroScene;
	virtual void loadScene() override;
};

#endif
