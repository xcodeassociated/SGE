#include "sge_camera_handler.hpp"
#include "../../Utils/sge_utils.hpp"
#include "../../Camera2d/sge_camera2d.hpp"
#include <iostream>

SGE::CameraHandler::CameraHandler(std::pair<int, int> resolution) noexcept
{
	this->camera = new Camera2d(resolution.first, resolution.second);
}

SGE::CameraHandler::CameraHandler(Camera2d* camera2d) noexcept : camera(camera2d)
{
}

SGE::Camera2d* SGE::CameraHandler::getCamera()
{
	return this->camera;
}

void SGE::CameraHandler::setScale(double _scale) noexcept
{
	this->camera->setScale(_scale);
}

void SGE::CameraHandler::setPosition(int _x, int _y) noexcept
{
	this->camera->setPosition(glm::vec2(_x, _y));
}

void SGE::CameraHandler::updateCamera() const noexcept
{
	this->camera->update();
}

const glm::mat4& SGE::CameraHandler::getCameraMatrix() const noexcept
{
	return this->camera->getCameraMatrix();
}

void SGE::CameraHandler::setPosition(glm::vec2 pos) noexcept
{
	this->setPosition(int(pos.x), int(pos.y));
}

glm::vec2 SGE::CameraHandler::getScreenToWorld(glm::vec2 screen, glm::vec2 pos) const noexcept
{
	return SGE::screenToWorld(screen, pos, this->camera->getPosition(), (double)this->camera->getScale());
}

glm::vec2 SGE::CameraHandler::getScreenToWorld(glm::vec2 screen, int _x, int _y) const noexcept
{
	return this->getScreenToWorld(screen, { _x, _y });
}

