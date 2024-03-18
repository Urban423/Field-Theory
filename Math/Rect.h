#pragma once

class Rect
{
public:
	Rect();
	Rect(unsigned int width, unsigned int height);
	Rect(unsigned int left, unsigned int top, unsigned int width, unsigned int height);
	Rect(const Rect& rect);
	//~Rect();
public:
	unsigned int width  = 0;
	unsigned int height = 0;
	unsigned int left  = 0;
	unsigned int top = 0;
};