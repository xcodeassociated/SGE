#include "sge_camera_handler.hpp"
#include "sge_utils.hpp"
#include "sge_camera2d.hpp"
#include <iostream>

namespace SGE {

	CameraHandler::CameraHandler(std::pair<int, int> resolution) noexcept
	{
		this->camera = new Camera2d(resolution.first, resolution.second);
	}

	Camera2d* CameraHandler::getCamera()
	{
		return this->camera;
	}

	void CameraHandler::setScale(double _scale) noexcept
	{
		this->camera->setScale(_scale);
	}

	void CameraHandler::setPosition(int _x, int _y) noexcept
	{
		this->camera->setPosition(glm::vec2(_x, _y));
	}

	void CameraHandler::updateCamera(void) const noexcept
	{
		this->camera->update();
	}

	const glm::mat4& CameraHandler::getCameraMatrix(void) const noexcept
	{
		return this->camera->getCameraMatrix();
	}

	void CameraHandler::setPosition(glm::vec2 pos) noexcept
	{
		this->setPosition(pos.x, pos.y);
	}

	glm::vec2 CameraHandler::getScreenToWorld(glm::vec2 pos) const noexcept
	{
		return SGE::screenToWorld(pos, this->camera->getPosition(), (double)this->camera->getScale());
	}

	glm::vec2 CameraHandler::getScreenToWorld(int _x, int _y) const noexcept
	{
		return this->getScreenToWorld({ _x, _y });
	}
}
