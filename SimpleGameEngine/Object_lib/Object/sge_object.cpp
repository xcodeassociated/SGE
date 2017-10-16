#include "sge_object.hpp"

SGE::ObjectID::ObjectID(const long id, SGE::Object* o) : ID(id), obj(o)
{
}

SGE::ObjectID::ObjectID() : ID(0)
{
}

SGE::ObjectID::ObjectID(SGE::Object* o) : ID(-1L), obj(o)
{
}

SGE::Object* SGE::ObjectID::getObject() const
{
	return this->obj;
}

SGE::Object* SGE::ObjectID::operator->() const
{
	return this->obj;
}

SGE::Object::Object(float x, float y): X(x), Y(y)
{
}

SGE::Object::Object(float x, float y, Shape* shape): X(x), Y(y), shape(shape)
{
}

SGE::Object::Object(float x, float y, bool draw): X(x), Y(y), drawable(draw)
{
}

SGE::Object::Object(float x, float y, bool draw, Shape* shape): X(x), Y(y), drawable(draw), shape(shape)
{
}

SGE::Object::~Object()
{
	if (this->shape->isDisposable()) delete this->shape;
}

float& SGE::Object::getX() noexcept
{
	return this->X;
}

float& SGE::Object::getY() noexcept
{
	return this->Y;
}

void SGE::Object::setDrawable(bool e) noexcept
{
	this->drawable = e;
}

bool SGE::Object::getDrawable() const noexcept
{
	return this->drawable;
}

void SGE::Object::setPosition(float x, float y)
{
	this->X = x;
	this->Y = y;
}

glm::vec2 SGE::Object::getPosition() const noexcept
{
	return glm::vec2(this->X, this->Y);
}

SGE::Shape* SGE::Object::getShape() noexcept
{
	return this->shape;
}

SGE::LogicPriority SGE::Object::getLock() const noexcept
{
	return lock;
}

void SGE::Object::setLock(const LogicPriority lock) noexcept
{
	this->lock = lock;
}

SGE::VoidObject::VoidObject(): Object()
{
}

SGE::ObjectBind::ObjectBind(const std::initializer_list<ObjectID>& object)
{
			this->_begin = new ObjectID[object.size()];
			int i = 0;
			for (ObjectID o : object) {
				*(this->_begin + i) = o;
				i++;
			}
			this->_end = (this->_begin + object.size());
		}

SGE::ObjectBind::ObjectBind(ObjectID object) : ObjectBind({ object })
{
}

SGE::ObjectBind::~ObjectBind()
{
	if (this->_begin != nullptr)
		delete[] this->_begin;
}

SGE::ObjectBind::ObjectBind(const ObjectBind& b)
{
	this->_begin = new ObjectID[b.size()];
	int i = 0;
	for (ObjectID o : b) {
		*(this->_begin + i) = o;
		i++;
	}
	this->_end = (this->_begin + i);
}

SGE::ObjectBind::ObjectBind(ObjectBind&& b) : _begin(b._begin), _end(b._end)
{
	b._begin = nullptr;
	b._end = nullptr;
}

SGE::ObjectBind& SGE::ObjectBind::operator=(const ObjectBind& b)
{
	if (this != &b) {
		this->_begin = new ObjectID[b.size()];
		int i = 0;
		for (ObjectID o : b) {
			*(this->_begin + i) = o;
			i++;
		}
		this->_end = (this->_begin + i);
	}
	return *this;
}

SGE::ObjectBind& SGE::ObjectBind::operator=(ObjectBind&& b) noexcept
{
	if (this != &b) {
		this->_begin = b._begin;
		this->_end = b._end;
		b._begin = nullptr;
		b._end = nullptr;
	}
	return *this;
}

SGE::ObjectID& SGE::ObjectBind::operator[](std::size_t i)
{
	return *(this->_begin + i);
}

const SGE::ObjectID& SGE::ObjectBind::operator[](std::size_t i) const
{
	return *(this->_begin + i);
}

SGE::ObjectID* SGE::ObjectBind::begin()
{
	return this->_begin;
}

SGE::ObjectID* SGE::ObjectBind::end()
{
	return this->_end;
}

SGE::ObjectID* SGE::ObjectBind::begin() const
{
	return this->_begin;
}

SGE::ObjectID* SGE::ObjectBind::end() const
{
	return this->_end;
}

std::size_t SGE::ObjectBind::size() const
{
	return this->_end - this->_begin;
}

