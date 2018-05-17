#include "sge_input_handler.hpp"
#include "../sge_game.hpp"
#include "../../IO/InputManager/sge_input_manager.hpp"
#include "../../IO/Mouse/sge_mouse.hpp"
#include "sge_input_binder.hpp"
#include "../../Action/sge_action.hpp"

#include <glm/glm.hpp>

SGE::InputHandler::MouseHandler::MouseHandler() noexcept : mouse(new SGE::MouseObject)
{
}

void SGE::InputHandler::MouseHandler::setMouseCoords(glm::vec2 coords) noexcept
{
	this->mouse->setMouseCoords(coords);
}

glm::vec2 SGE::InputHandler::MouseHandler::getMouseCoords() const noexcept
{
	return this->mouse->getMouseCoords();
}

SGE::MouseObject* SGE::InputHandler::MouseHandler::getMouseObject() noexcept
{
	return this->mouse;
}

SGE::InputHandler::InputHandler(SGE::Game* game) noexcept
		: game(game), input_manager(new SGE::InputManager), mouseHandler(new MouseHandler)
{
}

void SGE::InputHandler::mapAction(const SGE::InputBinder& bind)
{
	auto p = this->keyMap.insert(std::make_pair(bind.getKey(), bind.getAction()));
	if (!p.second)
		throw std::runtime_error("Could not map action");
	bind.getAction()->action_begin();
}

void SGE::InputHandler::unmapAction(const SGE::InputBinder& bind)
{
    auto action = bind.getAction();
	if (this->keyMap.erase(bind.getKey()) == 0)
		throw std::runtime_error("Could not unmap action");
	action->action_ends();
}

void SGE::InputHandler::pressKey(SGE::Key k)
{
	auto it = this->keyMap.find(k);
	if (it == this->keyMap.end())
		return;
	it->second->action_main();
}

void SGE::InputHandler::pollEvents() noexcept
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type) {
			case SDL_QUIT:
			{
				this->game->windowClosing();
			}break;

			case SDL_KEYDOWN:
			{
				this->pressKey(Key(event.key.keysym.sym));
			}break;

			case SDL_MOUSEMOTION:
			{
				this->mouseHandler->setMouseCoords({ event.motion.x, event.motion.y });
			}break;

			case SDL_MOUSEBUTTONDOWN:
			{
				this->mouseHandler->setMouseCoords({ event.motion.x, event.motion.y });
				this->pressKey(Key(-10));
			}break;

			case SDL_MOUSEBUTTONUP:
			{
			}break;
		}
	}
}

SGE::InputHandler::MouseHandler* SGE::InputHandler::getMouseHandler() noexcept
{
	return this->mouseHandler;
}

