#include "Rect.h"

Rect::Rect()
{
	
}

Rect::Rect(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
}

Rect::Rect(unsigned int left, unsigned int top, unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
	this->left = left;
	this->top = top;
}

Rect::Rect(const Rect& rect)
{
	this->width = rect.width;
	this->height = rect.height;
	this->left = rect.left;
	this->top = rect.top;
}

//Rect::~Rect(){	}