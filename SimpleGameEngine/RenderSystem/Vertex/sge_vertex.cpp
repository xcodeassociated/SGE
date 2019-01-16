#include "sge_vertex.hpp"

void SGE::Vertex::setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

void SGE::Vertex::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

void SGE::Vertex::setUV(float u, float v)
{
	uv.u = u;
	uv.v = v;
}
