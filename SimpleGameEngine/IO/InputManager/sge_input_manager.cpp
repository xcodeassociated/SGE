#include "sge_input_manager.hpp"

void SGE::InputManager::pressKey(unsigned _keyID)
{
	this->keyMap[_keyID] = true;
}

void SGE::InputManager::releaseKey(unsigned _keyID)
{
	this->keyMap[_keyID] = false;
}

bool SGE::InputManager::isKeyPressed(unsigned _keyID)
{
	auto it = this->keyMap.find(_keyID);
	if (it != this->keyMap.end())
		return it->second;
	else
		return false;
}
