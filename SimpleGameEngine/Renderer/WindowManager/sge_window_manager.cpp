#include "sge_window_manager.hpp"
#include <GL/glew.h>
#include <SDL.h>
#include <stdexcept>

#ifdef _WIN32
#include <gl/GL.h>
#endif

SGE::WindowManager::WindowManager(std::pair<int, int> resolution) noexcept : width(resolution.first), height(resolution.second) {
}

void SGE::WindowManager::createWindow() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw std::runtime_error{"SDL init filed"};

	this->window = SDL_CreateWindow("SGE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);

	if (this->window == nullptr)
		throw std::runtime_error{"Window pointer is null"};

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GLContext glContext = SDL_GL_CreateContext(this->window);
	if (glContext == nullptr)
		throw std::runtime_error{"GL Context is null"};

	glewExperimental = GL_TRUE;
	GLenum glewCheck = glewInit();

	if (glewCheck != GLEW_OK)
		throw std::runtime_error{"GLEW init filed"};

	glClearColor(.7f, .7f, .7f, 1.0f);

//	if (SDL_GL_SetSwapInterval(-1) != 0)
//		throw std::runtime_error{ "SDL_GL_SetSwapInterval not supported" };
	SDL_GL_SetSwapInterval(1);

	const GLubyte* version = glGetString(GL_VERSION);
	const char* glVersionChar = reinterpret_cast<const char*>(version);

	const GLubyte* render = glGetString(GL_RENDERER);
	const char* glRenderChar = reinterpret_cast<const char*>(render);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.6f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


}

void SGE::WindowManager::showWindow() const noexcept {
	SDL_ShowWindow(this->window);
}


void SGE::WindowManager::hideWindow() const noexcept {
	SDL_HideWindow(this->window);
}

void SGE::WindowManager::finalizeWindow() noexcept {
	SDL_DestroyWindow(this->window);
	this->window = nullptr;
}

SDL_Window* SGE::WindowManager::getWindow() const noexcept {
	return this->window;
}

bool SGE::WindowManager::isHidden() const
{
	return SDL_WINDOW_HIDDEN & SDL_GetWindowFlags(this->window);
}

void SGE::WindowManager::swapWindow() const
{
	SDL_GL_SwapWindow(this->window);
}


