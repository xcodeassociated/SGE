﻿#include "Logics.hpp"
#include "Actions.hpp"
#include <iostream>
#include <sge_action_move.hpp>
#include <sge_shape_circle.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <sge_keyboard_state.hpp>
#include <sge_fps_limiter.hpp>

SimpleMove::SimpleMove(SGE::Reactive* object, const float speed, const SGE::Key up, const SGE::Key down, const SGE::Key left, const SGE::Key right)
	: Logic(SGE::LogicPriority::Highest), object(object), speed(speed), up(up), down(down), left(left), right(right)
{
}

void SimpleMove::performLogic()
{
	b2Vec2 move = { 0,0 };
	if (isPressed(this->up)) move.y += this->speed;
	if (isPressed(this->down)) move.y -= this->speed;
	if (isPressed(this->right)) move.x += this->speed;
	if (isPressed(this->left)) move.x -= this->speed;
	if (b2Vec2{ 0,0 } != move)
	{
		object->getBody()->SetLinearVelocity(move);
	}
}

BiCollider::BiCollider(SGE::Object* a, SGE::Object* b): Logic(SGE::LogicPriority::Highest), a(a), b(b)
{
}

void BiCollider::performLogic()
{
	SGE::Circle* aCircle = reinterpret_cast<SGE::Circle*>(this->a->getShape());
	SGE::Circle* bCircle = reinterpret_cast<SGE::Circle*>(this->b->getShape());
	glm::vec2 selfPos = this->a->getPosition();
	glm::vec2 oponPos = this->b->getPosition();
	glm::vec2 pen = selfPos - oponPos;
	float distance = glm::length(pen);
	float radiuses = aCircle->getRadius() + bCircle->getRadius();

	if (distance < radiuses)
	{
		float move = (radiuses - distance) * 0.5;
		pen = glm::normalize(pen) * move;
		this->sendAction(new SGE::ACTION::Move(this->a, pen.x, pen.y, true));
		this->sendAction(new SGE::ACTION::Move(this->b, -pen.x, -pen.y, true));
	}
}

PortalLogic::PortalLogic(SGE::Object* portal, SGE::Object* player): SGE::Logics::Collide(SGE::LogicPriority::Highest), portal(portal), player(player)
{
}

void PortalLogic::performLogic()
{
	if (this->collideWithDifferentShape(this->portal, this->player))
	{
		try
		{
			SGE::ACTION::Move* moveAction = dynamic_cast<SGE::ACTION::Move*>(this->CircleToRectCollisionVec(
				this->portal, this->player));

			this->sendAction(moveAction);
			this->sendAction(new PortalAction);
		}
		catch (const std::bad_cast& exception)
		{
			std::cerr << exception.what() << std::endl;
		}
	}
}

HumanRandomMovement::HumanRandomMovement(std::vector<Human*>* humans): Logic(SGE::LogicPriority::Mid), humans(humans), angle(glm::radians(-90.f), glm::radians(90.f))
{
}

void HumanRandomMovement::performLogic()
{
	for (auto human : *humans)
	{
		this->velocity = human->getVelocity();
		if (human->getCounter() == 0)
		{
			this->velocity = b2Mul(b2Rot(this->angle(this->engine)), this->velocity);
			human->setVelocity(this->velocity);
			//human->body->ApplyForce(b2Vec2(this->velocity.x,this->velocity.y),human->body->GetPosition(),true);
			human->getBody()->SetLinearVelocity(this->velocity);
		}
	}
}

SnapCamera::SnapCamera(const float speed, const SGE::Key up, const SGE::Key down, const SGE::Key left, const SGE::Key right, const SGE::Key snapKey, SGE::Object* snapTo, SGE::Camera2d* cam): Logic(SGE::LogicPriority::Highest), speed(speed), up(up), down(down), left(left), right(right), snapKey(snapKey), snapTo(snapTo), cam(cam)
{
}

void SnapCamera::performLogic()
{
	this->snapped = SGE::isPressed(snapKey); //We need to be able to send signals to actions, like sending actions to objects
	glm::vec2 move = {0, 0};
	if (!this->snapped)
	{
		move = this->snapTo->getPosition();
		this->cam->setPosition(move.x, move.y); //Replace with action, i.e. GoTo
	}
	else
	{
		if (SGE::isPressed(this->up)) move.y += this->speed;
		if (SGE::isPressed(this->down)) move.y -= this->speed;
		if (SGE::isPressed(this->right)) move.x += this->speed;
		if (SGE::isPressed(this->left)) move.x -= this->speed;
		this->sendAction(new SGE::ACTION::Move(this->cam, move.x, move.y, true));
	}
}

Timer::Timer(float time, SGE::Action* action) : Logic(SGE::LogicPriority::Low), time(time), action(action)
{
}

void Timer::performLogic()
{
	if(this->time > .0f)
	{
		this->time -= SGE::delta_time;
	}
	else
	{
		this->isOn = false;
		this->sendAction(this->action);
	}
}
