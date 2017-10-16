#include "sge_input_handler.hpp"

namespace SGE {

	ObjectManager::InputHandler::MouseHandler::MouseHandler() noexcept : mouse(new MouseObject) {

	}

	void ObjectManager::InputHandler::MouseHandler::setMouseCoords(glm::vec2 coords) noexcept {
		this->mouse->setMouseCoords(coords);
	}

	glm::vec2 ObjectManager::InputHandler::MouseHandler::getMouseCoords(void) const noexcept {
		return this->mouse->getMouseCoords();
	}

	MouseObject* ObjectManager::InputHandler::MouseHandler::getMouseObject(void) noexcept {
		return this->mouse;
	}

	ObjectManager::InputHandler::InputHandler(ObjectManager* m) noexcept : manager(m), input_manager(new InputManager), mouseHandler(new MouseHandler) {
	}

	void ObjectManager::InputHandler::mapAction(const InputBinder& bind)
	{
		auto p = this->keyMap.insert(std::make_pair(bind.getKey(), bind.getBind()));
		if (!p.second) throw std::runtime_error("You are an idiot");
	}

	void ObjectManager::InputHandler::unmapAction(const InputBinder& bind)
	{
		if (this->keyMap.erase(bind.getKey()) == 0) throw std::runtime_error("You are an idiot");
	}

	void ObjectManager::InputHandler::pressKey(Key k)
	{
		auto it = this->keyMap.find(k);
		if (it == this->keyMap.end()) return;
		this->manager->action_handler->handleInputAction(it->second);
	}

	void ObjectManager::InputHandler::operator()(void) noexcept {

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: {
				this->manager->windowClosing();
			}break;

			case SDL_KEYDOWN: {
				this->pressKey(Key(event.key.keysym.sym));
			}break;

			case SDL_MOUSEMOTION: {
				this->mouseHandler->setMouseCoords({ event.motion.x, event.motion.y });
			}break;

			case SDL_MOUSEBUTTONDOWN: {
				this->mouseHandler->setMouseCoords({ event.motion.x, event.motion.y });
				this->pressKey(Key(-10));


				//                    glm::vec2 coords = this->camera->screenToWorld(this->inputManager->getMouseCoords());
				//                    std::cout << "Clicked: x=" << coords.x << ", y=" << coords.y << std::endl;
			}break;

			case SDL_MOUSEBUTTONUP: {
				//                    this->inputManager->releaseKey(event.button.button);
			}break;

			}
		}

	}

	ObjectManager::InputHandler::MouseHandler* ObjectManager::InputHandler::getMouseHandler() noexcept {
		return this->mouseHandler;
	}

}