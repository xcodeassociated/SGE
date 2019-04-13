#include "sge_window.hpp"

#include <GL/glew.h>
#include <SDL.h>
#include <stdexcept>

#ifdef _WIN32
#include <gl/GL.h>
#endif

SGE::Window::Window(std::pair<int, int> resolution) 
	: width(resolution.first), height(resolution.second) {}

SGE::Window::~Window() { SDL_DestroyWindow(window); }
void SGE::Window::createWindow(SGE::Color color) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    throw std::runtime_error{"SDL init filed"};

  this->window = SDL_CreateWindow(
      "SGE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width,
      this->height, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);

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

  glClearColor(color.r, color.g, color.b, color.a);

  //	if (SDL_GL_SetSwapInterval(-1) != 0)
  //		throw std::runtime_error{ "SDL_GL_SetSwapInterval not supported"
  //};
  SDL_GL_SetSwapInterval(1);

  const GLubyte *version = glGetString(GL_VERSION);
  const char *glVersionChar = reinterpret_cast<const char *>(version);

  const GLubyte *render = glGetString(GL_RENDERER);
  const char *glRenderChar = reinterpret_cast<const char *>(render);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);
}

void SGE::Window::showWindow() {
	SDL_ShowWindow(this->window);
}

void SGE::Window::finalizeWindow() {
	SDL_DestroyWindow(this->window);
}

SDL_Window* SGE::Window::getWindow() {
	return this->window;
}

bool SGE::Window::isHidden() const
{
	return SDL_WINDOW_HIDDEN & SDL_GetWindowFlags(this->window);
}
