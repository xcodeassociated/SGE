#include "sge_window_manager.hpp"
#include <GL/glew.h>
#include <SDL.h>
#include <stdexcept>

#ifdef _WIN32
#include <GL.h>
#endif

namespace SGE {

	WindowManager::WindowManager(std::pair<int, int> resolution, Game* m) noexcept : width(resolution.first), height(resolution.second) {
		this->game = m;
	}

	void WindowManager::createWindow(void) {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            throw std::runtime_error{"SDL init filed"};

		this->window = SDL_CreateWindow("SGE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_OPENGL);

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

		SDL_GL_SetSwapInterval(1);

		const GLubyte* version = glGetString(GL_VERSION);
		const char* glVersionChar = reinterpret_cast< const char* >(version);

		const GLubyte* render = glGetString(GL_RENDERER);
		const char* glRenderChar = reinterpret_cast< const char* >(render);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);


	}

	void WindowManager::showWindow(void) noexcept {
		SDL_ShowWindow(this->window);
	}

	void WindowManager::finalizeWindow(void) noexcept {
		SDL_DestroyWindow(this->window);
		SDL_Quit();
	}

	SDL_Window* WindowManager::getWindow(void) noexcept {
		return this->window;
	}

}
