#include "sge_vertex.hpp"

SGE::Position::Position(float _x, float _y): x(_x), y(_y)
{
}


SGE::Color::Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a): r(_r), g(_g), b(_b), a(_a)
{
}


SGE::UV::UV(float _u, float _v): u(_u), v(_v)
{
}

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

SGE::Vertex::Vertex()
{
}

SGE::Vertex::~Vertex()
{
}
