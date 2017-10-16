#include "sge_director.hpp"

SGE::Director::Director(int w, int h): relay(SGE::Relay::getRelay()), Width(w), Height(h)
{
	this->relay->registerDirector(this);
}

SGE::Director::~Director()
{
}

SGE::Director* SGE::Director::getDirector(int w, int h)
{
	static Director* director = new Director(w, h);
	return director; //Can convert to ARC later.
}

std::pair<int, int> SGE::Director::getResolution()
{
	return std::make_pair(this->Width, this->Height);
}

void SGE::Director::finalize()
{
}
