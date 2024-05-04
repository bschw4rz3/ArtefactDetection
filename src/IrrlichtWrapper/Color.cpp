#include "Color.h"

Color::Color()
{
	this->a = 0;
	this->r = 0;
	this->g = 0;
	this->b = 0;
}

Color::Color(int a, int r, int g, int b)
{
	this->a = a;
	this->r = r;
	this->g = g;
	this->b = b;
}