#include "sge_camera2d.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include "../Utils/sge_utils.hpp"

SGE::Camera2d::Camera2d(unsigned _width, unsigned _height): cameraMatrix(1.f), matUpdate(true)
{
	this->box[0] = _width;
	this->box[1] = _height;

	this->orthoMatrix = glm::ortho(0.0f, (float)this->box[0], 0.0f, (float)this->box[1]);
}

void SGE::Camera2d::setPosition(float x, float y)
{
	this->matUpdate = true;
}

void SGE::Camera2d::setPosition(glm::vec2 _position)
{
	this->Y = _position.y;
	this->X = _position.x;
	this->matUpdate = true;
}

glm::vec2 SGE::Camera2d::getPosition() const noexcept
{
	return glm::vec2{this->X,this->Y};
}

void SGE::Camera2d::setScale(float _scale)
{
	this->scale = _scale;
	this->matUpdate = true;
}

float SGE::Camera2d::getScale() const
{
	return this->scale;
}

const glm::mat4& SGE::Camera2d::getCameraMatrix() const
{
	return this->cameraMatrix;
}

void SGE::Camera2d::update()
{
	if (this->matUpdate)
	{
		glm::vec3 translate(- this->X + (this->box[0] / 2), - this->Y + (this->box[1] / 2), 0.0f);
		this->cameraMatrix = glm::translate(this->orthoMatrix, translate);

		glm::vec3 scale_vec(this->scale, this->scale, 0.0f);
		this->cameraMatrix = glm::scale(glm::mat4(1.0f), scale_vec) * this->cameraMatrix;

		this->matUpdate = false;
	}
}

glm::vec2 SGE::Camera2d::screenToWorld(glm::vec2 coords)
{
	return SGE::screenToWorld({this->box[0], this->box[1]}, coords, this->getPosition(), double(scale));
}

int SGE::Camera2d::getWidth() const
{
	return this->box[0];
}

int SGE::Camera2d::getHeight() const
{
	return this->box[1];
}
