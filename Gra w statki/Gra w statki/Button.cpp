#include "Button.h"

Button::Button(float width, float height, float x, float y, int button_ID):width(width), height(height), x(x), y(y), button_ID(button_ID)
{
	highlighted = false;
}

void Button::setWidth(float width)
{
	this->width = width;
}

void Button::setHeight(float height)
{
	this->height = height;
}

void Button::setX(float x)
{
	this->x = x;
}

void Button::setY(float y)
{
	this->y = y;
}

void Button::setHighlighted(bool h)
{
	highlighted = h;
}

float Button::getX()
{
	return x;
}

float Button::getY()
{
	return y;
}

float Button::getHeight()
{
	return height;
}

float Button::getWidth()
{
	return width;
}

bool Button::getHighlighted()
{
	return highlighted;
}

int Button::getButtonID()
{
	return button_ID;
}