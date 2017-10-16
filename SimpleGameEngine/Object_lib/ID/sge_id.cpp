#include "sge_id.hpp"

SGE::ID::ID(const long _id): id(_id)
{
}

long SGE::ID::getID() const
{
	return id;
}

bool SGE::ID::operator<(const ID& _id) const
{
	return id < _id.id;
}

bool SGE::ID::operator==(const ID& _id) const
{
	return this->id == _id.id;
}
